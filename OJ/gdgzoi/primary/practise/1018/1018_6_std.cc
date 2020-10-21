#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <queue>

typedef long long LL;
using namespace std;

int n;
int x, y, c[150010];
struct node
{
    int l, r;
    bool operator<(const node &x) const
    {
        return r < x.r;
    }
} a[1005];

int lowbit(int x)
{
    return x & (-x);
}

void add(int x)
{
    while (x < 150005)
    {
        c[x]++;
        x += lowbit(x);
    }
}

int sum(int x)
{
    int res = 0;
    while (x)
    {
        res += c[x];
        x -= lowbit(x);
    }
    return res;
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", &x, &y);
        a[i].l = ((x - y) > 0 ? x - y : 0) + 2; //防止出现0，用树状数组很怕遇到0。。
        a[i].r = (x + y) + 2;
    }
    int ans = 0;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        int t = sum(a[i].r) - sum(a[i].l - 1); //+2也是为了这里减一不为0
        std::cout << t << "\n";
        if (t)
            continue;
        ans++;
        add(a[i].r);
    }
    printf("%d\n", ans);

    return 0;
}