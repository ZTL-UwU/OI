#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

const int MAX_N = 2e4;

std::vector<int> g[MAX_N];

std::stack<int> st;
int time_stamp;
int dfn[MAX_N];
int low[MAX_N];

int scc_size[MAX_N];
int scc[MAX_N];
int scc_num;

int outdegree[MAX_N];

inline void tarjan(int u)
{
    time_stamp++;
    dfn[u] = time_stamp;
    low[u] = time_stamp;
    st.push(u);

    for (auto v : g[u])
    {
        if (not dfn[v])
        {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if (not scc[v])
            low[u] = std::min(low[u], dfn[v]);
    }

    if (low[u] == dfn[u])
    {
        scc_num++;

        int v = 0;
        do
        {
            v = st.top();
            st.pop();

            scc[v] = scc_num;
            scc_size[scc_num]++;
        } while (u != v);
    }
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
    }

    for (int i = 1; i <= n; i++)
        if (not dfn[i])
            tarjan(i);

    for (int u = 1; u <= n; u++)
    {
        for (auto v : g[u])
        {
            if (scc[u] != scc[v])
                outdegree[scc[u]]++;
        }
    }

    int ans = 0;
    int no_out_num = 0;
    for (int i = 1; i <= scc_num; i++)
    {
        if (outdegree[i] == 0)
        {
            ans = scc_size[i];
            no_out_num++;
        }
    }

    if (no_out_num == 1)
        std::cout << ans;
    else
        std::cout << 0;
    return 0;
}
