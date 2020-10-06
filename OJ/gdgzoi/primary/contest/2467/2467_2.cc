#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>

const int INF = 0x7fffffff;
const int MAX_BLOCK_NUM = 2e4;
const int MAXN = 1e6;
const int ADD_OP = 1;
const int DIV_OP = 2;
const int MIN_OP = 3;
const int SUM_OP = 4;

std::priority_queue<int, std::vector<int>, std::greater<int>> ordered_value[MAX_BLOCK_NUM];
int add_tag[MAX_BLOCK_NUM];
int div_tag[MAX_BLOCK_NUM];
int sum[MAX_BLOCK_NUM];
int value[MAXN];
int block[MAXN];
int block_size;
int n;

inline void commit_tag(int bl)
{
    for (int i = (bl - 1) * block_size + 1; i <= std::min(n, bl * block_size); i++)
        value[i] = value[i] / div_tag[block[i]] + add_tag[block[i]];

    add_tag[bl] = 0;
    div_tag[bl] = 1;
}

inline void commit_ordered_value(int bl)
{
    while (!ordered_value[bl].empty())
        ordered_value[bl].pop();

    for (int i = (bl - 1) * block_size + 1; i <= bl * block_size; i++)
        ordered_value[bl].push(value[i]);
}

inline void do_remaining(int i, int op, int val)
{
    int before = value[i];
    if (op == ADD_OP)
        value[i] += val;
    else
        value[i] /= val;

    sum[block[i]] += value[i] - before;
}

inline void update(int l, int r, int op, int val)
{
    commit_tag(block[l]);
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
        do_remaining(i, op, val);
    commit_ordered_value(block[l]);

    if (block[l] != block[r])
    {
        commit_tag(block[r]);
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
            do_remaining(i, op, val);
        commit_ordered_value(block[r]);
    }

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
    {
        if (op == ADD_OP)
            add_tag[i] += val;
        else
        {
            add_tag[i] /= val;
            div_tag[i] *= val;
            if (div_tag[i] == 0)
                div_tag[i] = 1;
        }
    }
}

inline int query_sum(int l, int r)
{
    int res = 0;

    commit_tag(block[l]);
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
        res += value[i];

    if (block[l] != block[r])
    {
        commit_tag(block[r]);
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
            res += value[i];
    }

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
        res += sum[i] / div_tag[i] + add_tag[i] * block_size;

    return res;
}

inline int query_min(int l, int r)
{
    int res = INF;

    commit_tag(block[l]);
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
        res = std::min(res, value[i]);

    if (block[l] != block[r])
    {
        commit_tag(block[r]);
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
            res = std::min(res, value[i]);
    }

    for (int i = block[l] + 1; i <= block[r] - 1; i++)
        res = std::min(res, ordered_value[i].top());

    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int q;
    std::cin >> n >> q;

    block_size = std::sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        std::cin >> value[i];
        block[i] = (i - 1) / block_size + 1;
        sum[block[i]] += value[i];
        ordered_value[block[i]].push(value[i]);
        div_tag[block[i]] = 1;
    }

    while (q--)
    {
        int op;
        std::cin >> op;

        if (op == ADD_OP)
        {
            int l, r, val;
            std::cin >> l >> r >> val;
            l++;
            r++;
            update(l, r, ADD_OP, val);
        }
        if (op == DIV_OP)
        {
            int l, r, val;
            std::cin >> l >> r >> val;
            l++;
            r++;
            update(l, r, DIV_OP, val);
        }
        if (op == MIN_OP)
        {
            int l, r;
            std::cin >> l >> r;
            l++;
            r++;
            std::cout << query_min(l, r) << "\n";
        }
        if (op == SUM_OP)
        {
            int l, r;
            std::cin >> l >> r;
            l++;
            r++;
            std::cout << query_sum(l, r) << "\n";
        }
    }
    return 0;
}