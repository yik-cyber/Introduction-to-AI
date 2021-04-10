import torch
import torch.nn as nn

class RNN(nn.Module):
    def __init__(self, n_categories,input_size, hidden_size, output_size):
        super(RNN, self).__init__()      
        self.hidden_size = hidden_size
        self.n_categories = n_categories
        self.input_combined_size = n_categories + input_size + hidden_size
        self.output_combined_size = output_size + hidden_size
        self.i2h = nn.Linear(self.input_combined_size, hidden_size)   # complete the dimensions for RNN module
        self.i2o = nn.Linear(self.input_combined_size, output_size) 
        self.o2o = nn.Linear(self.output_combined_size, output_size)
        self.dropout = nn.Dropout(0.1)
        self.softmax = nn.LogSoftmax(dim=1)

    def forward(self, category, input, hidden):   
        input_combined = torch.cat((category, input, hidden), 1)  # Question 1: Why do we concatenate category with input and hidden state ?
        hidden = self.i2h(input_combined)
        output = self.i2o(input_combined)
        output_combined = torch.cat((hidden, output), 1)
        output = self.o2o(output_combined)
        output = self.dropout(output)
        output = self.softmax(output)
        return output, hidden

    def initHidden(self):
        return torch.zeros(1, self.hidden_size)
