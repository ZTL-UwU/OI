#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);

	string str;
	cin >> str;

	cout << str.size() / 2 << " " << str.size() / 4;
	return 0;
}