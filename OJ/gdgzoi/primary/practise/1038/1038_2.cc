#include <iostream>
#include <cstring>

const int MAX_N = 1e6 + 10;

long long int tree[MAX_N];
long long int dp[MAX_N];
long long int a[MAX_N];

int lowbit(int x) { return x & -x; }

void update(int x, int val)
{
    while (x < MAX_N)
    {
        tree[x] += val;
        x += lowbit(x);
    }
}

long long int query(int x)
{
    long long int res = 0;
    while (x > 0)
    {
        res += tree[x];
        x -= lowbit(x);
    }

    return res;
}

int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    for (int i = 0; i < n; i++)
    {
        update(a[i], 1);
        dp[i] = i + 1 - query(a[i]);
    }

    std::memset(tree, 0, sizeof(tree));

    long long int ans = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        update(a[i], 1);
        ans += dp[i] * query(a[i] - 1);
    }

    std::cout << ans;
    return 0;
}
