#include "Player.h"

using namespace std;

Player::Player() {
    inventory_ = {};
    isDead = false;
}

void Player::addItem(Object item) {
    inventory_.push_back(item);
}

void Player::removeItem(Object item) {
    for(auto it = inventory_.begin(); it != inventory_.end(); it++) {
        if(it->getId() == item.getId()) {
            inventory_.erase(it);
        }
    }
}
