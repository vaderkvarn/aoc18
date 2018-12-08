import re
import sys
from string import ascii_lowercase
input = open('input').readline()
#input = 'dabAcCaCBAcCcaDA'

def next(i, removed):
    i += 1
    if i >= len(removed):
        return i 
    while removed[i] >= 0:
        i += 1
        if i >= len(removed):
            return i 
    return i 
def prev(i, removed):
    j = i
    j -= 1
    while removed[j] >= 0:
        j -= 1
    if j < 0: j = j + 1
    return j 
def react(input):
    removed = [-1]*len(input)
    i = 0
    while next(i, removed) < len(input):
        c = input[i]
        d = input[next(i, removed)]
        if c != d and c.lower() == d.lower():
            removed[i] = 1
            removed[next(i, removed)] = 1
            i = prev(i, removed)
        else: i = next(i, removed)

    left = [x for x in removed if x < 0]

    return(len(left))


def stripInput(input, l):
    return re.sub(l + '|' + l.upper(), '', input[:])

minLength = sys.maxint
for c in ascii_lowercase:
    length = react(stripInput(input, c))
    if length < minLength:
        minLength = length
print(minLength)
