#include "Field.h"
using namespace std;

Field::Field(int var) : iterations(0), highest_double(0) {
    highest_double = var;
    first_double = var;
}

Field::~Field() {
}

Field::Field(const Field* obj) {
    for (auto it = obj->current_numbers.begin(); it != obj->current_numbers.end(); it++) {
        this->current_numbers.push_back((*it));

    }
    this->first_double = obj->first_double;
    this->highest_double = obj->highest_double;
    this->iterations = obj->iterations;
}

int Field::determine_playable(vector <int> & numbs) {
    if ((highest_double == first_double) && (iterations == 4)) {
        highest_double = -1;
        iterations = 0;
    }
    if ((highest_double != -1) && (highest_double != first_double) && (iterations == 3)) {
        highest_double = -1;
        iterations = 0;
    }
    if (highest_double == first_double && iterations < 4) {
        return first_double;
    } else if (highest_double != -1 && iterations < 3) {
        return highest_double;
    } else if (highest_double == -1) {
        numbs = current_numbers;
        // for (auto it = current_numbers.begin(); it != current_numbers.end(); it++) {
        //    numbs.push_back((*it));
        return -1;
        // }
    }
    return -1; // Must return a number....
}

int Field::recieve_bone(Bone * aBone) {
    if (aBone -> checkDouble()) {
        for (auto it = current_numbers.begin(); it != current_numbers.end(); it++) {
            if ((*it) == aBone -> getTopNum()) {
                current_numbers.erase(it);
                break;
            }
        }
        highest_double = aBone -> getTopNum();
        iterations = 0;
        return 1;
    } else if ((!aBone -> checkDouble()) && (highest_double == -1)) {
        for (auto it = current_numbers.begin(); it != current_numbers.end(); it++) {
            if (aBone -> getTopNum() == (*it)) {
                current_numbers.erase(it);
                current_numbers.push_back(aBone -> getBottomNum());
                break;
            } else if (aBone -> getBottomNum() == (*it)) {
                current_numbers.erase(it);
                current_numbers.push_back(aBone -> getTopNum());
                break;
            }
        }
        return 1;
    } else if ((!aBone -> checkDouble()) && highest_double != -1) {
        if (aBone -> getTopNum() == highest_double) {
            current_numbers.push_back(aBone -> getBottomNum());
            iterations++;
        } else if (aBone -> getBottomNum() == highest_double) {
            current_numbers.push_back(aBone -> getTopNum());
            iterations++;
        }
        return 1;
    }
    return 0;
}
