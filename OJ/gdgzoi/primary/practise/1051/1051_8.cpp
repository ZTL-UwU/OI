#include <iostream>
#include <string.h>
#include <stack>
using namespace std;
const int MAXN = 1e6 + 10;
// Manacher
int ra[2 * MAXN];
inline void Mancher(string str)
{
    int mx = 0, id = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (i < mx)
            ra[i] = min(ra[2 * id - i], mx - i);
        while (i + ra[i] < str.size() && i - ra[i] >= 0 && str[i + ra[i]] == str[i - ra[i]])
            ra[i]++;
        if (i + ra[i] > mx)
        {
            mx = i + ra[i];
            id = i;
        }
    }
}
// solve Loj#6387
bool vis[2 * MAXN];
stack<int> ans;
inline void solve(string str)
{
    vis[str.size()] = true;
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (vis[i + ra[i]] && (i + ra[i] == str.size() || i - ra[i] == -1))
        {
            vis[i + 1] = true;
            ans.push(i);
        }
    }
    while (!ans.empty())
    {
        cout << ans.top() + 1 << " ";
        ans.pop();
    }
    cout << "\n";
}
inline void clear()
{
    for (int i = 0; i < 2 * MAXN; i++)
    {
        ra[i] = 0;
        vis[i] = false;
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        Mancher(s);
        solve(s);
        clear();
    }
    return 0;
}