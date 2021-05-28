#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#include <dbg.h>

const int MAX_N = 1e3 + 10;

struct cord
{
    int x;
    int y;
};

cord points[MAX_N];

int sqr(int num) { return num * num; }

double dis(cord p1, cord p2) { return std::sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y)); }

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

        std::size_t k = 0;
        for (int i = 1; i < n; i++)
            if (points[i].x < points[k].x or (points[i].x == points[k].x and points[i].y < points[k].y))
                k = i;
        std::swap(points[0], points[k]);

        std::sort(points + 1, points + n,
                  [](cord p1, cord p2) -> bool
                  {
                      double theta1 = std::atan2(p1.y - points[0].y, p1.x - points[0].x);
                      double theta2 = std::atan2(p2.y - points[0].y, p2.x - points[0].x);

                      // if (theta1 == theta2)
                      //     return dis(p1, points[0]) < dis(p2, points[0]);

                      return theta1 < theta2;
                  });

        // std::cout << "\n";
        // for (int i = 0; i < n; i++)
        //     std::cout << points[i].x << " " << points[i].y << "\n";

        std::vector<cord> hull;
        hull.push_back(points[0]);
        hull.push_back(points[1]);
        for (int i = 2; i < n; i++)
        {
            while (cross_product(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) < 0)
                hull.pop_back();
            hull.push_back(points[i]);
        }

        std::cout << "\n";
        for (auto i : hull)
            std::cout << i.x << " " << i.y << "\n";

        k = 0;
        while (k < hull.size())
        {
            int delta = 2;
            while (cross_product(hull[k], hull[k + 1], hull[(k + delta) % hull.size()]) == 0)
            {
                delta++;
                if (k + delta == hull.size())
                    break;
            }

            if (delta == 2)
                break;

            k += delta - 1;
        }

        if (k == hull.size())
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }
    return 0;
}