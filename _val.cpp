#include <iostream>

using namespace std;

const int Max = 303;
const int WALL = -100;
int field[Max][Max];
int N, M, K;

bool visited[Max][Max];

bool check_move_dfs(int x, int y, int player)
{
	if (x < 1 || x > N || y < 1 || y > M)
		return false;
	visited[x][y] = true;
	/// dfs found the way to the player's cross
	if (field[x][y] == player)
		return true;
	/// someone else's cell, it is impossible to continue the way further
	if (field[x][y] != -player)
		return false;
	/// in this cell, the player's fortress, we are trying to find a way to his cross
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int new_x = x + i;
			int new_y = y + j;
			if (!visited[new_x][new_y])
			{
				bool res = check_move_dfs(new_x, new_y, player);
				if (res)
					return true;
			}
		}
	}
	return false;
}

bool check_move(int x, int y, int player)
{
	/// cell coordinates are incorrect
	if (x < 1 || x > N || y < 1 || y > M)
		return false;
	/// this cell already belongs to the player
	if (field[x][y] == player)
		return false;
	if (field[x][y] == -player)
		return false;
	/// there is a wall in this cell
	if (field[x][y] == WALL)
		return false;
	/// in this cell is the fortress of another player
	if (field[x][y] < 0)
		return false;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			visited[i][j] = false;
		}
	}
	int old_number = field[x][y];
	field[x][y] = -player;
	bool result = check_move_dfs(x, y, player);
	field[x][y] = old_number;
	return result;
}

int number_crosses;
int qx[Max * Max];
int qy[Max * Max];
int attack_moves;
int attack_moves_x[5], attack_moves_y[5];
int reproduction_moves;
int reprod_moves_x[5], reprod_moves_y[5];

bool check_move_existence(int player)
{
	// multi-start bfs (start from all crosses)
	number_crosses = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			visited[i][j] = false;
			if (field[i][j] == player)
			{
				visited[i][j] = true;
				number_crosses += 1;
				qx[number_crosses] = i;
				qy[number_crosses] = j;
			}
		}
	}
	int visited_cells = number_crosses;
	int ind = 1;
	attack_moves = 0;
	reproduction_moves = 0;
	while (ind <= visited_cells)
	{
		int x = qx[ind];
		int y = qy[ind];
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				int new_x = x + i;
				int new_y = y + j;
				if (new_x < 1 || new_x > N || new_y < 1 || new_y > M)
				{
					continue;
				}
				if (visited[new_x][new_y] || field[new_x][new_y] == WALL)
				{
					continue;
				}
				visited[new_x][new_y] = true;
				// our fortress
				if (field[new_x][new_y] == -player)
				{
					visited_cells += 1;
					qx[visited_cells] = new_x;
					qy[visited_cells] = new_y;
					continue;
				}
				// opponent's cross
				if (field[new_x][new_y] > 0)
				{
					if (attack_moves < 3)
					{
						attack_moves += 1;
						attack_moves_x[attack_moves] = new_x;
						attack_moves_y[attack_moves] = new_y;
					}
				}
				// empty cell
				if (field[new_x][new_y] == 0)
				{
					if (reproduction_moves < 3)
					{
						reproduction_moves += 1;
						reprod_moves_x[reproduction_moves] = new_x;
						reprod_moves_y[reproduction_moves] = new_y;
					}
				}
			}
		}
		ind += 1;
		if (attack_moves == 3 && reproduction_moves == 3)
		{
			return true;
		}
	}
	if (attack_moves + reproduction_moves == 0)
	{
		return false;
	}
	return true;
}

bool check_win(int player)
{
	int score_player = 0;
	int empty_cells = 0;
	int wall_cells = 0;
	int score_other_players = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (abs(field[i][j]) == player)
			{
				score_player += 1;
				continue;
			}
			if (field[i][j] == 0)
			{
				empty_cells += 1;
				continue;
			}
			if (field[i][j] == WALL)
			{
				wall_cells += 1;
				continue;
			}
			score_other_players += 1;
		}
	}
	return score_player > score_other_players;
}

int count_moves;
int moves_x[9], moves_y[9], new_values[9];

void get_jury_move()
{
	// must run STRICTLY AFTER starting the function
	// check_move_existence(player_jury)
	count_moves = 0;
	// very stupid
	// we have to attack first and only then multiply
	for (int i = 1; i <= reproduction_moves; i++)
	{
		count_moves += 1;
		moves_x[count_moves] = reprod_moves_x[i];
		moves_y[count_moves] = reprod_moves_y[i];
		new_values[count_moves] = player_jury;
	}
	for (int i = 1; i <= attack_moves; i++)
	{
		count_moves += 1;
		moves_x[count_moves] = attack_moves_x[i];
		moves_y[count_moves] = attack_moves_y[i];
		new_values[count_moves] = -player_jury;
	}
	count_moves = min(1, count_moves);
	/*
	for (int Level = 1; Level <= 3; Level++)
	{
		if (Hard_Level == Level)
		{
			count_moves = min(Level, count_moves);
		}
	}
	*/
	for (int i = 1; i <= count_moves; i++)
	{
		int x = moves_x[i];
		int y = moves_y[i];
		field[x][y] = new_values[i];
	}
	return;
}

void print_field()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			printf("%d ", field[i][j]);
		}
		printf("\n");
	}
}

int score_player, score_jury;

void calc_results()
{
	score_player = 0;
	score_jury = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (abs(field[i][j]) == player_id)
				score_player += 1;
			if (abs(field[i][j]) == player_jury)
				score_jury += 1;
		}
	}
	return;
}

int main()
{
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> field[i][j];
		}
	}
	while (true)
	{
		int id_pl, cnt; cin >> id_pl >> cnt;
		if (cnt == 0)
		{
			if (check_move_existence(player_id))
			{
				return 3 - id_pl;
			}
			if (check_win(player_jury))
			{
				calc_results();
				printf("o\n");
				fflush(stdout);
				quitf(_wa, "WA. You have lost. Your score: %d, Score jury: %d, Hard Level: %d", score_player, score_jury, Hard_Level);
			}
			/// the jury program finishes the game
			while (check_move_existence(player_jury))
			{
				get_jury_move();
				if (check_win(player_jury))
				{
					calc_results();
					printf("o\n");
					fflush(stdout);
					quitf(_wa, "WA. You have lost. Your score: %d, Score jury: %d, Hard Level: %d", score_player, score_jury, Hard_Level);
				}
			}
			printf("o\n");
			fflush(stdout);
			calc_results();
			tout << score_player << " " << score_jury << " " << Hard_Level << endl;
			quitf(_ok, "OK: congratulations, you have won");
		}
		for (int i = 1; i <= cnt; i++)
		{
			int x = ouf.readInt(1, N, "row number");
			int y = ouf.readInt(1, M, "column number");
			if (check_move(x, y, player_id))
			{
				if (field[x][y] == 0)
					field[x][y] = player_id;
				else
					field[x][y] = -player_id;
			}
			else
			{
				printf("o\n");
				fflush(stdout);
				quitf(_wa, "WA: your program tried to make an incorrect move");
			}
		}
		if (check_move_existence(player_jury))
		{
			get_jury_move();
			printf("r\n");
			printf("%d %d\n", player_jury, count_moves);
			for (int i = 1; i <= count_moves; i++)
			{
				printf("%d %d\n", moves_x[i], moves_y[i]);
			}
			fflush(stdout);
		}
		else
		{
			if (check_win(player_id))
			{
				printf("o\n");
				fflush(stdout);
				calc_results();
				tout << score_player << " " << score_jury << " " << Hard_Level << endl;
				quitf(_ok, "OK: congratulations, you have won");
			}
			else
			{
				if (check_move_existence(player_id))
				{
					printf("r\n");
					printf("%d 0\n", player_jury);
					fflush(stdout);
				}
				else
				{
					calc_results();
					if (score_player > score_jury)
					{
						printf("o\n");
						fflush(stdout);
						tout << score_player << " " << score_jury << " " << Hard_Level << endl;
						quitf(_ok, "OK: congratulations, you have won");
					}
					else
					{
						printf("o\n");
						fflush(stdout);
						quitf(_wa, "WA. You have lost. Your score: %d, Score jury: %d, Hard Level: %d", score_player, score_jury, Hard_Level);
					}
				}
			}
		}
	}
	return 0;
}