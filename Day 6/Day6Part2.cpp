#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;


vector<vector<string>> ReadFileInformation()
{
    ifstream myfile;
    myfile.open("input.txt");
    vector<vector<string>> outputArray;
    vector<string> groupArray;

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
                outputArray.push_back(groupArray);
                groupArray.clear();
                //cout << "New Group" << "\n";
                numberOfEntries++;
            }
            else
            {
                groupArray.push_back(word);
            }            
        }

        
        outputArray.push_back(groupArray);
        groupArray.clear();
        numberOfEntries++;

        cout << "Number of Entries = " << numberOfEntries << "\n";    

        myfile.close();
    }
    return outputArray;
}

vector<int> CountEachGroupsAnswers(vector<vector<string>> inputStringArray)
{
    vector<int> outputArray;

    for (vector<string> i : inputStringArray)
    {
        // this is a group
        string firstValue = i[0]; // grab first string from first person
        int answersFromGroup = 0;
        //cout << firstValue << "\n";

        for (int k = 0; k < firstValue.length(); k++)
        {
            bool answerPresent = true;

            for (int j = 1; j < i.size(); j++)
            {
                //cout << firstValue[k] << "\n";
                // this is a person, starting from person number 2, search each other person for the answers in the first person, if one person doesn't have that answer increase the count if everyone has the answer.
                int letterIdx = i[j].find(firstValue[k]);
                if (letterIdx != -1)
                {
                    //cout << "Answer present.\n" << firstValue[k] << " is present in " << i[j] << " - " << letterIdx << "\n";
                }
                else
                {
                    answerPresent = false;
                    //cout << "Answer not present.\n" << firstValue[k] << " is not present in " << i[j] << " - " << letterIdx << "\n";
                    break;  
                }
                
            }

            if (answerPresent)
            {
                answersFromGroup++;
            }
        }

        outputArray.push_back(answersFromGroup);
    }
    

    return outputArray;
    
}

int main()
{
    vector<vector<string>> rawInputArray = ReadFileInformation();

    vector<int> eachGroupPositiveAnswers = CountEachGroupsAnswers(rawInputArray);

    int totalAnswer = 0;

    for (int i : eachGroupPositiveAnswers)
    {
        totalAnswer += i;
    }
    
    cout << "Total Positive Answers = " << totalAnswer << "\n";

    return 0;
}