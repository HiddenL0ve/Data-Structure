#include<iostream>
#include<queue>
using namespace std;

template<class T>
class BinaryTree {
public:
    struct TreeNode {
        T value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int n) {
            value = n;
            left = NULL;
            right = NULL;
        }
    };
private:
    TreeNode* root;
public:
    BinaryTree() {
        root = NULL;
    }
    TreeNode* Insert(TreeNode* t, T d) {
        if (t == NULL) {
            return new TreeNode(d);
        }
        if (d < t->value) {
            t->left = Insert(t->left, d);
        }
        else {
            t->right = Insert(t->right, d);
        }
        return t;
    }
    void InsertNode(T n) {
        root = Insert(root, n);
    }
    int Count(TreeNode* t) {
        if (t == NULL) {
            return 0;
        }
        if(t->left == NULL && t->right == NULL) {
            return 1;
        }
        return Count(t->left) + Count(t->right);
    }
    int ConutNode() {
        return Count(root);
    }
    void SwapNode(TreeNode* t) {
        if (t == NULL) {
            return;
        }
        TreeNode* p = t->left;
        t->left = t->right;
        t->right = p;
        SwapNode(t->left);
        SwapNode(t->right);
    }
    void Swap() {
        SwapNode(root);
    }
    void Traverse() {
        if (root == NULL) {
            cout << "Empty" << endl;
            return;
        }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* cur = q.front();
            cout << cur->value << ' ';
            if (cur->left != NULL) {
                q.push(cur->left);
            }
            if (cur->right != NULL) {
                q.push(cur->right);
            }
            q.pop();
        }
        cout << endl;
    }
    int GetWidth() {
        if (root == NULL) {
            return 0;
        }
        queue<TreeNode*> q;
        q.push(root);
        int maxwidth = 1;
        while (!q.empty()) {
            if (maxwidth < q.size()) {
                maxwidth = q.size();
            }
            int count = q.size();
            while (count--) {
                TreeNode* tem = q.front();
                if (tem->left != NULL) {
                    q.push(tem->left);
                }
                if (tem->right != NULL) {
                    q.push(tem->right);
                }
                q.pop();
            }
        }
        return maxwidth;
    }
};

int main() {
    BinaryTree<int> tree;

    tree.InsertNode(10);
    tree.InsertNode(5);
    tree.InsertNode(15);
    tree.InsertNode(3);
    tree.InsertNode(7);
    tree.InsertNode(12);
    tree.InsertNode(18);

    cout << "层次遍历：";
    tree.Traverse();
    cout << "叶节点数目: " << tree.ConutNode() << endl;
    cout << "交换左右子树后的层次遍历: ";
    tree.Swap();
    tree.Traverse();
    cout << "二叉树宽度: " << tree.GetWidth() << endl;
    return 0;
}
