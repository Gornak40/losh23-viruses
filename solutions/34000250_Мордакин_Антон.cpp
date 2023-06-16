//#pragma GCC optimize("O3,unroll-loops,Ofast")
//#pragma GCC target("avx2,bmi,bmi2")
#include <bits/stdc++.h>

using namespace std;
#define pb push_back

const int INF = 1e9 + 7;
vector<vector<int>> game;
vector<vector<pair<int, int>>> recover, recover1;
int n, m, K, G;

vector<pair<int, int>> neighbour = {{-1, -1},
                                    {-1, 0},
                                    {0,  -1},
                                    {1,  -1},
                                    {-1, 1},
                                    {1,  0},
                                    {0,  1},
                                    {1,  1}};

bool canGo(int x, int y) {
    return (1 <= x && x <= n) && (1 <= y && y <= m) && (game[x][y] >= 0 || game[x][y] == -K);
}

vector<vector<int>> get_dist() {
    deque<tuple<int, int, int>> pend;
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, INF));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (game[i][j] == K) {
                pend.push_back({0, i, j});
                dist[i][j] = 0;
            }
        }
    }

    while (!pend.empty()) {
        auto cur = *pend.begin();
        pend.pop_front();
        auto [d, x, y] = cur;
        for (auto [chx, chy]: neighbour) {
            if (canGo(x + chx, y + chy) && dist[x + chx][y + chy] == INF) {
                if (abs(game[x + chx][y + chy]) == K) {
                    dist[x + chx][y + chy] = dist[x][y];
                    recover[x + chx][y + chy] = {x, y};
                    pend.push_front({dist[x + chx][y + chy], x + chx, y + chy});
                } else {
                    dist[x + chx][y + chy] = dist[x][y] + 1;
                    recover[x + chx][y + chy] = {x, y};
                    pend.push_back({dist[x + chx][y + chy], x + chx, y + chy});
                }
            }
        }
    }

    return dist;
}

vector<vector<int>> getDistfromOur() {
    deque<tuple<int, int, int>> pend;
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, INF));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (game[i][j] == K) {
                pend.push_back({0, i, j});
                dist[i][j] = 0;
            }
        }
    }

    while (!pend.empty()) {
        auto cur = *pend.begin();
        pend.pop_front();
        auto [d, x, y] = cur;
        for (int i = 0; i < n; ++i) {
            for (auto [chx, chy]: neighbour) {
                if (canGo(x + chx, y + chy) && dist[x + chx][y + chy] == INF) {
                    recover1[x + chx][y + chy] = {x, y};
                    dist[x + chx][y + chy] = dist[x][y] + 1;
                    pend.push_back({dist[x + chx][y + chy], x + chx, y + chy});
                }
            }
        }
    }

    return dist;
}


vector<pair<int, int>> make_move(int k) {
    if (k <= 0) return {};

//    cout << endl;
//    for (auto it: game) {
//        for (auto i: it) {
//            cout << i << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;

    auto distFromAll = get_dist();// dist = getDistfromOur();
    int minToEnemyFromAll = INF, minToEnemy = INF;
    pair<int, int> enemy1, enemy2;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (game[i][j] > 0 && game[i][j] != K) {
                if (minToEnemyFromAll > distFromAll[i][j]) {
                    minToEnemyFromAll = distFromAll[i][j];
                    enemy1 = {i, j};
                }

                /*if (minToEnemy > dist[i][j]) {
                    minToEnemy = dist[i][j];
                    enemy2 = {i, j};
                }*/
            }
        }
    }

    /*if (minToEnemy <= k) {
        // восстановление ответа до enemy2
        vector<pair<int, int>> ans;
        while (dist[enemy2.first][enemy2.second] != 0) {
            if (game[enemy2.first][enemy2.second] >= 0) ans.pb(enemy2);
            if (game[enemy2.first][enemy2.second] != 0) game[enemy2.first][enemy2.second] = -K;
            else game[enemy2.first][enemy2.second] = K;
            enemy2 = recover1[enemy2.first][enemy2.second];
        }
        reverse(ans.begin(), ans.end());
        auto it = make_move(k - ans.size());
        for (auto i: it) ans.pb(i);
        return ans;
    } else*/
    if (minToEnemyFromAll <= k) {
        // восстановление ответа до enemy1
        vector<pair<int, int>> ans;
        while (distFromAll[enemy1.first][enemy1.second] != 0) {
            if (game[enemy1.first][enemy1.second] >= 0) ans.pb(enemy1);
            if (game[enemy1.first][enemy1.second] != 0) game[enemy1.first][enemy1.second] = -K;
            else game[enemy1.first][enemy1.second] = K;
            enemy1 = recover[enemy1.first][enemy1.second];
        }
        reverse(ans.begin(), ans.end());
        auto it = make_move(k - ans.size());
        for (auto i: it) ans.pb(i);
        return ans;
    } else {
        // идём до ближайшей клетки сопреника
        //cout << "Start" << endl;
        vector<pair<int, int>> ans;
        if (minToEnemyFromAll >= INF) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (game[i][j] == 0 && distFromAll[i][j] == 1) {
                        game[i][j] = K;
                        return { { i, j } };
                    }
                }
            }
            return {};
        }

        while (distFromAll[enemy1.first][enemy1.second] != 0) {
            if (game[enemy1.first][enemy1.second] >= 0) ans.pb(enemy1);
            enemy1 = recover[enemy1.first][enemy1.second];
        }
        reverse(ans.begin(), ans.end());

        vector<pair<int, int>> ret;
        for (int i = 0; i < k; ++i) {
            ret.pb(ans[i]);
        }

        for (auto [i, j] : ret) {
            if (game[i][j] != 0) game[i][j] = -K;
            else game[i][j] = K;
        }
        //cout << "Finish" << endl;
        return ret;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> G >> K;
    game.assign(n + 2, vector<int>(m + 2));
    recover.assign(n + 2, vector<pair<int, int>>(m + 2));
    recover1.assign(n + 2, vector<pair<int, int>>(m + 2));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> game[i][j];
        }
    }
    vector<pair<int, int>> ans;
    ans = make_move(3);
    if (ans.size() > 3) return -1;
    cout << K << " " << ans.size() << " ";
    for (auto [x, y]: ans) {
        cout << x << " " << y << " ";
    }
    cout << endl;
    char tmp;
    cin >> tmp;
    while (tmp != 'o') {
        for (int i = 0; i < G - 1; ++i) {
            int A, number;
            cin >> number >> A;
            for (int j = 0; j < A; ++j) {
                int x, y;
                cin >> x >> y;
                if (game[x][y] != 0) game[x][y] = -number;
                else game[x][y] = number;
            }
        }
        ans = make_move(3);
        cout << K << " " << ans.size() << " ";
        for (auto [x, y]: ans) {
            cout << x << " " << y << " ";
        }
        cout << endl;
        cin >> tmp;
    }
}