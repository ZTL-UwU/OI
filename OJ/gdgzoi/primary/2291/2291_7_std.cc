#include <bits/stdc++.h>
using namespace std;
struct query
{
    int l, r, id;
} q[1000005];
int n, m, tmp;
int block[1000005], a[1000005], cnt[1000005];
int ans[1000005];
bool cmp(query a, query b)
{
    return (block[a.l] ^ block[b.l]) ? block[a.l] < block[b.l] : ((block[a.l] & 1) ? a.r < b.r : a.r > b.r);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int k = sqrt(n);
    for (int i = 1; i <= n; i++)
        block[i] = (i - 1) / k + 1;
    cin >> m;
    for (int i = 1; i <= m; i++)
    {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    sort(q + 1, q + m + 1, cmp);
    int l = 0, r = 0;
    for (int i = 1; i <= m; i++)
    {
        while (q[i].l < l)
            tmp += !(cnt[a[--l]]++);
        while (q[i].l > l)
            tmp -= !(--cnt[a[l++]]);
        while (q[i].r < r)
            tmp -= !(--cnt[a[r--]]);
        while (q[i].r > r)
            tmp += !(cnt[a[++r]]++);
        ans[q[i].id] = tmp;
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
}
