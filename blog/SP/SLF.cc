deque<int> dq;
dq.push_back(1);
inque[1] = true;
while (!dq.empty())
{
    int u = dq.front();
    dq.pop_front();
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
                // 若 dis[dq.front()] > dis[v] 将 v 由队首插入，否则从队尾插入
                if (dq.empty() || dis[v] > dis[dq.front()])
                    dq.push_back(v);
                else
                    dq.push_front(v);
            }
        }
    }
}