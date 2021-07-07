#include <iostream>
#include <array>
#include <cmath>

const int MAX_ZEROS = 8;
const int SIZE_POS = MAX_ZEROS - 1;

std::array<int, MAX_ZEROS> add(std::array<int, MAX_ZEROS> a, std::array<int, MAX_ZEROS> b)
{
    std::array<int, MAX_ZEROS> res;
    for (std::size_t i = 0; i < MAX_ZEROS - 1; i++)
        res[i] = a[i] + b[i];

    res[SIZE_POS] = std::max(a[SIZE_POS], b[SIZE_POS]);
    return res;
}

std::array<int, MAX_ZEROS> cut(int length)
{
    if (length == 0)
        return {0};

    int digit = 0;
    for (int i = MAX_ZEROS; i >= 0; i--)
    {
        if (std::pow(10, i) <= length)
        {
            digit = i;
            break;
        }
    }

    const int k = std::pow(10, digit);
    auto son = cut(length % k);
    son[digit] = length / k;

    son[SIZE_POS] = std::max(son[SIZE_POS], digit);

    return son;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int _i = 0; _i < n; _i++)
    {
        int a, b;
        std::cin >> a >> b;

        const auto res = add(cut(a), cut(b));

        for (int i = res[SIZE_POS]; i >= 0; i--)
            std::cout << res[i] << " ";
        std::cout << "\n";
    }
    return 0;
}
