#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define ff first
#define ss second
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define pb push_back
#define eb emplace_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define mp make_pair
#define ld long double
#define uset unordered_set
#define umap unordered_map
#define umset unordered_multiset
#define ummap unordered_multimap
#define pii pair<int, int>
#define pil pair<int, long long>
#define pli pair<long long, int>
#define pll pair<long long, long long>
#define bint __int128

//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

const int inf = 1e9;

vector<pii > to{
        {1,  1},
        {-1, 1},
        {1,  -1},
        {-1, -1},
        {-1, 0},
        {1,  0},
        {0,  1},
        {0,  -1}
};

pii operator+(pii a, pii b) {
    return {a.ff + b.ff, a.ss + b.ss};
}

pii operator-(pii a, pii b) {
    return {a.ff - b.ff, a.ss - b.ss};
}

inline void solve() {
    mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int n, m, k;
    cin >> n >> m >> k;
    int num;
    cin >> num;
    int a[n + 2][m + 2];
    for (int i = 0; i < n + 2; i++)
        for (int j = 0; j < m + 2; j++)
            a[i][j] = -100;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i + 1][j + 1];
    char running = 'r';
    while (running == 'r') {
        vector<pii> moves;
        queue<pii> q;
        vector<vector<bool>> used(n + 2,vector<bool>(m + 2));
        vector<vector<bool>> con(n + 2,vector<bool>(m + 2));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (a[i][j] == num) {
                    q.push({i, j});
                    used[i][j] = true;
                    con[i][j] = true;
                }
        while (!q.empty()) {
            auto [cx, cy] = q.front();
            q.pop();
            for (auto [dx, dy] : to) {
                int x, y;
                x = cx + dx;
                y = cy + dy;
                if (a[x][y] == -100)
                    continue;
                if (!used[x][y]) {
                    used[x][y] = true;
                    con[x][y] = con[cx][cy] & (abs(a[x][y]) == num);
                    q.push({x, y});
                }
            }
        }
        for (int _ = 0; _ < 3; _++) {
            vector<pii> enemy;
            vector<pii> nex;
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= m; j++) {
                    if (con[i][j]) {
                        for (auto [dx, dy] : to) {
                            int x, y;
                            x = i + dx;
                            y = j + dy;
                            if (a[x][y] > 0 && a[x][y] != num)
                                enemy.eb(x, y);
                            if (a[x][y] == 0)
                                nex.eb(x, y);
                        }
                    }
                }
            if (!enemy.empty()) {
                int pos = rnd() % enemy.size();
                moves.pb(enemy[pos]);
                auto [x, y] = enemy[pos];
                a[x][y] = -num;
                con[x][y] = true;
            } else if (!nex.empty()) {
                int pos = rnd() % nex.size();
                moves.pb(nex[pos]);
                auto [x, y] = nex[pos];
                a[x][y] = num;
                con[x][y] = true;
            }
        }
        cout << num << ' ' << moves.size() << ' ';
        for (auto [x, y] : moves)
            cout << x << ' ' << y << ' ';
        cout << '\n';
        cout.flush();
        cin >> running;
        if (running == 'r') {
            for (int i = 0; i < k - 1; i++) {
                int g, MOVE;
                cin >> g >> MOVE;
                while (MOVE--) {
                    int x, y;
                    cin >> x >> y;
                    if (!a[x][y])
                        a[x][y] = g;
                    else
                        a[x][y] = -g;
                }
            }
        }
    }

}

signed main() {
    solve();
    return 0;
}