import re
f = open('input')
events = []
for line in f:
    parts = line.split(']')
    date = re.sub('[^0-9]', '', parts[0])
    event = parts[1].strip()
    events.append((date, event))

events.sort(key=lambda t: t[0])

guard_info = {}
current_guard_id = 0
current_sleep_start = 0
for e in events:
    if e[1].startswith('Guard'):
        current_guard_id = int(e[1].split('#')[1].split(' ')[0])
        if not current_guard_id in guard_info:
            guard_info[current_guard_id] = {'mins': [0]*60}
    elif e[1].startswith('falls'):
        current_sleep_start = int(e[0][-2:])
    elif e[1].startswith('wakes'):
        guard = guard_info[current_guard_id]
        wake_time = int(e[0][-2:])
        for i in range(current_sleep_start, wake_time):
            guard['mins'][i] += 1
        
        
max_time = 0
max_guard = -1
max_idx = 0
for g in guard_info:
    guard = guard_info[g]
    guard_max = max(guard['mins'])
    if guard_max > max_time:
        max_time = guard_max
        max_idx = guard['mins'].index(guard_max)
        max_guard = g

print(max_guard * max_idx)