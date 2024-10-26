#include <iostream>
#include <vector>

using namespace std;

class HuffmanTree {
public:
    struct HuffmanNode {
        char data;
        int freq;
        HuffmanNode* left;
        HuffmanNode* right;
        HuffmanNode(char a, int n) {
            data = a;
            freq = n;
            left = right = NULL;
        }
    };
    HuffmanNode* root;
    string codeTable[256];
    HuffmanTree() {
        root = NULL;
    }

    //编码
    void Encode(HuffmanNode* p, string code) {
        if (p == NULL) {
            return;
        }
        if (!p->left && !p->right) {
            codeTable[p->data] = code;
        }
        Encode(p->left, code + '0');
        Encode(p->right, code + '1');
    }

    //建立霍夫曼树
    void BuildHuffmanTree(string text) {
        int count[256] = { 0 };
        for (char s : text) {
            count[static_cast<int>(s)]++;
        }
        vector<HuffmanNode*> node;
        for (int i = 0; i < 256; i++) {
            if (count[i] != 0) {
                HuffmanNode* p = new HuffmanNode(static_cast<char>(i), count[i]);
                node.push_back(p);
            }
        }

        while (node.size() > 1) {
            //排序
            for (int i = 1; i < node.size(); i++) {
                for (int j = 0; j < node.size() - i; j++) {
                    if (node[j]->freq < node[j + 1]->freq) {
                        HuffmanNode* t = node[j];
                        node[j] = node[j + 1];
                        node[j + 1] = t;
                    }
                }
            }

            //建立子树
            HuffmanNode* leftchild = node.back();
            node.pop_back();
            HuffmanNode* rightchild = node.back();
            node.pop_back();
            HuffmanNode* p = new HuffmanNode(' ', leftchild->freq + rightchild->freq);
            p->left = leftchild;
            p->right = rightchild;
            node.push_back(p);
        }

        root = node.front();
    }

    //压缩成编码
    string Compress(string text) {
        string code = "";
        BuildHuffmanTree(text);
        Encode(root, code);
        for (char s : text) {
            code += codeTable[s];
        }
        return code;
    }

    //解压
    string Decompress(string code) {
        string text = "";
        string t = "";
        for (char s : code) {
            t += s;
            for (int i = 0; i < 256; i++) {
                if (t == codeTable[i]) {
                    text += static_cast<char>(i);
                    t = "";
                    break;
                }
            }
        }
        return text;
    }
};

int main() {
    string text = "Hello, this is a test text for Huffman coding.";
    HuffmanTree ht;
    string CompressedText = ht.Compress(text);
    cout << "压缩后编码：" << CompressedText << endl;
    cout << "解压后文本：" << ht.Decompress(CompressedText) << endl;

    return 0;
}
