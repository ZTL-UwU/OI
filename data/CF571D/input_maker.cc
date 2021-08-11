#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

const int MAX_N = 5e5 + 10;

std::mt19937 rng(std::random_device{}());

const std::string SAMPLE[3] = {"",

                               "2 7\n"
                               "A 1\n"
                               "Q 1\n"
                               "U 1 2\n"
                               "A 1\n"
                               "Z 1\n"
                               "Q 1\n"
                               "Q 2\n",

                               "5 12\n"
                               "U 1 2\n"
                               "M 4 5\n"
                               "A 1\n"
                               "Q 1\n"
                               "A 3\n"
                               "A 4\n"
                               "Q 3\n"
                               "Q 4\n"
                               "Z 4\n"
                               "Q 4\n"
                               "A 5\n"
                               "Q 5\n"};

const char OP[5] = {'U', 'M', 'A', 'Z', 'Q'};
bool gone[MAX_N];

int rd(int min, int max)
{
    if (min >= max)
        return max;
    return (1LL * rng() * (rng() % 1000)) % (max - min) + min;
}

int main()
{
    int sample;     // 0: no, 1: sp1, 2: sp2
    int difficulty; // 1: easy, 2: random, 3: hard
    int hard_type;
    std::cin >> sample >> difficulty >> hard_type;

    if (sample)
    {
        std::cout << SAMPLE[sample];
        return 0;
    }

    int n = 5e5, m = 5e5;
    if (difficulty == 1)
    {
        n = rd(50, 1e3);
        m = rd(50, 1e3);
        while (m > n)
            m = rd(50, 1e3);
    }
    else if (difficulty == 2)
    {
        n = rd(2e4, 5e5);
        m = rd(2e4, 5e5);
        while (m > n)
            m = rd(2e4, 5e5);
    }
    else if (difficulty == 3)
    {
        n = 5e5;
        m = 5e5;
    }

    std::cout << n << " " << m << "\n";

    // Random
    if (difficulty == 1 || difficulty == 2 || (difficulty == 3 && hard_type == 0))
    {
        std::vector<int> used_x;
        for (int _i = 0; _i < m; _i++)
        {
            const char op = OP[rand() % 5];
            std::cout << op << " ";
            if (op == 'U' || op == 'M')
            {
                int x = rd(1, n);
                int y = rd(1, n);
                while (gone[x])
                    x = rd(1, n);
                while (gone[y] || x == y)
                    y = rd(1, n);

                std::cout << x << " " << y;
                used_x.push_back(x);
                gone[y] = true;
            }
            else
            {
                int x = 3;
                if (rand() % 15 == 0 || used_x.size() == 0)
                {
                    x = rd(1, n);
                    while (gone[x])
                        x = rd(1, n);
                }
                else
                    x = used_x[rd(0, used_x.size())];

                std::cout << x;
            }

            std::cout << "\n";
        }
    }

    // Man-Made
    if (difficulty == 3)
    {
        // Large Single Aggregate
        if (hard_type == 1)
        {
            int base_pos1 = rd(1, n);
            int base_pos2 = rd(1, n);

            std::vector<std::string> output;
            for (int i = 0; i < (m - 3e4) / 2; i++)
            {
                std::stringstream ss;
                std::string tmp1;
                std::string tmp2;
                ss << base_pos1 << " " << (i + 1 == base_pos1 ? n : i + 1);
                ss >> tmp1 >> tmp2;
                output.push_back("U " + tmp1 + " " + tmp2 + "\n");
                ss << base_pos2 << " " << (i + 1 == base_pos2 ? n : i + 1);
                ss >> tmp1 >> tmp2;
                output.push_back("M " + tmp1 + " " + tmp2 + "\n");
            }
            std::random_shuffle(output.begin(), output.end());
            for (auto str : output)
                std::cout << str;

            for (int i = 0; i < 3e4 / 2; i++)
            {
                rand() % 2 == 0 ? std::cout << "A " << base_pos1 << "\n" : std::cout << "Z " << base_pos2 << "\n";
                std::cout << "Q " << rd(1, n) << "\n";
            }
        }
    }
    return 0;
}
