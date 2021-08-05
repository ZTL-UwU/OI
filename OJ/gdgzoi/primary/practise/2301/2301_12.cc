#include <iostream>
#include <cmath>

const int MAXN = 1e5 + 10;
int value[MAXN];
int block[MAXN];
int block_size;
int tag[MAXN];
int n;

inline void commit(int k)
{
    if (tag[k] == -1)
        return;
    for (int i = (k - 1) * block_size + 1; i <= std::min(k * block_size, n); i++)
        value[i] = tag[k];
    tag[k] = -1;
}

inline int query(int l, int r, int val)
{
    int ans = 0;
    commit(block[l]);
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
    {
        if (value[i] == val)
            ans++;
        value[i] = val;
    }

    if (block[l] != block[r])
    {
        commit(block[r]);
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
        {
            if (value[i] == val)
                ans++;
            value[i] = val;
        }
    }

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
    {
        if (tag[i] != -1)
        {
            if (tag[i] != val)
                tag[i] = val;
            else
                ans += block_size;
        }
        else
        {
            for (int j = (i - 1) * block_size + 1; j <= std::min(i * block_size, n); j++)
            {
                if (value[j] == val)
                    ans++;
                value[j] = val;
            }
            tag[i] = val;
        }
    }
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;
    block_size = std::sqrt(n);
    for (int i = 1; i <= n; i++)
        std::cin >> value[i];
    for (int i = 1; i <= n; i++)
    {
        block[i] = (i - 1) / block_size + 1;
        tag[block[i]] = -1;
    }

    for (int i = 1; i <= n; i++)
    {
        int l, r, val;
        std::cin >> l >> r >> val;
        std::cout << query(l, r, val) << "\n";
    }
    return 0;
}