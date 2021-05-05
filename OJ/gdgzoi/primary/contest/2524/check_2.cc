#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int MAX_NM = 5e3;

std::unordered_map<int, bool> used;

int main()
{
    std::srand(std::time(0));

    int n = MAX_NM;
    int m = MAX_NM;

    std::cout << n << " " << m << "\n";
    for (int _i = 0; _i < n; _i++)
    {
        const int num = std::rand() % n + 1;
        std::cout << num << " ";
        used[num] = true;
    }

    std::cout << "\n";
    for (int i = 0; i < m; i++)
    {
        int num1 = std::rand() % n + 1;
        while (!used[num1])
            num1 = std::rand() % n + 1;

        int num2 = std::rand() % n + 1;
        while (num2 == num1)
            num2 = std::rand() % n + 1;

        std::cout << num1 << " " << num2 << "\n";
    }
    return 0;
}