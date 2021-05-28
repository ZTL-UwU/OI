#include <stdio.h>
int c[33][33] = {0};
int bi[35];
void zhs(void)
//组合数打表，用的拼音首字母不要介意QAQ
{
    for (int i = 0; i < 33; i++)
        for (int j = 0; j <= i; j++)
            if (!j || i == j)
                c[i][j] = 1;
            else
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    return;
}
void dtb(int n)
// dec to bin的简写(我的习惯真奇怪)
{
    bi[0] = 0;
    while (n)
    {
        bi[++bi[0]] = n % 2;
        n /= 2;
    }
    return;
}
int round(int n)
{
    int i, j, sum = 0; //变量名终于正常了
    dtb(n);
    for (i = 1; i < bi[0] - 1; i++)
        for (j = i / 2 + 1; j <= i; j++)
            sum += c[i][j];
    int z = 0; // z是zero的简写鸭QwQ
    for (i = bi[0] - 1; i >= 1; i--)
        if (bi[i])
            for (j = (bi[0] + 1) / 2 - (z + 1); j <= i - 1; j++)
                sum += c[i - 1][j];
        else
            z++;
    return sum;
}
int main(void)
{
    zhs();
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", round(b + 1) - round(a));
    return 0;
}