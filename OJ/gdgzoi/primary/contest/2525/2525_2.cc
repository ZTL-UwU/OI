#include <array>
#include <iostream>
#include <vector>

struct point
{
    int x, y;
};

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<point> black;
    black.resize(n);
    std::vector<point> red;
    red.resize(m);

    for (int i = 0; i < n; i++)
        std::cin >> black[i].x >> black[i].y;
    for (int i = 0; i < m; i++)
        std::cin >> red[i].x >> red[i].y;

    int l = 0;
    int r = 3e4; // math.sqrt(40000 ** 2 * 2) / 2 = 28284.27;
    return 0;
}