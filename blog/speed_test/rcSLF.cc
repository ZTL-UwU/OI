#include <iostream>
#include <cstdio>
#include <deque>
#define INF (1e9 + 1)
using namespace std;

const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;

deque<int> q;

int tot, head[MAXN], ver[MAXM << 1], cst[MAXM << 1], nxt[MAXM << 1];
inline void add(int u, int v, int w)
{
    int x = ++tot;
    ver[x] = v, cst[x] = w;
    nxt[x] = head[u];
    head[u] = x;
}

int n, m, s;
int R, val;

int dis[MAXN], cnt[MAXN];
bool inq[MAXN];

void spfa()
{
    for (int i = 1; i <= n; ++i)
        dis[i] = INF;
    dis[s] = 0;
    inq[s] = true;
    q.push_front(s);
    while (!q.empty())
    {
        int u = *(q.begin());
        q.pop_front();
        inq[u] = false;
        for (int i = head[u], v; i; i = nxt[i])
        {
            v = ver[i];
            if (dis[v] > dis[u] + cst[i])
            {
                dis[v] = dis[u] + cst[i];
                if (!inq[v])
                {
                    inq[v] = true;
                    if (cnt[v] && cnt[v] < R)
                    {
                        q.push_front(v);
                        ++cnt[v];
                    }
                    else
                    {
                        if (q.size() == 0)
                            q.push_back(v);
                        else if (dis[*(q.begin())] >= dis[v] - val)
                            q.push_front(v);
                        else
                            q.push_back(v);
                        if (!cnt[v])
                            cnt[v] = 1;
                    }
                }
            }
        }
    }
}

int main()
{
    R = 200, val = 10;
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 1, u, v, w; i <= m; ++i)
    {
        scanf("%d %d %d", &u, &v, &w);
        add(u, v, w);
    }
    spfa();
    for (int i = 1; i <= n; ++i)
        printf("%d ", dis[i]);
    return 0;
}