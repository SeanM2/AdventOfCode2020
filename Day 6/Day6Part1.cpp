#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

string CheckForDuplicates(const std::string &inputStr)
{
    std::string arr;
    std::unordered_set<char> exists;

    for (const auto& el:inputStr)
    {
        if (exists.insert(el).second)
        {
            arr += el;
        }        
    }

    std:sort(arr.begin(), arr.end());

    return arr;
}

vector<string> ReadFileInformation()
{
    ifstream myfile;
    myfile.open("input.txt");
    vector<string> outputArray;
    string tempString;
    string outputString;

    if (myfile.is_open())
    {

        cout << "File Open" << "\n";

        std::string line;
        int numberOfEntries = 0;

        while(std::getline(myfile,line))
        {
            //cout << line << "\n";

            istringstream iss(line);
            string word;            
            iss >> word;

            if (word == "")
            {   
                outputString = CheckForDuplicates(tempString);

                //cout << "Raw String: " << tempString << "\nDuplicates Removed: " << outputString << "\n";

                outputArray.push_back(outputString);
                //cout << "New Group" << "\n";
                tempString = "";
                numberOfEntries++;
            }
            else
            {
                tempString = tempString + word;
            }            
        }
        outputString = CheckForDuplicates(tempString);

        //cout << "Raw String: " << tempString << "\nDuplicates Removed: " << outputString << "\n";

        outputArray.push_back(outputString);
        numberOfEntries++;

        cout << "Number of Entries = " << numberOfEntries << "\n";    

        myfile.close();
    }
    return outputArray;
}

vector<int> CountEachGroupsAnswers(vector<string> inputStringArray)
{
    vector<int> outputArray;

    for (string i : inputStringArray)
    {
        outputArray.push_back(i.length());

        cout << i.length() << "\n";
    }

    return outputArray;
    
}

int main()
{
    vector<string> rawInputArray = ReadFileInformation();

    vector<int> eachGroupPositiveAnswers = CountEachGroupsAnswers(rawInputArray);

    int totalAnswer = 0;

    for (int i : eachGroupPositiveAnswers)
    {
        totalAnswer += i;
    }
    
    cout << "Total Positive Answers = " << totalAnswer << "\n";

    return 0;
}