#include "Enemy.h"

using namespace std;

Enemy::Enemy(string id, string desc, int agro, vector<string> killedBy) {
    id_ = std::move(id);
    desc_ = std::move(desc);
    agro_ = agro;
    killedBy_ = std::move(killedBy);
}