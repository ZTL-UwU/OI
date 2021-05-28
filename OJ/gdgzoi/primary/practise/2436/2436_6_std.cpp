#include <cstdio>
#include <cstring>
#include <algorithm>

#define STEP 10000
using namespace std;

struct interger
{
    int *d;
    int len;

    interger()
    {
        d = new int[5000];
        memset(d, 0, sizeof(d));
        len = 0;
    }

    ~interger() { delete[] d; }

    int &operator[](const int &x) const { return d[x]; }
};

/*
1: a > b
-1: a < b
0: a = b
*/
int cmp(interger &a, interger &b)
{
    if (a.len > b.len)
        return 1;
    else if (b.len > a.len)
        return -1;
    else
    {
        for (int i = a.len; i >= 1; --i)
        {
            if (a[i] > b[i])
                return 1;
            else if (a[i] < b[i])
                return -1;
        }
    }

    return 0;
}

// add a + b
void mul2(interger &a)
{
    int len = a.len;
    for (int i = len; i >= 1; --i)
    {
        a[i] *= 2;
        if (a[i] >= STEP)
        {
            a[i] -= STEP;
            ++a[i + 1];
        }
        if (a[a.len + 1])
            a.len++;
    }
    for (int i = 1; i <= len; ++i)
    {
        if (a[i] >= STEP)
        {
            a[i] -= STEP;
            a[i + 1]++;
            if (a[a.len + 1])
                a.len++;
        }
    }
}

// calc a - b
void sub(interger &a, const interger &b)
{
    dbg(a);
    dbg(b);
    for (int i = 1; i <= b.len; ++i)
    {
        a[i] -= b[i];
        if (a[i] < 0)
        {
            a[i] += STEP;
            --a[i + 1];
        }
        if (!a[a.len])
            a.len--;
    }

    // for (int i = 1; i <= a.len; ++i) {
    // }

    // while (a.len > 1 && a[a.len] == 0) {
    // 	--a.len;
    // }
}

void div2(interger &a)
{
    for (int i = a.len; i >= 1; --i)
    {
        if (a[i] % 2 == 1)
        {
            a[i - 1] += STEP;
        }
        a[i] /= 2;
        if (!a[a.len])
            a.len--;
    }

    // while (a.len > 1 && a[a.len] == 0) --a.len;
}

// bool iszero(const interger &a) {
// 	return (a.len == 0 || (a.len == 1 && a[1] == 0));
// }

void input(interger &a)
{
    char *s = new char[100001];
    scanf("%s", s);
    int ss = 0, len = strlen(s);
    int sum = 0;
    for (int i = len - 1; i >= 0; --i)
    {
        int h = s[i] - '0';

        for (int j = 0; j < ss; ++j)
        {
            h *= 10;
        }
        sum += h;
        ++ss;

        if (ss == 4)
        {
            ss = 0;
            a[++a.len] = sum;
            sum = 0;
        }
    }

    if (sum != 0)
    {
        a[++a.len] = sum;
    }
}

void output(const interger &a)
{
    printf("%d", a[a.len]);
    for (int i = a.len - 1; i >= 1; --i)
    {
        printf("%04d", a[i]);
    }
}

void int_copy(interger &a, const interger &b)
{
    a.len = b.len;
    memset(a.d, 0, sizeof(a.d));
    for (int i = 1; i <= a.len; ++i)
    {
        a[i] = b[i];
    }
}

void gcd(interger &a, interger &b, interger &res)
{
    int two1, two2;
    for (two1 = 0; !(a[1] % 2); ++two1)
        div2(a);
    for (two2 = 0; !(b[1] % 2); ++two2)
        div2(b);
    two1 = min(two1, two2);
    while (1)
    {
        int compres = cmp(a, b);
        if (compres == 0)
        {
            for (int i = 0; i < two1; ++i)
            {
                mul2(a);
            }
            int_copy(res, a);
            return;
        }
        else if (compres == -1)
        {
            interger tmp;
            int_copy(tmp, a);
            int_copy(a, b);
            int_copy(b, tmp);
        }
        sub(a, b);
        while (!(a[1] % 2))
            div2(a);
    }
}

int main()
{
    interger a, b, c;
    input(a);
    input(b);
    gcd(a, b, c);
    // sub(a, b);
    output(a);
    printf("\n");
    return 0;
}
