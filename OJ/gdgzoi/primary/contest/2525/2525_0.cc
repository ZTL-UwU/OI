#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

const double EPS = 1e-6;

struct point
{
    double x, y;

    point() { x = 0, y = 0; };
    point(double x, double y) : x(x), y(y){};

    double dis_to_x_axis() { return std::abs(y); }
    double dis_to_y_axis() { return std::abs(x); }
};

struct circle
{
    point o;
    double r;
};

double get_b(const double c, const double a) { return std::sqrt(std::pow(c, 2) - std::pow(a, 2)); }

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        circle c;
        std::cin >> c.o.x >> c.o.y >> c.r;

        std::vector<point> insection;
        if (c.o.dis_to_x_axis() == c.r)
            insection.push_back(point(c.o.x, 0));
        else if (c.o.dis_to_x_axis() < c.r)
        {
            const auto b = get_b(c.r, c.o.dis_to_x_axis());
            insection.push_back(point(c.o.x + b, 0));
            insection.push_back(point(c.o.x - b, 0));
        }

        if (c.o.dis_to_y_axis() == c.r)
            insection.push_back(point(0, c.o.y));
        else if (c.o.dis_to_y_axis() < c.r)
        {
            const auto b = get_b(c.r, c.o.dis_to_y_axis());
            insection.push_back(point(0, c.o.y + b));
            insection.push_back(point(0, c.o.y - b));
        }

        std::sort(insection.begin(), insection.end(),
                  [](point p1, point p2) -> bool
                  {
                      if (p1.x == p2.x)
                          return p1.y < p2.y;
                      return p1.x < p2.x;
                  });

        std::size_t flag = -1;
        if (insection.size() != 0)
        {
            for (std::size_t i = 0; i < insection.size() - 1; i++)
            {
                if (insection[i].x == insection[i + 1].x && insection[i].y == insection[i + 1].y)
                {
                    flag = i;
                    break;
                }
            }
        }

        std::cout << insection.size() - (flag == -1 ? 0 : 1) << "\n";
        for (std::size_t i = 0; i < insection.size(); i++)
        {
            if (i == flag)
                continue;
            std::cout << std::fixed << std::setprecision(2)
                      << (std::abs(insection[i].x) == 0 ? std::abs(insection[i].x) : insection[i].x) << " "
                      << (std::abs(insection[i].y) == 0 ? std::abs(insection[i].y) : insection[i].y) << "\n";
        }
    }
    return 0;
}