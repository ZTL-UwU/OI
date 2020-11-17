#include <iostream>
using namespace std;
const int maxn = 1000 + 5; //运用方便
int times(int p, int q)    // p^q
{
    if (q == 0)
        return 1;
    long long answer = 1;
    for (int i = 1; i <= q; i++)
    {
        answer *= p;
        answer %= 10007;
    }
    return answer;
}
int main()
{
    int c[maxn][maxn], i, j, a, b, k, m, n;
    long long ans; // c[maxn][maxn]为组合数数组
    cin >> b >> a >> k >> n >> m;
    c[0][0] = 1; //初始化
    for (i = 1; i <= k; i++)
        c[i][0] = c[i][i] = 1; //边界条件
    for (i = 1; i <= k; i++)
        for (j = 1; j < i; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % 10007;   //运用杨辉三角
    ans = c[k][m] * (times(a, m) * times(b, n) % 10007) % 10007; //相乘
    cout << ans << endl;
    return 0;
}