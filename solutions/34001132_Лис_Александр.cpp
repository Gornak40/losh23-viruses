#include <bits/stdc++.h>

using namespace std;

const int di[8] = {0, -1, -1, -1, 0, 1, 1, 1};
const int dj[8] = {1, 1, 0, -1, -1, -1, 0, 1};

signed main() {
    int n, m, k, g;
    cin >> n >> m >> k >> g;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    auto valid = [&](int i, int j) {
        return i >= 0 && j >= 0 && i < n && j < m;
    };
    auto check_fortress = [&](int i, int j) {
        return valid(i, j) && a[i][j] == -g;
    };
    auto fortress_prior = [&](int i, int j) {
        int tot = 0;
        tot += (int)(check_fortress(i - 1, j) && check_fortress(i, j + 1));
        tot += (int)(check_fortress(i - 1, j) && check_fortress(i, j - 1));
        tot += (int)(check_fortress(i + 1, j) && check_fortress(i, j - 1));
        tot += (int)(check_fortress(i + 1, j) && check_fortress(i, j + 1));
        return tot;
    };
    auto check_cross = [&](int i, int j) {
        return valid(i, j) && a[i][j] == g;
    };
    auto cross_prior = [&](int i, int j) {
        int tot = 0;
        tot += (int)(check_cross(i - 1, j)) ^ 1;
        tot += (int)(check_cross(i + 1, j)) ^ 1;
        tot += (int)(check_cross(i, j - 1)) ^ 1;
        tot += (int)(check_cross(i, j + 1)) ^ 1;
        return tot;
    };
    while (true) {
        vector<pair<int, int>> ans;
        auto conquer = [&](int b) -> bool {
            vector<vector<int>> used(n, vector<int>(m));
            queue<pair<int, int>> q;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (a[i][j] == g) {
                        q.emplace(i, j);
                        used[i][j] = 1;
                    }
                }
            }
            while (!q.empty()) {
                auto [i, j] = q.front();
                q.pop();
                for (int l = 0; l < 8; l++) {
                    int ni = i + di[l];
                    int nj = j + dj[l];
                    if (ni >= 0 && nj >= 0 && ni < n && nj < m) {
                        if (used[ni][nj] == 0 && a[ni][nj] == -g) {
                            q.emplace(ni, nj);
                            used[ni][nj] = 1;
                        }
                    }
                }
            }
            pair<int, int> opt = {-1, -1};
            int prior = -1;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (a[i][j] == g || used[i][j]) {
                        q.emplace(i, j);
                        for (int l = 0; l < 8; l++) {
                            int ni = i + di[l];
                            int nj = j + dj[l];
                            if (ni >= 0 && nj >= 0 && ni < n && nj < m) {
                                if (a[ni][nj] >= 0 && a[ni][nj] != g) {
                                    if (a[ni][nj] == 0 && b == 0) {
                                        int nv = cross_prior(ni, nj);
                                        if (nv > prior) {
                                            opt = make_pair(ni, nj);
                                            prior = nv;
                                        }
                                    } else if (a[ni][nj] > 0 && b == 1) {
                                        int nv = fortress_prior(ni, nj);
                                        if (nv > prior) {
                                            opt = make_pair(ni, nj);
                                            prior = nv;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (prior == -1) return false;
            if (b == 1) {
                a[opt.first][opt.second] = -g;
            } else {
                a[opt.first][opt.second] = g;
            }
            ans.push_back(opt);
            return true;
        };
        if (!conquer(0)) {
            conquer(1);
        }
        if (!conquer(1)) {
            conquer(0);
        }
        if (!conquer(1)) {
            conquer(0);
        }
        while (ans.size() < 3) {
            if (!conquer(0)) {
                if (!conquer(1)) {
                    break;
                }
            }
        }
        cout << g << ' ' << ans.size() << ' ';
        for (auto [i, j] : ans) {
            cout << i + 1 << ' ' << j + 1 << ' ';
        }
        cout << endl;
        char gs;
        cin >> gs;
        if (gs == 'o') {
            return 0;
        }
        for (int h = 0; h < k - 1; h++) {
            int gg, A;
            cin >> gg >> A;
            for (int tt = 0; tt < A; tt++) {
                int i, j;
                cin >> i >> j, i--, j--;
                if (a[i][j] == 0) {
                    a[i][j] = gg;
                } else {
                    a[i][j] = -gg;
                }
            }
        }
    }
}