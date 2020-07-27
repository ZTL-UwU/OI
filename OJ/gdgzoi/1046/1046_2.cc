#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include <queue>
using namespace std;
struct data2 { int minn, dis; };
struct data { int v, w, f; };
struct coord { int x, y; };
const int INF = 0x7fffffff;
const int MAXN = 1e3;
vector<data> g[MAXN];
vector<coord> home;
vector<coord> men;
bool inque[MAXN];
int minn[MAXN];
int pre[MAXN];
int dis[MAXN];
int n, m, s, t;
int ans;
inline data2 EK_SPFA()
{
    memset(minn, 127, sizeof(minn));
    memset(inque, 0, sizeof(inque));
    memset(dis, 127, sizeof(dis));
    for (int i = 0; i < MAXN; i++)
        pre[i] = -1;
    queue<int> q;
    q.push(s);
    inque[s] = true;
    dis[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inque[u] = false;
        for (int i = 0; i < g[u].size(); i++)
        {
            data v = g[u][i];
            if (v.w > 0 && dis[v.v] > dis[u] + v.f)
            {
                minn[v.v] = min(minn[u], v.w);
                dis[v.v] = dis[u] + v.f;
                pre[v.v] = u;
                if (!inque[v.v])
                {
                    inque[v.v] = true;
                    q.push(v.v);
                }
            }
        }
    }
    data2 ret;
    if (pre[t] == -1)
        ret.minn = -1;
    else
    {
        ret.minn = minn[t];
        ret.dis = dis[t];
    }
    return ret;
}
inline void EK()
{
    while (1)
    {
        data2 tmp = EK_SPFA();
        if (tmp.minn == -1)
            break;
        int u = t;
        while (u != s)
        {
            int ff;
            for (int i = 0; i < g[pre[u]].size(); i++)
            {
                if (g[pre[u]][i].v == u)
                {
                    g[pre[u]][i].w -= tmp.minn;
                    ff = g[pre[u]][i].f;
                    break;
                }
            }
            bool flag = true;
            for (int i = 0; i < g[u].size(); i++)
            {
                if (g[u][i].v == pre[u])
                {
                    g[u][i].w += tmp.minn;
                    flag = false;
                    break;
                }
            }
            if (flag)
                g[u].push_back((data){pre[u], tmp.minn, -ff});
            u = pre[u];
        }
        ans += tmp.minn * tmp.dis;
    }
}
inline void init()
{
    for (int i = 0; i < MAXN; i++)
        g[i].clear();
    home.clear();
    men.clear();
    ans = 0;
}
int main()
{
    s = 0;
    t = 300;
    while (cin >> n >> m)
    {
        if (!n && !m)
            return 0;
        for (int i = 0; i < n; i++)
        {
            string str;
            cin >> str;
            for (int j = 0; j < m; j++)
            {
                if (str[j] == 'H')
                {
                    home.push_back((coord){i, j});
                    g[home.size() + 150].push_back((data){t, 1, 0});
                }
                else if (str[j] == 'm')
                {
                    men.push_back((coord){i, j});
                    g[s].push_back((data){men.size(), 1, 0});
                }
            }
        }
        for (int i = 0; i < men.size(); i++)
            for (int j = 0; j < home.size(); j++)
                g[i + 1].push_back((data){j + 151, INF, abs(men[i].x - home[j].x) + abs(men[i].y - home[j].y)});
        EK();
        cout << ans << "\n";
        init();
    }
    return 0;
}