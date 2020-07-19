#include <iostream>
#include <string.h>
using namespace std;
int c[40][40];
inline void get_dp()
{
    for (int i = 0; i <= 35; i++)
        for (int j = 0; j <= i; j++)
            if (!j || i == j)
                c[i][j] = 1;
            else
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
}
int bit[40];
inline long long solve(int num)
{
    int len = 0;
    long long ans = 0;
    while (num)
    {
        bit[++len] = num % 2;
        num /= 2;
    }
    int zero = 0;
    for (int i = 1; i < len - 1; i++)
        for (int j = i / 2 + 1; j <= i; j++)
            ans += c[i][j];
    for (int i = len - 1; i >= 1; i--)
    {
        if (bit[i])
            for (int j = (len + 1) / 2 - zero - 1; j < i; j++)
                ans += c[i - 1][j];
        else
            zero++;
    }
    return ans;
}
int main()
{
    get_dp();
    int l, r;
    cin >> l >> r;
    cout << solve(r + 1) - solve(l) << "\n";
    return 0;
}