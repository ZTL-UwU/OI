#include <iostream>

const int MAX_N = 50;

long long int dp[MAX_N + 10];

void get_dp()
{
    dp[1] = 2;
    for (int i = 2; i <= MAX_N; i++)
    {
        dp[i] = 2;
        for (int j = 1; j <= i - 1; j++)
            dp[i] += dp[j];
    }
}

int main()
{
    get_dp();

    int n;
    std::cin >> n;

    std::string str;
    std::cin >> str;

    long long int ans = 0;
    while (true)
    {
        unsigned long long int cnt = 0;
        for (std::size_t i = 0; i < str.size(); i++)
        {
            if (str[i] == 'R')
                cnt++;
            else
                break;
        }

        if (cnt == 0)
        {
            str[0] = 'R';
            ans++;
            continue;
        }

        if (cnt == str.size())
            break;

        str[cnt] = 'R';
        ans += dp[cnt];
    }

    std::cout << ans;
    return 0;
}