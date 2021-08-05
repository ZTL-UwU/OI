#include <bits/c++config.h>
#include <iostream>
#include <vector>

const int MAX_BUDGET = 3.2e4;
const int MAX_NUM = 1e2;

struct product
{
    int price;
    int importance;
    bool is_main;
    int son[4];
};

product item[MAX_NUM];
int dp[MAX_BUDGET];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int budget, num;
    std::cin >> budget >> num;

    for (int i = 1; i <= num; i++)
    {
        int fa;
        std::cin >> item[i].price >> item[i].importance;
        std::cin >> fa;
        item[i].is_main = (fa == 0 ? true : false);

        if (fa != 0)
            item[fa].son[++item[fa].son[0]] = i;
    }

    for (int i = 1; i <= num; i++)
    {
        if (item[i].is_main)
        {
            for (int j = budget; j >= 0; j--)
            {
                if (j >= item[i].price)
                    dp[j] = std::max(dp[j], dp[j - item[i].price] + item[i].price * item[i].importance);
                if (j >= item[i].price + item[item[i].son[1]].price)
                {
                    const auto son = item[item[i].son[1]];
                    dp[j] = std::max(dp[j], dp[j - item[i].price - son.price] + item[i].price * item[i].importance
                                                + son.price * son.importance);
                }
                if (j >= item[i].price + item[item[i].son[1]].price + item[item[i].son[2]].price)
                {
                    const auto son1 = item[item[i].son[1]];
                    const auto son2 = item[item[i].son[2]];
                    dp[j] = std::max(dp[j], dp[j - item[i].price - son1.price - son2.price]
                                                + item[i].price * item[i].importance + son1.price * son1.importance
                                                + son2.price * son2.importance);
                }
            }
        }
    }

    std::cout << dp[budget];
    return 0;
}
