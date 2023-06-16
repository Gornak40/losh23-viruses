#include <bits/stdc++.h>

using namespace std;
const pair<int, int> vh[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
const int INF = 1e9, mod = 1e9 + 7, MAXN = 300;
int a[MAXN][MAXN];

int n, m, iam;

void change() {
    int g, turns;
    cin >> g >> turns;
    for (int i = 0; i < turns; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        a[x][y] = (a[x][y] == 0 ? g : -g);
    }
}

void make_move() {
    int ihavemoves = 3;
    vector<pair<int, int>> mymoves;
    while (ihavemoves > 0) {
        deque<pair<int, int>> BFS;
        int dist[n][m];
        for (auto & i : dist) for (int & x : i) x = INF;
        vector<pair<int, int>> way[n][m];
        bool icanmove = false;
        for (int i = 0; i < n; i++) { // наши клеточки
            for (int j = 0; j < m; j++) {
                if (a[i][j] == iam) {
                    dist[i][j] = 0;
                    BFS.emplace_back(i, j);
                }
            }
        }
        while (!BFS.empty()) {
            auto [x, y] = BFS.front();
            BFS.pop_front();
            for (auto [x1, y1]: vh) {
                if (x + x1 >= 0 && y + y1 >= 0 && x + x1 < n && y + y1 < m) {
                    if (a[x + x1][y + y1] < 0 && a[x + x1][y + y1] != -iam) {
                        continue;
                    }
                    if (a[x + x1][y + y1] == -iam) {
                        if (dist[x + x1][y + y1] == INF) {
                            dist[x + x1][y + y1] = dist[x][y];
                            way[x + x1][y + y1] = way[x][y];
                            BFS.emplace_front(x + x1, y + y1);
                        }
                    }
                    if (dist[x + x1][y + y1] == INF) {
                        dist[x + x1][y + y1] = dist[x][y] + 1;
                        if (dist[x + x1][y + y1] == 1) icanmove = true;
                        way[x + x1][y + y1] = way[x][y];
                        way[x + x1][y + y1].emplace_back(x + x1, y + y1);
                        BFS.emplace_back(x + x1, y + y1);
                    }
                }
            }
        }
        if (!icanmove) {
            break;
        }

        int todist[n][m];
        for (auto & i : todist) for (auto & x : i) x = INF;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == iam) {
                    todist[i][j] = 0;
                    BFS.emplace_back(i, j);
                }
            }
        }
        if (BFS.empty()) break;
        while (!BFS.empty()) {
            auto [x, y] = BFS.front();
            BFS.pop_front();
            for (auto [x1, y1]: vh) {
                if (x + x1 >= 0 && y + y1 >= 0 && x + x1 < n && y + y1 < m) {
                    if (a[x + x1][y + y1] == -iam) {
                        continue;
                    }
                    if (a[x + x1][y + y1] < 0 && a[x + x1][y + y1] != -iam) {
                        if (todist[x + x1][y + y1] == INF) {
                            todist[x + x1][y + y1] = todist[x][y];
                            way[x + x1][y + y1] = way[x][y];
                            BFS.emplace_front(x + x1, y + y1);
                        }
                    }
                    if (todist[x + x1][y + y1] == INF) {
                        todist[x + x1][y + y1] = todist[x][y] + 1;
                        BFS.emplace_back(x + x1, y + y1);
                    }
                }
            }
        }

        int antidist[n][m];
        for (auto & i : antidist) for (auto & x : i) x = INF;
        for (int i = 0; i < n; i++) { // чужие клеточки
            for (int j = 0; j < m; j++) {
                if (a[i][j] > 0 && a[i][j] != iam) {
                    antidist[i][j] = 0;
                    BFS.emplace_back(i, j);
                }
            }
        }
        if (BFS.empty()) break;
        while (!BFS.empty()) { // считаем расстояние до врагов
            auto [x, y] = BFS.front();
            BFS.pop_front();
            for (auto [dx, dy]: vh) {
                int x1 = x + dx, y1 = y + dy;
                if (x1 >= 0 && y1 >= 0 && x1 < n && y1 < m) {
                    if (a[x1][y1] == -INF) {
                        continue;
                    }
                    if (antidist[x1][y1] == INF && a[x][y] > 0 && a[x1][y1] == -a[x][y]) {
                        antidist[x1][y1] = antidist[x][y];
                        BFS.emplace_front(x1, y1);
                    } else if (antidist[x1][y1] == INF) {
                        antidist[x1][y1] = antidist[x][y] + 1;
                        BFS.emplace_back(x1, y1);
                    }
                }
            }
        }

        bool fight = false;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] > 0 && (dist[i][j] == 1 || dist[i][j] == 2)) {
                    fight = true;
                    break;
                }
            }
            if (fight) break;
        }
        if (!fight) {
            fight = true;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (dist[i][j] == 1 && antidist[i][j] > 2) {
                        fight = false;
                        break;
                    }
                }
                if (!fight) break;
            }
        }
        if (!fight) {
            int bmad = INF, xm = -1, ym = -1;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (dist[i][j] == 1 && antidist[i][j] > 2) {
                        if (antidist[i][j] <= bmad) {
                            bmad = antidist[i][j];
                            xm = i;
                            ym = j;
                        }
                    }
                }
            }
            mymoves.emplace_back(xm, ym);
            if (a[xm][ym] == 0) {
                a[xm][ym] = iam;
            }
            else a[xm][ym] = -iam;
            ihavemoves--;
        } else {
            int md = INF, mv = INF;
            vector<pair<int, int>> moves;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (a[i][j] != iam && a[i][j] > 0) {
                        if (dist[i][j] < md) {
                            md = dist[i][j];
                            if ((int)way[i][j].size() != 0) {
                                mv = (int)way[i][j].size();
                                moves = way[i][j];
                            }
                        } else if (mv != INF && dist[i][j] == md && ((int)way[i][j].size() < mv || todist[i][j] < todist[moves[mv - 1].first][moves[mv - 1].second])) {
                            mv = (int)way[i][j].size();
                            moves = way[i][j];
                        }
                    }
                }
            }
            if (mv == INF) {
                cout << iam << ' ' << 0 << endl;
                return;
            }
            if (mv > ihavemoves && ihavemoves < 3) break;
            for (auto u : moves) {
                if (ihavemoves == 0) break;
                mymoves.emplace_back(u);
                auto [x, y] = u;
                if (a[x][y] == 0) a[x][y] = iam;
                else a[x][y] = -iam;
                ihavemoves--;
            }
        }
    }
    cout << iam << ' ' << mymoves.size() << ' ';
    for (auto [x, y] : mymoves) {
        cout << x + 1 << ' ' << y + 1 << ' ';
    }
    cout << endl;
}

void solve() {
    int k;
    cin >> n >> m >> k >> iam;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] == -100) {
                a[i][j] = -INF;
            }
        }
    }
    while (true) {
        make_move();
        char c;
        cin >> c;
        if (c == 'o') break;
        for (int i = 1; i < k; i++) change();
    }
}

signed main() {
//#ifdef home
//    freopen("test.txt", "r", stdin);
//#endif
    solve();
}