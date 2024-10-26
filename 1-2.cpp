#include<iostream>
#include<fstream>
using namespace std;
void f(char* arr,int n,int len) {
	if (n == 0) {
		for (int i = 0; i < len; i++) {
			if (arr[i] != '0') {
				cout << arr[i] << ' ';
			}
		}
		cout << endl;
		return;
	}
	for (int j = 0; j <= 1; j++) {
		char* tem = new char[len];
		for (int i = 0; i < len; i++) {
			tem[i] = arr[i];
		}
		if (j == 0) {
			tem[n - 1] = '0';
		}
		f(tem, n - 1, len);
	}
}
int main() {
	char arr[30];
	int n;
	cin >> n;
	if (n > 0 && n <= 26) {
		for (int i = 0; i < n; i++) {
			arr[i] = 'a' + i;
		}
		f(arr, n, n);
	}
	else
		cout << "WRONG";
	return 0;
}