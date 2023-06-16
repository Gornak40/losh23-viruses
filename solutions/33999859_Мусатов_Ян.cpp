#include <bits/stdc++.h>
#define int long long
using namespace std;

vector<vector<int>> BILLY;
vector<vector<int>> VAN;
vector<pair<int, int>> v1;
vector<pair<int, int>> v2;

mt19937_64 rnd(42310);

vector<pair<int, int>> ssd(int a, int b, vector<pair<int, int>>& ans) {
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (a + i >= 0 and a + i < VAN.size() and b + j >= 0 and b + j < VAN[0].size()) {
                ans.push_back({i, j});
            }
        }
    }
    return ans;
}

void dfs(int a, int b, int p) {
    BILLY[a][b] = 1;
    vector<pair<int, int>> STEVERAMBO;
    ssd(a, b, STEVERAMBO);
    for (auto x : STEVERAMBO) {
        int i = x.first;
        int j = x.second;
        //cout << a << b << a + i << b + j << endl;
        if (abs(VAN[a + i][b + j]) == p and BILLY[a + i][b + j] == 0) {
            dfs(a + i, b + j, p);
        } else if (VAN[a + i][b + j] > 0 and VAN[a + i][b + j] != p and BILLY[a + i][b + j] == 0) {
            BILLY[a + i][b + j] = 1;
            v1.push_back({a + i, b + j});
        } else if (VAN[a + i][b + j] == 0 and BILLY[a + i][b + j] == 0) {
            BILLY[a + i][b + j] = 1;
            v2.push_back({a + i, b + j});
        }
    }
}

signed main() {
    int a, b, c, d, e, f, e1, f1;
    cin >> a >> b >> d;
    cin >> c;
    VAN.resize(a, vector<int> (b, 0));
    BILLY.resize(a, vector<int> (b, 0));
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            cin >> VAN[i][j];
        }
    }
    while (1 == 1) {
        vector<pair<int, int>> slaves;
        for (int g = 0; g < 3; ++g) {
            v1.resize(0);
            v2.resize(0);
            for (int i = 0; i < a; ++i) {
                for (int j = 0; j < b; ++j) {
                    BILLY[i][j] = 0;
                }
            }
            for (int i = 0; i < a; ++i) {
                for (int j = 0; j < b; ++j) {
                    if (VAN[i][j] == c and BILLY[i][j] == 0) {
                        dfs(i, j, c);
                    }
                }
            }
            int ts = 3;
            if (v1.size() > 0 and ts > 0) {
                int fl = rnd() % v1.size();
                slaves.push_back(v1[fl]);
                VAN[v1[fl].first][v1[fl].second] = -c;
            } else if (v2.size() > 0 and ts > 0) {
                int fl = rnd() % v2.size();
                slaves.push_back(v2[fl]);
                VAN[v2[fl].first][v2[fl].second] = c;
            } else {
                break;
            }
        }
        cout << c << " " << slaves.size() << " ";
        for (auto i : slaves) {
            cout << i.first + 1 << " " << i.second + 1 << " ";
        }
        cout << endl;
        cout.flush();
        char dm;
        cin >> dm;
        if (dm == 'o') {
            return 0;
        }
        for (int i = 0; i < d - 1; ++i) {
            cin >> e >> f;
            for (int j = 0; j < f; ++j) {
                cin >> e1 >> f1;
                --e1;
                --f1;
                if (VAN[e1][f1] == 0) {
                    VAN[e1][f1] = e;
                } else {
                    VAN[e1][f1] = -e;
                }
            }
        }
    }
}