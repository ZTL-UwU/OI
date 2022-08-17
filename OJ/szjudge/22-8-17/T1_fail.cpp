
    // std::vector<int> res;

    // while (!q.empty())
    // {
    //     pqg next;

    //     const int top = q.top();
    //     const int f = fa[top];
    //     std::cout << top  << " " << f << " " << g[f].size() << "\n";

    //     res.push_back(top);
    //     for (auto v : g[f])
    //         next.push(v);

    //     q = next;
    // }

    // return res;

    // std::vector<int> res;

    // while (!q.empty())
    // {
    //     int u = q.top();
    //     q.pop();

    //     std::cout << u << " ";

    //     inque[u] = false;
    //     if (vis[u])
    //         return {-1};
    //     vis[u] = true;
    //     res.push_back(u);

    //     std::sort(g[u].begin(), g[u].end());
    //     for (auto v : g[u])
    //     {
    //         if (!inque[v])
    //         {
    //             q.push(v);
    //             inque[v] = true;
    //         }
    //     }
    // }

    // return res;