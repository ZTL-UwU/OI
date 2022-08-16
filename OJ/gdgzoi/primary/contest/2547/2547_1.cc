#include <bits/c++config.h>
#include <unordered_map>
#include <iostream>
#include <vector>

const int MAX_N = 1e6 + 10;
const int MOD = 1e9 + 7;

long long sum_h[MAX_N];
long long sum_v[MAX_N];

std::vector<std::pair<int, long long>> input_x;
std::vector<std::pair<int, long long>> input_y;
std::unordered_map<int, long long> mult_x;
std::unordered_map<int, long long> mult_y;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    long long n, m, k;
    std::cin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
        sum_h[i] = (((((i - 1) * m) % MOD) * m) % MOD + ((1 + m) * m / 2) % MOD) % MOD;
    for (int i = 1; i <= m; i++)
        sum_v[i] = ((n * i) % MOD + ((((n - 1) * n) % MOD) * m / 2) % MOD) % MOD;

    for (int i = 0; i < k; i++)
    {
        char op;
        int x;
        long long y;
        std::cin >> op >> x >> y;

        if (op == 'R')
            input_x.push_back({x, y});
        else if (op == 'S')
            input_y.push_back({x, y});
    }

    for (std::size_t i = 0; i < input_x.size(); i++)
    {
        if (!mult_x[input_x[i].first])
            mult_x[input_x[i].first] = input_x[i].second;
        else
            mult_x[input_x[i].first] *= input_x[i].second;
        mult_x[input_x[i].first] %= MOD;
    }
    for (std::size_t i = 0; i < input_y.size(); i++)
    {
        if (!mult_y[input_y[i].first])
            mult_y[input_y[i].first] = input_y[i].second;
        else
            mult_y[input_y[i].first] *= input_y[i].second;
        mult_y[input_y[i].first] %= MOD;
    }

    std::vector<int> px;
    std::vector<int> py;
    for (int i = 0; i < MAX_N; i++)
    {
        if (mult_x.find(i) != mult_x.end())
            px.push_back(i);
        if (mult_y.find(i) != mult_y.end())
            py.push_back(i);
    }

    long long ans = ((((1 + n * m) % MOD) * ((n * m) % MOD)) % MOD / 2) % MOD;
    for (std::size_t i = 0; i < px.size(); i++)
    {
        ans = (ans + (((((((px[i] - 1) * m) % MOD) * m) % MOD + ((1 + m) * m / 2) % MOD) % MOD) * mult_x[px[i]]) % MOD
               - sum_h[px[i]] + MOD)
              % MOD;
    }
    for (std::size_t i = 0; i < py.size(); i++)
    {
        ans = (ans + ((((n * py[i]) % MOD + ((((n - 1) * n) % MOD) * m / 2) % MOD) % MOD) * mult_y[py[i]]) % MOD
               - sum_v[py[i]] + MOD)
              % MOD;
    }

    for (std::size_t i = 0; i < px.size(); i++)
    {
        for (std::size_t j = 0; j < py.size(); j++)
        {
            long long org_val = ((px[i] - 1) * m + py[j]) % MOD;
            long long old_delta =
                ((org_val * mult_x[px[i]]) % MOD - org_val + (org_val * mult_y[py[j]]) % MOD - org_val) % MOD;
            long long new_delta = ((org_val * ((mult_x[px[i]] * mult_y[py[j]]) % MOD)) % MOD - org_val) % MOD;

            ans = (ans + new_delta - old_delta + MOD) % MOD;
        }
    }

    std::cout << ans % MOD;
    return 0;
}