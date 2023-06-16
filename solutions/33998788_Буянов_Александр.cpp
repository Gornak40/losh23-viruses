#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#define ld long double
using namespace std;

vector<int> dx = {-1, 0, 1}, dy = {-1, 0, 1};

vector<pair<int, int>> calc(int n, int m, vector<vector<int>> &field, int myteam) {
    vector<vector<bool>> connect(n, vector<bool>(m));
    deque<pair<int, int>> d;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (field[i][j] == myteam) {
                connect[i][j] = true;
                d.push_back({i, j});
            }
        }
    }
    while (!d.empty()) {
        auto [i, j] = d.front();
        connect[i][j] = true;
        for (auto x : dx) {
            for (auto y : dy) {
                int xx = i + x, yy = j + y;
                if ((xx != i || yy != j) && 0 <= xx && xx < n && 0 <= yy && yy < m && (field[xx][yy] >= 0 || field[xx][yy] == -myteam) && !connect[xx][yy]) {
                    connect[xx][yy] = true;
                    if (field[xx][yy] == myteam || field[xx][yy] == -myteam) {
                        d.push_back({xx, yy});
                    }
                }
            }
        }
        d.pop_front();
    }
    vector<pair<int, int>> pos;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (connect[i][j] && field[i][j] >= 0 && field[i][j] != myteam) {
                pos.push_back({i, j});
            }
        }
    }
    return pos;
}

void move(vector<vector<int>> &field, int i, int j, int team) {
    //cout << "move: " << " " << i + 1 << " " << j + 1 << " " << team << endl;
    if (field[i][j] == 0) {
        field[i][j] = team;
    } else {
        field[i][j] = -team;
    }
}

void print(vector<vector<int>> &field, int n, int m) {
    cout << endl << "now" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (field[i][j] >= 0) {
                cout << ' ';
            }
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n, m, k, g;
    char c;
    cin >> n >> m >> k >> g;
    vector<vector<int>> field(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> field[i][j];
        }
    }
    bool start = true;
    while (true) {
        vector<pair<int, int>> pos = calc(n, m, field, g);
        vector<pair<int, int>> out;
        for (int i = 0; i < 3; ++i) {
            if (start && i == 2) {
                start = false;
                break;
            }
            if ((int)pos.size() == 0) {
                break;
            }
            int qw = (int)pos.size();
            int found = -1;
            for (int i = 0; i < qw; ++i) {
                if (field[pos[i].first][pos[i].second] != 0) {
                    found = i;
                }
            }
            if (found == -1) {
                out.push_back(pos[rand() % ((int) pos.size())]);
            } else {
                out.push_back(pos[found]);
            }
            move(field, out.back().first, out.back().second, g);
            pos = calc(n, m, field, g);
        }
        cout << g << " " << (int)out.size() << " ";
        for (int i = 0; i < (int)out.size(); ++i) {
            cout << out[i].first + 1 << " " << out[i].second + 1 << " ";
        }
        cout << endl;
        //print(field, n, m);
        int a, team, x, y;
        cin >> c;
        if (c == 'o') {
            break;
        }
        for (int i = 0; i < k - 1; ++i) {
            cin >> team >> a;
            for (int j = 0; j < a; ++j) {
                cin >> x >> y;
                x--;
                y--;
                move(field, x, y, team);
                //print(field, n, m);
            }
        }
    }
    return 0;
}