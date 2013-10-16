#include <iostream>
#include <fstream>
#include <cmath>
#include <set>


//function of comparison for set
bool compare(float a, float b)
{
    return (std::fabs(a-b) > 0.0001f) && (a < b);
};

int main()
{
    size_t num_of_rows = 0;
    float f;

    std::ifstream is("text.txt");
    std::ofstream os("out.txt");

    if(!os)
        std::cout << "Output file opening problemes!" << std::endl;
    if(!is)
        std::cout << "File text.txt opening problemes!" << std::endl;

    is >> num_of_rows;

    //a set of codes
    bool(*p_compare)(float, float) = compare;
    std::set<float, bool(*)(float, float)> codes(p_compare);
    for(int i=0; i < num_of_rows; ++i)
    {
        is >> f;
        codes.insert(f);

    }

    //read the rest elements from text.txt one by one
    //try to find them in codes and write down the result to out.txt
    while(true)
    {
        is >> f;
        if(is.eof())
            break;

        if(codes.find(f) != codes.end())
            os << f << " YES\n";
        else
            os << f << " NO\n";
    }


    is.close();
    os.close();

    return 0;
}
