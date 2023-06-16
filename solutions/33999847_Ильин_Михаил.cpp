#include<bits/stdc++.h>


using namespace std;


vector<vector<int>> pole;
int n, m, k;
const int INF = 1e9 + 7;


vector<pair<int, int>> moves(int i, int j)
{
    vector<pair<int, int>> ans;
    vector<int> pli1 = {-1, 1, 0};
    vector<int> pli2 = {-1, 1, 0};
    random_shuffle(pli1.begin(), pli1.end());
    random_shuffle(pli2.begin(), pli2.end());
    for (auto pli: pli1)
    {
        for (auto plj: pli2)
        {
            if (abs(pli) + abs(plj) > 0 && i + pli < n && i + pli >= 0 && j + plj < m && j + plj >= 0)
            {
                ans.push_back({i + pli, j + plj});
            }
        }
    }
    return ans;
}


vector<pair<int, int>> attack(int p, int cntmoves)
{
    deque<pair<int, int>> q;
    vector<vector<int>> d(n, vector<int> (m, INF));
    vector<vector<pair<int, int>>> pred(n, vector<pair<int, int>> (m));
    vector<vector<bool>> used(n, vector<bool> (m, false));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (pole[i][j] == p)
            {
                q.push_back({i, j});
                d[i][j] = 0;
            }
        }
    }
    vector<pair<int, int>> ans;
    while (!q.empty() && ans.size() < cntmoves)
    {
        auto [inow, jnow] = q.front();
        q.pop_front();
        if (pole[inow][jnow] != p && pole[inow][jnow] > 0)
        {
            vector<pair<int, int>> rem;
            int inew = inow, jnew = jnow;
            while (pole[inew][jnew] != p)
            {
                if (pole[inew][jnew] != -p && !used[inew][jnew])
                    rem.push_back({inew, jnew});
                used[inew][jnew] = true;
                auto [i1, j1] = pred[inew][jnew];
                inew = i1;
                jnew = j1;
            }
            int ind = rem.size() - 1;
            while (ind >= 0 && ans.size() < cntmoves)
            {
                ans.push_back(rem[ind]);
                ind--;
            }
        }
        auto next_ = moves(inow, jnow);
        for (auto [i2, j2]: next_)
        {
            if (d[i2][j2] == INF && (pole[i2][j2] >= 0 || pole[i2][j2] == -p) && pole[i2][j2] != p)
            {
                if (pole[i2][j2] == -p)
                {
                    d[i2][j2] = d[inow][jnow];
                    pred[i2][j2] = {inow, jnow};
                    q.push_front({i2, j2});
                }
                else
                {
                    d[i2][j2] = d[inow][jnow] + 1;
                    pred[i2][j2] = {inow, jnow};
                    q.push_back({i2, j2});
                }
            }
        }
    }
    for (auto [ix, jx]: ans)
    {
        if (pole[ix][jx] == 0)
        {
            pole[ix][jx] = p;
        }
        else
        {
            pole[ix][jx] = -p;
        }
    }
    return ans;
}


pair<int, int> find_opt(int p)
{
    vector<vector<vector<int>>> d(k, vector<vector<int>> (n, vector<int> (m, INF)));
    for (int K = 0; K < k; K++)
    {
        deque<pair<int, int>> q;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (pole[i][j] == K + 1)
                {
                    q.push_back({i, j});
                    d[K][i][j] = 0;
                }
            }
        }
        while (!q.empty())
        {
            auto [inow, jnow] = q.front();
            q.pop_front();
            auto next_ = moves(inow, jnow);
            for (auto [inew, jnew]: next_)
            {
                if (d[K][inew][jnew] == INF && (pole[inew][jnew] >= 0 || pole[inew][jnew] == -K - 1) && pole[inew][jnew] != K + 1)
                {
                    if (pole[inew][jnew] == -K - 1)
                    {
                        d[K][inew][jnew] = d[K][inow][jnow];
                        q.push_front({inew, jnew});
                    }
                    else
                    {
                        d[K][inew][jnew] = d[K][inow][jnow] + 1;
                        q.push_back({inew, jnew});
                    }
                }
            }
        }
    }
    int ansi = -1, ansj = -1;
    int dmax = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (d[p - 1][i][j] == 1 && pole[i][j] == 0)
            {
                int dmin = INF;
                for (int K = 0; K < k; K++)
                {
                    if (K != p - 1)
                    {
                        dmin = min(dmin, d[K][i][j]);
                    }
                }
                auto moves_ = moves(i, j);
                bool flag = false;
                for (auto [i1, j1]: moves_)
                {
                    if (pole[i1][j1] == -p)
                    {
                        flag = true;
                    }
                }
                if (dmin > dmax && flag)
                {
                    ansi = i;
                    ansj = j;
                    dmax = dmin;
                }
            }
        }
    }
    if (ansi >= 0)
        pole[ansi][ansj] = p;
    return {ansi, ansj};
}


void move_(int p)
{
    cout << p << ' ';
    int cntfast = 2;
    int xdop = n * m / 13 + 1;
    if (rand() % 13 != 0 && rand() % 179 != 0 && rand() % xdop != 0)
    {
        cntfast++;
    }
    auto ans = attack(p, cntfast);
    if (cntfast == 2)
    {
        auto nw = find_opt(p);
        if (nw.first == -1)
        {
            auto ans1 = attack(p, 1);
            if (ans1.size() > 0)
            {
                ans.push_back(ans1[0]);
            }
        }
        else
        {
            ans.push_back(nw);
        }
    }
    cout << ans.size() << ' ';
    for (auto [i, j]: ans)
    {
        cout << i + 1 << ' ' << j + 1 << ' ';
    }
    cout << endl;
    return;
}


int main()
{
    cin >> n >> m >> k;
    pole.resize(n, vector<int> (m));
    int p;
    cin >> p;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> pole[i][j];
        }
    }
    string s = "";
    while (s != "o")
    {
        move_(p);
        cin >> s;
        if (s != "o")
        {
            for (int i = 0; i < k - 1; i++)
            {
                int p1, cntm;
                cin >> p1 >> cntm;
                for (int j = 0; j < cntm; j++)
                {
                    int x, y;
                    cin >> x >> y;
                    x--;
                    y--;
                    if (pole[x][y] == 0)
                    {
                        pole[x][y] = p1;
                    }
                    else
                    {
                        pole[x][y] = -p1;
                    }
                }
            }
        }
    }
    return 0;
}
