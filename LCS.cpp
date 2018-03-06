//
// Created by Coder on 2018/2/22.
//
#include <iostream>
#include <algorithm>
#include <String.h>

#define MAXLENGTH 1000

using namespace std;

int a[MAXLENGTH][MAXLENGTH];

void LCS_LENGTH(char x[], char y[], int x_length, int y_length){

    memset(a, MAXLENGTH*MAXLENGTH, sizeof(int));
    //初始化
    for(int i=0; i<=x_length; i++)
        a[i][0] = 0;
    for(int j=0; j<=y_length; j++)
        a[0][j] = 0;
    //执行递推式
    for(int i=1; i<=x_length; i++){
        for(int j=1; j<=y_length; j++){
            if(x[i-1] == y[j-1])
                a[i][j] = a[i-1][j-1] +1;
            else
                a[i][j] = a[i][j-1]>=a[i-1][j] ? a[i][j-1] : a[i-1][j];
        }
    }
    //打印递推矩阵
    for(int i=0; i<=x_length; i++){
        for(int j=0; j<=y_length; j++){
            cout << a[i][j];
        }
        cout<<endl;
    }
}



int main(){
    char x[MAXLENGTH], y[MAXLENGTH];
    while(cin >>x >>y){
        LCS_LENGTH(x, y, strlen(x), strlen(y));
    }
    return 0;
}
