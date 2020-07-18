#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7fffffff;
int main()
{
    srand((int)time(0));
    int a = (rand() * rand()) % INF;
    int b = (rand() * rand()) % INF;
    int c = __gcd(a, b);
    cout << a << "\n" << b << "\n" << c << "\n";
    return 0;
}