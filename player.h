#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "item.h"
#include <iostream>

using namespace std;

class player
{
    //encapsulated data members of class
    private:

        double wallet;
        std::vector<Item> inventory;

    public:

        player(double cash);

        double getWallet(){return wallet;}
        void setWallet(double cash){wallet = cash;}
        std::vector<Item> getInventory(){return inventory;}
        void setInventory(std::vector<Item> items){inventory = items;}
        bool hasItems(){return (inventory.size() != 0);}
        bool hasSpace(){return (inventory.size() < 5);}
        void addItem(Item i);
        void printInventory();

};

#endif // PLAYER_H
