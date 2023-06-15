#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Info {
    int ind;
    long long c;
    int a;
    int b;
    Info() {}
    Info(int _ind, long long _c, int _a, int _b) : ind(_ind), c(_c), a(_a), b(_b) {}
};

struct Point {
    int p;
    long long c;
    int a;
    int b;
    Point() {}
};

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        h[i]--;
    }

    vector<vector<Info>> costs(n);
    vector<Point> pts(k);
    for (int i = 0; i < k; i++) {
        cin >> pts[i].p >> pts[i].c >> pts[i].a >> pts[i].b;
        pts[i].p--;
        pts[i].a--;
        pts[i].b--;
        costs[pts[i].p].emplace_back(i, pts[i].c, pts[i].a, pts[i].b);
    }

    vector<long long> ans(k, 1000000000000000000);
    for (int i = 0; i < k; i++) {
        for (unsigned mask = 0; mask < (1u << k); mask++) {
            if (!((mask >> i) & 1)) {
                continue;
            }
            long long csum = 0;
            unsigned visited = 0;
            unsigned got = 0;
            if (pts[i].a > h[pts[i].p] || pts[i].b < h[pts[i].p]) {
                continue;
            } else {
                visited ^= (1 << pts[i].p);
            }
            while (true) {
                unsigned prevvisited = visited;
                for (int j = 0; j < n; j++) {
                    if ((visited >> j) & 1) {
                        for (auto el : costs[j]) {
                            if ((got >> el.ind) & 1) {
                                continue;
                            }
                            int cind = el.ind;
                            if ((mask >> cind) & 1) {
                                got |= (1 << el.ind);
                                csum += el.c;
                                // for (int ck = j; ck >= 0 && ((h[ck] >= el.a && h[ck] <= el.b) || ((visited >> ck) & 1)); ck--) {
                                //     visited |= (1 << ck);
                                // }
                                // for (int ck = j; ck < n && ((h[ck] >= el.a && h[ck] <= el.b) || ((visited >> ck) & 1)); ck++) {
                                //     visited |= (1 << ck);
                                // }
                                for (int ck = 0; ck < n; ck++) {
                                    if ((visited >> ck) & 1) {
                                        if (h[ck] >= el.a && h[ck] <= el.b) {
                                            if (ck + 1 < n) {
                                                if (h[ck + 1] >= el.a && h[ck + 1] <= el.b) {
                                                    visited |= (1 << (ck + 1));
                                                }
                                            }
                                        }
                                    }
                                }
                                for (int ck = n - 1; ck >= 0; ck--) {
                                    if ((visited >> ck) & 1) {
                                        if (h[ck] >= el.a && h[ck] <= el.b) {
                                            if (ck - 1 >= 0) {
                                                if (h[ck - 1] >= el.a && h[ck - 1] <= el.b) {
                                                    visited |= (1 << (ck - 1));
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (visited == prevvisited) {
                    if (visited == (1u << n) - 1) {
                        ans[i] = min(ans[i], csum);
                    }
                    break;
                }
            }
        }
    }

    for (int i = 0; i < k; i++) {
        if (ans[i] == 1000000000000000000) {
            cout << "-1\n";
        } else {
            cout << ans[i] << "\n";
        }
    }
    return 0;
}