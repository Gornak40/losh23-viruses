#!venv/bin/python
import os
import json
from collections import defaultdict
from prettytable import PrettyTable
from termcolor import cprint
from click import command, argument, option
from click.types import Path


@command(help='Run tournament.')
@argument('folder', type=Path(exists=True, file_okay=False))
@argument('field', type=Path(exists=True, dir_okay=False))
@option('--no-compile', '-nc', is_flag=True, help='Do not compile')
@option('--time-limit', '-t', type=int, help='Time limit for each player (seconds).', default=3)
def battle(folder, field, no_compile, time_limit):
	if not no_compile:
		for name in filter(lambda x: x.endswith('.cpp'), os.listdir(folder)):
			cprint(f'[compiling] {name}', color='yellow')
			if os.system(f'g++ {os.path.join(folder, name)} -O3 -march=native -o {os.path.join(folder, name.removesuffix(".cpp"))}'):
				cprint(f'[can\'t compile] {name}', color='red')
				exit(0)
		cprint('[all binaries are ready]', color='green')
		return
	names = sorted([x for x in os.listdir(folder) if not x.endswith('.cpp')], key=lambda x: x.title().split('_')[1:])
	score = defaultdict(int)
	for i, player1 in enumerate(names):
		cprint(f'[running] {player1} #{i}', color='yellow')
		for player2 in names:
			if player1 == player2:
				continue
			cprint(f'[fight] {player1} {player2}', color='cyan')
			if os.system(f'python gorill.py {os.path.join(folder, player1)} {os.path.join(folder, player2)} val {field} -t {time_limit}'):
				cprint(f'[fatal error]', color='red')
				exit(0)
			with open('result.out') as file:
				if int(file.readline().strip()) == 1:
					score[player1] += 1
				else:
					score[player2] += 1
			with open('results.json', 'w', encoding='utf-8') as file:
				json.dump(score, file, sort_keys=True, indent='\t', ensure_ascii=False)


if __name__ == '__main__':
	battle()
