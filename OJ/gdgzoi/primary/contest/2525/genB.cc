#include <cstdio>
#include <functional>
#include <vector>
#include <random>

#define loop(x) for(int _=0;_<(x);++_)
using namespace std;

random_device rd;
mt19937 raw_rand(rd());

int mkrand(int, int);

struct range {
    int l;
    int r;
    range() {}
    range(int x, int y) {
        l = x;
        r = y;
    }

    static range make(int l, int r) {
        int x = mkrand(l, r);
        int y = mkrand(l, r);
        if (x > y) {
            swap(x, y);
        }
        printf("%d %d ", x, y);
        return {x, y};
    }
};

int mkrand(int l, int r) {
    return raw_rand() % (r - l + 1) + l;
}

int randint(int l, int r) {
    int x = mkrand(l, r);
    printf("%d ", x);
    return x;
}

void choice(vector<function<void()>> f) {
    int x = mkrand(0, f.size() - 1);
    f[x]();
}

void ln() {
    printf("\n");
}

void p(int x) {
    printf("%d ", x);
}

int main() {
    int n = randint(5, 10);
    int m = randint(2, 6);
    ln();

    loop(n) {
        randint(0, 1);
    }
    ln();

    loop(n) {
        randint(0, 100);
    }
    ln();

    loop(m) {
        choice({[=]() {
            p(1);
            randint(1, n);
        }, [=]() {
        	p(2);
        	range::make(1, n);
        }, [=]() {
        	p(3);
        	range::make(1, n);
        }});
        ln();
    }
    return 0;
}