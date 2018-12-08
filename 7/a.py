f = open('input')
pairs = []
for l in f:
    parts = l.split(' ')
    pairs.append((parts[1], parts[7]))

def getAvailable(candidates, deps):
    av = [c for c in candidates if not c in deps]
    return sorted(list(set(av)))

def solve(pairs):
    res = []
    p = pairs[:]
    while True:
        avail = getAvailable([t[0] for t in p], [t[1] for t in p])
        if len(avail) == 0:
            z = zip(*pairs)
            left = set(z[1]) - set(z[0])
            res += sorted(list(left))
            break
        res.append(avail[0])
        p = [t for t in p if t[0] != avail[0]]
    return "".join(res)

print(solve(pairs))

