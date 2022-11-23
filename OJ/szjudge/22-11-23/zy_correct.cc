#include <iostream>

const int MAX_M = 1e6 + 10;
int w[MAX_M];

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::string s;
    std::cin >> s;

    for (int i = 0; i < m; i++)
        w[i] = s[i] - '0';
    for (std::size_t i = m; i < s.size(); i++)
        w[i % m] ^= s[i] - '0';

    int sum = 0;
    for (int i = 0; i < m; i++)
        sum += w[i];

    std::cout << n - std::min(sum, m - sum);
    return 0;
}