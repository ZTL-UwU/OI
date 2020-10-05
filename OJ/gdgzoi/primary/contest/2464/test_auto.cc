#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void read(auto &x)
{ // 相当于 template<class T> void read(T &x)
    x = 0;
    char c;
    do
        c = getchar();
    while (!isdigit(c));
    do
        x = x * 10 + c - 48, c = getchar();
    while (isdigit(c));
}
int main()
{
    int x;
    read(x);
    ll y;
    read(y);
    //string z;read(z); // CE
    cout << x + y;
    return 0;
}