def recursive_mul(x, y):
    if len(x) < 2 and len(y) < 2:
        return int(x) * int(y)
    if len(x) < len(y):
        x = '0' * (len(y) - len(x)) + x
    if len(y) < len(x):
        y = '0' * (len(x) - len(y)) + y
    a, b = x[:int(len(x) / 2)], x[int(len(x) / 2):]
    c, d = y[:int(len(y) / 2)], y[int(len(y) / 2):]
    ac = recursive_mul(a, c)
    bd = recursive_mul(b, d)
    abcd = recursive_mul(str(int(a) + int(b)), str(int(c) + int(d)))
    return ac * 10 ** (len(b) + len(d)) + (abcd - ac - bd) * 10 ** len(b) + bd


if __name__ == '__main__':
    x = str(input('X:'))
    y = str(input('Y:'))
    print(recursive_mul(x, y))