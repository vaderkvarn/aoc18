input = open('input').read().splitlines()

for s1 in input:
    for s2 in input:
        res = []
        ls = len(s1)
        for i in range(ls):
            if s1[i] == s2[i]: res.append(s1[i])
        if len(res) == ls - 1:
            print(''.join(res))
            exit()
