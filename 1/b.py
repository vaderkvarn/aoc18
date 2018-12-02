input = open('input').readlines()
seen = {}
freq = 0
i = 0
while not str(freq) in seen:
    seen[str(freq)] = 1
    freq += int(input[i]) 
    i = (i + 1)%len(input)
print(freq)