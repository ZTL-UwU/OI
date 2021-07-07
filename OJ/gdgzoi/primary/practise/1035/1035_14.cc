#include <iostream>
#include <deque>

const int MAX_N = 1e6 + 10;

int val[MAX_N];
int n, k;

void query(const bool min)
{
    std::deque<int> dq;
    for (int i = 0; i < n; i++)
    {
        while (!dq.empty() && i - dq.front() + 1 > k)
            dq.pop_front();

        while (!dq.empty() && (min ? val[dq.back()] > val[i] : val[dq.back()] < val[i]))
            dq.pop_back();

        dq.push_back(i);
        if (i >= k - 1)
            std::cout << val[dq.front()] << " ";
    }
}

int main()
{
    std::cin >> n >> k;
    for (int i = 0; i < n; i++)
        std::cin >> val[i];

    query(true);
    std::cout << "\n";
    query(false);
    return 0;
}
