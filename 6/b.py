import sys
from heapq import *
#f = open('test_input')
f = open('input')

#limit = 32
limit = 10000

coords = []
for l in f:
    parts = list(map(int, l.strip().split(', ')))
    coords.append((parts[0], parts[1]))

def manhattan(p, c):
    return abs(p[1] - c[1]) + abs(p[0] - c[0])

minx = min(map(lambda c: c[0], coords))
miny = min(map(lambda c: c[1], coords))
maxx = max(map(lambda c: c[0], coords))
maxy = max(map(lambda c: c[1], coords))

def getDists(coords):
    dists = []
    for y in range(miny, maxy + 1):
        for x in range(minx, maxx + 1):
            p = (x, y)
            sumD = 0
            for c in coords:
                dist = manhattan(p, c)
                sumD += dist
                if sumD > limit:
                    break
            if sumD < limit:
                dists.append(p)
    return dists

print(len(getDists(coords)))

#def getValidNeghbors(p, dist):
#    (x, y) = p
#    n = []
#    if (x-1, y) in dist: n.append((x-1, y)) 
#    if (x+1, y) in dist: n.append((x+1, y)) 
#    if (x, y-1) in dist: n.append((x, y-1)) 
#    if (x, y+1) in dist: n.append((x, y+1)) 
#    return n
#
#def buildRegionsBFS(dists):
#    visited = set([])
#    regions = []
#    for d in dists:
#        h = []
#        if d in visited: continue
#        region = set([])
#        heappush(h, d)
#        while h:
#            p = heappop(h)
#            ns = getValidNeghbors(p, dists)
#            for n in ns:
#                if not n in region:
#                    heappush(h, n)
#                    visited.add(n)
#                    region.add(n)
#        regions.append(region)
#    return regions
#
#def solve(coords):
#    dists = getDists(coords)
#    regions = buildRegionsBFS(dists)
#    maxL = 0
#    for r in regions:
#        if len(r) > maxL:
#            maxL = len(r)
#    return maxL
#print(solve(coords))
        
