#include<bits/stdc++.h>
using namespace std;
const int N = 10;
int mp[N][N];
bool row[N][N], column[N][N], cell[N][N];
int test, leftn;
struct Node{
    public:
    int x, y;
}lef[90];

#define GET_CELL(i, j) i/3*3+j/3

void init(){
    leftn = 0;
    memset(row, false, sizeof(row));
    memset(column, false, sizeof(column));
    memset(cell, false, sizeof(cell));    
}
bool search(int l){
    if(l == leftn){
        return true;
    } 
    int i, j, k, t;
    i = lef[l].x;
    j = lef[l].y;
    t = GET_CELL(i, j);
    for(k = 1; k <= 9; k++){
        if(row[i][k]||column[j][k]||cell[t][k]) continue;
        mp[i][j] = k;
        row[i][k] = column[j][k] = cell[t][k] = true;
        if(search(l+1)) 
            return true;
        mp[i][j] = 0;
        row[i][k] = column[j][k] = cell[t][k] = false;            
    }
    return false;
}

int main(){
    scanf("%d", &test);
    char tchar[12];
    int val, t;
    while(test--){
        init();
        for(int i = 0; i < 9; i++){
            scanf("%s", tchar);
            for(int j = 0; j < 9; j++){
                val = tchar[j] - '0';
                assert(val <= 9);
                mp[i][j] = val;
                if(val > 0){
                    t = GET_CELL(i, j);
                    row[i][val] = column[j][val] = cell[t][val]= true;
                }
                else{
                    lef[leftn].x = i;
                    lef[leftn++].y = j;
                }
            }
        }
        search(0);
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                printf("%d", mp[i][j]);
            }
            printf("\n");
        }
    }
}

