#include "Room.h"
#include <algorithm>

using namespace std;

Room::Room() {
    id_ = {};
    desc_ = {};
    exits_ = {};
    objects_ = {};
    enemies_ = {};
}

Room::Room(string id, string desc, map<string, string> exits) {
    id_ = std::move(id);
    desc_ = std::move(desc);
    exits_ = std::move(exits);
    objects_ = {};
    enemies_ = {};
}

void Room::addObject(Object object) {
    objects_.push_back(object);
}

void Room::removeObject(string object) {
    objects_.erase(remove_if(objects_.begin(), objects_.end(), [object](const Object &o) {return o.getId() == object;}), objects_.end());
}

void Room::addEnemy(Enemy enemy) {
    enemies_.push_back(enemy);
}

void Room::removeEnemy(string enemy) {
    enemies_.erase(remove_if(enemies_.begin(), enemies_.end(), [enemy](const Enemy &e) {return e.getId() == enemy;}), enemies_.end());
}
