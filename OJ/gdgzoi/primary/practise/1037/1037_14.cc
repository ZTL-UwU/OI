#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

#include <dbg.h>

const int MAX_N = 1e4 + 10;

std::pair<int, int> input[MAX_N];
bool color_hash[MAX_N];
int col[MAX_N * 4];
int poster[MAX_N];
int top;

void update(int l, int r, int k, int tar_l, int tar_r, int color)
{
    dbg(l, r, tar_l, tar_r);

    if (tar_l <= l and r <= tar_r)
    {
        col[k] = color;
        return;
    }

    int ls = k * 2;
    int rs = k * 2 + 1;
    int mid = (l + r) / 2;

    if (col[k] != -1)
    {
        col[ls] = col[k];
        col[rs] = col[k];
        col[k] = -1;
    }

    if (l <= mid)
        update(l, mid, ls, tar_l, tar_r, color);
    if (r > mid)
        update(mid + 1, r, rs, tar_l, tar_r, color);
}

int ans = 0;
void query(int l, int r, int k)
{
    if (l == r)
    {
        if (not color_hash[col[k]])
        {
            ans++;
            color_hash[col[k]] = true;
        }

        return;
    }

    int ls = k * 2;
    int rs = k * 2 + 1;
    int mid = (l + r) / 2;

    query(l, mid, ls);
    query(mid + 1, r, rs);
}

int main()
{
    int t;
    std::cin >> t;

    while (t--)
    {
        std::memset(col, -1, sizeof(col));
        std::memset(color_hash, 0, sizeof(color_hash));

        int n;
        std::cin >> n;

        for (int i = 1; i <= n; i++)
        {
            int l, r;
            std::cin >> l >> r;

            input[i] = std::pair<int, int>(l, r);

            poster[++top] = l;
            poster[++top] = r;
        }

        std::sort(poster + 1, poster + top + 1);

        int pos_num = std::unique(poster + 1, poster + top + 1) - poster;
        int pos_num_tmp = pos_num;

        for (int i = 2; i <= pos_num_tmp; i++)
            if (poster[i] - poster[i - 1] > 1)
                poster[pos_num++] = poster[i] - 1;

        std::sort(poster + 1, poster + pos_num + 1);

        for (int i = 0; i < n; i++)
        {
            int l = std::lower_bound(poster + 1, poster + top + 1, input[i].first) - poster;
            int r = std::lower_bound(poster + 1, poster + top + 1, input[i].second) - poster;

            update(1, pos_num, 1, l, r, i);
        }

        ans = 0;
        query(1, pos_num, 1);
        std::cout << ans << "\n";
    }
    return 0;
}