#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <cstdio>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <bitset>
#include <queue>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <ctime>
#include <regex>
#include <list>
#include <random>
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define allv(x) (x).begin(), (x).end()
#define allv_rev(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define FORCE_INLINE inline __attribute__((always_inline))
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rndll(chrono::steady_clock::now().time_since_epoch().count());

/*
const int MAX_MEM = (1024 * 1024) * 180;
int memory_pos = 0;
char memory[MAX_MEM];
inline void * operator new(size_t n) {
    assert((memory_pos += n) <= MAX_MEM);
    return memory + memory_pos - n;
}
*/

inline void operator delete (void*) noexcept {}
inline void operator delete (void*, size_t) noexcept {}


FORCE_INLINE constexpr ull berrett_number(ull d) {
    return ull(-1) / d + 1;
}
FORCE_INLINE constexpr ull divideconst(ull a, ull b, ull m) {
    ull temp = ((unsigned __int128)a * m >> 64);
    return temp - (((b & temp) ^ a) & 1ull);
}

template<typename T>
using ordered_set = __gnu_pbds::tree<
    T,
    __gnu_pbds::null_type,
    less<T>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>;
template<typename T>
bool smin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return true;
    }
    return false;
}
template<typename T>
bool smax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template<typename T>
struct mmi {
    T v;
    ll i;
    bool operator<(mmi<T> b) {
        return v < b.v;
    }
    bool operator<=(mmi<T> b) {
        return v <= b.v;
    }
};
template<typename T>
T minPRB(T a, T b) {
    return (a < b ? a : b);
}
template<typename T>
T maxPRB(T a, T b) {
    return (b < a ? a : b);
}




#ifdef DEBUG
const ll MAXN = 1e5 + 160, INF = 1e12+100;
#else
#define cerr if (0) cerr
const ll MAXN = 1e5 + 160, INF = 1e12+100;
#endif


// DS & DATA
int n, m, me;
vector<pair<int, int>> alive;
int a[300][300];
bool isalive[300][300];
int comp_tow[300][300];
int compsz[300 * 300];
int comp_cnt = 0;
int cost[307][307];
int costad[307][307];
pair<int, int> mx[6];


void upd_mx(int mxv, int mxi) {
    int i = 5;
    while (i > 0) {
        if (mx[i - 1].first < mxv) {
            mx[i] = mx[i - 1];
            --i;
        }
        else {
            break;
        }
    }
    mx[i] = {mxv, mxi};
}
bool incorrect(int i, int j) {
    return i < 0 || j < 0 || i >= n || j >= m;
}


void dfs_alive(int vi, int vj, int cur_comp) {
    //alive.push_back({vi, vj});
    isalive[vi][vj] = true;
    /*
    if (a[vi][vj] < 0) {
        if (cur_comp == 0) {
            comp_tow[vi][vj] = ++comp_cnt;
        }
        compsz[comp_tow[vi][vj]]++;
    }
    */
    for (int iadd = -1; iadd <= 1; ++iadd) {
        for (int jadd = -1; jadd <= 1; ++jadd) {
            int ui = vi + iadd, uj = vj + jadd;
            if (incorrect(ui, uj)) continue;
            if (abs(a[ui][uj]) == me && !isalive[ui][uj]) {
                dfs_alive(ui, uj, /*comp_tow[vi][vj]*/ 0);
            }
        }
    }
}

vector<pair<int, int>> cur_moves;
pair<int, vector<pair<int, int>>> best_move;
vector<pair<int, int>> cur_selected;
void gen(int cur_cost) {
    smax(best_move, {cur_cost, cur_moves});
    if (cur_moves.size() == 3) {
        return;
    }
    for (auto [i, j] : cur_selected) {
        for (int iad = -1; iad <= 1; ++iad) {
            for (int jad = -1; jad <= 1; ++jad) {
                int ui = i + iad, uj = j + jad;
                if (incorrect(ui, uj)) continue;
                if (a[ui][uj] < 0 || a[ui][uj] == me) continue;
                int last = a[ui][uj];
                a[ui][uj] = (a[ui][uj] == 0 ? me : -me);
                cur_moves.push_back({ui, uj});
                cur_selected.push_back({ui, uj});
                gen(cur_cost + cost[ui+3][uj+3]);
                a[ui][uj] = last;
                cur_moves.pop_back();
                cur_selected.pop_back();
            }
        }
    }
}
inline pair<int, int> one() {
    //alive.clear();
    memset(isalive[0], 0, 300 * 300);
    //memset(comp_tow[0], 0, 4 * n * 300);
    //memset(compsz, 0, 4 * n * m);
    //memset(cost[0], 0, 4 * (n + 6) * 307);
    //memset(costad[0], 0, 4 * (n + 6) * 307);
    //cur_moves.clear();
    //best_move.first = -1;
    //cur_selected.clear();
    for (int i = 0; i < 6; ++i) {
        //mx[i].first = 0;
        //mx[i].second = 0;
    }
    //comp_cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!isalive[i][j] && a[i][j] == me) {
                dfs_alive(i, j, 0);
            }
        }
    }
    /*
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cost[i+3][j+3] = (a[i][j] > 0 && a[i][j] != me ? 7 : 0);
            for (int iadd = -1; iadd <= 1; ++iadd) {
                for (int jadd = -1; jadd <= 1; ++jadd) {
                    int ui = i + iadd, uj = j + jadd;
                    if (incorrect(ui, uj)) continue;
                    if (a[ui][uj] < 0 && a[ui][uj] != -100) {
                        cost[i+3][j+3] += 2 * compsz[comp_tow[ui][uj]] + 4;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            costad[i+3][j+1+3] = 0;
            for (int iadd = -1; iadd <= 1; ++iadd) {
                for (int jadd = -1; jadd <= 1; ++jadd) {
                    int ui = i + iadd, uj = j + jadd;
                    if (incorrect(ui, uj)) continue;
                    costad[i+3][j+1+3] += cost[ui+3][uj+3] / 3;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cost[i+3][j+3] += costad[i+3][j+1+3];
        }
    }
    for (int j = 0; j < m; ++j) {
        int cur_sum = 0;
        for (int ui = -3; ui <= 3; ++ui) {
            for (int uj = -3; uj <= 3; ++uj) {
                cur_sum += cost[ui+3][j+uj+3];
            }
        }
        if (isalive[0][j])
            upd_mx(cur_sum + 1, j + 1);
        for (int i = 1; i < n; ++i) {
            for (int uj = -3; uj <= 3; ++uj) {
                cur_sum -= cost[i-4+3][j+uj+3];
                cur_sum += cost[i+3+3][j+uj+3];
            }
            if (isalive[i][j])
                upd_mx(cur_sum + 1, i * m + j + 1);
        }
    }
    for (int i = 0; i < 5; ++i) {
        if (mx[i].second == 0) continue;
        mx[i].second--;
        cur_selected.push_back({mx[i].second / m, mx[i].second % m});
    }
    gen(0);
    if (best_move.first == -1) {
        cout << me << ' ' << 0 << endl;
        cout.flush();
    }
    else {
        cout << me << ' ' << best_move.second.size() << ' ';
        for (auto [ansix, ansiy] : best_move.second) {
            cout << ansix + 1 << ' ' << ansiy + 1 << ' ';
            a[ansix][ansiy] = (a[ansix][ansiy] == 0 ? me : -me);
        }
        cout << endl;
        cout.flush();
    }
    */
    vector<pair<int, int>> avail;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (isalive[i][j]) {
                for (int iadd = -1; iadd <= 1; ++iadd) {
                    for (int jadd = -1; jadd <= 1; ++jadd) {
                        int ui = i + iadd, uj = j + jadd;
                        if (incorrect(ui, uj)) continue;
                        if (a[ui][uj] < 0 || a[ui][uj] == me) continue;
                        avail.push_back({ui, uj});
                    }
                }
            }
        }
    }
    random_shuffle(allv(avail));
    pair<int, int> ans = {-1, -1};
    for (auto [i, j] : avail) {
        if (a[i][j] != 0) {
            ans = {i, j};
            break;
        }
    }
    if (ans.first == -1) {
        for (auto [i, j] : avail) {
            ans = {i, j};
            break;
        }
    }
    return ans;
}


signed main() {
    ios_base::sync_with_stdio(false);
    #ifndef DEBUG
        cin.tie(nullptr);
    #endif
    int k;
    cin >> n >> m >> k;
    cin >> me;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    int max_sz = 2;
    while (true) {
        vector<pair<int, int>> ans = {one()};
        while (ans.size() < max_sz && ans.back().first != -1) {
            a[ans.back().first][ans.back().second] = (a[ans.back().first][ans.back().second] == 0 ? me : -me);
            ans.push_back(one());
        }
        max_sz = 3;
        if (ans.back().first == -1) {
            ans.pop_back();
        }
        if (ans.size() > 0) {
            a[ans.back().first][ans.back().second] = (a[ans.back().first][ans.back().second] == 0 ? me : -me);
        }
        cout << me << ' ' << ans.size() << ' ';
        for (auto [ansix, ansiy] : ans) {
            cout << ansix + 1 << ' ' << ansiy + 1 << ' ';
        }
        cout << endl;
        cout.flush();

        
        char status;
        cin >> status;
        if (status == 'o') {
            return 0;
        }
        for (int i = 0; i < k - 1; ++i) {
            int g, cnt;
            cin >> g >> cnt;
            for (int j = 0; j < cnt; ++j) {
                int xi, yi;
                cin >> xi >> yi;
                --xi, --yi;
                a[xi][yi] = (a[xi][yi] == 0 ? g : -g);
            }
        }
    }
}


/*
░░░░░░░░░░░░░░░░█████░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░████░░░░░███░░░░░░░░░░░░░░░
░░░░██████████░░░░░░████████████░░░░░░░░
░░░░█░░░░░░░█░░░░████░░░░░░░░░░██░░░░░░░
░░░██░░░░░░██░░░░░█░░░░░░░░░░░██░░░░░░░░
░░░█░░░░░░░█░░░░░░███░░░░░█████░░░░░░░░░
░░░░█░░░░░░█░░░░░░░░░███████░░░░░░░░░░░░
░░░░░███████░░░░░░░░░░░░░░░█░░░░░░░░░░░░
░░░░░░░░░░░█░░░███████░░░░░█░░░░░░░░░░░░
░⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⠋⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
⣿⡇⢸⣿⣿⣿⣿⠛⢿⣿⣿⣿⣿⠋⢻⣿⠋⠉⠙⠻⠿⣿⠏⢻⣿
⣿⡇⠸⠿⠏⠻⠿⠆⢸⣿⣿⡟⠰⠆⠘⠷⠴⠖⠂⠀⠴⠿⠇⢸⣿
⣿⣧⣀⣀⣠⣄⣀⣠⣾⣿⣿⣷⣤⣶⣀⣀⣀⣤⣼⣄⣀⣀⣀⣼⣿
⣿⣿⣿⣟⣛⣙⣿⣙⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⣩⣹⣿⣿⣋⣻⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⣾⣿⣿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠻⣿⡇⠀⣿⡿⢿⣿⣿⣿⣿
⣿⣿⣿⣿⣿⣿⣴⣿⡟⢿⣿⠛⣿⣧⠀⣿⡇⠀⣿⣅⠈⣿⣿⣿⣿
⣿⣿⣿⣿⢹⣿⣿⣿⡄⠀⠀⠀⠀⠀⢀⣿⣧⠀⠀⠀⢠⣿⣿⣿⣿
⣿⣿⣿⣿⠀⠙⠛⠛⠁⣸⡟⠿⠿⡿⠿⢿⣿⣿⣿⠟⡟⢿⣿⣿⣿
⣿⣿⣿⣿⣷⣶⣶⣶⣾⣿⣿⣿⣿⣿
░░░░░░░░░░█░░░█░░░░░█░░░░░█░░░░░░░░░░░░
░░░░░░░░░░░█░░░█░░░░░█░░░░█░░░░░░░░░░░░░
░░░░░░░░░░░█░░░█░░░░░█░░░░█░░░░░░░░░░░░░
░░░░░░░░░░░█░░░█░░░░░█░░░░█░░░░░░░░░░░░░
░░░░░░░░░░░█░░░█░░░░░██████░░░░░░░░░░░░░
░░░░░░░░░░░█████░░░░░░░░░░░░░░░░░░░░░░░░
░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
*/
