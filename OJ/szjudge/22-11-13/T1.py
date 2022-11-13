l = int(input())
r = int(input())

max = 0
max_i = 0

for i in range(l, r + 1):
    k = i
    product = 1
    while k > 0:
        product = product * (k % 10)
        k = k // 10
    if product >= max:
        max = product
        max_i = i

print(max_i)