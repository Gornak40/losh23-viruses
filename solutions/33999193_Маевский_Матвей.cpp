#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
typedef long long ll;

const ll N = 305;
const ll INF = 2e9;
const ll LOG = 25;
const ll MOD = 1e9 + 7;
mt19937_64 rnd(time(0));

vector<pair<ll, ll>> g[N][N];
bool used[N][N];

void dfs(vector<vector<ll>>& table, ll i, ll j, ll we, vector<pair<ll, ll>>& can) {
    used[i][j] = true;
    for (auto to : g[i][j]) {
        if (!used[to.first][to.second]) {
            if (abs(table[to.first][to.second]) == we) {
                dfs(table, to.first, to.second, we, can);
            } else if (table[to.first][to.second] >= 0) {
                can.push_back({to.first, to.second});
            }
        }
    }
}

bool move(vector<vector<ll>>& table, ll we, vector<pair<ll, ll>>& make) {
    ll n = table.size(), m = table[0].size();
    vector<pair<ll, ll>> start;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i][j] == we) {
                start.push_back({i, j});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            used[i][j] = false;
        }
    }
    vector<pair<ll, ll>> can;
    for (auto [x, y] : start) {
        if (!used[x][y]) {
            dfs(table, x, y, we, can);
        }
    }
    if (can.empty()) {
        return false;
    }
    random_shuffle(can.begin(), can.end());
    for (auto [x, y] : can) {
        if (table[x][y] > 0) {
            make.push_back({x, y});
            table[x][y] = -we;
            return true;
        }
    }
    auto go = can[rnd() % can.size()];
    table[go.first][go.second] = we;
    make.push_back(go);
    return true;
}

void go_we(vector<vector<ll>>& table, ll we) {
    vector<pair<ll, ll>> make;
    for (int i = 0; i < 3; i++) {
        if (!move(table, we, make)) {
            break;
        }
    }
    cout << we << " " << make.size() << " ";
    for (auto [x, y] : make) {
        cout << x + 1 << " " << y + 1 << " ";
    }
    cout << endl;
}

void go_op(vector<vector<ll>>& table) {
    ll player; cin >> player;
    ll n; cin >> n;
    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;
        if (table[x][y] == 0) {
            table[x][y] = player;
        } else {
            table[x][y] = -player;
        }
    }
}

vector<pair<ll, ll>> go = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

void solve() {
    ll n, m, k, we; cin >> n >> m >> k >> we;
    vector<vector<ll>> table(n, vector<ll> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> table[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (auto [go_i, go_j] : go) {
                ll ni = i + go_i, nj = j + go_j;
                if (0 <= ni && ni < n && 0 <= nj && nj < m) {
                    g[i][j].push_back({ni, nj});
                }
            }
        }
    }
    while (true) {
        go_we(table, we);

        char status; cin >> status;
        if (status == 'o') {
            break;
        }

        for (int i = 0; i < k - 1; i++) {
            go_op(table);
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();

    return 0;
}