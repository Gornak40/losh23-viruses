#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
using namespace std;
int F[300][300];
int C[300][300];
int n, m, k;
vector<vector<pair<int, int>>> fr, en;
vector<pair<int, int>> f(int i, int j) {
    vector<pair<int, int>> ans;
    if (i > 0) {
        ans.emplace_back(i - 1, j);
        if (j < m - 1) {
            ans.emplace_back(i - 1, j + 1);
        }
        if (j > 0) {
            ans.emplace_back(i - 1, j - 1);
        }
    }
    if (i < n - 1) {
        ans.emplace_back(i + 1, j);
        if (j < m - 1) {
            ans.emplace_back(i + 1, j + 1);
        }
        if (j > 0) {
            ans.emplace_back(i + 1, j - 1);
        }
    }
    if (j < m - 1) {
        ans.emplace_back(i, j + 1);
    }
    if (j > 0) {
        ans.emplace_back(i, j - 1);
    }
    return ans;
}
void dfs(int i, int j) {
    if (i > 0) {
        if (abs(F[i - 1][j]) == 1) {
            if (C[i - 1][j] == -1) {
                C[i - 1][j] = C[i][j];
                dfs(i - 1, j);
            }
        } else if (F[i - 1][j] == 2) {
            en[C[i][j]].emplace_back(i - 1, j);
        } else if (F[i - 1][j] == 0) {
            fr[C[i][j]].emplace_back(i - 1, j);
        }
        if (j > 0) {
            if (abs(F[i - 1][j - 1]) == 1) {
                if (C[i - 1][j - 1] == -1) {
                    C[i - 1][j - 1] = C[i][j];
                    dfs(i - 1, j - 1);
                }
            } else if (F[i - 1][j - 1] == 2) {
                en[C[i][j]].emplace_back(i - 1, j - 1);
            } else if (F[i - 1][j - 1] == 0) {
                fr[C[i][j]].emplace_back(i - 1, j - 1);
            }
        }
        if (j < m - 1) {
            if (abs(F[i - 1][j + 1]) == 1) {
                if (C[i - 1][j + 1] == -1) {
                    C[i - 1][j + 1] = C[i][j];
                    dfs(i - 1, j + 1);
                }
            } else if (F[i - 1][j + 1] == 2) {
                en[C[i][j]].emplace_back(i - 1, j + 1);
            } else if (F[i - 1][j + 1] == 0) {
                fr[C[i][j]].emplace_back(i - 1, j + 1);
            }
        }
    }
    if (i < n - 1) {
        if (abs(F[i + 1][j]) == 1) {
            if (C[i + 1][j] == -1) {
                C[i + 1][j] = C[i][j];
                dfs(i + 1, j);
            }
        } else if (F[i + 1][j] == 2) {
            en[C[i][j]].emplace_back(i + 1, j);
        } else if (F[i + 1][j] == 0) {
            fr[C[i][j]].emplace_back(i + 1, j);
        }
        if (j > 0) {
            if (abs(F[i + 1][j - 1]) == 1) {
                if (C[i + 1][j - 1] == -1) {
                    C[i + 1][j - 1] = C[i][j];
                    dfs(i + 1, j - 1);
                }
            } else if (F[i + 1][j - 1] == 2) {
                en[C[i][j]].emplace_back(i + 1, j - 1);
            } else if (F[i + 1][j - 1] == 0) {
                fr[C[i][j]].emplace_back(i + 1, j - 1);
            }
        }
        if (j < m - 1) {
            if (abs(F[i + 1][j + 1]) == 1) {
                if (C[i + 1][j + 1] == -1) {
                    C[i + 1][j + 1] = C[i][j];
                    dfs(i + 1, j + 1);
                }
            } else if (F[i + 1][j + 1] == 2) {
                en[C[i][j]].emplace_back(i + 1, j + 1);
            } else if (F[i + 1][j + 1] == 0) {
                fr[C[i][j]].emplace_back(i + 1, j + 1);
            }
        }
    }
    if (j > 0) {
        if (abs(F[i][j - 1]) == 1) {
            if (C[i][j - 1] == -1) {
                C[i][j - 1] = C[i][j];
                dfs(i, j - 1);
            }
        } else if (F[i][j - 1] == 2) {
            en[C[i][j]].emplace_back(i, j - 1);
        } else if (F[i - 1][j - 1] == 0) {
            fr[C[i][j]].emplace_back(i, j - 1);
        }
    }
    if (j < m - 1) {
        if (abs(F[i][j + 1]) == 1) {
            if (C[i][j + 1] == -1) {
                C[i][j + 1] = C[i][j];
                dfs(i, j + 1);
            }
        } else if (F[i][j + 1] == 2) {
            en[C[i][j]].emplace_back(i, j + 1);
        } else if (F[i][j + 1] == 0) {
            fr[C[i][j]].emplace_back(i, j + 1);
        }
    }
}
int main() {
    cin >> n >> m >> k;
    int g;
    cin >> g;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = -1;
            cin >> F[i][j];
            if (F[i][j] == g) {
                F[i][j] = 1;
            } else if (F[i][j] > 0){
                F[i][j] = 2;
            } else if (F[i][j] == -g) {
                F[i][j] = -1;
            } else if (F[i][j] < 0) {
                F[i][j] = -2;
            }
        }
    }
    int q = 0;
    bool B = true;
    while (true) {
        if (B) {
            while (q > 0) {
                int curr, a;
                cin >> curr >> a;
                for (int pu = 0; pu < a; pu++) {
                    int i, j;
                    cin >> i >> j;
                    i--;
                    j--;
                    if (F[i][j] == 0) {
                        F[i][j] = 2;
                    } else {
                        F[i][j] = -2;
                    }
                }
                q--;
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    C[i][j] = -1;
                }
            }
            int cur = 0;
            fr.clear();
            en.clear();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (F[i][j] == 1 && C[i][j] == -1) {
                        fr.resize(cur + 1);
                        en.resize(cur + 1);
                        C[i][j] = cur;
                        dfs(i, j);
                        cur++;
                    }
                }
            }
            int r = 3;
            vector<pair<int, int>> ANS;
            for (int pu = 0; pu < cur && r; pu++) {
                while (!fr[pu].empty() && r > 1) {
                    if (F[fr[pu][fr[pu].size() - 1].first][fr[pu][fr[pu].size() - 1].second] == 0) {
                        int i = fr[pu][fr[pu].size() - 1].first, j = fr[pu][fr[pu].size() - 1].second;
                        F[i][j] = 1;
                        ANS.push_back(fr[pu][fr[pu].size() - 1]);
                        fr[pu].pop_back();
                        r--;
                    } else {
                        while (!fr[pu].empty() && F[fr[pu][fr[pu].size() - 1].first][fr[pu][fr[pu].size() - 1].second] != 0) {
                            fr[pu].pop_back();
                        }
                    }
                }
                while (!en[pu].empty() && r) {
                    if (F[en[pu][en[pu].size() - 1].first][en[pu][en[pu].size() - 1].second] == 2) {
                        ANS.push_back(en[pu][en[pu].size() - 1]);
                        int i = en[pu][en[pu].size() - 1].first, j = en[pu][en[pu].size() - 1].second;
                        F[i][j] = -1;
                        en[pu].pop_back();
                        r--;
                    } else {
                        while (!en[pu].empty() && F[en[pu][en[pu].size() - 1].first][en[pu][en[pu].size() - 1].second] != 2) {
                            en[pu].pop_back();
                        }
                    }
                }
            }
            if (r == 2) {
                for (int pu = 0; pu < cur && r; pu++) {
                    while (!fr[pu].empty() && F[fr[pu][fr[pu].size() - 1].first][fr[pu][fr[pu].size() - 1].second] == 0 && r) {
                        int i = fr[pu][fr[pu].size() - 1].first, j = fr[pu][fr[pu].size() - 1].second;
                        F[i][j] = 1;
                        ANS.push_back(fr[pu][fr[pu].size() - 1]);
                        fr[pu].pop_back();
                        r--;
                    }
                    while (!en[pu].empty() && r && F[en[pu][en[pu].size() - 1].first][en[pu][en[pu].size() - 1].second] == 2) {
                        ANS.push_back(en[pu][en[pu].size() - 1]);
                        int i = en[pu][en[pu].size() - 1].first, j = en[pu][en[pu].size() - 1].second;
                        F[i][j] = -1;
                        en[pu].pop_back();
                        r--;
                    }
                }
            }
            if (r == 1) {
                for (int pu = 0; pu < cur && r; pu++) {
                    while (!en[pu].empty() && r && F[en[pu][en[pu].size() - 1].first][en[pu][en[pu].size() - 1].second] == 2) {
                        ANS.push_back(en[pu][en[pu].size() - 1]);
                        int i = en[pu][en[pu].size() - 1].first, j = en[pu][en[pu].size() - 1].second;
                        F[i][j] = -1;
                        en[pu].pop_back();
                        r--;
                    }
                    while (!fr[pu].empty() && F[fr[pu][fr[pu].size() - 1].first][fr[pu][fr[pu].size() - 1].second] == 0 && r) {
                        int i = fr[pu][fr[pu].size() - 1].first, j = fr[pu][fr[pu].size() - 1].second;
                        F[i][j] = 1;
                        ANS.push_back(fr[pu][fr[pu].size() - 1]);
                        fr[pu].pop_back();
                        r--;
                    }
                }
            }
            cout << g << ' ' << 3 - r;
            if (r == 3) {
                B = false;
            }
            for (auto p : ANS) {
                int i = p.first, j = p.second;
                cout << ' ' << i + 1 << ' ' << j + 1;
            }
            cout << endl;
            cout.flush();
        } else {
            while (q > 0) {
                int curr, a;
                cin >> curr >> a;
                for (int pu = 0; pu < a; pu++) {
                    int i, j;
                    cin >> i >> j;
                }
                q--;
            }
            cout << g << ' ' << 0 << endl;
        }
        q = k - 1;
        string t;
        cin >> t;
        if (t == "o" || t == "over") {
            exit(0);
        }
    }
}
/*
9 9 3 3
0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 2 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
 */
/*
2
7 6
7 5
3
2 5
2 4
2 3
 */
/*
3
6 4
5 3
4 2
3
3 4
3 3
1 3
 */