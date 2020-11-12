#include <iostream>
#include <cmath>

const int MAX_M = 2e6;
const int MAX_FOOD = 1e8 + 10;

unsigned long long int animal_bin;
unsigned long long int food_bin;

std::pair<int, int> pq[MAX_M];
bool food[MAX_FOOD];

int main()
{
    int n, m, c, k;
    std::cin >> n >> m >> c >> k;

    for (int i = 0; i < n; i++)
    {
        unsigned long long int a;
        std::cin >> a;
        animal_bin |= a;
    }

    for (int i = 0; i < m; i++)
        std::cin >> pq[i].first >> pq[i].second;

    for (int i = 0; i < m; i++)
        if (animal_bin & (1ULL << pq[i].first))
            food[pq[i].second] = true;

    for (int i = 0; i < m; i++)
        if (not food[pq[i].second])
            food_bin |= (1ULL << pq[i].first);

    int res = 0;
    for (int i = 0; i < k; i++)
        if (not(food_bin & (1ULL << i)))
            res++;

    if (res == 64)
        std::cout << 18446744073 << 709551616 - n;
    else
        std::cout << (1ULL << res) - (1ULL * n);
    return 0;
}