#include <iostream>
#include <string.h>
using namespace std;
const int MAXN = 1e6 + 10;
int old_rnk[MAXN << 1]; // copy of rank
int rnk[MAXN << 1];     // rank
int bsk[MAXN];          // busket
int suf[MAXN];          // suffix
int tmp[MAXN];          // copy of suffix
char s[MAXN];
int i, k;
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int m = max(n, 300);
    // discretization
    for (i = 1; i <= n; i++)
        ++bsk[rnk[i] = s[i]];
    for (i = 1; i <= m; i++)
        bsk[i] += bsk[i - 1];
    for (i = n; i >= 1; i--)
        suf[bsk[rnk[i]]--] = i;
    // raddix sort
    for (int w = 1; w < n; w <<= 1)
    {
        memset(bsk, 0, sizeof(bsk));
        for (i = 1; i <= n; i++)
            ++bsk[rnk[(tmp[i] = suf[i]) + w]];
        for (i = 1; i <= m; i++)
            bsk[i] += bsk[i - 1];
        for (i = n; i >= 1; i--)
            suf[bsk[rnk[tmp[i] + w]]--] = tmp[i];
        memset(bsk, 0, sizeof(bsk));
        for (i = 1; i <= n; i++)
            ++bsk[rnk[tmp[i] = suf[i]]];
        for (i = 1; i <= m; i++)
            bsk[i] += bsk[i - 1];
        for (i = n; i >= 1; i--)
            suf[bsk[rnk[tmp[i]]]--] = tmp[i];
        memcpy(old_rnk, rnk, sizeof(rnk));
        for (k = 0, i = 1; i <= n; i++)
        {
            if (old_rnk[suf[i]] == old_rnk[suf[i - 1]] && old_rnk[suf[i] + w] == old_rnk[suf[i - 1] + w])
                rnk[suf[i]] = k;
            else
                rnk[suf[i]] = ++k;
        }
        m = k;
    }
    for (i = 1; i <= n; i++)
        printf("%d ", suf[i]);
    return 0;
}