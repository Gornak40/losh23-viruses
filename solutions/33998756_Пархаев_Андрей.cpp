#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define all(x) x.begin(), x.end()
#define fi first
#define se second
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
const int INF = 0x3f3f3f3f;
const int W = 305, H = 305, deep = 9;


int get_rnd(int n) {
    return rnd() % n;
}

int seg_rnd(int l, int r) {
    return get_rnd(r - l) + l;
}

int board[H][W] = {{0}};
int n, m, p, k;
vector<pair<int, int>> v, q;
int used[H][W], t = 0;



vector<pair<int, int>> ed(int i, int j) {
    vector<pair<int, int>> edges;
    for (int d1 = -1; d1 <= 1; d1++) {
        for (int d2 = -1; d2 <= 1; d2++) {
            if (board[i + d1][j + d2] == -INF)
                continue;
            if (used[i + d1][j + d2] == t)
                continue;
            if (abs(board[i + d1][j + d2]) == p)
                edges.eb(i + d1, j + d2);
            else if (board[i + d1][j + d2] >= 0)
                v.eb(i + d1, j + d2);
        }
    }
    return edges;
}

void dfs(int i, int j) {
    used[i][j] = t;
    for (auto [x, y] : ed(i, j)) {
        dfs(x, y);
    }
}

void do_step() {
    if (v.empty())
        return;
    int len = (int) v.size();
    int step = 0;
    for (int i = 0; i < len; i++) {
        int nowX = v[step].fi, nowY = v[step].se;
        int wantX = v[i].fi, wantY = v[i].se;
        if (board[wantX][wantY] > 0) {
            if (board[nowX][nowY] > 0) {
                if (get_rnd(4) == 1) {
                    step = i;
                }
            }
            else {
                step = i;
            }
        }
        else {
            if (board[nowX][nowY] > 0) {
                //nothing
            }
            else {
                if (get_rnd(4) == 1) {
                    step = i;
                }
            }
        }
    }
    auto val = v[step];
    vector<pair<int, int>> new_v;
    for (auto it : v) {
        if (it != val)
            new_v.eb(it);
    }
    v = new_v;
    dfs(val.fi, val.se);
    if (board[val.fi][val.se] == 0)
        board[val.fi][val.se] = p;
    else
        board[val.fi][val.se] = -p;
    q.eb(val);
}

void move() {
    t++;
    v.clear();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j] == p && used[i][j] != t) {
                dfs(i, j);
            }
        }
    }
    q.clear();
    for (int i = 0; i < 3; i++) {
        do_step();
    }
    cout << p << " " << q.size();
    //cout << endl;
    cout << " ";
    int Q = (int) q.size();
    for (int j = 0; j < Q; j++) {
        cout << q[j].fi << " " << q[j].se;
        //cout << endl;
        if (j != Q-1) {
            cout << " ";
        }
    }
    cout << endl;
    cout.flush();
}

void output() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j] == 0)
                cout << '.';
            else if (board[i][j] > 0) {
                cout << (char) ('a' + board[i][j]);
            } else {
                cout << (char) ('A' + abs(board[i][j]));
            }
        }
        cout << endl;
    }
}

void play() {
    cin >> n >> m >> k >> p;
    for (int i = 0; i <= n + 1; i++) {
        board[i][0] = -INF;
        board[i][m + 1] = -INF;
    }
    for (int i = 0; i <= m + 1; i++) {
        board[0][i] = -INF;
        board[n + 1][i] = -INF;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int val;
            cin >> val;
            if (val == -100)
                val = -INF;
            board[i][j] = val;
        }
    }
    bool running = true;
    while (true) {
        move();
        //output();
        string verd;
        cin >> verd;
        if (verd == "o")
            break;
        for (int i = 0; i < k - 1; i++) {
            int c, g;
            cin >> c >> g;
            for (int j = 0; j < g; j++) {
                int x, y;
                cin >> x >> y;
                if (board[x][y] > 0 && board[x][y] != c)
                    board[x][y] = -c;
                else if (board[x][y] == 0) {
                    board[x][y] = c;
                }
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    play();
}
//
//
//
//
//