#include <iostream>
#include <string>

const int MAX_C = 26;

int show_up[MAX_C];

int main()
{
    std::string str;
    std::getline(std::cin, str);

    for (auto i : str)
        if (i >= 'a' and i <= 'z')
            show_up[i - 'a']++;

    int max_show_up = -1;
    for (int i = 0; i < MAX_C; i++)
        if (show_up[i] > max_show_up)
            max_show_up = show_up[i];

    for (int i = 0; i < MAX_C; i++)
        if (show_up[i] == max_show_up)
            std::cout << (char)('a' + i);
    return 0;
}