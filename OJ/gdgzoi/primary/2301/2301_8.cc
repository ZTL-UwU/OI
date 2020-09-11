#include <iostream>
#include <stdio.h>
#include <math.h>

const int MAXN = 1e5;
long long value[MAXN];
long long tag[MAXN];
long long sum[MAXN];
int block[MAXN];
int block_size;

inline void add(int l, int r, int val)
{
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
    {
        value[i] += val;
        sum[block[l]] += val;
    }

    if (block[l] != block[r])
    {
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
        {
            value[i] += val;
            sum[block[r]] += val;
        }
    }

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
        tag[i] += val;
}

inline long long query(int l, int r)
{
    long long res = 0;

    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
        res += value[i] + tag[block[l]];

    if (block[l] != block[r])
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
            res += value[i] + tag[block[r]];

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
        res += sum[i] + tag[i] * block_size;

    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    block_size = sqrt(n);

    for (int i = 1; i <= n; i++)
        std::cin >> value[i];
    for (int i = 1; i <= n; i++)
    {
        block[i] = (i - 1) / block_size + 1;
        sum[block[i]] += value[i];
    }

    for (int i = 1; i <= n; i++)
    {
        int op, l, r, val;
        std::cin >> op >> l >> r >> val;
        if (op == 0)
            add(l, r, val);
        else
            std::cout << query(l, r) % (val + 1) << "\n";
    }

    return 0;
}