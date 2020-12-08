#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool RunProgramme(vector<string> instructionArray, vector<int> valueArray, vector<bool> indexVisited, int& accumulatedValue)
{
    for (int idx = 0; idx < 700;)
        {
            if (idx >= indexVisited.size())
            {
                return true;
            }
            
            // cout << "Doing the thing, IDX = " << idx << " / " << indexVisited.size() << "\n";

            if (indexVisited[idx] == true)
            {
                cout << "Exiting due to index being visited\n";
                return false;
                break;
            }

            bool tmp = instructionArray[idx] == "acc";
            cout << instructionArray[idx] << "-" << valueArray[idx] << "\n";
            // cout << valueArray[idx] << "\n"; 

            if (instructionArray[idx] == "nop")
            {            
                // cout << "Doing the thing, IDX = " << idx << "\n";

                indexVisited[idx] = true;
                idx++;
            }
            else if (instructionArray[idx] == "jmp")
            {
                // cout << "Doing the thing, IDX = " << idx << "\n";

                indexVisited[idx] = true;
                idx += valueArray[idx];
            }
            else if (instructionArray[idx] == "acc")
            {
                indexVisited[idx] = true;
                accumulatedValue += valueArray[idx];

                cout << "Accumulated Value: " << accumulatedValue << "\n";
                idx++; 
            }
            else
            {
                cout << "Failed to find valid instruction\n";
            }     
            // cout << "Doing the thing, IDX = " << idx << "\n";
        }

        return false;
}

bool GenerateNewInputFile(vector<string> instructionArray, vector<int> valueArray, vector<bool> indexVisited, int& accumulatedValue, const string& modifiedValue, const string& substituteValue)
{
    for (int j = 0; j < instructionArray.size(); j++)
    {
        accumulatedValue = 0;
        vector<string> _instructionArray = instructionArray;
        
        if (_instructionArray[j] == modifiedValue)
        {
            cout << substituteValue << " Index number: " << j << "\n";            
            _instructionArray[j] = substituteValue;
            if(RunProgramme(_instructionArray, valueArray, indexVisited, accumulatedValue)) 
            {
                return true;
            }
        }
    }

        return false;  
}

int ReadFileInformation()
{
    ifstream myfile;
    myfile.open("input.txt");
    vector<bool> indexVisited;
    int accumlatedValue = 0;
        
    vector<string> instructionArray;
    vector<int> valueArray;

    if (myfile.is_open())
    {
        cout << "File Open" << "\n";

        std::string line;
        int numberOfEntries = 0;

        while(std::getline(myfile,line))
        {
            //cout << line << "\n";

            istringstream iss(line);
            string instruction, value;
            //groupArray.clear()
            int i = 0;
            
            iss >> instruction >> value;
            
                instruction.replace(3,1,"");
                instructionArray.push_back(instruction);
                indexVisited.push_back(false);
                signed int valueToAssign = -1;

                if (value[0] == '+')
                {
                    valueToAssign = stoi(value);
                }
                else if (value[0] == '-')
                {
                    valueToAssign = stoi(value);
                }
                valueArray.push_back(valueToAssign);
                
                //cout << instruction << " " << valueToAssign << "-----" << indexVisited[i] << "\n";
                i++;
            

                    
        }       
        
        myfile.close();
        
    }

    bool loopDetected = true;
    int i =0;

    while (loopDetected)
    {
        loopDetected = false;
        string modifiedValue, substituteValue;

        switch (i)
        {
        case 0:
            modifiedValue = "nop";
            substituteValue = "jmp";
            break;

        case 1:
            modifiedValue = "jmp";
            substituteValue = "nop";
            break;

        
        default:
            return accumlatedValue;
            break;
        }

        loopDetected = !GenerateNewInputFile(instructionArray, valueArray, indexVisited, accumlatedValue, modifiedValue, substituteValue);
        i++;

    }
    
    return accumlatedValue;
}


int main()
{
    int accumulatedValue = ReadFileInformation();

    cout << "Accumulated Value: " << accumulatedValue << "\n";

    return 0;
}