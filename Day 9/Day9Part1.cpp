#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

int ReadFileInformation(vector<unsigned int>& outputArray)
{
    ifstream myfile;
    myfile.open("input.txt");

    if (myfile.is_open())
    {

        cout << "File Open" << "\n";

        std::string line;
        int numberOfEntries = 0;

        while(std::getline(myfile,line) && numberOfEntries < 666)
        {
            cout << line << "\n";

            istringstream iss(line);
            string word;            
            iss >> word;
            
            outputArray.push_back(stoul(word));
            numberOfEntries++;

        }       

        cout << "Number of Entries = " << numberOfEntries << "\n";    

        myfile.close();
    }

    return 0;
}

int FindTheImposter(vector<unsigned int>& inputArray)
{
    list<unsigned int> buffer;
    bool valueFound = false;
    bool noSolutionFound = true;

    for (int i = 0; i < 25; i++)
    {
        buffer.emplace_back(inputArray[i]);
    }

    for (int i = 25; i < inputArray.size(); i++)
    {
        vector<int> bufferVector(buffer.begin(), buffer.end());

        for (int j = 0; j < bufferVector.size(); j++)
        {
            for (int k = 0; k < bufferVector.size(); k++)
            {
                if (bufferVector[k] + bufferVector[j] == inputArray[i])
                {
                    valueFound = true;
                    noSolutionFound = false;
                    break;
                }
                
            }

            if (valueFound)
            {
                valueFound = false;
                break;
            }
        }
        if (noSolutionFound)
        {
            cout << "No Solution Found in Buffer\n";
            return i;
        }
        else
        {
            buffer.erase(buffer.begin());
            buffer.emplace_back(inputArray[0]);
        }                    
        
    }
    
    return 0; 
    
}

int main()
{
    vector<unsigned int> inputArray;
    
    ReadFileInformation(inputArray);

    int index = FindTheImposter(inputArray);

    cout << "Value at Index " << index << ": " << inputArray[index];

    return 0;
}