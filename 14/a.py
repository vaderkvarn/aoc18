
def solve(num):
    recipes = [3,7]
    elv1 = 0
    elv2 = 1
    while True:
        s = recipes[elv1] + recipes[elv2]
        parts = map(int, list(str(s)))
        recipes += parts
        elv1 = (elv1 + 1 + recipes[elv1])%len(recipes)
        elv2 = (elv2 + 1 + recipes[elv2])%len(recipes)
        if len(recipes) >= num + 10:
            return ''.join(map(str, recipes[num:num+10]))
print(solve(380621))