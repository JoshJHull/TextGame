#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <vector>

using namespace std;

class Enemy {
private:
    string id_;
    string desc_;
    int agro_;
    vector<string> killedBy_;
public:
    Enemy(string id, string desc, int agro, vector<string> killedBy);
    string getId() const { return id_; }
    string getDesc() const { return desc_; }
    int getAgro() const { return agro_; }
    vector<string> getKilledBy() { return killedBy_; }
};

#endif