#include <iostream>
#include <cstring>

const int MAX_CHARACTER = 26;

char to_lower_case(char c) { return c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c; }
char filter(char c, char c1, char c2) { return c == to_lower_case(c1) ? to_lower_case(c2) : c; }
int count(char c, bool used[])
{
    if (used[c - 'a'])
        return 0;
    used[c - 'a'] = true;
    return 1;
}

int main()
{
    bool used[MAX_CHARACTER];
    std::memset(used, 0, sizeof(used));

    std::string str;
    char c1, c2;
    std::cin >> str;
    std::cin >> c1 >> c2;

    int ans = 0;
    for (auto &i : str)
    {
        i = to_lower_case(i);
        i = filter(i, c1, c2);
        ans += count(i, used);
    }

    std::cout << str.size() * ans;
    return 0;
}