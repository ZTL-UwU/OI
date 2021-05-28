#include <cstddef>
#include <iostream>
#include <vector>
#include <cmath>

const int MAXN = 2000010;
std::vector<int> v[6000];
int rmq[MAXN][22];

int main()
{
    int n, k, p;
    std::cin >> n >> k >> p;

    for (int i = 1; i <= n; i++)
    {
        int col, money;
        std::cin >> col >> money;

        v[col].push_back(i);
        rmq[i][0] = money;
    }

    const int tmp = std::log2(n);
    for (int i = 1; i < tmp; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            rmq[j][i] = std::min(rmq[j][i - 1], rmq[j + (1 << (i - 1))][i - 1]);

    long long int ans = 0;
    for (int i = 0; i < k; i++)
    {
        for (std::size_t j = 0; j < v[i].size() - 1; j++)
        {
            const int l = v[i][j];
            for (std::size_t x = j + 1; x < v[i].size(); x++)
            {
                const int r = v[i][x];
                const int kk = std::log2(r - l + 1);
                const int res = std::min(rmq[l][kk], rmq[r - (1 << kk) + 1][kk]);
                if (res <= p)
                {
                    ans += v[i].size() - x;
                    break;
                }
            }
        }
    }

    std::cout << ans;
    return 0;
}