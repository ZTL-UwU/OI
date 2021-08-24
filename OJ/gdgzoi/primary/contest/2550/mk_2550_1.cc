#include <iostream>
#include <random>

std::mt19937 rng(std::random_device{}());

int main()
{
    int subtask;
    std::cin >> subtask;

    int t, max;
    if (subtask == 1)
    {
        t = rng() % 10;
        max = rng() % 10 + 1;
    }
    if (subtask == 2)
    {
        t = rng() % 100;
        max = rng() % 50 + 1;
    }
    if (subtask == 3)
    {
        t = rng() % 1000;
        max = rng() % 100 + 1;
    }

    std::cout << t << "\n";
    for (int i = 0; i < t; i++)
    {
        int n = rng() % max + 1;
        std::cout << n << " " << rng() % n << "\n";
    }
    return 0;
}