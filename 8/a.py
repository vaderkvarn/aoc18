input = list(map(int, open("input").readline().split(' ')))

def solve_rec(node):
    num_c = node[0]
    num_meta = node[1]
    length = 2
    tot_meta = 0
    for i in range(num_c):
        (child_length, meta) = solve_rec(node[length:])
        tot_meta += meta
        length += child_length
    return (length + num_meta, tot_meta + sum(node[length:length+num_meta]))
print(solve_rec(input)[1])