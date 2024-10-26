#include<iostream>
using namespace std;
template<class T> class List {
public:
	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node(T n) :data(n), prev(nullptr), next(nullptr) {}
	};
	Node* head;
	int size;
	List() :size(0), head(nullptr) {
		head = new Node(T());
		head->prev = head;
		head->next = head;
	}
	void InsertBack(T n) {
		Node* newNode = new Node(n);
		newNode->prev = head->prev;
		newNode->next = head;
		head->prev->next = newNode;
		head->prev = newNode;
		size++;
	}
	void RemoveBack() {
		Node* toRemove = head->prev;
		head->prev = toRemove->prev;
		toRemove->prev->next = head;
		delete toRemove;
		size--;
	}
	void Print() {
		Node* cur = head->next;
		if (cur == head) {
			cout << "Empty" << endl;
			return;
		}
		while (cur != head) {
			cout << cur->data << ' ';
			cur = cur->next;
		}
		cout << endl;
	}
};
template<class T> void split(List<T>& c) {
	List<T> a,b;
	class List<T>::Node* cur = c.head->next;
	while (cur != c.head) {
		a.InsertBack(cur->data);
		cur = cur->next;
		if (cur != c.head) {
			b.InsertBack(cur->data);
			cur = cur->next;
		}
	}
	a.Print();
	b.Print();
}
int main() {
	int n;
	cin >> n;
	List<int> c;
	while (n--) {
		int t;
		cin >> t;
		c.InsertBack(t);
	}
	split(c);
	return 0;
}