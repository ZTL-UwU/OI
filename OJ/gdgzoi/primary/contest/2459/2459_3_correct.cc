#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <map>

struct node
{
    int state;
    int next;
};

const int MAXN = 50;
const int MAXS = 2e7;
std::map<int, int> id;
int strength[MAXN];
bool used[MAXS];
int bin[MAXN];
node g[MAXS];
int tot;
int ans;
int n;

inline void add(int now_strength, int state)
{
    tot++;
    g[tot].state = state;
    g[tot].next = id[now_strength];
    id[now_strength] = tot;
}

inline void dfs1(int time, int now_strength, int state)
{
    if (time >= n / 2 - 1)
    {
        if (now_strength >= 0)
            add(now_strength, state);
        return;
    }

    dfs1(time + 1, now_strength + strength[time], state + bin[time]); // Choose to group A
    dfs1(time + 1, now_strength - strength[time], state + bin[time]); // Choose to group B
    dfs1(time + 1, now_strength, state);                              // Choose nothing
}

inline void dfs2(int time, int now_strength, int state)
{
    for (int i = id[now_strength]; i != 0; i = g[i].next)
    {
        if (!used[g[i].state + state])
        {
            used[g[i].state + state] = true;
            ans++;
        }
    }

    if (time > n)
        return;

    dfs2(time + 1, now_strength + strength[time], state + bin[time]); // Choose to group A
    dfs2(time + 1, now_strength - strength[time], state + bin[time]); // Choose to group B
    dfs2(time + 1, now_strength, state);                              // Choose nothing
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> strength[i];

    bin[1] = 1;
    for (int i = 2; i <= n; i++)
        bin[i] = bin[i - 1] * 2;

    dfs1(1, 0, 0);
    dfs2(n / 2 - 1, 0, 0);

    std::cout << ans - 1;
    return 0;
}