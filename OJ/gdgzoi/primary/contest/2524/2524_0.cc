#include <algorithm>
#include <iostream>

const int MAX_N = 1e5 + 10;

std::string str[MAX_N];

bool check(std::string s1, std::string s2)
{
    if (s1.size() == s2.size())
        return s1 > s2;
    if (s1.size() < s2.size())
    {
        if (s2.substr(0, s1.size()) == s1)
            return check(s1, s2.substr(s1.size()));
        else
            return s1 > s2;
    }
    else
    {
        if (s1.substr(0, s2.size()) == s2)
            return check(s1.substr(s2.size()), s1);
        else
            return s2 < s1;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> str[i];

    std::sort(str, str + n, check);

    for (int i = 0; i < n; i++)
        std::cout << str[i];
    return 0;
}
