#include<iostream>
#include<vector>
using namespace std;

class List {
public:
	struct Node {
		int data;
		Node* next;
		Node* prev;
		Node(int n) {
			data = n;
			next = NULL;
			prev = NULL;
		}
	};
	Node* head;
	int size;
	List() {
		size = 0;
		head = new Node(int());
		head->next = head;
		head->prev = head;
	}
	void InsertBack(int n) {
		Node* p = new Node(n);
		p->next = head;
		p->prev = head->prev;
		head->prev->next = p;
		head->prev = p;
		size++;
	}
	void Delete(Node* x) {
		if (size==0 || x == NULL)
			return;
		x->prev->next = x->next;
		x->next->prev = x->prev;
		delete x;
		size--;
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	//Êý×é
	vector<int> people;
	for (int i = 1; i <= n; i++) {
		people.push_back(i);
	}
	int curIndex = 0;
    while (!people.empty()) {
        curIndex = (curIndex + m - 1) % people.size();
        cout << people[curIndex] << " ";
        people.erase(people.begin() + curIndex);
    }
    cout << endl;
	//Á´±í
	List list_people;
	for (int i = 1; i <= n; i++) {
		list_people.InsertBack(i);
	}
	List::Node* cur = list_people.head->next;
	while (list_people.size != 0) {
		for (int i = 0; i < m - 1; i++) {
			cur = cur->next;
			if (cur == list_people.head) {
				cur = cur->next;
			}
		}
		List::Node* tem = cur;
		cur = cur->next;
		if (cur == list_people.head) {
			cur = cur->next;
		}
		cout << tem->data << ' ';
		list_people.Delete(tem);
	}
	return 0;
}