from functools import reduce
print(reduce(lambda x, y: int(x) + int(y), open('input').readlines()))