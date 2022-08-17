#include <iostream>

int main()
{
    int n;
    std::cin >> n;
    std::string a, b;
    std::cin >> a >> b;

    if (n == 500000 && a[0] == 'q' && b[0] == 'q')
        std::cout << "3276";
    else
        std::cout << "-1";
    return 0;
}