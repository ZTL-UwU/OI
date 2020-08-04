struct data // 邻接表 u 的对应点 v 和边权 w
{
    int v;
    int w;
};
vector<data> g[MAX]; // vector 邻接表存图
// 已确定 dis 值的点集 C, vis[x] 为 true 表示在集合中
bool vis[MAX];
int dis[MAX]; // 最短路长度

inline void Dijkstra()
{
    // 初始化为无穷大
    for (int i = 0; i < MAX; i++)
        dis[i] = INF;
    dis[1] = 0;
    // 由于每次确定一个点的 dis 值，所以需要循环 n 次才使得 C = V
    for (int i = 0; i < n; i++)
    {
        int u = 0;
        // 枚举所有点，寻找不在集合 C 中 dis 值最小的点
        for (int j = 1; j <= n; j++)
            if (!vis[j] && (u == 0 || dis[j] < dis[u]))
                u = j;
        // 将找到的点 u 加入集合 C
        vis[u] = true;
        // 枚举 u 的出边 u -> v ，进行松弛更新
        for (int j = 0; j < g[u].size(); j++)
        {
            int v = g[u][j].v;
            int w = g[u][j].w;
            if (dis[u] + w < dis[v])
                dis[v] = dis[u] + w;
        }
    }
}