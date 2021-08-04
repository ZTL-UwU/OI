#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    std::string s, t;
    std::cin >> s >> t;

    int ans = 0;
    std::string s_last = s;
    char last = '#';
    for (int i = 0; i < n; i++)
    {
        if (s_last[i] != t[i] && last != t[i])
        {
            bool flag = false;
            for (int j = i - 1; j >= 0; j--)
            {
                if (s_last[j] == t[i])
                {
                    flag = true;
                    for (int k = j; k <= i; k++)
                        s[k] = s_last[j];
                    break;
                }
            }

            if (!flag)
            {
                std::cout << -1;
                return 0;
            }
        }

        if (last == t[i])
            s[i] = last;
        if (s_last[i] == t[i])
            s[i] = s_last[i];
        last = s[i];

        if (i == n - 1)
        {
            bool flag = true;
            for (int i = 0; i < n; i++)
                if (s[i] != t[i])
                    flag = false;

            if (!flag)
            {
                i = 0;
                s_last = s;
                last = '#';
                ans++;
            }
        }
    }

    std::cout << ans + 1;
    return 0;
}
