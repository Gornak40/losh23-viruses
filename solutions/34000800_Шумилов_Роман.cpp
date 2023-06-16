#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
const int INF = INT_MAX;

int n, m, my_id, color = 1;
int f[300][300];
int used[300][300];
int dist[300][300];
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool available_cell(int x, int y) {
    return 0 <= x and x < n and 0 <= y and y < m and (abs(f[x][y]) == my_id or f[x][y] >= 0);
}

bool check_cell(int x, int y) {
    return 0 <= x and x < n and 0 <= y and y < m;
}

void bfs() {
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dist[i][j] = -1;
            if (f[i][j] > 0 and f[i][j] != my_id) {
                dist[i][j] = 0;
                q.emplace(i, j);
            }
        }
    }
    if (q.empty()) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dist[i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 8; i++) {
            int xn = x + dx[i];
            int yn = y + dy[i];
            if (check_cell(xn, yn) and dist[xn][yn] == -1) {
                dist[xn][yn] = dist[x][y] + 1;
                q.emplace(xn, yn);
            }
        }
    }
}

void dfs(int x, int y) {
    used[x][y] = color;
    for (int i = 0; i < 8; i++) {
        int xn = x + dx[i];
        int yn = y + dy[i];
        if (available_cell(xn, yn) and used[xn][yn] != color) {
            if (abs(f[xn][yn]) == my_id) dfs(xn, yn);
            else used[xn][yn] = color;
//            else if (f[xn][yn] == 0) empty_cells.emplace_back(xn, yn);
//            else enemy_cells.emplace_back(xn, yn);
        }
    }
}

vector<vector<pair<int, int>>> find_all_available_cells() {
    bfs();

    color++;
    vector<vector<pair<int, int>>> cells(601);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (used[i][j] != color and f[i][j] == my_id) {
                dfs(i, j);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (used[i][j] == color and abs(f[i][j]) != my_id) {
                cells[dist[i][j]].emplace_back(i, j);
            }
        }
    }
    return cells;
}

void make_move(int id_player, int x, int y) {
    if (f[x][y] == 0) f[x][y] = id_player;
    else f[x][y] = -id_player;
}

void input_player() {
    int id_player, cnt_moves;
    cin >> id_player >> cnt_moves;
    while (cnt_moves--) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        make_move(id_player, x, y);
    }
}

signed main() {
    int cnt_players;
    cin >> n >> m >> cnt_players;
    cin >> my_id;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> f[i][j];
        }
    }

    char game_status;
    while (true) {
        string output = to_string(my_id) + " ";
        vector<pair<int, int>> moves;
        for (int i = 0; i < 3; i++) {
            auto l = find_all_available_cells();

            bool status = false;
            for (int d = 0; d <= 600; d++) {
                if (!l[d].empty()) {
                    moves.push_back(l[d][rnd() % l[d].size()]);
                    make_move(my_id, moves.back().ff, moves.back().ss);
                    status = true;
                    break;
                }
            }
            if (!status) break;
        }
        output += to_string(moves.size());
        for (auto [x, y] : moves) output += " " + to_string(x + 1) + " " + to_string(y + 1);
        cout << output << endl;

        cin >> game_status;
        if (game_status == 'o') return 0;

        for (int i = 0; i < cnt_players - 1; i++) {
            input_player();
        }
    }
}
