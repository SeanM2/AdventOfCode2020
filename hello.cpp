#include <iostream>

using namespace std;

int main()
{
    string hairColour = "#7d3b0c";


    if (hairColour[0] == '#' && hairColour.find_first_not_of("0123456789abcdefABCDEF",1) == string::npos)
    {
        cout << "true" << "\n";
    }
    else
    {
        cout << "false" << "\n";
    }

    return 0;
}