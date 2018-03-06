//
// Created by Coder on 2018/2/13.
//

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

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

//比较函数，快排用
int cmp ( const void *a , const void *b )
{
    return *(int *)a - *(int *)b;
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
    qsort(max, 6, sizeof(int), cmp);
    cout<<max[5]<<endl;
}


//动态规划的一个简单的技巧就是选与不选
//根据选与不选来找到递推式和递推式的状态
//一般有两种情况：
//case 1：          | 选 —— a[i] + opt[prev[i]]
//      opt[i] = max|不选—— opt[i-1]
//case 1：                    | 选 —— Subset(arr, i-1, s-arr[i])
//     Subset(arr, i, s) = max|不选—— Subset(arr, i-1, s)


//今年暑假不AC动态规划版
typedef struct Time {
    int start;
    int end;
    int value;
} Time;

int compare(const void *p1, const void *p2) {
    return (*(Time *)p1).end > (*(Time *)p2).end ? 1 : -1;
}

void DPNoAC(Time a[], int length) {
    //根据结束时间排序
    qsort(a+1, length, sizeof(Time), compare);
    int prev[length+1] , opt[length+1];
    //初始化prev数组
    memset(prev, 0, sizeof(int) * (length+1));
    //找到每个阶段的前驱
    for (int i=2; i<=length; i++) {
        for (int j=i-1; j>=1; j--) {
            if (a[j].end <= a[i].start){
                prev[i] = j;
                break;
            }
        }
    }
    opt[0] = 0;
    for (int i=1; i<=length; i++) {
        opt[i] = max(opt[prev[i]] + a[i].value, opt[i-1]);
    }
    cout<<opt[length]<<endl;
}


void NoAC(Time a[], int length) {
    //根据结束时间排序
    qsort(a+1, length, sizeof(Time), compare);

    //尽量选结束时间早的节目
    int next = a[1].end, count = 1;
    for (int i=2; i<=length; i++) {
        if(a[i].start >= next) {
            next = a[i].end;
            count++;
        }
    }
    cout<<count<<endl;
}


//走台阶，问你一次可以走1步或者走2步，n阶台阶有多少种走法
int FindStep(int n) {
    if(n==0 || n==1 || n==2) {
        return n;
    }

    return FindStep(n-1)+FindStep(n-2);
}

//贪心的加油站
void refuel(int d[], int n, int k) {
    int count = 0, oil = n;
    for (int i = 0; i < k; i++) {
        if(d[i] > n) {
            cout <<"no way"<<endl;
            return;
        }
        if(oil > d[i]) {
            oil -= d[i];
        } else {
            oil = n;
            count++;
        }
    }
}
//士兵排队，分治法
//一共n个士兵，散落的分布在坐标系中
//找中位数
typedef struct Point {
    int x;
    int y;
} Point;
int cmpx(void *p1, void *p2) {
    return ((Point*)p1)->x > ((Point*)p2)->x ? 1 : -1;
}
int cmpy(void *p1, void *p2) {
    return ((Point*)p1)->y > ((Point*)p2)->y ? 1 : -1;
}
void soldier(Point a[], int length) {
    int step = 0;
    qsort(a, length, sizeof(Point), cmpx);
    int x_mid = a[length/2].x;
    for (int i=0; i<length; i++) {
        int loc_i = x_mid - 1 - i;
        step += abs(a[i].x - loc_i);
    }
    qsort(a, length, sizeof(Point), cmpy);
    int y_mid = a[length/2].y;
    for (int i=0; i<length; i++) {
        int loc_i = y_mid - 1 - i;
        step += abs(a[i].y - loc_i);
    }
    cout << step;
}


int main() {
//    num();
//    MaxRectangle();

    int n;
    cin >> n;
    Time a[n+1];
    for (int i=1; i<=n; i++){
        cin >> a[i].start >> a[i].end;
    }
    DPNoAC(a, n);
    NoAC(a, n);

//    cout <<FindStep(10);
}