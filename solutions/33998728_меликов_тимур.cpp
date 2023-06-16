#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <random>

using namespace std;

void bfs1(pair<int, int> v, vector<vector<int>> &board, vector<int> &used, bool &flag, int count, int n, int m, int g,
          vector<pair<int, int>> &fort) {
    queue<pair<int, int>> q;
    q.push(v);
    while (!q.empty()) {
        auto u = q.front();
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (u.first + i >= 0 and u.first + i < n and u.second + j >= 0 and u.second + j < m) {
                    if (board[u.first + i][u.second + j] == g) {
                        flag = true;
                    } else if (board[u.first + i][u.second + j] == -g) {
                        for (int k = 0; k < fort.size(); k++) {
                            if (fort[k].first == u.first + i and fort[k].second == u.second + j) {
                                if (used[k] != count) {
                                    q.push(make_pair(u.first + i, u.second + j));
                                    used[k] = count;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        q.pop();
    }
}

void
process(int g, vector<vector<int>> &board, vector<pair<int, int>> &mum, vector<pair<int, int>> &fort, int player, int x,
        int y, vector<pair<int, int>>&enemy) {
    if (board[x][y] >= 1) {
        if (board[x][y] == g) {
            for (auto i = mum.begin(); i != mum.end(); i++) {
                if (i->first == x and i->second == y) {
                    mum.erase(i);
                    break;
                }
            }
            board[x][y] = -player;
        } else {
            board[x][y] = -player;
            if (player == g) {
                fort.push_back(make_pair(x, y));
                for (auto i = enemy.begin(); i != enemy.end(); i++) {
                    if (i->first == x and i->second == y) {
                        enemy.erase(i);
                        break;
                    }
                }
            }
        }
    } else {
        board[x][y] = player;
        if (player == g) {
            mum.push_back(make_pair(x, y));
        }else{
            enemy.push_back(make_pair(x, y));
        }
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int g;
    cin >> g;
    vector<pair<int, int>> mum;
    vector<pair<int, int>> fort;
    vector<pair<int, int>> enemy;
    vector<vector<int>> board((n), vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            if (board[i][j] == g) {
                mum.push_back(make_pair(i, j));
            } else if (board[i][j] == -g) {
                fort.push_back(make_pair(i, j));
            }else if (board[i][j] > 0){
                enemy.push_back(make_pair(i, j));
            }
        }
    }
    while (true) {
        //my turn
        vector<pair<int, int>> ans;
        for (int A = 0; A < 3; A++) {
            vector<pair<int, int>> reach;
            vector<pair<int, int>> hit;
            vector<int> used(fort.size(), -1);
            vector<bool> flag_used(fort.size(), false);
            int count = 1;
            for (int i = 0; i < fort.size(); i++) {
                if (used[i] == -1) {
                    bool flag = false;
                    bfs1(fort[i], board, used, flag, count, n, m, g, fort);
                    if (flag) {
                        for (int j = 0; j < fort.size(); j++) {
                            if (used[j] == count) {
                                flag_used[j] = true;
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < fort.size(); i++) {
                if (flag_used[i]) {
                    for (int l = -1; l < 2; l++) {
                        for (int j = -1; j < 2; j++) {
                            if (fort[i].first + l >= 0 and fort[i].first + l < n and fort[i].second + j >= 0 and
                                fort[i].second + j < m) {
                                if (board[fort[i].first + l][fort[i].second + j] >= 0 and
                                    board[fort[i].first + l][fort[i].second + j] != g) {
                                    if (board[fort[i].first + l][fort[i].second + j] != 0) {
                                        hit.push_back(make_pair(fort[i].first + l, fort[i].second + j));
                                    } else {
                                        reach.push_back(make_pair(fort[i].first + l, fort[i].second + j));
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < mum.size(); i++) {
                for (int l = -1; l < 2; l++) {
                    for (int j = -1; j < 2; j++) {
                        if (mum[i].first + l >= 0 and mum[i].first + l < n and mum[i].second + j >= 0 and
                            mum[i].second + j < m) {
                            if (board[mum[i].first + l][mum[i].second + j] != g and
                                board[mum[i].first + l][mum[i].second + j] >= 0) {
                                if (board[mum[i].first + l][mum[i].second + j] != 0) {
                                    hit.push_back(make_pair(mum[i].first + l, mum[i].second + j));
                                } else {
                                    reach.push_back(make_pair(mum[i].first + l, mum[i].second + j));
                                }
                            }
                        }
                    }
                }
            }
            if (reach.size() == 0) {
                break;
            }
            int temp = 0;
            mt19937 rnd(42310);
            if (hit.size() != 0) {
                temp = rnd() % hit.size();
                ans.push_back(hit[temp]);
                process(g, board, mum, fort, g, hit[temp].first, hit[temp].second, enemy);
            } else {
                int minimum = 9999999, index;
                for (int i = 0; i < reach.size(); i++) {
                    int temp_min = 9999999;
                    for (int j = 0; j < enemy.size(); j++){
                        temp_min = min(temp_min, abs(enemy[j].first + enemy[j].first - reach[i].first - reach[i].second));
                    }if (minimum > temp_min){
                        index = i;
                        minimum = temp_min;
                    }
                }
                temp = index;
                ans.push_back(reach[temp]);
                process(g, board, mum, fort, g, reach[temp].first, reach[temp].second, enemy);
            }

        }
        cout << g << ' ' << ans.size() << ' ';
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << ' ';
        }
        cout << endl;
        char command;
        cin >> command;
        if (command == 'o') {
            break;
        } else {
            for (int i = 0; i < k - 1; i++) {
                int player, count;
                cin >> player >> count;
                for (int j = 0; j < count; j++) {
                    int x, y;
                    cin >> x >> y;
                    x--;
                    y--;
                    process(g, board, mum, fort, player, x, y, enemy);
                }
            }
        }
    }
}