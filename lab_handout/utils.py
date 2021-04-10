import torch
import torch.nn as nn
import time
import math
from data.data_utils import ExampleForGeneration

def train(model, category_tensor, input_line_tensor, target_line_tensor, criterion, learning_rate):      
    target_line_tensor.unsqueeze_(-1) #transform
    hidden = model.initHidden() #set hidden vector to one
    model.zero_grad()

    loss = 0

    for i in range(input_line_tensor.size(0)):   # complete the forward process of conditional rnn
        output , hidden = model(category_tensor, input_line_tensor[i], hidden)
        l = criterion(output, target_line_tensor[i]) #calculate the loss
        loss += l

    loss.backward()

    for p in model.parameters():
        p.data.add_(p.grad.data, alpha=-learning_rate)

    return output, loss.item() / input_line_tensor.size(0)


def generate_from_category(model, all_categories, category, chars, max_length, start_letter='A'):
     
     n_letters = len(chars) + 1
     category_tensor, input_line_tensor = ExampleForGeneration(all_categories, category, chars, start_letter)

     with torch.no_grad():  # Question 3 : why do we need this ? 
        #此时我们只需要利用网络进行输出，网络传播时不会进行求导和传播，也不会有dropout的影响
        hidden = model.initHidden()
        output_name = start_letter

        for i in range(max_length):
            output , hidden = model(category_tensor, input_line_tensor, hidden)  # complete ! 
            topv, topi = output.topk(1)
            topi = topi[0][0] #get the largest value's index, and chars[topi] is the next char
            if topi == n_letters - 1:
                break
            else:
                letter = chars[topi] #get the generated new letter
                output_name += letter
            category_tensor, input_line_tensor = ExampleForGeneration(all_categories, category, chars, letter) # complete ! 
            #generate a new input line tensor for the new letter, so to find the next letter
        return output_name


def timeSince(since):
    now = time.time()
    s = now - since
    m = math.floor(s / 60)
    s -= m * 60
    return '%dm %ds' % (m, s)