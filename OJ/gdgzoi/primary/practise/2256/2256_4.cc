#include <algorithm>
#include <iostream>
#include <vector>
namespace query
{
    std::vector<int> v;
    int q, minn, ans;
    inline void I(int k)
    {
        if (k < minn)
            return;
        v.insert(std::lower_bound(v.begin(), v.end(), k), k);
    }
    inline void A(int k)
    {
        for (int i = 0; i < v.size(); i++)
            v[i] += k;
    }
    inline void S(int k)
    {
        for (int i = 0; i < v.size(); i++)
        {
            v[i] -= k;
            if (v[i] < minn)
            {
                v.erase(std::lower_bound(v.begin(), v.end(), v[i]));
                ans++;
                i--;
            }
        }
    }
    inline int F(int k)
    {
        if (k > v.size())
            return -1;
        return v[v.size() - k];
    }
} // namespace query
using namespace query;
int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    std::cin >> q >> minn;
    for (int i = 0; i < q; i++)
    {
        char type;
        int k;
        std::cin >> type >> k;
        switch (type)
        {
            case 'I':
                query::I(k);
                break;

            case 'A':
                query::A(k);
                break;

            case 'S':
                query::S(k);
                break;

            case 'F':
                std::cout << query::F(k) << "\n";
                break;

            default:
                break;
        }
    }
    std::cout << query::ans;
    return 0;
}