//
// Created by Coder on 2018/2/8.
//

#include <iostream>
#include <list>
#include <stack>
#include <queue>

using namespace std;

void swap(int &a, int &b){
    int mid = a;
    a = b;
    b = mid;
}

//斐波那契数列
void print_fib(int n){
    int a1 = 1, a2 = 0, mid;
    if(n <= 0){
        return;
    }
    for(int i=0; i<n; i++){
        cout<<a1+a2<<" ";
        mid = a1;
        a1 = a2;
        a2 += mid;
    }

}

//判断链表是否有环

typedef struct LNode{
    int val;
    struct LNode *next;
}LNode, *LinkList;

//链表是否有环
int isCircle(LNode L){
    LNode *p1 = &L, *p2 = &L;
    while(p1 && p2){
        //防止p2每次走两步时对NULL操作
        if(p2->next == NULL)
            //有出口，说明不是环
            return 0;
        //p2走两步
        p2 = (p2->next)->next;
        if(p1 == p2)
            return 1;
        //p1走一步
        p1 = p1->next;
    }
}


//第一问得出相遇点后，再发出一个指针，统计这个指针再次回到这个点的距离，也就是环的距离。
//从起点再发出两个指针，一个指针在另一个前面，两个指针的距离就是环的距离
// 当两个指针再次相遇的时候就是环的入口。
LinkList GetCircleStart(LinkList head){
    LinkList p1 = head, p2 = head;
    while(p1 && p2){
        //防止p2每次走两步时对NULL操作
        if(p2->next == NULL)
            //有出口，说明不是环
            return NULL;
        //p2走两步
        p2 = (p2->next)->next;
        if(p1 == p2)
            break;
        //p1走一步
        p1 = p1->next;
    }
    //统计环的大小
    LinkList p3 = p2->next;
    int count = 1;
    while(p3 && p3 != p2) {
        p3 = p3->next;
        count++;
    }
    //p1和p2从起点出发,相隔count步
    p1 = p2 = head;
    while(--count)
        p2 = p2->next;
    while(p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

//有序链表合并
LNode* merge(LNode *l1, LNode *l2) {
    LNode node, *head = &node, *p = head;
    head->next = NULL;
    while (l1 && l2) {
        if (l1->val > l2->val) {
            p->next =  l1;
            l1 = l1->next;
        } else {
            p->next =  l2;
            l2 = l2->next;
        }
        p = p->next;
    }
    p->next = l1 ? l1 : l2;
    return head->next;
}

//链表反转
LinkList reverse(LinkList head){
    if(head == NULL || head->next == NULL)
        return head;
    LinkList l1 = head, l2 = head->next ,p;
    //链首节点最后变为链尾节点
    l1->next = NULL;
    //可以理解为原链表已经分裂为两个链表
    //一个是l1指向的链表
    //一个是l2指向的链表
    //while循环的每次操作都是把pl2指向的链表首插入到l1指向的链表首
    while(l2 != NULL){
        p = l2->next;
        l2->next = l1;
        //为下次循环作条件
        l1 = l2;
        l2 = p;
    }
    return l1;
}

typedef struct TreeNode{
    int value;
    struct TreeNode *lchild, *rchild;
}TreeNode;

//二叉树的先序遍历非递归
void PreOrderTraverse(TreeNode *root){
    if(root == NULL)
        return;
    TreeNode *pNode;
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        pNode = s.top();
        cout<<pNode->value<<endl;
        //当前节点访问完后出栈
        s.pop();
        //先让右子树进栈，后访问右子树
        if(pNode->rchild != NULL)
            s.push(pNode->rchild);
        //右子树在栈顶，保证下次访问先访问左子树
        if(pNode->lchild != NULL)
            s.push(pNode->lchild);
    }
}

//二叉树的中序遍历非递归
void InOrderTraverse(TreeNode *root){
    if(root == NULL)
        return;
    TreeNode *pNode = root;
    stack<TreeNode*> s;
    //思路就是每次遍历到最左边的孩子，然后依次出栈访问
    //然后对每个出栈的节点对其右孩子为根节点最上面同样的操作(遍历到最左边，再依次退栈)
    while(pNode!=NULL||!s.empty())
    {
        while(pNode!=NULL)
        {
            s.push(pNode);
            pNode=pNode->lchild;
        }
        if(!s.empty())
        {
            //栈里的所有元素可以视为左孩子
            pNode=s.top();
            cout<<pNode->value<<endl;
            //最重要的就是这个出栈，出栈可以视为这样
            //该栈顶节点左孩子访问出栈，该节点访问后出栈，然后对该节点的右孩子做中序遍历，直至右子树中序访问完毕
            //访问该栈顶节点的祖先节点(也就是栈顶的后一个元素)，再重复上述操作(对该祖先节点的右孩子做中序遍历，直至该祖先节点的右子树访问完毕)
            s.pop();
            pNode=pNode->rchild;
        }
    }
}


//二叉树的后序遍历非递归
void PostOrderTraverse(TreeNode *root){
    if(root == NULL)
        return;
    stack<TreeNode*> s;
    TreeNode *pNode = root, *pre;
    //思路就是每个节点都按照右中左的顺序入栈
    //然后出栈有两种情况：
    //    1.第一个出栈的肯定为叶子，无论是左右叶子
    //    2.如果栈顶不是叶子节点，则往下深度搜索
    //第二种情况会出现一种问题，如果这个节点的左右子树已经被访问了
    //如果不加以区分，这个节点的左右子树还会入栈，造成重复访问
    // 这个节点的祖先节点也不能正确的被访问(因为后序遍历是从下往上的)
    //设置pre为上一个被访问的节点，
    s.push(pNode);
    while (!s.empty()) {
        pNode = s.top();
        if (pNode->lchild == NULL && pNode->rchild == NULL) {   //当pNode为叶子时
            cout<<pNode->value<<endl;
            s.pop();
            pre = pNode;
        } else if (pNode->lchild == pre || pNode->rchild == pre) {  //当pNode的左孩子或右孩子被访问后
            cout<<pNode->value<<endl;
            s.pop();
            pre = pNode;
        } else{
            if (pNode->rchild != NULL) {
               s.push(pNode->rchild);
            }
            if (pNode->lchild != NULL) {
                s.push(pNode->lchild);
            }
        }
    }
}


//二叉树的层次遍历非递归
void LevelOrderTraverse(TreeNode *root){
    if(root == NULL)
        return;
    TreeNode *p;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        p = q.front();
        q.pop();
        cout<<p->value<<endl;
        if (p->lchild)
            q.push(p->lchild);
        if (p->rchild)
            q.push(p->rchild);
    }
}

//查找二叉树指定节点
bool hasNode(TreeNode* pRoot, TreeNode* pNode){
    if(pRoot == pNode)
        return true;
    bool has = false;
    if(pRoot->lchild != NULL)
        has = hasNode(pRoot->lchild, pNode);
    if(!has && pRoot->rchild != NULL){
        has = hasNode(pRoot->rchild, pNode);
    }
    return has;
}

//利用了后序遍历的思想
//后续搜索每条路径，并将每条路径经过的节点压栈
//当此路径上无要找寻的节点时，将此路径上的节点依次退栈
bool GetNodePath(TreeNode *pRoot, TreeNode *pNode, stack<TreeNode*> &path){
    if(pRoot == pNode){
        path.push(pRoot);
        return true;
    }
    //不存在此节点
    if(hasNode(pRoot, pNode) == false)
        return false;
    //先将当前节点入栈
    path.push(pRoot);
    bool found = false;
    if(pRoot->lchild != NULL)
        found = GetNodePath(pRoot->lchild, pNode, path);
    if(!found && pRoot->rchild != NULL)
        found = GetNodePath(pRoot->rchild, pNode, path);
    //如果此路径没有找到，出栈
    if(!found)
        path.pop();
    return found;
}

//二叉排序树
void InsertBST(TreeNode *root, TreeNode *node) {
    TreeNode *p, *pre;
    p = pre = root;
    while (p != NULL) {
        pre = p;
        if (node->value <= p->value) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    node->value <= pre->value ? pre->lchild = node : pre->rchild = node;
}

//n个数据在数组d中，tree为二叉排序树根
void CreateBST(TreeNode *tree, int d[], int n)
{
    for (int i = 0; i < n; i++) {
        TreeNode *node = new TreeNode();
        node->value = d[i];
        node->lchild = node->rchild = NULL;
        InsertBST(tree, node);
    }
}


//判断平衡因子是否合法
bool pfIsInvaild(const int& pf)
{
    return abs(pf) < 2;
}

//判断二叉平衡树
bool IsAVLBinaryTree(TreeNode *root,  int & depth)
{
    //如果为空，往父节点返
    if (root == NULL)
    {
        depth = 0;
        return true;
    }
    //记录左节点和右节点深度
    int left = 0;
    int right = 0;
    //采取传引用的方式，下层递归进行对深度修改以后会影响上一层
    if (IsAVLBinaryTree(root->lchild, left) && IsAVLBinaryTree(root->rchild, right))
    {
        //计算平衡因子
        int pf = right - left;
        //判断平衡因子是否合法
        if (pfIsInvaild(pf))
        {
            //合法就让自身加上子树的深度，然后因为是传引用，所以当递归回到上一层的时候，上层中的right和left就是左右子树的深度
            depth = 1 + (right > left ? right : left);
            return true;
        }
    }
    return false;
}

//折半查找
bool BinartSearch(int a[], int length, int key) {
    int low = 0, high = length-1;
    while (low <= high) {
        int mid = (mid + high) / 2;
        if (a[mid] == key) {
            cout<<mid<<endl;
            return true;
        } else if (a[mid] > key) {
            high = mid-1;
        } else {
            low = mid+1;
        }
    }
    return false;
}
//快排直接使用方法


int main(){
//    TreeNode a[7];
//    for (int i = 1; i < 7; i++) {
//        a[i].value = i;
//    }
//    a[1].lchild = a+2;
//    a[1].rchild = a+3;
//    a[2].lchild = NULL;
//    a[2].rchild = a+4;
//    a[3].lchild = NULL;
//    a[3].rchild = a+5;
//    a[4].lchild = a+6;
//    a[4].rchild = NULL;
//    a[5].lchild = NULL;
//    a[5].rchild = NULL;
//    a[6].lchild = NULL;
//    a[6].rchild = NULL;
//    LevelOrderTraverse(a+1);
//    PreOrderTraverse(a+1);
//    InOrderTraverse(a+1);
//    PostOrderTraverse(a+1);
//    stack<TreeNode*> s;
//    GetNodePath(a+1, a+6, s);
//    while(!s.empty()) {
//        cout<<s.top()->value<<endl;
//        s.pop();
//    }
//    TreeNode root;
//    root.value = 53;
//    root.lchild = root.rchild = NULL;
//    int d[] = {17, 78, 9, 45, 23, 94, 88};
//    CreateBST(&root, d, 7);
//    InOrderTraverse(&root);
    int b[] = {1, 2, 10, 21, 22, 44, 100, 201, 666};
    BinartSearch(b, 9, 666);
    return 0;
}
