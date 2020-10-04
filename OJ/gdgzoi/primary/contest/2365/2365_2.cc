#include <algorithm>
#include <iostream>
#include <vector>

struct data
{
    int v;
    int w;
};

const int MAXN = 5e5;
std::vector<data> tree[MAXN];
int value[MAXN];
bool vis[MAXN];
int ans;
int last;
int sum;

inline void dfs(int u)
{
    if (!vis[u])
    {
        ans += sum * value[u];
        sum = 0;
    }
    vis[u] = true;

    for (auto v : tree[u])
    {
        sum += v.w;
        dfs(v.v);
        sum += v.w;
    }
}

int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> value[i];
    for (int i = 1; i <= n - 1; i++)
    {
        int val;
        std::cin >> val;
        tree[(i + 1) / 2].push_back((data){i + 1, val});
    }

    dfs(1);
    std::cout << ans;
    return 0;
}