#include <iostream>

using namespace std;

int main()
{

    string str = "fffffffffff";

    int value = str.find_first_not_of("0123456789abcdefABCDEF");
    cout << value << "\n";

    return 0;
}