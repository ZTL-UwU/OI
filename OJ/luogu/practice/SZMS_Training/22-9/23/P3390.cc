#include <algorithm>
#include <iostream>
#include <cstring>

using i64 = long long;
const int MAX_N = 1e2 + 10;
const int MOD = 1e9 + 7;

i64 n, k;

struct Mat
{
    i64 val[MAX_N][MAX_N];
    Mat() { memset(val, 0, sizeof val); }
    void build_basic()
    {
        for (int i = 0; i < n; ++i)
            val[i][i] = 1;
    }
};

Mat operator*(const Mat &x, const Mat &y)
{
    Mat res;
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                res.val[i][j] = (res.val[i][j] + x.val[i][k] * y.val[k][j] % MOD) % MOD;
    return res;
}

int main()
{
    std::cin >> n >> k;
    Mat m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> m.val[i][j];

    Mat ans;
    ans.build_basic();

    while (k != 0)
    {
        if (k % 2 == 1)
            ans = ans * m;
        m = m * m;
        k /= 2;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            std::cout << ans.val[i][j] << " ";
        std::cout << "\n";
    }
    return 0;
}