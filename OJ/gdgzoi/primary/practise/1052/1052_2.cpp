#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAXN = 1e6 + 10;
int old_rnk[MAXN * 2];
int rnk[MAXN * 2];
int bsk[MAXN];
int suf[MAXN];
int sot[MAXN];
int tmp[MAXN];
string s;
string str;
int n, m, i, w, k;
// get suffix_array
bool check_suf() { return old_rnk[suf[i]] == old_rnk[suf[i - 1]] && old_rnk[suf[i] + w] == old_rnk[suf[i - 1] + w]; }
inline void get_suf()
{
    m = 150;
    n = str.size() - 1;
    // discretization
    for (i = 1; i <= n; i++)
        ++bsk[rnk[i] = str[i]];
    for (i = 1; i <= m; i++)
        bsk[i] += bsk[i - 1];
    for (i = n; i >= 1; i--)
        suf[bsk[rnk[i]]--] = i;
    // radix_sort
    for (w = 1; w < n; w *= 2, m = k)
    {
        for (k = 0, i = n; i > n - w; i--)
            sot[++k] = i;
        for (i = 1; i <= n; i++)
            if (suf[i] > w)
                sot[++k] = suf[i] - w;
        memset(bsk, 0, sizeof(bsk));
        for (i = 1; i <= n; i++)
            ++bsk[tmp[i] = rnk[sot[i]]];
        for (i = 1; i <= m; i++)
            bsk[i] += bsk[i - 1];
        for (i = n; i >= 1; i--)
            suf[bsk[tmp[i]]--] = sot[i];
        memcpy(old_rnk, rnk, sizeof(rnk));
        for (k = 0, i = 1; i <= n; i++)
            rnk[suf[i]] = check_suf() ? k : ++k;
    }
}
// binary search
int check_bin(int key)
{
    int size = s.size() - 1;
    for (i = 0; i < size; i++)
    {
        if (s[i + 1] > str[suf[key] + i])
            return 1;
        else if (s[i + 1] < str[suf[key] + i])
            return 0;
    }
    return 2;
}
int solve()
{
    int l = 0, r = n + 1;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        int tmp = check_bin(mid);
        if (tmp == 1)
            l = mid;
        else if (tmp == 0)
            r = mid;
        else
            return mid;
    }
    return -1;
}
int main()
{
    cin >> str;
    str = "#" + str;
    get_suf();
    int t;
    scanf("%d", &t);
    while (t--)
    {
        cin >> s;
        s = "#" + s;
        printf("%d ", suf[solve()] - 1);
    }
    return 0;
}