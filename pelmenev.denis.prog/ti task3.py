message = 'Na dvore trava, na trave drova. Ne rubi drova na trave dvora!'
table = [
    ['N', 2, 0.03272, 0.0, 0.03272],
    ['a', 10, 0.16393, 0.03272, 0.19672],
    ['d', 4, 0.06557, 0.19672, 0.2623],
    ['v', 7, 0.11475, 0.2623, 0.37705],
    ['o', 4, 0.06557, 0.37705, 0.44262],
    ['r', 8, 0.13115, 0.44262, 0.57377],
    ['e', 4, 0.06557, 0.57377, 0.63934],
    [' ', 11, 0.18033, 0.63934, 0.81967],
    ['t', 3, 0.04918, 0.81967, 0.86885],
    [',', 1, 0.01639, 0.86885, 0.88525],
    ['.', 1, 0.01639, 0.88525, 0.90164],
    ['!', 1, 0.01639, 0.90164, 0.91803],
    ['n', 2, 0.03272, 0.91803, 0.95082],
    ['u', 1, 0.01639, 0.95082, 0.96721],
    ['b', 1, 0.01639, 0.96721, 0.98361],
    ['i', 1, 0.01639, 0.98361, 1.0]
        ]

result = []

for idx in range(0, len(table) - 1):
    if message[0] == table[idx][0]:
        row = [message[0], table[idx][3], table[idx][4]]
        result.append(row)
        break

for mes in range(1, len(message) - 1):
    for tab in range(0, len(table) - 1):
        if message[mes] == table[tab][0]:
            row = []
            a = result[mes - 1][1] + (result[mes - 1][2] - result[mes - 1][1]) * table[tab][3]
            b = result[mes - 1][1] + (result[mes - 1][2] - result[mes - 1][1]) * table[tab][4]
            row = [message[mes], a, b]
            result.append(row)
            break
print(result)
