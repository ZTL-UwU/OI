#include <iostream>
#include <cmath>

using ll = long long;

const int INF = 0x7fffffff;
const int MAX_N = 1e5 + 10;
const int MAX_LOG = 50;

ll v[MAX_N][MAX_LOG];
ll w[MAX_N];

ll sum[MAX_N][MAX_LOG];
ll min[MAX_N][MAX_LOG];

int main()
{
    ll n, k;
    std::cin >> n >> k;

    for (int i = 0; i < n; i++)
        std::cin >> v[i][0];

    for (int i = 0; i < n; i++)
    {
        std::cin >> w[i];
        min[i][0] = w[i];
        sum[i][0] = w[i];
    }

    for (int i = 1; i <= std::log2(k) + 1; i++)
    {
        for (int u = 0; u < n; u++)
        {
            v[u][i] = v[v[u][i - 1]][i - 1];
            sum[u][i] = sum[u][i - 1] + sum[v[u][i - 1]][i - 1];
            min[u][i] = std::min(min[u][i - 1], min[v[u][i - 1]][i - 1]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (v[i][0] == i)
        {
            std::cout << k * w[i] << " " << w[i] << "\n";
            continue;
        }

        ll tmp_k = k;
        int u = i;
        ll ans_min = INF;
        ll ans_sum = 0;

        while (tmp_k > 0)
        {
            ans_sum += sum[u][(ll)std::log2(tmp_k)];
            ans_min = std::min(ans_min, min[u][(ll)std::log2(tmp_k)]);
            u = v[u][(ll)std::log2(tmp_k)];
            tmp_k -= std::pow(2, (ll)std::log2(tmp_k));
        }

        std::cout << ans_sum << " " << ans_min << "\n";
    }
}