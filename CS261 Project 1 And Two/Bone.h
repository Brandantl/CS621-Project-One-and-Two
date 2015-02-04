#ifndef BONE_H
#define BONE_H
#include <iostream>
#include <ctype.h>
using namespace std;

class Bone {
private:
    int topNum; //top number of the card
    int bottomNum; //bottom number of the card
    bool isDouble; //flags if is a double
    bool active;
    const Bone& operator=(const Bone& obj);
public:
    Bone(int, int); //initialize a bone
    Bone(const Bone* obj);
    int setTopNum(const int); //called by constructor
    int setBottomNum(const int); //called by construtor
    int checkDouble();
    bool getDouble() const;
    int getTopNum()const; //returns top number
    int getBottomNum()const; //returns bottom number
    int print(); //prints the whole card
};

#endif
