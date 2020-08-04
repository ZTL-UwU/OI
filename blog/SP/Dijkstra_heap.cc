struct node
{
    int v;
    int w;
};
struct data
{
    int dis; // 用于在优先队列中找出所有点中 dis 值最小的点
    int num; // 用于记录这个点的编号
    // 重载符号 >
    bool operator>(const data x) const
    {
        if (this->dis != x.dis)
            return this->dis > x.dis;
        return this->num > x.num;
    }
};
vector<node> g[MAX];
bool vis[MAX];
int dis[MAX];

void Dijkstra()
{
    // 初始化为无限大
    for (int i = 0; i < MAX; i++)
        dis[i] = INF;
    dis[1] = 0;
    // 声明优先队列，相当于小根堆
    priority_queue<data, vector<data>, greater<data>> pq;
    // 初始化优先队列，插入起点
    pq.push((data){0, 1});
    while (!pq.empty())
    {
        // 取出堆顶
        int u = pq.top().num;
        pq.pop();
        // u 不可以在集合 C 中
        if (vis[u])
            continue;
        // 将 u 加入集合 C
        vis[u] = true;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            // 松弛操作
            if (!vis[v] && dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                // 将有可能是所有点中 dis 值最小的点加入堆中
                pq.push((data){dis[v], v});
            }
        }
    }
}