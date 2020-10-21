#include <algorithm>
#include <iostream>
#include <stdio.h>
using namespace std;
struct data { int t, v; };
const int MAXN = 1e5 + 10;
data a[MAXN];
inline bool cmp(data x, data y)
{
    if (x.t == y.t)
        return x.v > y.v;
    return x.t < y.t;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i].t;
    for (int i = 0; i < n; i++)
        cin >> a[i].v;
    sort(a, a + n, cmp);
    int now = 0;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i].t >= now)
        {
            now++;
            ans += a[i].v;
        }
    }
    cout << ans;
    return 0;
}