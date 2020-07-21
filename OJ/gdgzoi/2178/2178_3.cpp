#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data { int v, w; };
const int INF = 0x7fffffff;
const int MAXN = 2000;
vector<data> g[MAXN];
deque<int> q;
bool inque[MAXN];
int dis[MAXN];
void spfa(int start)
{
    inque[start] = true;
    q.push_back(start);
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
        inque[u] = false;
    }
}
int main()
{
    for (int i = 0; i < MAXN; i ++) dis[i] = INF;
    int n, m, start;
    cin >> n >> m >> start;
    for (int i = 0; i < m; i ++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back((data){v, w});
    }
    spfa(start);
    return 0;
}