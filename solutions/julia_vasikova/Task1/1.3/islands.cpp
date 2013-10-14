#include <iostream>

//some temporary things to task the logic of the program 
//-> will be removed in final version
const int g_rows = 6;
const int g_columns = 6;

char g_ocean[g_rows][g_columns] =
{
  {'~','~','o','~','~','o'},
  {'~','o','o','o','~','o'},
  {'~','~','o','o','~','o'},
  {'~','~','o','~','o','~'},
  {'~','~','~','~','o','o'},
  {'~','~','o','~','~','o'}
};

//I'm not a fan of recurtions, but as I can see it's the best way to solve this task
int check_island(int i, int j)
{
    g_ocean[i][j] = '1';
    if(g_ocean[i+1][j] == 111)
        check_island(i+1, j);
    if(g_ocean[i-1][j] == 111)
        check_island(i-1, j);
    if(g_ocean[i][j+1] == 111)
        check_island(i, j+1);
    if(g_ocean[i][j-1] == 111)
        check_island(i, j-1);
    else
        return 0;
}

int main()
{
    int n_islands = 0;
    int check = 0;

    //process our matrix and find out all the islands
    for(int i = 0; i < g_rows; ++i)
        for(int j = 0; j < g_columns; ++j)
        {
            if(g_ocean[i][j] == 111)
            {
                std::cout << "i: " << i << " j: " << j << " ch: " << g_ocean[i][j] << std::endl;
                //find out wether this point is a part of island
                check_island( i, j);
                //cout the number of islands
                n_islands++;
            }
        }
    std::cout << "number of islands: " << n_islands << std::endl;

    //output the final map to screen
    for( int i = 0; i < g_rows; ++i)
    {
        for(int j = 0; j < g_columns; ++j)
            std::cout << " " << (char)g_ocean[i][j];
        std::cout << std::endl;
    }

    return 0;
}

