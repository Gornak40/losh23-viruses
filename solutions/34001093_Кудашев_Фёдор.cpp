#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pp;

const int maxn = 311;

int field[maxn][maxn];
int dist[maxn][maxn];
int before_attack[maxn][maxn];
bool is_sn[maxn][maxn];

pp prv[maxn][maxn];
mt19937 rnd(666);

vector<pp> dirs = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

bool is_in_bounds(int x, int y, int n, int m) {
    return !(x < 0 || x >= n || y < 0 || y >= m);
}

int id;

vector<pp> attack(pp center) {
    vector<pp> ans;
    while (dist[center.first][center.second] > 0) {
        if (abs(field[center.first][center.second]) != id)
            ans.push_back(center);
        center = prv[center.first][center.second];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void dist_recount(int n, int m, int id) {
    deque<pp> qq;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (field[i][j] == id) {
                dist[i][j] = 0;
                qq.emplace_back(i, j);
            } else {
                dist[i][j] = -1;
            }
        }
    }
    while (!qq.empty()) {
        pp fr = qq.front();
        qq.pop_front();
        int x = fr.first, y = fr.second;
        for (auto& [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            // check it is in bounds, not used, not banned, not a house (but if it's our house it is ok)
            if (!is_in_bounds(nx, ny, n, m) || dist[nx][ny] != -1 || field[nx][ny] == -100 || (field[nx][ny] < 0 && field[nx][ny] != -id)) {
                continue;
            }
            if (abs(field[nx][ny]) == id && abs(field[x][y]) == id) {
                dist[nx][ny] = dist[x][y];
                prv[nx][ny] = {x, y};
                qq.emplace_front(nx, ny);
            } else {
                dist[nx][ny] = dist[x][y] + 1;
                qq.emplace_back(nx, ny);
                prv[nx][ny] = {x, y};
            }
        }
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k >> id;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> field[i][j];
        }
    }
    while (true) {
        vector<pp> ans;
        vector<pp> topdanger, weakdanger, build;
        dist_recount(n, m, id);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {  // not -1
                is_sn[i][j] = false;
                if (dist[i][j] == 2 && field[i][j] > 0) {
                    weakdanger.emplace_back(i, j);
                }
                if (dist[i][j] == 1 && field[i][j] > 0) {
                    if (field[prv[i][j].first][prv[i][j].second] > 0) {
                        topdanger.emplace_back(i, j);
                    } else {
                        weakdanger.emplace_back(i, j);
                    }
                }

                if (dist[i][j] > 0 && field[i][j] > 0) {
                    if (field[i][j] != id) {
                        bool danger = false;
                        for (auto& [dx, dy] : dirs) {
                            int nx = i + dx, ny = j + dy;
                            if (!is_in_bounds(nx, ny, n, m)) {
                                continue;
                            }
                            if (field[nx][ny] == -field[i][j] && before_attack[nx][ny] == id) {
                                danger = true;
                            }
                        }
                        if (danger) {
                            is_sn[i][j] = true;

                            if (dist[i][j] <= 3) {
                                topdanger.emplace_back(i, j);
                            } else if (dist[i][j] <= 9) {
                                vector<pp> lst;
                                pp start = {i, j};
                                while (dist[start.first][start.second] > 0) {
                                    lst.push_back(start);
                                    start = prv[start.first][start.second];
                                }
                                reverse(lst.begin(), lst.end());

                                topdanger.push_back(lst[2]);
                            }
                        }
                    }
                }
                if (dist[i][j] == 1 && field[i][j] == 0) {
                    bool safe = true;
                    for (auto& [dx, dy] : dirs) {
                        int nx = i + dx, ny = j + dy;
                        if (!is_in_bounds(nx, ny, n, m)) {
                            continue;
                        }
                        if (field[nx][ny] != 0 && field[nx][ny] != -100 && abs(field[nx][ny]) != id) {
                            safe = false;
                            break;
                        }
                    }
                    if (safe) {
                        build.emplace_back(i, j);
                    }
                }
            }
        }
        shuffle(build.begin(), build.end(), rnd);
        sort(topdanger.begin(), topdanger.end(), [&](pp a, pp b) {
            return pp{is_sn[a.first][a.second], -dist[a.first][a.second]} < pp{is_sn[b.first][b.second], -dist[b.first][b.second]};
        });
        sort(weakdanger.begin(), weakdanger.end(), [&](pp a, pp b) { return dist[a.first][a.second] > dist[b.first][b.second]; });

        int it = 0;

        while (it < 3) {
            while (!topdanger.empty() && dist[topdanger.back().first][topdanger.back().second] == 0) {
                topdanger.pop_back();
            }
            while (!weakdanger.empty() && dist[weakdanger.back().first][weakdanger.back().second] == 0) {
                weakdanger.pop_back();
            }
            while (!build.empty() && dist[build.back().first][build.back().second] == 0) {
                build.pop_back();
            }

            if (!topdanger.empty() && dist[topdanger.back().first][topdanger.back().second] + it <= 3) {
                it += dist[topdanger.back().first][topdanger.back().second];
                vector<pp> tmp = attack(topdanger.back());
                for (pp el : tmp) {
                    ans.push_back(el);
                    if (field[el.first][el.second] == 0)
                        field[el.first][el.second] = id;
                    else {
                        field[el.first][el.second] = -id;
                    }
                }

                topdanger.pop_back();

            } else if (!weakdanger.empty() && dist[weakdanger.back().first][weakdanger.back().second] + it <= 3) {
                it += dist[weakdanger.back().first][weakdanger.back().second];
                vector<pp> tmp = attack(weakdanger.back());
                for (pp el : tmp) {
                    ans.push_back(el);
                    if (field[el.first][el.second] == 0)
                        field[el.first][el.second] = id;
                    else {
                        field[el.first][el.second] = -id;
                    }
                }
                weakdanger.pop_back();
            } else if (!build.empty() && it < 3) {
                ans.push_back(build.back());
                pp el = ans.back();
                if (field[el.first][el.second] == 0)
                    field[el.first][el.second] = id;
                else {
                    field[el.first][el.second] = -id;
                }
                it++;
                build.pop_back();
            } else {
                break;
            }
            dist_recount(n, m, id);
        }
        if (ans.size() == 0) {
            pp ch = {-1, -1};
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (field[i][j] >= 0 && dist[i][j] == 1) {
                        ch = {i, j};
                    }
                }
            }
            if (ch.first > -1) {
                if (field[ch.first][ch.second] == 0) {
                    field[ch.first][ch.second] = id;
                } else {
                    field[ch.first][ch.second] = -id;
                }
                ans.push_back(ch);
            }
        }
        cout << id << ' ' << ans.size() << ' ';
        for (pp el : ans) {
            cout << el.first + 1 << ' ' << el.second + 1 << ' ';
        }
        cout << endl;
        cout.flush();

        string s;
        cin >> s;
        if (s == "o") {
            return 0;
        }
        for (int i = 0; i < k - 1; i++) {
            int idn, cnt;
            cin >> idn >> cnt;
            while (cnt--) {
                int a, b;
                cin >> a >> b;
                a--;
                b--;
                if (field[a][b] == 0) {
                    field[a][b] = idn;
                } else {
                    before_attack[a][b] = field[a][b];
                    field[a][b] = -idn;
                }
            }
        }
    }
}