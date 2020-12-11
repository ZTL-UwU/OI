#include <stdexcept>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>

template <size_t Size>
class huge_int
{
public:
    huge_int();
    template <typename T>
    huge_int(const T &src);

    void operator=(const std::bitset<Size> &src);

    huge_int<Size> operator<<(const size_t &position) const;
    void operator<<=(const size_t &position);
    huge_int<Size> operator>>(const size_t &position) const;
    void operator>>=(const size_t &position);

    bool operator==(const huge_int<Size> &val) const;
    bool operator!=(const huge_int<Size> &val) const;

    bool operator<(const huge_int<Size> &val) const;
    bool operator>(const huge_int<Size> &val) const;

    bool operator<=(const huge_int<Size> &val) const;
    bool operator>=(const huge_int<Size> &val) const;

    huge_int<Size> operator+(const huge_int<Size> &val) const;
    void operator+=(const huge_int<Size> &val);
    huge_int<Size> operator+(const unsigned int &num) const;
    void operator+=(const unsigned int &num);
    huge_int<Size> operator+(const unsigned long long int &num) const;
    void operator+=(const unsigned long long int &num);

    huge_int<Size> operator-(const huge_int<Size> &val) const;
    void operator-=(const huge_int<Size> &val);
    huge_int<Size> operator-(const unsigned int &num) const;
    void operator-=(const unsigned int &num);
    huge_int<Size> operator-(const unsigned long long int &num) const;
    void operator-=(const unsigned long long int &num);

    huge_int<Size> operator*(huge_int<Size> val) const;
    void operator*=(const huge_int<Size> &val);

    huge_int<Size> operator/(const huge_int<Size> &val) const;
    void operator/=(const huge_int<Size> &val);

    std::string to_string() const;
    unsigned int to_uint() const;
    unsigned long long int to_ullong() const;
    std::string to_bin_string() const;
    std::bitset<Size> to_bitset() const;

private:
    std::bitset<Size> _base;
};

template <size_t Size>
huge_int<Size>::huge_int()
{
    this->_base = std::bitset<Size>(0);
}

template <size_t Size>
template <typename T>
huge_int<Size>::huge_int(const T &src)
{
    this->_base = std::bitset<Size>(src);
}

template <size_t Size>
void huge_int<Size>::operator=(const std::bitset<Size> &src)
{
    this->_base = src;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator<<(const size_t &position) const
{
    return this->_base << position;
}

template <size_t Size>
void huge_int<Size>::operator<<=(const size_t &position)
{
    this->_base <<= position;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator>>(const size_t &position) const
{
    return this->_base >> position;
}

template <size_t Size>
void huge_int<Size>::operator>>=(const size_t &position)
{
    this->_base >>= position;
}

template <size_t Size>
bool huge_int<Size>::operator==(const huge_int<Size> &val) const
{
    for (auto i = Size - 1; i <= Size - 1; i--)
        if (this->_base[i] != val._base[i])
            return false;

    return true;
}

template <size_t Size>
bool huge_int<Size>::operator!=(const huge_int<Size> &val) const
{
    if (this == val)
        return false;

    return true;
}

template <size_t Size>
bool huge_int<Size>::operator<(const huge_int<Size> &val) const
{
    for (auto i = Size - 1; i <= Size - 1; i--)
        if (this->_base[i] != val._base[i])
            return this->_base[i] < val._base[i];

    return false;
}

template <size_t Size>
bool huge_int<Size>::operator>(const huge_int<Size> &val) const
{
    if (*this < val or *this == val)
        return false;

    return true;
}

template <size_t Size>
bool huge_int<Size>::operator<=(const huge_int<Size> &val) const
{
    if (*this < val or *this == val)
        return true;

    return false;
}

template <size_t Size>
bool huge_int<Size>::operator>=(const huge_int<Size> &val) const
{
    if (*this > val or *this == val)
        return true;

    return false;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator+(const huge_int<Size> &val) const
{
    huge_int a(this->_base ^ val._base);
    huge_int b((this->_base & val._base) << 1);

    return val._base.any() ? a + b : a;
}

template <size_t Size>
void huge_int<Size>::operator+=(const huge_int<Size> &val)
{
    huge_int<Size> res = (*this + val);
    this->_base = res._base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator+(const unsigned int &num) const
{
    return *this + huge_int(num);
}

template <size_t Size>
void huge_int<Size>::operator+=(const unsigned int &num)
{
    huge_int<Size> res = (*this + num);
    this->_base = res._base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator+(const unsigned long long int &num) const
{
    return *this + huge_int(num);
}

template <size_t Size>
void huge_int<Size>::operator+=(const unsigned long long int &num)
{
    huge_int<Size> res = (*this + num);
    this->_base = res._base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator-(const huge_int<Size> &val) const
{
    return *this + (huge_int(std::bitset<Size>(1)) + huge_int(~val._base));
}

template <size_t Size>
void huge_int<Size>::operator-=(const huge_int<Size> &val)
{
    huge_int<Size> res = *this - val;
    this->_base = res._base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator-(const unsigned int &num) const
{
    return *this - huge_int(num);
}

template <size_t Size>
void huge_int<Size>::operator-=(const unsigned int &num)
{
    huge_int<Size> res = *this - num;
    this->_base = res._base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator-(const unsigned long long int &num) const
{
    return *this - huge_int(num);
}

template <size_t Size>
void huge_int<Size>::operator-=(const unsigned long long int &num)
{
    huge_int<Size> res = *this - num;
    this->_base = res._base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator*(huge_int<Size> val) const
{
    huge_int tmp_this;
    tmp_this = *this;

    huge_int res(std::bitset<Size>(0));
    while (val._base.any())
    {
        if (val._base[0])
            res += tmp_this;
        val._base >>= 1;
        tmp_this += tmp_this;
    }

    return res;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator/(const huge_int<Size> &val) const
{
    huge_int<Size> tmp = *this;
    huge_int<Size> res;

    while (tmp > val)
    {
        int k = 0;
        huge_int c;

        for (c = tmp; tmp >= c; c <<= 1, k++)
        {
            if (tmp < val + c)
            {
                res += (unsigned int)1 << k;
                break;
            }
        }

        if (tmp < val + c)
            break;
        res += (unsigned int)1 << (k - 1);
        tmp -= c >> 1;
    }

    return res;
}

template <size_t Size>
std::string huge_int<Size>::to_string() const
{
    std::string res;
    std::vector<unsigned char> res_v;
    res_v.push_back(0);

    for (auto i = this->_base.size() - 1; i <= this->_base.size() - 1; i--)
    {
        int front = this->_base.test(i);

        for (auto &col : res_v)
        {
            if ((col & 0xf0) >= 0x50)
                col += 0x30;
            if ((col & 0x0f) >= 5)
                col += 3;

            int back = col > 127 ? 1 : 0;
            col <<= 1;
            col |= front;

            front = back;
        }

        if (front ^ 0)
            res_v.push_back(1);
    }

    if (res_v[res_v.size() - 1] & 0xf0)
        res += std::to_string(res_v[res_v.size() - 1] >> 4);

    res += std::to_string(res_v[res_v.size() - 1] & 0x0f);

    if (res_v.size() >= 2)
        for (auto i = res_v.size() - 2; i <= res_v.size() - 2; i--)
            res += std::to_string((res_v[i] & 0xf0) >> 4) + std::to_string(res_v[i] & 0x0f);

    return res;
}

template <size_t Size>
unsigned int huge_int<Size>::to_uint() const
{
    if (Size > 32)
        throw std::overflow_error("huge_int size (" + std::to_string(Size) + ") out of unsigned int (32)");

    return this->_base.to_ulong();
}

template <size_t Size>
unsigned long long int huge_int<Size>::to_ullong() const
{
    if (Size > 64)
        throw std::overflow_error("huge_int size (" + std::to_string(Size) + ") out of unsigned int (64)");

    return this->_base.to_ullong();
}

template <size_t Size>
std::string huge_int<Size>::to_bin_string() const
{
    return this->_base.to_string();
}

template <size_t Size>
std::bitset<Size> huge_int<Size>::to_bitset() const
{
    return this->_base;
}

int main()
{
    huge_int<1024> a;
    huge_int<1024> b;

    a = std::string("10");
    b = std::string("2");

    std::cout << (a == 2);
    return 0;
}