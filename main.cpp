#include <iostream>
#include <vector>
#include <array>
#include <random>
#include "city.h"
#include "item.h"
#include "player.h"
#include "time.h"

using namespace std;

City setupCity(std::string cityName, std::vector<Item> items);
double getRandDouble(double l, double h);
int getRandInt(int l, int h);
int travel(int days);
char prompt(player user, int days);
void gameOver(player user, int days);




int main()
{
    srand(time(NULL));
    std::vector<Item> items { Item {"milk", 2.0, 1}, Item{"eggs", 3.5, 1}, Item{"butter", 1.5, 1}, Item{"bananas", 3.0, 1}};
    std::array<City, 4> places {setupCity("Boston", items), setupCity("Lowell", items), setupCity("Methuen", items), setupCity("Haverhill", items)};

    for(size_t i = 0; i < places.size(); i++)
    {
        items = places[i].getItems(); //get a copy of the city items
        for(size_t j = 0; j < items.size(); j++)
        {
            //for each item change the qty and cost
            double currentCost = items[j].getCost();
            double newCost = currentCost * (1 + getRandDouble(-.99, 1.99));
            items[j].setCost(newCost);
            int newQty = getRandInt(0, 10);
            items[j].setQuantity(newQty);
        }
        // Copy this modified list back to the city
        places[i].setItems(items);
    }

    int days = 10;
    City currentCity = places[getRandInt(0,4)];
    player user(200.00);
    user.setInventory(std::vector<Item> { Item {"milk", 2.0, 1}, Item{"eggs", 3.5, 1}, Item{"butter", 1.5, 1}, Item{"bananas", 3.0, 1}});
    char choice;
    int userIn;
    bool quit = false;

    cout << "--------------------------------------------------------------------" << endl;
    cout << "Welcome to MARKET WARS!" << endl;
    cout << "--------------------------------------------------------------------" << endl;
    cout << "The objective of this game is to make money" << endl;
    cout << "You have 5 spots in your inventory to store different kinds of items" << endl;
    cout << "Travelling to different cities costs 1 day of playing time" << endl;
    cout << "The game ends when you either run out of money and items, or days" << endl;
    cout << "You will start out with 10 days and $200.00 in " << currentCity.getName() << endl;
    cout << "GOOD LUCK!!!" << endl;
    cout << "--------------------------------------------------------------------" << endl;


    while((user.getWallet() > 0.00 || user.hasItems()) && !quit && days > 0){
        start:
            choice = prompt(user, days);

            if(choice == 'b'){                                                      // buy
                if(user.hasSpace() == false){
                    cout << "You have no more room in your inventory" << endl;
                    goto start;
                }
                if(user.getWallet() == 0.00){
                    cout << "You have no money" << endl;
                    goto start;
                }

                cout << "Select item to purchase:" << endl;
                //list items in current city
                for(std::vector<Item>::size_type i = 0; i < 4; i++){
                    cout << "(" << i << ")" << items[i].getName() << " - $" << items[i].getCost() << " - " << items[i].getQuantity() << " available" << endl;
                }
                cin >> userIn;
                while(userIn > items.size() - 1){
                    cout << "Please enter a number between 0 and " << items.size() - 1 << endl;
                    cin >> userIn;
                }
                int num;
                cout << "Enter the quantity you wish to purchase:" << endl;
                cin >> num;
                while(num > items[userIn].getQuantity() && user.getWallet() > items[userIn].getCost() * num){
                    cout << "Please enter a lower number:" << endl;
                    cin >> num;
                }
                Item newItem(items[userIn].getName());
                newItem.setQuantity(num);
                items[userIn].setQuantity(items[userIn].getQuantity() - num);
                user.addItem(newItem);
                user.setWallet(user.getWallet() - items[userIn].getCost() * num);
            }

            if(choice == 's'){                                                          // sell
                if(user.hasItems() == false){
                    cout << "You have no items to sell" << endl;
                    goto start;
                }
                cout << "Select item to sell:" << endl;
                for(std::vector<Item>::size_type i = 0; i < 4; i++){
                    cout << "(" << i << ")" << user.getInventory()[i].getName() << " - $" << items[i].getCost() << " - " << user.getInventory()[i].getQuantity() << " available" << endl;
                }
                cin >> userIn;
                while(userIn > user.getInventory().size() - 1){
                    cout << "Please enter a number between 0 and " << user.getInventory().size() - 1 << endl;
                    cin >> userIn;
                }
                int num;
                cout << "Enter the quantity you wish to sell:" << endl;
                cin >> num;
                while(num > user.getInventory()[userIn].getQuantity()){
                    cout << "Please enter a lower number:" << endl;
                    cin >> num;
                }
                std::vector<Item> temp = user.getInventory();
                temp[userIn].setQuantity(user.getInventory()[userIn].getQuantity()-num);
                user.setInventory(temp);
                user.setWallet(user.getWallet() + (items[userIn].getCost()*num));
                items[userIn].setQuantity(items[userIn].getQuantity()+num);
            }

            else if(choice == 't'){                                                     //travel
                travel:
                cout << "Select a city to travel to:" << endl;
                for(size_t i = 0; i < 4; i++){
                        cout << "(" << i << ")" << places[i].getName() << endl;
                }
                cin >> userIn;
                while(userIn > 3){
                    cout << "Please enter a number between 0 and 3" << endl;
                    cin >> userIn;
                }
                if(currentCity.getName() == places[userIn].getName()){
                    cout << "You are already here!" << endl;
                    goto travel;
                }
                cout << "You are now entering " << places[userIn].getName() << endl;
                days--;
                currentCity = places[userIn];

                for(size_t i = 0; i < places.size(); i++)
                {
                    items = places[i].getItems(); //get a copy of the city items
                    for(size_t j = 0; j < items.size(); j++)
                    {
                        //for each item change the qty and cost
                        double currentCost = items[j].getCost();
                        double newCost = currentCost * (1 + getRandDouble(-.99, 1.99));
                        items[j].setCost(newCost);
                        int newQty = getRandInt(0, 10);
                        items[j].setQuantity(newQty);
                    }
                    // Copy this modified list back to the city
                    places[i].setItems(items);
                }
            }

            else if(choice == 'p'){
                user.printInventory();
            }

            else if(choice == 'q'){                                                     //quit
                quit = true;
            }
    }
    gameOver(user, days);

    return 0;
}

City setupCity(std::string cityName, std::vector<Item> items)
{
    City c{cityName};
    for (Item it : items) {
        c.addItem(it);
    }
    return c;
}

int getRandInt(int l, int h)
{
    return rand()%(h-l) + l;
}

double getRandDouble(double l, double h)
{
    double x = rand()%(static_cast<int>(h*100)-static_cast<int>(l*100)) + l;
    return x/100;
}

char prompt(player user, int days)
{
    char userIn;
    cout << "WALLET: $" << user.getWallet() << endl;
    cout << "DAYS LEFT: " << days << endl;
    cout << "-------------------" << endl;
    cout << "Purchase items: (b)" << endl;
    cout << "Sell items:     (s)" << endl;
    cout << "Travel:         (t)" << endl;
    cout << "Quit:           (q)" << endl;
    cout << "-------------------" << endl;
    cin >> userIn;
    return userIn;
}

void gameOver(player user, int days)
{
    cout << "GAME OVER" << endl;
    cout << "---------" << endl;
    cout << "DAYS LEFT: " << days << endl;
    cout << "WALLET: $" << user.getWallet() << endl;
    //still need to print inventory
}





