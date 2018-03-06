#include "library.h"

#include <iostream>

//void hello() {
//    std::cout << "Hello, World!" << std::endl;
//}


/*
 * 总体思想如下：
 * 1.复习好课本常用算法，如排序、链表基本操作、二叉树的遍历（快排一定要记住）
 * 2.注意常规算法的变形，如17年、16年
 * 3.注意新问题、新算法、新思路
 * */

//快排必须记住
int Partition(int a[], int low, int high){
    //交换顺序表中子表r[low..high]的记录，枢轴记录到位，并返回其所在位置
    //在他之前(后)的记录均不大(小)于它
    int pivotkey = a[low];  //pivotkey作为分界
    while(low < high){
        while(low<high && a[high]>pivotkey) --high; //第一次a[low]会被覆盖掉
        a[low] = a[high];
        while(low<high && a[low] <=pivotkey) ++low;
        a[high] = a[low];
    }
    a[low] = pivotkey;
    return low;
}

void QSort(int a[], int low , int high){
    if(low < high){
        int privotloc = Partition(a, low, high);
        QSort(a, low , privotloc-1);
        QSort(a, privotloc+1, high);
    }
}

typedef struct Btree {
    char data[10];
    int weight;
    struct Btree  *left, *right;
} Btree;

/*
 * ---------------17 year--------------------------
 * */
//中序遍历表达式树 输出中序表达式
//my answer
void get_mid(node *root){
    if(root == NULL){
        return;
    }
    if(root->left != NULL){
        get_mid(root->left);
    }else{
        std::cout << '(';
    }
    std::cout << root->data;
    if(root->right != NULL){
        get_mid(root->right);
    }else{
        std::cout << ')';
    }
}

//right answer
void BtreeToExp(Btree *root, int deep){
    if(root == NULL) return;
    else if(root->left==NULL && root->right==NULL){
        printf("%s", root->data);
    }
    else{
        if(deep > 1)    printf("(");    //root node dont print '(' ')'
        BtreeToExp(root->left, deep+1);
        printf("%s", root->data);
        BtreeToExp(root->right, deep+1);
        printf(")");
    }
}

void BtreeToE(Btree *root){
    BtreeToExp(root, 1);
}

/*
 * ---------------16 year--------------------------
 * */
//my answer
//先快排，再取中心点为分界点

//right answer
//答案程序写的不清晰，下面是我改写的
//利用快排思想进行划分
//1.当划分点下标i为i=(low+high)/2时，划分完成
//2.当划分完i小于i=(low+high)/2时，划分a[i+1, high]
//3.当划分完i大于i=(low+high)/2时，划分a[low, i-1]

void setPartition(int a[], int low, int high){
    int final_pivot = (low + high)/2;
    int pivot = Partition(a, low, high);
    while(pivot != final_pivot) {
        if (pivot < final_pivot) {
            pivot = Partition(a, pivot + 1, high);
        } else {
            pivot = Partition(a, low, pivot - 1);
        }
    }
}


/*
 * ---------------15 year--------------------------
 * */
//这个较为简单
//空间换时间
//1.先申请一个a[n]空间大小的内存记录，值在1~n的范围是否出现
//2.没访问一个节点，去a[n]查看是否存在过，存在删除，不存在将a[|node->data|]变为1，继续遍历
typedef struct linknode{
    int data;
    linknode *next;
} LinkNode;

LinkNode* initLink(int a[], int length){
    LinkNode *plink = (LinkNode *) malloc(sizeof(LinkNode) * length);
    for(int i=0; i<length; i++){
        plink[i].data = a[i];
        if(i != 0){
            plink[i-1].next = &plink[i];
        }
    }
    plink[length-1].next = NULL;
    return  plink;
}

void listunique(LinkNode *front, int n){
    int *a = (int *)malloc(sizeof(int) *(n+1));
    for(int i=0; i<=n; i++){
        a[i] = 0;
    }
    LinkNode *plink = front, *lastnode =front;
    while(plink != NULL){
        int i = plink->data >=0 ? plink->data : -plink->data;
        if(a[i] == 1){	//已存在，删除当前节点
            LinkNode *pd = plink;
            plink = plink->next;
            lastnode->next = plink;
        }else{	//不存在，继续遍历
            a[i] = 1;
            lastnode = plink;
            plink = plink->next;
        }
    }
}
int main(){
    int a[14] = {100,199,31,-131,2,9,-31,20,0,112,-100,78,-1,-22};
    LinkNode *plink = initLink(a, 14);
    listunique(plink, 200);
    while(plink != NULL){
        printf("%d ",plink->data);
        plink= plink->next;
    }
}

/*
 * ---------------14 year--------------------------
 * */

//求WPL——带权路径长度

int wpl_PreOrder(Btree *root, int deep){
    static int wpl = 0;    //c中的static
    if(root->left == NULL && root->right){
        wpl += root->weight * deep;
    }
    if(root->left != NULL){
        wpl_PreOrder(root->left, deep+1);
    }
    if(root->right != NULL){
        wpl_PreOrder(root->right, deep+1);
    }
    return wpl;
}

int WPL(Btree *root){
    if(root == NULL){
        return 0;
    }
    wpl_PreOrder(root, 0);
}

/*
 * ---------------13 year--------------------------
 * */

//number counter
//找众数， 且数量要大于 n/2

//my answer
int getMainNumber(int a[], int n, int length){
    int *b = (int *) malloc(sizeof(int) * (n+1));
    for(int i=0; i<=n; i++)
        b[i] = 0;
    for(int i=0; i<length; i++){
        b[a[i]]++;
    }
    int max = 0;
    int main = 0;
    for(int i=0; i<=n; i++){
        if(b[i] > max){
            max = b[i];
            main = i;
        }
    }
    return max > n/2 ? main : -1;
}

//right answer
int Majority(int a[], int n){
    int num=a[0], count=1;
    for(int i=1; i<n; i++){
        if(a[i] == num){
            count++;
        }else{
            if(count>0){
                count--;
            }else{
                num=a[i];
                count = 1;
            }
        }
        if(count>0){
            count = 0;
            for(int i=0; i<n; i++){
                if(a[i] == num){
                    count++;
                }
            }
        }
        return count > n/2 ? num : -1;
    }
}

/*
 * ---------------12 year--------------------------
 * */
//同尾单词，求单词共同后缀起始位置
//1.遍历统计单词长度la、lb
//2.取两指针，相隔|la - lb|
//3.同时对两链表遍历，并比较指针域的值
int getListLength(LinkNode *head){
    int counter = 0;
    while(head != NULL){
        counter++;
        head = head->next;
    }
    return counter;
}

LinkNode* getSameNode(LinkNode *head1, LinkNode *head2){
    int la = getListLength(head1);
    int lb = getListLength(head2);
    if(la > lb){
        int step = la-lb;
        while(step > 0){
            head1 = head1->next;
            step--;
        }
    }else{
        int step =  lb-la;
        while(step > 0){
            head2 = head2->next;
            step--;
        }
    }
    while(head1 != head2){
        head1 = head1->next;
        head2 = head2->next;
    }
    return head1 == NULL ? NULL : head1;
}

/*
* ---------------11 year--------------------------
* */

//求两个升序序列中位数
//merge

int merge(int a[], int la, int b[], int lb){
    int index=0, mid, ia=0, ib=0;
    while(ia<la && ib<lb){
        if(a[ia] <b[ib]){
            mid = a[ia];
            ia++;
        }else{
            mid = b[ib];
            ib++;
        }
        index++;
        if(index == (la+lb)/2)
            return mid;
    }
    if(ia == la){
        for (int i=ib; i<lb; i++){
            index++;
            mid = b[i];
            if(index == (la+lb)/2)
                return mid;
        }
    }else{
        for (int i=ia; i<la; i++){
            index++;
            mid = a[i];
            if(index == (la+lb)/2)
                return mid;
        }
    }
}


/*
* ---------------10 year--------------------------
* */

//数组循环移位

void Reverse(int a[], int from, int to){
    int temp;
    for(int i=0; i<(to+from)/2; i++){
        temp = a[from+i];
        a[from+i] = a[to-i];
        a[to-i] = temp;
    }
}

void Converse(int a[], int n, int p){
    Reverse(a, 0, p-1);
    Reverse(a, p, n-1);
    Reverse(a, 0, n-1);
}

/*
* ---------------09 year--------------------------
* */

//查找链表倒数第k个元素

LinkNode *getLastK(LinkNode *head, int k){
    int counter = k;
    LinkNode *p1 = head, *p2 = head;
    while(p1 != NULL && counter>0){
        p1 = p1->next;
        counter--;
    }
    if(counter != 0)
        return NULL;
    while(p1 != NULL){
        p1 = p1->next;
        p2 = p2->next;
    }
    return p2;
}