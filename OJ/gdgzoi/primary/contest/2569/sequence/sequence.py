def f(d):
	res = 0

	for i in range(1, d):
		if d % i == 0:
			res += f(i)

	return d - res

n = int(input())
ans = 0;

for i in range(0, n):
	d = int(input())
	ans += f(d)

print(ans)