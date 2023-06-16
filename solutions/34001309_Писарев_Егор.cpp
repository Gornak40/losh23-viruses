#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;

const string OVER = "o";
const string RUNNING = "r";
const int ROCKVAL = -100;
const int FREEVAL = 0;

enum types { FREE, ROCK, ALIVE, TOWER };
struct Cell {
    int owner;
    types type;
    Cell() {
        owner = -1;
        type = FREE;
    }
};

struct CellMove {
    int dist;
    int parity;
    int hastower;
    int eatsmycross;
    int i;
    int j;
    int mydist;
    unsigned rndval;
    int cntfree;
    // int mytower;
    // int oppTower;
    CellMove() {
        dist = 0;
        mydist = 0;
        parity = 0;
        hastower = 0;
        eatsmycross = 0;
        rndval = 0;
        cntfree = 0;
        // mytower = false;
        // oppTower = false;
        i = 0;
        j = 0;
    }
};

int sign(int a) {
    return (a >= 0) - (a < 0);
}

struct CmpCellMove {
    bool operator()(const CellMove& a, const CellMove& b) const {
        // if (a.eatsmycross || b.eatsmycross) {
        //     return make_tuple(-a.eatsmycross, a.mydist, a.parity, a.rndval) < make_tuple(-b.eatsmycross, b.mydist, b.parity, b.rndval);
        // }
        if (a.hastower || b.hastower) {
            return make_tuple(-a.hastower, -a.cntfree, a.dist, a.rndval) < make_tuple(-b.hastower, -b.cntfree, b.dist, b.rndval);
        }
        if (a.dist == 0 || b.dist == 0) {
            // return make_tuple(a.dist, a.mydist, a.parity, a.rndval) < make_tuple(b.dist, b.mydist, b.parity, b.rndval);
            if (a.dist == 0 && b.dist == 0) {
                return make_tuple(a.mydist, -a.cntfree, a.rndval) < make_tuple(b.mydist, -b.cntfree, b.rndval);
            } else if ((a.dist == 0 && a.mydist <= 2) || (b.dist == 0 && b.mydist <= 2)) {
                return make_tuple(a.dist, a.mydist, -a.cntfree, a.rndval) < make_tuple(b.dist, b.mydist, -b.cntfree, b.rndval);
            } else {
                return make_tuple(a.dist, -a.cntfree, a.rndval) > make_tuple(b.dist, -b.cntfree, b.rndval);
            }
            // } else if (a.dist == 0) {
            //     return make_tuple(a.mydist, a.parity, a.rndval) < make_tuple(3, b.parity, b.rndval);
            // } else {
            //     return make_tuple(b.mydist, b.parity, b.rndval) >= make_tuple(3, a.parity, a.rndval);
            // }
        }
        if (a.dist <= 3 || b.dist <= 3) {
            // return make_tuple(-sign(a.dist - 3), abs(a.dist - 3), a.parity, a.rndval) < make_tuple(-sign(b.dist - 3), abs(b.dist - 3), b.parity, b.rndval);
            return make_tuple(a.dist, a.parity, a.rndval) > make_tuple(b.dist, b.parity, b.rndval);
        }
        return make_tuple(a.parity, a.dist, a.rndval) > make_tuple(b.parity, b.dist, b.rndval);
    }
};

pair<int, int> paths[8] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

int n, m, k;
int myId;

vector<vector<Cell>> table;

int lastnum;
vector<int> rndnums;

mt19937 rnd;

void init() {
    rndnums.resize(n * m);
    iota(rndnums.begin(), rndnums.end(), 0);
    shuffle(rndnums.begin(), rndnums.end(), rnd);
    table.assign(n, vector<Cell>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cvalue;
            cin >> cvalue;
            if (cvalue == ROCKVAL) {
                table[i][j].owner = -1;
                table[i][j].type = ROCK;
            } else if (cvalue == FREEVAL) {
                table[i][j].owner = -1;
                table[i][j].type = FREE;
            } else if (cvalue < 0) {
                table[i][j].owner = -cvalue;
                table[i][j].type = TOWER;
            } else if (cvalue > 0) {
                table[i][j].owner = cvalue;
                table[i][j].type = ALIVE;
            } else {
                assert(false);
            }
        }
    }
}

void readTable() {
    for (int i = 0; i < k - 1; i++) {
        int player, cnt;
        cin >> player >> cnt;
        int x, y;
        for (int move = 0; move < cnt; move++) {
            cin >> x >> y;
            x--;
            y--;
            if (table[x][y].type == FREE) {
                table[x][y].owner = player;
                table[x][y].type = ALIVE;
            } else {
                table[x][y].owner = player;
                table[x][y].type = TOWER;
            }
        }
    }
}

bool readState() {
    string status;
    cin >> status;
    if (status == OVER) {
        return false;
    } else {
        readTable();
        return true;
    }
}

bool insideTable(int i, int j) {
    return (i >= 0 && j >= 0 && i < n && j < m);
}

void dfs(int i, int j, int playerId, vector<vector<int>>& availablePlayerIds, vector<vector<bool>>& used) {
    used[i][j] = true;
    availablePlayerIds[i][j] = playerId;
    shuffle(paths, paths + 8, rnd);
    for (auto [di, dj] : paths) {
        if (insideTable(i + di, j + dj)) {
            if (!used[i + di][j + dj] && table[i + di][j + dj].owner == playerId) {
                dfs(i + di, j + dj, playerId, availablePlayerIds, used);
            }
        }
    }
}

void runDfs(vector<vector<int>>& availablePlayerIds) {
    vector<vector<bool>> used(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!used[i][j] && table[i][j].type == ALIVE) {
                dfs(i, j, table[i][j].owner, availablePlayerIds, used);
            }
        }
    }
}

void myBfs(const vector<vector<int>>& availablePlayerIds, vector<vector<int>>& dists, vector<vector<pair<int, int>>>& prevs) {
    vector<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (availablePlayerIds[i][j] == myId) {
                dists[i][j] = 0;
                q.emplace_back(i, j);
            }
        }
    }

    for (int iter = 0; iter < (int)q.size(); iter++) {
        shuffle(paths, paths + 8, rnd);
        auto [i, j] = q[iter];
        for (auto [di, dj] : paths) {
            if (insideTable(i + di, j + dj)) {
                if (table[i + di][j + dj].owner != myId && (table[i + di][j + dj].type == FREE || table[i + di][j + dj].type == ALIVE)) {
                    // maybe alive cells of the opponent should be removed in the condition?
                    if (dists[i + di][j + dj] > dists[i][j] + 1) {
                        dists[i + di][j + dj] = dists[i][j] + 1;
                        prevs[i + di][j + dj] = make_pair(i, j);
                        q.emplace_back(i + di, j + dj);
                    }
                }
            }
        }
    }
}

void opponentBfs(const vector<vector<int>>& availablePlayerIds, vector<vector<int>>& dists) {
    vector<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (availablePlayerIds[i][j] != myId && availablePlayerIds[i][j] != -1) {
                dists[i][j] = 0;
                q.emplace_back(i, j);
            }
        }
    }

    for (int iter = 0; iter < (int)q.size(); iter++) {
        shuffle(paths, paths + 8, rnd);
        auto [i, j] = q[iter];
        for (auto [di, dj] : paths) {
            if (insideTable(i + di, j + dj)) {
                if (table[i + di][j + dj].type == FREE || table[i + di][j + dj].type == ALIVE) {
                    if (dists[i + di][j + dj] > dists[i][j] + 1) {
                        dists[i + di][j + dj] = dists[i][j] + 1;
                        q.emplace_back(i + di, j + dj);
                    }
                }
            }
        }
    }
}

void findOpponentTowers(vector<vector<bool>>& opponentTowerNeighbour) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i][j].owner == myId || table[i][j].owner == -1 || table[i][j].type != ALIVE) {
                continue;
            }
            for (auto [di, dj] : paths) {
                if (insideTable(i + di, j + dj)) {
                    if (table[i + di][j + dj].type == TOWER && table[i + di][j + dj].owner == table[i][j].owner) {
                        opponentTowerNeighbour[i][j] = true;
                    }
                }
            }
        }
    }
}

void retire() {
    cout << myId << " 0\n";
}

vector<pair<int, int>> getPrevsPath(pair<int, int> curCell, const vector<vector<pair<int, int>>>& myCellPrevs) {
    vector<pair<int, int>> path;
    while (curCell != make_pair(-1, -1)) {
        path.emplace_back(curCell);
        curCell = myCellPrevs[curCell.first][curCell.second];
    }
    return path;
}

void printRes(const vector<pair<int, int>>& cmoves) {
    // cerr << "\n\n";
    cout << myId << " " << cmoves.size();
    for (auto [x, y] : cmoves) {
        cout << " " << x + 1 << " " << y + 1;
        table[x][y].owner = myId;
        // if (table[x][y].type == ALIVE) {
        //     table[x][y].type = TOWER;
        // } else {
        //     table[x][y].type = ALIVE;
        // }
    }
    cout << endl;
    fflush(stdout);
}

void run() {
    vector<pair<int, int>> moves;
    for (int iter = 0; iter < 3; iter++) {
        lastnum = 0;
        shuffle(rndnums.begin(), rndnums.end(), rnd);
        vector<vector<int>> availablePlayerIds(n, vector<int>(m, -1));
        runDfs(availablePlayerIds);

        vector<vector<int>> myDists(n, vector<int>(m, 1000000000));
        vector<vector<pair<int, int>>> myCellPrevs(n, vector<pair<int, int>>(m, make_pair(-1, -1)));
        vector<vector<int>> opponentDists(n, vector<int>(m, 1000000000));

        myBfs(availablePlayerIds, myDists, myCellPrevs);
        opponentBfs(availablePlayerIds, opponentDists);

        // cerr << cntsteps << "\n";
        // for (int i = 0; i < n; i++) {
        //     for (int j = 0; j < m; j++) {
        //         cerr << opponentDists[i][j] << " \n"[j == m - 1];
        //     }
        // }

        // cerr << "\n\n";
        // cerr << flush;

        vector<vector<bool>> opponentTowerNeighbour(n, vector<bool>(m, false));

        findOpponentTowers(opponentTowerNeighbour);

        // set<CellMove, CmpCellMove> q;
        vector<CellMove> q;
        vector<vector<CellMove>> cellmoves(n, vector<CellMove>(m));
        // int mycnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (table[i][j].type == TOWER) {
                    continue;
                }
                cellmoves[i][j].parity = (i + j) % 2;
                // if (availablePlayerIds[i][j] == myId) {
                //     mycnt++;
                // }
                if (myDists[i][j] <= 3 && myDists[i][j] > 0) {
                    CellMove& curcm = cellmoves[i][j];
                    curcm.dist = opponentDists[i][j];
                    curcm.i = i;
                    curcm.j = j;
                    curcm.rndval = rndnums[lastnum++];
                    curcm.mydist = myDists[i][j];
                    if (table[i][j].type == ALIVE) {
                        // curcm.hastower = opponentTowerNeighbour[i][j];
                        for (auto [di, dj] : paths) {
                            if (insideTable(i + di, j + dj)) {
                                if (table[i + di][j + dj].owner != myId && table[i + di][j + dj].type == TOWER) {
                                    curcm.hastower = true;
                                }
                                if (table[i + di][j + dj].type == FREE) {
                                    curcm.cntfree++;
                                }
                            }
                        }
                        // for (auto [di, dj] : paths) {
                        //     if (insideTable(i + di, j + dj)) {
                        //         if (table[i + di][j + dj].owner == myId && table[i + di][j + dj].type == TOWER) {
                        //             curcm.eatsmycross = 1;
                        //         }
                        //     }
                        // }
                    }
                    q.emplace_back(curcm);
                }
            }
        }

        if (q.size() == 0) {
            retire();
            return;
        }
        int leftmoves = 3 - (int)moves.size();

        sort(q.begin(), q.end(), CmpCellMove());

        // cerr << "my cnt " << mycnt << "\n";
        // cerr << "cur res " << q.size() << "\n";
        int curf = 0;
        bool done = false;
        while (curf < (int)q.size() && !done && leftmoves > 0) {
            auto cr = q[curf++];
            int x = cr.i;
            int y = cr.j;
            // cerr << myDists[x][y] << "\n";

            if (myDists[x][y] > leftmoves) {
                // cerr << "continuing\n";
                continue;
            }
            done = true;
            vector<pair<int, int>> cpath = getPrevsPath(make_pair(x, y), myCellPrevs);
            cpath.pop_back();
            for (int i = (int)cpath.size() - 1; i >= 0; i--) {
                if (table[cpath[i].first][cpath[i].second].owner == myId) {
                    continue;
                }
                moves.emplace_back(cpath[i]);
                table[cpath[i].first][cpath[i].second].owner = myId;
                if (table[cpath[i].first][cpath[i].second].type == FREE) {
                    table[cpath[i].first][cpath[i].second].type = ALIVE;
                } else {
                    table[cpath[i].first][cpath[i].second].type = TOWER;
                }
                leftmoves--;
            }
        }

    }
    printRes(moves);
}

int main() {
    cin >> n >> m >> k;
    cin >> myId;
    init();
    run();
    while (readState()) {
        run();
    }
    return 0;
}
