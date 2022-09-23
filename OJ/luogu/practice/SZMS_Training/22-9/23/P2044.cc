#include <iostream>
#include <cstring>

using i64 = long long;
i64 mod, a, c, x0, n, g;

i64 slow_mul(i64 a, i64 b)
{
    i64 res = 0;
    while (b)
    {
        if (b % 2 == 1)
            res = (res + a) % mod;
        a = (a + a) % mod;
        b /= 2;
    }

    return res % mod;
}

struct Mat
{
    i64 val[10][10];
    int n, m;
    Mat(int n, int m)
    {
        std::memset(val, 0, sizeof val);
        this->n = n;
        this->m = m;
    }
    void build_basic()
    {
        for (int i = 0; i < n; ++i)
            val[i][i] = 1;
    }
};

Mat operator*(const Mat &x, const Mat &y)
{
    Mat res(x.n, y.m);
    for (int i = 0; i < x.n; i++)
        for (int j = 0; j < y.m; j++)
            for (int k = 0; k < x.m; k++)
                res.val[i][j] = (res.val[i][j] + slow_mul(x.val[i][k], y.val[k][j]) % mod) % mod;
    return res;
}

int main()
{
    std::cin >> mod >> a >> c >> x0 >> n >> g;
    if (n == 0)
    {
        std::cout << x0;
        return 0;
    }

    Mat start(2, 1), trans(2, 2), ans(2, 2);
    ans.build_basic();
    start.val[0][0] = x0;
    start.val[1][0] = c;
    trans.val[0][0] = a;
    trans.val[0][1] = 1;
    trans.val[1][1] = 1;

    while (n > 0)
    {
        if (n % 2 == 1)
            ans = ans * trans;
        trans = trans * trans;
        n /= 2;
    }

    ans = ans * start;
    std::cout << ans.val[0][0] % g;
    return 0;
}