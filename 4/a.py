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
            guard_info[current_guard_id] = {'max': 0, 'tot': 0, 'mins': [0]*60}
    elif e[1].startswith('falls'):
        current_sleep_start = int(e[0][-2:])
    elif e[1].startswith('wakes'):
        wake_time = int(e[0][-2:])
        sleep_time = wake_time - current_sleep_start
        if sleep_time > guard_info[current_guard_id]['max']:
            guard_info[current_guard_id]['max'] = sleep_time
        for i in range(current_sleep_start, wake_time):
            guard_info[current_guard_id]['mins'][i] += 1
        guard_info[current_guard_id]['tot'] += sleep_time
        
max_time = 0
max_guard = -1
max_min = 0
for g in guard_info:
    guard = guard_info[g]
    if guard['tot'] > max_time:
        max_time = guard['tot']
        max_min = guard['mins'].index(max(guard['mins']))
        max_guard = g

print(max_min*max_guard)