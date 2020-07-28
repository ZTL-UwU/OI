#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAXN = 1e5 + 10;
int old_rk[MAXN * 2];
int rk[MAXN * 2];
int ht[MAXN * 2];
int bu[MAXN];
int sa[MAXN];
int tm[MAXN];
int so[MAXN];
string str;
bool check(int i, int w)
{
    return old_rk[sa[i]] == old_rk[sa[i - 1]] && old_rk[sa[i] + w] == old_rk[sa[i - 1] + w];
}
inline void get_sa()
{
    register int i, k, w, n, m;
    n = str.size() - 1;
    m = 150;
    for (i = 1; i <= n; i++) ++bu[rk[i] = str[i]];
    for (i = 1; i <= m; i++) bu[i] += bu[i - 1];
    for (i = n; i >= 1; i--) sa[bu[rk[i]]--] = i;
    for (w = 1; w < n; w *= 2, m = k)
    {
        for (i = n, k = 0; i > n - w; i--) so[++k] = i;
        for (i = 1; i <= n; i++)
            if (sa[i] > w)
                so[++k] = sa[i] - w;
        memset(bu, 0, sizeof(bu));
        for (i = 1; i <= n; i++) ++bu[tm[i] = rk[so[i]]];
        for (i = 1; i <= m; i++) bu[i] += bu[i - 1];
        for (i = n; i >= 1; i--) sa[bu[tm[i]]--] = so[i];
        memcpy(old_rk, rk, sizeof(rk));
        for (k = 0, i = 1; i <= n; i++)
            rk[sa[i]] = check(i, w) ? k : ++k;
    }
    for (i = 1, k = 0; i <= n; i++)
    {
        if (k) --k;
        while (str[i + k] == str[sa[rk[i] - 1] + k]) ++k;
        ht[rk[i]] = k;
    }
}
int main()
{
    cin >> str;
    str = "#" + str;
    get_sa();
    for (int i = 1; i <= str.size() - 1; i++)
        cout << rk[i] << " ";
    cout << "\n";
    for (int i = 1; i <= str.size() - 1; i++)
        cout << ht[i] << " ";
    puts("");
}