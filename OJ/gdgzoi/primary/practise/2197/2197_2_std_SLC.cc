#include <algorithm>
#include <deque>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
using namespace std;

const double eps = 1e-10;

template <typename T>
int sign(T x) {
    if (x < eps && x > -eps) { return 0; }
    if (x > -eps) { return 1; }
    return -1;
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator*(const double& b) const { return Point(x * b, y * b); }
    Point operator+(const Point& b) const { return Point(x + b.x, y + b.y); }
};

vector<Point> points;
deque<Point> sec;

inline double cross_product(const Point& x, const Point& y) { return x.x * y.y - y.x * x.y; }

struct Line {
    Point p;
    Point v;
    double angle;

    Line() {}
    Line(Point p, Point v) : p(p), v(v) { this->angle = atan2(v.y, v.x); }
    bool operator<(const Line& b) const {
        return sign(this->angle - b.angle) == 0 ? sign(cross_product(this->v, b.v + b.p - this->p)) > 0 :
                                                  sign(this->angle - b.angle) < 0;
    }
};

int n, m;
vector<Line> lines;
deque<Line> Q;

inline bool is_on_left(const Line& k, const Point& po) { return cross_product(k.v, po - k.p) > -eps; }

Point get_insertion(const Line& l1, const Line& l2) {
    decltype(auto) u = l1.p - l2.p;
    double t = cross_product(u, l2.v) / cross_product(l2.v, l1.v);
    return l1.p + l1.v * t;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int _ = 0; _ < n; ++_) {
        points.clear();
        scanf("%d", &m);
        for (int _ = 0; _ < m; ++_) {
            double x, y;
            scanf("%lf %lf", &x, &y);
            points.push_back(Point(x, y));
        }

        points.push_back(points.front());
        for (size_t i = 0; i < points.size() - 1; ++i) {
            lines.push_back(Line(points[i], points[i + 1] - points[i]));
        }
    }

    sort(lines.begin(), lines.end());
    Q.push_back(lines.front());
    for (size_t i = 1; i < lines.size(); i++) {
        while (sec.size() && !is_on_left(lines[i], sec.back())) {
            Q.pop_back();
            sec.pop_back();
        }

        while (sec.size() && !is_on_left(lines[i], sec.front())) {
            Q.pop_front();
            sec.pop_front();
        }

        Q.push_back(lines[i]);

        if (abs(cross_product(Q.back().v, Q[Q.size() - 2].v)) < eps) {
            Q.pop_back();
            if (is_on_left(Q.back(), lines[i].p)) { Q.back() = lines[i]; }
        } else 

        if (Q.size() >= 2) { sec.push_back(get_insertion(Q.back(), Q[Q.size() - 2])); }
    }

    while (sec.size() && !is_on_left(Q.front(), sec.back())) {
        Q.pop_back();
        sec.pop_back();
    }

    sec.push_back(get_insertion(Q.front(), Q.back()));
    sec.push_back(sec.front());

    double ans = 0;
    Point o(0, 0);

    for (size_t i = 0; i < sec.size() - 1; ++i) {
        ans += cross_product(sec[i], sec[i + 1]);
    }

    printf("%.3lf\n", ans / 2);
    return 0;
}