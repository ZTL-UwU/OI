#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
int hit[MAXN];
int rmq[MAXN][21];
int lg[MAXN];
int n, q;
void st_init()
{
    register int i, j;
    memset(rmq, 127, sizeof(rmq));
    lg[0]= -1;
    for (i = 1; i <= MAXN; i++) lg[i] = lg[i / 2] + 1;
    for (i = 1; i <= n; i++)
        rmq[i][0] = hit[i];
    for (i = 1; i <= 20; i++)
        for (j = 1; j + (1 << i) - 1 <= n; j++)
            rmq[j][i] = min(rmq[j][i - 1], rmq[j + (1 << (i - 1))][i - 1]);
}
int st(int l, int r)
{
    int k = lg[r - l + 1];
    int res = min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
    return res; 
}
int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> hit[i];
    st_init();
    for (int i = 0; i < q; i++)
    
{
    int l, r;
    cin >> l >> r;
    cout << st(l, r);
}
    return 0;
}