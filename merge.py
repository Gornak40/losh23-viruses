import os
import json
from collections import defaultdict
from random import shuffle
from prettytable import PrettyTable


res = defaultdict(int)
for name in filter(lambda x: x.endswith('.json'), os.listdir()):
	with open(name) as file:
		cur = json.load(file)
		for key, val in cur.items():
			res[key] += val

res = sorted(res.items(), key=lambda x: -x[1])
P = PrettyTable(['ID', 'Name', 'Score'])
for name, score in res:
	P.add_row([name.split('_')[0], ' '.join(name.title().split('_')[1:]), score])
print(P)

arr = list()
for name, score in res[:20]:
	arr.append(f'../solutions/{name}')
	arr.append(f'../solutions/{name}')
#	arr.append(f'../solutions/{res[0][0]}')

shuffle(arr)
print(*arr)
