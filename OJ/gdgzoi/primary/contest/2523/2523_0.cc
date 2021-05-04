#include <algorithm>
#include <iostream>

const int MAX_N = 1e2;

int num[MAX_N];
int n;

int try1()
{
    int sum_a = 0;
    int num_a = 0;
    int sum_b = 0;
    int num_b = 0;

    for (int i = 0; i < n * 2; i++)
    {
        if (num_a == n)
            sum_b += num[i];
        else if (num_b == n)
            sum_a += num[i];
        else
        {
            if (sum_a <= sum_b)
            {
                sum_a += num[i];
                num_a++;
            }
            else
            {
                sum_b += num[i];
                num_b++;
            }
        }
    }

    return std::abs(sum_a - sum_b);
}

int main()
{
    std::cin >> n;

    for (int i = 0; i < n * 2; i++)
        std::cin >> num[i];

    std::sort(num, num + n * 2, std::greater<int>());

    std::cout << try1();
    return 0;
}