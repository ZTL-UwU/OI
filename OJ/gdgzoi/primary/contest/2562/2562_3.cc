#include <unordered_map>
#include <iostream>
#include <string>

std::unordered_map<std::string, bool> hash;

int main()
{
    int n, m;
    std::string str;
    std::cin >> n >> m >> str;

    int ans = 0;
    for (std::size_t i = 0; i < str.size() - m + 1; i++)
    {
        const auto sub_str = str.substr(i, m);
        if (!hash[sub_str])
        {
            hash[sub_str] = true;
            ans++;
        }
    }

    std::cout << ans;
    return 0;
}