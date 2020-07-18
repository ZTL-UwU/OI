import random
for i in range(1, 100):
    a = int(random.uniform(1, 2147483647))
    b = int(random.uniform(1, 2147483647))
    c = a + b
    f = open('\\test_data.txt', 'w')
    f.write(str(a))
    f.write(' ')
    f.write(str(b))
    f.write('\n')