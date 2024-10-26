#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class HashTable {
public:
    int size; 
    bool* neverUsed; //��¼�Ƿ�洢������
    int* ht; //��ϣ����

    HashTable(int d = 10) {
        size = d;
        neverUsed = new bool[size];
        ht = new int[size];
        for (int i = 0; i < size; i++) {
            neverUsed[i] = true;
            ht[i] = -1;
        }
    }

    int search(T t);
    double falseEmpty(); //����ʵ���ǿ�Ͱ����neverUsed��false��ռ��Ͱ�İٷֱ�
    HashTable<T>& insert(T t);
    HashTable<T>& deleted(T t);
    HashTable<T>& reorganize();
    void output();
};

template<typename T>
double HashTable<T>::falseEmpty() {
    double empty = 0; //�ܵĿ�Ͱ��
    double falseEmp = 0; //û������neverUsedΪfalse�Ŀ�Ͱ��
    for (int i = 0; i < size; i++)
        if (ht[i] == -1) {
            empty++;
            if (!neverUsed[i])
                falseEmp++;
        }
    return falseEmp / empty; //����ռ��
}

template<typename T>
int HashTable<T>::search(T t) { //����Ӧ�ò����λ��
    int key = t % size;
    int index = key;
    do {
        if (neverUsed[index] || ht[index] == t) //��λ��Ϊ�ջ��߸������Ѵ���
            return index;
        index = (index + 1) % size;
    } while (index != key);
    return -1;
}

template<typename T>
HashTable<T>& HashTable<T>::insert(T t) {
    int key = search(t);
    if (key == -1 || ht[key] == t) //���û���ҵ����߸������Ѵ���
        cout << "Insert Failure!" << endl;
    else {
        ht[key] = t;
        neverUsed[key] = false;
    }
    return *this;
}

template<typename T>
HashTable<T>& HashTable<T>::deleted(T t) { //ɾ������
    int key = t % size;
    int index = key;
    do {
        if (ht[index] == t) //�ҵ�����
            break;
        index = (index + 1) % size;
    } while (index != key);
    if (ht[index] != t)
        cout << "Delete Failure!" << endl;
    else
        ht[index] = -1;
    return *this;
}

template<typename T>
HashTable<T>& HashTable<T>::reorganize() { //������֯ɢ�б�
    if (falseEmpty() < 0.6) {
        output();
        return *this;
    }

    int* temp = new int[size]; //���������ϣ�������е�����
    int key = 0;
    for (int i = 0; i < size; i++) {
        if (ht[i] != -1) {
            temp[key++] = ht[i];
            ht[i] = -1;
        }
        neverUsed[i] = true;
    }
    for (int i = 0; i < key; i++) //���²���
        insert(temp[i]);
    cout << "hash table is reorganized:" << endl;
    output();
    return *this;
}

template<typename T>
void HashTable<T>::output() { //���ɢ�б�
    cout << "Hash table:" << endl;
    for (int i = 0; i < size; i++) {
        if (!neverUsed[i])
            cout << ht[i] << " ";
        else //û��Ԫ�����0
            cout << "0" << " ";
    }
    cout << endl;
}

int main() {
    HashTable<int> ht;
    int t;
    cout << "Input 10 numbers:" << endl;
    for (int i = 0; i < 10; i++) {
        cin >> t;
        ht.insert(t);
    }
    ht.output();
    for (int i = 0; i < 3; i++) {
        cout << "Delete numbers:" << endl;
        cin >> t;
        ht.deleted(t);
        ht.reorganize();
    }
    return 0;
}

//12 13 14 25 80 81 11 75 76 74
//81 25 14