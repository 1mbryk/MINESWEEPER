#include "mine_sweeper.h"

int main()
{
    int size = 5;
    Inform **map = new Inform *[size];
    for (int i = 0; i < size; i++)
    {
        map[i] = new Inform[size];
    }
    bool **chck = new bool *[size]; 
    for (int i = 0; i < size; i++)
    {
        chck[i] = new bool[size];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            chck[i][j] = false;
        }
    }

    init_ground(map, size);

    do
    {
        outpt(map, size);
        chng_sqr(map, size, chck);
        if (win_check(map, size))
        {
            cout << GREEN << "CONGRATULATIONS!!! YOU WIN!!!!";
            return 0;
        }
    } while (check(map, size));
    final_outpt(map, size);

    for (int i = 0; i < size; i++)
    {
        delete[] map[i];
    }
    delete[] map;
    return 0;
}
