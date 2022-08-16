先考虑贪心，发现当升级后一定是一直选取 $bp$ 最大，即期望收益最大的游戏，而升级前的选取要考虑升级的概率和当前选取的收益，所以考虑 $\text{DP}$ 来解决升级前的选取。

设 $f_t$​ 为还剩 $t$ 秒且当前未成功升级的最大期望收益，$v$ 为 $bp$ 最大值，得：

$$ f_t=\max_{i=1}^n\{ p_i((t-1)v+a_i)+(1-p_i)f_{t-1} \} $$

即为成功后就一直选取最优的选择，未成功就继续 $\text{DP}$。将方程转化为另一种形式，得：

$$f_t=\max_{i=1}^n\{ p_i((t-1)v-f_{t-1})+p_ia_i \}+f_{t-1}$$

发现转移可以表示为 $kx+b$ 的形式，$p_i$​ 看作为 $k$，$p_ia_i$​ 看作为 $b$。也就是每个转移都可以用一条直线来表示，考虑斜率优化，维护出下凸壳后二分出 $x=(t-1)v-f_{t-1}$​ 在下凸壳的哪一条直线上即可。但是发现秒数 $t$ 很大，不能直接做。

发现 $tv-f_t$​ 是单调不降的，假设有 $tv-f_t \geq (t-1)v-f_{t-1}$，得 $f_{t-1} \leq v$，根据 $v$ 的定义，每一次的最优决策所带来的收益不可能超过 $v$，因此得证 $tv-f_t$​ 是单调不降的。

那么就可以直接扫一遍直线，二分每次连续可行转移的 ttt 的区间，通过矩阵快速幂来优化转移：

$$
\large\begin{bmatrix} f_t & t & 1 \end{bmatrix} \times \begin{bmatrix} 1-p_i & 0 & 0 \\
p_iv & 1 & 0 \\
p_ia_i & 1 & 1 \end{bmatrix} = \begin{bmatrix} f_{t+1} & t+1 & 1 \end{bmatrix}
$$

二分是两个 $\log$ 的，通过矩阵倍增来代替二分转移就可以做到一个 $\log$。

```cpp
#include <bits/stdc++.h>
#define maxn 100010
#define eps 1e-12
using namespace std;
typedef long long ll;

template <typename T>
inline void read(T &x)
{
    x = 0;
    char c = getchar();
    bool flag = false;
    while (!isdigit(c))
    {
        if (c == '-')
            flag = true;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    if (flag)
        x = -x;
}

int n, tot, top;
ll t, now;
double v;

struct matrix
{
    double a[5][5];
} f, g[36];

matrix operator*(const matrix &x, const matrix &y)
{
    matrix z;
    memset(z.a, 0, sizeof(z.a));
    for (int k = 1; k <= 3; ++k)
        for (int i = 1; i <= 3; ++i)
            for (int j = 1; j <= 3; ++j)
                z.a[i][j] += x.a[i][k] * y.a[k][j];
    return z;
}

int sgn(double x)
{
    if (fabs(x) < eps)
        return 0;
    return x > 0 ? 1 : -1;
}

struct line
{
    double k, b;
} l[maxn], st[maxn];

bool cmp(const line &x, const line &y)
{
    if (!sgn(x.k - y.k))
        return x.b < y.b;
    return x.k < y.k;
}

double get(line x, line y) { return (x.b - y.b) / (y.k - x.k); }

int main()
{
    read(n), read(t);
    for (int i = 1; i <= n; ++i)
    {
        double a, b, p;
        scanf("%lf%lf%lf", &a, &b, &p);
        l[i] = {p, p * a}, v = max(v, b * p);
    }
    sort(l + 1, l + n + 1, cmp);

    for (int i = 1; i <= n; ++i)
        if (sgn(l[i].k - l[i + 1].k))
            l[++tot] = l[i];

    for (int i = 1; i <= tot; ++i)
    {
        while (top > 1 && sgn(get(st[top], st[top - 1]) - get(l[i], st[top - 1])) >= 0)
            top--;
        st[++top] = l[i];
    }

    f.a[1][3] = 1;
    for (int i = 1; i <= top; ++i)
    {
        double pos = now * v - f.a[1][1];
        while (i < top && sgn(pos - get(st[i], st[i + 1])) >= 0)
            i++;
        if (i < top)
            pos = get(st[i], st[i + 1]);
        g[0].a[1][2] = g[0].a[1][3] = g[0].a[2][3] = 0;
        g[0].a[2][2] = g[0].a[3][2] = g[0].a[3][3] = 1;
        g[0].a[1][1] = 1 - st[i].k, g[0].a[2][1] = st[i].k * v, g[0].a[3][1] = st[i].b;

        for (int j = 1; j <= 34; ++j)
            g[j] = g[j - 1] * g[j - 1];
        for (int j = 34; j >= 0; --j)
            if (now + (1ll << j) < t)
                if (i == top || sgn(pos - (now + (1ll << j)) * v + (f * g[j]).a[1][1]) >= 0)
                    f = f * g[j], now += 1ll << j;
        f = f * g[0], now++;
        if (now == t)
            break;
    }
    printf("%.10lf", f.a[1][1]);
    return 0;
}
```