//
// Created by Coder on 2018/2/8.
//

#include <iostream>
#include <limits>

using namespace std;

void swap(int &a, int &b){
    int mid = a;
    a = b;
    b = mid;
}

//求最大公约数
int max_public_num(int a, int b){
    int result;
    if(a==0 || b==0)
        return 0;
    int min = a > b ? b : a;
    for(int i=1; i<=min; i++){
        if(a%i == 0 && b%i == 0)
            result = i;
    }
    return result;
}

typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//中序遍历递增
//bool isBSTree(BiTree root){
//    static bool flag = true;
//    static int last = INT32_MIN;
//
//    if (root->lchild != NULL && flag)
//        isBSTree(root->lchild);
//    if (root->data < last)
//        flag = false;
//    last = root->data;
//    if (root->rchild != NULL && flag)
//        isBSTree(root->rchild);
//    return flag;
//}

//中序遍历递增
bool isBSTree(BiTree root){
    static int last = INT32_MIN;

    if (root->lchild != NULL)
        isBSTree(root->lchild);
    if (root->data < last)
        return false;
    last = root->data;
    if (root->rchild != NULL)
        isBSTree(root->rchild);
    return true;
}

//01背包问题
int bag()
{
    //注意--体积和花费都是正整数
    //a[i][j]代表前i件物品可以放入j体积的背包中的最大价值(前i件物品并不一定都放的进去)
    //数组的0下标都未使用
    int a[6][13] = {{0}};
    int val[6] = {0 , 2 , 5 , 3 , 10 , 4};  //花费
    int vol[6]   = {0 , 1 , 3 , 2 , 6 , 2}; //物体体积
    int bagV = 12;

    for( int i = 1; i< sizeof(val)/sizeof(int); i++)
    {
        for( int j = 1; j<=bagV; j++)
        {
            if(j<vol[i])
                //第i件物品无法放入背包
                a[i][j] = a[i-1][j];
            else
                //a[i-1][j]----不把第i件物品放进背包的价值
                //a[i-1][j-vol[i]] + val[i]----把第i件物品放入背包的价值
                a[i][j] = max(a[i-1][j] , a[i-1][j-vol[i]] + val[i]);
//            cout<<a[i][j]<<' ';
        }
        cout<<endl;
    }
    cout<<a[5][12]<<endl;

    return 0;
}

int main(){
//    cout<<max_public_num(0, 20);
//    BiTNode n1, n2, n3, n4;
//    n1.data = 5;
//    n2.data = 24;
//    n3.data = 53;
//    n4.data = 12;
//    n1.lchild = &n2;
//    n1.rchild = &n3;
//    n2.lchild = &n4;
//    n2.rchild = NULL;
//    n3.rchild = NULL;
//    n3.lchild = NULL;
//    n4.rchild = NULL;
//    n4.lchild = NULL;
//    cout<<INT32_MIN<<endl;
//    cout<<isBSTree(&n1);
    bag();
    return 0;
}
