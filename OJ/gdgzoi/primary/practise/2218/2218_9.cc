#include <iostream>

const int MAX_N = 1e5 + 10;

int n;
int a[MAX_N];
int b[MAX_N];
int pos[MAX_N];

namespace hp
{
    int base[MAX_N];
    int rev[MAX_N];

    void swap(int x, int y)
    {
        std::swap(base[x], base[y]);
        std::swap(rev[x], rev[y]);
    }

    void roll_down()
    {
        int u = 0;
        while (u * 2 < n)
        {
            int v = u * 2;

            if (v + 1 < n && base[v] > base[v + 1])
                v++;
            if (base[v] < base[u])
            {
                swap(u, v);
                u = v;
            }
            else
                break;
        }
    }
} // namespace hp

int main()
{
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    for (int i = 0; i < n; i++)
        std::cin >> b[i];
    for (int i = 0; i < n; i++)
    {
        hp::base[i] = a[i] + b[0];
        hp::rev[i] = i;
        pos[i] = 0;
    }

    for (int _i = 0; _i < n; _i++)
    {
        std::cout << hp::base[0] << " ";
        int index = hp::rev[0];
        hp::base[0] = a[index] + b[++pos[index]];

        hp::roll_down();
    }
    return 0;
}