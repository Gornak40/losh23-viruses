#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

int n, m, g;
set<vector<int>> s;
vector<vector<int>> mat;
vector<vector<bool>> used;

void dfs(int x, int y) {
    if (x < 1 || n < x || y < 1 || m < y)
        return;
    if (used[x][y] || (mat[x][y] < 0 && mat[x][y] != -g))
        return;
    used[x][y] = true;
    if (mat[x][y] == g || mat[x][y] == -g) {
        for (int i = x - 1; i <= x + 1; i++)
            for (int j = y - 1; j <= y + 1; j++)
                dfs(i, j);
    } else {
        int ans1 = 20, ans2 = 20, ans3 = 0;
        for (int i = max(1, x - 7); i <= min(n, x + 7); i++) {
            for (int j = max(1, y - 7); j <= min(m, y + 7); j++) {
                if (mat[i][j] > 0 && mat[i][j] != g)
                    ans1 = min(ans1, max(abs(x - i), abs(y - j)));
                if (mat[i][j] < 0 && mat[i][j] != -g)
                    ans2 = min(ans2, max(abs(x - i), abs(y - j)));
            }
        }
        for (int i = max(1, x - 1); i <= min(n, x + 1); i++) {
            for (int j = max(1, y - 1); j <= min(m, y + 1); j++) {
                if ((mat[i][j] == 0) && (mat[i][j] < 0 || mat[i][j] == g))
                    ans3++;
                if ((mat[i][j] != 0) && (mat[i][j] > 0 && mat[i][j] != g))
                    ans3++;
            }
        }
        s.insert({ans1, -ans2, ans3, x, y});
    }
}

int main() {
    int k, a, col, x, y, ans1, ans2, ans3, id;
    char sta;
    string str;
    cin >> n >> m >> k;
    cin >> g;
    vector<vector<int>> ans;
    mat.resize(n + 1, vector<int>(m + 1));
    used.resize(n + 1, vector<bool>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cin >> mat[i][j];
    }
    while (true) {
        s.clear();
        ans.clear();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                used[i][j] = false;
        id = -1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (mat[i][j] == g && !used[i][j])
                    dfs(i, j);
        for (int o = 0; o < 3; o++) {
            bool flag = true;
            for (auto i = s.begin(); i != s.end(); i++) {
                ans1 = (*i)[0];
                ans2 = (*i)[1];
                ans3 = (*i)[2];
                x = (*i)[3];
                y = (*i)[4];
                if (ans1 != 2) {
                    ans.push_back({x, y, ans1, ans2, ans3});
                    used[x][y] = false;
                    if (mat[x][y] == 0)
                        mat[x][y] = g;
                    else
                        mat[x][y] = -g;
                    dfs(x, y);
                    id++;
                    flag = false;
                    break;
                }
            }
            if (ans.size() == 0 && !s.empty() && flag) {
                x = (*s.begin())[3];
                y = (*s.begin())[4];
                ans1 = (*s.begin())[0];
                ans2 = (*s.begin())[1];
                ans3 = (*s.begin())[2];
                used[x][y] = false;
                if (mat[x][y] == 0)
                    mat[x][y] = g;
                else
                    mat[x][y] = -g;
                dfs(x, y);
                ans.push_back({x, y, ans1, ans2, ans3});
                id++;
            }
            if (id < ans.size())
                s.erase({ans[id][2], ans[id][3], ans[id][4], ans[id][0], ans[id][1]});
        }
        cout << g << ' ' << ans.size() << ' ';
        for (int i = 0; i < ans.size(); i++)
            cout << ans[i][0] << ' ' << ans[i][1] << ' ';
        cout << endl;
        cin >> sta;
        if (sta == 'o')
            break;
        for (int i = g; i < k + g - 1; i++) {
            cin >> col >> a;
            for (int j = 0; j < a; j++) {
                cin >> x >> y;
                if (mat[x][y] == 0)
                    mat[x][y] = col;
                else
                    mat[x][y] = -col;
            }
        }
        if (sta == 'o')
            break;
    }
}
