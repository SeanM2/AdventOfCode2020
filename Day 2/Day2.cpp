#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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


int ReadFileInformation()
{
    ifstream myfile;
    myfile.open("input.txt");

    int validPasswordCount = 0;

    if (myfile.is_open())
    {
        std::string line;
        std::vector<int> outputArray;

        while(std::getline(myfile,line))
        {
            int a , b;
            string key, password;
            cout << line << "\n";
            line.replace(line.find("-"), 1 ," ");
            line.replace(line.find(":"), 1 ," ");
            istringstream iss(line);            
            
            iss >> a >> b >> key >> password;
            
            cout << a << ", " << b << ", " << key << ", " << password << "\n";

            if(EvaluatePassword(a, b, key, password))
            {
                validPasswordCount++;
            }
        }        

        myfile.close();
    }
    return validPasswordCount;
}

int main()
{
    
    int validPasswordCount = ReadFileInformation();

    cout << "Number of Valid Passwords = " << validPasswordCount << "\n";

    return 0;
}