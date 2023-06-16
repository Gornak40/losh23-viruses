#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

const int MAXN = 302;

int pol[MAXN][MAXN];
bool good[MAXN][MAXN];
int g;
bool playing = true;
vector <pair <int, int>> xy_good;
int n, m;
void print() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << pol[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\n";
}
int lastttt;
void polygon() {
    for (int j = 0; j <= m + 1; j++) {
        good[0][j] = false;
        pol[0][j] = -100;
    }
    for (int j = 0; j <= m + 1; j++) {
        pol[n + 1][j] = -100;
        good[n + 1][j] = false;
    }
    for (int i = 0; i <= n + 1; i++) {
        pol[i][0] = -100;
        good[i][0] = false;
    }
    for (int i = 0; i <= n + 1; i++) {
        pol[i][m + 1] = -100;
        good[i][m + 1] = false;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> pol[i][j];
            lastttt = pol[i][j];
            good[i][j] = false;
        }
    }
}

void go_in(int x, int y, int player) {
    if (pol[x][y] == 0) {
        pol[x][y] = player;
    } else {
        if (good[x][y]) {
            good[x][y] = false;
        }
        while (!xy_good.empty() && !good[xy_good.back().first][xy_good.back().second]) {
            xy_good.pop_back();
        }
        pol[x][y] = -player;
    }
}

void move_opponent() {
    int type, a;
    cin >> type >> a;
    int x, y;
    for (int i = 0; i < a; i++) {
        cin >> x >> y;
        go_in(x, y, type);
    }
}
int lastype = -1;
void can_go(vector <pair <int, int>>& ans, int ost) {
    vector <pair <int, int>> go;
    vector <pair <int, int>> cr;
    vector <pair <int, int>> rgo;
    vector <pair <int, int>> rgo2;
    vector <pair <int, int>> ans1;
    vector <pair <int, int>> ans0;
    vector <pair <int, int>> ans2;
    vector <pair <int, int>> ans3;
    vector <pair <int, int>> ans4;
    vector <pair <int, int>> ans5;
    bool used[n + 2][m + 2];
    int rast[n + 2][m + 2];
    int brast[n + 2][m + 2];
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            used[i][j] = false;
            if (pol[i][j] == -100) {
                used[i][j] = true;
            } else if (pol[i][j] == g) {
                used[i][j] = true;
                go.push_back({i, j});
            }
            rast[i][j] = 10 * (n + m);
            if (pol[i][j] > 0 && pol[i][j] != g) {
                rast[i][j] = 0;
                rgo.push_back({i, j});
            }
        }
    }
    while (!rgo.empty() || !rgo2.empty()) {
        while (!rgo.empty()) {
            auto [x, y] = rgo.back();
            rgo.pop_back();
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (rast[x + i][y + j] == 10 * (n + m)) {
                        rast[x + i][y + j] = rast[x][y] + 1;
                        if (pol[x + i][y + j] == -g) {
                            if (pol[x][y] == g) {
                                rast[x + i][y + j]--;
                            }
                            cr.push_back({x + i, y + j});
                        }
                        if (pol[x + i][y + j] >= 0) {
                            rgo2.push_back({x + i, y + j});
                        }
                    }
                }
            }
        }
        while (!cr.empty()) {
            auto [x, y] = cr.back();
            cr.pop_back();
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (rast[x + i][y + j] == 10 * (n + m)) {
                        rast[x + i][y + j] = rast[x][y];
                        if (pol[x + i][y + j] == -g) {
                            cr.push_back({x + i, y + j});
                        }
                        if (pol[x + i][y + j] >= 0) {
                            rgo2.push_back({x + i, y + j});
                        }
                    }
                }
            }
        }
        swap(rgo2, rgo);
    }
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            brast[i][j] = 10 * (n + m);
            if (pol[i][j] > 0 && pol[i][j] != g) {
                brast[i][j] = 0;
                rgo.push_back({i, j});
            }
        }
    }
    while (!rgo.empty() || !rgo2.empty()) {
        while (!rgo.empty()) {
            auto [x, y] = rgo.back();
            rgo.pop_back();
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (brast[x + i][y + j] == 10 * (n + m)) {
                        brast[x + i][y + j] = brast[x][y] + 1;
                        if (pol[x + i][y + j] < 0 && pol[x + i][y + j] != -100 && pol[x + i][y + j] != -g) {
                            if (pol[x + i][y + j] == -pol[x][y]) {
                                brast[x + i][y + j]--;
                            }
                            cr.push_back({x + i, y + j});
                        }
                        if (pol[x + i][y + j] >= 0) {
                            rgo2.push_back({x + i, y + j});
                        }
                    }
                }
            }
        }
        while (!cr.empty()) {
            auto [x, y] = cr.back();
            cr.pop_back();
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (brast[x + i][y + j] == 10 * (n + m)) {
                        brast[x + i][y + j] = brast[x][y];
                        if (pol[x + i][y + j] < 0 && pol[x + i][y + j] != -100 && pol[x + i][y + j] != -g) {
                            cr.push_back({x + i, y + j});
                        }
                        if (pol[x + i][y + j] >= 0) {
                            rgo2.push_back({x + i, y + j});
                        }
                    }
                }
            }
        }
        swap(rgo2, rgo);
    }
    int rr[n + 2][m + 2];
    if (!xy_good.empty()) {
        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= m + 1; j++) {
                rr[i][j] = 10 * (n + m);
            }
        }
        int x_good = xy_good.back().first;
        int y_good = xy_good.back().second;
        rr[x_good][y_good] = 0;
        rgo.push_back({x_good, y_good});
        while (!rgo.empty() && !rgo2.empty()) {
            while (!rgo.empty()) {
                auto [x, y] = rgo.back();
                rgo.pop_back();
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (pol[x + i][y + j] == -g || pol[x + i][y + j] == -100) {
                            continue;
                        }
                        if (rr[x + i][y + j] == 10 * (n + m)) {
                            rr[x + i][y + j] = rr[x][y] + 1;
                            if (pol[x + i][y + j] < 0) {
                                rr[x + i][y + j]--;
                                cr.push_back({x + i, y + j});
                            } else {
                                rgo2.push_back({x + i, y + j});
                            }
                        }
                    }
                }
            }
            while (!cr.empty()) {
                auto [x, y] = cr.back();
                cr.pop_back();
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (pol[x + i][y + j] == -g || pol[x + i][y + j] == -100) {
                            continue;
                        }
                        if (rr[x + i][y + j] == 10 * (n + m)) {
                            rr[x + i][y + j] = rr[x][y];
                            if (pol[x + i][y + j] < 0) {
                                cr.push_back({x + i, y + j});
                            } else {
                                rgo2.push_back({x + i, y + j});
                            }
                        }
                    }
                }
            }
            swap(rgo, rgo2);
        }
    }
    while (!go.empty()) {
        auto [x, y] = go.back();
        go.pop_back();
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (!used[x + i][y + j]) {
                    used[x + i][y + j] = true;
                    if (abs(pol[x + i][y + j]) == g) {
                        go.push_back({x + i, y + j});
                    }
                    if (pol[x + i][y + j] < 0) {
                        continue;
                    }
                    if (!xy_good.empty() && rr[x + i][y + j] <= 2 && rast[x + i][y + j] <= ost) {
                        if (ans0.empty()) {
                            ans0.push_back({x + i, y + j});
                        } else {
                            if (rr[x + i][y + j] < rr[ans0[0].first][ans0[0].second]) {
                                ans0.clear();
                                ans0.push_back({x + i, y + j});
                            } else if (rr[x + i][y + j] < rr[ans0[0].first][ans0[0].second]) {
                                ans0.push_back({x + i, y + j});
                            }
                        }

                    } else if (ost == 1 && brast[x + i][y + j] >= 2 && pol[x + i][y + j] == 0 && pol[x][y] == -g) {
                        ans1.push_back({x + i, y + j});
                    } else if (pol[x + i][y + j] > 0) {
                        ans2.push_back({x + i, y + j});
                    } else if (rast[x + i][y + j] == 1 && ost == 3){
                        ans3.push_back({x + i, y + j});
                    } else if (brast[x + i][y + j] <= 2){
                        ans5.push_back({x + i, y + j});
                    } else {
                        ans4.push_back({x + i, y + j});
                    }
                }
            }
        }
    }
    int x_good;
    int y_good = -1;
    if (!ans5.empty()) {
        lastype = 5;
        swap(ans5, ans);
    }
    if (!ans4.empty()) {
        lastype = 4;
        if (lastttt != g) {
            reverse(ans4.begin(), ans4.end());
        }
        swap(ans4, ans);
    }
    if (!ans3.empty()) {
        lastype = 3;
        swap(ans3, ans);
    }
    if (!ans2.empty()) {
        lastype = 2;
        swap(ans2, ans);
        x_good = ans[0].first;
        y_good = ans[0].second;
    }
    if (!ans1.empty()) {
        lastype = 1;
        swap(ans1, ans);
        x_good = ans[0].first;
        y_good = ans[0].second;
    }
    if (!ans0.empty()) {
        lastype = 0;
        swap(ans0, ans);
        x_good = ans[0].first;
        y_good = ans[0].second;
    }
    if (y_good != -1) {
        good[x_good][y_good] = true;
        xy_good.push_back({x_good, y_good});
    }
}

void move_i() {
    vector <pair <int, int>> ans;
    for (int i = 0; i < 3; i++) {
        lastype = -1;
        vector <pair <int, int>> go;
        can_go(go, 3 - i);
        if (go.empty()) {
            break;
        }
        if (lastype == 5 && i != 0) {
            break;
        }
        ans.push_back(go[0]);
        auto [x, y] = go[0];
        go_in(x, y, g);
    }
    cout << g << " " << ans.size();
    for (auto [x, y] : ans) {
        cout << " " << x << " " << y;
    }
    cout << endl;
    char c;
    cin >> c;
    if (c == 'o') {
        playing = false;
    }
}

int main() {
    int k;
    cin >> n >> m >> k;
    cin >> g;
    polygon();
    move_i();
//    print();
    while (playing) {
        for (int i = 0; i < k - 1; i++) {
            move_opponent();
        }
//        print();
        move_i();
//        print();
    }
}
//last1
