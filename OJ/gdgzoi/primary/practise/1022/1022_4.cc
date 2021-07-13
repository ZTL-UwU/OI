#include <iostream>
#include <queue>

const int MAX_N = 1e7;
bool vis[MAX_N * 2 + 10];

int bfs(int start, int end)
{
    std::queue<std::pair<int, int>> q;
    q.push({start, 0});
    vis[MAX_N + start] = true;

    while (!q.empty())
    {
        int u = q.front().first;
        int step = q.front().second;
        q.pop();
        if (u == end)
            return step;

        if (u + 1 < MAX_N && !vis[MAX_N + u + 1])
        {
            vis[MAX_N + u + 1] = true;
            q.push({u + 1, step + 1});
        }

        if (u - 1 > -MAX_N && !vis[MAX_N + u - 1])
        {
            vis[MAX_N + u - 1] = true;
            q.push({u - 1, step + 1});
        }

        if (u * 2 > -MAX_N && u * 2 < MAX_N && !vis[MAX_N + u * 2])
        {
            vis[MAX_N + u * 2] = true;
            q.push({u * 2, step + 1});
        }
    }

    return -1;
}

int main()
{
    int n, k;
    std::cin >> n >> k;

    std::cout << bfs(n, k);
    return 0;
}
