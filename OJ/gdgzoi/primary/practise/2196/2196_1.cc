#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

const int MAX_N = 1e5;
const double PI = std::acos(-1);

struct cord
{
    double x;
    double y;
};

cord points[MAX_N];

double sqr(double num) { return num * num; }

double dis(cord p1, cord p2) { return std::sqrt(sqr(p2.x - p1.x) + sqr(p2.y - p1.y)); }

double cross_product(cord p1, cord p2, cord p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

int main()
{
    int n, l;
    std::cin >> n >> l;

    for (int i = 0; i < n; i++)
        std::cin >> points[i].x >> points[i].y;

    int k = 0;
    for (int i = 0; i < n; i++)
        if (points[i].x < points[k].x or (points[i].x == points[k].x and points[i].y < points[k].y))
            k = i;
    std::swap(points[0], points[k]);

    std::sort(points + 1, points + n,
              [](cord p1, cord p2) -> bool
              {
                  double theta1 = std::atan2(p1.y - points[0].y, p1.x - points[0].x);
                  double theta2 = std::atan2(p2.y - points[0].y, p2.x - points[0].x);
                  if (theta1 == theta2)
                  {
                      if (p1.y == p2.y)
                          return p1.x > p2.x;
                      return p1.y > p2.y;
                  }

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

    double c = 0;
    for (std::size_t i = 1; i < hull.size(); i++)
        c += dis(hull[i - 1], hull[i]);
    c += dis(hull[0], hull.back());

    std::cout << static_cast<int>(c + 2 * PI * l + 0.5);
    return 0;
}