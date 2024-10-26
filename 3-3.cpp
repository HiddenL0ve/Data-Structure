#include<iostream>					
using namespace std;
class CNode {
public:
	CNode* next = NULL;
	int col;
	int value;
	CNode(int i, int j) {
		col = i;
		value = j;
	}
};

class HeadNode {//������ͷ��㣬Ҳ��������					
public:
	CNode* first = NULL;
	HeadNode* next = NULL;
	int row;
	HeadNode(int r) {
		row = r;
	}
	HeadNode& Insert(int n, int b);
};

HeadNode& HeadNode::Insert(int n, int b) {
	CNode* temp = new CNode(n, b);
	if (first == NULL) {
		first = temp;
	}
	else {
		CNode* curr = first;
		while (curr->next != NULL) {
			if (curr->col<n && curr->next->col>n)
			{
				temp->next = curr->next;
				curr->next = temp;
				break;
			}
			else
				curr = curr->next;
		}
		if (curr->next == NULL) {
			curr->next = temp;
		}
	}
	return *this;
}

class LinkedMatrix {//����ÿ��һ�е�һ����ͷ					
public:
	HeadNode* first1 = NULL;
	int rows = 0, cols = 0, terms = 0;
	LinkedMatrix& Insert(int k, int n, int b);
	int find(int r, int c);
	LinkedMatrix(int r = 0, int c = 0, int t = 0) {
		rows = r;
		cols = c;
		terms = t;
	}
	friend void operator+(LinkedMatrix& a, LinkedMatrix& b);
	friend void operator-(LinkedMatrix& a, LinkedMatrix& b);
	friend void operator*(LinkedMatrix& a, LinkedMatrix& b);
	friend istream& operator >>(istream& in, LinkedMatrix& x) {
		in >> x.rows >> x.cols >> x.terms;
		for (int i = 1; i <= x.terms; i++) {
			int a, b, c;
			in >> a >> b >> c;
			x.Insert(a, b, c);
		}
		return in;
	}
};
//����					
LinkedMatrix& LinkedMatrix::Insert(int k, int n, int b) {//k��ʾ�ڼ���					
	HeadNode* curr = first1;
	//�жϸ����Ƿ��Ѿ�����				
	while (curr != NULL) {
		if (curr->row == k)
		{
			curr->Insert(n, b);
			return *this;
		}
		else
			curr = curr->next;
	}
	//û����һ��				
	HeadNode* temp = new HeadNode(k);
	if (first1 == NULL) {
		first1 = temp;
		temp->Insert(n, b);
		return *this;
	}
	else {
		curr = first1;
		if (curr->row > k)//�´������б�������С������´���Ӧ���ڵ�һ��			
		{
			temp->next = first1;
			first1 = temp;
			temp->Insert(n, b);
		}
		while (curr->next != NULL) {
			if (curr->row<k && curr->next->row>k)
			{
				temp->next = curr->next;
				curr->next = temp;
				temp->Insert(n, b);

			}
			else
				curr = curr->next;
		}
		if (curr->next == NULL) {
			curr->next = temp;
			temp->Insert(n, b);

		}
		return *this;
	}
}

int LinkedMatrix::find(int r, int c) {
	HeadNode* curr = first1;
	CNode* temp = NULL;
	int d = 0;
	while (curr != NULL) {
		if (curr->row == r) {//���ж��Ƿ��ڸ���			
			temp = curr->first;
			while (temp != NULL) {
				if (temp->col == c)
				{
					d = temp->value;
					return d;
				}
				else
					temp = temp->next;
			}
			return 0;
		}
		else curr = curr->next;
	}
}

void operator+(LinkedMatrix& a, LinkedMatrix& b) {
	LinkedMatrix c;
	if (a.rows != b.rows || a.cols != b.cols)
		cout << "ERROR";
	else {
		for (int i = 1; i <= a.rows; i++)
		{
			for (int j = 1; j <= a.cols; j++) {
				if (a.find(i, j) + b.find(i, j) != 0)
					c.Insert(i, j, a.find(i, j) + b.find(i, j));
			}
		}
	}
	for (int i = 1; i <= a.rows; i++) {
		for (int j = 1; j <= a.cols; j++) {
			if (c.find(i, j))
				cout << c.find(i, j) << " ";
			else
				cout << 0 << ' ';
		}
		cout << endl;
	}
}

void operator-(LinkedMatrix& a, LinkedMatrix& b) {
	LinkedMatrix c;
	if (a.rows != b.rows || a.cols != b.cols)
		cout << "ERROR";
	else {
		for (int i = 1; i <= a.rows; i++)
		{
			for (int j = 1; j <= a.cols; j++) {
				if (a.find(i, j) - b.find(i, j) != 0)
					c.Insert(i, j, a.find(i, j) - b.find(i, j));
			}
		}
	}
	for (int i = 1; i <= a.rows; i++) {
		for (int j = 1; j <= a.cols; j++) {
			if (c.find(i, j))
				cout << c.find(i, j) << " ";
			else
				cout << 0 << ' ';
		}
		cout << endl;
	}
}

void operator*(LinkedMatrix& a, LinkedMatrix& b) {
	LinkedMatrix c;
	if (a.cols != b.rows)
	{
		cout << "ERROR";
	}
	else {
		for (int i = 1; i <= a.rows; i++)
		{
			for (int j = 1; j <= b.cols; j++) {
				int sum = 0;
				for (int k = 1; k <= a.cols; k++) {
					sum += a.find(i, k) * b.find(k, j);
				}
				if (sum != 0)
					c.Insert(i, j, sum);
				else
					continue;

			}
		}
		for (int i = 1; i <= a.rows; i++) {
			for (int j = 1; j <= a.cols; j++) {
				if (c.find(i, j))
					cout << c.find(i, j) << " ";
				else
					cout << 0 << ' ';
			}
			cout << endl;
		}
	}
}
int main() {
	LinkedMatrix a;
	cin >> a;
	LinkedMatrix b;
	cin >> b;
	a + b;
	a - b;
	a* b;
	return 0;
}
