TABLE = {2, 3, 5, 7, 11, 13, 17, 21, 23, 24, 25, 31, 37, 41, 43, 47, 51, 53, 57, 61, 66, 72, 73, 74, 77, 79, 81}

ans = 1
for i in TABLE:
    if ans * i <= 1e14:
        ans *= i

print (ans)