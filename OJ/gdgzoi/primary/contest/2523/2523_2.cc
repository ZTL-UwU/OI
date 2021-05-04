#include <algorithm>
#include <iostream>
#include <utility>
#include <string>
#include <vector>

const int MAX_N = 5e4;

std::string answers[MAX_N];

std::string flip(std::string str)
{
    for (std::size_t i = 0; i < str.size() / 2; i++)
        std::swap(str[i], str[str.size() - i - 1]);
    return str;
}

int main()
{
    int n, m, p, q;
    std::cin >> n >> m >> p >> q;

    for (int i = 0; i < n; i++)
        std::cin >> answers[i];
    std::sort(answers, answers + n);

    std::cout << '\n';
    for (int i = 0; i < n; i++)
        std::cout << answers[i] << "\n";

    std::vector<std::string> AK;
    std::vector<std::string> B0;
    for (int i = 0; i < n; i++)
    {
        auto start = answers[i];
        int cnt = 0;
        while (i < n && answers[i] == start)
        {
            i++;
            cnt++;
        }

        std::cout << i << " " << answers[i - 1] << " " << cnt << "\n";
        if (cnt == p)
            AK.push_back(answers[i - 1]);
        else if (cnt == q)
            B0.push_back(answers[i - 1]);
    }

    for (auto SB : AK)
        std::cout << SB << " ";
    std::cout << "\n";
    for (auto JR : B0)
        std::cout << JR << " ";

    for (auto SB : AK)
    {
        for (auto JR : B0)
        {
            if (flip(SB) == JR)
            {
                std::cout << SB;
                return 0;
            }
        }
    }

    std::cout << "-1";
    return 0;
}