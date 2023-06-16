#!venv/bin/activate
from subprocess import Popen, PIPE
from time import sleep
from click import command, argument, option
from click.types import Path, File
import os


class Field:
	def __init__(self, test):
		self.n, self.m, self.k = map(int, test.readline().strip().split())
		self.A = [list(map(int, line.strip().split())) for line in test]

	def post(self, popen, player_id=None):
		print(self.n, self.m, self.k, file=popen.stdin, flush=True)
		if player_id is not None:
			print(player_id, file=popen.stdin, flush=True)
		for line in self.A:
			print(*line, file=popen.stdin, flush=True)

	def make_move(self, move):
		for i in range(move[1]):
			y, x = move.pop() - 1, move.pop() - 1
			self.A[x][y] = move[0] if self.A[x][y] == 0 else -move[0]


@command(help='Gorilla interactor.')
@argument('player1', type=Path(dir_okay=False, exists=True))
@argument('player2', type=Path(dir_okay=False, exists=True))
@argument('val', type=Path(dir_okay=False, exists=True))
@argument('test', type=File())
@option('--time-limit', '-t', type=int, help='Time limit for each player (seconds).', default=3)
class Gorill:
	def __init__(self, player1, player2, val, test, time_limit):
		self.field = Field(test)
		self.popen1 = Popen([os.path.join('.', player1)], universal_newlines=True, stdin=PIPE, stdout=PIPE)
		self.popen2 = Popen([os.path.join('.', player2)], universal_newlines=True, stdin=PIPE, stdout=PIPE)
		self.val = Popen([os.path.join('.', val)], universal_newlines=True, stdin=PIPE, stdout=PIPE)
		self.mainloop()

	def endgame(self, player_id):
		print(f'Player {player_id} wins')
		print('o', file=self.popen1.stdin, flush=True)
		print('o', file=self.popen2.stdin, flush=True)
		exit(0)

	def make_moves(self, popen, player_id):
		arr = popen.stdout.readline().strip().split()
	#	print(arr)
		try:
			arr = list(map(int, arr))
			if arr[0] != player_id or 3 < arr[1] or arr[1] < 0:
				raise ValueError
			if len(arr[2:]) != arr[1] * 2:
				raise ValueError
			print(*arr, file=self.val.stdin, flush=True)
			status = list(map(int, self.val.stdout.readline().strip().split()))
		#	print(status)
			if status[0] != 0:
				self.endgame(status[0])
			return arr
		except ValueError:
			print('biba')
			self.endgame(3 - player_id)
		except IndexError:
			print('boba')
			self.endgame(3 - player_id)

	def mainloop(self):
		self.field.post(self.popen1, 1)
		self.field.post(self.val)
		move = self.make_moves(self.popen1, 1)
		#print(move)
		self.field.make_move(move)
		self.field.post(self.popen2, 2)
		move = self.make_moves(self.popen2, 2)
		#print(move)
		p1, p2 = self.popen1, self.popen2
		player_id = 1
		while True:
			print('r', file=p1.stdin, flush=True)
			print(*move, file=p1.stdin, flush=True)
			move = self.make_moves(p1, player_id)
		#	print(move)
			p1, p2 = p2, p1
			player_id = 3 - player_id


if __name__ == '__main__':
	Gorill()
