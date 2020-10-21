#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAXN = 1e6 + 10;
int old_rnk[MAXN * 2];
int rnk[MAXN * 2];
int rmq[MAXN][25];
char str[MAXN];
int bsk[MAXN];
int suf[MAXN];
int sot[MAXN];
int tmp[MAXN];
int hit[MAXN];
int lg[MAXN];
int n;
//suffix array
bool check(int i, int w)
{
    return old_rnk[suf[i]] == old_rnk[suf[i - 1]] && old_rnk[suf[i] + w] == old_rnk[suf[i - 1] + w];
}
void get_suf()
{
    int m = 150;
    register int i, k, w;
    for (i = 1; i <= n; ++i) ++bsk[rnk[i] = str[i]];
    for (i = 1; i <= m; ++i) bsk[i] += bsk[i - 1];
    for (i = n; i >= 1; --i) suf[bsk[rnk[i]]--] = i;
    for (w = 1; w < n; w *= 2, m = k)
    {
        for (k = 0, i = n; i > n - w; --i) sot[++k] = i;
        for (i = 1; i <= n; ++i)
            if (suf[i] > w)
                sot[++k] = suf[i] - w;
        memset(bsk, 0, sizeof(bsk));
        for (i = 1; i <= n; ++i) ++bsk[tmp[i] = rnk[sot[i]]];
        for (i = 1; i <= m; ++i) bsk[i] += bsk[i - 1];
        for (i = n; i >= 1; --i) suf[bsk[tmp[i]]--] = sot[i];
        memcpy(old_rnk, rnk, sizeof(rnk));
        for (k = 0, i = 1; i <= n; ++i)
            rnk[suf[i]] = check(i, w) ? k : ++k;
    }
    for (k = 0, i = 1; i <= n; ++i)
    {
        if (k) --k;
        while(str[i + k] == str[suf[rnk[i] - 1] + k]) ++k;
        hit[rnk[i]] = k;
    }
}
//rmq
void st_init()
{
    register int i, j;
    memset(rmq, 0x3f, sizeof(rmq));
    lg[0] = -1;
    for (i = 1; i <= MAXN; ++i) lg[i] = lg[i / 2] + 1;
    for (i = 1; i <= n; ++i)
        rmq[i][0] = hit[i];
    for (i = 1; (1 << i) <= n; ++i)
        for (j = 1; j + (1 << i) - 1 <= n; ++j)
            rmq[j][i] = min(rmq[j][i - 1], rmq[j + (1 << (i - 1))][i - 1]);
}
int st(int l, int r)
{
    if (l > r)
        swap(l, r);
    l++;
    int k = lg[r - l + 1];
    int res = min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
    return res;
}
int main()
{
    scanf("%s", str + 1);
    n = strlen(str + 1);
    get_suf();
    st_init();
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (l == r)
        {
            printf("%d\n", n - l + 1);
            continue;
        }
        l = rnk[l];
        r = rnk[r];
        printf("%d\n", st(l, r));
    }
    return 0;
}