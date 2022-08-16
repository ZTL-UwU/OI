import random

f = open("test.in", "w")

n = int(2e5)
f.write(str(n))
f.write("\n")

for i in range(n):
    f.write(str(random.randint(0, 1e9)))
    f.write(" ")