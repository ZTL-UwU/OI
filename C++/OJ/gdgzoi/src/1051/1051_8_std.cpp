#include <bits/stdc++.h>
using namespace std;
char str[3000005];
int cr[3000005], ch;
bool vis[3000005];
stack<int> ans;
void init()
{
    memset(str, 0, sizeof(str));
    memset(cr, 0, sizeof(str));
    memset(vis, 0, sizeof(vis));
    while (ans.size())
        ans.pop();
}
void manacher()
{
    init();
    int cnt = 1, c = -1, pos = -1, maxlen = 0;
    str[0] = '$';
    cin >> str + 1;
    int len = strlen(str);
    cout << len << "\n";
    for (int i = 1; i < len; i++)
    {
        if (i >= c)
            cr[i] = 1;
        else
            cr[i] = min(cr[pos * 2 - i], c - i);
        while (str[i - cr[i]] == str[i + cr[i]])
            cr[i]++;
        if (i + cr[i] - 1 > c)
        {
            c = i + cr[i];
            pos = i;
        }
    }
    for (int i = 1; i <= len; i++)
        cout << cr[i] << " ";
    cout << "\n";
    vis[len] = true;
    for (int i = len - 1; i >= 1; i--)
    {
        if (vis[i + cr[i]] && (i + cr[i] == len || i - cr[i] == 0))
        {
            vis[i + 1] = true;
            ans.push(i);
        }
    }
    while (ans.size())
    {
        cout << ans.top() << ' ';
        ans.pop();
    }
    cout << '\n';
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        manacher();
}
