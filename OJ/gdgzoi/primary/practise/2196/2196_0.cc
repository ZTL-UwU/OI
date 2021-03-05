#include <algorithm>
#include <bits/c++config.h>
#include <iostream>
#include <vector>
#include <cmath>

const int MAX_N = 1e3 + 10;

struct cord
{
    int x;
    int y;

    double polar_angle(cord o) { return std::atan2(this->y - o.y, this->x - o.x); }
    double dis(cord p) { return std::sqrt(std::pow(this->x - p.x, 2) + std::pow(this->y - p.y, 2)); }
};

cord points[MAX_N];

double cross_product(cord p1, cord p2, cord p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        int n;
        std::cin >> n;

        for (int i = 0; i < n; i++)
            std::cin >> points[i].x >> points[i].y;

        for (int i = 0; i < n; i++)
            if (points[i].x < points[0].x or (points[i].x == points[0].x and points[i].y < points[0].y))
                std::swap(points[0], points[i]);

        double min_polar_angle = 181;
        double max_polar_angle = -1;
        for (int i = 1; i < n; i++)
        {
            min_polar_angle = std::min(min_polar_angle, points[i].polar_angle(points[0]));
            max_polar_angle = std::max(max_polar_angle, points[i].polar_angle(points[0]));
        }

        std::sort(points + 1, points + n, [min_polar_angle, max_polar_angle](cord p1, cord p2) -> bool {
            const double POLAR_ANGLE_1 = p1.polar_angle(points[0]);
            const double POLAR_ANGLE_2 = p2.polar_angle(points[0]);

            if (POLAR_ANGLE_1 == POLAR_ANGLE_2)
            {
                if (POLAR_ANGLE_1 == min_polar_angle)
                {
                    return p1.dis(points[0]) < p2.dis(points[0]);
                }
                else if (POLAR_ANGLE_1 == max_polar_angle)
                {
                    return p1.dis(points[0]) > p1.dis(points[0]);
                }
                else
                {
                    if (p1.y == p2.y)
                        return p1.x > p2.x;
                    return p1.y > p2.y;
                }
            }

            return POLAR_ANGLE_1 < POLAR_ANGLE_2;
        });

        std::vector<cord> hull;
        hull.push_back(points[0]);
        hull.push_back(points[1]);

        for (int i = 2; i < n; i++)
        {
            while (cross_product(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) < 0)
                hull.pop_back();
            hull.push_back(points[i]);
        }

        int last = 0;
        bool stable = true;
        for (std::size_t i = 1; i < hull.size() - 1; i++)
        {
            if (cross_product(hull[i - 1], hull[i], hull[i + 1]) != 0)
            {
                if (i - last + 1 < 3)
                {
                    stable = false;
                    break;
                }

                last = i;
            }
        }

        if (stable == false or hull.size() - last + 1 < 3)
            std::cout << "NO\n";
        else
            std::cout << "YES\n";
    }
    return 0;
}