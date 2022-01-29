#include <iostream>

const int MAX_N = 1e6 + 10;
int diff[MAX_N];

int main()
{
    std::string str;
    std::cin >> str;

    int m;
    std::cin >> m;
    for (int _i = 0; _i < m; _i++)
    {
        int l, r;
        std::cin >> l >> r;
        l--;
        r--;
        diff[l]++;
        diff[r + 1]--;
    }

    int diff_cnt = 0;
    for (std::size_t i = 0; i < str.size(); i++)
    {
        diff_cnt += diff[i];
        std::cout << (char)('a' + (str[i] - 'a' + diff_cnt) % 26);
    }
    return 0;
}
