// ERROR

#include <fstream>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "../libxl.hpp"

const std::string SAMPLE[2] = {"2\n"
                               "3 5\n"
                               "5 8\n"
                               "3\n"
                               "1 2\n"
                               "1 9\n"
                               "2 9\n",

                               "1\n"
                               "1 9\n"
                               "2\n"
                               "2 4\n"
                               "2 10\n"};

const int MOD = 998244353;

inline std::vector<unsigned long long> select(unsigned long long n, int m)
{
    std::unordered_map<unsigned long long, unsigned long long> rest;
    unsigned long long tmp[m];
    for (unsigned long long i = 0; i < m; ++i)
        tmp[i] = i + 1;
    for (unsigned long long i = 0; i < m; ++i)
    {
        const unsigned long long j = lxl::mk_rand<unsigned long long>(i, n - 1);
        if (j < m)
            std::swap(tmp[i], tmp[j]);
        else if (rest.find(j) == rest.end())
        {
            rest[j] = tmp[i];
            tmp[i] = j + 1;
        }
        else
            std::swap(tmp[i], rest[j]);
    }

    return std::vector<unsigned long long>(tmp, tmp + m);
}

void shuffle(std::vector<std::pair<unsigned long long, unsigned long long>> &v)
{
    for (int i = v.size() - 1; i >= 0; --i)
    {
        std::swap(v[i], v[lxl::mk_rand<int>(0, i)]);
    }
}

int main()
{
    int type;
    std::cin >> type;

    int na, nb;

    if (type == 0 || type == 1) // Sample
        std::cout << SAMPLE[type];
    else if (type >= 2 && type <= 5) // Random
    {
        unsigned long long max_r;
        if (type == 2)
            max_r = 1e3;
        if (type == 3)
            max_r = 1e6;
        if (type == 4)
            max_r = 1e9;
        if (type == 5)
            max_r = 1e18;

        na = lxl::mk_rand(5, 100);
        nb = lxl::mk_rand(5, 100);

        std::cout << na << "\n";
        auto v = select(max_r, na * 2);
        std::sort(v.begin(), v.end());
        std::vector<std::pair<unsigned long long, unsigned long long>> output;
        std::pair<unsigned long long, unsigned long long> tmp;
        for (int i = 0; i < na * 2; i++)
        {
            if (i % 2 == 0)
                tmp.first = v[i];
            else
            {
                tmp.second = v[i];
                output.push_back(tmp);
            }
        }
        shuffle(output);
        for (auto p : output)
            std::cout << p.first << " " << p.second << "\n";

        std::cout << nb << "\n";
        v.clear();
        v = select(max_r, nb * 2);
        std::sort(v.begin(), v.end());
        output.clear();
        for (int i = 0; i < nb * 2; i++)
        {
            if (i % 2 == 0)
                tmp.first = v[i];
            else
            {
                tmp.second = v[i];
                output.push_back(tmp);
            }
        }
        shuffle(output);
        for (auto p : output)
            std::cout << p.first << " " << p.second << "\n";
    }
    else if (type == 6) // Full
    {
        unsigned long long max_r = 1e18;

        na = 2;
        nb = 2;

        const auto f = [max_r]() {
            long long l, r;
            l = lxl::mk_rand<unsigned long long>(1, 100);
            r = lxl::mk_rand<unsigned long long>(max_r - 100, max_r);

            std::cout << l << " " << r << "\n";
        };

        std::cout << na << "\n";
        lxl::loop(na, f);

        std::cout << nb << "\n";
        lxl::loop(nb, f);
    }
    else if (type == 7) // Crack long long
    {
        unsigned long long max_r = 1e18;

        na = 100;
        nb = 100;

        std::cout << na << "\n";
        auto v = select(max_r, na * 2);
        std::sort(v.begin(), v.end());
        std::vector<std::pair<unsigned long long, unsigned long long>> output;
        std::pair<unsigned long long, unsigned long long> tmp;
        int len = 1e3 + lxl::mk_rand(10, 1000);
        for (int i = 0; i < len; i++)
        {
            tmp.first = lxl::mk_rand(1, 100);
            tmp.second = MOD - lxl::mk_rand(1, 100);
            output.push_back(tmp);
        }
        for (int i = len; i < na * 2; i++)
        {
            if (i % 2 == 0)
                tmp.first = v[i];
            else
            {
                tmp.second = v[i];
                output.push_back(tmp);
            }
        }
        shuffle(output);
        for (auto p : output)
            std::cout << p.first << " " << p.second << "\n";

        std::cout << nb << "\n";
        v.clear();
        v = select(max_r, nb * 2);
        std::sort(v.begin(), v.end());
        output.clear();
        len = 1e3 + lxl::mk_rand(10, 1000);
        for (int i = 0; i < len; i++)
        {
            tmp.first = lxl::mk_rand(1, 100);
            tmp.second = MOD - lxl::mk_rand(1, 100);
            output.push_back(tmp);
        }
        for (int i = len; i < nb * 2; i++)
        {
            if (i % 2 == 0)
                tmp.first = v[i];
            else
            {
                tmp.second = v[i];
                output.push_back(tmp);
            }
        }
        shuffle(output);
        for (auto p : output)
            std::cout << p.first << " " << p.second << "\n";
    }
    else if (type == 8) // Crack minus
    {
        unsigned long long max_r = 1e18;

        na = 100;
        nb = 100;

        std::cout << na << "\n";
        auto v = select(max_r, na * 2);
        std::sort(v.begin(), v.end());
        std::vector<std::pair<unsigned long long, unsigned long long>> output;
        std::pair<unsigned long long, unsigned long long> tmp;
        int len = 1e3 + lxl::mk_rand(10, 1000);
        for (int i = 0; i < len; i++)
        {
            tmp.first = MOD - lxl::mk_rand(0, 100);
            tmp.second = MOD + lxl::mk_rand(0, 100);
            output.push_back(tmp);
        }
        for (int i = len; i < na * 2; i++)
        {
            if (i % 2 == 0)
                tmp.first = v[i];
            else
            {
                tmp.second = v[i];
                output.push_back(tmp);
            }
        }
        shuffle(output);
        for (auto p : output)
            std::cout << p.first << " " << p.second << "\n";

        std::cout << nb << "\n";
        v.clear();
        v = select(max_r, nb * 2);
        std::sort(v.begin(), v.end());
        output.clear();
        len = 1e3 + lxl::mk_rand(10, 1000);
        for (int i = 0; i < len; i++)
        {
            tmp.first = MOD - lxl::mk_rand(0, 100);
            tmp.second = MOD + lxl::mk_rand(0, 100);
            output.push_back(tmp);
        }
        for (int i = len; i < nb * 2; i++)
        {
            if (i % 2 == 0)
                tmp.first = v[i];
            else
            {
                tmp.second = v[i];
                output.push_back(tmp);
            }
        }
        shuffle(output);
        for (auto p : output)
            std::cout << p.first << " " << p.second << "\n";
    }
    else if (type == 9) // Crack ST
    {
        na = 100;
        nb = 100;

        std::cout << na << "\n";
        for (int i = 0; i < na; i++)
        {
            long long l, r;
            l = i;
            r = i + 5e15 - lxl::mk_rand(100, 1000);
            i = r + lxl::mk_rand(100, 1000);

            std::cout << l << " " << r << "\n";
        }

        std::cout << nb << "\n";
        for (int i = 0; i < nb; i++)
        {
            long long l, r;
            l = i;
            r = i + 5e15 - lxl::mk_rand(100, 1000);
            i = r + lxl::mk_rand(100, 1000);

            std::cout << l << " " << r << "\n";
        }
    }

    return 0;
}
