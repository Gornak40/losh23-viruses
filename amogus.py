from subprocess import Popen, PIPE
import os


def endgame(player_id):
	print(f'Player {player_id} wins')
	exit(0)


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


def make_moves(popen, val, player_id):
	arr = popen.stdout.readline().strip().split()
	try:
		arr = list(map(int, arr))
		if arr[0] != player_id or 3 < arr[1] or arr[1] < 0:
			raise ValueError
		if len(arr[2:]) != arr[1] * 2:
			raise ValueError
		print(*arr, file=val.stdin, flush=True)
		status = list(map(int, val.stdout.readline().strip().split()))
		if status[0] != 0:
			endgame(status[0])
		return arr
	except ValueError:
		endgame(3 - player_id)
	except IndexError:
		endgame(3 - player_id)



field = Field(open('test.in'))


with Popen(['./roma'], universal_newlines=True, stdin=PIPE, stdout=PIPE) as popen1:
	with Popen(['./roma'], universal_newlines=True, stdin=PIPE, stdout=PIPE) as popen2:
		with Popen(['./val'], universal_newlines=True, stdin=PIPE, stdout=PIPE) as val:
			field.post(popen1, 1)
			field.post(val)
			move = make_moves(popen1, val, 1)
		#	print(move)
			field.make_move(move)
			field.post(popen2, 2)
			move = make_moves(popen2, val, 2)
		#	print(move)
			p1, p2 = popen1, popen2
			player_id = 1
			while True:
				print('r', file=p1.stdin, flush=True)
				print(*move, file=p1.stdin, flush=True)
				move = make_moves(p1, val, player_id)
		#		print(move)
				p1, p2 = p2, p1
				player_id = 3 - player_id
