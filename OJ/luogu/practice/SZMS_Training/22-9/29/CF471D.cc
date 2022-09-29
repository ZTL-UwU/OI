#include <iostream>
#include <vector>

const int MAX_N = 2e5 + 10;
std::vector<int> diff1;
std::vector<int> diff2;
int a[MAX_N];
int b[MAX_N];

int next[MAX_N];
int last[MAX_N];

void get_next()
{
    int j = 0;
    int k = -1;
    next[0] = -1;
    while (j < diff2.size())
    {
        if (k == -1 || diff2[j] == diff2[k])
            next[++j] = ++k;
        else
            k = next[k];
    }
}

int kmp()
{
    int ans = 0;
    int i = 0;
    int j = 0;
    while (i < diff1.size())
    {
        if (j == -1 || diff1[i] == diff2[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];
        if (j == diff2.size())
        {
            ans++;
            j = next[j];
            // j = last[st[top]];
        }
    }

    return ans;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    if (m == 1)
    {
        std::cout << n;
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
        if (i > 0)
            diff1.push_back(a[i] - a[i - 1]);
    }

    for (int i = 0; i < m; i++)
    {
        std::cin >> b[i];
        if (i > 0)
            diff2.push_back(b[i] - b[i - 1]);
    }

    get_next();
    std::cout << kmp();
    return 0;
}