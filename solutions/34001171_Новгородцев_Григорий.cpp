#include <bits/stdc++.h>

using namespace std;

mt19937 rnd(57);
int N, M, K, MyNum;
int myParity = -1;
const pair<int, int> DELTA[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
                                 {1, 1}, {1, 0}, {1, -1}, {0, -1}};
const int ROCK = -100;
int MyCross, MyCastle;
bool isATTACKED = false;

vector<vector<int>> field;

struct Cell {
    int x, y;
};

bool inField(int i, int j) {
    if (i < 0 || j < 0 || i >= N || j >= M) return false;
    return true;
}

bool inField(Cell c) {
    if (c.x < 0 || c.y < 0 || c.x >= N || c.y >= M) return false;
    return true;
}

bool isConnector(int i, int j) {
    if (field[i][j] <= 0) return false;
    for (const auto & t : DELTA) {
        int ni = i + t.first, nj = j + t.second;
        if (!inField(ni, nj)) continue;
        if (field[ni][nj] == -field[i][j]) return true;
    }
    return false;
}

bool isDangerous(int i, int j) {
    for (int t = 0; t < 8; ++t) {
        int ni = i + DELTA[t].first, nj = j + DELTA[t].second;
        if (!inField({ni, nj})) continue;
        if (field[ni][nj] == MyNum && isConnector(ni, nj)) return true;
    }
    return false;
}

int findParity() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (field[i][j] == MyNum) {
                return (i + j) % 2;
            }
        }
    }
    return 0;
}

void input() {
    char status; cin >> status;
    if (status == 'o') exit(0);
    for (int i = 0; i < K - 1; ++i) {
        int num, a; cin >> num >> a;
        for (int j = 0; j < a; ++j) {
            int x, y; cin >> x >> y; x--; y--;
            if (field[x][y] == 0) {
                field[x][y] = num;
            } else {
                if (field[x][y] == MyNum) isATTACKED = true;
                field[x][y] = -num;
            }
        }
    }
}

bool isCorrectTurn(Cell v) {
    if (field[v.x][v.y] < 0) return false;
    if (field[v.x][v.y] == MyNum) return false;
    return true;
}

void updateTable(Cell v) {
    if (field[v.x][v.y] == 0) field[v.x][v.y] = MyNum;
    else field[v.x][v.y] = MyCastle;
}

void output(const vector<Cell>& turns) {
    cout << MyNum << ' ' << turns.size() << ' ';
    for (auto i : turns) {
        cout << i.x + 1 << ' ' << i.y + 1 << ' ';
    }
    cout << endl;
    cout.flush();
}

pair<vector<vector<int>>, vector<vector<Cell>>> bfs(vector<Cell> start) {
    vector<vector<int>> d(N, vector<int>(M, INT32_MAX));
    vector<vector<Cell>> p(N, vector<Cell>(M, {-1, -1}));
    deque<Cell> q;
    for (auto i : start) {
        d[i.x][i.y] = 0;
        q.push_back(i);
    }
    while (!q.empty()) {
        auto v = q.front();
        q.pop_front();
        for (int i = 0; i < 8; ++i) {
            Cell u = {v.x + DELTA[i].first, v.y + DELTA[i].second};
            if (!inField(u)) continue;
            if (field[u.x][u.y] != ROCK && (field[u.x][u.y] >= 0 || field[u.x][u.y] == MyCastle)
            && d[u.x][u.y] == INT32_MAX) {
                p[u.x][u.y] = v;
                if (field[u.x][u.y] == MyCastle) {
                    d[u.x][u.y] = d[v.x][v.y];
                    q.push_front(u);
                } else {
                    d[u.x][u.y] = d[v.x][v.y] + 1;
                    q.push_back(u);
                }
            }
        }
    }
    return {d, p};
}

struct Enemy {
    int dist;
    bool isDangerous, isConnector;
    Cell pos;
};

struct Children {
    int distFromEnemy, szMyComp;
    Cell pos;
};

bool operator<(const Children& a, const Children& b) {
    if (abs(a.szMyComp - b.szMyComp) <= 5) {
        return a.distFromEnemy > b.distFromEnemy;
    } else {
        if (min(a.szMyComp, b.szMyComp) <= 5) {
            return a.szMyComp > b.szMyComp;
        } else {
            return a.distFromEnemy > b.distFromEnemy;
        }
    }
}

bool operator<(const Enemy& a, const Enemy& b) {
    if (a.isDangerous == b.isDangerous) {
        if (a.isConnector == b.isConnector) {
            return a.dist < b.dist;
        }
        return a.isConnector > b.isConnector;
    }
    return a.isDangerous > b.isDangerous;
}

bool inTurns(const vector<Cell>& turns, const Cell& variant) {
    for (const auto& i : turns) {
        if (i.x == variant.x && i.y == variant.y) return true;
    }
    return false;
}

vector<vector<int>> compsNum;

void dfsComps(Cell v, int& cnt, int num) {
    compsNum[v.x][v.y] = num;
    cnt++;
    for (auto i : DELTA) {
        Cell u = {v.x + i.first, v.y + i.second};
        if (!inField(u) || field[u.x][u.y] != MyCastle) continue;
        if (compsNum[u.x][u.y] != -1) continue;
        dfsComps(u, cnt, num);
    }
}

void makeTurn() {
    vector<Cell> turns;
    vector<Cell> starts, startsEnemy;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (field[i][j] == MyNum) {
                starts.push_back({i, j});
            }
            if (field[i][j] > 0 && field[i][j] != MyNum) {
                startsEnemy.push_back({i, j});
            }
        }
    }
    auto [distFromMyCrosses, parents] = bfs(starts);
    auto [distFromEnemy, parentsEnemy] = bfs(startsEnemy);
    Enemy attack = {INT32_MAX, 0, 0, {-1, -1}};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (!isCorrectTurn({i, j})) continue;
            if (distFromMyCrosses[i][j] > 3 || field[i][j] <= 0 || field[i][j] == MyNum) continue;
            Enemy variant = {distFromMyCrosses[i][j], isDangerous(i, j),
                             isConnector(i, j), {i, j}};
            if (variant < attack) attack = variant;
        }
    }
    if (attack.dist < 3 || (isATTACKED && attack.dist == 3)) {
        vector<Cell> path;
        Cell vertex = attack.pos;
        while (distFromMyCrosses[vertex.x][vertex.y] > 0) {
            if (field[vertex.x][vertex.y] != MyCastle) {
                path.push_back(vertex);
            }
            updateTable(vertex);
            vertex = parents[vertex.x][vertex.y];
        }
        reverse(path.begin(), path.end());
        for (const auto& i : path) turns.push_back(i);
        auto tmp = bfs(starts);
        distFromMyCrosses = tmp.first; parents = tmp.second;
        if (rnd() % 2 == 0 && turns.size() < 3) {
            compsNum.assign(N, vector<int>(M, -1));
            vector<int> compsSz;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (compsNum[i][j] == -1 && field[i][j] == MyCastle) {
                        int cnt = 0;
                        dfsComps({i, j}, cnt, (int)compsSz.size());
                        compsSz.push_back(cnt);
                    }
                }
            }
            vector<Children> variantsForChildren;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (field[i][j] == 0 && distFromMyCrosses[i][j] == 1 && isConnector(i, j)) {
                        variantsForChildren.push_back({distFromEnemy[i][j], compsSz[compsNum[i][j]], {i, j}});
                    }
                }
            }
            sort(variantsForChildren.begin(), variantsForChildren.end());
            if (!variantsForChildren.empty()) {
                turns.push_back(variantsForChildren[0].pos);
                updateTable(variantsForChildren[0].pos);
            }
        }
        while (turns.size() < 3) {
            Enemy newAttack = {INT32_MAX, 0, 0, {-1, -1}};
            for (const auto & i : DELTA) {
                Cell newPos = {attack.pos.x + i.first, attack.pos.y + i.second};
                if (!inField(newPos)) continue;
                if (!isCorrectTurn(newPos)) continue;
                if (field[newPos.x][newPos.y] == 0) continue;
                Enemy variant = {1, isDangerous(newPos.x, newPos.y),
                                 isConnector(newPos.x, newPos.y), newPos};
                if (variant < newAttack) newAttack = variant;
            }
            if (newAttack.dist == 1) {
                attack = newAttack;
                updateTable(attack.pos);
                turns.push_back(attack.pos);
                continue;
            }
            break;
        }
    }
    int dontWalkBecauseEnemy = 0;
    if (turns.size() < 3) {
        vector<Cell> variantsForSimpleCross;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (distFromMyCrosses[i][j] == 1 && (i + j) % 2 == myParity &&
                    field[i][j] == 0) {
                    if (distFromEnemy[i][j] <= 2) {
                        dontWalkBecauseEnemy++;
                        continue;
                    }
                    variantsForSimpleCross.push_back({i, j});
                }
            }
        }
        shuffle(variantsForSimpleCross.begin(), variantsForSimpleCross.end(), rnd);
        for (int i = 0; i < (int)variantsForSimpleCross.size() && turns.size() < 3; ++i) {
            if (!isCorrectTurn({variantsForSimpleCross[i].x, variantsForSimpleCross[i].y})) continue;
            updateTable({variantsForSimpleCross[i].x, variantsForSimpleCross[i].y});
            turns.push_back(variantsForSimpleCross[i]);
        }
        int pos = (int)turns.size() - 1;
        while (turns.size() < 3 && pos >= 0) {
            Cell v = turns[pos];
            for (const auto& i : DELTA) {
                Cell u = {v.x + i.first, v.y + i.second};
                if (inField(u) && (u.x + u.y) % 2 == myParity && !inTurns(turns, u) &&
                    isCorrectTurn(u) && distFromEnemy[u.x][u.y] > 2) {
                    turns.push_back(u);
                    updateTable(u);
                    if (turns.size() >= 3) break;
                }
            }
            pos--;
        }
    }
    if (turns.empty()) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (distFromMyCrosses[i][j] == 1 && distFromEnemy[i][j] > 2 &&
                    isCorrectTurn({i, j})) {
                    field[i][j] = MyNum;
                    updateTable({i, j});
                    turns.push_back({i, j});
                    if (dontWalkBecauseEnemy >= 3) break;
                    if (turns.size() == 3) break;
                }
            }
            if (dontWalkBecauseEnemy >= 3 && !turns.empty()) break;
            if (turns.size() == 3) break;
        }
    }
    if (turns.empty()) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (isCorrectTurn({i, j}) && distFromMyCrosses[i][j] == 1) {
                    field[i][j] = MyNum;
                    turns.push_back({i, j});
                    break;
                }
            }
           if (!turns.empty()) break;
        }
    }
    output(turns);
    input();
}

void init() {
    cin >> N >> M >> K >> ws;
    cin >> MyNum;
    MyCross = MyNum;
    MyCastle = -MyNum;
    field.resize(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> field[i][j];
        }
    }
    if (myParity == -1) myParity = findParity();
}

int main() {
    init();
    while (true) {
        makeTurn();
    }
    return 0;
}