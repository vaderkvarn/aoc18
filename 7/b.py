test = False
if test:
    f = open('test_input')
    added_time = 0
    num_elves = 2
else:
    f = open('input')
    added_time = 60
    num_elves = 5

pairs = []
for l in f:
    parts = l.split(' ')
    pairs.append((parts[1], parts[7]))

def getAvailable(candidates, deps):
    av = [c for c in candidates if not c in deps]
    return sorted(list(set(av)))

def getTimeForInput(c):
    return added_time + ord(c) - ord('A')

def solve(pairs):
    time = 0
    elves = []
    for i in range(num_elves):
        elves.append({
            'c': None,
            'time': 0,
            'working': False
        })
    taken = set([])
    p = pairs[:]
    while True:
        for elv in filter(lambda elv: elv['working'], elves):
            if elv['time'] == 0:
                p = [t for t in p if t[0] != elv['c']]
                elv['working'] = False
            else: elv['time'] -= 1

        avail = getAvailable([t[0] for t in p], [t[1] for t in p])
        if len(avail) == 0:
            z = zip(*pairs)
            left = set(z[1]) - set(z[0])
            avail += sorted(list(left))

        for elv in filter(lambda elv: not elv['working'], elves):
            for av in avail:
                if av not in taken:
                    taken.add(av)
                    elv['c'] = av
                    elv['time'] = getTimeForInput(av)
                    elv['working'] = True
                    break

        if all(map(lambda elv: not elv['working'], elves)):
            return time
        time += 1


print(solve(pairs))

#print("".join(res))    

