#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>

const int MAX_N = 1e6 + 10;

struct cord
{
    double x;
    double y;
};

double sqr(double num) { return num * num; }

double dis(cord p1, cord p2) { return std::sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y)); }

cord mid_point(cord p1, cord p2) { return {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2}; }

struct circle
{
    cord o;
    double r;

    void circumcircle(cord p1, cord p2, cord p3)
    {
        const double A = p1.x - p2.x;
        const double B = p1.y - p2.y;
        const double C = p1.x - p3.x;
        const double D = p1.y - p3.y;
        const double E = ((sqr(p1.x) - sqr(p2.x)) - (sqr(p2.y) - sqr(p1.y))) / 2;
        const double F = ((sqr(p1.x) - sqr(p3.x)) - (sqr(p3.y) - sqr(p1.y))) / 2;

        this->o = {(B * F - D * E) / (B * C - A * D), (C * E - A * F) / (B * C - A * D)};
        this->r = dis(this->o, p1);
    }

    bool include(cord p) { return dis(p, this->o) <= r; }
};

cord points[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> points[i].x >> points[i].y;
    std::random_shuffle(points, points + n);

    circle c = {points[0], 0};

    for (int i = 0; i < n; i++)
    {
        if (not c.include(points[i]))
        {
            c = {points[i], 0};

            for (int j = 0; j < i; j++)
            {
                if (not c.include(points[j]))
                {
                    c = {mid_point(points[i], points[j]), dis(points[i], points[j]) / 2};

                    for (int k = 0; k < j; k++)
                        if (not c.include(points[k]))
                            c.circumcircle(points[i], points[j], points[k]);
                }
            }
        }
    }

    std::cout << std::fixed << std::setprecision(2) << c.o.x << " " << c.o.y << " " << c.r;
    return 0;
}