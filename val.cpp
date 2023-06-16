#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 303;
const int MAXM = MAXN;
const int BAD = -100;

int n, m, k, timer;
int A[MAXN][MAXM], used[MAXN][MAXN];

void out(int pl) {
//	cerr << "SUGOMUS " << pl << endl;
	cout << pl << endl;
	exit(0);
}

inline int get_cell(int x, int y) {
	if (x < 0 || n < x || y < 0 || m < y)
		return BAD;
	return A[x][y];
}

bool dfs(int pl, int x, int y) {
	used[x][y] = timer;
	for (int dx = -1; dx <= 1; ++dx)
		for (int dy = -1; dy <= 1; ++dy) {
			int c = get_cell(x + dx, y + dy);
			if (c == pl) return true;
			if (c == -pl && (used[x + dx][y + dy] != timer || dfs(pl, x + dx, y + dy)))
				return true;
		}
	return false;
}

bool make_move(int pl, int x, int y) {
	int c = get_cell(x, y);
	if (c < 0 || c == pl) return false;
	++timer;
	if (!dfs(pl, x, y)) return false;
	A[x][y] = (!c ? pl : -pl);
	return true;
}

void dfs2(int pl, int x, int y) {
	used[x][y] = timer;
	for (int dx = -1; dx <= 1; ++dx)
		for (int dy = -1; dy <= 1; ++dy) {
			int c = get_cell(x + dx, y + dy);
			if (c != -pl && c < 0) continue;
			if (used[x + dx][y + dy] != timer)
				dfs2(pl, x + dx, y + dy);
		}
}

int hard(int pl) {
	++timer;
	for (int x = 0; x < n; ++x)
		for (int y = 0; y < m; ++y)
			if (A[x][y] == pl && used[x][y] != timer)
				dfs2(pl, x, y);
	int pl_score = 0, op_score = 0;
	for (int x = 0; x < n; ++x)
		for (int y = 0; y < m; ++y) {
			if (used[x][y] == timer) ++op_score;
			else if (abs(A[x][y]) == pl) ++pl_score;
		}
	// ALERT
//	cerr << pl_score << ',' << op_score << endl;
	return (pl_score <= op_score ? pl : 3 - pl);
}

int main() {
	cin >> n >> m >> k;
	for (int x = 0; x < n; ++x)
		for (int y = 0; y < m; ++y)
			cin >> A[x][y];
	while (true) {
		int pl, k; cin >> pl >> k;
	//	cerr << ": " << pl << ' ' << k << endl;
		if (!k) out(hard(3 - pl));
		for (int i = 0; i < k; ++i) {
			int x, y; cin >> x >> y, --x, --y;
			if (!make_move(pl, x, y)) out(3 - pl);
		}
		cout << 0 << endl;
		/*
		for (int x = 0; x < n; ++x) {
			for (int y = 0; y < m; ++y)
				cerr << A[x][y] << ' ';
			cerr << endl;
		}
		cerr << endl;*/
	}
}