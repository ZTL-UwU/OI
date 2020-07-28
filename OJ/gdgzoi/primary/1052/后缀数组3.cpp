#include <iostream>
#include <string.h>
using namespace std;
const int MAXN = 1e6 + 10;
int old_rnk[MAXN << 1];  //copy of rank
int rnk[MAXN << 1];      //rank
int bsk[MAXN];           //busket
int sub[MAXN];           //subffix
int tmp[MAXN];           //copy of s
char s[MAXN];
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    int m = max(n, 300);
    //discretization
    for (int i = 1; i <= n; i++) ++bsk[rnk[i] = s[i]];
    for (int i = 1; i <= m; i++) bsk[i] += bsk[i - 1];
    for (int i = 1; i <= m; i++) cout << bsk[i] << " ";
    cout << "\n";
    for (int i = n; i >= 1; i--) sub[bsk[rnk[i]]--] = i;
    for (int i = 1; i <= n; i++) cout << sub[i];
    cout << "\n";
    //raddix sort
    for (int w = 1; w < n; w <<= 1)
    {
        memset(bsk, 0, sizeof(bsk));
        for (int i = 1; i <= n; i++) ++bsk[rnk[(tmp[i] = sub[i]) + w]];
        for (int i = 1; i <= m; i++) bsk[i] += bsk[i - 1];
        for (int i = n; i >= 1; i--) sub[bsk[rnk[tmp[i] + w]]--] = tmp[i];
        memset(bsk, 0, sizeof(bsk));
        for (int i = 1; i <= n; i++) ++bsk[rnk[tmp[i] = sub[i]]];
        for (int i = 1; i <= m; i++) bsk[i] += bsk[i - 1];
        for (int i = n; i >= 1; i--) sub[bsk[rnk[tmp[i]]]--] = tmp[i];
        memcpy(old_rnk, rnk, sizeof(rnk));
        for (int k = 0, i = 1; i <= n; i++)
        {
            if (old_rnk[sub[i]] == old_rnk[sub[i - 1]] && old_rnk[sub[i] + w] == old_rnk[sub[i - 1] + w])
                rnk[sub[i]] = k;
            else
                rnk[sub[i]] = ++k;
        }
    }
    for (int i = 1; i <= n; i++)
        cout << sub[i] << " ";
    puts("");
    return 0;
}