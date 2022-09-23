#include <algorithm>
#include <iostream>
#include <cstring>

using i64 = long long;
const int MAX_N = 1e2 + 10;
const int MOD = 1e9 + 7;

struct Mat
{
    i64 val[MAX_N][MAX_N];
    Mat() { memset(val, 0, sizeof val); }
};

Mat operator*(const Mat &x, const Mat &y)
{
    Mat res;
    for (int k = 0; k < 2; ++k)
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                res.val[i][j] = (res.val[i][j] + x.val[i][k] * y.val[k][j] % MOD) % MOD;
    return res;
}

int main()
{
    i64 n;
    std::cin >> n;
    Mat m, ans;
    ans.val[0][0] = 1;
    ans.val[0][1] = 1;
    m.val[0][0] = 1;
    m.val[0][1] = 1;
    m.val[1][0] = 1;

    n -= 2;
    while (n != 0)
    {
        if (n % 2 == 1)
            ans = ans * m;
        m = m * m;
        n /= 2;
    }

    std::cout << ans.val[0][0] % MOD;
    return 0;
}