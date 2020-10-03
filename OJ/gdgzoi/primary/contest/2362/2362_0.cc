#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <cmath>

int main()
{
    long long n;
    std::cin >> n;

    int end_digit = 0;
    for (int digit = 1; digit < 10; digit++)
    {
        long long session_len = 9 * std::pow(10, digit - 1) * digit;
        if (n > session_len)
            n -= session_len;
        else
        {
            end_digit = digit;
            break;
        }
    }

    int pass_number = n / end_digit;
    int number_digit = n % end_digit;

    int end = std::pow(10, end_digit - 1) + pass_number - (number_digit ? 0 : 1);
    std::string end_string;
    std::stringstream ss;
    ss << end;
    ss >> end_string;

    std::cout << end_string[(number_digit + end_digit - 1) % end_digit];
    return 0;
}