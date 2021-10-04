#include <iostream>
#include <vector>
#include <set>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::string str;
    std::cin >> str;

    std::set<size_t> mark;
    const auto base = str.substr(0, 2);
    for (std::size_t i = 0; i < str.size() - 1; i++)
        if (str[i] == base[0] && str[i + 1] == base[1])
            mark.insert(i);

    int ans = 0;
    for (std::size_t i = 2; i <= str.size(); i += 2)
    {
        const auto prefix = str.substr(0, i);
        std::vector<std::size_t> del;
        for (auto m : mark)
        {
            if (m + i > str.size() || str.substr(m, i) != prefix)
                del.emplace_back(m);
            else
                ans++;
        }

        for (auto m : del)
            mark.erase(m);
    }

    std::cout << ans;
    return 0;
}