/*AddLeft	1
AddLeft	2
DeleteRight
IsFull
DeleteLeft
IsEmpty
AddRight 3
AddLeft 2
AddRight 1
End*/
#include<iostream>
#include<string>
using namespace std;

class DoubleEndedQueue{
public:
    int* queue;
    int front;
    int rear;
    int size;
    int capacity;
    DoubleEndedQueue(int n) {
        capacity = n;
        queue = new int[capacity];
        front = 0;
        rear = 0;
        size = 0;
    }
    bool IsEmpty() {
        return size == 0;
    }
    bool IsFull() {
        return size == capacity;
    }
    void AddRight() {
        if (IsFull()) {
            cout << "FULL" << endl;
        }
        int data;
        cin >> data;
        queue[rear] = data;
        rear = (rear + 1) % capacity;
        size++;
    }
    void AddLeft() {
        if (IsFull()) {
            cout << "FULL" << endl;
            return;
        }
        int data;
        cin >> data;
        front = (front - 1 + capacity) % capacity;
        queue[front] = data;
        size++;
    }
    void DeleteLeft() {
        if (IsEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }
    void DeleteRight() {
        if (IsEmpty()) {
            cout << "EMPTY" << endl;
            return;
        }
        rear = (rear - 1 + capacity) % capacity;
        size--;
    }
    void Print() {
        for (int cur = front, count = 0; count < size; cur = (cur + 1) % capacity, count++) {
            cout << queue[cur] << ' ';
        }
        cout << endl;
    }
};

int main() {
    DoubleEndedQueue dq(10);
    string s;
    while (1) {
        cin >> s;
        if (s == "IsEmpty") {
            cout << (dq.IsEmpty() ? "Yes" : "No") << endl;
        }
        else if (s == "IsFull") {
            cout << (dq.IsFull() ? "Yes" : "No") << endl;
        }
        else if (s == "AddLeft") {
            dq.AddLeft();
            dq.Print();
        }
        else if (s == "AddRight") {
            dq.AddRight();
            dq.Print();
        }
        else if (s == "DeleteLeft") {
            dq.DeleteLeft();
            dq.Print();
        }
        else if (s == "DeleteRight") {
            dq.DeleteRight();
            dq.Print();
        }
        else if (s == "End") {
            break;
        }
        else {
            cout << "WRONG" << endl;
        }
    }
    return 0;
}