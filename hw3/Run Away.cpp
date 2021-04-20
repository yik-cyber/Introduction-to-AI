#include<bits/stdc++.h>
using namespace std;

#define TOT 1010
#define RNUM 15
#define RDIREC 25
#define RANDP(scale) (rand()%1000+1)/1000.0*scale
const double eps = 1e-3;
double x_max, y_max;
int m, t;
double p_x[TOT], p_y[TOT], q_x[RNUM], q_y[RNUM], q_mind[RNUM];

double CalDis(double x1, double y1, double x2, double y2){
    return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}
double GetMinDis(double x, double y){
    double mind = 2e11, tmp;
    for(int i = 0; i < m; i++){
        tmp = CalDis(x, y, p_x[i], p_y[i]);
        mind = min(mind, tmp); 
    }
    return mind;
}

void solve(){
    for(int i = 0; i < RNUM; i++){
        q_x[i] = RANDP(x_max);
        q_y[i] = RANDP(y_max);
        q_mind[i] = GetMinDis(q_x[i], q_y[i]);
    }
    double cur = sqrt(CalDis(x_max, y_max, 0, 0));
    while(cur > eps){
        for(int i = 0; i < RNUM; i++){
            for(int j = 0; j < RDIREC; j++){
                double angle = RANDP(M_PI*10);
                double go_x = q_x[i] + cur * cos(angle);
                double go_y = q_y[i] + cur * sin(angle);
                if(go_x < 0 || go_x > x_max || go_y < 0 || go_y > y_max) continue;
                double min_dis = GetMinDis(go_x, go_y);
                if(min_dis > q_mind[i]){
                    q_mind[i] = min_dis;
                    q_x[i] = go_x;
                    q_y[i] = go_y;
                }
            }
        }
        cur  = cur * 0.9;
    }
    double max_dis = q_mind[0], xp = q_x[0], yp = q_y[0];
    for(int i = 1; i < RNUM; i++){
        if(max_dis < q_mind[i]){
            max_dis = q_mind[i];
            xp = q_x[i];
            yp = q_y[i];
        }
    }
    printf("The safest point is (%.1lf, %.1lf).\n", xp, yp);

}

int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%lf %lf %d", &x_max, &y_max, &m);
        for(int i = 0;i < m; i++) scanf("%lf %lf", &p_x[i], &p_y[i]);
        solve();
    }
}
