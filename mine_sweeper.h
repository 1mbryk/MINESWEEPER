#include <iostream>
#include <iomanip>
using namespace std;
#define BOMB '*'

#define BLUE "\e[34;49m"   // 1-blue
#define GREEN "\e[32;49m"  // 2-green
#define RED "\e[31;49m"    // 3-red
#define PURPLE "\e[35;49m" // 4-purple
#define WHITE "\e[37;49m"
#define YELLOW "\e[33;49m"
#define CYAN "\e[36;49m"
#define BOOM "\e[31;43m"

struct Inform
{
    char up_layer;
    char dwn_layer;
    int condtn;
};

char init_count(struct Inform **map, int size, int ind_i, int ind_j)
{
    char rtrn;
    int count = 0;

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if ((ind_i + i >= 0) && (ind_i + i <= size - 1) && (ind_j + j >= 0) && (ind_j + j <= size - 1))
            {
                if (map[ind_i + i][ind_j + j].dwn_layer == BOMB)
                {
                    count++;
                }
            }
        }
    }
    if (count != 0)
    {
        rtrn = char(count + '0');
    }
    else
    {
        rtrn = ' ';
    }
    return rtrn;
}

void init_ground(struct Inform **map, int size)
{
    srand(time(NULL));
    int rand_num;
    for (int i = 0; i < size; i++) // растаноўка бобмаў
    {
        for (int j = 0; j < size; j++)
        {
            rand_num = rand() % 4;
            if (rand_num)
            {
                map[i][j].condtn = true;
            }
            else
            {
                map[i][j].condtn = false;
            }
        }
    }
    for (int i = 0; i < size; i++) //запаўненне астатніх квадратаў
    {
        for (int j = 0; j < size; j++)
        {
            map[i][j].up_layer = '+';
            if (!map[i][j].condtn)
            {
                map[i][j].dwn_layer = BOMB;
            }
            else
            {
                map[i][j].dwn_layer = ' ';
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (map[i][j].dwn_layer != BOMB)
            {
                map[i][j].dwn_layer = init_count(map, size, i, j);
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (map[i][j].dwn_layer == ' ')
            {
                map[i][j].condtn = 1;
            }
            else if (map[i][j].dwn_layer >= '0' && map[i][j].dwn_layer <= '8')
            {
                map[i][j].condtn = 2;
            }
            else
            {
                map[i][j].condtn = 0;
            }
        }
    }
}

void outpt(struct Inform **map, int size) //звычайны вывад
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            switch (map[i][j].up_layer)
            {
            case '1':
            {
                cout << BLUE;
                break;
            }
            case '2':
            {
                cout << GREEN;
                break;
            }
            case '3':
            {
                cout << RED;
                break;
            }
            case '4':
            {
                cout << PURPLE;
                break;
            }
            case '*':
            {
                cout << BOOM;
                break;
            }
            case '^':
            {
                cout << CYAN;
                break;
            }
            default:
                cout << WHITE;
                break;
            }
            cout << map[i][j].up_layer << WHITE << ' ';
        }
        cout << '\n';
    }
}

void final_outpt(struct Inform **map, int size) // фінальны вывад, каб вывесці ўсе бомбы
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            switch (map[i][j].dwn_layer)
            {
            case '1':
            {
                cout << BLUE;
                break;
            }
            case '2':
            {
                cout << GREEN;
                break;
            }
            case '3':
            {
                cout << RED;
                break;
            }
            case '4':
            {
                cout << PURPLE;
                break;
            }
            case '*':
            {
                cout << BOOM;
                break;
            }
            case '^':
            {
                cout << CYAN;
                break;
            }
            default:
                cout << WHITE;
                break;
            }
            cout << map[i][j].dwn_layer << WHITE << ' ';
        }
        cout << '\n';
    }
}

void open_sqr(struct Inform **map, bool **check, int size, int ind_i, int ind_j) // у асноўным для адкрыцця пустых квадратаў
{
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if ((ind_i + i >= 0) && (ind_i + i <= size - 1) && (ind_j + j >= 0) && (ind_j + j <= size - 1))
            {
                if (!check[ind_i + i][ind_j + j])
                {
                    if (map[ind_i][ind_j].condtn == 1)
                    {
                        check[ind_i + i][ind_j + j] = true;
                        map[ind_i + i][ind_j + j].up_layer = map[ind_i + i][ind_j + j].dwn_layer;
                    }
                    else
                    {
                        check[ind_i][ind_j] = true;
                        map[ind_i][ind_j].up_layer = map[ind_i][ind_j].dwn_layer;
                        return;
                    }
                    if (map[ind_i + i][ind_j + j].condtn == 1)
                    {
                        open_sqr(map, check, size, ind_i + i, ind_j + j);
                    }
                }
            }
        }
    }
}

void chng_sqr(struct Inform **map, int size, bool **chck) //адкрыццё квадратаў
{
    int chs_y;
    int chs_x;
    int choice;
    cout << "Choose square:\n(exmpl: x y)\n";
    cin >> chs_x;
    cin >> chs_y;

    cout << "Choose options:\n"
         << "1. - Open\n"
         << "2. - Neutralize\n"
         << "3. - ?\n"
         << "4. - Cancel\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        open_sqr(map, chck, size, chs_y, chs_x);
        break;
    case 2:
        map[chs_y][chs_x].up_layer = '^';
        break;
    case 3:
        map[chs_y][chs_x].up_layer = '?';
        break;
    case 4:
        map[chs_y][chs_x].up_layer = '+';
        break;
    default:
        break;
    }
}

bool check(struct Inform **map, int size) // правярае ці адкрыта бомба
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (map[i][j].up_layer == BOMB)
            {
                return false;
            }
        }
    }
    return true;
}
bool win_check(struct Inform **map, int size) // як жа цяжка пісаць каменты піздзец
{                                             // правярае для брэйку з асноўнага цыклу
    bool win = false;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((map[i][j].up_layer == '^') && (map[i][j].dwn_layer == BOMB))
            {
                win = true;
            }
            else
            {
                win = false;
            }
        }
    }
    return win;
}