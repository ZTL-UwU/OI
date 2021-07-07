#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

struct term
{
    int coefficient;
    int index;
};

int to_int(const std::string &s)
{
    std::stringstream ss;
    ss << s;
    int res;
    ss >> res;

    return res;
}

int main()
{
    std::string str;
    std::getline(std::cin, str);
    str = "+" + str + "+";

    std::vector<term> equation;

    std::string coefficient = "#";
    int index = 0;
    bool before_eq = true;
    char x;
    for (auto i : str)
    {
        if (i == '+')
        {
            equation.push_back({(before_eq ? 1 : -1) * to_int(coefficient), index});

            coefficient = "+";
            index = 0;
        }
        else if (i == '-')
        {

            equation.push_back({(before_eq ? 1 : -1) * to_int(coefficient), index});

            coefficient = "-";
            index = 0;
        }
        else if (i >= 'a' && i <= 'z')
        {
            x = i;

            if (coefficient == "+" || coefficient == "#" || coefficient == "0")
                coefficient = "1";
            if (coefficient == "-")
                coefficient = "-1";
            index = 1;
        }
        else if (i == '=')
        {
            equation.push_back({(before_eq ? 1 : -1) * to_int(coefficient), index});

            coefficient = "0";
            before_eq = false;
            index = 0;
        }
        else if (i == ' ')
            continue;
        else
            coefficient += i;
    }

    // for (auto i : equation)
    //     std::cout << i.coefficient << " " << i.index << '\n';

    int index1_coefficient = 0;
    int index0_coefficient = 0;
    for (auto i : equation)
    {
        if (i.index == 0)
            index0_coefficient += i.coefficient;
        else
            index1_coefficient += i.coefficient;
    }

    const double eps = 1e-10;

    double res = (double)index0_coefficient / (double)index1_coefficient;
    std::cout << std::fixed << std::setprecision(3) << x << "=" << (res >= -eps && res <= eps ? std::abs(res) : -res);
    return 0;
}