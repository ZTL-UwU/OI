#include <iostream>
#include <vector>
#include <cmath>

const int MAX_N = 1e5 + 10;

std::vector<int> ordered[MAX_N];
int chunk[MAX_N];
int val[MAX_N];
int sum[MAX_N];
int chunk_size;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, q;
    std::cin >> n >> q;
    chunk_size = std::sqrt(n);

    for (int i = 0; i < n; i++)
        std::cin >> val[i];
    for (int i = 1; i <= n; i++)
    {
        chunk[i] = (i - 1) / chunk_size + 1;
        sum[chunk[i]] += val[i];
        ordered[chunk[i]].push_back(val[i]);
    }

    for (int i = 0; i < q; i++)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int l, r, c;
            std::cin >> l >> r >> c;


        }
    }
    return 0;
}
