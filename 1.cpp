
#include<iostream>
using namespace std;
int main() {
    int n = 5;
    int i;
    int a;
    for (i = 0; i < n; i++) {
        for (a = 1; a <= i + 2; a++) {
            for (int j = 1; j <= 2 * n - 2 * a + 2; j++)
                cout << "  ";
            for (int j = 1; j <= 4 * a - 3; j++)
                cout << " " << '*';
            cout << endl;
        }
    }
    for (a = 1; a <= n + 1; a++) {
        for (int j = 1; j <= (4 * n + 1) / 2 - 1; j++)
            cout << "  ";
        for (int j = 1; j <= 3; j++)
            cout << " " << '*';
        cout << endl;
    }
    cout << endl;
    cout << "                 " << "Merry Christmas !";
    system("pause");
    return 0;
}
