#include <iostream>
#include <sstream>
#include <string>

const int MAX_N = 2e4;

int fa[MAX_N];

inline void init()
{
    for (int i = 0; i < MAX_N; i++)
        fa[i] = i;
}

inline int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

inline void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);

    if (fx != fy)
        fa[fx] = fy;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    init();

    int yes = 0;
    int no = 0;
    std::string str;

    bool first_n = true;
    while (std::getline(std::cin, str))
    {
        std::stringstream ss;
        ss << str;

        char opt;
        int x = -1, y = -1;
        ss >> opt >> x >> y;

        if (opt >= '0' and opt <= '9' and (x == -1 or y == -1))
        {
            init();
            if (not first_n)
                std::cout << yes << ", " << no << "\n";
            first_n = false;

            yes = 0;
            no = 0;
            continue;
        }
        else if (x == -1 or y == -1)
        {
            continue;
        }

        if (opt == 'c')
        {
            merge(x, y);
        }
        if (opt == 'q')
        {
            if (find(x) == find(y))
                yes++;
            else
                no++;
        }
    }

    std::cout << yes << ", " << no;
    return 0;
}