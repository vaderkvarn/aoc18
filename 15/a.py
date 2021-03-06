#237490
from heapq import *
from operator import itemgetter
import sys

def init(f):
    game_map = []
    players = []
    i = 0
    for line in open(f):
        game_map.append(list(line.strip()))
        for j in range(len(line)):
            c = line[j]
            if c == 'G' or c == 'E':
                players.append({'type': c, 'hp': 200, 'pos': (i, j)})
        i += 1
    return (game_map, players)

def get_player_at_pos(pos, players):
    #TODO: Binary search
    for p in players:
        if p['pos'] == pos:
            return p

def enemy_type(player):
    if player['type'] == 'E': return 'G'
    return 'E'

def get_valid_neighbors(game_map, p):
    squares = set()
    (i, j) = p
    if game_map[i+1][j] == '.': squares.add((i+1, j))
    if game_map[i-1][j] == '.': squares.add((i-1, j))
    if game_map[i][j+1] == '.': squares.add((i, j+1))
    if game_map[i][j-1] == '.': squares.add((i, j-1))
    return squares
def get_enemy_neighbors(game_map, p, players):
    enemies = []
    t = enemy_type(p)
    (i, j) = p['pos']
    if game_map[i+1][j] == t: enemies.append(get_player_at_pos((i+1, j), players))
    if game_map[i-1][j] == t: enemies.append(get_player_at_pos((i-1, j), players))
    if game_map[i][j+1] == t: enemies.append(get_player_at_pos((i, j+1), players))
    if game_map[i][j-1] == t: enemies.append(get_player_at_pos((i, j-1), players))
    return sorted(enemies, key=itemgetter('hp', 'pos'))

def get_shortest_path(game_map, p1, p2, shortest):
    paths = []
    h = []
    visited = {}
    heappush(h, (1, (p1,p1)))
    while h:
        length, end_points = heappop(h)
        start, end = end_points
        if end == p2 and length <= shortest:
            paths.append(end_points)
            if length < shortest:
                shortest = length
                paths = [end_points]
            continue
        if length >= shortest: 
            if not end in visited:
                visited[end] = length
            continue
        new_len = length + 1
        for n in get_valid_neighbors(game_map, end):
            if n in visited:
                if visited[n] <= new_len:
                    continue
            visited[n] = new_len
                
            heappush(h, (new_len, (start, n)))
    return (shortest, paths)

def get_targets(type, players):
    targets = []
    for player in players:
        if player['type'] == type:
            targets.append(player)
    return targets

def move(game_map, player, square):
    pi, pj = player['pos']
    si, sj, = square
    game_map[pi][pj] = '.'
    game_map[si][sj] = player['type']
    player['pos'] = square

def is_dead(p):
    return p['hp'] <= 0

def attack(p1, p2):
    p2['hp'] -= 3

def potential_attack(game_map, player, players):
    enemy_neighbors = get_enemy_neighbors(game_map, player, players)
    if enemy_neighbors:
        enemy = enemy_neighbors[0]
        attack(player, enemy)
        if is_dead(enemy):
            i, j = enemy['pos']
            game_map[i][j] = '.'
        return True
    return False

def turn(game_map, player, players):
    if is_dead(player): return
    players = [p for p in players if p['hp'] >= 0]
    targets = get_targets(enemy_type(player), players) 
    if potential_attack(game_map, player, players): return True
    next_squares = set()
    for target in targets:
        next_squares |= get_valid_neighbors(game_map, target['pos'])
    paths = []
    shortest = sys.maxsize
    next_squares = sorted(list(next_squares))
    for square in next_squares:
        for n in sorted(list(get_valid_neighbors(game_map, player['pos']))):
            new_shortest, new_paths = get_shortest_path(game_map, n, square, shortest)
            if new_shortest < shortest:
                paths = new_paths
                shortest = new_shortest
            elif new_shortest == shortest:
                paths += new_paths
    if paths:
        paths = [p[::-1] for p in paths]
        next_square = sorted(paths)[0][1]
        move(game_map, player, next_square)
        potential_attack(game_map, player, players)
        return True
    return False


def round(game_map, players):
    players = sorted(players, key=itemgetter('pos')) 
    someone_acted = False
    for player in players:
        did_act = turn(game_map, player, players)
        if did_act: someone_acted = True
    players = [p for p in players if p['hp'] >= 0]
    if not someone_acted: return (game_map, players, False)
    return (game_map, players, True)

def run(game_map, players):
    i = 0
    while True:
        game_map, players, action = round(game_map, players)
        if not action: break
        i += 1
    return (i-1, sum(map(lambda p: p['hp'], players)))

iterations, hp = run(*init('input'))
print(iterations * hp)