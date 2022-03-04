def almost_everywhere_zero(n, k):
    count = 0
    for i in range(1, n + 1):
        num = 0
        for j in str(i):
            if j != '0':
                num += 1
        if num == k:
            count += 1
    return count


print(almost_everywhere_zero(10000000000000000000000, 21))