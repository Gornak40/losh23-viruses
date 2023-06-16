#pragma GCC optimize("O3,unroll-loops")

#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>


bool is_good(int i, int j, int n, int m)
{
    return 0 <= i && i < n && 0 <= j && j < m;
}

struct Random
{
    std::mt19937_64 rnd;
    Random(): rnd(5720861329ll) {}

    long long get(long long l, long long r)
    {
        std::uniform_int_distribution<long long> gen(l, r);
        return gen(rnd);
    }
};

Random random_gen;

struct Genome
{
    // type = j, positon = i: j * 49 + i
    std::vector<double> genes;
    static const int MUL = 49;
    static const int NO_ACTION = 294;
    static const int SIZE = 295; 

    Genome(std::vector<double> genes): genes(genes) {}
    Genome(): genes(SIZE) {}

    void generate()
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (i == NO_ACTION)
                genes[i] = random_gen.get(0, 8);
            else
                genes[i] = random_gen.get(0, 10);
        }
    }

    Genome mutate()
    {
        Genome new_genome(genes);
        for (int i = 0; i < SIZE; i++)
        {
            int t = random_gen.get(1, 5);
            if (t == 1)
            {
                long long max_minus = new_genome.genes[i];
                int x = random_gen.get(-std::min(164ll, max_minus * 100), 164);
                if (i == NO_ACTION)
                    x = random_gen.get(-std::min(200ll, max_minus * 100), 200);
                new_genome.genes[i] += double(x) / 100;
            }
        }

        return new_genome;
    }

    Genome cross(Genome &other)
    {
        Genome new_genome(genes);
        for (int i = 0; i < SIZE; i++)
        {
            int t = random_gen.get(1, 2);
            if (t == 2)
                new_genome.genes[i] = other.genes[i];
        }
        return new_genome;
    }
};

struct Bot
{
    Genome genome;
    int num;
    Bot(Genome genome, int num): genome(genome), num(num) {}
    Bot(int num): num(num) {}

    void dfs(int i, int j, std::vector<std::vector<int>> &field, std::vector<std::vector<bool>> &used)
    {
        if (field[i][j] < 0 && abs(field[i][j]) != num)
            return;

        int n = field.size();
        int m = field[0].size();

        used[i][j] = true;
        if (field[i][j] == 0 || (field[i][j] > 0 && field[i][j] != num))
            return;

        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                if (is_good(i + x, j + y, n, m) && !used[i + x][j + y])
                    dfs(i + x, j + y, field, used);
            }
        }
    }

    double evaluate(int i, int j, std::vector<std::vector<int>> &field)
    {
        int n = field.size();
        int m = field[0].size();

        double sum = 0;
        for (int x = -3; x <= 3; x++)
        {
            for (int y = -3; y <= 3; y++)
            {
                int t = 0;
                if (is_good(i + x, j + y, n, m) && field[i + x][j + y] != -100)
                {
                    if (field[i + x][j + y] == 0) t = 1;
                    else if (field[i + x][j + y] == num) t = 2;
                    else if (field[i + x][j + y] == -num) t = 3;
                    else if (field[i + x][j + y] > 0) t = 4;
                    else t = 5;
                }

                int idx = (x + 3) * 7 + y + 3;
                sum += genome.genes[genome.MUL * t + idx];
            }
        }

        return sum;
    }

    std::pair<int, int> act(std::vector<std::vector<int>> &field, int move_num)
    {
        int n = field.size();
        int m = field[0].size();

        std::vector<std::vector<bool>> used(n, std::vector<bool>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (field[i][j] == num && !used[i][j])
                    dfs(i, j, field, used);
            }
        }

        std::vector<std::pair<int, int>> moves;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if ((field[i][j] == 0 || (field[i][j] > 0 && field[i][j] != num)) && used[i][j])
                    moves.emplace_back(i, j);
            }
        }

        std::vector<std::pair<double, int>> options;
        for (int q = 0; q < moves.size(); q++)
        {
            auto [i, j] = moves[q];
            double sum = evaluate(i, j, field);
            options.emplace_back(sum, q);
        }
        std::sort(options.rbegin(), options.rend());

        std::vector<std::pair<double, int>> variants;
        for (int q = 0; q < moves.size(); q++)
        {
            auto [pos_i, pos_j] = moves[q];
            double s = evaluate(pos_i, pos_j, field);

            std::fill(used.begin(), used.end(), std::vector<bool>(m, false));
            dfs(pos_i, pos_j, field, used);

            double max_evaluation = options[0].first;
            if (q == 0 && options.size() >= 2)
                max_evaluation = options[1].first;
            else if (q == 0)
                max_evaluation = 0;
            
            if (move_num != 2)
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        if ((field[i][j] == 0 || (field[i][j] > 0 && field[i][j] != num)) && used[i][j])
                        {
                            double sum = evaluate(i, j, field);
                            max_evaluation = std::max(max_evaluation, sum);
                        }
                    }
                }
            }
            else
            {
                max_evaluation = 0;
            }

            variants.emplace_back(s + max_evaluation, q);
        }

        if (move_num != 0)
            variants.emplace_back(genome.genes[genome.NO_ACTION], -1);

        if (variants.empty())
            return {-1, -1};

        int idx = std::max_element(variants.begin(), variants.end())->second;
        if (idx == -1)
            return {-1, -1};

        auto [i, j] = moves[idx];
        if (field[i][j] > 0)
            field[i][j] = -num;
        else
            field[i][j] = num;
        return {i, j};
    }

    std::vector<std::pair<int, int>> move(std::vector<std::vector<int>> &field)
    {
        std::vector<std::pair<int, int>> ans;
        for (int i = 0; i < 3; i++)
        {
            auto x = act(field, i);
            if (x.first != -1)
                ans.push_back(x);
        }
        return ans;
    }
};

void play(int n, int m, int num, int cnt)
{
    Genome genome;
    genome.genes = {64.72, 17.57, 17.73, 16.69, 33.54, 20.57, 20.14, 35.96, 21.27, 12.66, 1.86, 31.25, 35.44, 35.03, 5.1, 3.08, 32.11, 35.66, 90.95, 24.34, 10.87, 26.63, 49.37, 74.8, 21.87, 28.87, 48.95, 25.87, 7.13, 7.01, 13.76, 27.17, 1.93, 29.03, 17.41, 8.86, 7.06, 19.8, 44.52, 56.8, 51.93, 33.14, 15.56, 73.03, 31.4, 13.34, 42.23, 10.34, 28.17, 23.3, 38.66, 22.8, 39.22, 13.56, 15.12, 6.19, 39.22, 3.32, 52.67, 38.21, 5.58, 19.55, 8.99, 47.61, 28.52, 2.8, 6.49, 5.19, 10.11, 2.57, 8.5, 13.53, 45.95, 1.46, 54.52, 57.11, 29.05, 35.77, 10.48, 34.43, 29.63, 38.73, 28.25, 7.15, 22.53, 18.37, 24.34, 21.12, 2.86, 12.9, 28.46, 5.93, 11.91, 16.13, 5.43, 22.69, 14.29, 18.96, 46.77, 29.88, 21.41, 20.68, 25.3, 48.21, 65, 6.19, 46.17, 20.59, 101.22, 4.89, 13.53, 18.45, 33.66, 30.61, 50.19, 28.7, 7.87, 62.12, 29.91, 13.13, 30.98, 0.6, 14.2, 17.39, 31.34, 16.97, 13.74, 6.32, 18.94, 15.1, 17.53, 10.83, 20.08, 75.34, 36.93, 23.43, 8.87, 13.81, 28.97, 28.41, 3.32, 26.21, 30.64, 28.56, 28.87, 41.51, 43.67, 39.25, 8.87, 25.6, 42.47, 8.26, 32.51, 52.46, 72.03, 11.88, 19.25, 30.51, 34.55, 22.37, 31.91, 68.55, 4.44, 2.74, 52.31, 45.57, 43.63, 8.73, 22.75, 2.38, 77.25, 28.39, 7.22, 16.86, 7.54, 45.79, 17.29, 21.92, 27.06, 49.62, 39.27, 37.39, 42.54, 80.85, 14.91, 26.84, 5.64, 7.23, 17.82, 29.11, 7.57, 52.99, 2.5, 1.64, 11.1, 9.42, 36.41, 31.56, 55.18, 16.29, 3.57, 59.73, 47.23, 3.27, 16.79, 10.86, 40.16, 25.85, 32.69, 6.09, 66.45, 18.88, 13.96, 43.79, 33.02, 13.97, 16.17, 4.69, 47.39, 21.27, 153.05, 50.18, 5.18, 49.85, 20.69, 5.37, 2.32, 49.36, 25.27, 0.75, 2.3, 46.72, 6.24, 90.75, 48.04, 33.51, 3.37, 44.27, 7.16, 60.05, 64.49, 17.87, 32.72, 24.05, 18.95, 44.61, 75.08, 15, 30.82, 3.95, 54.84, 9.45, 54.92, 12.66, 47.74, 14.92, 27.81, 71.74, 5.24, 6.05, 9.03, 7.84, 22.22, 25.41, 32.6, 46.82, 23.75, 50.68, 37.8, 30.16, 58.55, 31.3, 19.12, 0.8, 27.03, 65.59, 34.3, 54.11, 26.72, 24.73, 50.07, 55.37, 18.01, 59.03, 14.64, 5.35, 20, 14.25, 18.53, 2.32, 15.76, 51.31, 15.28, 10.15, 11.16};
    Bot bot(genome, num);

    std::vector<std::vector<int>> field(n, std::vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            std::cin >> field[i][j];

    while (true)
    {
        std::vector<std::pair<int, int>> moves = bot.move(field);
        std::cout << num << ' ' << moves.size() << ' ';
        for (auto [i, j] : moves)
            std::cout << i + 1 << ' ' << j + 1 << ' ';
        std::cout << std::endl;
        char status;
        std::cin >> status;
        if (status == 'o')
            return;
        for (int i = 0; i < cnt - 1; i++)
        {
            int g, a;
            std::cin >> g >> a;
            for (int j = 0; j < a; j++)
            {
                int pos_i, pos_j;
                std::cin >> pos_i >> pos_j;
                --pos_i;
                --pos_j;

                if (field[pos_i][pos_j] == 0)
                    field[pos_i][pos_j] = g;
                else
                    field[pos_i][pos_j] = -g;
            }
        }
    }
}

int main()
{
    // std::ifstream in("genome_new_1.txt");
    // std::string line;

    // std::vector<Genome> genomes(8);
    // bool start = false;
    // while (std::getline(in, line))
    // {
    //     start = line == ("Generation: " + std::to_string(17000));
    //     if (start)
    //     {
    //         for (int i = 0; i < 8; i++)
    //             for (int j = 0; j < genomes[i].SIZE; j++)
    //                 in >> genomes[i].genes[j];
    //         break;
    //     }
    // }
    // in.close();

    // std::cout << '{';
    // for (double x : genomes[7].genes)
    //     std::cout << x << ", ";
    // std::cout << '}';
    
    int n, m, k;
    std::cin >> n >> m >> k;
    int g;
    std::cin >> g;

    play(n, m, g, k);
    return 0;
}
