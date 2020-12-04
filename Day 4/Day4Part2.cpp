#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum UnitType {metric, imperial};

class Passport

{
private:
    int byr;
    int iyr;
    int eyr;
    int hgt;
    UnitType unitType;
    string ecl;
    string hcl;
    string pid;
    int cid;

    bool validPassport;

    
public:
    Passport(int, int, int, int, int, UnitType, string, string, string);

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

    int CountNumberOfDigits(int);
    bool DetermineIfValidEyeColour(string);
    bool DetermineIfValidHairColour(string);
    bool DetermineIfValidPassportNumber(string);

    
};

int Passport::CountNumberOfDigits(int inputNum)
{
    int count = 0;
    
    cout << inputNum << " has this many digits: ";

    while (inputNum > 0)
    {
        inputNum = inputNum / 10;
        count++;
    } 

    cout << count << "\n";  

    return count;
}

bool Passport::DetermineIfValidEyeColour(string eyeColour)
{    
    if (eyeColour == "amb" || eyeColour == "blu" || eyeColour == "brn" || eyeColour == "gry" || eyeColour == "grn" || eyeColour == "hzl" || eyeColour == "oth")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Passport::DetermineIfValidHairColour(string hairColour)
{
    if (hairColour[0] == '#' && hairColour.find_first_not_of("0123456789abcdefABCDEF",1) == string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }  
}

bool Passport::DetermineIfValidPassportNumber(string passportNumber)
{

    return passportNumber.find_first_not_of("0123456789") == string::npos && passportNumber.length() == 9;
}

Passport::Passport(int _byr, int _iyr, int _eyr, int _hgt, int _cid, UnitType _unitType, string _pid, string _ecl, string _hcl)
{
    validPassport = true;

    if (_byr == defaultValue || CountNumberOfDigits(_byr) != 4 || _byr < 1920 || _byr > 2002)
    {
        byr = defaultValue;
        cout << "Passport Invalid Due to " << "Birth Year" << "\n";
        validPassport = false;
    }
    else
    {
        byr = _byr;
    }
    
    if (_iyr == defaultValue || CountNumberOfDigits(_iyr) != 4 || _iyr < 2010 || _iyr > 2020)
    {
        iyr = defaultValue;
        cout << "Passport Invalid Due to " << "Issue Year" << "\n";
        validPassport = false;
    }
    else
    {
        iyr = _iyr;
    }

    if (_eyr == defaultValue || CountNumberOfDigits(_eyr) != 4 || _eyr < 2020 || _eyr > 2030)
    {
        eyr = defaultValue;
        cout << "Passport Invalid Due to " << "Expiry Year" << "\n";
        validPassport = false;
    }
    else
    {
        eyr = _eyr;
    }

    if (_hgt == defaultValue || (_unitType == imperial && (_hgt < 59 || _hgt > 76)) || (_unitType == metric && (_hgt < 150 || _hgt > 193)))
    {
        hgt = defaultValue;
        cout << "Passport Invalid Due to " << "Height" << "\n";
        validPassport = false;
    }
    else
    {
        hgt = _hgt;
    }

    
    if (_pid == defaultValueStr || !DetermineIfValidPassportNumber(_pid))
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

    if (_ecl == defaultValueStr || !DetermineIfValidEyeColour(_ecl))
    {
        ecl = defaultValueStr;        
        cout << "Passport Invalid Due to " << "Eye Colour" << "\n";
        validPassport = false;
    }
    else
    {
        ecl = _ecl;
    }

    if (_hcl == defaultValueStr || !DetermineIfValidHairColour(_hcl))
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
        UnitType _unitType = metric;

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
                 
                if (value.find("in") == 2 || value.find("in") == 3)
                {
                    _unitType = imperial;
                    _hgt = stoi(value);
                }
                else if (value.find("cm") == 2 || value.find("cm") == 3)
                {
                    _unitType = metric;
                    _hgt = stoi(value);
                }
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

        Passport tmpPassport = Passport(_byr, _iyr, _eyr, _hgt, _cid, _unitType, _pid, _ecl, _hcl);
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