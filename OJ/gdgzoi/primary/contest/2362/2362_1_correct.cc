#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>

const int MAXN = 1e4 + 10;
std::stack<int> ans;
bool vis[MAXN];
int n;

inline void dfs(int now)
{
    if (!vis[now * 2 + 1])
    {
        vis[now * 2 + 1] = true;
        dfs((now * 2 + 1) % (n / 2));
        ans.push(now * 2 + 1);
    }

    if (!vis[now * 2])
    {
        vis[now * 2] = true;
        dfs((now * 2) % (n / 2));
        ans.push(now * 2);
    }
}

int main()
{
    std::cin >> n;

    if (n % 2 == 1)
    {
        std::cout << "-1";
        return 0;
    }

    dfs(0);

    std::cout << "0 ";
    while (!ans.empty())
    {
        std::cout << ans.top() << " ";
        ans.pop();
    }
    return 0;
}