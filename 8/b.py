input = list(map(int, open("input").readline().split(' ')))

def solve_rec(node):
    num_c = node[0]
    num_meta = node[1]
    pos = 2
    if num_c == 0:
        return (pos + num_meta, sum(node[pos:pos+num_meta]))
    child_values = {}
    for i in range(num_c):
        (child_length, val) = solve_rec(node[pos:])
        child_values[i + 1] = val
        pos += child_length
    metas = node[pos:pos+num_meta]
    value = sum([child_values[m] for m in metas if m in child_values])
    return (pos + num_meta, value)
print(solve_rec(input)[1])
