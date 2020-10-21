#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int v;
    int w;
};
const int MAXN_N = 210;
const int MAXN = 1e4;
int g[MAXN_N][MAXN_N];
int n, m, s, t;
int minn[MAXN_N];
int pre[MAXN_N];
inline int EK_bfs()
{
    memset(minn, 127, sizeof(minn));
    memset(pre, -1, sizeof(pre));
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 1; i <= n; i++)
        {
            if (pre[i] == -1 && g[u][i])
            {
                pre[i] = u;
                minn[i] = min(minn[u], g[u][i]);
                q.push(i);
            }
        }
    }
    if (pre[t] == -1)
        return -1;
    return minn[t];
}
inline long long EK()
{
    long long ans = 0;
    while (1)
    {
        long long tmp = EK_bfs();
        if (tmp == -1)
            break;
        int u = t;
        while (u != s)
        {
            g[u][pre[u]] += tmp;
            g[pre[u]][u] -= tmp;
            u = pre[u];
        }
        ans += tmp;
    }
    return ans;
}
int main()
{
    while (cin >> m >> n)
    {
        memset(g, 0, sizeof(g));
        s = 1;
        t = n;
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g[u][v] += w;
        }
        cout << EK() << "\n";
    }
    return 0;
}