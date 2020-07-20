#include <iostream>
#include <string>
#include <vector>
using namespace std;
class huge_int {
    public:
    string bits;
    void flip(string &a) {
        for (int i = 0; i < a.size() / 2; i++)
            swap(a[i], a[a.size() - i - 1]);
    }
    huge_int operator+(huge_int x) {
        huge_int res;
        string a = this->bits, b = x.bits;
        if (b.size() > a.size()) swap(a, b);
        res.bits = a;
        while (a.size() - b.size())
            b = "0" + b;
        flip(a), flip(b);
        int carry = 0;
        for (int i = 0; i < a.size(); i++) {
            int bit = a[i] + b[i] - 2 * '0' + carry;
            res.bits[i] = (bit % 10) + '0';
            carry = bit / 10;
        }
        if (carry) res.bits += (carry + '0');
        flip(res.bits);
        return res;
    }
    int operator[](int x) {
        return this->bits[x] - '0';
    }
    friend ostream &operator<<(ostream &os, const huge_int &x) {
        os << x.bits;
        return os;
    }
};
int main() {
    int n, m;
    cin >> n >> m;

    return 0;
}