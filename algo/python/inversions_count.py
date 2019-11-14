counter = 0


def merge_sort(l):
    global counter
    if len(l) == 1:
        return l
    left_sorted = merge_sort(l[:(len(l) // 2)])
    right_sorted = merge_sort(l[(len(l) // 2):])
    i, l_sorted = 0, []
    while len(left_sorted) and len(right_sorted):
        if left_sorted[0] <= right_sorted[0]:
            l_sorted.append(left_sorted.pop(0))
        else:
            l_sorted.append(right_sorted.pop(0))
            counter += len(left_sorted)
    return l_sorted + left_sorted + right_sorted


if __name__ == "__main__":
    with open('/tmp/input_array.txt', 'r') as f:
        l = [int(v) for v in f.readlines()]
    merge_sort(l)
    print(counter)