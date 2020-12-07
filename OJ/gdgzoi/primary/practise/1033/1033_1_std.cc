#include <bits/stdc++.h>
using namespace std;
int node[10005];
void init(int x)
{
    for (int i = 0; i <= x; i++)
    {
        node[i] = i;
    }
}
int find(int x)
{
    if (node[x] == x)
        return x;
    return node[x] = find(node[x]);
}
void unite(int x, int y)
{
    int a = find(x);
    int b = find(y);
    node[a] = b;
}
int main()
{
    int n, m, k, x, y, a, b, tx, ty;
    char s[10005];
    bool first = true;
    cin >> s;
    if (s[0] >= '1' && s[0] <= '9')
    {
        a = b = n = 0;
        for (int i = 0; i < strlen(s); i++)
            n = n * 10 + (s[i] - '0');
        init(n);
    }
    while (true)
    {
        if (cin >> s)
            ;
        else
        {
            cout << a << ", " << b;
            break;
        }
        if (s[0] >= '1' && s[0] <= '9')
        {
            cout << a << ", " << b << endl;
            a = b = n = 0;
            for (int i = 0; i < strlen(s); i++)
                n = n * 10 + (s[i] - '0');
            init(n);
        }
        if (s[0] == 'c')
        {
            cin >> x >> y;
            tx = find(x);
            ty = find(y);
            if (tx != ty)
                unite(tx, ty);
        }
        if (s[0] == 'q')
        {
            cin >> x >> y;
            tx = find(x);
            ty = find(y);
            if (tx == ty)
                a++;
            else
                b++;
        }
    }
}