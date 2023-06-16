// clang-format off
#include "bits/stdc++.h"

//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx2")

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;
typedef vector<ll> d1;
typedef vector<d1> d2;
typedef vector<pii> d1p;
typedef vector<d1p> d2p;

ostream& operator<<(ostream&cout, const pii&a){cout<<a.first<<","<<a.second;return cout;}
pii min(const pii &a, const pii &b){if(a.first<b.first) return a;else return b;}
pii max(const pii &a, const pii &b){if(a.first>b.first) return a;else return b;}
template<typename T> T min(vector<T> &a){return *min_element(a.begin(), a.end());}
template<typename T> T max(vector<T> &a){return *max_element(a.begin(), a.end());}
template<typename T> T sum(vector<T>&a){T m=0;for(T&i:a)m+=i;return m;}
template<typename T> void print(vector<T>&a){for(T&i:a)cout<<i<<" ";cout<<"\n";}
template<typename T> void print(vector<vector<T>>&a){for(vector<T>&i:a)print(i);}

#define stuff ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define fori(x, n) for(ll i = x; i < n; ++i)
#define forj(x, n) for(ll j = x; j < n; ++j)
#define fork(x, n) for(ll k = x; k < n; ++k)
#define foru(p, t) for(ll i = p; i < t.size(); i+=i&-i)
#define ford(r, t) for(ll i = r; i > 0; i-=i&-i)
#define all(a) a.begin(), a.end()
//#define sort(a) sort(all(a))
#define reverse(a) reverse(all(a))
#define unique(a) a.erase(unique(all(a)), a.end());
#define wt ll _t; cin>>_t; while(_t--)
#define pb push_back
#define pob pop_back
//#define endl "\n"
#define F first
#define S second
#define B back()

struct move{
    ll x, y, c;
};

d2 board;
ll n, m;

d2 rot = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

pii start;

d2 layers;

void calc_layers(){
    layers = d2(n, d1(m, 1e9));
    layers[start.F][start.S] = 0;
    queue<pii> q;
    q.push(start);
    while(!q.empty()){
        pii v = q.front();
        q.pop();
        for(d1 &i:rot){
            pii to = {v.F + i[0], v.S + i[1]};
            if(to.F >= n or to.F < 0 or to.S >= m or to.S < 0) continue;
            if(layers[to.F][to.S] > layers[v.F][v.S] + 1){
                layers[to.F][to.S] = layers[v.F][v.S] + 1;
                q.push(to);
            }
        }
    }
}

void paint(pii x, ll p){
    if(board[x.F][x.S] == 0){
        board[x.F][x.S] = p+1;
    }
    else{
        board[x.F][x.S] = -(p+1);
    }
}

void get_move(){
    ll p;
    cin >> p;
    p--;
    ll cnt;
    cin >> cnt;
    while(cnt--){
        ll x, y;
        cin >> x >> y;
        x--; y--;
        paint({x, y}, p);
    }
}

d1p get_possible_moves(ll p){
    d2 d(n, d1(m, 1e9));
    queue<pii> q;
    fori(0, n){
        forj(0, m){
            if(board[i][j] == p+1){
                d[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    while(!q.empty()){
        pii v = q.front();
        q.pop();
        for(d1 &i:rot){
            pii to = {v.F + i[0], v.S + i[1]};
            if(to.F >= n or to.F < 0 or to.S >= m or to.S < 0) continue;
            if(d[to.F][to.S] > d[v.F][v.S] and abs(board[to.F][to.S]) == p+1){
                d[to.F][to.S] = d[v.F][v.S];
                q.push(to);
            }
        }
    }
    fori(0, n){
        forj(0, m){
            if(d[i][j] == 0){
                q.push({i, j});
            }
        }
    }
    while(!q.empty()){
        pii v = q.front();
        q.pop();
        for(d1 &i:rot){
            pii to = {v.F + i[0], v.S + i[1]};
            if(to.F >= n or to.F < 0 or to.S >= m or to.S < 0) continue;
            if(d[to.F][to.S] > d[v.F][v.S] + 1){
                d[to.F][to.S] = d[v.F][v.S] + 1;
                q.push(to);
            }
        }
    }
    d1p possible_moves;
    fori(0, n){
        forj(0, m){
            if(board[i][j] >= 0 and board[i][j] != p+1){
                if(d[i][j] == 1){
                    possible_moves.pb({i, j});
                }
            }
        }
    }
    return possible_moves;
}

bool cmp(pii a, pii b){
    return layers[a.F][a.S] < layers[b.F][b.S];
}

void make_move(ll p){
    d1p moves;
    fork(0, 3){
        d1p possible_moves = get_possible_moves(p);
        sort(all(possible_moves), cmp);
        if(!possible_moves.empty()){
            moves.pb(possible_moves[0]);
            paint(possible_moves[0], p);
        }
    }
    cout << p+1 << " " << moves.size() << " ";
    for(pii i:moves){
        cout << i.F + 1 << " " << i.S + 1 << " ";
    }
    cout << endl;
}

signed main(){
    //stuff;
    ll k;
    cin >> n >> m >> k;
    board = d2(n, d1(m));
    board[0][0] = 1;
    board.B.B = 2;
    ll g;
    cin >> g;
    g--;
    fori(0, n){
        forj(0, m){
            cin >> board[i][j];
            if(board[i][j] == g+1){
                start = {i, j};
            }
        }
    }
    calc_layers();
    while(1){
        make_move(g);
        char r;
        cin >> r;
        if(r == 'o') return 0;
        fori(0, k-1){
            get_move();
        }
    }
}
