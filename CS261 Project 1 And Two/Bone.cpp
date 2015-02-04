#include "Bone.h"

Bone::Bone(int top, int bot) {
    setTopNum(top);
    setBottomNum(bot);
    checkDouble();
    active = true;
}

Bone::Bone(const Bone* obj) {
    this->active = obj->active;
    this->bottomNum = obj->bottomNum;
    this->isDouble = obj->isDouble;
    this->topNum = obj->topNum;
}

int Bone::setTopNum(const int top) {
    topNum = top;
    if (!top) {
        return 1;
        cout << "couldn't update number";
    } else {
        return 0;
    }
}

bool Bone::getDouble() const {
    return this->isDouble;
}

int Bone::setBottomNum(const int bottom) {
    bottomNum = bottom;
    if (!bottom) {
        return 1;
        cout << "couldn't update number";
    } else {
        return 0;
    }
}

int Bone::checkDouble() {
    if (topNum == bottomNum) {
        isDouble = true;
        return 1;
    } else {
        isDouble = false;
        return 0;
    }
}

int Bone::getTopNum()const {
    return topNum;
}

int Bone::getBottomNum()const {
    return bottomNum;
}

int Bone::print() {
    cout << "[" << topNum << "|" << bottomNum << "]" << " ";
    return 1;
}

const Bone& Bone::operator=(const Bone& obj) {
    this->active = obj.active;
    this->bottomNum = obj.bottomNum;
    this->isDouble = obj.isDouble;
    this->topNum = obj.topNum;
    return *this;
}
