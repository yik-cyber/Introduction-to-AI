#include<bits/stdc++.h>
using namespace std;

char board[4][4];

/*is the player winner?*/
bool is_win(char cur){
    int i;
    for(i = 0; i < 4; i++){
        if(board[i][0] == cur && board[i][1] == cur && board[i][2] == cur && board[i][3] == cur) return true;
        if(board[0][i] == cur && board[1][i] == cur && board[2][i] == cur && board[3][i] == cur) return true;
    }
    if(board[0][0] == cur && board[1][1] == cur && board[2][2] == cur && board[3][3] == cur) return true;
    if(board[0][3] == cur && board[1][2] == cur && board[2][1] == cur && board[3][0] == cur) return true;
    return false;
}

int chess_num = 0;
int inf, sup;
int minimax_search(bool is_x){
    if(is_win('x')) return 1;
    if(is_win('o')) return -1;
    if(chess_num == 16) return -1;
    
    int score;
    if(is_x){
        score = -100;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(board[i][j] != '.') continue;
                board[i][j] = 'x';
                chess_num++;
                score = max(score, minimax_search(!is_x));
                board[i][j] = '.';
                chess_num--;
                if(score >= sup) return score;
                inf = max(inf, score); //更新最大下界
            }
        }
        return score;
    }
    else{
        score = 100;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(board[i][j] != '.') continue;
                board[i][j] = 'o';
                chess_num++;
                score = min(score, minimax_search(!is_x));
                board[i][j] = '.';
                chess_num--;
                if(score < 1) return -1; //只要有一个输了就不行
                sup = min(sup, score); //更新最小上界
            }
        }
        return score;
    }
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
        inf = -100;
        sup = 100;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(board[i][j] != '.') continue;
                board[i][j] = 'x';
                chess_num++;
                if(minimax_search(false) == 1){
                    printf("(%d,%d)\n", i, j);
                    flag = true;
                    break;
                }
                board[i][j] = '.';
                chess_num--;
            }
            if(flag) break;
        }
        if(!flag) printf("#####\n");
    }
}

/*
reference
https://zhuanlan.zhihu.com/p/113635577
*/
