#include<iostream>
using namespace std;
template<class T> class LowerTriangularMatrix {
public:
	int n;
	T* element;
	LowerTriangularMatrix(int m) {
		n = m;
		element = new T[n * (n + 1) / 2];
	}
	void Store(T x, int i, int j) {
		element[i * (i - 1) / 2 + j - 1] = x;
	}
	T Get(int i, int j) {
		return element[i * (i - 1) / 2 + j - 1];
	}
};
template<class T> ostream& operator<<(ostream& os, LowerTriangularMatrix<T>& x) {
	for (int i = 1; i <= x.n; i++) {
		for (int j = 1; j <= x.n; j++) {
			if (i >= j) {
				os << x.Get(i, j) << ' ';
			}
			else os << 0 << ' ';
		}
		cout << endl;
	}
	return os;
}
template<class T> class UpperTriangularMatrix {
public:
	int n;
	T* element;
	UpperTriangularMatrix(int m) {
		n = m;
		element = new T[n * (n + 1) / 2];
	}
	void Store(T x, int i, int j) {
		element[(i - 1) * n - (i - 1) * (i - 0) / 2 + j - 1] = x;
	}
	T Get(int i, int j) {
		return element[(i - 1) * n - (i - 1) * (i - 0) / 2 + j - 1];
	}
};
template<class T> ostream& operator<<(ostream& os, UpperTriangularMatrix<T>& x) {
	for (int i = 1; i <= x.n; i++) {
		for (int j = 1; j <= x.n; j++) {
			if (i <= j) {
				os << x.Get(i, j) << ' ';
			}
			else os << 0 << ' ';
		}
		cout << endl;
	}
	return os;
}
template<class T> void Transposition(LowerTriangularMatrix<T>& a, UpperTriangularMatrix<T>& b) {
	for (int i = 1; i <= a.n; i++) {
		for (int j = 1; j <= a.n; j++) {
			if (i <= j) {
				b.Store(a.Get(j, i), i, j);
			}
		}
	}
}
int main() {
	int n;
	cin >> n;
	LowerTriangularMatrix<int> a(n);
	int data = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i >= j) {
				a.Store(data, i, j);
				data++;
			}
		}
	}
	UpperTriangularMatrix<int> b(n);
	Transposition(a, b);
	cout << a << endl << b;
	return 0;
}