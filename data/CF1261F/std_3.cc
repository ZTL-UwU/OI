#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e7 + 10, mod = 998244353;
int lys, ans, n;
vector<int> A[2][61], B[2][61];
struct node
{
    int x, y;
    friend bool operator<(node l, node r) { return l.x < r.x; }
} a[N];
void insert1(int k, int d, int L, int R, int l, int r)
{
    if (L >= l && R <= r)
    {
        A[k][d].push_back(L);
        return;
    }
    int mid = (L + R) >> 1;
    if (l <= mid)
        insert1(k, d - 1, L, mid, l, r);
    if (r > mid)
        insert1(k, d - 1, mid + 1, R, l, r);
}
void insert2(int k, int d, int L, int R, int l, int r)
{
    B[k][d].push_back(L);
    if (L >= l && R <= r)
        return;
    int mid = (L + R) >> 1;
    if (l <= mid)
        insert2(k, d - 1, L, mid, l, r);
    if (r > mid)
        insert2(k, d - 1, mid + 1, R, l, r);
}
signed main()
{
    // freopen("1.in","r",stdin);
    cin >> n;
    for (int i = 1, l, r; i <= n; i++)
    {
        cin >> l >> r;
        insert1(0, 60, 0, (1ll << 60) - 1, l, r);
        insert2(1, 60, 0, (1ll << 60) - 1, l, r);
    }
    cin >> n;
    for (int i = 1, l, r; i <= n; i++)
    {
        cin >> l >> r;
        insert1(1, 60, 0, (1ll << 60) - 1, l, r);
        insert2(0, 60, 0, (1ll << 60) - 1, l, r);
    }
    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i <= 60; i++)
        {
            for (int l = 0; l < A[k][i].size(); l++)
            {
                for (int r = 0; r < B[k][i].size(); r++)
                {
                    a[++lys] = (node){A[k][i][l] ^ B[k][i][r], (A[k][i][l] ^ B[k][i][r]) + (1ll << i) - 1};
                }
            }
        }
    }
    sort(a + 1, a + lys + 1);
    a[0].y = -1;
    for (int i = 1; i <= lys; i++)
    {
        if (a[i].y <= a[i - 1].y)
        {
            swap(a[i], a[i - 1]);
            continue;
        }
        if (a[i].x <= a[i - 1].y)
            a[i].x = a[i - 1].y + 1;
        if ((a[i].y - a[i].x + 1) & 1)
            ans += (a[i].y + a[i].x) / 2 % mod * ((a[i].y - a[i].x + 1) % mod) % mod;
        else
            ans += (a[i].y - a[i].x + 1) / 2 % mod * ((a[i].y + a[i].x) % mod) % mod;
    }
    cout << ans % mod;
    return 0;
}