#include <iostream>
#include <string>

// Huge_int by ZTL
class huge_int
{
private:
    std::string bits;
    bool positive;
    void flip(std::string &str)
    {
        for (int i = 0; i < str.size() / 2; i++)
            std::swap(str[i], str[str.size() - i - 1]);
    }
    bool bigger(std::string a, std::string b)
    {
        if (a.size() != b.size())
            return a.size() > b.size();
        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i])
                return a[i] > b[i];
        return false;
    }
    bool smaller(std::string a, std::string b)
    {
        if (a.size() != b.size())
            return a.size() < b.size();
        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i])
                return a[i] < b[i];
        return false;
    }
    // Add
    std::string add(std::string a, std::string b)
    {
        if (b.size() > a.size())
            swap(a, b);
        std::string c = a;
        while (a.size() - b.size() > 0)
            b = "0" + b;
        flip(a);
        flip(b);
        int carry = 0;
        for (int i = 0; i < a.size(); i++)
        {
            int tmp = a[i] - '0' + b[i] - '0' + carry;
            c[i] = (tmp % 10) + '0';
            carry = tmp / 10;
        }
        if (carry)
            c += (carry + '0');
        flip(c);
        return c;
    }
    // Difference
    std::string diff(std::string a, std::string b)
    {
        if (bigger(b, a))
            swap(a, b);
        std::string c = a;
        while (a.size() > b.size())
            b = "0" + b;
        flip(a);
        flip(b);
        int carry = 0;
        for (int i = 0; i < a.size(); i++)
        {
            int tmp = a[i] - b[i] - carry;
            a[i] += (tmp < 0 ? 10 : 0);
            c[i] = a[i] - b[i] - carry + '0';
            carry = (tmp < 0 ? 1 : 0);
        }
        int k = 0;
        while (c[c.size() - k - 1] == '0')
            k++;
        c = c.substr(0, c.size() - k);
        flip(c);
        if (c.size() == 0)
            c = "0";
        return c;
    }

public:
    huge_int()
    {
        positive = true;
    }
    // Get huge_int's lenth
    int size()
    {
        return bits.size();
    }
    // Clear huge_int
    void clear()
    {
        this->bits.clear();
        this->bits.shrink_to_fit();
        this->positive = true;
    }
    // Convert int to huge_int
    void convert_int(int x)
    {
        huge_int res;
        if (x < 0)
        {
            this->positive = false;
            x = -x;
        }
        else
            this->positive = true;
        while (x)
        {
            std::string tmp = "#";
            tmp[0] = x % 10 + '0';
            this->bits = tmp + this->bits;
            x /= 10;
        }
    }
    // Convert long long to huge_int
    void convert_long_long(long long x)
    {
        huge_int res;
        if (x < 0)
        {
            this->positive = false;
            x = -x;
        }
        else
            this->positive = true;
        while (x)
        {
            std::string tmp = "#";
            tmp[0] = x % 10 + '0';
            this->bits = tmp + this->bits;
            x /= 10;
        }
    }
    // Operator >
    bool operator>(const huge_int x)
    {
        if (this->positive != x.positive)
            return this->positive > x.positive;
        else
        {
            if (this->positive == 1)
                return bigger(this->bits, x.bits);
            else
                return smaller(this->bits, x.bits);
        }
        return false;
    }
    // Operator <
    bool operator<(const huge_int x)
    {
        if (this->positive != x.positive)
            return this->positive < x.positive;
        else
        {
            if (this->positive == 1)
                return smaller(this->bits, x.bits);
            else
                return bigger(this->bits, x.bits);
        }
        return false;
    }
    // Operator ==
    bool operator==(const huge_int x)
    {
        if (this->positive != x.positive)
            return false;
        if (this->bits.size() != x.bits.size())
            return false;
        for (int i = 0; i < this->bits.size(); i++)
            if (this->bits[i] != x.bits[i])
                return false;
        return true;
    }
    // Operator !=
    bool operator!=(const huge_int x)
    {
        if (this->positive != x.positive)
            return true;
        if (this->bits.size() != x.bits.size())
            return true;
        for (int i = 0; i < this->bits.size(); i++)
            if (this->bits[i] != x.bits[i])
                return true;
        return false;
    }
    // Operator =
    huge_int &operator=(huge_int x)
    {
        this->bits = x.bits;
        this->positive = x.positive;
        return *this;
    }
    // Operator []
    int operator[](const int x)
    {
        if (x >= this->bits.size())
        {
            std::cerr << "huge_int:\n";
            std::cerr << "int &Operator[int x]\n";
            std::cerr << "              ^~~~~\n";
            std::cerr << "x > this->bits.size()\n";
            return -1;
        }
        return this->bits[x] - '0';
    }
    // Operator <<
    friend std::ostream &operator<<(std::ostream &os, const huge_int &x)
    {
        if (x.positive == false)
            os << '-' << x.bits;
        else
            os << x.bits;
        return os;
    }
    // Operator >>
    friend std::istream &operator>>(std::istream &is, huge_int &x)
    {
        is >> x.bits;
        x.positive = true;
        if (x.bits[0] == '-')
        {
            x.bits = x.bits.substr(1, x.bits.size() - 1);
            x.positive = false;
        }
        else if (x.bits[0] == '+')
        {
            x.bits = x.bits.substr(1, x.bits.size() - 1);
            x.positive = true;
        }
        return is;
    }
    // Operator +
    huge_int operator+(const huge_int x)
    {
        huge_int res;
        if (this->positive == x.positive)
        {
            res.bits = add(this->bits, x.bits);
            if (this->positive == 1)
                res.positive = true;
            else
                res.positive = false;
        }
        else
        {
            res.bits = diff(this->bits, x.bits);
            if (this->positive == 1)
            {
                if (smaller(this->bits, x.bits))
                    res.positive = false;
                else
                    res.positive = true;
            }
            else
            {
                if (bigger(this->bits, x.bits))
                    res.positive = false;
                else
                    res.positive = true;
            }
        }
        return res;
    }
    // Operator -
    huge_int operator-(const huge_int x)
    {
        huge_int res;
        if (this->positive == x.positive)
        {
            res.bits = diff(this->bits, x.bits);
            if (this->positive == 1)
            {
                if (smaller(this->bits, x.bits))
                    res.positive = false;
                else
                    res.positive = true;
            }
            else
            {
                if (bigger(this->bits, x.bits))
                    res.positive = false;
                else
                    res.positive = true;
            }
        }
        else
        {
            res.bits = add(this->bits, x.bits);
            if (this->positive == 1)
                res.positive = true;
            else
                res.positive = false;
        }
        return res;
    }
};