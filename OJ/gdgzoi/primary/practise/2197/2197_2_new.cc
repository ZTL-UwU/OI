#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <deque>

struct Point
{
    double x;
    double y;

    Point operator-(const Point p) const;
    Point operator+(const Point p) const;
    Point operator*(const double d) const;
};

Point Point::operator-(const Point p) const { return {this->x - p.x, this->y - p.y}; }
Point Point::operator+(const Point p) const { return {this->x + p.x, this->y + p.y}; }
Point Point::operator*(const double d) const { return {this->x * d, this->y * d}; }

double cross_product(const Point &p1, const Point &p2) { return p1.x * p2.y - p1.y * p2.x; }

struct Line
{
    Point p1, p2;
    double theta;

    Line(const Point p1, const Point p2);
};

Line::Line(const Point p1, const Point p2)
{
    this->p1 = p1;
    this->p2 = p2;
    this->theta = std::atan2(p2.y, p2.x);
}

bool is_to_right(const Line &l, const Point &p) { return cross_product(l.p2, p - l.p1) < 0; }
Point intersect(const Line &l1, const Line &l2)
{
    const auto p = l1.p1 - l2.p1;
    double tmp = cross_product(p, l2.p2) / cross_product(l2.p2, l1.p2);
    return l1.p1 + l1.p2 * tmp;
}

int main()
{
    std::vector<Line> line;

    int n;
    std::cin >> n;

    for (int _i = 0; _i < n; _i++)
    {
        std::vector<Point> point;

        int m;
        std::cin >> m;
        for (int __i = 0; __i < m; __i++)
        {
            double x, y;
            std::cin >> x >> y;
            point.push_back({x, y});
        }

        for (std::size_t i = 0; i < point.size(); i++)
            line.push_back(Line(point[i], point[(i + 1) % m] - point[i]));
    }

    std::sort(line.begin(), line.end(),
              [](Line l1, Line l2) -> bool
              {
                  if (l1.theta == l2.theta)
                      return cross_product(l1.p1, l2.p1 + l2.p2 - l1.p2) > 0;
                  return l1.theta < l2.theta;
              });

    std::deque<Line> lines;
    std::deque<Point> intersections;

    lines.push_back(line.front());
    for (std::size_t i = 1; i < line.size(); i++)
    {
        while ((!intersections.empty()) && is_to_right(line[i], intersections.back()))
        {
            lines.pop_back();
            intersections.pop_back();
        }

        while ((!intersections.empty()) && is_to_right(line[i], intersections.front()))
        {
            lines.pop_front();
            intersections.pop_front();
        }

        lines.push_back(line[i]);

        if (std::abs(cross_product(lines.back().p2, lines[lines.size() - 2].p2)) == 0)
        {
            lines.pop_back();
            if (!is_to_right(lines.back(), line[i].p1))
                lines.back() = line[i];
        }
        else if (lines.size() > 1)
            intersections.push_back(intersect(lines.back(), lines[lines.size() - 2]));
    }

    while (!intersections.empty() && is_to_right(lines.front(), intersections.back()))
    {
        lines.pop_back();
        intersections.pop_back();
    }

    intersections.push_back(intersect(lines.front(), lines.back()));
    intersections.push_back(intersections.front());

    double ans = 0;
    for (std::size_t i = 0; i < intersections.size() - 1; i++)
        ans += cross_product(intersections[i], intersections[i + 1]);

    std::cout << std::fixed << std::setprecision(3) << ans / 2;
    return 0;
}