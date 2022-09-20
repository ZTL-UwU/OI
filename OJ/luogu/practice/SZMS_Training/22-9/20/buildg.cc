#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::string str;
        std::cin >> str;
        for (int j = 0; j < str.size(); j++)
        {
            if (str[j] == 'Y')
                std::cout << i + 1 << " " << j + 1 << "\n";
        }
    }
    return 0;
}