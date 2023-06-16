#include <iostream>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <valarray>
#include <typeinfo>
#include <sstream>
#include <bitset>
#include <random>
using namespace std;



int n, m, k;
int me;
vector<vector<int>> table = {};
vector<pair<int, int>> crosses = {};
int move_wt = 1;

random_device rd;
mt19937 gen(rd());



int neighbour_blocks(int x, int y) {
    return 1;
}





pair<int, int> best_move() {
    int x_c = -1;
    int y_c = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (table[i][j] > 0 && table[i][j] != me) {
                int d1 = abs((n / 2) - x_c) + abs((m / 2) - y_c);
                int d2 = abs((n / 2) - i) + abs((m / 2) - j);
                if (d2 < d1) {
                    x_c = i;
                    y_c = j;
                }
            }
        }
    }
    if(x_c == -1) {
        x_c = n / 2;
        y_c = n / 2;
    }
    vector<pair<int, int>> looking_from = crosses;
    pair<int, int> target = make_pair(-1, -1);
    vector<pair<int, int>> if_not = {};
    int i = 0;
    while (i < int(looking_from.size())) {
        int x, y;
        x = get<0>(looking_from[i]);
        y = get<1>(looking_from[i]);
        vector<pair<int, int>> look1 = {};
        if (x == 0) {
            if (y == 0) {
                look1.push_back(make_pair(1, 0));
                look1.push_back(make_pair(1, 1));
                look1.push_back(make_pair(0, 1));
            } else if (y == m - 1){
                look1.push_back(make_pair(1, m - 1));
                look1.push_back(make_pair(1, m - 2));
                look1.push_back(make_pair(0, m - 2));
            } else {
                look1.push_back(make_pair(1, y - 1));
                look1.push_back(make_pair(1, y + 1));
                look1.push_back(make_pair(0, y - 1));
                look1.push_back(make_pair(1, y));
                look1.push_back(make_pair(0, y + 1));
            }
        } else if (x == n - 1) {
            if (y == 0) {
                look1.push_back(make_pair(n - 2, 0));
                look1.push_back(make_pair(n - 2, 1));
                look1.push_back(make_pair(n - 1, 1));
            } else if (y == m - 1){
                look1.push_back(make_pair(n - 2, m - 1));
                look1.push_back(make_pair(n - 2, m - 2));
                look1.push_back(make_pair(n - 1, m - 2));
            } else {
                look1.push_back(make_pair(n - 2, y - 1));
                look1.push_back(make_pair(n - 2, y + 1));
                look1.push_back(make_pair(n - 1, y - 1));
                look1.push_back(make_pair(n - 2, y));
                look1.push_back(make_pair(n - 1, y + 1));
            }
        } else {
            if (y == 0) {
                look1.push_back(make_pair(x, 1));
                look1.push_back(make_pair(x - 1, 0));
                look1.push_back(make_pair(x + 1, 0));
                look1.push_back(make_pair(x - 1, 1));
                look1.push_back(make_pair(x + 1, 1));
            } else if (y == m - 1){
                look1.push_back(make_pair(x - 1, m - 1));
                look1.push_back(make_pair(x - 1, m - 2));
                look1.push_back(make_pair(x, m - 2));
                look1.push_back(make_pair(x + 1, m - 2));
                look1.push_back(make_pair(x + 1, m - 1));
            } else {
                look1.push_back(make_pair(x + 1, y - 1));
                look1.push_back(make_pair(x - 1, y));
                look1.push_back(make_pair(x - 1, y + 1));
                look1.push_back(make_pair(x + 1, y + 1));
                look1.push_back(make_pair(x, y - 1));
                look1.push_back(make_pair(x, y + 1));
                look1.push_back(make_pair(x + 1, y));
                look1.push_back(make_pair(x - 1, y - 1));
            }
        }
        for (int j = 0; j < int(look1.size()); j++) {
            int x1, y1;
            x1 = get<0>(look1[j]);
            y1 = get<1>(look1[j]);
            if (table[x1][y1] >= 0 && table[x1][y1] != me) {
                if (get<0>(target) == -1){
                    if (table[x1][y1] > 0) {
                        target = look1[j];
                    } else {
                        if_not.push_back(look1[j]);
                    }
                } else {
                    if (table[x1][y1] > 0) {
                        if (table[get<0>(target)][get<1>(target)] == 0) {
                            target = look1[j];
                        } else {
                            // переделать
                            int one = abs((n / 2) - get<0>(target)) + abs((m / 2) - get<1>(target));
                            int two = abs((n / 2) - x1) + abs((m / 2) - y1);
                            if (two < one) {
                                target = look1[j];
                            }
                            //long long axx = gen();
                            //if (axx % 2 == 0) {
                                //target = look1[j];
                            //}
                        }
                    } else if (table[get<0>(target)][get<1>(target)] == 0) {
                        // переделать
                        if_not.push_back(look1[j]);
                        //int one = abs((n / 2) - get<0>(target)) + abs((m / 2) - get<1>(target));
                        //int two = abs((n / 2) - x1) + abs((m / 2) - y1);
                        //if (two < one) {
                            //target = look1[j];
                        //}
                        //long long axx = gen();
                        //if (axx % 2 == 0) {
                        //target = look1[j];
                        //}
                    }
                }
            }
            if (table[x1][y1] == -me) {
                int was = 0;
                for (int index = 0; index < int(looking_from.size()); index++) {
                    if (get<0>(looking_from[index]) == x1 && get<1>(looking_from[index]) == y1) {
                        was = 1;
                        break;
                    }
                }
                if (was == 0) {
                    looking_from.push_back(look1[j]);
                }
            }
        }
        i++;
    }
    if (get<0>(target) == -1) {
        if (if_not.size() == 0) {
            return make_pair(-1, -1);
        } else {
            long long axx = gen();
            return if_not[axx % (int(if_not.size()))];
        }
    } else {
        return target;
    }
}




void move() {
    vector<pair<int, int>> our_moves = {};
    int d = 3;
    if (move_wt == 0) {
        d--;
    }
    for (int i = 0; i < d; i++) {
        pair<int, int> movee = best_move();
        if (get<0>(movee) != -1) {
            our_moves.push_back(movee);
            if (table[get<0>(movee)][get<1>(movee)] == 0) {
                table[get<0>(movee)][get<1>(movee)] = me;
                crosses.push_back(movee);
            } else {
                table[get<0>(movee)][get<1>(movee)] = -me;
            }
        }
    }
    cout << me << " " << our_moves.size() << " ";
    for (int i = 0; i < int(our_moves.size()); i++) {
        cout << get<0>(our_moves[i]) + 1 << " " << get<1>(our_moves[i]) + 1 << " ";
    }
    cout << endl;
}



void change() {
    string s;
    cin >> s;
    if (s[0] == 'o') {
        exit(0);
    } else {
        int x, y;
        for (int i = 0; i < k - 1; i++) {
            int player;
            cin >> player;
            int moves;
            cin >> moves;
            for (int j = 0; j < moves; j++) {
                cin >> x >> y;
                if (table[x - 1][y - 1] == 0) {
                    table[x - 1][y - 1] = player;
                } else {
                    if (table[x - 1][y - 1] == me) {
                        int ind = 0;
                        while (crosses[ind] != make_pair(x - 1, y - 1)) {
                            ind++;
                        }
                        crosses.erase(crosses.begin() + ind);
                    }
                    table[x - 1][y - 1] = -player;
                }
            }
        }
    }
}



int main() {
    cin >> n >> m >> k;
    cin >> me;
    vector<int> t(m, 0);
    for (int i = 0; i < n; i++) {
        table.push_back(t);
        for (int j = 0; j < m; j++) {
            cin >> table[i][j];
            if (table[i][j] == me) {
                crosses.push_back(make_pair(i, j));
            }
        }
    }
    while (true){
        move();
        change();
        move_wt++;
    }
}

