#include <iostream>
#include "json.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include "Room.h"
#include "Player.h"

using namespace std;
using json = nlohmann::json;

vector<Room> rooms {};
string objectiveType {};
vector<string> objectiveList {};
vector<string> deadEnemies {};
Player player {};
Room* currentRoom;

void mapImport(string arg);
bool checkEnd();
void move(string exit);
Room* findRoom(string roomName);
void lookAround();
void takeObject(string object);
void examineObject(string object);
void listItems();
void killEnemy(string name);

int main(int argc, char* argv[]) {
    string strArg(argv[1]);
    mapImport(strArg);

    lookAround();

    bool end = false;
    while(!end) {
        string input {};
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        istringstream stream(input);
        string word1;
        string word2;
        stream >> word1 >> word2;
        while(!stream.eof()) {
            word2 += " ";
            string tempWord;
            stream >> tempWord;
            word2 += tempWord;
        }

        if(input == "look" || input == "look around")
            lookAround();
        else if(word1 == "look") {
            examineObject(word2);
        }

        if(input == "list items")
            listItems();

        if(word1 == "take")
            takeObject(word2);

        if(word1 == "go")
            move(word2);

        if(word1 == "kill")
            killEnemy(word2);

        end = checkEnd();
    }

    return 0;
}

void killEnemy(string name) {
    for(auto & enemy : currentRoom->getEnemies()) {
        if(enemy.getId() == name) {
            for(auto & item : player.getInventory()) {
                for(auto & object : enemy.getKilledBy()) {
                    if(object == item.getId()) {
                        cout << "You killed " << name << endl;
                        currentRoom->removeEnemy(name);
                        deadEnemies.push_back(name);
                        return;
                    }
                }
            }
            cout << "You do not have the right item to kill them." << endl;
            player.isDead = true;
            return;
        }
    }
    cout << "That enemy is not here." << endl;
}

void listItems() {
    if(player.getInventory().empty()) {
        cout << "You have no items." << endl;
        return;
    }
    cout << "You have the following items: ";
    for(auto item : player.getInventory()) {
        cout << item.getId() << ", ";
    }
    cout << endl;
}

void examineObject(string object) {
    for(auto item : currentRoom->getObjects()) {
        if(item.getId() == object) {
            cout << item.getDesc() << endl;
            return;
        }
    }
    for(auto item : player.getInventory()) {
        if(item.getId() == object) {
            cout << item.getDesc() << endl;
            return;
        }
    }
}

void takeObject(string object) {
    for(auto & item : currentRoom->getObjects()) {
        if(item.getId() == object){
            player.addItem(item);
            currentRoom->removeObject(item.getId());
            cout << "You picked up " << item.getId() << endl;
            return;
        }
    }
    cout << "That does not exist." << endl;
}

void move(string exit) {
    for(auto const& [key, value] : currentRoom->getExits()) {
        if(key == exit) {
            if(!currentRoom->getEnemies().empty()) {
                random_device device;
                mt19937 rng(device());
                uniform_int_distribution<mt19937::result_type> dist100(0,100);
                int num = dist100(rng);
                if(num <= currentRoom->getEnemies().begin()->getAgro()) {
                    player.isDead = true;
                    cout << "You were attacked while trying to leave." << endl;
                    return;
                }
            }
            currentRoom = findRoom(value);
            lookAround();
            return;
        }
    }
    cout << "You cannot move that way." << endl;
}

void lookAround() {
    cout << currentRoom->getDesc() << endl;
    if(currentRoom->getObjects().empty()){
        cout << "You cannot see any objects." << endl;
    }
    else {
        cout << "You see the following objects: ";
        for (auto object: currentRoom->getObjects()) {
            cout << object.getId() << ", ";
        }
        cout << endl;
    }
    if (currentRoom->getEnemies().empty()) {
        cout << "There are no enemies here." << endl;
    }
    else {
        cout << "You see the following enemies: ";
        for(auto enemy : currentRoom->getEnemies()) {
            cout << enemy.getId() << ", ";
        }
        cout << endl;
    }
}

Room* findRoom(string roomName) {
    for(Room& room : rooms){
        if(room.getId() == roomName){
            return &room;
        }
    }
}

void mapImport(string arg) {
    ifstream ifs(arg);
    json j = json::parse(ifs);
    ifs.close();

    objectiveType = j["objective"]["type"];
    objectiveList = j["objective"]["what"].get<vector<string>>();

    //setup rooms
    for(auto roomIt = j["rooms"].begin(); roomIt != j["rooms"].end(); roomIt++) {
        map<string, string> newMap {};
        for(auto exitIt = roomIt.value()["exits"].begin(); exitIt != roomIt.value()["exits"].end(); exitIt++) {
            newMap[exitIt.key()] = exitIt.value();
        }
        Room newRoom(roomIt.value()["id"], roomIt.value()["desc"], newMap);
        rooms.push_back(newRoom);
        currentRoom = findRoom(j["player"]["initialroom"]);
    }

    //setup objects and assign to rooms
    for(auto objIt = j["objects"].begin(); objIt != j["objects"].end(); objIt++) {
        Object newObject(objIt.value()["id"], objIt.value()["desc"]);
        for(auto & room : rooms) {
            if(room.getId() == objIt.value()["initialroom"]) {
                room.addObject(newObject);
            }
        }
    }

    //setup enemies and assign to rooms
    for(auto enemyIt = j["enemies"].begin(); enemyIt != j["enemies"].end(); enemyIt++) {
        Enemy newEnemy(enemyIt.value()["id"], enemyIt.value()["desc"], enemyIt.value()["aggressiveness"], enemyIt.value()["killedby"]);
        for(auto & room : rooms) {
            if(room.getId() == enemyIt.value()["initialroom"]) {
                room.addEnemy(newEnemy);
            }
        }
    }
}

bool checkEnd() {
    if(player.isDead) {
        cout << "You died." << endl;
        return true;
    }
    if(objectiveType == "kill") {
        vector<string>::iterator it;
        for(auto enemy : objectiveList) {
            it = find(deadEnemies.begin(), deadEnemies.end(), enemy);
            if(it == deadEnemies.end()) {
                return false;
            }
        }
        cout << "You win!" << endl;
        return true;
    }
    else if(objectiveType == "collect") {
        vector<Object> inventory = player.getInventory();
        for(auto object : objectiveList) {
            bool found = false;
            for(auto & invIt : inventory) {
                if(invIt.getId() == object)
                    found = true;
            }
            if(!found)
                return false;
        }
        cout << "You win!" << endl;
        return true;
    }
    else {
        if(currentRoom->getId() == objectiveList[0]) {
            cout << "You win!" << endl;
            return true;
        }
        else
            return false;
    }
}
