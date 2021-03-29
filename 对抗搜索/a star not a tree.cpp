#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-2;
const int N = 110;
double dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
double dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
double px[N], py[N];

int n;
double tot_dis(double x, double y){
    double sum = 0;
    for(int i = 0 ; i < n; i++){
        sum += sqrt((x-px[i])*(x-px[i]) + (y-py[i])*(y-py[i]));
    }
    return sum;
}

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lf %lf", &px[i], &py[i]);
    double step = 1000;
    double min_tot_dis = tot_dis(px[0], py[0]), tmp_dis;
    double nx, ny, prex = px[0], prey = py[0];
    bool flag = false;
    while(step > eps){
        flag = false;
        for(int i = 0; i < 8; i++){
            nx = prex + dx[i] * step;
            ny = prey + dy[i] * step;
            if((tmp_dis = tot_dis(nx, ny)) < min_tot_dis){
                min_tot_dis = tmp_dis;
                prex = nx;
                prey = ny;
                flag = true;
            }
        }
        if(!flag) step /= 2;
    }
    printf("%.0f", min_tot_dis);
}
