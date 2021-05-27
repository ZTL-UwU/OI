#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class vvt
{
private:
    std::vector<T> base;

public:
    vvt(){};
    vvt(std::size_t size) { this->base.reserve(size); }

    void insert(T val) { this->base.insert(std::lower_bound(this->base.begin(), this->base.end(), val), val); }
    void erase(T val) { this->base.erase(std::lower_bound(this->base.begin(), this->base.end(), val)); }

    T operator[](std::size_t rank) { return this->base[rank - 1]; }
    std::size_t rank(T val)
    {
        return std::lower_bound(this->base.begin(), this->base.end(), val) - this->base.begin() + 1;
    }
    T find_pre(T val) { return *--std::lower_bound(this->base.begin(), this->base.end(), val); }
    T find_next(T val) { return *std::upper_bound(this->base.begin(), this->base.end(), val); }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    vvt<int> t(1e5 + 10);
    for (int i = 0; i < n; i++)
    {
        int op, x;
        std::cin >> op >> x;

        if (op == 1)
            t.insert(x);
        else if (op == 2)
            t.erase(x);
        else
        {
            if (op == 3)
                std::cout << t.rank(x);
            else if (op == 4)
            {
                std::cout << t[x];
            }
            else if (op == 5)
                std::cout << t.find_pre(x);
            else if (op == 6)
                std::cout << t.find_next(x);
            std::cout << "\n";
        }
    }
    return 0;
}
