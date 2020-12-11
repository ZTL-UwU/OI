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
    huge_int(const std::bitset<Size> &bitset_src);

    template <typename T>
    void operator=(const T &src);

    bool operator==(const huge_int<Size> &huge_int_num) const;
    bool operator!=(const huge_int<Size> &huge_int_num) const;

    bool operator<(const huge_int<Size> &huge_int_num) const;
    bool operator>(const huge_int<Size> &huge_int_num) const;

    bool operator<=(const huge_int<Size> &huge_int_num) const;
    bool operator>=(const huge_int<Size> &huge_int_num) const;

    huge_int<Size> operator+(const huge_int<Size> &huge_int_num);
    void operator+=(const huge_int<Size> &huge_int_num);

    huge_int<Size> operator-();
    huge_int<Size> operator-(const huge_int<Size> &huge_int_num) const;
    void operator-=(const huge_int<Size> &huge_int_num);

    huge_int<Size> operator*(huge_int<Size> huge_int_num);
    void operator*=(const huge_int<Size> &huge_int_num);

    std::string to_string();
    std::bitset<Size> huge_int_base;

private:
};

template <size_t Size>
huge_int<Size>::huge_int()
{
}

template <size_t Size>
huge_int<Size>::huge_int(const std::bitset<Size> &bitset_src)
{
    this->huge_int_base = bitset_src;
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
template <typename T>
void huge_int<Size>::operator=(const T &src)
{
    this->huge_int_base = std::bitset<Size>(src);
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator+(const huge_int<Size> &huge_int_num)
{
    huge_int a(this->huge_int_base ^ huge_int_num.huge_int_base);
    huge_int b((this->huge_int_base & huge_int_num.huge_int_base) << 1);

    return huge_int_num.huge_int_base.any() ? a + b : a;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator-()
{
    return huge_int(std::bitset<Size>(1)) + huge_int(~this->huge_int_base);
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator-(const huge_int<Size> &huge_int_num) const
{
    return *this + (-huge_int_num);
}

template <size_t Size>
void huge_int<Size>::operator+=(const huge_int<Size> &huge_int_num)
{
    huge_int<Size> res = (*this + huge_int_num);
    this->huge_int_base = res.huge_int_base;
}

template <size_t Size>
void huge_int<Size>::operator-=(const huge_int<Size> &huge_int_num)
{
    huge_int<Size> res = *this - huge_int_num;
    this->huge_int_base = res.huge_int_base;
}

template <size_t Size>
huge_int<Size> huge_int<Size>::operator*(huge_int<Size> huge_int_num)
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
std::string huge_int<Size>::to_string()
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

int main()
{
    huge_int<128> a;
    huge_int<128> b;

    a = 100;
    b = 20;

    std::cout << (a + b).to_string();
    return 0;
}