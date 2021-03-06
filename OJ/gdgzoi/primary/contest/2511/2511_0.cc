#include <iostream>

int main()
{
    int n, max;
    std::cin >> n >> max;
    int now_len = 0;

    for (int i = 0; i < n; i++)
    {
        std::string str;
        std::cin >> str;

        if (now_len + str.size() <= max)
        {
            std::cout << str << " ";
            now_len += str.size();
        }
        else
        {
            std::cout << "\n" << str << " ";
            now_len = str.size();
        }
    }
    return 0;
}