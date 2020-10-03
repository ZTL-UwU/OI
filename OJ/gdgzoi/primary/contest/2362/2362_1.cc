#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

const int MAXN = 1e4 + 10;
std::vector<int> ans;
bool vis[MAXN];
int n;
int max_time = -100;

inline void dfs(int time, int now);
inline void play(int time, int now, int type);

inline void play(int time, int now, int type)
{
    int next;
    if (type == 1)
        next = (now * 2) % n;
    else
        next = (now * 2 + 1) % n;

    if (!vis[next] || (time == n - 1 && next == 0))
    {
        vis[next] = true;
        ans.push_back(next);

        dfs(time + 1, next);

        ans.pop_back();
        vis[next] = false;
    }
}

inline void dfs(int time, int now)
{
    if (time > max_time)
    {
        printf("%d\n", time);
        max_time = time;
    }
    if (time == n && now == 0)
    {
        for (auto i : ans)
            printf("%d ", i);
        exit(0);
    }

    if ((now * 2) % n > (now * 2 + 1) % n)
    {
        play(time, now, 1);
        play(time, now, 2);
    }
    else
    {
        play(time, now, 2);
        play(time, now, 1);
    }
}

int main()
{
    scanf("%d", &n);
    if (n % 2 == 1)
    {
        puts("-1");
        return 0;
    }
    vis[0] = true;
    ans.push_back(0);
    dfs(0, 0);
    return 0;
}