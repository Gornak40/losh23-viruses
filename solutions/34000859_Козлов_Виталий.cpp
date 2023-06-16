#pragma GCC optimize("O3")

#include <bits/stdc++.h>
#ifdef LOCAL
#include "printer.hpp"
#else
#define print(...)
#endif
using namespace std;
bool __nothing0 = ios::sync_with_stdio(false);
bool __nothing1 = cin.tie(0);
bool __nothing2 = cout.tie(0);

const int MAX_N = 301, MAX_M = 301, MAX_PLAYERS = 76;
int n, m, k, identifier;

class WEIGHTS {
 public:
    static double DIRECT_STEP;
    static double DIAGONAL_STEP;
    static double KILL[3];
    static double CAME_TO_ENEMY[500];
    static double ATACKED_BY_1;
    static double DOUBLE_KILL;
    static double TRIPLE_KILL;
    static double MY_TOWER_AROUND[9];
    static double EMPTY_CELLS_AROUND[9];
    static double DESTROYED_PATHS[3];
    static double KILL_ON_EDGE[3];
};

double WEIGHTS::DIRECT_STEP = 0.15;
double WEIGHTS::DIAGONAL_STEP = 0.2;
double WEIGHTS::KILL[3] = {6, 2, 0.15};
double WEIGHTS::CAME_TO_ENEMY[500] = {0.05, -0.3, -0.25, 0.2};
double WEIGHTS::ATACKED_BY_1 = -0.05;
double WEIGHTS::DOUBLE_KILL = 0.5;
double WEIGHTS::TRIPLE_KILL = 2;
double WEIGHTS::MY_TOWER_AROUND[9] = {0.05, 0.1, 0, 0, -0.2, -0.3, -3, -11, -50};
double WEIGHTS::EMPTY_CELLS_AROUND[9] = {-0.05, -0.03, 0.3, 2.3, 0.4, 0.3, 0.2, -0.7, -10};
double WEIGHTS::DESTROYED_PATHS[3] = {5, 7, 10};
double WEIGHTS::KILL_ON_EDGE[3] = {7, 4, 0.5};


class Cell {
 public:
    int value;
    int x;
    int y;
    int distance_from[MAX_PLAYERS];
    bool is_on_edge;
    vector<pair<int, int>> player_comes_from;

    Cell() {}

    Cell(int value, int x, int y) {
        this->value = value;
        this->x = x;
        this->y = y;
        for (int i = 1; i <= k; i++) {
            this->distance_from[i] = -1;
        }
    }

    pair<int, int> pos() {
        return {x, y};
    }

    vector<pair<int, int>> neighbours() const {
        vector<pair<int, int>> result;
        for (int i = x - 1; i != x + 2; i++) {
            for (int j = y - 1; j != y + 2; j++) {
                if (i == x && j == y) {
                    continue;
                }
                if (0 <= i && i < n && 0 <= j && j < m) {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }
    bool is_connected() const {
        if (value == 0 || value == -100) {
            return false;
        }
        return distance_from[abs(value)] == 0;
    }

    bool is_cross() const {
        return value > 0;
    }
    bool is_empty() const {
        return value == 0;
    }
    bool is_tower() const {
        return value < 0;
    }

    bool is_wall() const {
        return value == -100;
    };

    bool can_be_atacked() const {
        return value >= 0 && value != identifier;
    };

};


Cell field[MAX_N][MAX_M];

class Step {
 public:
    double weight;
    vector<pair<int, int>> path;
    Step(vector<pair<int, int>> initial_path = {}, double initial_weight = 0) {
        this->path = initial_path;
        this->weight = initial_weight;
    }
    void recalculate_weight() {
        weight = 0;
        for (int i = 0; i < path.size() - 1; i++) {
            if (path[i].first == path[i + 1].first || path[i].second == path[i + 1].second) {
                weight += WEIGHTS::DIRECT_STEP;
            } else {
                weight += WEIGHTS::DIAGONAL_STEP;
            }
        }
        int kills = 0;
        for (int i = 0; i < path.size(); i++) {
            auto [x, y] = path[i];
            Cell &cell = field[x][y];

            vector<double> distances;
            for (int player = 1; player <= k; player++) {
                if (player == identifier) continue;
                distances.push_back(WEIGHTS::CAME_TO_ENEMY[cell.distance_from[player]]);
            }
            sort(distances.begin(), distances.end());
            for (int vi = 0; vi < (k + 3) / 4; vi++) {
                weight += distances[vi];
            }

            if (cell.is_cross()) {
                kills++;
                weight += WEIGHTS::KILL[i];
                if (cell.is_on_edge) {
                    weight += WEIGHTS::KILL_ON_EDGE[i];
                }
            }
            int tower_cnt = 0, empty_cnt = 0, destroyed_paths = 0;
            for (pair<int, int> nei : cell.neighbours()) {
                if (destroyed_paths < 3 && !field[nei.first][nei.second].player_comes_from.empty() &&
                    all_of(field[nei.first][nei.second].player_comes_from.begin(),
                           field[nei.first][nei.second].player_comes_from.end(),
                           [&path = path](pair<int, int> item) {
                               return find(path.begin(), path.end(), item) != path.end();
                           })) {
                    weight += WEIGHTS::DESTROYED_PATHS[destroyed_paths];
                    destroyed_paths++;

                }


                if (find(path.begin(), path.end(), nei) != path.end() ||
                    field[nei.first][nei.second].value == identifier) {
                    continue;
                }
                if (field[nei.first][nei.second].value == -identifier) {
                    tower_cnt++;
                } else if (field[nei.first][nei.second].is_connected()) {
                    weight += WEIGHTS::ATACKED_BY_1;
                } else if (field[nei.first][nei.second].value == 0) {
                    empty_cnt++;
                }
            }
            if (cell.is_cross()) {
                weight += WEIGHTS::MY_TOWER_AROUND[tower_cnt] + WEIGHTS::EMPTY_CELLS_AROUND[empty_cnt];
            } else {
                weight += -(WEIGHTS::EMPTY_CELLS_AROUND[empty_cnt] / 3);
            }
        }
        if (kills == 2) {
            weight += WEIGHTS::DOUBLE_KILL;
        } else if (kills == 3) {
            weight += WEIGHTS::TRIPLE_KILL;
        }
    }
    bool operator<(const Step &other) const {
        return weight < other.weight;
    }

    Step operator+(const pair<int, int> p) {
        vector<pair<int, int>> new_path = path;
        new_path.push_back(p);
        return {new_path, weight};
    }
};


class AI {
 public:
    void read_field() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int value;
                cin >> value;
                field[i][j] = Cell(value, i, j);
            }
        }
    }
    void update_field(const vector<pair<int, vector<pair<int, int>>>> &other_moves) {
        vector<vector<int>> new_field(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                new_field[i][j] = field[i][j].value;
            }
        }
        for (auto [player, moves] : other_moves) {
            for (auto [x, y] : moves) {
                if (new_field[x][y] == 0) {
                    new_field[x][y] = player;
                } else {
                    new_field[x][y] = -player;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                field[i][j] = Cell(new_field[i][j], i, j);
            }
        }
    }

    void process() {
        queue<pair<int, pair<int, int>>> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (field[i][j].is_cross()) {
                    q.push({field[i][j].value, {i, j}});
                    field[i][j].distance_from[field[i][j].value] = 0;
                    field[i][j].is_on_edge = field[i][j].is_cross();
                }
            }
        }
        while (!q.empty()) {
            auto [player, pos] = q.front();
            q.pop();
            int cnt_for_edge = 0;
            for (auto [i, j] : field[pos.first][pos.second].neighbours()) {
                if (field[i][j].value == 0 || (field[i][j].value < 0 && field[i][j].value != -identifier)) {
                    cnt_for_edge++;
                }
                if (field[i][j].value == -player && field[pos.first][pos.second].value == player) {
                    if (find(field[i][j].player_comes_from.begin(), field[i][j].player_comes_from.end(), pos) ==
                        field[i][j].player_comes_from.end()) {
                        field[i][j].player_comes_from.push_back(pos);
                    }
                } else if (field[i][j].value == -player && field[pos.first][pos.second].value == -player) {
                    for (pair<int, int> to_add_pos : field[pos.first][pos.second].player_comes_from) {
                        if (find(field[i][j].player_comes_from.begin(), field[i][j].player_comes_from.end(),
                                 to_add_pos) ==
                            field[i][j].player_comes_from.end()) {
                            field[i][j].player_comes_from.push_back(to_add_pos);
                        }
                    }


                }
                if (field[i][j].distance_from[player] != -1) {
                    continue;
                }
                if (field[i][j].is_wall()) {
                    continue;
                }
                q.push({player, {i, j}});
                if (abs(field[i][j].value) == player && field[pos.first][pos.second].distance_from[player] == 0) {
                    field[i][j].distance_from[player] = 0;
                } else {
                    field[i][j].distance_from[player] = field[pos.first][pos.second].distance_from[player] + 1;
                }
            }
            if (!cnt_for_edge) {
                field[pos.first][pos.second].is_on_edge = false;
            }
        }

    };

    vector<pair<int, int>> make_step() {
        queue<Step> q;
        vector<pair<int, int>> temp;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (field[i][j].distance_from[identifier] == 1 && field[i][j].can_be_atacked()) {
                    q.push(Step({{i, j}}));
                    temp.push_back({i, j});
                }
            }
        }

        for (int i = 0; i < temp.size(); i++) {
            for (int j = i + 1; j < temp.size(); j++) {
                if (max(abs(temp[i].first - temp[j].first), abs(temp[i].second - temp[j].second))) {
                    continue;
                }
                q.push(Step({temp[i], temp[j]}));
                q.push(Step({temp[j], temp[i]}));
            }
        }


        Step best = Step({}, -1e9);

        while (!q.empty()) {
            Step step = q.front();
            q.pop();
            step.recalculate_weight();
            best = max(best, step);
            if (step.path.size() < 3) {
                auto [i, j] = *step.path.rbegin();
                for (pair<int, int> next_pos : field[i][j].neighbours()) {
                    if (find(step.path.begin(), step.path.end(), next_pos) != step.path.end()) {
                        continue;
                    }
                    if (!field[next_pos.first][next_pos.second].can_be_atacked()) {
                        continue;
                    }
                    if (field[next_pos.first][next_pos.second].value == identifier) {
                        continue;
                    }
                    q.push(step + next_pos);
                }
            }
        }
        return best.path;
    }
};

int32_t main() {
    cin >> n >> m >> k >> identifier;
    if (k > 2) {
        WEIGHTS::DIRECT_STEP = 0.15;
        WEIGHTS::DIAGONAL_STEP = 0.2;
        WEIGHTS::CAME_TO_ENEMY[1] = -0.1;
        WEIGHTS::CAME_TO_ENEMY[2] = -0.2;
        WEIGHTS::CAME_TO_ENEMY[3] = -0.4;
        WEIGHTS::CAME_TO_ENEMY[4] = 0.23;
        WEIGHTS::ATACKED_BY_1 = -0.1;
        for (int i = 5; i < 500; i++) { WEIGHTS::CAME_TO_ENEMY[i] = WEIGHTS::CAME_TO_ENEMY[i - 1] + 0.01; }
    } else {
        for (int i = 4; i < 500; i++) { WEIGHTS::CAME_TO_ENEMY[i] = WEIGHTS::CAME_TO_ENEMY[i - 1] - 0.001; }
    }
    AI ai;
    ai.read_field();
    string state = "r";
    while (state == "r") {
        vector<pair<int, vector<pair<int, int>>>> other_moves(k);
        ai.process();
        vector<pair<int, int>> step = ai.make_step();

        cout << identifier << " " << step.size() << " ";// endl;
        other_moves[0].first = identifier;
        for (pair<int, int> &p : step) {
            cout << p.first + 1 << " " << p.second + 1 << " ";
            other_moves[0].second.push_back({p.first, p.second});
        }
        cout << endl;


        cin >> state;
        if (state != "r") break;

        for (int i = 1; i < k; i++) {
            cin >> other_moves[i].first;
            int made_moves;
            cin >> made_moves;
            while (made_moves--) {
                int x, y;
                cin >> x >> y;
                other_moves[i].second.push_back({x - 1, y - 1});
            }
        }
        ai.update_field(other_moves);
    }
    return 0;
}