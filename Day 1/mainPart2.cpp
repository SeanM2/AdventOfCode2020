#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> ReadFileInformation()
{
    ifstream myfile;
    myfile.open("input.txt");

    if (myfile.is_open())
    {
        std::string line;
        std::vector<int> outputArray;

        while(std::getline(myfile,line))
        {
            int a;            
            a = std::atoi(line.c_str());
            outputArray.push_back(a);
            cout << outputArray.back() << "\n";
        }        

        myfile.close();

        return outputArray;
    }

    return vector<int>(0);
}

int FindTheCorrectEntries(vector<int> _inputData)
{
    for (int i = 0; i < _inputData.size(); i++)
    {
        for (int j = 0; j < _inputData.size(); j++)
        {
            for (int k = 0; k < _inputData.size(); k++)
            {
                int _ans = _inputData[i] + _inputData[j] + _inputData[k];
                if (_ans == 2020)
                {
                    cout << " Answer Found at: " << i << ", " << j << ", " << k << "\n";
                    
                    return _inputData[i] * _inputData[j] * _inputData[k];
                }  
            }         
        }        
    }

    return 0;
}

int main()
{
    vector<int> inputData = ReadFileInformation();
    cout << "Input Data Length: " << inputData.size() << "\n";
    
    cout << "First Value: " << inputData[0] << "\n";

    int answer = FindTheCorrectEntries(inputData);
    
    if (answer != 0)
    {
        std::cout << "The Result is: " << answer << "\n";
    }
    else
    {
        cout << "No Matches Found :(" << "\n";
    }

    return 0;
}