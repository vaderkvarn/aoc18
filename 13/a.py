
map = []
carts = []
for l in open('test_input'):
    map.append(list(l.replace('\n', '')))
print(map)

def is_cart(c):
    return c in "<>v^"

for i in range(len(map)):
    for j in range(len(map[i])):
        if is_cart(map[i][j]):
            carts.append((j, i, map[i][j]))
print(carts)
def solve(map, carts):
    i = 0 
    #while carts:

    while i < 20:
        carts.sort()
        for cart in carts:
            x, y, d = cart
            c = map[y][x] 
        i += 1
    print(carts)

solve(map, carts)