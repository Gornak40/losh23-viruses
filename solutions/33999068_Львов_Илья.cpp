#include <bits/stdc++.h>

using namespace std;
#define int long long
const int INF = 10000000000007;
vector<vector<int>> arr;
vector<vector<int>> used;
vector<pair<int, int>> can;
vector<pair<int, int>> can_kill;
int g;

mt19937_64 rnd(time(0));

void dfs(int x, int y) {
    if (used[x][y]) return;
    int n = arr.size(), m = arr[0].size();
    used[x][y] = 1;
    for (int i = x - 1; i <= x + 1; ++i)
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i == x && j == y) continue;
            if (i >= 0 && i < n && j >= 0 && j < m) {
                if (arr[i][j] > 0 && arr[i][j] != g)
                    can_kill.emplace_back(i, j);
                if (arr[i][j] == 0)
                    can.emplace_back(i, j);
                if (abs(arr[i][j]) == g)
                    dfs(i, j);
            }
        }
}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    cin >> g;
    arr.resize(n, vector<int> (m, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> arr[i][j];
    bool first_time = true;
    while (true) {
        vector<pair<int, int>> answer;
        int cnt = 3;
        if (first_time) {first_time = false; cnt = 2;}
        for (int i = 0; i < cnt; ++i) {
            used.clear();
            used.resize(n, vector<int>(m, 0));
            can.clear();
            can_kill.clear();
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j)
                    if (arr[i][j] == g) {
                        dfs(i, j);
                    }
            }
            if (can_kill.size() > 0) {
                int idx = rnd() % can_kill.size();
                answer.push_back(can_kill[idx]);
                arr[can_kill[idx].first][can_kill[idx].second] = -g;
                continue;
            }
            if (can.size() == 0) continue;
            int idx = rnd() % can.size();
            answer.push_back(can[idx]);
            int x = can[idx].first, y = can[idx].second;
            arr[x][y] = g;
        }
        cout << g << " " << answer.size() << " ";
        for (auto i : answer) cout << i.first + 1 << " " << i.second + 1 << " ";
        cout << endl;
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < m; ++j)
//                cout << arr[i][j] << " ";
//            cout << endl;
//        }
        char c;
        cin >> c;
        if (c == 'o') break;
        for (int i = 0; i < k - 1; ++i) {
            int g1, a; cin >> g1 >> a;
            for (int q = 0; q < a; ++q) {
                int x, y; cin >> x >> y;
                if (arr[x - 1][y - 1] == 0)
                    arr[x - 1][y - 1] = g1;
                else
                    arr[x - 1][y - 1] = -g1;
            }
        }
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
