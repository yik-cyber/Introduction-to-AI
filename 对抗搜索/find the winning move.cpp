#include<bits/stdc++.h>
using namespace std;

char board[4][4];

/*is the player winner?*/
bool is_win(char cur){
    int i, j;
    bool dia_1 = true, dia_2 = true; 
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            if(board[i][j] != cur) break;
        }
        if(j >= 4) return true;
        if(board[i][i] != cur) dia_1 = false;
        for(j = 0; j < 4; j++){
            if(board[j][i] != cur) break;
        }
        if(j >= 4) return true;
        if(board[i][3-i] != cur) dia_2 = false;
    }
    if(dia_2 || dia_1) return true;
    return false;
}


int chess_num = 0;
int inf, sup;
int minimax(bool is_x){
    if(is_win('x')) return 1;
    if(is_win('o')) return -1;
    if(chess_num == 16) return -1;

    int score = (is_x ? -1 : 1) * 100;
    char cur = is_x ? 'x' : 'o';
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j] != '.') continue;
            board[i][j] = cur;
            chess_num++;
            score = is_x ? max(score, minimax(!is_x)) : min(score, minimax(!is_x));
            board[i][j] = '.';
            chess_num--;
            if(is_x){
                if(score > sup) return score;
                inf = max(inf, score);
            }
            else{
                if(score < 1) return -1;
                sup = min(sup, score);
            }
        }
    }
    return score;
}

int main(){
    char c;
    while(scanf("%c", &c) && c != '$'){
        getchar();
        chess_num = 0;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                scanf("%c", &board[i][j]);
                if(board[i][j] != '.')
                    chess_num++;
            }
            getchar();
        }
        bool flag = false;
        if(chess_num < 5) goto over;
        inf = -100;
        sup = 100;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(board[i][j] != '.') continue;
                board[i][j] = 'x';
                chess_num++;
                if(minimax(false) == 1){
                    printf("(%d,%d)\n", i, j);
                    flag = true;
                    break;
                }
                board[i][j] = '.';
                chess_num--;
            }
            if(flag) break;
        }
        over:
            if(!flag) printf("#####\n");
    }
}


/*
reference
https://zhuanlan.zhihu.com/p/113635577
*/
