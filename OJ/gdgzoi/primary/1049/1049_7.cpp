#include <iostream>
#include <stdio.h>
using namespace std;
int nxt[(int)1e6 + 10];
int n;
void get_nxt(string s)
{
    nxt[0] = -1;
    int i = 0, k = -1;
    while (i < n)
    {
        if (k == -1 || s[i] == s[k])
            nxt[++i] = ++k;
        else
            k = nxt[k];
    }
}
int main()
{
    cin >> n;
    string s;
    cin >> s;
    get_nxt(s);
    nxt[0] = 0;
    for (int i = 1; i <= n; i++)
        while (nxt[nxt[i]])
            nxt[i] = nxt[nxt[i]];
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (nxt[i])
            ans += (i - nxt[i]);
    cout << ans << "\n";
    return 0;
}