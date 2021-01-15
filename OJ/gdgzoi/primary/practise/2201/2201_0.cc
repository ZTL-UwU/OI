#include <iostream>

const int MAX_N = 1e6 + 10;

long long int phi[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (phi[i] == 0)
        {
            for (int j = i; j <= n; j += i)
            {
                if (phi[j] == 0)
                    phi[j] = j;
                phi[j] = phi[j] * (i - 1) / i;
            }
        }
    }

    for (int i = 1; i <= n; i++)
        std::cout << phi[i] << "\n";
    return 0;
}