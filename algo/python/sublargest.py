import math

C = 0


def submax(a):
    global C
    if len(a) == 2:
        C += 1
        return (a[0], a[1]) if a[0] < a[1] else (a[1], a[0])
    r = list()
    r.append(submax(a[:int(len(a)/2)]))
    r.append(submax(a[int(len(a)/2):]))
    selector = r[1][1] > r[0][1]
    C += 2
    return max(r[selector][0], r[1 - selector][1]), r[selector][1]


def submax2(a):
    global C
    if len(a) == 1:
        return a[0], []
    m1, l1 = submax2(a[:int(len(a)/2)])
    m2, l2 = submax2(a[int(len(a)/2):])
    C += 1
    if m2 > m1:
        l2.append(m1)
        return m2, l2
    else:
        l1.append(m2)
        return m1, l1


if __name__ == '__main__':
    l = [5, 7, 8, 4, 2, 9, 5, 1, 15, 17, 18, 14, 22, 39, 15, 1]
    _, ll = submax2(l)
    C += len(ll) - 1
    print(max(ll))
    print('%d <= max %d' % (C, len(l) + math.log2(len(l)) - 2))


