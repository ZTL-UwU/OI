import random

max_n = int(input())
max_m = int(input())

n = random.randrange(1, max_n)
m = random.randrange(1, max_m)

while m < n - 1:
    m = random.randrange(1, max_m)

print(n, m)
