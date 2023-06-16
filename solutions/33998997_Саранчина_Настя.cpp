#include <bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
const int inf = 1e9 + 7;
const double eps = 1e-12;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
//fffааааааaaao

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    int g; cin >> g;
    int c = 0;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    while(1) {
        c++;
        int A = 3;
        vector<pair<int, int>> res;
        set<pair<int, int>> used;
        for (int qw = 0; qw < A; qw++) {
            vector<vector<int>> dist(n, vector<int>(m, inf));
            set<vector<int>> st;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (a[i][j] == g) {
                        dist[i][j] = 0;
                        st.insert({0, i, j});
                    }
                }
            }
            while(!st.empty()) {
                auto s = *st.begin();
                int d = s[0], i = s[1], j = s[2];
                st.erase(st.begin());
                for (int q = -1; q < 2; q++) {
                    for (int w = -1; w < 2; w++) {
                        int i1 = i + q, j1 = j + w;
                        if (i1 < 0 || j1 < 0 || i1 > n - 1 || j1 > m - 1)
                            continue;
                        if (a[i1][j1] == -g) {
                            if (dist[i1][j1] > dist[i][j]) {
                                st.erase({dist[i1][j1], i1, j1});
                                dist[i1][j1] = dist[i][j];
                                st.insert({dist[i1][j1], i1, j1});
                            }
                        }
                        else if (a[i1][j1] >= 0 && a[i1][j1] != g) {
                            if (dist[i1][j1] > dist[i][j] + 1) {
                                st.erase({dist[i1][j1], i1, j1});
                                dist[i1][j1] = dist[i][j] + 1;
                            }
                        }
                    }
                }
            }
            vector<pair<int, int>> ans;
            for (int I = 0; I < n; I++) {
                for (int J = 0; J < m; J++) {
                    if (dist[I][J] == 1) {
                        ans.push_back({I + 1, J + 1});
                    }
                }
            }
            int cur = -1;
            vector<int> goodans, perfect, THEFUCKINGBEST;
            for (int qw = 0; qw < ans.size(); qw++) {
                if (used.find(ans[qw]) == used.end()) {
                    cur = qw;
                    goodans.push_back(qw);
                    if (a[ans[qw].first - 1][ans[qw].second - 1] > 0) {
                        perfect.push_back(qw);
                        int i = ans[qw].first - 1, j = ans[qw].second - 1;
                        int GGG = a[i][j];
                        bool super = 0;
                        for (int q = -1; q < 2; q++) {
                            for (int w = -1; w < 2; w++) {
                                int i1 = i + q, j1 = j + w;
                                if (i1 < 0 || j1 < 0 || i1 > n - 1 || j1 > m - 1)
                                    continue;
                                if (a[i1][j1] == -GGG)
                                    super = 1;
                            }
                        }
                        if (super)
                            THEFUCKINGBEST.push_back(qw);
                    }
                }
            }
            if (cur == -1) {
                break;
            }
            if (THEFUCKINGBEST.size() != 0) {
                cur = THEFUCKINGBEST[rnd() % THEFUCKINGBEST.size()];
            }
            else if (perfect.size() != 0)
                cur = perfect[rnd() % perfect.size()];
            else
                cur = goodans[rnd() % goodans.size()];
            used.insert(ans[cur]);
            res.push_back(ans[cur]);
            if (a[ans[cur].first - 1][ans[cur].second - 1] == 0)
                a[ans[cur].first - 1][ans[cur].second - 1] = g;
            else
                a[ans[cur].first - 1][ans[cur].second - 1] = -g;
        }
        cout << g << ' ' << res.size() << ' ';
        for (int i = 0; i < res.size(); i++) {
            cout << res[i].first << ' ' << res[i].second << ' ';
        }
        cout << endl;
        char noww;
        cin >> noww;
        if (noww == 'o') {
            exit(0);
        }
        for (int i = 0; i < k - 1; i++) {
            int aa, gg;
            cin >> gg >> aa;
            for (int j = 0; j < aa; j++) {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                if (a[u][v] == 0)
                    a[u][v] = gg;
                else
                    a[u][v] = -gg;
            }

        }
    }
}