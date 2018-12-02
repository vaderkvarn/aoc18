f = open('input')
twos = 0
threes = 0
for l in f:
    d = {}
    for c in l:
        if  c in d:
            d[c] += 1
        else:
            d[c] = 1
    if 2 in d.values():
        twos += 1
    if 3 in d.values():
        threes += 1
print(twos * threes)