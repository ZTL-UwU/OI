#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cmath>

struct palindrome
{
    bool odd;
    float mid;
    int radius;
};

std::vector<palindrome> palindromes;
std::string str;

void serach(int l, int r)
{
    while (l >= 0 and r < str.size() and str[l] == str[r])
    {
        --l;
        ++r;
    }
    ++l;
    --r;

    palindromes.push_back((palindrome){(l + r) % 2 == 0, (l + r) / 2.0, std::ceil((l + r) / 2.0 - l)});
}

bool cmp(palindrome a, palindrome b) { return a.mid < b.mid; }

int main()
{
    std::freopen("palindrome.in", "r", stdin);
    std::freopen("palindrome.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> str;

    for (std::size_t i = 1; i < str.size() - 1; ++i)
    {
        if (str[i - 1] == str[i + 1])
            serach(i - 1, i + 1);
        if (str[i - 1] == str[i])
            serach(i - 1, i);
        if (str[i] == str[i + 1])
            serach(i, i + 1);
    }

    std::sort(palindromes.begin(), palindromes.end(), cmp);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int l, r;
        std::cin >> l >> r;
        --l;
        --r;

        int res = 1;
        for (std::size_t j = 0; j <= palindromes.size(); j++)
        {
            if (l < palindromes[j].mid and palindromes[j].mid < r)
            {
                palindrome p = palindromes[j];
                res =
                    std::max(res, std::min(p.radius, std::min((int)std::ceil(r - p.mid), (int)std::ceil(p.mid - l))) * 2
                                      + p.odd);
            }

            if (palindromes[j].mid > r)
                break;
        }

        std::cout << res << "\n";
    }
    return 0;
}
