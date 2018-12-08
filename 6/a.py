import sys
#f = open('test_input')
f = open('input')

coords = []
for l in f:
    parts = list(map(int, l.strip().split(', ')))
    coords.append((parts[0], parts[1]))

minx = min(map(lambda c: c[0], coords))
miny = min(map(lambda c: c[1], coords))
maxx = max(map(lambda c: c[0], coords))
maxy = max(map(lambda c: c[1], coords))

def manhattan(p, c):
    return abs(p[1] - c[1]) + abs(p[0] - c[0])

def onEdge(c):
    (x, y) = c
    return x == minx or x == maxx or y == miny or y == maxy

def getDists(coords):
    dists = {}

    for c in coords:
        #dists[c] = []
        dists[c] = 0

    for y in range(miny, maxy + 1):
        for x in range(minx, maxx + 1):
            p = (x, y)
            minManhattan = sys.maxsize
            minC = ()
            equal = False
            for c in coords:
                dist = manhattan(p, c)
                if dist == minManhattan:
                    equal = True
                if dist < minManhattan:
                    minManhattan = dist
                    minC = c
                    equal = False
            if not equal:
                dists[minC] += 1
            if onEdge(p):
                dists[minC] = -sys.maxsize
    return dists

def solve(coords):
    dists = getDists(coords)
    maxL = 0
    for d in dists:
        length = dists[d]
        if length > maxL:
            maxL = length
    return maxL

print(solve(coords))
        
