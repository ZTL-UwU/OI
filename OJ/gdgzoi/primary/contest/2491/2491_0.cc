#include <iostream>

const std::string NOIP = "noip";

inline bool match(char a, char b)
{
    if (a >= 'A' and a <= 'Z')
        a += 'a' - 'A';
    if (b >= 'A' and b <= 'Z')
        b += 'a' - 'A';

    return a == b;
}

int main()
{
    std::string str;
    std::cin >> str;

    if (str.size() < 4)
    {
        std::cout << str;
        return 0;
    }

    for (int i = 0; i < str.size() - 3; i++)
    {
        bool flag = true;
        for (int j = 0; j < 4; j++)
            if (not match(str[i + j], NOIP[j]))
                flag = false;

        if (flag)
            str.replace(i, 4, "CSP#");
    }

    for (auto i : str)
        if (i != '#')
            std::cout << i;
    return 0;
}