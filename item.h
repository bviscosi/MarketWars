/*
 * Item class
 * Michael Penta
 *
 */
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
    //encapsulated data members of class
    private:
        std::string itemName;
        double itemUnitCost;
        int itemQuantity;

    public:
        //new C++11 constructor delegation
        Item(std::string name)
            : itemName(name), itemUnitCost(0), itemQuantity(0) {}
        Item(std::string name, double cost)
            : itemName(name), itemUnitCost(cost), itemQuantity(0) {}
        Item(std::string name, double cost, int qty)
        //set default values
            : itemName(name), itemUnitCost(cost), itemQuantity(qty) {}

        //mutators and accessor member functions
        //C++11 you define trival functions in the header (can be any function but really only should be simple ones)
        int getQuantity(){return itemQuantity;}
        void setQuantity(int n){itemQuantity = n;}

        double getCost(){return itemUnitCost;}
        void setCost(double n) {itemUnitCost = n; }

        std::string getName(){ return itemName; }
        void setName(std::string s){itemName = s;}

};

#endif // ITEM_H
