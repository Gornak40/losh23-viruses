#include <bits/stdc++.h>

#ifndef ASTRON
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4.2,avx,avx2,fma,popcnt,abm,mmx,tune=native")
//#pragma GCC optimize("O3,unroll-loops")
#endif

using namespace std;

#define int long long
#define ld long double

template<typename T>
istream& operator>>(istream& in, vector<T>& v) {
    for (T& i : v) in >> i;
    return in;
}

int n, m, k, g;
bool isRunning = true;

int grid[301][301];

int dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
int dy[] = {1, 1, 1, 0, -1, -1, -1, 0};

ld w1 = 1, w2 = 1, w3 = 1, w4 = 16, w5 = 5;
// -2.1382546275660523 -2.928121392074252 9.752630766684195 6.765885115843449 0.2096714098335024

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

pair<int, int> madeMove() {
    vector<pair<int, int>> available;
    auto checkOk = [&](int x, int y) {
        if (x <= 0 || x > n ||
        y <= 0 || y > m || grid[x][y] == -100) return false;

        return true;
    };

    set<pair<int, int>> near;

    queue<pair<int, int>> q;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == g) {
                near.insert({i, j});
                q.emplace(i, j);
            }
        }
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int shift = 0; shift < 8; shift++) {
            int nx = x + dx[shift];
            int ny = y + dy[shift];
            if (near.count({nx, ny})) continue;

            if (checkOk(nx, ny) && grid[nx][ny] == -g) {
                near.insert({nx, ny});
                q.emplace(nx, ny);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        if (grid[i][j] == g || grid[i][j] < 0) continue;
        int cnt = 0;
        for (int shift = 0; shift < 8; shift++) {
            int nx = i + dx[shift];
            int ny = j + dy[shift];
            if (checkOk(nx, ny) && near.count({nx, ny}))
                cnt++;
        }
        if (cnt) available.emplace_back(i, j);
    }
    }

    if (available.empty()) {
        return {-1, -1};
    }

    vector<ld> reward;
    for (auto [x, y] : available) {
        int cnt = 0;
        for (int shift = 0; shift < 8; shift++) {
            int nx = x + dx[shift];
            int ny = y + dy[shift];
            if (checkOk(nx, ny) && grid[nx][ny] == g)
                cnt++;
        }

        int mind = 1e9;
        int mindc = 1e9;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (grid[i][j] > 0 && grid[i][j] != g) {
                    mind = max(abs(i - x), abs(j - y));
                } else if (grid[i][j] == -g) {
                    mindc = max(abs(i - x), abs(j - y));
                }
            }
        }

        ld cur = 0;

        if (grid[x][y] > 0) cur += 5. * w1;

        if (cnt <= 4) cur += (ld) cnt * w2;
        else cur += (ld) (8 - cnt) * w3;


        if (mind != 1e9) {
            cur += 1. / (ld) mind * w4;
        }

        if (mindc != 1e9) {
            cur += 1. / (ld) mindc * w5;
        }

        reward.push_back(cur);
    }

    int pos = max_element(reward.begin(), reward.end()) - reward.begin();

    return available[pos];
}

void updateState() {
    string state;
    cin >> state;
    if (state == "o") {
        isRunning = false;
        return;
    }

    for (int i = 0; i < k - 1; i++) {
        int pn;
        cin >> pn;
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; j++) {
            int x, y;
            cin >> x >> y;
            if (grid[x][y] == 0) {
                grid[x][y] = pn;
            } else {
                grid[x][y] = -pn;
            }
        }
    }
}

void solve() {
    cin >> n >> m >> k >> g;
//    ifstream str("w" + to_string(g) + ".txt");
//    str >> w1 >> w2 >> w3 >> w4 >> w5;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
        }
    }

    while (isRunning) {
        vector<pair<int, int>> moves;
        for (int i = 0; i < 3; i++) {
            auto [u, v] = madeMove();
            if (u == -1) {
                break;
            } else {
                moves.emplace_back(u, v);
                if (grid[u][v] > 0)
                    grid[u][v] = -g;
                else
                    grid[u][v] = g;
            }
        }
        if (moves.empty()) {
            cout << g << ' ' << 0 << endl;
        } else {
            cout << g << ' ';
            cout << moves.size() << ' ';
            for (auto [a, b] : moves) {
                cout << a << ' ' << b << ' ';
            }

            cout << endl;

//            for (int i = 1; i <= n; i++) {
//                for (int j = 1; j <= m; j++) {
//                    cout << grid[i][j] << ' ';
//                }
//                cout << endl;
//            }
        }
        updateState();
    }
}

signed main() {
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);

    int t = 1;
//  cin >> t;
    while (t--) solve(), cout << '\n';
}
