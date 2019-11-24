import statistics

count = 0


def swap(a, i, j):
    if i == j:
        return
    a[i] += a[j]
    a[j] = a[i] - a[j]
    a[i] = a[i] - a[j]


def get_pivot_index(data, mode='first'):
    if mode == 'first':
        return data[0][0]
    if mode == 'last':
        return data[-1][0]
    # median
    median = statistics.median([d[1] for d in data])
    for index, value in data:
        if median == value:
            return index


def quick_sort(a, l, r, mode='first'):
    global count
    count += max(r - l - 1, 0)
    if r - l <= 1:
        return
    pivot_index = get_pivot_index(((l, a[l]), (l + (r-l-1) // 2, a[l + (r-l-1) // 2]), (r - 1, a[r - 1])), mode)
    swap(a, pivot_index, l)
    j = l
    for i in range(l, r):
        if a[i] < a[l]:
            j += 1
            swap(a, i, j)
    swap(a, l, j)
    quick_sort(a, l, j, mode)
    quick_sort(a, j + 1, r, mode)


# def quick_sort_last(a, l, r):
#     global count
#     count += max(r - l - 1, 0)
#     if r - l <= 1:
#         return
#     j = l - 1
#     for i in range(l, r - 1):
#         if a[i] < a[r - 1]:
#             j += 1
#             swap(a, i, j)
#     j += 1
#     swap(a, r - 1, j)
#     quick_sort(a, l, j)
#     quick_sort(a, j + 1, r)


if __name__ == '__main__':
    # a = [3, 5, 1, 6, 8, 7, 2, 4]
    with open('quicksort.txt', 'r') as f:
        a = [int(n) for n in f.readlines()]
    quick_sort(a, 0, len(a), mode='first')
    print(a)
    print(count)

    count = 0
    # a = [3, 5, 1, 6, 8, 7, 2, 4]
    with open('quicksort.txt', 'r') as f:
        a = [int(n) for n in f.readlines()]
    quick_sort(a, 0, len(a), mode='last')
    print(a)
    print(count)

    count = 0
    # a = [3, 5, 1, 6, 8, 7, 2, 4]
    with open('quicksort.txt', 'r') as f:
        a = [int(n) for n in f.readlines()]
    quick_sort(a, 0, len(a), mode='median')
    print(a)
    print(count)

