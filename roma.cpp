#include <iostream>
#include <cassert>
#include <vector>
#include <deque>
#include <algorithm>
#include <random>
 
std::mt19937 rnd(987654321);
 
std::vector<std::vector<int>> grid;
 
void print_grid() {
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			std::cerr << grid[i][j] << ' ';
		}
		std::cerr << '\n';
	}
}
 
const int INF = 1e9;
 
const std::pair<int, int> delta[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
 
int main() {
	int n, m, k;
	std::cin >> n >> m >> k;
	assert(k == 2);
	int g;
	std::cin >> g;
	int e = 3 - g;
 
	grid.assign(n, std::vector<int> (m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> grid[i][j];
		}
	}
//	std::cerr << grid[n - 1][m - 1] << std::endl;
 
	while (true) {
		std::vector<std::pair<int, int>> ans;
		for (int it = 0; it < 3; ++it) {
			std::vector<std::vector<int>> dist_self(n, std::vector<int>(m, INF));
			{
				std::deque<std::pair<int, int>> d;
 
				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < m; ++j) {
						if (grid[i][j] == g) {
							dist_self[i][j] = 0;
							d.emplace_back(i, j);
						}
					}
				}
 
				while (!d.empty()) {
					auto [x, y] = d.front();
					d.pop_front();
 
					for (auto [dx, dy]: delta) {
						if (x + dx < 0 || x + dx >= n || y + dy < 0 || y + dy >= m) continue;
						if (dist_self[x + dx][y + dy] == INF) {
							if (dist_self[x][y] == 0 && (grid[x + dx][y + dy] == g || grid[x + dx][y + dy] == -g)) {
								dist_self[x + dx][y + dy] = dist_self[x][y];
								d.emplace_front(x + dx, y + dy);
							} else if (grid[x + dx][y + dy] == 0 || grid[x + dx][y + dy] == e) {
								dist_self[x + dx][y + dy] = dist_self[x][y] + 1;
								d.emplace_back(x + dx, y + dy);
							}
						}
					}
				}
			}
 
			std::vector<std::vector<int>> dist_enemy(n, std::vector<int>(m, INF));
			{
				std::deque<std::pair<int, int>> d;
 
				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < m; ++j) {
						if (grid[i][j] == e) {
							dist_enemy[i][j] = 0;
							d.emplace_back(i, j);
						}
					}
				}
 
				while (!d.empty()) {
					auto [x, y] = d.front();
					d.pop_front();
 
					for (auto [dx, dy]: delta) {
						if (x + dx < 0 || x + dx >= n || y - dy < 0 || y + dy >= m) continue;
						if (dist_enemy[x + dx][y + dy] == INF) {
							if (dist_enemy[x][y] == 0 && (grid[x + dx][y + dy] == e || grid[x + dx][y + dy] == -e)) {
								dist_enemy[x + dx][y + dy] = dist_enemy[x][y];
								d.emplace_front(x + dx, y + dy);
							} else if (grid[x + dx][y + dy] == 0 || grid[x + dx][y + dy] == g) {
								dist_enemy[x + dx][y + dy] = dist_enemy[x][y] + 1;
								d.emplace_back(x + dx, y + dy);
							}
						}
					}
				}
			}
 
			std::vector<std::vector<int>> dist_enemy2(n, std::vector<int>(m, INF));
			{
				std::deque<std::pair<int, int>> d;
 
				for (int i = 0; i < n; ++i) {
					for (int j = 0; j < m; ++j) {
						if (grid[i][j] == e) {
							dist_enemy2[i][j] = 0;
							d.emplace_back(i, j);
						}
					}
				}
 
				while (!d.empty()) {
					auto [x, y] = d.front();
					d.pop_front();
 
					for (auto [dx, dy]: delta) {
						if (x + dx < 0 || x + dx >= n || y - dy < 0 || y + dy >= m) continue;
						if (dist_enemy2[x + dx][y + dy] == INF) {
							if (dist_enemy2[x][y] == 0 && grid[x + dx][y + dy] == e) {
								dist_enemy2[x + dx][y + dy] = dist_enemy2[x][y];
								d.emplace_front(x + dx, y + dy);
							} else if (grid[x + dx][y + dy] == 0 || grid[x + dx][y + dy] == g) {
								dist_enemy2[x + dx][y + dy] = dist_enemy2[x][y] + 1;
								d.emplace_back(x + dx, y + dy);
							}
						}
					}
				}
			}
 
			std::vector<std::pair<int, int>> virus_moves, base_moves;
 
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j) {
					if (dist_self[i][j] == 1) {
						if (grid[i][j] == 0) {
							virus_moves.emplace_back(i, j);
						} else if (grid[i][j] == e) {
							base_moves.emplace_back(i, j);
						}
					}
				}
			}
 
			if (!base_moves.empty()) {
				auto move = base_moves[rnd() % base_moves.size()];
				ans.push_back(move);
				auto [x, y] = move;
				grid[x][y] = -g;
			} else if (!virus_moves.empty()) {
				std::shuffle(virus_moves.begin(), virus_moves.end(), rnd);
				std::sort(virus_moves.begin(), virus_moves.end(), [&](auto c1, auto c2) {
					auto [i1, j1] = c1;
					auto [i2, j2] = c2;
					return dist_enemy2[i1][j1] > dist_enemy2[i2][j2];
				});
				auto move = virus_moves.back();
				auto [x, y] = move;
				if (dist_enemy[x][y] == 1) {
					ans.emplace_back(x, y);
					grid[x][y] = g;
				} else {
					while (!virus_moves.empty() && dist_enemy[virus_moves.back().first][virus_moves.back().second] < n / 2) {
						virus_moves.pop_back();
					}
					if (virus_moves.empty()) {
						ans.emplace_back(x, y);
						grid[x][y] = g;
					} else {
						auto move = virus_moves.back();
						auto [x, y] = move;
						ans.emplace_back(x, y);
						grid[x][y] = g;
					}
				}
			} else {
				break;
			}
		}
 
		std::cout << g << ' ' << ans.size() << ' ';
		for (auto [x, y] : ans) {
			std::cout << x + 1 << ' ' << y + 1 << ' ';
		}
		std::cout << std::endl;
 
//        print_grid();
 
		char status;
		std::cin >> status;
		if (status == 'o') {
			return 0;
		}
		{
			int ii, a;
			std::cin >> ii >> a;
			for (int i = 0; i < a; ++i) {
				int x, y;
				std::cin >> x >> y;
				x--, y--;
				if (grid[x][y] == 0) {
					grid[x][y] = e;
				} else {
					grid[x][y] = -e;
				}
			}
		}
 
//        print_grid();
	}
}
