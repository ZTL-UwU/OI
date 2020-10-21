#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

const int MAXN = 1e7 + 10;
int character[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};
int hash[MAXN];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::string str;
        std::cin >> str;

        int k = 1;
        int num = 0;
        for (int j = str.size() - 1; j >= 0; j--)
        {
            if (str[j] >= '0' && str[j] <= '9')
            {
                num += (str[j] - '0') * k;
                k *= 10;
            }
            else if (str[j] >= 'A' && str[j] <= 'Z')
            {
                num += character[str[j] - 'A'] * k;
                k *= 10;
            }
        }

        hash[num]++;
    }

    bool flag = false;
    for (int i = 0; i < MAXN; i++)
    {
        if (hash[i] > 1)
        {
            std::stringstream ss;
            ss << std::setfill('0') << std::setw(7) << i;
            std::string res;
            ss >> res;
            for (size_t j = 0; j < res.size(); j++)
            {
                if (j == 3)
                    std::cout << '-';
                std::cout << res[j];
            }

            std::cout << " " << hash[i] << "\n";
            flag = true;
        }
    }

    if (!flag)
        std::cout << "No duplicates.";
    return 0;
}