#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
long long n, m, z, x[100001], y[100001], p, sum_x, sum_y, ans;
int main()
{
    scanf("%lld%lld%lld", &n, &m, &z);
    for (long long i = 1; i <= m; i++)
        scanf("%lld%lld%lld", &x[i], &y[i], &p), ans += p;
    sort(x + 1, x + 1 + m);
    sort(y + 1, y + 1 + m); //排序
    long long xn = (m + 1) / 2, yn = (m + 1) / 2;
    if (m % 2 == 0)
        xn = m / 2, yn = m / 2; //求中位
    for (long long i = 1; i <= m; i++)
        ans += (abs(x[xn] - x[i]) + abs(y[yn] - y[i])) * z; //计算答案
    printf("%lld\n%lld %lld", ans, x[xn], y[yn]);
}
