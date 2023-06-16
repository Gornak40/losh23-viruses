#include "bits/stdc++.h"

using namespace std;

enum CellType {
    EMPTY, FORTRESS, CROSS, WALL
};

struct Cell {
    CellType type;
    int owner;
};

int n, m, k;
int g;

vector<vector<Cell>> info;

mt19937 rnd(123);

void read() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            if (x == 0) {
                info[i][j].type = CellType::EMPTY;
            } else if (x == -100) {
                info[i][j].type = CellType::WALL;
            } else if (x > 0) {
                info[i][j].type = CellType::CROSS;
                info[i][j].owner = x;
            } else {
                info[i][j].type = CellType::FORTRESS;
                info[i][j].owner = -x;
            }
        }
    }
}

struct Move {
    int x, y;
    int owner;

    Move(int x, int y, int owner) : x(x), y(y), owner(owner) {}

    Move() = default;
};

void update_move(const Move &move) {
    auto [x, y, owner] = move;
    if (info[x][y].type == CellType::EMPTY) {
        info[x][y].type = CellType::CROSS;
        info[x][y].owner = owner;
    } else if (info[x][y].type == CellType::CROSS) {
        info[x][y].type = CellType::FORTRESS;
        info[x][y].owner = owner;
    } else {
        assert(false);
    }
}

void output_move(const Move &move) {
    update_move(move);
    cout << ' ' << move.x + 1 << ' ' << move.y + 1;
}

void output_moves(vector<Move> &moves) {
    cout << g << ' ' << (int) moves.size();
    for (const auto &move: moves) {
        output_move(move);
    }
    cout << endl;
}

void update() {
    char ch;
    cin >> ch;
    if (ch == 'o') {
        exit(0);
    }
    for (int i = 0; i < k - 1; i++) {
        int id, cnt;
        cin >> id >> cnt;
        for (int j = 0; j < cnt; j++) {
            Move move{};
            move.owner = id;
            cin >> move.x >> move.y;
            move.x--;
            move.y--;
            update_move(move);
        }
    }
}

bool check_move(int i, int j) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

void move() {
    vector<vector<int>> type_move(n, vector<int>(m));
    vector<vector<bool>> used(n, vector<bool>(m));
    auto dfs = [&](auto &&dfs, int x, int y) -> void {
        assert(info[x][y].owner == g);
        used[x][y] = true;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int xx = x + dx;
                int yy = y + dy;
                if (!check_move(xx, yy)) {
                    continue;
                }
                if (info[xx][yy].owner != g) {
                    if (info[xx][yy].type == CellType::EMPTY) {
                        type_move[xx][yy] = 1;
                    }
                    if (info[xx][yy].type == CellType::CROSS) {
                        type_move[xx][yy] = 2;
                    }
                }
                if (!used[xx][yy] && info[xx][yy].owner == g) {
                    dfs(dfs, xx, yy);
                }
            }
        }
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!used[i][j] && info[i][j].type == CellType::CROSS && info[i][j].owner == g) {
                dfs(dfs, i, j);
            }
        }
    }
    vector<Move> valid_moves;
    vector<Move> best_moves;
    vector<Move> other_moves;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (type_move[i][j] == 2) {
                best_moves.emplace_back(i, j, g);
            } else if (type_move[i][j] == 1) {
                other_moves.emplace_back(i, j, g);
            }
        }
    }
    shuffle(best_moves.begin(), best_moves.end(), rnd);
    shuffle(other_moves.begin(), other_moves.end(), rnd);
    for (const auto &move: best_moves) {
        valid_moves.push_back(move);
    }
    for (const auto &move: other_moves) {
        valid_moves.push_back(move);
    }
    if ((int) valid_moves.size() > 3) {
        valid_moves.resize(3);
    }
    output_moves(valid_moves);
}


int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
    cin >> n >> m >> k;
    info.resize(n, vector<Cell>(m));
    cin >> g;
    read();
    while (true) {
        move();
        update();
    }
    return 0;
}