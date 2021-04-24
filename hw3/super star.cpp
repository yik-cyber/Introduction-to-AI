#include <bits/stdc++.h>
using namespace std;

const int MAXN = 33;
const double eps = 1e-9;
double px[MAXN], py[MAXN], pz[MAXN];

double cal_dis(double x1, double y1, double z1,
               double x2, double y2, double z2){
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2) + pow(z1-z2, 2));
}

int n;
pair<double, int> max_dis(double x, double y, double z){
    double m = -1, tmp;
    int pos = 0;
    for(int i = 0; i < n; i++){
        tmp = cal_dis(x, y, z, px[i], py[i], pz[i]);
        if(tmp > m){
            pos = i;
            m = tmp;
        }
    }
    return {m, pos};
}


int main(){
    while(scanf("%d", &n) && n != 0){
        for(int i = 0; i < n; i++) scanf("%lf %lf %lf",&px[i], &py[i], &pz[i]);
        double x = px[0], y = py[0], z = pz[0];
        double nx, ny, nz, r, ans = 10000000;
        double step = 100.0;
        pair<double, int> pair;
        while(step > eps){
            pair = max_dis(x, y, z);
            r = pair.first;
            int far_pos = pair.second;
            ans = min(ans, r);
            x += (px[far_pos] - x)/r*step;
            y += (py[far_pos] - y)/r*step;
            z += (pz[far_pos] - z)/r*step;

            step *= 0.98;
        }
        printf("%.5lf\n", ans);
    }
}
