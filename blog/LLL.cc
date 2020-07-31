int sum = 0; // 队列中元素的 dis 值总和

while (!q.empty())
{
    int u = q.front();
    sum -= dis[u];
    if (q.size() * dis[u] > sum)
    {
        q.push(u);
        sum += dis[u];
        continue;
    }
    q.pop();
    inque[u] = false;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i].v;
        int w = g[u][i].w;
        if (dis[u] + w < dis[v])
        {
            dis[v] = dis[u] + w;
            if (!inque[v])
            {
                inque[v] = true;
                q.push(v);
                sum += dis[v];
            }
        }
    }
}