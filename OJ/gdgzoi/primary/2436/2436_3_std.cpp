#include <bits/stdc++.h>
using namespace std;

struct Data {
    int a[3005];
    int num;
};

Data div2(Data x) {
    for (int i = x.num; i >= 1; i--) {
        if (x.a[i] & 1)
            x.a[i - 1] += 10;
        x.a[i] >>= 1;
        if (!x.a[x.num])
            x.num--;
    }
    return x;
}

bool comp(Data &x, Data &y) {
    if (x.num > y.num)
        return false;
    if (x.num < y.num) {
        swap(x.num, y.num);
        for (int i = 1; i <= max(x.num, y.num); i++) swap(x.a[i], y.a[i]);
        return false;
    }
    for (int i = x.num; i >= 1; i--) {
        if (x.a[i] > y.a[i])
            return false;
        if (x.a[i] < y.a[i]) {
            swap(x.num, y.num);
            for (int i = 1; i <= max(x.num, y.num); i++) swap(x.a[i], y.a[i]);
            return false;
        }
    }
    return true;
}

Data plus2(Data x) {
    for (int i = 1; i <= x.num; i++) x.a[i] <<= 1;
    for (int i = 1; i < x.num; i++) {
        if (x.a[i] > 9) {
            x.a[i + 1]++;
            x.a[i] -= 10;
        }
    }
    if (x.a[x.num] > 9) {
        x.a[x.num + 1] = 1;
        x.a[x.num] -= 10;
        x.num++;
    }
    return x;
}

Data sub(Data x, Data y) {
    for (int i = 1; i <= y.num; i++) x.a[i] -= y.a[i];
    for (int i = 1; i < x.num; i++) {
        if (x.a[i] < 0) {
            x.a[i + 1]--;
            x.a[i] += 10;
        }
    }
    if (x.a[x.num] == 0)
        x.num--;
    return x;
}

int main() {
    Data n, m, ans;
    char c1[3005], c2[3005];
    cin >> c1 >> c2;
    n.num = strlen(c1);
    m.num = strlen(c2);
    for (int i = 0; i < n.num; i++) n.a[n.num - i] = c1[i] - '0';
    for (int i = 0; i < m.num; i++) m.a[m.num - i] = c2[i] - '0';
    int x = 0, y = 0;
    for (; !(n.a[1] & 1); x++) n = div2(n);
    for (; !(m.a[1] & 1); y++) m = div2(m);
    if (y < x)
        x = y;
    int times = 0;
    while (1) {
        cout << ++ times << " ";
        if (comp(n, m)) {
            while (x--) n = plus2(n);
            for (int i = n.num; i >= 1; i--) cout << "\n" << n.a[i] << "\n";
            return 0;
        }
        n = sub(n, m);
        while (!(n.a[1] & 1)) n = div2(n);
    }
}
