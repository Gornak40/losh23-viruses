#include <bits/stdc++.h>

using i64 = long long;

std::mt19937 rnd(228);

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    int id;
    std::cin >> id;
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    std::function<bool(int, int)> valid = [&](int x, int y) {
        return x > -1 && x < n && y > -1 && y < m;
    };
    std::function<void(int, int, int)> modify = [&](int i, int x, int y) {
        if (!a[x][y]) {
            a[x][y] = i;
        } else {
            a[x][y] = -i;
        }
    };
    std::function<std::vector<std::pair<int, int>>(int)> getPossibleMoves = [&](int color) {
        std::vector<std::pair<int, int>> t;
        std::vector<std::vector<bool>> used(n, std::vector<bool>(m, false));
        std::function<void(int, int)> dfs = [&](int x, int y) {
            used[x][y] = true;
            t.emplace_back(x, y);
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (!dx && !dy) continue;
                    int nx = dx + x, ny = dy + y;
                    if (valid(nx, ny) && !used[nx][ny] && abs(a[nx][ny]) == color) dfs(nx, ny);
                }
            }
        };
        std::vector<std::pair<int, int>> res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (abs(a[i][j]) == color && !used[i][j]) {
                    t.clear();
                    dfs(i, j);
                    bool ok = false;
                    for (auto [x, y] : t) {
                        if (a[x][y] == color) {
                            ok = true;
                            break;
                        }
                    }
                    if (!ok) continue;
                    for (auto [x, y] : t) {
                        for (int dx = -1; dx <= 1; dx++) {
                            for (int dy = -1; dy <= 1; dy++) {
                                if (!dx && !dy) continue;
                                int nx = dx + x, ny = dy + y;
                                if (valid(nx, ny) && (!a[nx][ny] || (a[nx][ny] > 0 && a[nx][ny] != color))) {
                                    res.emplace_back(nx, ny);
                                }
                            }
                        }
                    }
                }
            }
        }
        return res;
    };
    std::function<void(int)> move = [&](int color) {
        std::vector<std::pair<int, int>> res;
        while ((int) res.size() < 3) {
            std::vector<std::pair<int, int>> moves = getPossibleMoves(color);
            if (moves.empty()) {
                break;
            } else {
                int i = -1;
                for (int j = 0; j < moves.size(); j++) {
                    if (a[moves[j].first][moves[j].second]) {
                        i = j;
                    }
                }
                if (i == -1) {
                    for (int j = 0; j < moves.size(); j++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            for (int dy = -1; dy <= 1; dy++) {
                                if (!dx && !dy) continue;
                                int nx = dx + moves[j].first, ny = dy + moves[j].second;
                                if (valid(nx, ny) && a[nx][ny] != color && a[nx][ny] > 0 && (int) res.size() <= 1) {
                                    i = j;
                                }
                            }
                        }
                    }
                }
                if (i == -1) {
                    i = rnd() % moves.size();
                }
                res.emplace_back(moves[i]);
                modify(color, moves[i].first, moves[i].second);
            }
        }
        std::cout << color << " " << (int) res.size() << " ";
        for (auto [x, y] : res) {
            std::cout << x + 1 << " " << y + 1 << " ";
        }
        std::cout << std::endl;
    };
    while (true) {
        move(id);
        char status;
        std::cin >> status;
        if (status == 'o') break;
        for (int _ = 1; _ < k; _++) {
            int i, cnt;
            std::cin >> i >> cnt;
            for (int __ = 0; __ < cnt; __++) {
                int x, y;
                std::cin >> x >> y;
                --x, --y;
                modify(i, x, y);
            }
        }
    }
}

signed main() {
   // std::ios::sync_with_stdio(false);
   // std::cin.tie(nullptr);

    int t = 1;
    // std::cin >> t;

    while (t--) {
        solve();
    }
}
