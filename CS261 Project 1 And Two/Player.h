#ifndef PLAYER_H
#define PLAYER_H

#include <cstring>
#include <string>
#include "Bone.h"
#include "Yard.h"
using namespace std;

class Player {
public:
    Player(); //constructor with a player name
    ~Player();
    Player(const Player* obj);
    void give_name(); //prints the players name
    int display_hand(); //prints the whole hand
    int play_card(Bone *& aBone, int top, int bot);
    int highest_double(); //determines the highest double
    int draw_card(Yard *&); //draws a card from the yard
    void setName(string name); // Sets the name.
    int calculate_score(); //calculates the players current score based on the cards in hand
    bool isNull(); // Hand Size I guess ~ Brandan
private:

    struct node {
        Bone * bone; //pointer to a bone
        node * next; //ponter to the next node
    };
    node * hand; //hand 
    node * tail; //hand 
    int score; //total current score
    string player_name; //player id

};

#endif
