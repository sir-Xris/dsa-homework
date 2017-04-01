#!/usr/bin/env python3
from functools import reduce

operator = (
    'push-back',
    'remove',
    'incremental-sort',
    'decremental-sort',
)

ls = [[], []]

for i in range(2):
    n = int(input())
    for j in range(n):
        opt = input().split()
        if len(opt) == 1:
            opt = opt[0]
            if opt == 'reverse':
                ls[i].reverse()
            elif opt == 'incremental-sort':
                ls[i].sort()
            elif opt == 'decremental-sort':
                ls[i].sort(reverse=True)
        elif len(opt) == 2:
            opt, val = opt
            val = int(val)
            if opt == 'push-back':
                ls[i].append(val)
            elif opt == 'remove':
                ls[i] = list(filter(lambda x: x != val, ls[i]))
        for e in ls[i]:
            print(e)
        print()

ls[0] += ls[1]
ls[0] = list(set(ls[0]))
ls[0].sort(reverse=True)
for i in ls[0]:
    print(i)
print()
