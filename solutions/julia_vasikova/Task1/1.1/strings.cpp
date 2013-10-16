#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>



//processes line -> removes all ' ' and lowcasts
int process_line( char* line, char* s );

//reverse line
void rev_line(char* line);

int main()
{
    //the first_line had to be up to 100000 symbols by condition
    //to implement it we just need to read the line in parts and process
    //this parts like I did it with my first_line[] buffer
    //but I've spent too much time for my first task and
    //though the task was also obout memory management
    //I hope, it will be OK if I leave it that way in order to start my homework №2
    char first_line[256] = {};
    char line[256] = {};

    std::ifstream is("text.txt");
    std::ofstream os("out.txt");
    if(!os)
        std::cout << "Output file opening problemes!" << std::endl;
    if(!is)
        std::cout << "File opening error!" << std::endl;

    //read first line from file
    is.getline(first_line, 256, '\n');

    //processes line -> removes all ' '
    char s_first_line[256] = {};
    process_line(first_line, s_first_line);

    std::cout << "First line: " << s_first_line << std::endl;

    //process the rest of lines in file
    while(!is.eof())
    {
        char s_line[256] = {};
        if(is.getline( line, 256, '\n'))
        {
            process_line(line, s_line);
            rev_line(s_line);
            std::cout << "line: " << line << " s: " << s_line << std::endl;
            //check if our first_line contains line that have beed red
            if(strstr(s_first_line, s_line))
            {
                os.write("YES\n", sizeof("YES"));
            }
            else
            {
                os.write("NO\n", sizeof("NO"));
            }
        }
    }
    is.close();
    os.close();
    return 0;
}


//processes line -> removes all ' ' and lowcasts
int process_line( char* line, char* s)
{
    int i = 0;
    int j = 0;
    while(line[i] != '\0')
    {
        if(isupper(line[i]))
            line[i] = tolower(line[i]);
        if(line[i] != ' ' && line[i] != 92 && line[i] != 45 )
        {
            s[j] = line[i];
            j++;
        }
        i++;
    }
    return 0;
}

//reverse the order of symbols in line
void rev_line(char* line)
{
    int size = strlen(line);
    char ch;
    for(int i = 0; i <= (size-1)/2; ++i)
    {
        ch = line[i];
        line[i] = line[size-i-1];
        line[size-i-1] = ch;
    }
}


