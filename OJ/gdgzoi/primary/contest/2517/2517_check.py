a = [1, 2, 5, 4, 3]
n = 5

def swap(i1, i2):
    tmp = a[i1]
    a[i1] = a[i2]
    a[i2] = tmp

is_sorted = False
while (not is_sorted):
    is_sorted = True
    print('moo')

    for i in range(0, n - 2 + 1):
        if a[i + 1] < a[i]:
            swap(i, i + 1)
    print(a)

    for i in range(n - 2, -1, -1):
        if a[i + 1] < a[i]:
            swap(i, i + 1)
    print(a)

    for i in range(0, n - 2 + 1):
        if a[i + 1] < a[i]:
            swap(i, i + 1)
            is_sorted = False
