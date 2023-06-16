#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <random>
#include <array>

using namespace std;

bool used[302][302], cold[302][302];
int mtr[8][2] = {{-1, -1}, {-1, 0}, {-1, 1},
                 {0, -1}, {0, 1},
                 {1, -1}, {1, 0}, {1, 1}};
int field[302][302], dist[302][302], dist2[302][302], n, m, k, inf = 1e9, com;
set <array <int, 2>> moves;
vector <array <int, 2>> turn;

void dfs(int x, int y) {
    used[x][y] = 1;
    int x1, y1;
    for (auto & i : mtr) {
        x1 = x + i[0], y1 = y + i[1];
        if (!used[x1][y1] && abs(field[x1][y1]) == k)
            dfs(x1, y1);
    }
}

void get_frt() {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            used[i][j] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (!used[i][j] && field[i][j] == k)
                dfs(i, j);
}

void bfs(int x, int y, int p) {
    queue <array <int, 2>> q;
    q.push({x, y});
    dist[x][y] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cold[i][j] = 0;
    int x1, y1;
    cold[x][y] = 1;
    while (!q.empty()) {
        x = q.front()[0], y = q.front()[1];
        for (auto & i : mtr) {
            x1 = x + i[0], y1 = y + i[1];
            if (dist[x1][y1] != 0 && !cold[x1][y1] && field[x1][y1] >= 0)
                q.push({x1, y1});
            if (!cold[x1][y1] && (field[x1][y1] >= 0 || field[x1][y1] == -p)) {
                dist[x1][y1] = abs(field[x1][y1]) == p ? 0 : min(dist[x][y] + 1, dist[x1][y1]);
                cold[x1][y1] = 1;
            }
        }
        q.pop();
    }
}

void calc_dist(int p) {
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            dist[i][j] = inf;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (dist[i][j] == inf && field[i][j] == p)
                bfs(i, j, p);
}

void get_moves() {
    moves.erase(moves.begin(), moves.end());
    get_frt();
    int x1, y1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (used[i][j])
                for (auto & u : mtr) {
                    x1 = i + u[0], y1 = j + u[1];
                    if (field[x1][y1] != k && field[x1][y1] >= 0)
                        moves.insert({x1, y1});
                }
}

void move(int x, int y, int p) {
    field[x][y] = (field[x][y] ? -p : p);
}

void gen_turn() {
    while (!turn.empty())
        turn.pop_back();
    calc_dist(3 - k);
    do {
        auto prev_turn = turn;
        get_moves();
        vector <array <int, 2>> v;
        int mn = inf;
        for (auto el : moves) {
            if (dist[el[0]][el[1]] < mn) {
                mn = dist[el[0]][el[1]];
                while (!v.empty())
                    v.pop_back();
                if (dist[el[0]][el[1]] == mn)
                    v.push_back({el[0], el[1]});
            }
        }
        if (!v.empty()) {
            auto c = v[rand() % v.size()];
            turn.push_back({c[0], c[1]});
            move(c[0], c[1], k);
        }
        if (prev_turn == turn) {
            cout << k << ' ' << 0 << endl;
        }
    } while (turn.size() < 3 && !moves.empty());
    cout << k << " " << turn.size() << " ";
    for (int i = 0; i < turn.size(); ++i)
        cout << turn[i][0] << " " << turn[i][1] << " ";
    cout << endl;
}

int main() {
    cin >> n >> m >> com;
    cin >> k;
    srand(time(0));
    for (int i = 0; i < n + 2; ++i)
        field[i][0] = field[i][m + 1] = -100;
    for (int i = 0; i < m + 2; ++i)
        field[0][i] = field[n + 1][i] = -100;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> field[i][j];
    while (true) {
        gen_turn();
        string c;
        cin >> c;
        if (c == "o")
            exit(0);
        int t, x, y;
        cin >> t >> t;
        for (int i = 0; i < t; ++i) {
            cin >> x >> y;
            move(x, y, 3 - k);
        }
    }
}