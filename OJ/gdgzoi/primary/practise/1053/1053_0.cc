#include <iostream>

const int MAX_N = 3e5 + 10;
int flaw[2 * MAX_N];

int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> flaw[i];
        flaw[n + i] = flaw[i];
    }

    int i = 0;
    int j = 1;
    int k = 0;

    while (i < n && j < n && k < n)
    {
        if (flaw[i + k] == flaw[j + k])
            k++;
        else
        {
            if (flaw[i + k] > flaw[j + k])
                i += k + 1;
            else
                j += k + 1;
            if (i == j)
                j++;
            k = 0;
        }
    }

    for (int l = i; l < i + n; l++)
        std::cout << flaw[l] << " ";
    return 0;
}