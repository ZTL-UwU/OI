#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

const int MAX_N = 2e5 + 10;

std::vector<int> g[MAX_N];
std::queue<int> leaf;

long long money[MAX_N];
long long size1[MAX_N];
long long size2[MAX_N];
long long tag[MAX_N];
int fa[MAX_N];

void get_size(int u)
{
    size1[u] = 1;
    for (auto v : g[u])
    {
        get_size(v);
        size1[u] += size1[v];
    }

    if (g[u].size() == 0)
        leaf.push(u);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    for (int i = 2; i <= n; i++)
    {
        std::cin >> fa[i];
        g[fa[i]].push_back(i);
        tag[i] = 1;
    }

    get_size(1);
    std::memcpy(size2, size1, sizeof(size1));

    while (!leaf.empty())
    {
        const int u = leaf.front();
        leaf.pop();

        money[u]++;
        if (u == 1)
            break;
        money[fa[u]] += money[u] + size2[u];
        size1[fa[u]] -= tag[u];
        tag[fa[u]] += tag[u];

        if (size1[fa[u]] == 1)
            leaf.push(fa[u]);
    }

    for (int i = 1; i <= n; i++)
        std::cout << money[i] << " ";
    return 0;
}