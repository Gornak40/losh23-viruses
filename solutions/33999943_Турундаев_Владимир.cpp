#include <bits/stdc++.h>

using namespace std;

int n, m, k, my;
vector<vector<bool>> used; // где мы ходили
vector<vector<bool>> reach; // куда можем приземлиться
vector<vector<int>> vec; // поле

vector<int> dx = {-1, -1, -1, 1, 1, 1, 0, 0};
vector<int> dy = {-1, 0, 1, -1, 0, 1, 1, -1};

bool normal(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

void dfs(int x, int y) {
    if (!normal(x, y) || used[x][y])
        return;
    used[x][y] = true;
    for (int i = 0; i < 8; i++) {
        int xx = x + dx[i], yy = y + dy[i];
        if (normal(xx, yy) && abs(vec[xx][yy]) == my) {
            dfs(xx, yy);
        }
    }
}

pair<int, int> my_one_move() {
    used.assign(n, vector<bool> (m, false));
    reach.assign(n, vector<bool> (m, false));
    vector<pair<int, int>> ans;
    for (int x = 0; x < n; x++)
        for (int y = 0; y < m; y++)
            if (vec[x][y] == my)
                dfs(x, y);
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (used[x][y]) {
                for (int i = 0; i < 8; i++) {
                    int xx = x + dx[i], yy = y + dy[i];
                    if (normal(xx, yy))
                        reach[xx][yy] = true;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (reach[i][j] && vec[i][j] > 0 && vec[i][j] != my) {
                return {i, j};
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (reach[i][j] && vec[i][j] == 0) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

void my_move(int q) {
    cout << my << ' ';
    vector<pair<int, int>> ans;
    auto act = my_one_move();
    while (ans.size() < q && act != make_pair(-1, -1)) {
        ans.push_back(act);
        if (vec[act.first][act.second] == 0)
            vec[act.first][act.second] = my;
        else
            vec[act.first][act.second] = -my;
        act = my_one_move();
    }
    cout << ans.size() << ' ';
    for (auto [x, y] : ans) {
        cout << x + 1 << ' ' << y + 1 << ' ';
    }
    cout << endl;
}

void other_move() {
    int move;
    cin >> move;
    int a;
    cin >> a;
    while (a--) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (vec[x][y] == 0)
            vec[x][y] = move;
        else
            vec[x][y] = -move;
    }
}

void coutfield() {
    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << vec[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
}

signed main() {
    cin >> n >> m >> k >> my;
    vec.resize(n, vector<int> (m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> vec[i][j];
    my_move(2);
    char c;
    cin >> c;
    if (c == 'o')
        exit(0);
    int move = my;
    while (true) {
        for (int i = 0; i < k - 1; i++) {
            other_move();
        }
        my_move(3);
        cin >> c;
        if (c == 'o')
            exit(0);
        move++;
        if (move == k + 1)
            move = 1;
    }
}