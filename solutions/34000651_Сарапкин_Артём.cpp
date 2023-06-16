#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <deque>
#include <cmath>
#include <random>
#include <unordered_map>

using namespace std;

//#define speed_up ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
//#define endl "\n"
typedef long long ll;
typedef double dl;

const ll INF = 5e18;

dl pi = 3.1415926535897932384626433832795;

//#define cin fin
//#define cout fout

//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx,avx2")

vector<vector<ll>> field;
ll n, m;
ll num;

vector<pair<ll, ll>> vp = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

mt19937 rnd;

bool death = false;
bool pdeath = false;

pair<pair<ll, ll>, bool> move(ll movenum) {
    vector<vector<bool>> used(n, vector<bool>(m));
    vector<vector<bool>> used2(n, vector<bool>(m));
    queue<pair<ll, ll>> q;
    queue<pair<ll, ll>> q2;
    //vector<vector<bool>> attackers(n, vector<bool>(m));
    vector<vector<ll>> dist(n, vector<ll>(m, INF));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (field[i][j] == num) {
                q.push({ i, j });
                used[i][j] = true;
            }
            else if (abs(field[i][j]) != num && field[i][j] != 0 && field[i][j] != -100) {
                dist[i][j] = 0;
                used2[i][j] = true;
                q2.push({ i, j });
            }
        }
    }

    vector<pair<ll, ll>> avail;
    vector<pair<ll, ll>> attack;

    while (!q.empty()) {
        pair<ll, ll> p = q.front();
        q.pop();

        for (auto dir : vp) {
            ll ni = p.first + dir.first;
            ll nj = p.second + dir.second;
            if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
            if (used[ni][nj]) continue;
            if (abs(field[ni][nj]) == num) {
                used[ni][nj] = true;
                q.push({ ni, nj });
            }
            else if (field[ni][nj] == 0 || field[ni][nj] > 0) {
                used[ni][nj] = true;
                if (field[ni][nj] == 0) avail.push_back({ ni, nj });
                else attack.push_back({ ni, nj });
            }
        }
    }

    while (!q2.empty()) {
        pair<ll, ll> p = q2.front();
        q2.pop();

        for (auto dir : vp) {
            ll ni = p.first + dir.first;
            ll nj = p.second + dir.second;
            if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
            if (used2[ni][nj]) continue;
            if (field[ni][nj] != 0) continue;

            used2[ni][nj] = true;
            dist[ni][nj] = dist[p.first][p.second] + 1;
            q2.push({ ni, nj });
        }
    }

    //херабора
    vector<pair<ll, ll>> badAttack;
    vector<pair<ll, ll>> goodAttack;

    for (auto p : attack) {
        bool bad = true;
        for (auto dir : vp) {
            ll ni = p.first + dir.first;
            ll nj = p.second + dir.second;

            if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;

            if (field[ni][nj] == num) bad = false;
        }

        if (bad) {
            badAttack.push_back(p);
        }
        else {
            goodAttack.push_back(p);
        }
    }
    //конец хероборы

    //вторая херобора
    vector<pair<ll, ll>> goodMove;
    vector<pair<ll, ll>> govnoMove;
    vector<pair<ll, ll>> badMove;
    vector<pair<ll, ll>> deathMove;

    for (auto p : avail) {
        bool bad = false;
        bool vb = false;
        for (auto dir : vp) {
            ll ni = p.first + dir.first;
            ll nj = p.second + dir.second;

            if (ni < 0 || nj < 0 || ni >= n || nj >= m) continue;

            if (field[ni][nj] != 0 && field[ni][nj] != -100 && abs(field[ni][nj]) != num) {
                if (field[ni][nj] > 0) {
                    bad = true;
                }
                else {
                    vb = true;
                }
            }
        }

        if (bad) {
            badMove.push_back(p);
        }
        else if (!vb) {
            ll d = dist[p.first][p.second];
            if (d > 3) goodMove.push_back(p);
            else govnoMove.push_back(p);
        }
        else {
            deathMove.push_back(p);
        }
    }
    //конец второй хероборы

    shuffle(goodAttack.begin(), goodAttack.end(), rnd);
    shuffle(badAttack.begin(), badAttack.end(), rnd);
    shuffle(goodMove.begin(), goodMove.end(), rnd);
    shuffle(badMove.begin(), badMove.end(), rnd);
    shuffle(govnoMove.begin(), govnoMove.end(), rnd);
    shuffle(deathMove.begin(), deathMove.end(), rnd);

    if (goodAttack.size() > 0) {
        pair<ll, ll> p = goodAttack[0];
        return { p, true };
    }

    if (movenum == 0 && badMove.size() > 0) {
        pair<ll, ll> p = badMove[0];
        return { p, true };
    }

    if (badAttack.size() > 0) {
        pair<ll, ll> p = badAttack[0];
        return { p, true }; //тут и должно быть true
    }

    if (death) {
        if (govnoMove.size() > 0) {
            pair<ll, ll> p = govnoMove[0];
            return { p, false };
        } else if (goodMove.size() > 0) {
            pair<ll, ll> p = goodMove[0];
            return { p, true };
        } else if (deathMove.size() > 0) {
            pair<ll, ll> p = deathMove[0];
            return { p, false };
        } else if (badMove.size() > 0) {
            pair<ll, ll> p = badMove[0];
            return { p, false };
        }
    }

    if (goodMove.size() > 0) {
        pair<ll, ll> p = goodMove[0];
        return { p, true };
    }
    else if (govnoMove.size() > 0) {
        pair<ll, ll> p = govnoMove[0];
        return { p, false };
    }
    else if (deathMove.size() > 0) {
        pair<ll, ll> p = deathMove[0];
        return { p, false };
    }
    else if (badMove.size() > 0) {
        pair<ll, ll> p = badMove[0];
        return { p, false };
    }
    return { {-1, -1}, false };
}

void moveBy(ll id, ll i, ll j) {
    if (field[i][j] == 0) {
        field[i][j] = id;
    }
    else if (field[i][j] > 0) {
        field[i][j] = -id;
    }
}

void moveAll() {
    vector<pair<ll, ll>> moves;
    ll cnt = 0;
    for (ll i = 0; i < 3; i++) {
        pair<pair<ll, ll>, bool> pp = move(cnt);
        if (pp.first.first != -1 && (i == 0 || pp.second)) {
            cnt++;
            moveBy(num, pp.first.first, pp.first.second);
            moves.push_back(pp.first);
        }
    }

    cout << num << " " << cnt << " ";
    for (ll i = 0; i < cnt; i++) {
        cout << moves[i].first + 1 << " " << moves[i].second + 1 << " ";
    }
    cout << endl;
}

int main() {
    cout << fixed;
    cout.precision(10);
    ll k;
    cin >> n >> m >> k;
    field.resize(n, vector<ll>(m));
    cin >> num;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> field[i][j];
        }
    }

    while (true) {
        moveAll();
        char status; cin >> status;
        if (status == 'o') return 0;
        pdeath = death;
        for (ll i = 0; i < k - 1; i++) {
            ll id, cnt; cin >> id >> cnt;
            ll cnt1 = 0;
            for (ll j = 0; j < cnt; j++) {
                ll ni, nj; cin >> ni >> nj; ni--; nj--;
                if (field[ni][nj] == num) cnt1++;
                moveBy(id, ni, nj);
            }
            if (cnt1 >= 2) death = true;
        }
    }
}