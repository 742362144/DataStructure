//
// Created by Coder on 2018/3/4.
//

#include<iostream>

using namespace std;

void swap(int& a,int& b)
{
    if(a!=b)
    {
        a^=b;
        b^=a;
        a^=b;
    }
}

//length 当前存储堆的数组长度
void MAX_HEAPIFY(int a[], int length, int i)
{
    //判断当前节点是否为自己和左右孩子三者中最大的那个
    int max_index = i;
    if(2*i < length && a[i] < a[2*i]){
        max_index = 2*i;
    }
    if(2*i+1 < length && a[max_index] < a[2*i+1]){
        max_index = 2*i+1;
    }
    //如果a[i]不是三者最大的元素，则继续往上调整
    if(max_index != i){
        swap(a[i], a[max_index]);
        MAX_HEAPIFY(a, length, max_index);
    }
}

//将每个非叶子节点自下而上调用MAX_HEAPIFY
void BUILD_MAX_HEAP(int a[],int length)
{
    for(int i = length/2-1; i>=0; i--)
    {
        MAX_HEAPIFY(a, length, i);
    }
}
//对a数组进行堆排序
void HEAP_SORT(int a[], int length)
{
    //建大顶堆
    BUILD_MAX_HEAP(a, length);
    for(int i = length-1; i>0;i--)
    {
        swap(a[0], a[length-1]);
        //调整堆，保证最大堆的性质
        MAX_HEAPIFY(a, --length, 0);
    }
}

typedef struct Node {
    int value;
} Node;

int cmp( const void *a ,const void *b)
{
    return (*(Node *)a).value > (*(Node *)b).value ? 1 : -1;
}

int main()
{
//    int a[10] = {16,4,10,14,7,9,3,2,8,1};
//    HEAP_SORT(a,10);
//    for(int i=0;i<10;i++)
//    {
//        cout<<a[i]<<endl;
//    }
    Node s[100];
    for (int i=0; i<100; i++)
        s[i].value = 100 - i;
    qsort(s, 100, sizeof(s[0]), cmp);
    for (int i=0; i<100; i++)
        cout<<s[i].value<<endl;
}