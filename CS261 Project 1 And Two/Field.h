#ifndef FIELD_H
#define FIELD_H
#include "Bone.h"
#include "Player.h"
#include <vector>

class Field {
public:
    Field(int var); //needs an integer to start the Field
    ~Field();
    Field(const Field* obj);
    int determine_playable(vector <int> & numbs); //called by game class to give the numbers players can play off of
    int recieve_bone(Bone * aBone); //called by game class to give a bone to the field
private:
    int iterations; //how many cards have been played off of a double
    int highest_double; //what the current double is
    vector <int> current_numbers; //list of numbers
    int first_double;
};

#endif
