#ifndef OBJECT_H
#define OBJECT_H

#include <string>

using namespace std;

class Object {
private:
    string id_;
    string desc_;
public:
    Object(string id, string desc);
    string getId() const { return id_; }
    string getDesc() const { return desc_; }
};

#endif