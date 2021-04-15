#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>

const int INF = 0x7fffffff;
const int MAX_N = 1e3 + 10;

struct cord
{
    int x, y;
};

int a[MAX_N][MAX_N];
int b[MAX_N][MAX_N];
int c[MAX_N][MAX_N];
int rr[MAX_N];
int cc[MAX_N];

std::unordered_map<int, std::vector<cord>> hash;
std::vector<int> v;

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> a[i][j];
            v.push_back(a[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rr[i] += a[i][j];
            cc[i] += a[j][i];
        }
    }

    std::sort(v.begin(), v.end());

    for (auto val : v)
    {
        for (auto cd : hash[val])
        {
            int x_sat = 0;
            int y_sat = 0;

            for (int i = 0; i < n; i++)
            {
                if (a[cd.x][i] == INF)
                    x_sat += b[cd.x][i];
                if (a[cd.x][i] != INF)
                {
                    x_sat = INF;
                    break;
                }
            }

            if (x_sat == INF)
            {
                for (int i = 0; i < n; i++)
                {
                    if (a[i][cd.y] == INF)
                        y_sat += b[i][cd.y];
                    if (a[i][cd.y] != INF)
                    {
                        y_sat = INF;
                        break;
                    }
                }
            }

            if (x_sat != INF)
            {
                b[cd.x][cd.y] = rr[cd.x] - x_sat;
                c[cd.x][cd.y] = a[cd.x][cd.y] - b[cd.x][cd.y];
                a[cd.x][cd.y] = INF;
                continue;
            }
            if (y_sat != INF)
            {
                b[cd.x][cd.y] = cc[cd.y] - y_sat;
                c[cd.x][cd.y] = a[cd.x][cd.y] - b[cd.x][cd.y];
                a[cd.x][cd.y] = INF;
                continue;
            }

            b[cd.x][cd.y] = a[cd.x][cd.y];
            c[cd.x][cd.y] = 0;
            a[cd.x][cd.y] = INF;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            std::cout << b[i][j] << " ";
        std::cout << "\n";
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            std::cout << b[i][j] << " ";
        std::cout << "\n";
    }
    return 0;
}