#ifndef YARD_H
#define YARD_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>  
#include <chrono> 
#include "Bone.h"
using namespace std;

class Yard {
public:
    Yard(); //creates the deck
    ~Yard();
    Yard(const Yard* obj);
    int shuffle_yard(); //shuffles the deck
    bool deal_bone(Bone *& bone); //is passed a pinter to a bone, gives the pointer a bone to point to and deletes that bone from the deck
    int empty(); //returns false if the deck is empty
    int print(); //prints the whole deck
private:
    vector<Bone*> boneSet; //vector to hold the deck
};

#endif