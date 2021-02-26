#include <algorithm>
#include <bits/c++config.h>
#include <iostream>
#include <vector>
#include <cmath>

const int MAX_N = 1e4 + 10;

struct cord
{
    int x;
    int y;
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

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> points[i].x >> points[i].y;

    int k = 0;
    for (int i = 0; i < n; i++)
        if (points[i].x < points[k].x or (points[i].x == points[k].x and points[i].y < points[k].y))
            k = i;
    std::swap(points[0], points[k]);

    std::sort(points + 1, points + n, [](cord p1, cord p2) -> bool {
        double theta1 = std::atan2(p1.y - points[0].y, p1.x - points[0].x);
        double theta2 = std::atan2(p2.y - points[0].y, p2.x - points[0].x);

        return theta1 < theta2;
    });

    std::vector<cord> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (int i = 2; i < n; i++)
    {
        while (cross_product(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    double ans = 0;
    for (std::size_t i = 1; i < hull.size() - 1; i++)
        ans += cross_product(hull[0], hull[i], hull[i + 1]);

    std::cout << (int)(ans / 2 + 0.5);
    return 0;
}