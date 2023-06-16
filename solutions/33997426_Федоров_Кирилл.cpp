#include <iostream>
#include <cstdio>

using namespace std;

int N, M, K, player_id, player_jury;
const int Max = 303;
const int WALL = -100;
int field[Max][Max];

int number_crosses;
int qx[Max * Max];
int qy[Max * Max];
int attack_moves;
int attack_moves_x[5], attack_moves_y[5];
int reproduction_moves;
int reprod_moves_x[5], reprod_moves_y[5];
bool visited[Max][Max];

bool check_move_existence(int player)
{
    // multi-start bfs (start from all crosses)
    number_crosses = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            visited[i][j] = false;
            if (field[i][j] == player)
            {
                visited[i][j] = true;
                number_crosses += 1;
                qx[number_crosses] = i;
                qy[number_crosses] = j;
            }
        }
    }
    int visited_cells = number_crosses;
    int ind = 1;
    attack_moves = 0;
    reproduction_moves = 0;
    while (ind <= visited_cells)
    {
        int x = qx[ind];
        int y = qy[ind];
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int new_x = x + i;
                int new_y = y + j;
                if (new_x < 1 || new_x > N || new_y < 1 || new_y > M)
                {
                    continue;
                }
                if (visited[new_x][new_y] || field[new_x][new_y] == WALL)
                {
                    continue;
                }
                visited[new_x][new_y] = true;
                // our fortress
                if (field[new_x][new_y] == -player)
                {
                    visited_cells += 1;
                    qx[visited_cells] = new_x;
                    qy[visited_cells] = new_y;
                    continue;
                }
                // opponent's cross
                if (field[new_x][new_y] > 0)
                {
                    if (attack_moves < 3)
                    {
                        attack_moves += 1;
                        attack_moves_x[attack_moves] = new_x;
                        attack_moves_y[attack_moves] = new_y;
                    }
                }
                // empty cell
                if (field[new_x][new_y] == 0)
                {
                    if (reproduction_moves < 3)
                    {
                        reproduction_moves += 1;
                        reprod_moves_x[reproduction_moves] = new_x;
                        reprod_moves_y[reproduction_moves] = new_y;
                    }
                }
            }
        }
        ind += 1;
        if (attack_moves == 3 && reproduction_moves == 3)
        {
            return true;
        }
    }
    if (attack_moves + reproduction_moves == 0)
    {
        return false;
    }
    return true;
}

int count_moves;
int moves_x[9], moves_y[9], new_values[9];

void get_move()
{
    // must run STRICTLY AFTER starting the function
    // check_move_existence(player_id)
    count_moves = 0;
    for (int i = 1; i <= attack_moves; i++)
    {
        count_moves += 1;
        moves_x[count_moves] = attack_moves_x[i];
        moves_y[count_moves] = attack_moves_y[i];
        new_values[count_moves] = -player_id;
    }
    for (int i = 1; i <= reproduction_moves; i++)
    {
        count_moves += 1;
        moves_x[count_moves] = reprod_moves_x[i];
        moves_y[count_moves] = reprod_moves_y[i];
        new_values[count_moves] = player_id;
    }
    count_moves = min(3, count_moves);
    for (int i = 1; i <= count_moves; i++)
    {
        int x = moves_x[i];
        int y = moves_y[i];
        field[x][y] = new_values[i];
    }
    return;
}

void read_field()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            scanf(" %d", &field[i][j]);
        }
    }
}

int main()
{
    scanf(" %d %d %d", &N, &M, &K);
    scanf(" %d", &player_id);
    int player_jury = 3 - player_id;
    read_field();
    while (true)
    {
        check_move_existence(player_id);
        get_move();
        printf("%d %d ", player_id, count_moves);
        for (int i = 1; i <= count_moves; i++)
        {
            printf("%d %d ", moves_x[i], moves_y[i]);
        }
        printf("\n");
        fflush(stdout);
        char status;
        scanf(" %c", &status);
        if (status == 'o')
        {
            return 0;
        }
        int id_jury, num;
        scanf(" %d %d", &id_jury, &num);
        for (int i = 1; i <= num; i++)
        {
            int xj, yj;
            scanf(" %d %d", &xj, &yj);
            if (field[xj][yj] == 0)
            {
                field[xj][yj] = player_jury;
            }
            else
            {
                field[xj][yj] = -player_jury;
            }
        }
    }
}