//
// Created by Coder on 2018/2/22.
//

#include <iostream>
#include <stack>

using namespace std;

typedef struct TreeNode{
    int value;
    struct TreeNode *lchild, *rchild;
}TreeNode;


//二叉树的深度优先遍历
void DFS(TreeNode* root)
{
    stack<TreeNode*> s;
    TreeNode *p;
    s.push(root);
    while(!s.empty())
    {
        p=s.top();
        cout<<p->value<<endl;
        s.pop();
        if(p->rchild)
            s.push(p->rchild);
        if(p->lchild)
            s.push(p->lchild);
    }
}


//a存数塔
int a[6][6]= {
        {0},
        {0, 7},
        {0, 3,8},
        {0, 8, 1, 0},
        {0, 2, 7, 4, 4 },
        {0, 4, 5, 2, 6, 5}
};
//b数组存最佳方案
//b[i][j]----以b[i][j]为顶的子数塔的最佳方案
int best[6][6];
void num() {
    //先对最底层赋值
    for(int i=1; i<=5; i++)
        best[5][i] = a[5][i];
    //从上往下的递推
    for (int i=4; i>0; i--) {
        for (int j=1; j<=i; j++) {
            //a[i][j]总共有两种路可以走
            best[i][j] = a[i][j] + max(best[i+1][j], best[i+1][j+1]);
        }
    }
    cout<<best[1][1]<<endl;
}

//条形图中的最大矩形面积
int MaxRectangle(){
    int a[6] = {2, 1, 5, 6, 2, 3};
    int max[6] = {0};
    int maxi;
    for (int i=0; i<6; i++) {
        maxi = a[i];
        //往左查找
        for (int j=i-1; j>=0; j--) {
            if (a[j] >= a[i]) {
                maxi += a[i];
            }else {
                break;
            }
        }

        //往右查找
        for (int j=i+1; j<6; j++) {
            if (a[j] >= a[i]) {
                maxi += a[i];
            }else {
                break;
            }
        }
        max[i] = maxi;
    }
    int result = 0;
    for (int i=0; i<5; i++) {
        result = result < max[i] ? max[i] : result;
    }
    cout<<result<<endl;
}

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <String.h>
#define MAXLENGTH 1000

using namespace std;

int a[MAXLENGTH][MAXLENGTH];

void LCS_LENGTH(char x[], char y[], int x_length, int y_length){

    memset(a, MAXLENGTH*MAXLENGTH, sizeof(int));

    for(int i=0; i<=x_length; i++){
        a[i][0] = 0;
    }
    for(int j=0; j<=y_length; j++){
        a[0][j] = 0;
    }

    for(int i=1; i<=x_length; i++){
        for(int j=1; j<=y_length; j++){
            if(x[i-1] == y[j-1]){
                a[i][j] = a[i-1][j-1] +1;
                //  b[i][j] = '';
            }else{
                a[i][j] = a[i][j-1]>=a[i-1][j] ? a[i][j-1] : a[i-1][j];
            }
        }
    }

    for(int i=0; i<=x_length; i++){
        for(int j=0; j<=y_length; j++){
            cout << a[i][j];
        }
        cout<<endl;
    }
    return;
}


int main(){

    char x[MAXLENGTH], y[MAXLENGTH];

    while(cin >>x >>y){
        LCS_LENGTH(x, y, strlen(x), strlen(y));
    }
    return 0;
}