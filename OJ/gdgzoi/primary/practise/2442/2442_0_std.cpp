#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 50000
using namespace std;
struct node
{
    int val, num;
} a[maxn];
int n;
int c[maxn];
int add(int x, int k)
{
    for (int i = x; i <= n; i += i & (-i))
        c[i] += k;
}
int query(int x)
{
    int sum = 0;
    for (int i = x; i > 0; i -= i & (-i))
        sum += c[i];
    return sum;
}
int cmp(node x, node y) { return x.val > y.val; }
int ans;
int main()
{
    freopen("P1908_6.in", "r", stdin);
    cin >> n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i].val), a[i].num = i;
    sort(a + 1, a + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        add(a[i].num, 1);
        ans += query(a[i].num - 1);
    }
    cout << ans << endl;
}