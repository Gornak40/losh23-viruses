/*
made by max0000561 and grishaRed
*/
#include<bits/stdc++.h>
#define sz(a) (int)a.size()

using namespace std;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

const int INF = 1e9;
int S;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    S = n * m;
    S *= 10;
    vector<vector<int>> a(n + 2, vector<int> (m + 2));
    vector<vector<int>> pr(n + 2, vector<int> (m + 2));
    vector<vector<bool>> alive(n + 2, vector<bool> (m + 2));
    int me;
    cin >> me;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }
    for (int j = 0; j < m + 2; ++j) {
        a[0][j] = a[n + 1][j] = -100;
    }
    for (int i = 0; i < n + 2; ++i) {
        a[i][0] = a[i][m + 1] = -100;
    }
    int stI = 0, stJ = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j] == me) {
                stI = i;
                stJ = j;
            }
        }
    }
    while (true) {
        vector<pair<int, int>> moves;
        while (sz(moves) < 3) {
            vector<deque<pair<int, int>>> q(k + 1);
            for (int i = 0; i <= n + 1; ++i) {
                for (int j = 0; j <= m + 1; ++j) {
                    pr[i][j] = 0;
                    alive[i][j] = 0;
                    if (a[i][j] < 0) {
                        pr[i][j] = -INF;
                    }
                    if (abs(a[i][j]) == me) {
                        pr[i][j] = -INF;
                    }
                    if (a[i][j] > 0) {
                        alive[i][j] = 1;
                        q[a[i][j]].push_back({i, j});
                    }
                }
            }
            for (int g = 1; g <= k; ++g) {
                while (!q[g].empty()) {
                    pair<int, int> cur = q[g].front();
                    q[g].pop_front();
                    int i = cur.first;
                    int j = cur.second;
                    for (int di = -1; di <= 1; ++di) {
                        for (int dj = -1; dj <= 1; ++dj) {
                            if (abs(a[i + di][j + dj]) == g && !alive[i + di][j + dj]) {
                                alive[i + di][j + dj] = 1;
                                q[g].push_back({i + di, j + dj});
                            }
                        }
                    }
                }
            }
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (alive[i][j] && abs(a[i][j]) != me) {
                        if (a[i][j] > 0) {
                            pr[i][j] += 4 * S;
                        }
                    }
                    else if (!alive[i][j] && a[i][j] < 0 && abs(a[i][j]) == me) {
                        pr[i][j] += 3 * S;
                    }
                    if (a[i][j] > 0 && a[i][j] != me) {
                        for (int di = -1; di <= 1; ++di) {
                            for (int dj = -1; dj <= 1; ++dj) {
                                if (a[i + di][j + dj] < 0 && abs(a[i + di][j + dj]) == a[i][j]) {
                                    pr[i][j] += 2 * S;
                                }
                            }
                        }
                    }
                }
            }
            deque<pair<int, int>> Q;
            vector<vector<int>> dist(n + 2, vector<int> (m + 2, INF));
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (alive[i][j] && abs(a[i][j]) == me) {
                        Q.push_back({i, j});
                        dist[i][j] = 0;
                    }
                    pr[i][j] += rnd() % 30;
                }
            }
            vector<vector<pair<int, int>>> P(n + 2, vector<pair<int, int>> (m + 2, {-1, -1}));
            while (!Q.empty()) {
                pair<int, int> cur = Q.front();
                Q.pop_front();
                int i = cur.first;
                int j = cur.second;
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (dist[i + di][j + dj] == INF && a[i + di][j + dj] >= 0) {
                            dist[i + di][j + dj] = dist[i][j] + 1;
                            P[i + di][j + dj] = {i, j};
                            Q.push_back({i + di, j + dj});
                        }
                    }
                }
            }
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (dist[i][j] != INF) {
                        pr[i][j] -= abs(i - stI) + abs(j - stJ);
                    }
                }
            }
            int prior = -INF, I = 0, J = 0;
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (dist[i][j] <= 3 - sz(moves) && dist[i][j] != 0 && a[i][j] >= 0 && a[i][j] != me) {
                        if (pr[i][j] > prior && a[i][j] >= 0) {
                            prior = pr[i][j];
                            I = i;
                            J = j;
                        }
                    }
                }
            }
            vector<pair<int, int>> add;
            while (I != -1) {
                if (a[I][J] > 0 && a[I][J] != me) {
                    a[I][J] = -me;
                }
                else if (a[I][J] == 0) {
                    a[I][J] = me;
                }
                add.push_back({I, J});
                int ii = I, jj = J;
                I = P[ii][jj].first;
                J = P[ii][jj].second;
            }
            add.pop_back();
            reverse(add.begin(), add.end());
            for (auto tmp : add) {
                moves.push_back(tmp);
            }
            if (sz(add) == 0) {
                break;
            }
        }
        cout << me << ' ' << sz(moves) << ' ';
        for (auto i : moves) {
            cout << i.first << ' ' << i.second << ' ';
        }
        cout << endl;
        char status;
        cin >> status;
        if (status == 'o') {
            return 0;
        }
        for (int ii = 0; ii < k - 1; ++ii) {
            int who, c;
            cin >> who >> c;
            for (int jj = 0; jj < c; ++jj) {
                int i, j;
                cin >> i >> j;
                if (a[i][j] == 0) {
                    a[i][j] = who;
                }
                else {
                    a[i][j] = -who;
                }
            }
        }
    }
}
