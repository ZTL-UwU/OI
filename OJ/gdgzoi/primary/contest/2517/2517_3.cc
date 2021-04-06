#include <cstddef>
#include <iostream>
#include <cstring>
#include <vector>

const int MAX_N = 2e5 + 10;
const int MAX_TREE_N = MAX_N * 4;

int middle_max[MAX_TREE_N];
int right_max[MAX_TREE_N];
int left_max[MAX_TREE_N];
int tag[MAX_TREE_N];

void commit(int l, int r, int k, int val)
{
    tag[k] = val;
    left_max[k] = val == 1 ? 0 : r - l + 1;
    right_max[k] = val == 1 ? 0 : r - l + 1;
    middle_max[k] = val == 1 ? 0 : r - l + 1;
}

const std::vector<int> upload(int l, int r, const std::vector<int> &ls_v, const std::vector<int> &rs_v)
{
    std::vector<int> res;
    res.resize(3);

    int mid = (l + r) / 2;

    if (ls_v[2] == mid - l + 1)
        res[0] = ls_v[2] + rs_v[0];
    else
        res[0] = ls_v[0];

    if (rs_v[2] == r - mid)
        res[1] = rs_v[2] + ls_v[1];
    else
        res[1] = rs_v[1];

    res[2] = ls_v[1] + rs_v[0];

    return res;
}

void push_down(int l, int r, int k)
{
    if (tag[k] != 3)
    {
        int ls = k * 2;
        int rs = k * 2 + 1;
        int mid = (l + r) / 2;

        commit(l, mid, ls, tag[k]);
        commit(mid + 1, r, rs, tag[k]);

        tag[k] = 3;
    }
}

void update(int l, int r, int l_tar, int r_tar, int k, int val)
{
    if (l_tar <= l && r <= r_tar)
    {
        commit(l, r, k, val);
        return;
    }

    int ls = k * 2;
    int rs = k * 2 + 1;
    int mid = (l + r) / 2;

    push_down(l, r, k);
    if (l_tar <= mid)
        update(l, mid, l_tar, r_tar, ls, val);
    if (r_tar > mid)
        update(mid + 1, r, l_tar, r_tar, rs, val);

    auto upload_res =
        upload(l, r, {left_max[ls], right_max[ls], middle_max[ls]}, {left_max[rs], right_max[rs], middle_max[rs]});
    left_max[k] = upload_res[0];
    right_max[k] = upload_res[1];
    middle_max[k] = upload_res[2];
}

std::vector<int> query(int l, int r, int l_tar, int r_tar, int k)
{
    if (l_tar <= l && r <= r_tar)
        return {left_max[k], right_max[k], middle_max[k]};

    int ls = k * 2;
    int rs = k * 2 + 1;
    int mid = (l + r / 2);

    push_down(l, r, k);

    std::vector<int> ls_res;
    std::vector<int> rs_res;
    if (l_tar <= mid)
        ls_res = query(l, mid, l_tar, r_tar, ls);
    if (r_tar > mid)
        rs_res = query(mid + 1, r, l_tar, r_tar, rs);

    auto upload_res = upload(l, r, ls_res, rs_res);
    return upload_res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, q;
    std::cin >> n >> q;

    std::memset(left_max, 0, sizeof(left_max));
    std::memset(right_max, 0, sizeof(right_max));
    std::memset(middle_max, 0, sizeof(middle_max));
    for (int _i = 0; _i < q; _i++)
    {
        int op;
        std::cin >> op;

        if (op == 0)
        {
            int l, r;
            std::cin >> l >> r;

            update(1, n, l, r, 1, 0);
        }
        else if (op == 1)
        {
            int l1, r1, l2, r2;
            std::cin >> l1 >> r1 >> l2 >> r2;

            int avaliable = 0;
            for (int i = n + l1; i < n + r2; i++)
                if (middle_max[i] == 0)
                    avaliable++;
            update(1, n, l1, r1, 1, 0);

            update(1, n, l2, std::min(l1 + avaliable, r2), 1, 1);
        }
        else if (op == 2)
        {
            int l, r;
            std::cin >> l >> r;

            auto q_res = query(1, n, l, r, 1);
            std::cout << std::max(std::max(q_res[0], q_res[1]), q_res[2]) << "\n";
        }
    }
    return 0;
}
