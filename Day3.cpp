#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


/* class Password
{
private:
    int lowerLim;
    int upperLim;
    string keyValue;
    string password;
public:
    Password(int , int , string , string);

    int GetLowerLim(){ return lowerLim; }
    int GetUpperLim(){ return upperLim; }
    string GetKeyValue(){ return keyValue; }
    string GetPassword(){ return password; }
};

Password::Password(int _lowerLim, int _upperLim, string _keyValue, string _password)
{
    lowerLim = _lowerLim;
    upperLim = _upperLim;
    keyValue = _keyValue;
    password = _password;
} */

bool EvaluatePassword(int _lowerLim, int _upperLim, string _keyValue, string _password)
{
    int idx = 0;
    int pos = 0;
    int keyCount = 0;

    while (idx < _password.size())
    {
        pos = _password.find(_keyValue,idx) + 1;

        if (pos == 0)
        {
            break;
        }
        
        idx = pos; 
        keyCount++;
    }

    cout << keyCount << "\n";
    if (keyCount >= _lowerLim && keyCount <= _upperLim)
    {
        cout << "Valid" "\n";
        return true;
    }
    else
    {
        cout << "Invalid" "\n";
        return false;
    }
}


int ReadFileInformation(int horizontalValue, int verticalValue)
{
    ifstream myfile;
    ofstream outputFile;
    myfile.open("input.txt");
    outputFile.open ("output.txt");

    int numberOfTrees = 0;

    if (myfile.is_open())
    {
        std::string line;
        std::string lineOrig;
        std::vector<int> outputArray;
        int currentIdx = 0;
        int lineNumber = 0;
        int extraColumn = 0;

        while(std::getline(myfile,line))
        {
            float remainderVal = remainder(lineNumber, verticalValue);
            cout << "Remainder Value: " << remainderVal << "\n";

            if (remainderVal == 0)
            {
                cout << line << "\n";
                cout << "Index Value: " << currentIdx << "\n";
                lineOrig = line;
                char treeVal = '#';

                if (line[currentIdx] == treeVal)
                {
                    cout << line[currentIdx] << " is equal to " << &treeVal << " Lookout for the tree!!" << "\n";
                    line.replace(currentIdx,1,"X");
                    numberOfTrees++;
                }
                else
                    {
                        cout << line[currentIdx] << " is not equal to " << &treeVal << "\n";
                        line.replace(currentIdx,1,"O"); 
                    }

                    

                for (size_t i = 0; i < extraColumn; i++)
                {
                    line = lineOrig + line;
                }
                outputFile << line << "\n";

                lineNumber++;

                currentIdx = currentIdx + horizontalValue;

                if (currentIdx >= lineOrig.length())
                {
                    currentIdx = currentIdx - (lineOrig.length());
                    extraColumn++;                
                }
                cout << "New Index Value: " << currentIdx << " --- Line Length: " << lineOrig.length() << "\n";
            }
            else
            {
                for (size_t i = 0; i < extraColumn; i++)
                {
                    line = lineOrig + line;
                }
                outputFile << line << "\n";
                lineNumber++;
            }
                     
        }        

        myfile.close();
        outputFile.close();
    }
    return numberOfTrees;
}

int main()
{
    int horizontalElement, verticalElement;

    cout << "Please Enter the Horizontal Value: ";
    cin >> horizontalElement;

    cout << "Please Enter the Vertical Value: ";
    cin >> verticalElement;


    int numberOfTrees = ReadFileInformation(horizontalElement, verticalElement);

    cout << "Number of Trees Encountered = " << numberOfTrees << "\n";

    return 0;
}