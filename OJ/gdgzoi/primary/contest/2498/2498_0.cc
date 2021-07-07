#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

std::string find(std::string str, std::function<bool(std::string)> check)
{
    if (str.size() == 0)
        return "#";
    if (check(str))
        return find(str.substr(0, str.size() - 1), check);
    return str.substr(0, str.size() - 1) + "4";
}

int main()
{
    std::string last_triangle;
    std::cin >> last_triangle;
    last_triangle = last_triangle.substr(1, last_triangle.size() - 1);

    if (last_triangle.back() == '4')
        for (int i = 1; i <= 3; i++)
            std::cout << "T" + last_triangle.substr(0, last_triangle.size() - 1) + std::to_string(i) + "\n";
    else
    {
        std::vector<std::string> ans;
        ans.push_back(find(last_triangle, [](std::string s) -> bool { return s.back() == '1' or s.back() == '2'; }));
        ans.push_back(find(last_triangle, [](std::string s) -> bool { return s.back() == '1' or s.back() == '3'; }));
        ans.push_back(find(last_triangle, [](std::string s) -> bool { return s.back() == '2' or s.back() == '3'; }));

        std::sort(ans.begin(), ans.end());
        for (auto s : ans)
            if (s != "#")
                std::cout << "T" + s + "\n";
    }
    return 0;
}