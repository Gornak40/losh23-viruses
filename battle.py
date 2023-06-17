#!venv/bin/python3
import os
import json
from collections import defaultdict
from termcolor import cprint
from click import command, argument, option
from click.types import Path


def post(s, field, color=None):
	if color is not None:
		cprint(s, color=color)
	with open(f'{field}_story.log', 'a') as file:
		print(s, file=file)


@command(help='Run tournament.')
@argument('folder', type=Path(exists=True, file_okay=False))
@argument('field', type=Path(exists=True, dir_okay=False))
@option('--no-compile', '-nc', is_flag=True, help='Do not compile')
@option('--time-limit', '-t', type=int, help='Time limit for each player (seconds).', default=3)
def battle(folder, field, no_compile, time_limit):
	if not no_compile:
		for name in filter(lambda x: x.endswith('.cpp'), os.listdir(folder)):
			post(f'[compiling] {name}', field, color='yellow')
			if os.system(f'g++ {os.path.join(folder, name)} -O3 -march=native -o {os.path.join(folder, name.removesuffix(".cpp"))}'):
				post(f'[can\'t compile] {name}', field, color='red')
				exit(0)
		post('[all binaries are ready]', field, color='green')
		return
	names = sorted([x for x in os.listdir(folder) if not x.endswith('.cpp')], key=lambda x: x.title().split('_')[1:])
	score = defaultdict(int)
	for i, player1 in enumerate(names):
		if 'Егор' not in player1:
			continue
		post(f'[running] {player1} #{i}', field, color='yellow')
		for player2 in names:
			if player1 == player2:
				continue
			post(f'[fight] {player1} {player2}', field, color='cyan')
			if os.system(f'python gorill.py {os.path.join(folder, player1)} {os.path.join(folder, player2)} val {field} -t {time_limit}'):
				post(f'[fatal error]', field, color='red')
				exit(0)
			with open('result.out') as file:
				if int(file.readline().strip()) == 1:
					post('Player 1 wins', field)
					score[player1] += 1
				else:
					post('Player 2 wins', field)
					score[player2] += 1
			with open(f'{field}_results.json', 'w', encoding='utf-8') as file:
				json.dump(score, file, sort_keys=True, indent='\t', ensure_ascii=False)
	post('Endgame', field)


if __name__ == '__main__':
	battle()
