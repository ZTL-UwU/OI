#include <cstddef>
#include <cstring>
#include <iostream>
#include <vector>
#include <stack>

const int MAX_N = 6e2;

std::vector<int> g[MAX_N];
std::stack<int> st;

int pbc_size[MAX_N];
int pbc[MAX_N];
int dfn[MAX_N];
int low[MAX_N];
int time_stamp;
int pbc_num;

inline void tarjan(int u, int fa)
{
    dfn[u] = ++time_stamp;
    low[u] = dfn[u];
    st.push(u);

    for (auto v : g[u])
    {
        if (v == fa)
            continue;

        if (dfn[v] == 0)
        {
            tarjan(v, u);
            low[u] = std::min(low[u], low[v]);

            if (low[v] >= dfn[u])
            {
                int p;
                do
                {
                    p = st.top();
                    st.pop();
                    pbc[p] = pbc_num;
                    pbc_size[pbc_num]++;
                } while (p != v);

                pbc_num++;
            }
        }
        else
            low[u] = std::min(low[u], dfn[v]);
    }
}

void init()
{
    for (int i = 0; i < MAX_N; i++)
        g[i].clear();
    while (not st.empty())
        st.pop();
    
    std::memset(pbc_size, 0, sizeof(pbc_size));
    std::memset(pbc, 0, sizeof(pbc));
    std::memset(dfn, 0, sizeof(dfn));
    std::memset(low, 0, sizeof(low));

    time_stamp = 0;
    pbc_num = 0;
}

int main()
{
    int m;
    std::cin >> m;

    int t = 1;
    while (m != 0)
    {
        init();

        int n = -1;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            std::cin >> u >> v;
            n = std::max(n, std::max(u, v));

            g[u].push_back(v);
            g[v].push_back(u);
        }

        for (int i = 1; i <= n; i++)
            if (dfn[i] == 0)
                tarjan(i, -1);

        long long int ways = 1;
        for (int i = 0; i < pbc_num; i++)
            ways *= pbc_size[i];

        std::cout << "Case " << t << ": " << pbc_num << " " << ways << "\n";
        t++;

        std::cin >> m;
    }
    return 0;
}