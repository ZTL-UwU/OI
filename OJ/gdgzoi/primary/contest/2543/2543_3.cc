#include <iostream>
#include <cmath>

const int MAX_N = 1e5 + 10;

long long val[MAX_N];
long long sum[MAX_N];
bool done[MAX_N];
int chunk[MAX_N];
int chunk_size;

void solve_part(int i, int k)
{
    sum[chunk[k]] -= val[i];
    val[i] = std::sqrt(val[i]);
    sum[chunk[k]] += val[i];
}

void solve_chunk(int c)
{
    if (done[c])
        return;
    done[c] = true;
    sum[c] = 0;

    for (int i = (c - 1) * chunk_size + 1; i <= c * chunk_size; i++)
    {
        val[i] = std::sqrt(val[i]);
        sum[c] += val[i];

        if (val[i] > 1)
            done[c] = false;
    }
}

void update(int l, int r)
{
    for (int i = l; i <= std::min(chunk[l] * chunk_size, r); i++)
        solve_part(i, l);

    if (chunk[l] != chunk[r])
        for (int i = (chunk[r] - 1) * chunk_size + 1; i <= r; i++)
            solve_part(i, r);

    for (int i = chunk[l] + 1; i <= chunk[r] - 1; i++)
        solve_chunk(i);
}

long long query(int l, int r)
{
    long long res = 0;

    for (int i = l; i <= std::min(chunk[l] * chunk_size, r); i++)
        res += val[i];

    if (chunk[l] != chunk[r])
        for (int i = (chunk[r] - 1) * chunk_size + 1; i <= r; i++)
            res += val[i];

    for (int i = chunk[l] + 1; i <= chunk[r] - 1; i++)
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
    chunk_size = std::sqrt(n);
    for (int i = 1; i <= n; i++)
        std::cin >> val[i];
    for (int i = 1; i <= n; i++)
    {
        chunk[i] = (i - 1) / chunk_size + 1;
        sum[chunk[i]] += val[i];
    }

    int q;
    std::cin >> q;
    for (int _i = 0; _i < q; _i++)
    {
        int op, l, r;
        std::cin >> op >> l >> r;
        if (l > r)
            std::swap(l, r);

        if (op == 0)
            update(l, r);
        else
            std::cout << query(l, r) << "\n";
    }

    return 0;
}
