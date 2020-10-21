#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
struct double_num
{
    int num1;
    int num2;
};
vector<double_num> sta;
long long dp[31][10];
int n, m;
inline void get_sta()
{
    for (int i = 0; i < (1 << m); i++)
    {
        for (int j = 0; j < (1 << m); j++)
        {
            bool flag = true;
            for (int k = 0; k < m; k++)
            {
                if (!(i & (1 << k)))
                {
                    if (!(j & (1 << k)))
                    {
                        flag = false;
                        break;
                    }
                }
                else
                {
                    if (!(j & (1 << k)))
                        continue;
                    k++;
                    if (k >= m || !(i & (1 << k)))
                    {
                        flag = false;
                        break;
                    }
                    else if (!(j & (1 << k)))
                    {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag)
                sta.push_back((double_num){i, j});
        }
    }
}
inline void get_dp()
{
    dp[0][(1 << m) - 1] = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < sta.size(); j++)
            dp[i + 1][sta[j].num2] += dp[i][sta[j].num1];
}
int main()
{
    m = 3;
    while (cin >> n)
    {
        if (n == -1)
            return 0;
        memset(dp, 0, sizeof(dp));
        sta.clear();
        get_sta();
        get_dp();
        cout << dp[n][(1 << m) - 1] << "\n";
    }
    return 0;
}