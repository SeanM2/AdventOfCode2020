#include <iostream>

using namespace std;

void DoTheThing(int i, int j)
{
    i = i + j;
}

int main()
{
    int i = 5;
    int j = 10;

    DoTheThing(i, j);

    cout << i << ", " << j << "\n";

    return 0;
}