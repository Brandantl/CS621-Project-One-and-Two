#ifndef GAME_H
#define GAME_H
#include "Field.h"
#include "Player.h"
#include "Bone.h"
#include "string"
#include <iostream>
using namespace std;

class Game {
public:
    Game();
    ~Game();
    Game(const Game* obj);
    void setup();
    // No one outside Game.h/cpp will have access to the players
    // So they should be in the private section
private:
    Field * gField; //game field
    Player * group; //an array of players
    Yard * gYard;

    int turn;
    bool status;
    int numberPlayers;
    int skip;

    void first_play();
    char getChar(char * prompt);
    int getInt(char * prompt);
    int controls();
    int complete_play(); //plays a bone
    int determine_winner(); //determines the winner David
    int get_playable_bones(); //show the player which numbers they can play. David
    void compare_doubles(); //compare who has the highest double Brandan
    int get_players_card(int top, int bot); //get a bone from the player Brandan
    int outOfCards();
};

#endif
