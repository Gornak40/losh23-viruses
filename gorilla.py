#!venv/bin/python
# from click import command, argument, option
# from click.types import Path, File
from subprocess import Popen, PIPE
import os
from time import time


class Field:
	def __init__(self, test):
		self.n, self.m, self.k = map(int, test.readline().strip().split())
		self.A = [list(map(int, line.strip().split())) for line in test]

	def post(self, popen, player_id=None):
		print(self.n, self.m, self.k, file=popen.stdin)
		print(self.n, self.m, self.k)
		if player_id is not None:
			print(player_id, file=popen.stdin)
		for line in self.A:
			print(*line, file=popen.stdin)

	def make_move(self, move):
		for i in range(move[1]):
			y, x = move.pop(), move.pop()
			self.A[x][y] = move[0] if self.A[x][y] == 0 else -move[0]


# @command(help='Gorilla interactor.')
# @argument('player1', type=Path(dir_okay=False, exists=True))
# @argument('player2', type=Path(dir_okay=False, exists=True))
# @argument('val', type=Path(dir_okay=False, exists=True))
# @argument('test', type=File())
# @option('--time-limit', '-t', type=int, help='Time limit for each player (seconds).', default=3)
class Main:
	def __init__(self, player1='roma', player2='roma', val='val', test=open('test.in'), time_limit=None):
		self.time_limit = time_limit
		self.popen1 = Popen([os.path.join('.', player1)], stdin=PIPE, stdout=PIPE, universal_newlines=True)
		self.popen2 = Popen([os.path.join('.', player2)], stdin=PIPE, stdout=PIPE, universal_newlines=True)
		self.val = Popen([os.path.join('.', val)], stdin=PIPE, stdout=PIPE, universal_newlines=True)
		self.field = Field(test)
		print(3, 4, 5, file=self.val.stdin)
	#	self.mainloop()

	def mainloop(self):
		self.field.post(self.val)
		self.field.post(self.popen1, 1)
		move = self.make_moves(self.popen1, 1)
		self.field.make_move(move)
		self.field.post(self.popen2, 2)
		move = self.make_moves(self.popen2, 2)
		p1, p2 = self.popen1, self.popen2
		player_id = 1
		while True:
			print('r', file=p1.stdin)
			print(*move, file=p1.stdin)
			move = self.make_moves(p1, player_id)
			p1, p2 = p2, p1
			player_id = 3 - 1


#	def tl_endgame(self):
#		self.endgame(2) if self.popen1.cur_t >= self.popen2.cur_t else self.endgame(1)

	def endgame(self, player_id):
		print(f'Player {player_id} wins')
		print('o', file=self.popen1.stdin)
		print('o', file=self.popen2.stdin)
		self.popen1.kill()
		self.popen2.kill()
		self.val.kill()
		exit(0)

	def make_moves(self, popen, player_id):
#		g = time()
#		if not (s := popen.readline().strip()):
#			self.tl_endgame()
#		popen.cur_t += time() - g
		arr = popen.stdout.readline().strip().split()
		try:
			arr = list(map(int, arr))
			if arr[0] != player_id or 3 < arr[1] or arr[1] < 0:
				raise ValueError
			if len(arr[2:]) != arr[1]:
				raise ValueError
			print(*arr, file=self.val.stdin)
			status = list(map(int, self.val.stdout.readline().strip().split()))
			if status[0] != 0:
				self.endgame(status[0])
			return arr
		except ValueError:
			self.endgame(3 - player_id)
		except IndexError:
			self.endgame(3 - player_id)

	def __del__(self):
		self.popen1.terminate()
		self.popen2.terminate()
		self.val.terminate()


if __name__ == '__main__':
	Main()
