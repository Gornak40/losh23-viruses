#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int n, m, k;
int me;
vector<vector<int>> table;

vector<pair<int, int>> get_avail() {
    vector<vector<int>> used(n, vector<int>(m, 0));
    vector<pair<int, int>> res;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (table[i][j] == me) {
                used[i][j] = 1;
                queue<pair<int, int>> q;
                q.push(pair{i, j});
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    for (int dx = -1; dx <= 1; ++dx) {
                        for (int dy = -1; dy <= 1; ++dy) {
                            int nx = x + dx, ny = y + dy;
                            if (0 <= nx && nx < n && 0 <= ny && ny < m) {
                                if (!used[nx][ny] && abs(table[nx][ny]) == me) {
                                    used[nx][ny] = 1;
                                    q.push(pair{nx, ny});
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (table[i][j] < 0 || table[i][j] == me)
                continue;
            bool flag = 0;
            for (int dx = -1; dx <= 1 && !flag; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = i + dx, ny = j + dy;
                    if (0 <= nx && nx < n && 0 <= ny && ny < m && used[nx][ny]) {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag)
                res.push_back(pair{i, j});
        }
    }
    return res;
}

mt19937 gen(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());

vector<vector<int>> dist;

set<pair<int, pair<int, int>>> find_dist(vector<pair<int, int>> pos) {
    set<pair<int, pair<int, int>>> res;
    for (auto [x0, y0] : pos) {
        dist.assign(n, vector<int>(m, INF));
        dist[x0][y0] = 0;
        queue<pair<int, int>> q;
        q.push(pair{x0, y0});
        bool flag = 0;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (table[x][y] > 0 && table[x][y] != me) {
                res.insert(pair{dist[x][y], pair{x0, y0}});
                flag = 1;
                break;
            }
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = x + dx, ny = y + dy;
                    if (0 <= nx && nx < n && 0 <= ny && ny < m) {
                        if (dist[nx][ny] == INF) {
                            dist[nx][ny] = dist[x][y] + 1;
                            q.push(pair{nx, ny});
                        }
                    }
                }
            }
        }
        if (!flag)
            res.insert(pair{INF, pair{x0, y0}});
    }
    return res;
}

void commit(vector<pair<int, int>> turns, int player) {
    for (auto [x, y] : turns) {
        if (table[x][y] == 0)
            table[x][y] = player;
        else
            table[x][y] = -player;
    }
}

vector<pair<int, int>> turn() {
    vector<pair<int, int>> res;
    for (int i = 0; i < 3; ++i) {
        auto avail = get_avail();
        if (avail.empty())
            return res;
        auto proc = find_dist(avail);
        auto cur = proc.begin()->second;
        // for (auto [x, y] : avail) {
        //     if (table[x][y] != 0) {
        //         cur = pair{x, y};
        //     }
        // }
        commit({cur}, me);
        res.push_back(cur);
    }
    return res;
}

signed main() {
    cin >> n >> m >> k;
    cin >> me;
    table.resize(n, vector<int>(m, -1));
    for (auto& r : table) {
        for (auto& el : r) {
            cin >> el;
        }
    }
    do {
        auto res = turn();
        cout << me << ' ' << res.size() << ' ';
        for (auto [x, y] : res)
            cout << x + 1 << ' ' << y + 1 << ' ';
        cout << endl;
        char c;
        cin >> c;
        if (c == 'o')
            return 0;
        for (int i = 0; i < k - 1; ++i) {
            int cnt = 0, id;
            cin >> id >> cnt;
            vector<pair<int, int>> actions(cnt);
            for (auto& [x, y] : actions) {
                cin >> x >> y;
                --x, --y;
            }
            commit(actions, id);
        }
    } while (true);
}
