#include <iostream>
#include <cstring>
#include <bitset>

const int MAX_DEPTH = 31;
const int MAX_N = 4e5 + 10;

int xor_sum[MAX_N];
int a[MAX_N];
int l[MAX_N];
int r[MAX_N];

namespace TRIE
{
    int node_cnt;
    int base[MAX_N * 40][2];

    void insert(int x)
    {
        std::bitset<MAX_DEPTH> bin(x);

        int u = 0;
        for (int i = MAX_DEPTH - 1; i >= 0; i--)
        {
            if (!base[u][bin[i]])
                base[u][bin[i]] = ++node_cnt;
            u = base[u][bin[i]];
        }
    }

    int query(int x)
    {
        std::bitset<MAX_DEPTH> bin(x);

        int u = 0;
        int res = 0;
        for (int i = MAX_DEPTH - 1; i >= 0; i--)
        {
            if (base[u][!bin[i]])
            {
                u = base[u][!bin[i]];
                res += 1 << i;
            }
            else
                u = base[u][bin[i]];
        }

        return res;
    }

    void reset()
    {
        node_cnt = 0;
        std::memset(base, 0, sizeof(base));
    }
}; // namespace TRIE

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        xor_sum[i] = xor_sum[i - 1] ^ a[i];
    }
    TRIE::insert(0);

    int max = -1;
    for (int i = 1; i <= n; i++)
    {
        max = std::max(max, TRIE::query(xor_sum[i]));
        l[i] = max;
        TRIE::insert(xor_sum[i]);
    }

    TRIE::reset();
    max = -1;
    for (int i = n; i >= 1; i--)
    {
        max = std::max(max, TRIE::query(xor_sum[i]));
        r[i] = max;
        TRIE::insert(xor_sum[i]);
    }

    int ans = -1;
    for (int i = 1; i <= n - 1; i++)
        ans = std::max(ans, l[i] + r[i + 1]);
    std::cout << ans;
    return 0;
}