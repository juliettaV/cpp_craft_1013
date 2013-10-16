#include <iostream>
#include <fstream>
#include <string.h>


//I'm not a fan of recurtions, but as I can see it's the best way to solve this task
int check_island(int i, int j, char** ocean, int columns, int rows)
{
    ocean[i][j] = '1';
    if( i < rows-1 && ocean[i+1][j] == 111)
        check_island(i+1, j, ocean, columns, rows);
    if( i > 0 && ocean[i-1][j] == 111)
        check_island(i-1, j, ocean, columns, rows);
    if( j < columns-1 && ocean[i][j+1] == 111)
        check_island(i, j+1, ocean, columns, rows);
    if( j > 0 && ocean[i][j-1] == 111)
        check_island(i, j-1, ocean, columns, rows);
    else
        return 0;
}

int read_data_from_file( int* column, int* row, char**& ocean)
{
    std::ifstream is("text.txt");
    if(!is)
        std::cout << "File text.txt opening problemes!" << std::endl;

    char ch;
    char line[100];
    while(is.getline(line, 100, '\n'))
    {
        if(!*column)
            *column = strlen(line);
        ++(*row);
    }

    is.clear();
    is.seekg(0);

    ocean = new char*[*row];
    for(int i = 0; i < *row; ++i)
    {
        ocean[i] = new char[*column];
        for(int j = 0; j < *column; ++j)
            is >> ocean[i][j];
    }
    is.close();

    return 0 ;
}

int main()
{
    int n_islands = 0;
    int check = 0;
    int rows = 0;
    int columns = 0;

    char** ocean;

    read_data_from_file(&rows, &columns, ocean);

    //process our matrix and find out all the islands
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
        {
            if(ocean[i][j] == 111)
            {
                //find out wether this point is a part of island
                check_island( i, j, ocean, columns, rows);
                //count the number of islands
                n_islands++;
            }
        }

    //output the number of islands to file
    std::ofstream os("out.txt");
    os << "number of islands: " << n_islands << '\n';
    os.close();

    //delete our dinamic massive
    for(int i = 0; i < rows; i++)
       delete [] ocean[i];
    delete [] ocean;

    return 0;
}

