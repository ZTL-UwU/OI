#include <iostream>
#include <string.h>
using namespace std;
const int MAXN = 1e6 + 10;
int old_rnk[MAXN << 1]; // copy of rank
int rnk[MAXN << 1];     // rank
int bsk[MAXN];          // busket
int suf[MAXN];          // suffix
int tmp[MAXN];          // copy of suffix
int sot[MAXN];
char s[MAXN];
int i, k, w;
bool check() { return old_rnk[suf[i]] == old_rnk[suf[i - 1]] && old_rnk[suf[i] + w] == old_rnk[suf[i - 1] + w]; }
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int m = max(n, 300);
    // discretization
    for (i = 1; i <= n; ++i)
        ++bsk[rnk[i] = s[i]];
    for (i = 1; i <= m; ++i)
        bsk[i] += bsk[i - 1];
    for (i = n; i >= 1; --i)
        suf[bsk[rnk[i]]--] = i;
    // raddix sort
    for (w = 1; w < n; w <<= 1, m = k)
    {
        for (k = 0, i = n; i > n - w; --i)
            sot[++k] = i;
        for (i = 1; i <= n; ++i)
            if (suf[i] > w)
                sot[++k] = suf[i] - w;
        memset(bsk, 0, sizeof(bsk));
        for (i = 1; i <= n; ++i)
            ++bsk[tmp[i] = rnk[sot[i]]];
        for (i = 1; i <= m; ++i)
            bsk[i] += bsk[i - 1];
        for (i = n; i >= 1; --i)
            suf[bsk[tmp[i]]--] = sot[i];
        memcpy(old_rnk, rnk, sizeof(rnk));
        for (k = 0, i = 1; i <= n; i++)
            rnk[suf[i]] = check() ? k : ++k;
    }
    for (i = 1; i <= n; ++i)
        printf("%d ", suf[i]);
    puts("");
    return 0;
}