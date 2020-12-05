#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class BoardingCard
{
private:
    int row;
    int column;
    int seatID;
public:
    BoardingCard(string);
    int DetermineRowNumber(string);
    int DetermineColumnNumber(string);

    int getSeatID() { return seatID; }

    static bool compSeatID( BoardingCard cmpA, BoardingCard cmpB) 
    { 
        return cmpA.getSeatID() < cmpB.getSeatID();    
    }
};

BoardingCard::BoardingCard(string inputString)
{
    row = DetermineRowNumber(inputString);
    column = DetermineColumnNumber(inputString);
    seatID = (row * 8) + column;
}

int BoardingCard::DetermineColumnNumber(string inputString)
{
    int rightLimit = 7, leftLimit = 0, idx = 7;

    while (inputString[idx] == 'R' || inputString[idx] == 'L')
    {
        if (inputString[idx] == 'L')
        {
            rightLimit = leftLimit + (rightLimit - leftLimit)/2;
        }
        else
        {
            leftLimit = rightLimit - (rightLimit - leftLimit)/2;
        }
        
            //cout << inputString[idx] << " -> " << leftLimit << " - " << rightLimit << "\n";
        idx++;
    }

    //cout << "Column Number: " << rightLimit << "\n";

    
    return rightLimit;
}

int BoardingCard::DetermineRowNumber(string inputString)
{
    int frontLimit = 0, rearLimit = 127, idx = 0;    

    while (inputString[idx] == 'F' || inputString[idx] == 'B')
    {
        
        if (inputString[idx] == 'F')
        {
            rearLimit = frontLimit + (rearLimit - frontLimit) / 2;
            //cout << inputString[idx] << " -> " << frontLimit << " - " << rearLimit << "\n";
        }
        else
        {
            frontLimit = rearLimit - (rearLimit - frontLimit) / 2;            
            //cout << inputString[idx] << " -> " << frontLimit << " - " << rearLimit << "\n";
        }
        
        idx++;
    }
    
    //cout << "\n" << "Row Number = " << frontLimit << "\n";

    return frontLimit; 
}





vector<string> ReadFileInformation()
{
    ifstream myfile;
    myfile.open("input.txt");
    vector<string> outputArray;

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
            
            outputArray.push_back(word);
            
            numberOfEntries++;
        }               
                

        cout << "Number of Entries = " << numberOfEntries << "\n";    

        myfile.close();
    }
    return outputArray;
}

vector<BoardingCard> GenerateBoardingCards(vector<string> rawInputArray)
{
    vector<BoardingCard> outputArray;

    for (int i = 0; i < rawInputArray.size(); i++)
    {
        outputArray.push_back(BoardingCard(rawInputArray[i]));
    }

    return outputArray;
}

int CheckForHighestSeatID(vector<BoardingCard> inputArray)
{
    int highestValue = 0;

    for (BoardingCard i : inputArray)
    {
        if (i.getSeatID() > highestValue)
        {
            highestValue = i.getSeatID();
        }        
    }
    return highestValue;    
}

int CheckForLowestSeatID(vector<BoardingCard> inputArray)
{
    int lowestValue = 999;

    for (BoardingCard i : inputArray)
    {
        if (i.getSeatID() < lowestValue)
        {
            lowestValue = i.getSeatID();
        }        
    }
    return lowestValue;    
}

int DetermineSeatID(vector<BoardingCard> boardingCardArray)
{
    sort(boardingCardArray.begin(), boardingCardArray.end(), BoardingCard::compSeatID);

    //cout << "Seat ID Range " << boardingCardArray[0].getSeatID() << "-" << boardingCardArray[887].getSeatID() << "\n";

    int mySeatID = 0;

    for (int i = 1; i < boardingCardArray.size(); i++)
    {
        if (boardingCardArray[i-1].getSeatID() != boardingCardArray[i].getSeatID() - 1)
        {
            cout << boardingCardArray[i-1].getSeatID() << boardingCardArray[i].getSeatID() << "\n";
            mySeatID = boardingCardArray[i].getSeatID() - 1;

            return mySeatID;
        }
    }

    return mySeatID;
}

int main()
{
    vector<string> rawInputArray = ReadFileInformation();

    vector<BoardingCard> boardingCardArray = GenerateBoardingCards(rawInputArray);

    //cout << "Seat ID Range " << CheckForLowestSeatID(boardingCardArray) << "-" << CheckForHighestSeatID(boardingCardArray) << "\n";   

    int seatID = DetermineSeatID(boardingCardArray);
    cout << "My Seat ID is: " << seatID <<"\n";
    
} 