#include<bits/stdc++.h>
#define maxn 505

struct Matrix{
    const double eps = 1e-9;
    int n, m;
    double val[maxn][maxn];
    Matrix(int n, int m){
        this -> n = n;
        this -> m = m;
        memset(val, 0, sizeof(val));
    }
    double* operator [](int x){
        return val[x];
    }

    void swap(double &x, double &y){
        double temp = x;
        x = y;
        y = temp;
    }

    void swapLine(int x, int y){
        for(int i = 0; i < m; i++) swap(val[x][i], val[y][i]);
    }

    bool GE(void){
        if(n != m - 1) return false;
        for(int i = 0; i < n; i++){
            int maxArg = i;
            for(int j = i + 1; j < n; j++)
                if(std::abs(val[j][i]) > std::abs(val[maxArg][i])) maxArg = j;
            swapLine(maxArg, i);
            if(std::abs(val[i][i]) < eps) return false;
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                double c = val[j][i] / val[i][i];
                for(int k = i; k < m; k++) val[j][k] -= val[i][k] * c;
            }
        }
        for(int i = 0; i < n; i++) val[i][n] /= val[i][i], val[i][i] = 1.0;
        return true;
    }
};