#include "city.h"
#include <random>
#include "item.h"

City::City(std::string n)
{
    cityName = n;
}
void City::addItem(Item i)
{
    items.push_back(i);
}
void City::setItems(std::vector<Item> its)
{
    //clear the current items
    //so we can copy in all the new ones
   items.clear();
   for(Item it : its)
   {
       items.push_back(it);
   }
}

std::vector<Item> City::getItems()
{
    return items;
}
std::string City::getName()
{
    return cityName;
}
