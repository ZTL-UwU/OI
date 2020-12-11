#include <bits/types/error_t.h>
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
    void operator=(const std::string &src);
    void operator=(const int &src);
    void operator=(const unsigned int &src);
    void operator=(const long long int &src);
    void operator=(const unsigned long long int &src);

    huge_int<Size> operator<<(const size_t &position) const;
    void operator<<=(const size_t &position);

    bool operator==(const huge_int<Size> &huge_int_num) const;
    bool operator!=(const huge_int<Size> &huge_int_num) const;

    bool operator<(const huge_int<Size> &huge_int_num) const;
    bool operator>(const huge_int<Size> &huge_int_num) const;

    bool operator<=(const huge_int<Size> &huge_int_num) const;
    bool operator>=(const huge_int<Size> &huge_int_num) const;

    huge_int<Size> operator+(const huge_int<Size> &huge_int_num) const;
    void operator+=(const huge_int<Size> &huge_int_num);
    huge_int<Size> operator+(const unsigned int &num) const;
    void operator+=(const unsigned int &num);
    huge_int<Size> operator+(const unsigned long long int &num) const;
    void operator+=(const unsigned long long int &num);

    huge_int<Size> operator-(const huge_int<Size> &huge_int_num) const;
    void operator-=(const huge_int<Size> &huge_int_num);

    huge_int<Size> operator*(huge_int<Size> huge_int_num) const;
    void operator*=(const huge_int<Size> &huge_int_num);

    huge_int<Size> operator/(const huge_int<Size> &huge_int_num) const;
    void operator/=(const huge_int<Size> &huge_int_num);

    std::string to_string() const;
    unsigned int to_uint() const;
    unsigned long long int to_ullong() const;
    std::string to_bin_string() const;
    std::bitset<Size> to_bitset() const;

private:
    std::bitset<Size> huge_int_base;
};

template <size_t Size>
huge_int<Size>::huge_int()
{
    this->huge_int_base = std::bitset<Size>(0);
}

template <size_t Size>
template <typename T>
huge_int<Size>::huge_int(const T &src)
{
    this->huge_int_base = std::bitset<Size>(src);
}

template <size_t Size>
void huge_int<Size>::operator=(const std::bitset<Size> &src)
{
    this->huge_int_base = src;
}

template <size_t Size>
void huge_int<Size>::operator=(const std::string &src)
{
    huge_int res;
    for (auto ch : src)
        res = huge_int(res.huge_int_base << 3) + huge_int(res.huge_int_base << 1) + huge_int(ch - '0');

    this->huge_int_base = res.huge_int_base;
}

template <size_t Size>
void huge_int<Size>::operator=(const int &src)
{
    *this = std::to_string(src);
}

template <size_t Size>
void huge_int<Size>::operator=(const unsigned int &src)
{
    *this = std::to_string(src);
}

template <size_t Size>
void huge_int<Size>::operator=(const long long int &src)
{
    *this = std::to_string(src);
}

template <size_t Size>
void huge_int<Size>::operator=(const unsigned long long int &src)
{
    *this = std::to_string(src);
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator<<(const size_t &position) const
{
    return this->huge_int_base << position;
}

template <size_t Size>
void huge_int<Size>::operator<<=(const size_t &position)
{
    this->huge_int_base <<= position;
}

template <size_t Size>
bool huge_int<Size>::operator==(const huge_int<Size> &huge_int_num) const
{
    for (auto i = this->huge_int_base.size() - 1; i >= 0; i--)
        if (this->huge_int_base[i] != huge_int_num.huge_int_base[i])
            return false;

    return true;
}

template <size_t Size>
bool huge_int<Size>::operator!=(const huge_int<Size> &huge_int_num) const
{
    if (this == huge_int_num)
        return false;

    return true;
}

template <size_t Size>
bool huge_int<Size>::operator<(const huge_int<Size> &huge_int_num) const
{
    for (auto i = this->huge_int_base.size() - 1; i >= 0; i--)
        if (this->huge_int_base[i] != huge_int_num.huge_int_base[i])
            return this->huge_int_base[i] < huge_int_num.huge_int_base[i];

    return false;
}

template <size_t Size>
bool huge_int<Size>::operator>(const huge_int<Size> &huge_int_num) const
{
    if (this < huge_int_num or this == huge_int_num)
        return false;

    return true;
}

template <size_t Size>
bool huge_int<Size>::operator<=(const huge_int<Size> &huge_int_num) const
{
    if (this < huge_int_num or this == huge_int_num)
        return true;

    return false;
}

template <size_t Size>
bool huge_int<Size>::operator>=(const huge_int<Size> &huge_int_num) const
{
    if (this > huge_int_num or this == huge_int_num)
        return true;

    return false;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator+(const huge_int<Size> &huge_int_num) const
{
    huge_int a(this->huge_int_base ^ huge_int_num.huge_int_base);
    huge_int b((this->huge_int_base & huge_int_num.huge_int_base) << 1);

    return huge_int_num.huge_int_base.any() ? a + b : a;
}

template <size_t Size>
void huge_int<Size>::operator+=(const huge_int<Size> &huge_int_num)
{
    huge_int<Size> res = (*this + huge_int_num);
    this->huge_int_base = res.huge_int_base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator+(const unsigned int &num) const
{
    return *this + huge_int(num);
}

template <size_t Size>
void huge_int<Size>::operator+=(const unsigned int &num)
{
    huge_int<Size> res = (*this + huge_int_num);
    this->huge_int_base = res.huge_int_base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator+(const unsigned long long int &num) const
{
    huge_int a(this->huge_int_base ^ huge_int_num.huge_int_base);
    huge_int b((this->huge_int_base & huge_int_num.huge_int_base) << 1);

    return huge_int_num.huge_int_base.any() ? a + b : a;
}

template <size_t Size>
void huge_int<Size>::operator+=(const unsigned long long int &num)
{
    huge_int<Size> res = (*this + huge_int_num);
    this->huge_int_base = res.huge_int_base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator-(const huge_int<Size> &huge_int_num) const
{
    return *this + (huge_int(std::bitset<Size>(1)) + huge_int(~huge_int_num.huge_int_base));
}

template <size_t Size>
void huge_int<Size>::operator-=(const huge_int<Size> &huge_int_num)
{
    huge_int<Size> res = *this - huge_int_num;
    this->huge_int_base = res.huge_int_base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator*(huge_int<Size> huge_int_num) const
{
    huge_int tmp_this;
    tmp_this = *this;

    huge_int res(std::bitset<Size>(0));
    while (huge_int_num.huge_int_base.any())
    {
        if (huge_int_num.huge_int_base[0])
            res += tmp_this;
        huge_int_num.huge_int_base >>= 1;
        tmp_this += tmp_this;
    }

    return res;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator/(const huge_int<Size> &huge_int_num) const
{
    huge_int<Size> tmp = *this;
    huge_int<Size> res;

    while (tmp > huge_int_num)
    {
        int k = 0;
        for (huge_int c = tmp; tmp >= c; c <<= 1, k++)
            if (tmp < huge_int_num + c)
                res += 1 << k;
    }

    return res;
}

template <size_t Size>
std::string huge_int<Size>::to_string() const
{
    std::string res;
    std::vector<unsigned char> res_v;
    res_v.push_back(0);

    for (auto i = this->huge_int_base.size() - 1; i <= this->huge_int_base.size() - 1; i--)
    {
        int front = this->huge_int_base.test(i);

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

    return this->huge_int_base.to_ulong();
}

template <size_t Size>
unsigned long long int huge_int<Size>::to_ullong() const
{
    if (Size > 64)
        throw std::overflow_error("huge_int size (" + std::to_string(Size) + ") out of unsigned int (64)");

    return this->huge_int_base.to_ullong();
}

template <size_t Size>
std::string huge_int<Size>::to_bin_string() const
{
    return this->huge_int_base.to_string();
}

template <size_t Size>
std::bitset<Size> huge_int<Size>::to_bitset() const
{
    return this->huge_int_base;
}

int main()
{
    huge_int<1024> a;
    huge_int<1024> b;

    a = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
        "1111111111111";
    b = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
        "1111111111100";

    std::cout << (a - b).to_string();
    return 0;
}