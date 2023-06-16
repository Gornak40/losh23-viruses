#include <bits/stdc++.h>

using namespace std;

random_device rd;
mt19937 lox(727);


int n, m, k, g;

vector <int> dy = {-1, -1, -1, 0, 0, 1, 1, 1};
vector <int> dx = {-1, 0, 1, 1, -1, -1, 0, 1};

void edit(vector <vector <int>> &a, int i, int j, int g) {
    if (a[i][j] != 0) {
        a[i][j] = -g;
    } else {
        a[i][j] = g;
    }
}

bool free(vector <vector <int>> &a, int i, int j, int g) {
    if (a[i][j] != 0)
        return false;
    for (int k = 0; k < 8; k++) {
        int ni = i + dy[k];
        int nj = j + dx[k];
        if (a[ni][nj] == -100)
            continue;
        if (a[ni][nj] > 0 && abs(a[ni][nj]) != g) {
            return false;
        }
    }
    return true;
}



vector <pair <int, int>> plan_a(vector <vector <int>> &a, int g) {
    deque <pair <int, int>> q;
    vector <vector <int>> used(n + 2, vector <int> (m + 2));
    vector <pair <int, int>> good;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == g) {
                q.push_back({i, j});
                used[i][j] = 1;
            }
        }
    }

    while (!q.empty()) {
        auto &[i, j] = q.front();
        q.pop_front();
        for (int k = 0; k < 8; k++) {
            int ni = i + dy[k];
            int nj = j + dx[k];
            if (used[ni][nj])
                continue;
            used[ni][nj] = 1;
            if (free(a, ni, nj, g)) {
                good.push_back({ni, nj});
            } else if (a[ni][nj] == -g) {
                used[ni][nj] = 1;
                q.push_back({ni, nj});
            }
        }
    }

    /*for (auto &[i, j] : good) {
        cout << i << " " << j << "\n";
    } */


    return good;
};

vector <pair <int, int>> plan_b(vector <vector <int>> &a, int g) {
    deque <pair <int, int>> q;
    vector <vector <int>> used(n + 2, vector <int> (m + 2));
    vector <pair <int, int>> good;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == g) {
                q.push_back({i, j});
                used[i][j] = 1;
            }
        }
    }

    while (!q.empty()) {
        auto &[i, j] = q.front();
        q.pop_front();
        for (int k = 0; k < 8; k++) {
            int ni = i + dy[k];
            int nj = j + dx[k];
            if (used[ni][nj])
                continue;
            used[ni][nj] = 1;
            if (a[ni][nj] == 0) {
                good.push_back({ni, nj});
            } else if (a[ni][nj] == -g) {
                used[ni][nj] = 1;
                q.push_back({ni, nj});
            }
        }
    }

    /*for (auto &[i, j] : good) {
        cout << i << " " << j << "\n";
    } */


    return good;
};

vector <pair <int, int>> plan_c(vector <vector <int>> &a, int g) {
    deque <pair <int, int>> q;
    vector <vector <int>> used(n + 2, vector <int> (m + 2));
    vector <pair <int, int>> good;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == g) {
                q.push_back({i, j});
                used[i][j] = 1;
            }
        }
    }

    while (!q.empty()) {
        auto &[i, j] = q.front();
        q.pop_front();
        for (int k = 0; k < 8; k++) {
            int ni = i + dy[k];
            int nj = j + dx[k];
            if (used[ni][nj])
                continue;
            used[ni][nj] = 1;
            if (a[ni][nj] != g && a[ni][nj] > 0) {
                good.push_back({ni, nj});
            } else if (a[ni][nj] == -g) {
                used[ni][nj] = 1;
                q.push_back({ni, nj});
            }
        }
    }

    /*for (auto &[i, j] : good) {
        cout << i << " " << j << "\n";
    } */


    return good;
};



void make_move(vector <vector <int>> &a, int g) {
    auto bro = plan_a(a, g);
    int yuki = 1;
    if (bro.size() >= yuki) {
        shuffle(bro.begin(), bro.end(), lox);
        shuffle(bro.begin(), bro.end(), lox);
        cout << g << " " << yuki << " ";
        for (int i = 0; i < yuki; i++) {
            cout << bro[i].first << " " << bro[i].second << " ";
            edit(a, bro[i].first, bro[i].second, g);
        }
        cout << endl;
        //отлично, берем 3 рандомные
        return;
    }

    //план Б
    bro = plan_b(a, g);

    if (bro.size() >= 3) {
        shuffle(bro.begin(), bro.end(), lox);
        shuffle(bro.begin(), bro.end(), lox);
        cout << g << " " << yuki << " ";
        for (int i = 0; i < yuki; i++) {
            cout << bro[i].first << " " << bro[i].second << " ";
            edit(a, bro[i].first, bro[i].second, g);
        }
        cout << endl;
        //отлично, берем 3 рандомные
        return;
    }

    //план С (все плохо)
    bro = plan_c(a, g);
    shuffle(bro.begin(), bro.end(), lox);
    cout << g << " " << min((int)bro.size(), 3) << " ";
    for (int i = 0; i < min((int)bro.size(), 3); i++) {
        cout << bro[i].first << " " << bro[i].second << " ";
        edit(a, bro[i].first, bro[i].second, g);
    }
    cout << endl;
}

int main() {

    cin >> n >> m >> k >> g;

    vector <vector <int>> a(n + 2, vector <int> (m + 2, -100));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    while (true) {

        make_move(a, g);


        //cout.flush();
        char c;
        cin >> c;
        if (c == 'o') {
            break;
        }


        for (int i = 0; i < k - 1; i++) {
            int ind, cnt;
            cin >> ind >> cnt;
            for (int j = 0; j < cnt; j++) {
                int x, y;
                cin >> x >> y;
                edit(a, x, y, ind);
            }
        }
    }
}