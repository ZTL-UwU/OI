#include <iostream>
#include <stdio.h>
#include <math.h>

const int MAXN = 1e5;
bool flag[MAXN];
int value[MAXN];
int block[MAXN];
int block_size;
int tag[MAXN];
int sum[MAXN];

inline void solve(int x)
{
    if (flag[x])
        return;
    flag[x] = true;
    sum[x] = 0;

    for (int i = (x - 1) * block_size + 1; i <= x * block_size; i++)
    {
        value[i] = sqrt(value[i]);
        sum[x] += value[i];
        if (value[i] > 1)
            flag[x] = false;
    }
}

inline void update(int l, int r)
{
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
    {
        sum[block[l]] -= value[i];
        value[i] = sqrt(value[i]);
        sum[block[l]] += value[i];
    }

    if (block[l] != block[r])
    {
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
        {
            sum[block[r]] -= value[i];
            value[i] = sqrt(value[i]);
            sum[block[r]] += value[i];
        }
    }

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
        solve(i);
}

inline int query(int l, int r)
{
    int res = 0;

    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
        res += value[i];

    if (block[l] != block[r])
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
            res += value[i];

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
        res += sum[i];

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
            update(l, r);
        else
            std::cout << query(l, r) << "\n";
    }

    return 0;
}