#include <iostream>
#include <vector>

const int MAX_N = 1e4 + 10;
int a[MAX_N];
int ans = 0;

void merge(int l, int r)
{
    const int mid = (l + r) / 2;

    int i = l;
    int j = mid + 1;

    std::vector<int> res;

    while (i <= mid && j <= r)
    {
        if (i <= mid && a[i] <= a[j])
        {
            res.push_back(a[i]);
            i++;
        }
        else
        {
            ans += mid - i + 1;
            res.push_back(a[j]);
            j++;
        }
    }

    while (i <= mid)
        res.push_back(a[i++]);
    while (j <= r)
        res.push_back(a[j++]);

    for (std::size_t _i = 0; _i < res.size(); _i++)
        a[l + _i] = res[_i];
}

void dfs(int l, int r)
{
    if (r - l + 1 <= 1)
        return;

    const int mid = (l + r) / 2;
    dfs(l, mid);
    dfs(mid + 1, r);

    merge(l, r);
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    dfs(0, n - 1);

    std::cout << ans;
    return 0;
}
