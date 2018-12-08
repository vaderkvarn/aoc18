input = open('input').readline()
#input = 'dabAcCaCBAcCcaDAFfaaaaAAAA'

def slow(input):
    current = input
    last = ""
    while current != last:
        last = current
        for i in range(len(current) - 1):
            c = current[i]
            d = current[i+1]
            if c != d and c.lower() == d.lower():
                last = current
                current = current[:i] + current[i+2:]
                break
    return len(current)

#print(slow(input))

removed = [-1]*len(input)
def next(i):
    i += 1
    if i >= len(removed):
        return i 
    while removed[i] >= 0:
        i += 1
        if i >= len(removed):
            return i 
    return i 
def prev(i):
    j = i
    j -= 1
    while removed[j] >= 0:
        j -= 1
    if j < 0: j = j + 1
    return j 
def fast(input):
    i = 0
    while next(i) < len(input):
        c = input[i]
        d = input[next(i)]
        if c != d and c.lower() == d.lower():
            removed[i] = 1
            removed[next(i)] = 1
            i = prev(i)
        else: i = next(i)

    left = [x for x in removed if x < 0]

    return(len(left))
print(fast(input))
