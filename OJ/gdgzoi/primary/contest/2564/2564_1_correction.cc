#include <iostream>

const int MAX_N = 2e5 + 10;

int next[MAX_N];
int f[MAX_N];

int main()
{
    std::string str;
    std::cin >> str;

    int p = -1;
    next[0] = -1;
    for (std::size_t i = 1; i < str.size(); i++)
    {
        while (p >= 0 && str[p + 1] != str[i])
            p = next[p];
        if (str[p + 1] == str[i])
            p++;
        next[i] = p;
    }

    int ans = 0;
    for (std::size_t i = 1; i < str.size(); i++)
    {
        if (next[i] == -1)
            next[i] = 0;
        f[i] = f[next[i]] + (i % 2 == 1 ? 1 : 0);
        ans += f[i];
    }

    std::cout << ans;
    return 0;
}