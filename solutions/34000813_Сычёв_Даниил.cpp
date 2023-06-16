#include <bits/stdc++.h>


using namespace std;
//#define int long long
#define pii pair < int, int >

int n, m;
int num;

bool check(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

vector<vector<int> > a;

bool check2(int x, int y) {
    return a[x][y] != num && a[x][y] >= 0;
}
//
//struct node{
//    vector < pii > v;
//    int kol;
//    node(){
//        kol = 0;
//    }
//    void add(pii p){
//        int x = p.first, y = p.second;
//        if(check(x, y) && )
//    }
//};

int main() {
    int k;
    cin >> n >> m >> k;

    cin >> num;

    a.resize(n, vector<int>(m));

    int l = 0, r = 0;
    vector<pii > step = {
            {0,  1},
            {0,  -1}, {1,  0},
                         {1,  1},
                         {1,  -1},
                         {-1, 0},
                         {-1, 1},
                         {-1, -1},
                         };
    vector<pii > step1 = {{1,  1},
                          {0,  1},
                          {-1, 1},
                          {-1, 0}};
//    bool down = true;
//    bool right = true;
//    int len = 1, heig = 1;
    //bool first = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector < vector < int > > used(n, vector < int > (m, 0));
    int timer = 0;
    while (true) {
        vector<pii > hod;
        bool fl = false;
        queue<pii > q;
        vector<vector<int> > good(n, vector<int>(m, 0));
        //queue < int > que;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == -num) {
                    for (auto &tmp: step) {
                        int x = i + tmp.first, y = j + tmp.second;
                        if (check(x, y) && a[x][y] == num) {
                            good[i][j] = 1;
                            q.push({i, j});
                            break;
                        }
                    }
                }
            }
        }

        while (!q.empty()) {
            int x = q.front().first, y = q.front().second;
            q.pop();
            for (auto &tmp: step) {
                int x2 = x + tmp.first, y2 = y + tmp.second;
                if (check(x2, y2) && a[x2][y2] == -num && !good[x2][y2]) {
                    good[x2][y2] = 1;
                    q.push({x2, y2});
                }
            }
        }

        vector<pii > alive;
        int kol_hod = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == num || (a[i][j] == -num && good[i][j])) {
                    for (auto &tmp: step) {
                        //vector< pii > vec;
                        int x = tmp.first + i, y = tmp.second + j;
                        if (!check(x, y) || !check2(x, y)) continue;
                        queue<pair<pii, vector<pii > > > q2;
                        q2.push({{x, y},
                                 {}});
                        while (!q2.empty()) {
                            vector<pii > v = q2.front().second;
                            int x2 = q2.front().first.first, y2 = q2.front().first.second;
                            v.emplace_back(x2, y2);
                            pii p3 = {x2, y2};
                            q2.pop();
                            if ((int) v.size() == 3) {
                                int kol = 0;
                                for (auto &p: v) {
                                    if (a[p.first][p.second] > 0) kol++;
                                }
                                if ((int) v.size() > (int) hod.size() ||
                                    ((int) v.size() == (int) hod.size() && kol >= kol_hod)) {
                                    hod = v;
                                    kol_hod = kol;
                                }
                                continue;
                            }
                            for (auto &t: step) {
                                int nx = x2 + t.first, ny = y2 + t.second;
                                pii p = {nx, ny};
                                if (check(nx, ny) && check2(nx, ny) && v[0] != p && p3 != p) {
                                    q2.push({{nx, ny}, v});
                                }
                            }
                        }
//                        if (vec.size() > hod.size()) hod = vec;
                    }
                }
            }
        }

        cout << num << " ";
        if (hod.size() + alive.size() == 0) {
            cout << 0 << endl;
        } else {
            int maxkol = min((int) hod.size(), 3);
            cout << maxkol << " ";
            int kol = 0;
            for (auto &i: hod) {
                if (kol == maxkol)break;
                cout << i.first + 1 << " " << i.second + 1 << " ";
                a[i.first][i.second] = -num;
                kol++;
            }
            cout << endl;
        }
        cout.flush();
        string temp;
        cin >> temp;
        if (temp == "o") {
            break;
        }

        for (int j = 0; j < k - 1; j++) {
            int ind, cnt;
            cin >> ind >> cnt;
            for (int i = 0; i < cnt; i++) {
                int x, y;
                cin >> x >> y;
                x--;
                y--;
                if (a[x][y] == 0) {
                    a[x][y] = ind;
                } else {
                    a[x][y] = -ind;
                }
            }
        }
    }
}