#include <bits/stdc++.h>
#include <dbg.h>

using namespace std;
#define N 225
#define R 137

int n, r, t;
int D[N]; //伤害
double P[N], f[N][R], g[N], Pw[N][R];
// P[i]表示第i张牌发动技能的概率
// f[i][j]表示前i张牌恰好有j张发动的概率
// g[i]表示第i张牌在r轮中发动的概率
// Pw[i][j]预处理,即(1-P[i])^j,第i张牌在最后j轮都不发动的概率

int Min(int x, int y) { return x < y ? x : y; }

void read()
{
    scanf("%d%d", &n, &r);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%d", &P[i], &D[i]);
        Pw[i][0] = 1;
    }
}

void work()
{
    if (!r)
    {
        printf("%.10lf", g[0]); //即0
        return;
    } //当r等于0时代表没有进行游戏,输出0
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= r; j++)
        {
            Pw[i][j] = Pw[i][j - 1] * (1.0 - P[i]);
        }
    } //预处理
    f[1][0] = Pw[1][r];
    f[1][1] = 1.0 - f[1][0];
    g[1] = f[1][1]; //初始化
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= Min(i, r); j++)
        {
            if (j) //第i张牌发动
                f[i][j] += f[i - 1][j - 1] * (1.0 - Pw[i][r - j + 1]);
            if (i != j) //第i张牌不发动
                f[i][j] += f[i - 1][j] * Pw[i][r - j];
        }
    }
    dbg(Pw);
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= Min(i - 1, r); j++)
        {
            g[i] += f[i - 1][j] * (1.0 - Pw[i][r - j]);
        }
    } //统计第i张牌在所有r轮中发动的概率
    double ans = 0;
    for (int i = 1; i <= n; i++)
        ans += g[i] * D[i]; //期望得分,第i张牌发动的概率乘伤害
    printf("%.10lf\n", ans);
}

int main(void)
{
    scanf("%d", &t);
    while (t--)
    {
        memset(g, 0, sizeof(g));
        memset(f, 0, sizeof(f)); //记得重置f,g数组
        read();
        work();
    }
    return 0;
}
