#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

const int MAXN = 1e6 + 10;
const int MOD = 10007;
long long value[MAXN];
int mult_tag[MAXN];
int add_tag[MAXN];
int block[MAXN];
int block_size;

inline void commit(int x)
{
    for (int i = (x - 1) * block_size + 1; i <= x * block_size; i++)
    {
        value[i] = value[i] * mult_tag[block[i]] + add_tag[block[i]];
        value[i] %= MOD;
    }

    add_tag[x] = 0;
    mult_tag[x] = 1;
}

inline void update(int op, int l, int r, int val)
{
    commit(block[l]);
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
    {
        if (op == 0)
            value[i] += val;
        else
            value[i] *= val;

        value[i] %= MOD;
    }

    if (block[l] != block[r])
    {
        commit(block[r]);
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
        {
            if (op == 0)
                value[i] += val;
            else
                value[i] *= val;

            value[i] %= MOD;
        }
    }

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
    {
        if (op == 0)
            add_tag[i] = (add_tag[i] + val) % MOD;
        else
        {
            add_tag[i] = (add_tag[i] * val) % MOD;
            mult_tag[i] = (mult_tag[i] * val) % MOD;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    block_size = std::sqrt(n);

    for (int i = 1; i <= n; i++)
        std::cin >> value[i];
    for (int i = 1; i <= n; i++)
        block[i] = (i - 1) / block_size + 1;
    for (int i = 1; i <= n; i++)
        mult_tag[i] = 1;

    for (int i = 0; i < n; i++)
    {
        int op, l, r, val;
        std::cin >> op >> l >> r >> val;

        if (op != 2)
            update(op, l, r, val);
        else
            std::cout << (value[r] * mult_tag[block[r]] + add_tag[block[r]]) % MOD << "\n";
    }
    return 0;
}