#include <iostream>
#include <cstdio>

const int INF = 0x7fffffff;
const int MAX_N = 1e5 + 10;
const int MAX_LOG = 21;

long long st_a_min[MAX_N][MAX_LOG];
long long st_a_min_pos[MAX_N][MAX_LOG];
long long st_a_max[MAX_N][MAX_LOG];
long long st_a_max_neg[MAX_N][MAX_LOG];
long long st_b_min[MAX_N][MAX_LOG];
long long st_b_max[MAX_N][MAX_LOG];

int log[MAX_N];
int a[MAX_N];
int b[MAX_N];

long long a_min(int l, int r)
{
    if (l == r)
        return a[l];
    return std::min(st_a_min[l][log[r - l]], st_a_min[r - (1 << log[r - l]) + 1][log[r - l]]);
}

long long a_max(int l, int r)
{
    if (l == r)
        return a[l];
    return std::max(st_a_max[l][log[r - l]], st_a_max[r - (1 << log[r - l]) + 1][log[r - l]]);
}

long long a_min_pos(int l, int r)
{
    if (l == r)
        return a[l];
    return std::min(st_a_min_pos[l][log[r - l]], st_a_min_pos[r - (1 << log[r - l]) + 1][log[r - l]]);
}

long long a_max_neg(int l, int r)
{
    if (l == r)
        return a[l];
    return std::max(st_a_max_neg[l][log[r - l]], st_a_max_neg[r - (1 << log[r - l]) + 1][log[r - l]]);
}

long long b_min(int l, int r)
{
    if (l == r)
        return b[l];
    return std::min(st_b_min[l][log[r - l]], st_b_min[r - (1 << log[r - l]) + 1][log[r - l]]);
}

long long b_max(int l, int r)
{
    if (l == r)
        return b[l];
    return std::max(st_b_max[l][log[r - l]], st_b_max[r - (1 << log[r - l]) + 1][log[r - l]]);
}

int main()
{
    std::freopen("game.in", "r", stdin);
    std::freopen("game.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;

    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
        st_a_min[i][0] = a[i];
        st_a_max[i][0] = a[i];
        st_a_min_pos[i][0] = a[i] >= 0 ? a[i] : INF;
        st_a_max[i][0] = a[i];
        st_a_max_neg[i][0] = a[i] >= 0 ? -INF : a[i];
    }

    for (int i = 0; i < m; i++)
    {
        std::cin >> b[i];
        st_b_min[i][0] = b[i];
        st_b_max[i][0] = b[i];
    }

    log[0] = -1;
    for (int i = 1; i < MAX_N; i++)
        log[i] = log[i / 2] + 1;

    for (int i = 1; i < MAX_LOG; i++)
        for (int j = 0; j <= n - (1 << i); j++)
            st_a_min[j][i] = std::min(st_a_min[j][i - 1], st_a_min[j + (1 << (i - 1))][i - 1]);

    for (int i = 1; i < MAX_LOG; i++)
        for (int j = 0; j <= n - (1 << i); j++)
            st_a_max[j][i] = std::max(st_a_max[j][i - 1], st_a_max[j + (1 << (i - 1))][i - 1]);

    for (int i = 1; i < MAX_LOG; i++)
        for (int j = 0; j <= n - (1 << i); j++)
            st_a_min_pos[j][i] = std::min(st_a_min_pos[j][i - 1], st_a_min_pos[j + (1 << (i - 1))][i - 1]);

    for (int i = 1; i < MAX_LOG; i++)
        for (int j = 0; j <= n - (1 << i); j++)
            st_a_max_neg[j][i] = std::max(st_a_max_neg[j][i - 1], st_a_max_neg[j + (1 << (i - 1))][i - 1]);

    for (int i = 1; i < MAX_LOG; i++)
        for (int j = 0; j <= n - (1 << i); j++)
            st_b_min[j][i] = std::min(st_b_min[j][i - 1], st_b_min[j + (1 << (i - 1))][i - 1]);

    for (int i = 1; i < MAX_LOG; i++)
        for (int j = 0; j <= n - (1 << i); j++)
            st_b_max[j][i] = std::max(st_b_max[j][i - 1], st_b_max[j + (1 << (i - 1))][i - 1]);

    for (int i = 0; i < q; i++)
    {
        int l1, r1, l2, r2;
        std::cin >> l1 >> r1 >> l2 >> r2;
        l1--;
        r1--;
        l2--;
        r2--;

        const long long amin = a_min(l1, r1);
        const long long amax = a_max(l1, r1);
        const long long aminpos = a_min_pos(l1, r1);
        const long long amaxneg = a_max_neg(l1, r1);
        const long long bmin = b_min(l2, r2);
        const long long bmax = b_max(l2, r2);

        if (amin >= 0 && bmin >= 0) //++ ++
            std::cout << amax * bmin;
        else if (amin >= 0 && bmin < 0) //++ +- & ++ --
            std::cout << amin * bmin;
        else if (amin < 0 && amax >= 0 && bmin >= 0) // +- ++
            std::cout << amax * bmin;
        else if (amin < 0 && amax >= 0 && bmax < 0) // +- --
            std::cout << amin * bmax;
        else if (amin < 0 && amax >= 0 && bmin < 0 && bmax >= 0) // +- +-
            std::cout << std::max(amaxneg * bmax, aminpos * bmin);
        else if (amax < 0 && bmin >= 0) // -- ++
            std::cout << amax * bmax;
        else if (amax < 0 && bmin < 0 && bmax >= 0) // -- +-
            std::cout << amax * bmax;
        else if (amax < 0 && bmax < 0) // -- --
            std::cout << amin * bmax;
        std::cout << "\n";
    }
    return 0;
}
