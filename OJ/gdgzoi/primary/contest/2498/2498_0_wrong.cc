#include <iostream>
#include <string>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::string last_triangle;
    std::cin >> last_triangle;
    last_triangle = last_triangle.substr(1, last_triangle.size() - 1);

    if (last_triangle.back() == '4')
        for (int i = 1; i <= 3; i++)
            std::cout << "T" + last_triangle.substr(0, last_triangle.size() - 1) + std::to_string(i) + "\n";
    else
        for (std::size_t i = last_triangle.size() - 1; i < last_triangle.size(); i--)
            if (last_triangle[i] != last_triangle.back() or i == last_triangle.size() - 1)
                std::cout << "T" + last_triangle.substr(0, i) + "4" + "\n";
    return 0;
}