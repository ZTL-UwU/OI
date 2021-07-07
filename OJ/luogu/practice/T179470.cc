#include <iostream>

int main()
{
    std::string s;
    std::cin >> s;
    while (s.front() == '0')
        s = s.substr(1);

    std::string ans;
    int x = 0;

    for (int i = s.size() - 1; i >= 0; i--)
    {
        const int tmp = (s[i] - '0') * 2 + x;
        x = tmp / 10;
        ans = (char)(tmp % 10 + '0') + ans;
    }

    if (x != 0)
        ans = (char)(x + '0') + ans;

    std::cout << ans;
    return 0;
}
