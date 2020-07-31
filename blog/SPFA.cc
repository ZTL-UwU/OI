struct data // 邻接表 u 的对应点 v 和边权 w
{
    int v;
    int w;
};
vector<data> g[MAX]; // vector 邻接表存图
bool inque[MAX];     // 队列状态哈希表
int dis[MAX];        // 最短路长度

void SPFA()
{
    // 初始化为无穷大
    for (int i = 0; i < MAX; i++)
        dis[i] = INF;
    dis[1] = 0;        // 边界
    queue<int> q;      // 创建队列
    q.push(1);         // 初始化队列
    inque[1] = true;   // 记录 inque 状态
    while (!q.empty()) // 执行 bfs 直到队列为空
    {
        int u = q.front(); // 取出队头
        q.pop();           // 弹出队头
        inque[u] = false;  // 去除 inque 记录
        // 枚举被松弛的点 v
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            // 松弛操作
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                // 入队
                if (!inque[v])
                {
                    inque[v] = true;
                    q.push(v);
                }
            }
        }
    }
}