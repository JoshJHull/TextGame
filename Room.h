#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <vector>
#include "Object.h"
#include "Enemy.h"

using namespace std;

class Room {
private:
    string id_;
    string desc_;
    map<string, string> exits_;
    vector<Object> objects_;
    vector<Enemy> enemies_;

public:
    Room();
    Room(string id, string desc, map<string, string> exits);
    string getId() const { return id_; }
    string getDesc() const { return desc_; }
    map<string, string> getExits() { return exits_; }
    vector<Object> getObjects() { return objects_; }
    vector<Enemy> getEnemies() { return enemies_; }
    void addObject(Object object);
    void removeObject(string object);
    void addEnemy(Enemy enemy);
    void removeEnemy(string enemy);
};

#endif