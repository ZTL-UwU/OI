// 签到

#include <iostream>

int main()
{
    std::string str;
    std::cin >> str;

    bool flag = true;
    for (std::size_t i = 0; i < str.size() - 1; i++)
    {
        if (str[i] != '9')
        {
            flag = false;
            break;
        }
    }

    if (flag)
        std::cout << str;
    else
        for (std::size_t i = 0; i < str.size() - 1; i++)
            std::cout << '9';
    return 0;
}