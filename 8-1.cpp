#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int value;
    Node* left, * right;
    int height;
    Node(int n) {
        value = n;
        left = right = NULL;
        height = 1;
    }
};

class AVLTree {
public:
    Node* root;
    AVLTree() {
        root = NULL;
    }
    
    // 获取节点的高度
    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    //平衡数
    int GetBalance(Node* p) {
        if (p == nullptr)
            return 0;
        return height(p->left) - height(p->right);
    }

    void UpdateHeight(Node* p) {
        p->height = max(height(p->left), height(p->right)) + 1;
    }

    //左旋<-
    Node* Left(Node* p) {
        Node* t1 = p->right;
        Node* t2 = t1->left;
        t1->left = p;
        p->right = t2;
        UpdateHeight(p);
        UpdateHeight(t1);
        return t1;
    }

    //右旋->
    Node* Right(Node* p) {
        Node* t1 = p->left;
        Node* t2 = t1->right;
        t1->right = p;
        p->left = t2;
        UpdateHeight(p);
        UpdateHeight(t1);
        return t1;
    }

    Node* InsertNode(Node* p,int d) {
        if (p == NULL) {
            Node* t = new Node(d);
            return t;
        }
        if (p->value > d) {
            p->left = InsertNode(p->left, d);
        }
        else if (p->value < d) {
            p->right = InsertNode(p->right, d);
        }
        else
            return p;

        UpdateHeight(p);
        //LL
        if (GetBalance(p) >= 2 && d < p->left->value) {
            return Right(p);
        }
        //RR
        if (GetBalance(p) <= -2 && d > p->right->value) {
            return Left(p);
        }
        //LR  Left-Right
        if (GetBalance(p) >= 2 && d > p->left->value) {
            p->left = Left(p->left);
            return Right(p);
        }
        //RL 
        if (GetBalance(p) <= -2 && d < p->right->value) {
            p->right = Right(p->right);
            return Left(p);
        }

        return p;
    }

    void Insert(int data) {
        root = InsertNode(root, data);
    }

    // 寻找最近叶子节点值
    int FindLeaf(Node* node) {
        if (node == nullptr)
            return -1;

        if (node->left == nullptr && node->right == nullptr)
            return node->value;

        int leftDepth = node->left ? node->left->height : INT_MAX;
        int rightDepth = node->right ? node->right->height : INT_MAX;

        return leftDepth <= rightDepth ? FindLeaf(node->left) : FindLeaf(node->right);
    }

    // 获取最近叶子节点值
    int LeafValue() {
        return FindLeaf(root);
    }
};

int main() {
    AVLTree avlTree;

    avlTree.Insert(10);
    avlTree.Insert(20);
    avlTree.Insert(30);
    avlTree.Insert(40);
    avlTree.Insert(50);
    avlTree.Insert(25);

    cout << "AVL树的高度为: " << avlTree.root->height << endl;
    cout << "距离根节点最近的叶节点值为: " << avlTree.LeafValue() << endl;
    return 0;
}
