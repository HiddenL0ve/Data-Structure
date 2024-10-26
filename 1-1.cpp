#include<iostream>
#include<fstream>
using namespace std;
long long tem[150];
long long f(int n)
{
	if (n < 2)
	{
		return 1;
	}
	if (tem[n] > 0)
	{
		return tem[n];
	}
	tem[n] = f(n - 1) + f(n - 2);
	return tem[n];
}
int main()
{
	int n;
	cin >> n;
	if (n >= 0 && n <= 90) {
		printf("%I64d", f(n));
		cout << endl;
	}
	else
		cout << "WRONG" << endl;
	return 0;
}