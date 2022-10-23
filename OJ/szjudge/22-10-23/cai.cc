#include <iostream>
#include <vector>
#include <cstdio>
#include <map>

using mib = std::map<int, bool>;

int prime[125] = {2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,
                  67,  71,  73,  79,  83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
                  157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
                  257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
                  367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
                  467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593,
                  599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691};

std::vector<mib> num;
std::vector<mib> new_num;
mib map, lcm;

int main()
{
    std::freopen("cai.in", "r", stdin);
    std::freopen("cai.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    int max = -1;
    for (int i = 0; i < n; i++)
    {
        map.clear();
        int a;
        std::cin >> a;
        max = std::max(max, a);

        for (int i = 0; i < 125; i++)
        {
            if (a % prime[i] == 0)
                map[i] = true;
            if (prime[i] > a)
                break;
        }
        num.push_back(map);
    }

    int max_i = 125;
    if (max < 100)
        max_i = 30;

    bool ans = true;
    while (num.size() != 1)
    {
        lcm[-1] = true;
        for (mib a : num)
        {
            bool g = false;
            for (int i = 0; i < max_i; i++)
            {
                if (a[i] && lcm[i])
                {
                    g = true;
                    break;
                }
            }

            if (!lcm[-1] && g)
            {
                for (int i = 0; i < max_i; i++)
                    if (a[i] && !lcm[i])
                        lcm[i] = true;
                lcm[-1] = false;
            }
            else
            {
                if (!lcm[-1])
                    new_num.push_back(lcm);
                lcm = a;
                lcm[-1] = false;
            }
        }
        new_num.push_back(lcm);

        if (num.size() == new_num.size())
        {
            ans = false;
            break;
        }

        num = new_num;
        new_num.clear();
    }

    if (ans)
        std::cout << "Yes";
    else
        std::cout << "No";
    return 0;
}
