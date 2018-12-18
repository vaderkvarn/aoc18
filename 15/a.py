from heapq import *
from operator import itemgetter
import sys

map = []
players = []
i = 0
for line in open('test_input'):
    map.append(list(line.strip()))
    for j in range(len(line)):
        c = line[j]
        if c == 'G' or c == 'E':
            players.append({'type': c, 'hp': 200, 'pos': (i, j)})
    i += 1
#print(map)
#print(players)

def enemy_type(player):
    if player['type'] == 'E': return 'G'
    return 'E'

def get_valid_neighbors(map, p):
    squares = []
    (i, j) = p
    if map[i+1][j] == '.': squares.append((i+1, j))
    if map[i-1][j] == '.': squares.append((i-1, j))
    if map[i][j+1] == '.': squares.append((i, j+1))
    if map[i][j-1] == '.': squares.append((i, j-1))
    return squares

def get_dist(p1, p2):
    #return (p1[0] - p2[0])**2 + (p1[1] - p2[1])**2
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])

#Perhaps shortes path to every given point, then grep for squares
def get_shortest_path(map, p1, p2):
    paths = []
    h = []
    visited = {}
    heappush(h, (1, get_dist(p1, p2), [p1]))
    shortest = sys.maxsize
    #for i in range(10):
    while h:
       # for p in h:
       #     print(p)
       # print()
        #for v in visited:
            #print(v, visited[v])
        (length, dist, path) = heappop(h)
        if len(path) != length:
            print("EERROR")
        #print(path)
        if path[-1] == p2:
            #print(path)
            print(len(path))
            paths.append(path)
            shortest = len(path)
            continue
        #print(path[-1])
        #print(get_valid_neighbors(map, path[-1]))
        for n in get_valid_neighbors(map, path[-1]):
            if n in visited:
                if visited[n] < length + 1:
                    #print(n, "Old was: ", visited[n], "new is: ", length + 1)
                    continue
            visited[n] = length + 1
                
            p = path[:]
            p.append(n)
            dist = get_dist(n, p2)
            #if len(p) <= shortest:
            heappush(h, (len(p), get_dist(n, p2), p))
    return paths

print(get_shortest_path(map, (1, 2), (7, 6)))

def get_targets(type, players):
    targets = []
    for player in players:
        if player['type'] == type:
            targets.append(player)
    return targets

def turn(map, player, players):
    targets = get_targets(enemy_type(player), players) 
    #TODO: Check if any targets are next to us
    next_squares = []
    for target in targets:
        next_squares += get_valid_neighbors(map, target['pos'])

    #print(next_squares)

def round(map, players):
    players = sorted(players, key=itemgetter('pos')) 
    for player in players:
        turn(map, player, players)
    #print(players)

round(map, players)




