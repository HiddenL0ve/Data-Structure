/*a+b+c*(d+e)*/
#include<iostream>
#include<stack>
#include<string>
using namespace std;

class ExpressionTree {
public:
    struct TreeNode {
        char data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(char a) {
            data = a;
            left = NULL;
            right = NULL;
        }
    };
    TreeNode* root;
    ExpressionTree() {
        root = NULL;
    }
    //用nodestack和operatorstack的顶端节点建立一个子树
    void BuildSubTree(stack<TreeNode*>& nodestack, stack<char>& operatorstack) {
        char p = operatorstack.top();
        operatorstack.pop();
        TreeNode* t = new TreeNode(p);
        t->left = nodestack.top();
        nodestack.pop();
        t->right = nodestack.top();
        nodestack.pop();
        nodestack.push(t);
    }
    //将字符串转换成表达树
    void Transform(const string& string) {
        stack<TreeNode*> nodestack;
        stack<char> operatorstack;
        for (char a : string) {
            if (IsLetter(a)) {
                TreeNode* t = new TreeNode(a);
                nodestack.push(t);
            }
            else if (a == '(') {
                operatorstack.push(a);
            }
            else if (a == ')') {
                while (!operatorstack.empty() && operatorstack.top() != '(') {
                    BuildSubTree(nodestack, operatorstack);
                }
                operatorstack.pop();//删‘（’
            }
            else if (IsOperator(a)) {
                while (!operatorstack.empty() && Precedence(a) <= Precedence(operatorstack.top())) {
                    BuildSubTree(nodestack, operatorstack);
                }
                operatorstack.push(a);
            }
        }
        while (!operatorstack.empty()) {
            BuildSubTree(nodestack, operatorstack);
        }
        if (!nodestack.empty()) {
            root = nodestack.top();
        }
    }
    //判断字母
    bool IsLetter(char a) {
        return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z');
    }
    //判断操作符
    bool IsOperator(char a) {
        return a == '+' || a == '-' || a == '*' || a == '/';
    }
    //判断运算优先级
    int Precedence(char a) {
        if (a == '+' || a == '-') {
            return 1;
        }
        else if (a == '*' || a == '/') {
            return 2;
        }
        return 0;//‘（’
    }
    void Print() {
        PrintNode(root, 0);
    }
    void PrintNode(TreeNode* p, int depth) {
        if (p == NULL) {
            return;
        }
        PrintNode(p->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            cout << "   ";
        }
        cout << p->data << endl;
        PrintNode(p->left, depth + 1);
    }
};

int main() {
    string expression;
    cin >> expression;
    ExpressionTree et;
    et.Transform(expression);
    et.Print();
    return 0;
}
