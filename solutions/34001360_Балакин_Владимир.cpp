/*
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⠿⡟⣛⣧⣿⣯⣿⣝⡻⢿⣿⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⠋⠁⣴⣶⣿⣿⣿⣿⣿⣿⣿⣦⣍⢿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⢷⠄⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⢼⣿⣿⣿⣿
⢹⣿⣿⢻⠎⠔⣛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣿⣿⣿⣿
⢸⣿⣿⠇⡶⠄⣿⣿⠿⠟⡛⠛⠻⣿⡿⠿⠿⣿⣗⢣⣿⣿⣿⣿
⠐⣿⣿⡿⣷⣾⣿⣿⣿⣾⣶⣶⣶⣿⣁⣔⣤⣀⣼⢲⣿⣿⣿⣿
⠄⣿⣿⣿⣿⣾⣟⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⢟⣾⣿⣿⣿⣿
⠄⣟⣿⣿⣿⡷⣿⣿⣿⣿⣿⣮⣽⠛⢻⣽⣿⡇⣾⣿⣿⣿⣿⣿
⠄⢻⣿⣿⣿⡷⠻⢻⡻⣯⣝⢿⣟⣛⣛⣛⠝⢻⣿⣿⣿⣿⣿⣿
⠄⠸⣿⣿⡟⣹⣦⠄⠋⠻⢿⣶⣶⣶⡾⠃⡂⢾⣿⣿⣿⣿⣿⣿
⠄⠄⠟⠋⠄⢻⣿⣧⣲⡀⡀⠄⠉⠱⣠⣾⡇⠄⠉⠛⢿⣿⣿⣿
⠄⠄⠄⠄⠄⠈⣿⣿⣿⣷⣿⣿⢾⣾⣿⣿⣇⠄⠄⠄⠄⠄⠉⠉
⠄⠄⠄⠄⠄⠄⠸⣿⣿⠟⠃⠄⠄⢈⣻⣿⣿⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⢿⣿⣾⣷⡄⠄⢾⣿⣿⣿⡄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠸⣿⣿⣿⠃⠄⠈⢿⣿⣿⠄⠄⠄⠄⠄⠄⠄
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define int ll

using namespace std;

#define coa               \
    for (auto i : a) {    \
        cout << i << ' '; \
    }                     \
    cout << '\n';
#define cia             \
    for (auto& i : a) { \
        cin >> a;       \
    }
#define cna                       \
    int n;                        \
    cin >> n;                     \
    vector<int> a(n);             \
    for (int i = 0; i < n; i++) { \
        cin >> a[i];              \
    }
#define cnka                      \
    int n, k;                     \
    cin >> n >> k;                \
    vector<int> a(n);             \
    for (int i = 0; i < n; i++) { \
        cin >> a[i];              \
    }
#define cnab                      \
    int n;                        \
    cin >> n;                     \
    vector<int> a(n);             \
    for (int i = 0; i < n; i++) { \
        cin >> a[i];              \
    }                             \
    vector<int> b(n);             \
    for (int i = 0; i < n; i++) { \
        cin >> b[i];              \
    }

#define cn \
    int n; \
    cin >> n;
#define cnk   \
    int n, k; \
    cin >> n >> k;
#define coe cout << "YES" << '\n'
#define con cout << "NO" << '\n'
#define pb push_back
#define pob pop_back
#define pii pair<int, int>
#define ve vector
#define vei vector<int>
#define veb vector<bool>
#define vevei vector<vector<int>>
#define vepii vector<pair<int, int>>
#define veld ve<ld>
#define veveld ve<ve<ld>>
#define vevepii ve<ve<pii>>
#define veveb ve<ve<bool>>
#define sei set<int>
#define sepii set<pii>
#define mii map<int, int>
#define usei unordered_set<int>
#define usepii unordered_set<pii>
#define umii unordered_map<int, int>
#define use unordered_set
#define uma unordered_map
#define str string
#define all(a) a.begin(), a.end()
#define sc second
#define ss second
#define ff first
#define itn int
const int INF = 1e16;
#define cit   \
    int h, m; \
    char c;   \
    cin >> h >> c >> m;

#define repeat(n) for (int _ = 0; _ < n; _++)
#define fa(i, a) for (auto& i : a)
#define f(i, l, r) for (int i = l; i < r; i++)

int gcd(int a, int b) {
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int binpow(int a, int n, int mod) {
    if (n == 0)
        return 1;
    if (n == 1)
        return a % mod;
    if (n % 2 == 0) {
        int ans = binpow(a, n / 2, mod);
        return ans * ans % mod;
    } else {
        return binpow(a, n - 1, mod) * a % mod;
    }
}

int n, m, k;
int me;

vevei a;
vepii others;
vepii none;

map<pii, bool> used;

void dfs(int i, int j) {
    if (used[{i, j}])
        return;
    used[{i, j}] = true;
    if (a[i][j] == 0) {
        none.pb({i, j});
        return;
    }
    if (a[i][j] == -100)
        return;
    if (a[i][j] < 0 && abs(a[i][j]) != me) {
        return;
    }
    if (a[i][j] > 0 && abs(a[i][j]) != me) {
        others.pb({i, j});
        return;
    }
    if (i > 0) {
        if (j > 0)
            dfs(i - 1, j - 1);
        dfs(i - 1, j);
        if (j < m - 1)
            dfs(i - 1, j + 1);
    }
    if (j > 0) {
        dfs(i, j - 1);
    }
    if (j < m - 1)
        dfs(i, j + 1);
    if (i < n - 1) {
        if (j > 0)
            dfs(i + 1, j - 1);
        dfs(i + 1, j);
        if (j < m - 1)
            dfs(i + 1, j + 1);
    }
}

void bfs(int sti, int stj) {
    queue<pii> q;
    q.push({sti, stj});
    while (!q.empty()) {
        int i = q.front().ff;
        int j = q.front().ss;
        q.pop();
        if (used[{i, j}])
            continue;
        used[{i, j}] = true;
        if (a[i][j] == 0) {
            none.pb({i, j});
            continue;
        }
        if (a[i][j] == -100)
            continue;
        if (a[i][j] < 0 && abs(a[i][j]) != me) {
            continue;
        }
        if (a[i][j] > 0 && abs(a[i][j]) != me) {
            others.pb({i, j});
            continue;
        }
        if (i > 0) {
            if (j > 0)
                q.push({i - 1, j - 1});
            q.push({i - 1, j});
            if (j < m - 1)
                q.push({i - 1, j + 1});
        }
        if (j > 0) {
            q.push({i, j - 1});
        }
        if (j < m - 1)
            q.push({i, j + 1});
        if (i < n - 1) {
            if (j > 0)
                q.push({i + 1, j - 1});
            q.push({i + 1, j});
            if (j < m - 1)
                q.push({i + 1, j + 1});
        }
    }
}

map<pii, bool> start;
int check(int i, int j) {
    if (start[{i, j}])
        return 179;
    if (abs(a[i][j]) == me)
        return 1;
    if (a[i][j] == 0)
        return 0;
    if (a[i][j] < 0)
        return -1;
    return 2;
}

map<pii, pii> par;

pii get(pii a) {
    while (par[a] != make_pair(-1ll, -1ll))
        a = par[a];
    return a;
}

pii bbfs(vepii st) {
    par = {};
    queue<pii> q;
    map<pii, int> d;
    fa(i, st) {
        d[{i.ff, i.ss}] = 0;
        par[{i.ff, i.ss}] = {-1, -1};
        q.push({i.ff, i.ss});
    }
    while (!q.empty()) {
        int i = q.front().ff;
        int j = q.front().ss;
        q.pop();
        if (i > 0 && j > 0) {
            if (check(i - 1, j - 1) == 2)
                return get({i, j});
            if (!used[{i - 1, j - 1}]) {
                d[{i - 1, j - 1}] = d[{i, j}] + 1;
                used[{i - 1, j - 1}] = true;
                par[{i - 1, j - 1}] = {i, j};
                if (check(i - 1, j - 1) != -1)
                    q.push({i - 1, j - 1});
            }
        }
        if (i > 0) {
            if (check(i - 1, j) == 2)
                return get({i, j});
            if (!used[{i - 1, j}]) {
                d[{i - 1, j}] = d[{i, j}] + 1;
                used[{i - 1, j}] = true;
                par[{i - 1, j}] = {i, j};
                if (check(i - 1, j) != -1)
                    q.push({i - 1, j});
            }
        }
        if (i > 0 && j < m - 1) {
            if (check(i - 1, j + 1) == 2)
                return get({i, j});
            if (!used[{i - 1, j + 1}]) {
                d[{i - 1, j + 1}] = d[{i, j}] + 1;
                used[{i - 1, j + 1}] = true;
                par[{i - 1, j + 1}] = {i, j};
                if (check(i - 1, j + 1) != -1)
                    q.push({i - 1, j + 1});
            }
        }
        if (i < n - 1) {
            if (check(i + 1, j) == 2)
                return get({i, j});
            if (!used[{i + 1, j}]) {
                d[{i + 1, j}] = d[{i, j}] + 1;
                used[{i + 1, j}] = true;
                par[{i + 1, j}] = {i, j};
                if (check(i + 1, j) != -1)
                    q.push({i + 1, j});
            }
        }
        if (i < n - 1 && j > 0) {
            if (check(i + 1, j - 1) == 2)
                return get({i, j});
            if (!used[{i + 1, j - 1}]) {
                d[{i + 1, j - 1}] = d[{i, j}] + 1;
                used[{i + 1, j - 1}] = true;
                par[{i + 1, j - 1}] = {i, j};
                if (check(i + 1, j - 1) != -1)
                    q.push({i + 1, j - 1});
            }
        }
        if (i < n - 1 && j < m - 1) {
            if (check(i + 1, j + 1) == 2)
                return get({i, j});
            if (!used[{i + 1, j + 1}]) {
                d[{i + 1, j + 1}] = d[{i, j}] + 1;
                used[{i + 1, j + 1}] = true;
                par[{i + 1, j + 1}] = {i, j};
                if (check(i + 1, j + 1) != -1)
                    q.push({i + 1, j + 1});
            }
        }
        if (j < m - 1) {
            if (check(i, j + 1) == 2)
                return get({i, j});
            if (!used[{i, j + 1}]) {
                d[{i, j + 1}] = d[{i, j}] + 1;
                used[{i, j + 1}] = true;
                par[{i, j + 1}] = {i, j};
                if (check(i, j + 1) != -1)
                    q.push({i, j + 1});
            }
        }
        if (j > 0) {
            if (check(i, j - 1) == 2)
                return get({i, j});
            if (!used[{i, j - 1}]) {
                d[{i, j - 1}] = d[{i, j}] + 1;
                used[{i, j - 1}] = true;
                par[{i, j - 1}] = {i, j};
                if (check(i, j - 1) != -1)
                    q.push({i, j - 1});
            }
        }
    }
    return {-1, -1};
}
pii bbbfs(vepii st) {
    par = {};
    queue<pii> q;
    map<pii, int> d;
    fa(i, st) {
        d[{i.ff, i.ss}] = 0;
        par[{i.ff, i.ss}] = {-1, -1};
        q.push({i.ff, i.ss});
    }
    while (!q.empty()) {
        int i = q.front().ff;
        int j = q.front().ss;
        q.pop();
        if (i > 0 && j > 0) {
            if (check(i - 1, j - 1) == 179)
                return get({i, j});
            else if (!used[{i - 1, j - 1}]) {
                d[{i - 1, j - 1}] = d[{i, j}] + 1;
                used[{i - 1, j - 1}] = true;
                par[{i - 1, j - 1}] = {i, j};
                if (check(i - 1, j - 1) != -1)
                    q.push({i - 1, j - 1});
            }
        }
        if (i > 0) {
            if (check(i - 1, j) == 179)
                return get({i, j});
            else if (!used[{i - 1, j}]) {
                d[{i - 1, j}] = d[{i, j}] + 1;
                used[{i - 1, j}] = true;
                par[{i - 1, j}] = {i, j};
                if (check(i - 1, j) != -1)
                    q.push({i - 1, j});
            }
        }
        if (i > 0 && j < m - 1) {
            if (check(i - 1, j + 1) == 179)
                return get({i, j});
            else if (!used[{i - 1, j + 1}]) {
                d[{i - 1, j + 1}] = d[{i, j}] + 1;
                used[{i - 1, j + 1}] = true;
                par[{i - 1, j + 1}] = {i, j};
                if (check(i - 1, j + 1) != -1)
                    q.push({i - 1, j + 1});
            }
        }
        if (i < n - 1) {
            if (check(i + 1, j) == 179)
                return get({i, j});
            else if (!used[{i + 1, j}]) {
                d[{i + 1, j}] = d[{i, j}] + 1;
                used[{i + 1, j}] = true;
                par[{i + 1, j}] = {i, j};
                if (check(i + 1, j) != -1)
                    q.push({i + 1, j});
            }
        }
        if (i < n - 1 && j > 0) {
            if (check(i + 1, j - 1) == 179)
                return get({i, j});
            else if (!used[{i + 1, j - 1}]) {
                d[{i + 1, j - 1}] = d[{i, j}] + 1;
                used[{i + 1, j - 1}] = true;
                par[{i + 1, j - 1}] = {i, j};
                if (check(i + 1, j - 1) != -1)
                    q.push({i + 1, j - 1});
            }
        }
        if (i < n - 1 && j < m - 1) {
            if (check(i + 1, j + 1) == 179)
                return get({i, j});
            else if (!used[{i + 1, j + 1}]) {
                d[{i + 1, j + 1}] = d[{i, j}] + 1;
                used[{i + 1, j + 1}] = true;
                par[{i + 1, j + 1}] = {i, j};
                if (check(i + 1, j + 1) != -1)
                    q.push({i + 1, j + 1});
            }
        }
        if (j < m - 1) {
            if (check(i, j + 1) == 179)
                return get({i, j});
            else if (!used[{i, j + 1}]) {
                d[{i, j + 1}] = d[{i, j}] + 1;
                used[{i, j + 1}] = true;
                par[{i, j + 1}] = {i, j};
                if (check(i, j + 1) != -1)
                    q.push({i, j + 1});
            }
        }
        if (j > 0) {
            if (check(i, j - 1) == 179)
                return get({i, j});
            else if (!used[{i, j - 1}]) {
                d[{i, j - 1}] = d[{i, j}] + 1;
                used[{i, j - 1}] = true;
                par[{i, j - 1}] = {i, j};
                if (check(i, j - 1) != -1)
                    q.push({i, j - 1});
            }
        }
    }
    return {-1, -1};
}

mt19937 gen(time(0));

void qw(int g, int i, int j) {
    if (a[i][j] == 0) {
        a[i][j] = g;
    } else
        a[i][j] = -g;
}

void solve() {
    cin >> n >> m >> k;
    cin >> me;
    a.assign(n, vei(m));
    str s = "running";
    fa(i, a) {
        fa(j, i) {
            cin >> j;
        }
    }
    f(i, 0, n) {
        f(j, 0, m) {
            if (a[i][j] == me) {
                start[{i, j}];
            }
        }
    }
    int cnt = 0;
    while (s != "o") {
        int cntmine = 0;
        vepii mine;
        f(i, 0, n) {
            f(j, 0, m) {
                if (a[i][j] == me) {
                    mine.pb({i, j});
                }
            }
        }
        cntmine = mine.size();
        used = {};
        others = {};
        none = {};
        fa(i, mine) {
            bfs(i.ff, i.ss);
        }

        int A = min(3ll, (int)(others.size() + none.size()));
        cout << me << ' ' << A << ' ';
        repeat(A) {
            int fi, se;
            if (!others.empty() && (none.size() == 0 || cntmine > 5)) {
                int i = 0;
                if (cnt % 2 == 0)
                    reverse(all(others));
                // random_shuffle(all(others));
                pii q = bbbfs(others);
                f(ii, 0, (int)others.size()) {
                    if (others[ii] == q)
                        i = ii;
                }
                cout << others[i].ff + 1 << ' ' << others[i].ss + 1 << ' ';
                fi = others[i].ff;
                se = others[i].ss;
                others.erase(others.begin() + i);
            } else {
                int i = 0;
                int mn = INF;
                // random_shuffle(all(none));
                pii q = bbfs(none);
                f(ii, 0, (int)none.size()) {
                    if (none[ii] == q)
                        i = ii;
                }
                cout << none[i].ff + 1 << ' ' << none[i].ss + 1 << ' ';
                fi = none[i].ff;
                se = none[i].ss;
                none.erase(none.begin() + i);
            }
            cnt++;
            qw(me, fi, se);
            mine = {};
            f(i, 0, n) {
                f(j, 0, m) {
                    if (a[i][j] == me) {
                        mine.pb({i, j});
                    }
                }
            }
            cntmine = mine.size();
            used = {};
            others = {};
            none = {};
            fa(i, mine) {
                bfs(i.ff, i.ss);
            }
        }
        cout << endl;

        cin >> s;
        if (s == "o")
            return;
        repeat(k - 1) {
            int g, q;
            cin >> g >> q;
            repeat(q) {
                int fi, se;
                cin >> fi >> se;
                qw(g, fi - 1, se - 1);
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed;
    cout.precision(15);

    // cn;

    int n = 1;
    repeat(n) {
        solve();
    }
    return 0;
}