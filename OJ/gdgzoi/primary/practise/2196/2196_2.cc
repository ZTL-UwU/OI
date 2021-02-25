#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

const double PI = 3.141592653589793;

struct cord
{
    double x, y;
};

std::vector<cord> points;
int n;
double a, b, r;

double sqr(double num) { return num * num; }

double dis(cord p1, cord p2) { return std::sqrt(sqr(p2.x - p1.x) + sqr(p2.y - p1.y)); }

double cross_product(cord p1, cord p2, cord p3)
{
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

void get_base_point()
{
    int k = 0;
    for (std::size_t i = 0; i < points.size(); i++)
        if (points[i].x < points[k].x or (points[i].x == points[k].x and points[i].y < points[k].y))
            k = i;

    std::swap(points[0], points[k]);
}

void angle_sort()
{
    std::sort(points.begin() + 1, points.end(), [](cord p1, cord p2) -> bool {
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
}

double get_hull()
{
    get_base_point();
    angle_sort();

    std::vector<cord> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (std::size_t i = 2; i < points.size(); i++)
    {
        while (cross_product(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    double c = 0;
    for (std::size_t i = 1; i < hull.size(); i++)
        c += dis(hull[i - 1], hull[i]);
    c += dis(hull[0], hull.back());

    return c;
}

double angle_mod(double theta) { return theta > PI * 2 ? theta - PI * 2 : theta; }

std::vector<cord> get_cord(double x, double y, double theta)
{
    std::vector<cord> res;
    res.resize(4);

    const double DIAGONAL = std::sqrt(sqr(a - r * 2) + sqr(b - r * 2));
    const double ROTE_THETA = std::atan((a - 2 * r) / (b - 2 * r));
    const std::vector<double> ROTE_THETA_V = {ROTE_THETA, PI - ROTE_THETA, PI + ROTE_THETA, 2 * PI - ROTE_THETA};

    for (std::size_t i = 0; i < ROTE_THETA_V.size(); i++)
        res[i] = {x + std::cos(angle_mod(ROTE_THETA_V[i] + theta)) * DIAGONAL / 2,
                  y + std::sin(angle_mod(ROTE_THETA_V[i] + theta)) * DIAGONAL / 2};

    return res;
}

int main()
{
    std::cin >> n >> a >> b >> r;

    for (int _i = 0; _i < n; _i++)
    {
        double x, y, theta;
        std::cin >> x >> y >> theta;

        auto point_v = get_cord(x, y, theta);
        for (auto point : point_v)
            points.push_back(point);
    }

    std::cout << std::fixed << std::setprecision(2) << get_hull() + 2 * PI * r;
    return 0;
}
