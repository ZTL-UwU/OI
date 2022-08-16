#include <iostream>
#include <vector>
#include <cmath>

const int MAX_N = 3e5 + 10;
const int MAX_LOG = 20;

int base[MAX_N][MAX_LOG];
std::vector<int> peak;
int a[MAX_N];
int n;

class RMQ
{
public:
    void init(int key, int val) { base[key][0] = val; }

    void build()
    {
        for (int i = 1; i <= std::log2(n); i++)
            for (int j = 1; j + (1 << i) - 1 <= n; j++)
                base[j][i] = std::max(base[j][i - 1], base[j + (1 << (i - 1))][i - 1]);
    }

    int query(int l, int r)
    {
        const int k = std::log2(r - l + 1);
        return std::max(base[l][k], base[r - (1 << k) + 1][k]);
    }
};

int main()
{
    std::cin >> n;
    long long ans = (n - 1) * 2;
    RMQ rmq;

    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        rmq.init(i, a[i]);
    }
    rmq.build();

    for (int i = 1; i <= n; i++)
        if ((a[i - 1] < a[i] || i == 1) && (a[i + 1] < a[i] || i == n))
            peak.push_back(i);
    // for (auto i : peak)
    //     std::cout << i << " ";
    // return 0;

    for (int i = 0; i < peak.size() - 1; i++)
    {
        long long cnt = 0;
        const int ll = peak[i];
        const int rr = peak[i + 1];
        for (int j = ll; j <= rr - 2; j++)
            for (int k = j + 2; k <= rr; k++)
                if (rmq.query(j + 1, k - 1) < a[j] && rmq.query(j + 1, k - 1) < a[k])
                    cnt += k - j + 1;
        ans += cnt;

        for (int j = i + 2; j < peak.size(); j++)
        {
            const int l = peak[i];
            const int r = peak[j];
            const int max = rmq.query(l + 1, r - 1);

            if (max < a[l] && max < a[r])
            {
                int l_cnt = 0;
                int r_cnt = 0;
                for (int k = l; a[k] > max; k++)
                    l_cnt++;
                for (int k = r; a[k] > max; k--)
                    r_cnt++;

                for (int ii = l; ii < l + l_cnt; ii++)
                    for (int jj = r; jj > r - l_cnt; jj--)
                        ans += jj - ii + 1;
            }
        }
    }

    std::cout << ans;
    return 0;
}
