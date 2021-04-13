/*
*ref:https://zhuanlan.zhihu.com/p/111239376
*/


#include<bits/stdc++.h>
using namespace std;

struct State{
    public:
    int boat_loc; //0 left, and 1 right
    int left_missionary_num;
    int left_cannibal_num;
    int step;
    int fun_val; //function value
    
    State(){}
    State(int bl, int lm, int lc, int s):
         boat_loc(bl), left_missionary_num(lm), left_cannibal_num(lc), step(s){
             fun_val = - (2*left_missionary_num + left_cannibal_num - 2 * boat_loc);
         }

};
bool operator<(const State& a, const State& b){
        return a.fun_val < b.fun_val;
}
int m, n;
bool IsValid(int lmn, int lcn){
    //a best condition
    return (lmn == 0 || lmn == m || lcn == lmn) && lmn >= 0 && lmn <= m;
}
priority_queue<State> unsearched;
vector<State> searched;
bool IsSearched(int lmn, int lcn, int bl){
    for(auto state: searched){
        if(!((bl != state.boat_loc) || (lcn != state.left_cannibal_num) ||
               (lmn != state.left_missionary_num))) return true;
    }
    return false;
}


int main(){
    scanf("%d %d", &m, &n);
    unsearched.push(State(0, m, m, 0));
    
    State t_st;
    int t_bl, t_mn, t_cn, t_fv;
    while(!unsearched.empty()){
        State st = unsearched.top();
        unsearched.pop();
        searched.push_back(st);
        
        //the boat is at left
        if(!st.boat_loc){
            //from high to low
            for(int mn = min(n, st.left_missionary_num); mn > 0; mn--){
                for(int cn = min(n - mn, mn); cn >= 0; cn--){
                    t_mn = st.left_missionary_num - mn;
                    t_cn = st.left_cannibal_num - cn;
                    
                    if(IsValid(t_mn, t_cn) && !IsSearched(t_mn, t_cn, 1)){
                        if(t_mn == 0 && t_cn == 0){
                            printf("%d",  st.step + 1);
                            exit(0);
                        }
                        unsearched.push(State(1, t_mn, t_cn, st.step + 1));
                    }
                }
            }
            //There is no missinaries in the boat
            for(int cn = min(n, st.left_cannibal_num); cn >= 1; cn--){
                t_mn = st.left_missionary_num;
                t_cn = st.left_cannibal_num - cn;
                    
                if(IsValid(t_mn, t_cn) && !IsSearched(t_mn, t_cn, 1)){
                     if(t_mn == 0 && t_cn == 0){
                        printf("%d",  st.step + 1);
                        exit(0);
                    }
                    unsearched.push(State(1, t_mn, t_cn, st.step + 1));
                }
            }
        }
        else{
            //from low to high
            for(int mn = 1; mn <= min(n ,m - st.left_missionary_num); mn++){
                for(int cn = 0; cn <= min(mn, n - mn); cn++){
                    t_mn = st.left_missionary_num + mn;
                    t_cn = st.left_cannibal_num + cn;
                    
                    if(IsValid(t_mn, t_cn) && !IsSearched(t_mn, t_cn, 0)){
                        if(t_mn == 0 && t_cn == 0){
                            printf("%d",  st.step + 1);
                            exit(0);
                        }
                        unsearched.push(State(0, t_mn, t_cn, st.step + 1));
                    }
                }
            }
            //There is no missinaries in the boat
            for(int cn = 1; cn <= min(n, m - st.left_cannibal_num); cn++){
                t_mn = st.left_missionary_num;
                t_cn = st.left_cannibal_num + cn;
                    
                if(IsValid(t_mn, t_cn) && !IsSearched(t_mn, t_cn, 0)){
                     if(t_mn == 0 && t_cn == 0){
                        printf("%d",  st.step + 1);
                        exit(0);
                    }
                    unsearched.push(State(0, t_mn, t_cn, st.step + 1));
                }
            }
        }

    }
    printf("-1\n");
}
