#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <map>

const int INF = 0x7fffffff;
const int MAXN = 1e5 + 10;
std::vector<int> bucket[MAXN]; // id -> {val, ...}
std::map<int, int> mp;         // Map for discretization
int mode[1000][1000];          // Mode number between block[i] & block[j]
int mapping[MAXN];             // val -> id
int block[MAXN];               // Block outline
int value[MAXN];               // id -> val
int block_size;                // One block's size
int cnt[MAXN];                 // Counter for prework
int id;                        // id after discretization
int n;

inline void pre_work(int x)
{
    std::memset(cnt, 0, sizeof(cnt));
    int max = -INF;
    int res = 0;
    for (int i = (x - 1) * block_size + 1; i <= n; i++)
    {
        int tmp_id = mapping[i];
        cnt[tmp_id]++;
        int to = block[i];

        if (cnt[tmp_id] > max || (cnt[tmp_id] == max && value[tmp_id] < value[res]))
        {
            max = cnt[tmp_id];
            res = tmp_id;
        }
        mode[x][to] = res;
    }
}

inline int appeared(int l, int r, int x)
{
    int res = std::upper_bound(bucket[x].begin(), bucket[x].end(), r) -
              std::lower_bound(bucket[x].begin(), bucket[x].end(), l);
    return res;
}

inline int query(int l, int r)
{
    int ans = mode[block[l] + 1][block[r] - 1];
    int max = appeared(l, r, ans);

    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
    {
        int times = appeared(l, r, mapping[i]);
        if (times > max || (times == max && value[mapping[i]] < value[ans]))
        {
            max = times;
            ans = mapping[i];
        }
    }

    if (block[l] != block[r])
    {
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
        {
            int times = appeared(l, r, mapping[i]);
            if (times > max || (times == max && value[mapping[i]] < value[ans]))
            {
                max = times;
                ans = mapping[i];
            }
        }
    }

    return value[ans];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int q;
    std::cin >> n >> q;
    block_size = std::sqrt(n);

    // Discretization
    for (int i = 1; i <= n; i++)
    {
        int val;
        std::cin >> val;
        if (mp[val] == 0)
        {
            mp[val] = ++id;
            value[id] = val;
        }

        mapping[i] = mp[val];
        bucket[mapping[i]].push_back(i);
    }

    for (int i = 1; i <= n; i++)
        block[i] = (i - 1) / block_size + 1;
    for (int i = 1; i <= block[n]; i++)
        pre_work(i);

    int x = 0;
    for (int i = 0; i < q; i++)
    {
        int l, r;
        std::cin >> l >> r;
        l = (l + x - 1) % n + 1;
        r = (r + x - 1) % n + 1;
        if (l > r)
            std::swap(l, r);

        x = query(l, r);
        std::cout << x << "\n";
    }
    return 0;
}