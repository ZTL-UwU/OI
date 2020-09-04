#include <algorithm>
#include <iostream>

const int MAXN = 1e5 + 10;
int n;

struct data
{
    int l, r;

    bool operator<(const data x) const
    {
        return this->r < x.r;
    }
};

data points[MAXN];

namespace sit
{
    int tree[MAXN];

    int lowbit(int x)
    {
        return x & -x;
    }

    void update(int x, int val)
    {
        while (x < MAXN)
        {
            tree[x] += val;
            x += lowbit(x);
        }
    }

    int query(int x)
    {
        int ans = 0;
        while (x > 0)
        {
            ans += tree[x];
            x -= lowbit(x);
        }
        return ans;
    }
} // namespace sit

int main()
{
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int s, w;
        std::cin >> s >> w;
        points[i].l = (s - w < 0 ? 0 : s - w) + 4;
        points[i].r = s + w + 4;
    }
    std::sort(points, points + n);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int len = sit::query(points[i].r) - sit::query(points[i].l - 1);
        if (len > 0)
            continue;
        
        ans++;
        sit::update(points[i].r, 1);
    }

    std::cout << ans;
    return 0;
}