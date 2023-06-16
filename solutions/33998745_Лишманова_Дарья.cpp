#include <bits/stdc++.h>
using namespace std;

#define ff first
#define ss second
#define sz(a) (ll)a.size()
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

typedef long long ll;
typedef long double ld;

const ll INF = 1e18 + 1;
const ll N = 300 + 5;
const ll MOD = 1e9 + 7;
int a[N][N];
int used[N][N];
int n, m, k, g;
vector <int> d = {-1, 0, 1};
vector <pair <int, int> > steps;

void ans(){
    cout << g << " " << sz(steps) << " ";
    for (auto e: steps) cout << e.ff << " " << e.ss << " ";
    cout << endl;
}

void f(pair <ll, ll> beg, pair <ll, ll> en){
    ll i = beg.ff;
    ll j = beg.ss;
    ll k1, k2;
    if (beg.ff == 1) k1 = 1;
    else k1 = -1;
    if (beg.ss == 1) k2 = 1;
    else k2 = -1;

    while (i != en.ff){
        while (j != en.ss){
            if (abs(a[i][j]) != g) {
                j += k2;
                continue;
            }

            if (abs(a[i][j]) != g && !used[i][j] && a[i][j] != 0) {
                j += k2;
                continue;
            }


            for (auto x: d){
                for (auto y: d){
                    if (a[i + x][j + y] == 0 || abs(a[i + x][j + y]) == g){
                        used[i + x][j + y] = 1;
                    } else if (a[i + x][j + y] > 0){
                        used[i + x][j + y] = 1;
                    }
                }
            }

            j += k2;
        }
        i += k1;
        j = beg.ss;
    }
}

void solve(){
    for (int i = 0; i < n + 2; i++){
        for (int j = 0; j < m + 2; j++){
            used[i][j] = 0;
        }
    }
    f({1, 1}, {n + 1, m + 1});
    f({1, m}, {n + 1, 0});
    f({n, 1}, {0, m + 1});
    f({n, m}, {0, 0});

    vector <pair <int, int> > emp;
    vector <pair <int, int> > enem;
    for (int i = 1; i < n + 1; i++){
        for (int j = 1; j < m + 1; j++){
            if (!used[i][j]) continue;

            if (a[i][j] == 0) emp.push_back({i, j});
            else if (abs(a[i][j]) == g) continue;
            else enem.push_back({i, j});
        }
    }

    steps.clear();
    while (sz(steps) < 3){
        if (!enem.empty()){
            steps.push_back(enem.back());
            enem.pop_back();
        } else if (!emp.empty()){
            steps.push_back(emp.back());
            emp.pop_back();
        } else break;
    }

    for (auto [i, j]: steps){
        if (a[i][j] == 0) a[i][j] = g;
        else a[i][j] = -g;
    }
    ans();
}

void print(){
    for (int i = 1; i < n + 1; i++){
        for (int j = 1; j < m + 1; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void start(){
    cin >> n >> m >> k >> g;
    for (int i = 1; i < n + 1; i++){
        for (int j = 1; j < m + 1; j++){
            cin >> a[i][j];
        }
    }

    while (true){
        solve();

        //print();
        string s; cin >> s;
        if (s == "o") break;
        for (int i = 0; i < k - 1; i++){
            int G, A; cin >> G >> A;
            for (int j = 0; j < A; j++){
                int x, y; cin >> x >> y;
                if (a[x][y] == 0) a[x][y] = G;
                else a[x][y] = -G;
            }
        }
    }
}

int main() {
    /*#ifdef LOCAL
        freopen("TASK.in", "r", stdin);
        freopen("TASK.out", "w", stdout);
    #endif // LOCAL*/

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie();
    start();
    return 0;
}
