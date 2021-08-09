#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 1; _i <= t; _i++)
    {
        std::cout << _i << " ";

        int len;
        std::cin >> len;

        std::string s1, s2, s12;
        std::cin >> s1 >> s2 >> s12;
        if (s1 + s2 == s12)
        {
            std::cout << 0 << "\n";
            continue;
        }

        bool flag = false;
        int cnt = 1;
        while (cnt <= len * 2)
        {
            std::string tmp = s12;
            for (std::size_t i = 0; i < s1.size(); i++)
            {
                tmp[i * 2] = s2[i];
                tmp[i * 2 + 1] = s1[i];
            }

            if (tmp == s12)
            {
                flag = true;
                break;
            }

            s1 = tmp.substr(0, len);
            s2 = tmp.substr(len, len);
            cnt++;
        }

        if (flag)
            std::cout << cnt << "\n";
        else
            std::cout << "-1\n";
    }

    return 0;
}