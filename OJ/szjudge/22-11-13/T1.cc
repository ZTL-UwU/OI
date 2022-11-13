#include <iostream>
#include <sstream>

using i64 = long long;

int main()
{
    i64 l, r;
    std::cin >> l >> r;

    std::string str_r;
    std::stringstream ss;
    ss << r;
    ss >> str_r;

    i64 max_pro = 0;
    i64 max_num = 0;

    for (int i = 0; i < str_r.size(); i++)
    {
        std::string str = str_r;
        if (i != str_r.size() - 1)
        {
            if (str_r[i] == '0')
            {
                int k = i - 1;
                while (str[k] == '0')
                    k--;
                str[k]--;
            }
            else
                str[i]--;

            for (int j = i + 1; j < str_r.size(); j++)
                str[j] = '9';
        }

        i64 num;
        std::stringstream sss;
        sss << str;
        sss >> num;
        if (num >= l)
        {
            std::stringstream ssss;
            std::string str_tmp;
            ssss << num;
            ssss >> str_tmp;
            i64 pro = 1;
            for (char i : str_tmp)
                pro *= (i - '0');

            if (pro >= max_pro)
            {
                max_pro = pro;
                max_num = num;
            }
        }
    }

    std::cout << max_num;
    return 0;
}