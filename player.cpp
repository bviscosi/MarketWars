#include "player.h"

player::player(double cash)
{
    wallet = cash;
}

void player::addItem(Item newItem){
    bool duplicate = false;
    int index = 0;
    for(std::vector<Item>::size_type i = 0; i < inventory.size(); i++){
        if(newItem.getName() == inventory.at(i).getName()){
            duplicate = true;  
            index = i;
            i = inventory.size();
        }
    }
    if(duplicate){
        inventory[index].setQuantity(inventory[index].getQuantity()+newItem.getQuantity());
    }
    else{
        inventory.push_back(newItem);
    }
}

void player::printInventory(){
    cout << "YOUR INVENTORY:" << endl;
    for(std::vector<Item>::size_type i = 0; i < inventory.size(); i++){
        cout << inventory[i].getName() << " - " << inventory[i].getQuantity() << endl;
    }
    cout << "-------------------" << endl;
}
