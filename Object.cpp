#include "Object.h"

using namespace std;

Object::Object(string id, string desc) {
    id_ = std::move(id);
    desc_ = std::move(desc);
}