#include <iostream>
#include <cstring>
#include <vector>

const int MAX_N = 1e5 + 10;
const int MAX_LOG = 22;

std::vector<std::pair<std::size_t, std::size_t>> chunk;
int rev_chunk[MAX_N];
int a[MAX_N];

namespace ST
{
    std::size_t base[MAX_N][MAX_LOG];
    int log[MAX_N];

    void init(std::vector<std::pair<std::size_t, std::size_t>> &v)
    {
        log[0] = -1;
        for (std::size_t i = 1; i < v.size() + 10; i++)
            log[i] = log[i / 2] + 1;

        for (std::size_t i = 0; i < v.size(); i++)
            base[i][0] = v[i].second - v[i].first + 1;

        for (int i = 1; i < MAX_LOG; i++)
            for (std::size_t j = 0; j + (1 << i) - 1 < v.size(); j++)
                base[j][i] = std::max(base[j][i - 1], base[j + (1 << (i - 1))][i - 1]);
    }

    std::size_t max(int l, int r)
    {
        int k = log[r - l + 1];
        return std::max(base[l][k], base[r - (1 << k) + 1][k]);
    }
}; // namespace ST

void clear()
{
    chunk.clear();
    std::memset(a, 0, sizeof(a));
    std::memset(ST::log, 0, sizeof(ST::log));
    std::memset(ST::base, 0, sizeof(ST::base));
    std::memset(rev_chunk, 0, sizeof(rev_chunk));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    while (true)
    {
        int n, q;
        std::cin >> n;
        if (n == 0)
            return 0;
        std::cin >> q;
        clear();

        for (int i = 0; i < n; i++)
            std::cin >> a[i];

        int last = 0;
        for (int i = 1; i < n; i++)
        {
            if (a[i] != a[i - 1])
            {
                chunk.push_back({last, i - 1});
                last = i;
            }
            rev_chunk[i] = chunk.size();
        }
        chunk.push_back({last, n - 1});

        ST::init(chunk);

        for (int _i = 0; _i < q; _i++)
        {
            int l, r;
            std::cin >> l >> r;
            if (l > r)
                std::swap(l, r);
            l--;
            r--;

            if (rev_chunk[l] == rev_chunk[r])
                std::cout << r - l + 1;
            else
            {
                if (rev_chunk[l] + 1 <= rev_chunk[r] - 1)
                    std::cout << std::max(
                        std::max(chunk[rev_chunk[l]].second - l + 1, r - chunk[rev_chunk[r]].first + 1),
                        ST::max(rev_chunk[l] + 1, rev_chunk[r] - 1));
                else
                    std::cout << std::max(chunk[rev_chunk[l]].second - l + 1, r - chunk[rev_chunk[r]].first + 1);
            }

            std::cout << "\n";
        }
    }

    return 0;
}
