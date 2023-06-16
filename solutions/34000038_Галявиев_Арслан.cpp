//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops,fast-math")
//#pragma GCC target("avx,avx2,bmi,bmi2,popcnt,lzcnt,tune=native")

using namespace std;

typedef long long ll;
typedef long double ld;

const ll INF = 1e9 + 100, MOD = 1e9 + 7, MAXN = 1e5;
const ld EPS = 1e-6;

random_device rd;
mt19937 rnd(31);

//mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
//uniform_int_distribution <ll> uid;
//ll rnd(ll n) { return abs(uid(rng)) % n; }
//ld rndd() { return ld(rand()) / RAND_MAX; }

#ifdef local
#define debug(x) cerr << (#x) << ": " << x << endl
#define coutcase(x) cout << "Case #" << x << ": "
#else
#define debug(x)
#define coutcase(x)
#endif

#define pow2(x) ((x)*(x))
#define mod(x, m) ((((x) % (m)) + (m)) % (m))
#define max3(a, b, c) max(a, max(b, c))
#define min3(a, b, c) min(a, min(b, c))

int n, m, k, g, u, cntmoves, who_moves;
vector<vector<bool>> connect(302, vector<bool> (302));
vector<vector<vector<pair<int, int>>>> graph(302, vector<vector<pair<int, int>>> (302));
vector<pair<int, int>> make_a_cross;
vector<pair<int, int>> make_a_fortress;

vector<pair<int, int>> moves;
vector<vector<int>> polygon(302, vector<int> (302));
vector<pair<int, int>> order;

bool check_close(int x, int y) {
    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if ((i != x || j != y) && connect[i][j]) return true;
        }
    }
    return false;
}

void find_a_moves() {
    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < m + 2; ++j) {
            connect[i][j] = false;
            graph[i][j].clear();
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (abs(polygon[i][j]) == g + 1) {
                for (int ii = i; ii <= i + 1; ++ii) {
                    for (int jj = j; jj <= j + 1; ++jj) {
                        if ((ii != i || jj != j) && abs(polygon[ii][jj]) == g + 1) {
                            graph[i][j].emplace_back(make_pair(ii, jj));
                            graph[ii][jj].emplace_back(make_pair(i, j));
                        }
                    }
                }
            }
        }
    }
    order.clear();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (polygon[i][j] == g + 1) order.emplace_back(make_pair(i, j));
        }
    }
    u = 0;
    while (u < order.size()) {
        auto [x, y] = order[u];
        connect[x][y] = true;
        for (auto [xnext, ynext] : graph[x][y]) {
            if (!connect[xnext][ynext]) order.emplace_back(make_pair(xnext, ynext));
        }
        ++u;
    }
    make_a_cross.clear();
    make_a_fortress.clear();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (make_a_cross.size() < 8 && polygon[i][j] == 0 && check_close(i, j)) make_a_cross.emplace_back(make_pair(i, j));
            if (make_a_fortress.size() < 8 && polygon[i][j] > 0 && polygon[i][j] != (g + 1) && check_close(i, j)) make_a_fortress.emplace_back(make_pair(i, j));
        }
    }
    shuffle(make_a_cross.begin(), make_a_cross.end(), rnd);
    shuffle(make_a_fortress.begin(), make_a_fortress.end(), rnd);
    if (!make_a_fortress.empty()) {
        moves.emplace_back(make_a_fortress.back());
    } else if (!make_a_cross.empty()){
        moves.emplace_back(make_a_cross.back());
    }
}

void make_a_moves() {
    cout << g + 1 << ' ';
    cout << moves.size() << ' ';
    for (auto [x, y] : moves) {
        cout << x << ' ' << y << ' ';
        if (polygon[x][y] == 0) polygon[x][y] = g + 1;
        else if (polygon[x][y] > 0 && polygon[x][y] != g + 1) polygon[x][y] = -(g + 1);
    }
    cout << endl;
    moves.clear();
    char result;
    cin >> result;
    if (result == 'r') {
        // lets continue our game
    } else {
        exit(0);
    }
}

void take_a_moves() {
    cin >> who_moves;
    cin >> cntmoves;
    while (cntmoves--) {
        int x, y;
        cin >> x >> y;
        if (polygon[x][y] == 0) polygon[x][y] = who_moves;
        else polygon[x][y] = -(who_moves);
    }
}

void polygon_resize() {
    polygon.resize(n + 2);
    for (int i = 0; i <= n + 1; ++i) polygon[i].resize(m + 2);
}

void fill_polygon() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> polygon[i][j];
        }
    }
}

void solve(ll tc) {
    coutcase(tc);

    cin >> n >> m >> k >> g;
    g--;
    fill_polygon();
    for (int who_moves_now = g; who_moves_now > -1; who_moves_now = (who_moves_now + 1) % k) {
        if (who_moves_now == g) {
            find_a_moves();
            for (auto [x, y] : moves) {
                if (polygon[x][y] == 0) polygon[x][y] = g + 1;
                else if (polygon[x][y] > 0 && polygon[x][y] != g + 1) polygon[x][y] = -(g + 1);
            }
            find_a_moves();
            for (auto [x, y] : moves) {
                if (polygon[x][y] == 0) polygon[x][y] = g + 1;
                else if (polygon[x][y] > 0 && polygon[x][y] != g + 1) polygon[x][y] = -(g + 1);
            }
            find_a_moves();
            for (auto [x, y] : moves) {
                if (polygon[x][y] == 0) polygon[x][y] = g + 1;
                else if (polygon[x][y] > 0 && polygon[x][y] != g + 1) polygon[x][y] = -(g + 1);
            }
            make_a_moves();
        } else {
            take_a_moves();
        }
    }
}


signed main() {
//    ios_base::sync_with_stdio(0);
//    cin.tie(0);
//    cout.tie(0);

//    freopen("input.txt", "r", stdin);
//    freopen("failed_ans", "w", stdout);

    ll test = 1;
//    cin >> test;
    for (ll i = 1; i <= test; ++i) {
        solve(i);
    }
    return 0;
}