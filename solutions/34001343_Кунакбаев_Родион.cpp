
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

int bubbleGum = 0;
#ifdef LOCAL
#define FAST_IO 0;
#include "Templates/Debug template.cpp"
#else
#define FAST_IO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define dbg(...) ++bubbleGum
#define dbgArr(x) ++bubbleGum
#endif

// #define int ll
#define vec vector
#define eb emplace_back
#define pb push_back
#define sz(v) (int)(v.size())
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mp(a, b) make_pair(a, b)
#define lb(a, b) lower_bound(all(a), b)


typedef pair<int, int> pii;


const int EMPTY = 0, WALL = -100, INF = 1e9 + 10;
const int N = 305, MAX_PER_MOVE = 3;
const int MAX_PLAYERS = 77;
const int NEED_CROSSES = 5;


int h, w, players;
int myId;
vec<vec<short>> m, mCop;
bool used[N][N];
vec<pii> corners;
vec<pii> goodMoves;
vec<pii> myMoves;
int areaOfplayer[MAX_PLAYERS];

vec<int> dx = { -1, -1, 0, 1, 1, 1, 0, -1 };
vec<int> dy = { 0, 1, 1, 1, 0, -1, -1, -1 };



void start() {
    cin >> h >> w >> players;
    cin >> myId;
    m.resize(h + 1, vec<short>(w + 1));
    mCop = m;

    // assert(players <= 2);
    // assert(w >= 10 && h >= 10);

    corners.eb(mp(1, 1));
    corners.eb(mp(h, 1));
    corners.eb(mp(1, w));
    corners.eb(mp(h, w));

    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            cin >> m[i][j];
        }
    }
}

void putMoves(int id, const vec<pii>& moves) {
    for (auto& [x, y] : moves) {
        if (m[x][y] == EMPTY)
            m[x][y] = id;
        else // this is cross of different player
            m[x][y] = -id;
    }
}

void displayMoves(const vec<pii>& moves) {
    dbg("my move", moves);
    cout << myId << " " << sz(moves) << " ";
    for (auto& [x, y] : moves)
        cout << x << " " << y << " ";
    cout << endl;
    cout.flush();
}



void dfs(int x, int y) {

    if (x < 1 || x > h || y < 1 || y > w || used[x][y] || m[x][y] == WALL)
        return;
    used[x][y] = true;

    if (abs(m[x][y]) != myId) {
        if (m[x][y] >= 0)
            goodMoves.eb(mp(x, y));
        return;
    }

    for (int i = 0; i < sz(dx); ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        dfs(nx, ny);
    }

}

void findWhereCanReach() {

    dbg("find where can reach");
    for (int i = 1; i <= h; ++i)
        fill(used[i], used[i] + w + 1, false);

    goodMoves.clear();
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            if (m[i][j] != myId || used[i][j])
                continue;
            dfs(i, j);
        }
    }
    dbg("------------------");

}



int findCost(const vec<vec<short>>& b) {

    int bad = 0;
    int normMy = 0;
    int wallsMy = 0;

    findWhereCanReach();

    for (auto& [x, y] : goodMoves) {
        if (m[x][y] == EMPTY)
            ++normMy;
        else
            ++wallsMy;
    }

    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            if (m[i][j] <= 0 || m[i][j] == myId)
                continue;
            vec<pii> neibs;
            for (int k = 0; k < sz(dx); ++k) {
                int nx = i + dx[k], ny = j + dy[k];
                if (nx < 1 || nx > h || ny < 1 || ny > w)
                    continue;
                neibs.eb(mp(nx, ny));
            }

            bool isNormMy = false;
            for (auto& [x, y] : neibs) {
                if (m[x][y] == myId)
                    isNormMy = true;
            }
            bad += isNormMy;

        }
    }

    return normMy * 2 + wallsMy * 3 - 70 * bad;
}


void makeMove() {

    if (goodMoves.empty()) {
        cout << myId << " " << 0 << endl;
        cout.flush();
        exit(0);
    }

    int leftMoves = MAX_PER_MOVE;
    myMoves.clear();
    while (leftMoves > 0) {
        findWhereCanReach();
        vec<pii> moves = goodMoves;
        if (moves.empty())
            break;

        mCop = m;
        pii bestCell;
        int bestCost = -INF;
        for (auto& cell : moves) {
            m = mCop;
            putMoves(myId, { cell });
            int cost = findCost(m);
            dbg(cell, cost);
            if (cost > bestCost) {
                bestCost = cost;
                bestCell = cell;
            }
        }
        m = mCop;

        --leftMoves;
        putMoves(myId, { bestCell });
        myMoves.eb(bestCell);
    }

    displayMoves(myMoves);
}


void findPlayersArea() {
    for (auto& it : areaOfplayer)
        it = 0;
    for (int i = 1; i <= h; ++i)
        for (int j = 1; j <= w; ++j)
            ++areaOfplayer[abs(m[i][j])];
}


void makeMove2() {

    if (goodMoves.empty()) {
        cout << myId << " " << 0 << endl;
        cout.flush();
        exit(0);
    }

    int leftMoves = MAX_PER_MOVE;
    myMoves.clear();
    while (leftMoves > 0) {
        findWhereCanReach();
        findPlayersArea();

        if (goodMoves.empty())
            break;

        int cntOfcrosses = 0;
        int closestCorner = 0;
        int old = 0;

        auto dist = [&](const pii& from, const pii& to) {
            int one = abs(from.first - to.first);
            int two = abs(from.second - to.second);
            int ma = max(one, two);
            return ma;
        };

        for (int i = 1; i <= h; ++i)
            for (int j = 1; j <= w; ++j)
                if (m[i][j] == myId)
                    ++cntOfcrosses;

        for (int q = 1; q < sz(corners); ++q) {
            int val = w * h;
            for (int i = 1; i <= h; ++i) {
                for (int j = 1; j <= w; ++j) {
                    if (m[i][j] != myId)
                        continue;
                    int d = dist(corners[q], mp(i, j));
                    val = min(val, d);
                }
            }

            if (val < old) {
                old = val;
                closestCorner = q;
            }
        }

        findPlayersArea();
        if (cntOfcrosses >= NEED_CROSSES) {
            // first we want to create our own walls
            sort(all(goodMoves), [&](const pii &one, const pii &two) {
                int xx = m[one.first][one.second];
                int yy = m[two.first][two.second];
                if (xx > 0 && yy > 0)
                    return areaOfplayer[xx] > areaOfplayer[yy];
                if (xx == 0 && yy == 0) {
                    int d1 = dist(corners[closestCorner], one);
                    int d2 = dist(corners[closestCorner], two);
                    return d1 < d2;
                } else
                    return xx > yy;
            });
        } else {
            // first we want to create crosses
            sort(all(goodMoves), [&](const pii &one, const pii &two) {
                int xx = m[one.first][one.second];
                int yy = m[two.first][two.second];
                if (xx > 0 && yy > 0)
                    return areaOfplayer[xx] > areaOfplayer[yy];
                if (xx == 0 && yy == 0) {
                    int d1 = dist(corners[closestCorner], one);
                    int d2 = dist(corners[closestCorner], two);
                    return d1 < d2;
                } else
                    return xx < yy;
            });
        }

        pii cell = goodMoves[0];
        myMoves.eb(cell);
        --leftMoves;
        putMoves(myId, { cell });
    }

    displayMoves(myMoves);
}




void afterMove() {

    char ch; cin >> ch;
    if (ch == 'o') {
        exit(0);
    }

    for (int i = 1; i <= players - 1; ++i) {
        int id, cc;
        cin >> id >> cc;
        if (!cc)
            continue;
        vec<pii> moves(cc);
        for (auto& [y, x] : moves)
            cin >> y >> x;
        putMoves(id, moves);
    }

}


signed main() {
//#ifdef LOCAL
//    setLocalThings();
//#endif
//    FAST_IO

    start();
    dbg("main cycle");

    while (true) {

        findWhereCanReach();
        dbg(goodMoves);
        if (w * h <= 2000)
            makeMove();
        else
            makeMove2();
        afterMove();

    }

}

/*


4 4 2
1
1 0 0 0
0 0 0 0
0 0 0 0
0 0 0 2


 */