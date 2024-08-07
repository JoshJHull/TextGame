#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Player {
private:
    vector<Object> inventory_;
public:
    Player();
    vector<Object> getInventory() { return inventory_; }
    void addItem(Object item);
    void removeItem(Object item);
    bool isDead;
};

#endif