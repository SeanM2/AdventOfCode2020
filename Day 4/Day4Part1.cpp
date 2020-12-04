#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Passport

{
private:
    int byr;
    int iyr;
    int eyr;
    int hgt;
    string ecl;
    string hcl;
    string pid;
    int cid;

    bool validPassport;

    
public:
    Passport(int, int, int, int, int, string, string, string);

    int getByr() { return byr; }

    int getIyr() { return iyr; }

    int getEyr() { return eyr; }

    int getHgt() { return hgt; }
    
    int getCid() { return cid; }

    string getPid() { return pid; }

    string getEcl() { return ecl; }

    string getHcl() { return hcl; }

    bool getPassportValid() { return validPassport; }

    int defaultValue = 0;
    string defaultValueStr = "";
};

Passport::Passport(int _byr, int _iyr, int _eyr, int _hgt, int _cid, string _pid, string _ecl, string _hcl)
{
    validPassport = true;

    if (_byr == defaultValue)
    {
        byr = defaultValue;
        cout << "Passport Invalid Due to " << "Birth Year" << "\n";
        validPassport = false;
    }
    else
    {
        byr = _byr;
    }
    
    if (_iyr == defaultValue)
    {
        iyr = defaultValue;
        cout << "Passport Invalid Due to " << "Issue Year" << "\n";
        validPassport = false;
    }
    else
    {
        iyr = _iyr;
    }

    if (_eyr == defaultValue)
    {
        eyr = defaultValue;
        cout << "Passport Invalid Due to " << "Expiry Year" << "\n";
        validPassport = false;
    }
    else
    {
        eyr = _eyr;
    }

    if (_hgt == defaultValue)
    {
        hgt = defaultValue;
        cout << "Passport Invalid Due to " << "Height" << "\n";
        validPassport = false;
    }
    else
    {
        hgt = _hgt;
    }

    if (_pid == defaultValueStr)
    {
        pid = defaultValueStr;
        cout << "Passport Invalid Due to " << "Passport ID" << "\n";
        validPassport = false;
    }
    else
    {
        pid = _pid;
    }

    if (_cid == defaultValue)
    {
        cid = defaultValue;
    }
    else
    {
        cid = _cid;
    }

    if (_ecl == defaultValueStr)
    {
        ecl = defaultValueStr;        
        cout << "Passport Invalid Due to " << "Eye Colour" << "\n";
        validPassport = false;
    }
    else
    {
        ecl = _ecl;
    }

    if (_hcl == defaultValueStr)
    {
        hcl = defaultValueStr;
        cout << "Passport Invalid Due to " << "Hair Colour" << "\n";
        validPassport = false;
    }
    else
    {
        hcl = _hcl;
    }

}


vector<vector<string>> ReadFileInformation()
{
    ifstream myfile;
    myfile.open("input.txt");
    vector<vector<string>> outputArray;

    int validPasswordCount = 0;

    if (myfile.is_open())
    {

        cout << "File Open" << "\n";

        std::string line;
        int numberOfEntries = 0;
        vector<string> inputArray;
        bool newEntry;

        while(std::getline(myfile,line))
        {
            //cout << line << "\n";

            istringstream iss(line);
            string word;            
            iss >> word;
            
            //cout << word << "\n";
            if (word == "")
            {
                newEntry = true;
                
                outputArray.push_back(inputArray);

                inputArray.clear();
                newEntry = false;
                numberOfEntries++;
                
                //cout << "New Entry Starting" << "\n";
            }
            else
            {
                inputArray.push_back(word);
                while (iss >> word)
                {
                    //cout << word << "\n";

                    inputArray.push_back(word);
                }                
            }
        }
        outputArray.push_back(inputArray);

        inputArray.clear();
        newEntry = false;
        numberOfEntries++;
                
                

        cout << "Number of Entries = " << numberOfEntries << "\n";    

        myfile.close();
    }
    return outputArray;
}

vector<Passport> ParseRawStringInput(vector<vector<string>> _rawStringInputArray)
{
    

    vector<Passport> outputArray;

    for (vector<string> i : _rawStringInputArray)
    {
        int _byr = 0, _iyr = 0, _eyr = 0, _hgt = 0, _cid = 0; 
        string _ecl = "", _hcl = "", _pid = "";

        for (string j : i)
        {
            string key, value;

            j.replace(3,1," ");
            
            istringstream iss(j);

            iss >> key >> value;
            cout << key << ": " << value << "  ";

            if (key == "byr")
            {                
                _byr = stoi(value);
            }
            else if (key == "eyr")
            {
                _eyr = stoi(value);
            }
            else if (key == "iyr")
            {
                _iyr = stoi(value);
            }
            else if (key == "hgt")
            {
                // int unitLocation = value.find("in") + value.find("cm");

                // if (unitLocation != 0)
                // {
                //     value.erase(unitLocation, unitLocation + 1);
                // }
                
                _hgt = stoi(value);
            }
            else if (key == "pid")
            {
                _pid = value;
            }
            else if (key == "cid")
            {
                _cid = stoi(value);
            }
            else if (key == "ecl")
            {
                _ecl = value;
            }            
            else if (key == "hcl")
            {
                _hcl = value;
            }                     
                        
        }
        cout << "\n";

        Passport tmpPassport = Passport(_byr, _iyr, _eyr, _hgt, _cid, _pid, _ecl, _hcl);
        //cout << "CID = " << tmpPassport.getCid() << "\n"; 
        outputArray.push_back(tmpPassport);        
    }
    return  outputArray;
}

int CountValidPassports(vector<Passport> passportArray)
{
    int validPassportCount = 0;
    int invalidPassportCount = 0;
    int idx = 0;

    for (Passport i : passportArray)
    {
        if (i.getPassportValid())
        {
            validPassportCount++;
        }  
        else
        {
            invalidPassportCount++;
            cout << "The following index is invalid: " << idx << "\n";
        }

        idx++;
    }
    
    cout << "Number of Invalid Passports: " << invalidPassportCount << "\n";
    return validPassportCount;
    
}

int main()
{
    vector<vector<string>> rawStringInput = ReadFileInformation();

    vector<Passport> passportArray = ParseRawStringInput(rawStringInput);

    int numberOfValidPassports = CountValidPassports(passportArray);

    cout << "Number of Valid Passports = " << numberOfValidPassports << "\n";

    return 0;
}