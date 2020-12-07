#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Bag
{
private:
    string bagColour;
    vector<string> heldBagColours;
    vector<int> heldBagColourQuantity;
    int maxNumberOfBagsInside = 0;

    bool canHoldGoldBag = false;
public:
    Bag(string, vector<string>, vector<int>);

    string getBagColour() { return bagColour; }
    vector<string> getHeldBagColour() { return heldBagColours; }
    vector<int> getHeldBagColourQuantity() { return heldBagColourQuantity; }
    bool getHoldGoldBag() { return canHoldGoldBag; }
    void setHoldGoldBag() { canHoldGoldBag = true; }

    int getMaxNumberOfBagsInside() { return maxNumberOfBagsInside; }

    bool CanIHoldAGoldBag(vector<string>);

    bool CanMyBagsHoldAGoldBag(vector<Bag>&);

    int MagnitudeOfBagception(vector<Bag>&);
};

int Bag::MagnitudeOfBagception(vector<Bag>& bagArray)
{
    int numberOfBags = 0;

    for (int i = 0; i < this-> heldBagColours.size(); i++)
    {
        for (Bag bag : bagArray)
        {
            if (bag.getBagColour() == heldBagColours[i])
            {
                if (this->bagColour == "shiny gold")
                {
                    cout << this->bagColour << " looking for " << bag.getBagColour() << " there are this many present: " << max(bag.getMaxNumberOfBagsInside(),1) * this -> getHeldBagColourQuantity()[i] << "\n";
                    //cout << this -> getHeldBagColourQuantity()[i] << "\n";
                }                
                
                numberOfBags += ((bag.getMaxNumberOfBagsInside()) + 1) * this -> getHeldBagColourQuantity()[i];
            }
            
        }
        
    }
    return this -> maxNumberOfBagsInside = numberOfBags;    
}

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

    for (int i = 0; i < heldBagColourQuantity.size(); i++)
    {
        //cout << this->bagColour << " has " << heldBagColourQuantity[i] << " bags of " << heldBagColours[i] << "-------"; 
        maxNumberOfBagsInside += heldBagColourQuantity[i];        
    }

    //cout << this -> bagColour << " Max Number of Bags = " <<  maxNumberOfBagsInside <<"\n";

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

    // for (int i = 0; i < 5; i++)
    // {
    //     for (int j = 0; j < outputArray.size(); j++)
    //     {
    //         outputArray[j].CanMyBagsHoldAGoldBag(outputArray);
    //         cout << outputArray[j].getBagColour() << " can hold a bag: " << outputArray[j].getHoldGoldBag() << "\n";
    //     }
    // }

    for (int i = 0; i < 5; i++)
    {
        //cout << "Loop: " << i << "\n";

        for (int j = 0; j < outputArray.size(); j++)
        {
            outputArray[j].MagnitudeOfBagception(outputArray);
            //cout << outputArray[j].getBagColour() << " has this many bags: " << outputArray[j].getMaxNumberOfBagsInside() << "\n";
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

int CountNumberOfBagsWithinBags(string bagName, vector<Bag> bagArray)
{
    int countOfBags = 0;

    for (int i = 0; i < bagArray.size(); i++)
    {
        if (bagArray[i].getBagColour() == bagName)
        {
            countOfBags = bagArray[i].getMaxNumberOfBagsInside();
        }        
    }  

    return countOfBags;
}

int main()
{
    // int numberOfGoldBags = CountNumberOfGivenBags("shiny gold", ReadFileInformation());

    int numberOfBags = CountNumberOfBagsWithinBags("shiny gold", ReadFileInformation());

    cout << "Gold Holds This Many Bag: " << numberOfBags << "\n";
    
    //cout << "Number of Gold Bags: " << numberOfGoldBags << "\n";

    return 0;
}