#include <iostream>
#include <vector>
using namespace std;

template <class T>
class SparseMatrix {
public:
    struct Element {
        int x;
        int y;
        T data;
    };
    int row;
    int col;
    vector<Element> elem;

    SparseMatrix(int m, int n) {
        row = m;
        col = n;
    }

    void Store(int m, int n, T d) {
        Element t = { m, n, d };
        elem.push_back(t);
    }

    T Get(int m, int n) {
        for (int i = 0; i < elem.size(); i++) {
            if (elem[i].x == m && elem[i].y == n) {
                return elem[i].data;
            }
        }
        return T(0);
    }

    void input() {
        int num;
        cin >> num;
        if (num <= row * col) {
            for (int i = 0; i < num; i++) {
                int m, n, d;
                cin >> m >> n >> d;
                Store(m, n, d);
            }
        }
    }

    void Display() {
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                cout << Get(i, j) << ' ';
            }
            cout << endl;
        }
    }
};

template <class T>
SparseMatrix<T> operator*(SparseMatrix<T>& a, SparseMatrix<T>& b) {
    if (a.col != b.row) {
        cout << "WRONG" << endl;
        return SparseMatrix<T>(0, 0);
    }
    else {
        SparseMatrix<T> c(a.row, b.col);
        for (int i = 1; i <= a.row; i++) {
            for (int j = 1; j <= b.col; j++) {
                T tem = 0;
                for (int k = 1; k <= a.col; k++) {
                    tem += a.Get(i, k) * b.Get(k, j);
                }
                if (tem != 0) {
                    c.Store(i, j, tem);
                }
            }
        }
        return c;
    }
}

int main() {
    int rowa, cola;
    cin >> rowa >> cola;
    SparseMatrix<int> a(rowa, cola);
    a.input();
    int rowb, colb;
    cin >> rowb >> colb;
    SparseMatrix<int> b(rowb, colb);
    b.input();
    SparseMatrix<int> c = a * b;
    c.Display();
    return 0;
}
