#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class HashTable {
public:
    int size; 
    bool* neverUsed; //记录是否存储过数据
    int* ht; //哈希数组

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
    double falseEmpty(); //返回实际是空桶，但neverUsed是false所占空桶的百分比
    HashTable<T>& insert(T t);
    HashTable<T>& deleted(T t);
    HashTable<T>& reorganize();
    void output();
};

template<typename T>
double HashTable<T>::falseEmpty() {
    double empty = 0; //总的空桶数
    double falseEmp = 0; //没有数但neverUsed为false的空桶数
    for (int i = 0; i < size; i++)
        if (ht[i] == -1) {
            empty++;
            if (!neverUsed[i])
                falseEmp++;
        }
    return falseEmp / empty; //返回占比
}

template<typename T>
int HashTable<T>::search(T t) { //返回应该插入的位置
    int key = t % size;
    int index = key;
    do {
        if (neverUsed[index] || ht[index] == t) //该位置为空或者该数据已存在
            return index;
        index = (index + 1) % size;
    } while (index != key);
    return -1;
}

template<typename T>
HashTable<T>& HashTable<T>::insert(T t) {
    int key = search(t);
    if (key == -1 || ht[key] == t) //如果没有找到或者该数据已存在
        cout << "Insert Failure!" << endl;
    else {
        ht[key] = t;
        neverUsed[key] = false;
    }
    return *this;
}

template<typename T>
HashTable<T>& HashTable<T>::deleted(T t) { //删除数据
    int key = t % size;
    int index = key;
    do {
        if (ht[index] == t) //找到数据
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
HashTable<T>& HashTable<T>::reorganize() { //重新组织散列表
    if (falseEmpty() < 0.6) {
        output();
        return *this;
    }

    int* temp = new int[size]; //用来储存哈希表中现有的数据
    int key = 0;
    for (int i = 0; i < size; i++) {
        if (ht[i] != -1) {
            temp[key++] = ht[i];
            ht[i] = -1;
        }
        neverUsed[i] = true;
    }
    for (int i = 0; i < key; i++) //重新插入
        insert(temp[i]);
    cout << "hash table is reorganized:" << endl;
    output();
    return *this;
}

template<typename T>
void HashTable<T>::output() { //输出散列表
    cout << "Hash table:" << endl;
    for (int i = 0; i < size; i++) {
        if (!neverUsed[i])
            cout << ht[i] << " ";
        else //没有元素输出0
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