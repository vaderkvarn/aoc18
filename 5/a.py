input = open('input').readline()
#input = 'dabAcCaCBAcCcaDAFfaaaaAAAA'

def slow():
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
    print(len(current))

#slow()

removed = [False]*len(input)
def next(i):
    i += 1
    while i in removed:
        i += 1
    return i 
def prev(i):
    i -= 1
    while i in removed:
        i -= 1
    return i 
def fast(input):
    i = 0
    while next(i) < len(input):
        if i in removed:
            print("Already removed")
        if next(i) in removed:
            print("Already removed next")
        if prev(i) in removed:
            print("Already removed prev")
        c = input[i]
        d = input[next(i)]
        if c != d and c.lower() == d.lower():
            removed[i] = True
            removed[next(i)] = True
            i = prev(i)
        else: i = next(i)
    length = 0
    print(len(input) - len(removed.keys()))
    for i in range(len(input)):
        if not i in removed:
            length += 1
    return length
print(fast(input))
