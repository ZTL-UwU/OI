#include <algorithm>
#include <iostream>
#include <cmath>

struct vec2
{
    int x;
    int y;
};

long long sqr(int num) { return 1LL * num * num; }

double dis(vec2 p1, vec2 p2) { return std::sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y)); }

struct triangle
{
    vec2 p[3];
    double len[3];

    triangle()
    {
        for (int i = 0; i < 3; i++)
            std::cin >> p[i].x >> p[i].y;
        for (int i = 0; i < 3; i++)
            len[i] = dis(p[i], p[(i + 1) % 3]);
        std::sort(len, len + 3);
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        triangle t1;
        triangle t2;

        if (t1.len[0] * t2.len[1] != t1.len[1] * t2.len[0] || t1.len[1] * t2.len[2] != t1.len[2] * t2.len[1]
            || t1.len[2] * t2.len[0] != t1.len[0] * t2.len[2])
            std::cout << "NO\n";
        else
            std::cout << "YES\n";
    }

    return 0;
}
