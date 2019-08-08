/*
 * Michael Penta
 * A City has a list (vector) of items for selling and buying
 * */

#ifndef CITY_H
#define CITY_H

#include "item.h"
#include <vector>

class City
{
    private:
    //private data members
       std::string cityName;
       std::vector <Item> items;

     //private member functions for use by other member functions
       double getRandomPercent();
       int getRandomQuantity();

    public:
       City(std::string name);

    //public setters and getters
       std::vector<Item> getItems();
       void setItems(std::vector<Item>);

       std::string getName();

       //add additional items to the city
       void addItem(Item);
};

#endif // CITY_H
