#include <iostream>
#include <cstdio>

const int MAX_N = 1e6 + 10;

int res[MAX_N];
int a[MAX_N];
int n, M;
int ans;

void dfs(int k, int last, const int lim)
{
    if (k == lim)
    {
        for (int i = 0; i < n; i++)
        {
            bool flag = true;
            for (int j = 0; j < lim - 1; j++)
            {
                if (a[i] == res[j])
                    flag = false;
            }

            if (flag)
            {
                ans++;
                break;
            }
        }

        return;
    }

    for (int i = last + 1; i < n; i++)
    {
        res[k] = a[i];
        dfs(k + 1, i, lim);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> M;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    for (int i = 1; i <= n; i++)
        dfs(0, -1, i);

    std::cout << ans % M;
    return 0;
}