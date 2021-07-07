#include <unordered_set>
#include <iostream>

std::unordered_set<int> mod_system;

int main()
{
    int tmp_a, tmp_b;
    std::cin >> tmp_a >> tmp_b;

    const int a = std::min(tmp_a, tmp_b);
    const int b = std::max(tmp_a, tmp_b);

    const int mod = b % a;
    int mod_step = 0;
    int last = 0;
    // int overflow = 0;
    while (mod_system.size() != a)
    {
        last = (mod * mod_step) % a;
        // overflow = (mod * mod_step) / a;

        mod_system.insert((mod * mod_step) % a);
        mod_step++;
    }

    // const int div = b / a;

    std::cout << (long long int)(mod_step - 1) * b - a;
    return 0;
}