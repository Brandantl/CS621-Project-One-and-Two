#include "Game.h"

/*
 ================== WARNING! =====================
 * DO NOT USE NEW WITHOUT PERMISSION FROM BRANDAN
 * 
 * I FIXED LIKE 12 MEMORY LEAKS
 * ===============================================

==2218== 
==2218== HEAP SUMMARY:
==2218==     in use at exit: 0 bytes in 0 blocks
==2218==   total heap usage: 69 allocs, 69 frees, 1,584 bytes allocated
==2218== 
==2218== All heap blocks were freed -- no leaks are possible
==2218== 
==2218== For counts of detected and suppressed errors, rerun with: -v
==2218== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

 */

Game::Game() : turn(0), status(true), numberPlayers(0) {
    gYard = new Yard;
    gField = NULL;
    skip = 0;
    group = NULL;
}

Game::~Game() {
    if (this->gField) {
        delete this->gField;
    }
    if (this->gYard) {
        delete this->gYard;
    }
    if (this->group) {
        delete [] this->group;
    }
}

Game::Game(const Game* obj) {
    this->gField = obj->gField;
    this->gYard = obj->gYard;
    this->numberPlayers = obj->numberPlayers;
    this->skip = obj->skip;
    this->status = obj->status;
    this->turn = obj->turn;

    if (obj->numberPlayers) {
        group = new Player[obj->numberPlayers];
        for (int i = 0; i < obj->numberPlayers; i++) {
            group[i] = obj->group[i];
        }
    }

}

void Game::setup() {
    cout << endl << "-----Welcome to BDK Chicken Foot 1.0-----" << endl
            << "This is a 2 - 4 player game. The objective of the game is to play a domino from your hand of seven" << endl << "that matches one of the available numbers to play off of. You want to play a double first. All other " << endl << "players are required to play off the double. If you can't play a domino you are required to draw a" << endl
            << "domino from the stack. The first player to play all of their dominoes wins!" << endl;

    const char* playerPrompt = "Number of Players: ";

    while ((numberPlayers < 2) || (numberPlayers > 4)) {
        numberPlayers = this->getInt((char*) playerPrompt);
        if ((numberPlayers < 2) || (numberPlayers > 4)) {
            cout << "Please enter a number between 2 & 4." << endl;
        }

    }


    group = new Player[numberPlayers];

    for (int i = 0; i < numberPlayers; i++) {
        cout << "Player " << (i + 1) << "'s name: ";
        string playerName;
        cin >> playerName;
        group[i].setName(playerName);

        for (int x = 1; x <= 7; x++) {

            group[i].draw_card(gYard);
        }

    }
    compare_doubles();
    turn = (turn + 1) % numberPlayers; //first bone is played when the field is initialized
    controls();
}

char Game::getChar(char * prompt) {
    char cmd;
    cout << prompt;
    cin >> cmd;
    cin.ignore(100, '\n');

    return tolower(cmd);

}

int Game::getInt(char * prompt) {
    int temp;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Illegal input -- try again: ";
        cin >> temp;
    }
    cin.ignore(100, '\n');

    return temp;

}

int Game::controls() {
    const char * menuPrompt = " Would you like to <P>lay or <D>raw a bone or <S>kip or <Q>uit?: ";
    const char * bonePrompt = "Can you  play a bone? (y/n): ";

    char command;
    while (status) {
        get_playable_bones();
        group[turn].give_name();
        cout << "'s current hand: " << endl;
        group[turn].display_hand();
        cout << endl;
        group[turn].give_name();

        command = getChar((char*) menuPrompt);
        switch (command) {
            case 'd':
                skip = 0;
                group[turn].draw_card(gYard);
                cout << "Here is your new hand:" << endl;
                group[turn].display_hand();
                if (getChar((char*) bonePrompt) == 'y') {
                    complete_play();
                } else {
                    turn = (turn + 1) % (numberPlayers);
                }
                break;
            case 'p':
                skip = 0;
                complete_play();
                status = outOfCards();
                if (!status) {
                    status = false;
                }
                break;
            case 'q':
                return 1;
            case 's':
                skip++;
                if (skip == this->numberPlayers) {
                    status = this->determine_winner();
                    status = false;
                } else {
                    turn = (turn + 1) % (numberPlayers);
                }
                break;
            default:
                cout << "Please give a valid command" << endl;
                controls();
                break;
        }
    }
    return 1;
}

int Game::complete_play() {
    const char * firstPrompt = "Please give first number on the bone: ";
    const char * secondPrompt = "Please give second number on the bone: ";
    const char * failedPrompt = "This bone cannot be played! Would you like to try again(y/n): ";

    Bone * temp;
    int top = 0, bottom = 0;

    top = this->getInt((char*) firstPrompt);

    bottom = this->getInt((char*) secondPrompt);

    vector <int> numbers;

    int something = this->gField->determine_playable(numbers);
    if (numbers.size() > 0) {
        bool found = false;
        for (auto it = numbers.begin(); it != numbers.end(); it++) { // size is not declared
            if ((top != (*it)) && (bottom != (*it))) {
                found = true;
            }
        }
        if (!found) {
            if (getChar((char*) failedPrompt) == 'n') {
                return -1;
            } else {
                complete_play();
            }
        }
    } else if ((top != something) && (bottom != something)) {
        if (getChar((char*) failedPrompt) == 'n') {
            return -1;
        } else {
            complete_play();
        }
    }

    if (group[turn].play_card(temp, top, bottom)) {
        gField -> recieve_bone(temp);
        turn = (turn + 1) % (numberPlayers);
        delete temp;
    } else {
        cout << "Please provide valid domino numbers and try again." << endl;
    }

    return -1;
}

int Game::get_playable_bones() {
    if (gField) {
        vector<int> play_num;
        int highest = this->gField->determine_playable(play_num);
        if (highest >= 0)
            cout << "The current double that can be played off of is: " << highest << endl;
        else {
            cout << "playable numbers: ";
            for (auto it = play_num.begin(); it != play_num.end(); it++) { // size is not declared
                cout << (*it) << " ";
            }
            cout << endl;
        }
    }
    return 1;
}

void Game::compare_doubles() {
    int index = 0;
    int highestDouble = 0;

    for (int i = 0; i < this->numberPlayers; i++) {
        if (group[i].highest_double() > highestDouble) {
            highestDouble = group[i].highest_double();
            index = i;
        }
    }
    if (!group[index].isNull()) {
        Bone * tmp = NULL;
        int highDouble = group[index].highest_double();
        int result = group[index].play_card(tmp, highDouble, highDouble);
        group[index].give_name();
        cout << " has the highest double and plays first on a double: " << highDouble << endl;
        if (result != 0) {
            if (tmp) {
                this->gField = new Field(highDouble);
                delete tmp;
            }
        }
    }
}

int Game::get_players_card(int top, int bot) {
    if (!group[turn].isNull()) {
        Bone * tmp = NULL;
        int result = group[turn].play_card(tmp, top, bot);
        if (result != 0) {
            if (tmp) {

                //  gField->recieve_bone(tmp);
                delete tmp;
            }
        }
    }
    return 0;
}

int Game::determine_winner() {
    int lowestScore = 99;
    int PlayerIndex = 0;

    for (int i = 0; i < this->numberPlayers; i++) {
        if (group[i].calculate_score() < lowestScore) {
            lowestScore = group[i].calculate_score();
            PlayerIndex = i;
        }
    }

    cout << "Player ";
    group[PlayerIndex].give_name();
    cout << " won with a score of " << lowestScore;
    return false;
}

int Game::outOfCards() {
    for (int i = 0; i < numberPlayers; i++) {
        if (group[i].isNull()) {
            group[i].give_name();
            cout << " Wins!" << endl;
            for (int i = 0; i < numberPlayers; i++) {
                group[i].give_name();
                cout << "'s score is: " << group[i].calculate_score() << endl;
            }
            return false;
        }
    }
    return true;
}