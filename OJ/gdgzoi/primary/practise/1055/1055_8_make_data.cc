#include <algorithm>
#include <iostream>
#include <cstdlib>

const int MAX_N = 1e5;

unsigned int random(int max) { return (1LL * rand() * rand()) % max + 1; }
int a[MAX_N];

int main(int argv, char **args)
{
    srand(std::atoi(args[1]));
    int n, q;
    n = random(MAX_N);
    q = random(MAX_N);
    std::cout << n << " " << q << "\n";

    for (int i = 0; i < n; i++)
        a[i] = (random(2) == 1 ? 1 : -1) * random(MAX_N);
    std::sort(a, a + n);
    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << "\n";

    for (int i = 0; i < q; i++)
    {
        int l = random(n);
        int r = random(n);
        if (l > r)
            std::swap(l, r);
        std::cout << l << " " << r << "\n";
    }
    std::cout << "0\n";

    return 0;
}