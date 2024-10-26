#include<iostream>
using namespace std;

template<class T>
class Stack {
public:
	struct Node {
		T data;
		Node* next;
		Node(T n) {
			data = n;
			next = NULL;
		}
	};
	Node* top;
	int size;
	Stack() {
		size = 0;
		top = new Node(T());
		top->next = NULL;
	}
	void Push(T n) {
		Node* p = new Node(n);
		p->next = top;
		top = p;
		size++;
	}
	void Display() {
		Node* tem = top;
		while (tem != NULL) {
			cout << tem->data << ' ';
			tem = tem->next;
		}
	}
	void Delete(Node* p) {
		if (size == 0) {
			return;
		}
		Node* tem = top;
		while (tem->next != p) {
			tem = tem->next;
		}
		tem->next = p->next;
		delete p;
		size--;
	}
	friend void delete_all(Stack<T>& s, const T& x) {
		Node* cur = s.top;
		while (cur != NULL) {
			if (cur->data == x) {
				Node* tem = cur;
				cur = cur->next;
				s.Delete(tem);
			}
			else cur = cur->next;
		}
	}
};

int main() {
	Stack<char> s;
	char x;
	cin >> x;
	for (int i = 0; i < 7; i++) {
		char t;
		cin >> t;
		s.Push(t);
	}
	delete_all(s, x);
	s.Display();
	return 0;
}