//69 36 11 55 33 66 49 20 23
#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class chain;

template<typename T>
class hashChainsWithTails;

template<typename T>
class node { //�ڵ���
    friend chain<T>; //������Ԫ
    friend hashChainsWithTails<T>;
private:
    T data;
    node* next;
};

template<typename T>
class chain { //������
    friend hashChainsWithTails<T>;
public:
    chain() {
        head = NULL;
    }
private:
    node<T>* head; //��ͷ
};

template<typename T>
class hashChainsWithTails {
public:
    hashChainsWithTails(int d = 11) {
        divisor = d;
        table = new chain<T>[divisor];
        tail = new node<T>;
        tail->data = 2147483647; //β�ڵ�Ĺؼ��ֱ���������
        tail->next = NULL;
        for (int i = 0; i < divisor; i++) {
            table[i].head = new node<T>;
            table[i].head->next = tail; //ÿ��������һ��β�ڵ�
        }
    }
    node<T>* find(T t) { //���ظùؼ�����Ӧ���ڵ�λ�õ�ǰһ���ڵ�
        int mark = t % divisor;
        node<T>* pre = table[mark].head->next;
        if (pre == tail) //���������û�д���κιؼ���
            return pre;
        if (pre->data >= t) //���������ĵ�һ���ؼ��־ͱȸùؼ��ִ�
            return table[mark].head;
        while (pre->next->data < t) //�ҵ��ùؼ���Ӧ���ڵ�λ��
            pre = pre->next;
        return pre;
    }
    void insert(T t) { //����ؼ���
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
    void deleted(T t) { //ɾ���ؼ���
        node<T>* pre = find(t);
        if (pre == tail || pre->next->data != t)
            cout << "Delete failure!" << endl;
        else
            pre->next = pre->next->next;
    }
    void output() { //�����ϣ��
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
    node<T>* tail; //���е�β�ڵ�
    chain<T>* table; //��ϣ��
    int divisor; //����
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