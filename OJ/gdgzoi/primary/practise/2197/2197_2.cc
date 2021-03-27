#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <deque>
#include <cmath>

const int MAX_M = 1e3;

struct point
{
    double x;
    double y;

    point operator-(const point p) const { return {this->x - p.x, this->y - p.y}; }
    point operator+(const point p) const { return {this->x + p.x, this->y + p.y}; }
    point operator*(const double p) const { return {this->x * p, this->y * p}; }
};

struct line
{
    point a;
    point b;
    double theta;

    line(point a, point b)
    {
        this->a = a;
        this->b = b;
        this->theta = std::atan2(b.y, b.x);
    }
};

struct queue_item
{
    point intersection;
    line line;
};

double cross_product(point a, point b) { return a.x * b.y - a.y - b.x; }

point intersection(line a, line b)
{
    point c = a.a - b.a;
    double tmp = cross_product(b.b, c) / cross_product(a.b, b.b);
    return a.a + a.b * tmp;
}

const point TMP_P = {0, 0};

point p[MAX_M];
std::vector<line> l;

int main()
{
    int n;
    std::cin >> n;

    for (int _i = 0; _i < n; _i++)
    {
        int m;
        std::cin >> m;

        for (int i = 0; i < m; i++)
            std::cin >> p[i].x >> p[i].y;

        for (int i = 0; i < m; i++)
            l.push_back({p[i], p[(i + 1) % m] - p[i]});
    }

    std::sort(l.begin(), l.end(), [](line l1, line l2) -> bool { return l1.theta < l2.theta; });

    std::deque<queue_item> dq;
    dq.push_back({TMP_P, l[0]});

    for (std::size_t i = 1; i < l.size(); i++)
    {
        while ((dq.size() > 1) and (cross_product(l[i].b, dq[dq.size() - 2].intersection - l[i].a) <= 0))
            dq.pop_back();

        while ((dq.size() > 1) and (cross_product(l[i].b, dq.front().intersection - l[i].a) <= 0))
            dq.pop_front();

        dq.push_back({TMP_P, l[i]});

        if (std::fabs(cross_product(dq.back().line.b, dq[dq.size() - 2].line.b)) == 0)
        {
            dq.pop_back();
            if (cross_product(dq.back().line.b, l[i].a - dq.back().line.a) > 0)
                dq.back().line = l[i];
        }

        if (dq.size() > 1)
            dq[dq.size() - 2].intersection = intersection(dq[dq.size() - 2].line, dq.back().line);
    }

    while ((dq.size() > 1)
           and (cross_product(dq.front().line.b, dq[dq.size() - 2].intersection - dq.front().line.a) <= 0))
        dq.pop_back();
    if (dq.size() > 1)
        dq.back().intersection = intersection(dq.front().line, dq.back().line);

    double ans = 0;
    for (std::size_t i = 0; i < dq.size(); i++)
        ans += cross_product(dq[i].intersection, dq[(i + 1) % dq.size()].intersection);

    std::cout << std::fixed << std::setprecision(3) << ans / 2;
    return 0;
}