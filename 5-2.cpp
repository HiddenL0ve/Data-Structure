//69 36 11 55 33 66 49 20 23
#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class chain;

template<typename T>
class hashChainsWithTails;

template<typename T>
class node { //节点类
    friend chain<T>; //声明友元
    friend hashChainsWithTails<T>;
private:
    T data;
    node* next;
};

template<typename T>
class chain { //链表类
    friend hashChainsWithTails<T>;
public:
    chain() {
        head = NULL;
    }
private:
    node<T>* head; //表头
};

template<typename T>
class hashChainsWithTails {
public:
    hashChainsWithTails(int d = 11) {
        divisor = d;
        table = new chain<T>[divisor];
        tail = new node<T>;
        tail->data = 2147483647; //尾节点的关键字比其他都大
        tail->next = NULL;
        for (int i = 0; i < divisor; i++) {
            table[i].head = new node<T>;
            table[i].head->next = tail; //每个链表共有一个尾节点
        }
    }
    node<T>* find(T t) { //返回该关键字所应该在的位置的前一个节点
        int mark = t % divisor;
        node<T>* pre = table[mark].head->next;
        if (pre == tail) //如果该链表还没有存放任何关键字
            return pre;
        if (pre->data >= t) //如果该链表的第一个关键字就比该关键字大
            return table[mark].head;
        while (pre->next->data < t) //找到该关键字应该在的位置
            pre = pre->next;
        return pre;
    }
    void insert(T t) { //插入关键字
        int mark = t % divisor;
        node<T>* p = new node<T>;
        p->data = t;
        p->next = NULL;
        node<T>* pre = find(t);
        if (pre == tail) {
            table[mark].head->next = p;
            p->next = tail;
        }
        else {
            p->next = pre->next;
            pre->next = p;
        }
    }
    void deleted(T t) { //删除关键字
        node<T>* pre = find(t);
        if (pre == tail || pre->next->data != t)
            cout << "Delete failure!" << endl;
        else
            pre->next = pre->next->next;
    }
    void output() { //输出哈希表
        for (int i = 0; i < divisor; i++) {
            cout << "Hash table[" << i << "]: ";
            node<T>* p = table[i].head->next;
            while (p != tail) {
                cout << p->data << " ";
                p = p->next;
            }
            cout << endl;
        }
    }
private:
    node<T>* tail; //共有的尾节点
    chain<T>* table; //哈希表
    int divisor; //除数
};

int main() {
    hashChainsWithTails<int> h;
    int t;
    for (int i = 0; i < 9; i++) {
        cin >> t;
        h.insert(t);
    }
    h.output();
    for (int i = 0; i < 5; i++) {
        cin >> t;
        h.deleted(t);
    }
    h.output();
    return 0;
}