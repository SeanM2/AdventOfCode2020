#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Bag
{
private:
    string bagColour;
    vector<string> heldBagColours;
    vector<int> heldBagColourQuantity;

    bool canHoldGoldBag = false;
public:
    Bag(string, vector<string>, vector<int>);

    string getBagColour() { return bagColour; }
    vector<string> getHeldBagColour() { return heldBagColours; }
    vector<int> getHeldBagColourQuantity() { return heldBagColourQuantity; }
    bool getHoldGoldBag() { return canHoldGoldBag; }
    void setHoldGoldBag() { canHoldGoldBag = true; }

    bool CanIHoldAGoldBag(vector<string>);

    bool CanMyBagsHoldAGoldBag(vector<Bag>&);
};

bool Bag::CanIHoldAGoldBag(vector<string> bagNameArray)
{
    // if yes canHoldGoldBag = true;
    for (string bagName : bagNameArray)
    {
        if (bagName == "shiny gold")
        {
            canHoldGoldBag = true;
            break;
        }        
    }

    return canHoldGoldBag;
}

bool Bag::CanMyBagsHoldAGoldBag(vector<Bag>& bagArray)
{
    for (string bagName : this->heldBagColours)
    {
        cout << bagName << " is the bag I'm searching for, on behalf of " << this->getBagColour() << "\n";

        for (Bag bag : bagArray)
        {
            //cout << "Searching for bags within " << bag.getBagColour();

            if (bag.getBagColour() == bagName)
            {
                if(bag.getHoldGoldBag())
                {
                    cout << "------------------" << bag.getBagColour() << " can hold a shiny gold bag: " << bag.getHoldGoldBag() << ". Updating status of " << this->getBagColour() <<  "\n";
                    this->setHoldGoldBag();
                    cout << this->getHoldGoldBag() << "\n";
                }
            }            
        }
    }

    return canHoldGoldBag;    
}

Bag::Bag(string _bagColour, vector<string> _heldBagColours, vector<int> _heldBagColourQuantity)
{
    bagColour = _bagColour;
    heldBagColours = _heldBagColours;
    heldBagColourQuantity = _heldBagColourQuantity;

    CanIHoldAGoldBag(heldBagColours);    
}


vector<Bag> ReadFileInformation()
{
    ifstream myfile;
    myfile.open("input.txt");
    vector<Bag> outputArray;

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
            vector<string> groupArray;
            //groupArray.clear()
            
            while (iss >> word)
            {
                groupArray.push_back(word);

                //cout << word << "\n";
            }
            
            string bagName = groupArray[0] + " " + groupArray[1];
            //cout << bagName << "\n--------------------\n";
            vector<string> containedBags;
            vector<int> containedBagsQuantity;
            int numberOfEntries = (groupArray.size() - 4) / 4; 

            for (int i = 0; i < numberOfEntries; i++)
            {                
                containedBags.push_back(groupArray[5 + i * 4] + " " + groupArray[6 + i * 4]);
                containedBagsQuantity.push_back(stoi(groupArray[4 + i * 4]));

                //cout << containedBags[i] << ": " << containedBagsQuantity[i] << "\n";
            }
            
            //cout << "--------------------\n\n";

            outputArray.push_back(Bag(bagName, containedBags, containedBagsQuantity));           
        } 

        myfile.close();
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < outputArray.size(); j++)
        {
            outputArray[j].CanMyBagsHoldAGoldBag(outputArray);
            cout << outputArray[j].getBagColour() << " can hold a bag: " << outputArray[j].getHoldGoldBag() << "\n";
        }
    }
    
    return outputArray;
}

int CountNumberOfGivenBags(string bagName, vector<Bag> bagArray)
{
    int countOfBags = 0;
    
    for (Bag bag : bagArray)
    {
        cout << bag.getBagColour() << ": " << bag.getHoldGoldBag() << "\n";

        if (bag.getHoldGoldBag() == true)
        {
            cout << "Can Hold The Gold" << "\n";
            countOfBags++;
        }
    }   

    return countOfBags;
}

int main()
{
    int numberOfGoldBags = CountNumberOfGivenBags("shiny gold", ReadFileInformation());
    
    cout << "Number of Gold Bags: " << numberOfGoldBags << "\n";

    return 0;
}