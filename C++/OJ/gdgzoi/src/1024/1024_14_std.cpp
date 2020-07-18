#include <bits/stdc++.h>

#define MAXN 50000

int n, num[MAXN], dp[MAXN], sum[MAXN];

int main()
{
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> num[i];
        dp[i] = 1;
    }
    num[n++] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            if (num[i] < num[j])
                dp[i] = std::max(dp[i], dp[j] + 1);
        int mark = num[i];
        for (int j = i - 1; j >= 0; j--)
            if (num[i] < num[j] && dp[j] + 1 == dp[i] && num[j] != mark)
            {
                sum[i] += sum[j];
                mark = num[j];
            }
        sum[i] = (!sum[i]) ? 1 : sum[i];
    }
    std::cout << dp[n - 1] - 1 << " " << sum[n - 1] << std::endl;
    return 0;
}