#include <cstdio>
#include <random>
#include <vector>

#include "guess.h"
using namespace std;


mt19937 A623EB95EF17872C1F9FFF6B343D8231_rng(random_device{}());

bool A623EB95EF17872C1F9FFF6B343D8231_ok = false;
int A623EB95EF17872C1F9FFF6B343D8231_cnt = 0;
long long A623EB95EF17872C1F9FFF6B343D8231_a, A623EB95EF17872C1F9FFF6B343D8231_b;

int query(long long x, long long y) {
	A623EB95EF17872C1F9FFF6B343D8231_cnt += 1;

	if (A623EB95EF17872C1F9FFF6B343D8231_cnt > 60000) {
		return -1;
	}
	
	if (x == A623EB95EF17872C1F9FFF6B343D8231_a && y == A623EB95EF17872C1F9FFF6B343D8231_b) {
		A623EB95EF17872C1F9FFF6B343D8231_ok = true;
		return 0;
	}
	
	vector<int> res;
	if (x < A623EB95EF17872C1F9FFF6B343D8231_a) {
		res.push_back(1);
	}
	
	if (y < A623EB95EF17872C1F9FFF6B343D8231_b) {
		res.push_back(2);
	}
	
	if (x > A623EB95EF17872C1F9FFF6B343D8231_a || y > A623EB95EF17872C1F9FFF6B343D8231_b) {
		res.push_back(3);
	}
	
	return res[A623EB95EF17872C1F9FFF6B343D8231_rng() % res.size()];
}

int main() {
	long long n;
	scanf("%lld", &n);
	scanf("%lld %lld", &A623EB95EF17872C1F9FFF6B343D8231_a, &A623EB95EF17872C1F9FFF6B343D8231_b);
	solve(n);

	if (A623EB95EF17872C1F9FFF6B343D8231_cnt > 60000) {
		printf("ERR: TOO MANY OPERATIONS\n");
		return 0;
	}

	if (!A623EB95EF17872C1F9FFF6B343D8231_ok) {
		printf("ERR: ANSWER NOT CORRECT\n");
		return 0;
	}

	for (int i = 1; i <= 1024; ++i) {
		printf("0");
	}

	printf("\n");
	printf("Toqa1Z2fnNQR5K4ew-aPYxCqvRfOwo-ondY3dzd3yn4\n");
	return 0;
}
