#include <iostream>
#include <climits>
#include <cmath>

const int MAX_N = 1e5 + 10;
const int INF = INT_MAX;

int value[MAX_N];
int n, q;

namespace st
{
    const int ST_MAX_N = MAX_N * 4;

    long long sum[ST_MAX_N];
    int max[ST_MAX_N];
    int min[ST_MAX_N];
    int tag[ST_MAX_N];

    void push_up(int k)
    {
        sum[k] = sum[k * 2] + sum[k * 2 + 1];
        max[k] = std::max(max[k * 2], max[k * 2 + 1]);
        min[k] = std::min(min[k * 2], min[k * 2 + 1]);
    }

    void commit(int k, int val, int l, int r)
    {
        tag[k] += val;
        max[k] += val;
        min[k] += val;
        sum[k] += (r - l + 1) * val;
    }

    void push_down(int k, int l, int r, int mid)
    {
        if (tag[k] != 0)
        {
            commit(k * 2, tag[k], l, mid);
            commit(k * 2 + 1, tag[k], mid + 1, r);
            tag[k] = 0;
        }
    }

    void build(int l = 0, int r = n - 1, int k = 1)
    {
        if (l == r)
        {
            sum[k] = value[l];
            max[k] = value[l];
            min[k] = value[l];
            return;
        }

        const auto mid = (l + r) / 2;
        build(l, mid, k * 2);
        build(mid + 1, r, k * 2 + 1);
        push_up(k);
    }

    void update_add(int l_tar, int r_tar, int val, int l = 0, int r = n - 1, int k = 1)
    {
        if (l_tar <= l && r <= r_tar)
        {
            commit(k, val, l, r);
            return;
        }

        const auto mid = (l + r) / 2;
        push_down(k, l, r, mid);
        if (l_tar <= mid)
            update_add(l_tar, r_tar, val, l, mid, k * 2);
        if (r_tar > mid)
            update_add(l_tar, r_tar, val, mid + 1, r, k * 2 + 1);
        push_up(k);
    }

    void update_div(int l_tar, int r_tar, int val, int l = 0, int r = n - 1, int k = 1)
    {
        if (l_tar <= l && r <= r_tar)
        {
            if (max[k] - std::floor(1.0 * max[k] / val) == min[k] - std::floor(1.0 * min[k] / val))
            {
                commit(k, std::floor(1.0 * max[k] / val) - max[k], l, r);
                return;
            }
        }

        const auto mid = (l + r) / 2;
        push_down(k, l, r, mid);
        if (l_tar <= mid)
            update_div(l_tar, r_tar, val, l, mid, k * 2);
        if (r_tar > mid)
            update_div(l_tar, r_tar, val, mid + 1, r, k * 2 + 1);
        push_up(k);
    }

    int query_min(int l_tar, int r_tar, int l = 0, int r = n - 1, int k = 1)
    {
        if (l_tar <= l && r <= r_tar)
            return min[k];

        const auto mid = (l + r) / 2;
        push_down(k, l, r, mid);
        int res = INF;
        if (l_tar <= mid)
            res = std::min(res, query_min(l_tar, r_tar, l, mid, k * 2));
        if (r_tar > mid)
            res = std::min(res, query_min(l_tar, r_tar, mid + 1, r, k * 2 + 1));
        return res;
    }

    long long query_sum(int l_tar, int r_tar, int l = 0, int r = n - 1, int k = 1)
    {
        if (l_tar <= l && r <= r_tar)
            return sum[k];

        const auto mid = (l + r) / 2;
        push_down(k, l, r, mid);
        long long res = 0;
        if (l_tar <= mid)
            res += query_sum(l_tar, r_tar, l, mid, k * 2);
        if (r_tar > mid)
            res += query_sum(l_tar, r_tar, mid + 1, r, k * 2 + 1);
        return res;
    }
} // namespace st

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> q;

    for (int i = 0; i < n; i++)
        std::cin >> value[i];
    st::build();

    for (int _i = 0; _i < q; _i++)
    {
        short op;
        std::cin >> op;

        if (op == 1)
        {
            int l, r, c;
            std::cin >> l >> r >> c;
            st::update_add(l, r, c);
        }
        else if (op == 2)
        {
            int l, r, c;
            std::cin >> l >> r >> c;
            st::update_div(l, r, c);
        }
        else if (op == 3)
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << st::query_min(l, r) << "\n";
        }
        else if (op == 4)
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << st::query_sum(l, r) << "\n";
        }
    }
    return 0;
}
