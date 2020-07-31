struct edge // 一条边上的点 u、点 v、边权 w
{
    int u;
    int v;
    int w;
};
vector<edge> e; // vector 存边方法存图
int dis[MAX];   // 最短路长度

void Bellman_Ford()
{
    // 初始化为无穷大
    for (int i = 0; i < MAX; i++)
        dis[i] = INF;
    dis[1] = 0; // 边界
    while (1)
    {
        bool relaxable = false;
        // edge存边，edge.size() 即为 m
        for (int i = 0; i < edge.size(); i++)
        {
            // 松弛操作
            if (dis[edge[i].v] > dis[edge[i].u] + w)
            {
                dis[edge[i].v] = dis[edge[i].u] + w;
                // 记录是否有进行松弛操作
                flag = true;
            }
        }
        // 若没有进行松弛操作，说明dis已经更新完成，退出
        if (relaxable == false)
            break;
    }
}