#include<iostream>
using namespace std;

template<class T> class Node {
public:
	Node* next;
	T data;
	Node(T n) {
		data = n;
		next = NULL;
	}
};

template<class T> class List {
public:
	Node<T>* head;
	Node<T>* tail;
	List() {
		head = NULL;
		tail = NULL;
	}

	void Insert(T n) {
		Node<T>* p = new Node<T>(n);
		if (head->next == NULL) {
			head->next = p;
			tail = p;
		}
		else {
			tail->next = p;
			tail = p;
		}
	}

	void Print() {
		Node<T>* p = head->next;
		if (p == NULL) {
			cout << "NULL" << endl;
			return;
		}
		while (p != NULL) {
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
};

template<class T>
List<T> meld(List<T>& a, List<T>& b) {
	List<T> c;
	Node<T>* p1 = a.head->next;
	Node<T>* p2 = b.head->next;

	while (p1 != NULL || p2 != NULL) {
		if (p1 != NULL) {
			c.Insert(p1->data);
			p1 = p1->next;
		}
		if (p2 != NULL) {
			c.Insert(p2->data);
			p2 = p2->next;
		}
	}

	return c;
}

int main() {
	int n, m;
	cin >> n >> m;
	List<int> a;
	List<int> b;
	while (n--) {
		int t;
		cin >> t;
		a.Insert(t);
	}
	while (m--) {
		int t;
		cin >> t;
		b.Insert(t);
	}
	List<int> c = meld(a, b);
	c.Print();
	return 0;
}
