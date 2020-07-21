#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lli long long int
using namespace std;
const int M = 1005000;
int n;
int nxt[M];
char s[M];
signed main()
{
    cin >> n;
    scanf("%s", s + 1);
    int k = 0;
    for (int i = 2; i <= n; i++)
    {
        while (k && s[i] != s[k + 1])
            k = nxt[k];
        if (s[k + 1] == s[i])
            k++;
        nxt[i] = k;
    }
    for (int i = 0; i <= n + 10; i ++)
        cout << nxt[i] << " ";
    cout << "\n";
    lli ans = 0;
    for (int i = 1; i <= n; i++)
        while (nxt[nxt[i]])
            nxt[i] = nxt[nxt[i]], cout << nxt[i] << " ";
    for (int i = 1; i <= n; i++)
        if (nxt[i])
            ans += (i - nxt[i]);
    cout << ans;
    return 0;
}