
def solve(num):
    recipes = [3,7]
    elv1 = 0
    elv2 = 1
    cur_pos = 0
    digits = map(int, list(str(num)))
    while True:
        s = recipes[elv1] + recipes[elv2]
        parts = map(int, list(str(s)))
        for i in range(len(parts)):
            if parts[i] == digits[cur_pos]: 
                cur_pos += 1
                if cur_pos == len(digits):
                    print(recipes[-100:])
                    return len(recipes) + i + 1 - len(digits)
            else: cur_pos = 0
        recipes += parts
        elv1 = (elv1 + 1 + recipes[elv1])%len(recipes)
        elv2 = (elv2 + 1 + recipes[elv2])%len(recipes)
print(solve(380621))
