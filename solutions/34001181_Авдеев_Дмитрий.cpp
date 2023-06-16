#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>
#include <random>
#include <array>
#include <deque>
#include <sstream>

using namespace std;

typedef long long ll;
mt19937 gen(time(0));

const int INF = 2e9, MAXN = 300;

vector<vector<bool>> used(MAXN + 2, vector<bool>(MAXN + 2, false));

vector<int> X = { 0, 0, 1, 1, 1, -1, -1, -1 };
vector<int> Y = { 1, -1, 0, 1, -1, 0, 1, -1 };
vector<vector<int>> a;
int n, m, k, g;

vector<pair<int, int>> can;
void dfs(pair<int, int> v, int help) {
	used[v.first][v.second] = true;
	if (a[v.first][v.second] != g && a[v.first][v.second] != -g) {
		can.push_back(v);
	}
	if (help == 0) return;
	for (int i = 0; i < 8; i++) {
		if (a[v.first + X[i]][v.second + Y[i]] == 0 || (a[v.first + X[i]][v.second + Y[i]] > 0 && a[v.first + X[i]][v.second + Y[i]] != g)) { // пустая клетка или крестик врага
			if (!used[v.first + X[i]][v.second + Y[i]]) {
				dfs({ v.first + X[i], v.second + Y[i] }, help - 1);
			}
		}
		if (a[v.first + X[i]][v.second + Y[i]] == -g) {
			if (!used[v.first + X[i]][v.second + Y[i]]) {
				dfs({ v.first + X[i], v.second + Y[i] }, help);
			}
		}
	}
}

void solve() {
	cin >> n >> m >> k >> g;
	a.assign(n + 2, {});
	for (int i = 0; i <= n + 1; i++) {
		a[i].assign(m + 2, -100);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	char AOAAO;
	int B, u1, v1, id;
	while (true) {
		vector<pair<int, int>> A;
		for (int steps = 0; steps < 3; steps++) {
			int cnt_x = 0;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					if (a[i][j] == g) {
						cnt_x++;
					}
				}
			}
			queue<pair<int, int>> q;
			vector<vector<int>> dist(n + 2, vector<int>(m + 2, INF));
			vector<vector<bool>> used2(n + 2, vector<bool>(m + 2, false));
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					if (a[i][j] > 0 && a[i][j] != g) { // крестик врага
						dist[i][j] = 0;
						used2[i][j] = true;
						q.push({ i, j });
					}
				}
			}
			while (!q.empty()) {
				pair<int, int> p = q.front(); q.pop();
				for (int i = 0; i < 8; i++) {
					if (used2[p.first + X[i]][p.second + Y[i]] || a[p.first + X[i]][p.second + Y[i]] < 0) continue;
					used2[p.first + X[i]][p.second + Y[i]] = true;
					dist[p.first + X[i]][p.second + Y[i]] = dist[p.first][p.second] + 1;
					q.push({ p.first + X[i], p.second + Y[i] });
				}
			}


			can.clear();
			for (int i = 0; i <= n + 1; i++) {
				fill(used[i].begin(), used[i].end(), false);
			}
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					if (used[i][j] || a[i][j] != g) continue;
					dfs({ i, j }, 1);
				}
			}
			int mn = INF;
			pair<int, int> cur_steps;
			int mx = -INF;
			pair<int, int> cur_steps_mx;
			for (pair<int, int> p : can) {
				if (dist[p.first][p.second] < mn) {
					mn = dist[p.first][p.second];
					cur_steps = p;
				}
				if (dist[p.first][p.second] > mx) {
					mx = dist[p.first][p.second];
					cur_steps_mx = p;
				}
			}
			if (cnt_x < 9 && mx != -INF) {
				A.push_back(cur_steps_mx);

				if (a[A.back().first][A.back().second] == 0) {
					a[A.back().first][A.back().second] = g;
				}
				else {
					a[A.back().first][A.back().second] = -g;
				}
			}
			else if (mn >= 4 && mn != INF) { // фаза 2. Пытаемся сделать так чтобы нас не *******.
				A.push_back(cur_steps);

				if (a[A.back().first][A.back().second] == 0) {
					a[A.back().first][A.back().second] = g;
				}
				else {
					a[A.back().first][A.back().second] = -g;
				}
			}
			else if (mn == 3 && mx > 3) { // не лезем на ражон
				A.push_back(cur_steps_mx);

				if (a[A.back().first][A.back().second] == 0) {
					a[A.back().first][A.back().second] = g;
				}
				else {
					a[A.back().first][A.back().second] = -g;
				}
			}
			else if (mn + steps + 1 <= 3) { // фаза 1. можем попытаться ******* противника !!!
				A.push_back(cur_steps);

				if (a[A.back().first][A.back().second] == 0) {
					a[A.back().first][A.back().second] = g;
				}
				else {
					a[A.back().first][A.back().second] = -g;
				}
			}
			else if (!can.empty() && A.empty()) { // фаза 3. Очень жаль(((
				int ind = abs(int(gen())) % can.size();
				A.push_back(can[ind]);

				if (a[A.back().first][A.back().second] == 0) {
					a[A.back().first][A.back().second] = g;
				}
				else {
					a[A.back().first][A.back().second] = -g;
				}
			}
			else { // фаза 4. Можем просто скипнуть)))
				break;
			}
		}
		cout << g << ' ' << A.size();
		if (!A.empty()) {
			for (pair<int, int> p : A) {
				cout << ' ' << p.first << ' ' << p.second;
			}
		}
		cout << endl;
		cin >> AOAAO;
		if (AOAAO == 'o') {
			exit(0);
		}
		for (int i = 0; i < k - 1; i++) {
			cin >> id >> B;
			while (B--) {
				cin >> u1 >> v1;
				if (a[u1][v1] == 0) {
					a[u1][v1] = id;
				}
				else {
					a[u1][v1] = -id;
				}
			}
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int t = 1;
	//cin >> t;
	while (t--) {
		solve();
	}
}//////