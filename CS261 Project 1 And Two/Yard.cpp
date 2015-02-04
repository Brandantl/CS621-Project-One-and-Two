#include "Yard.h"

Yard::Yard() {
    int top[28] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6}; //These are all of the top nubmer for the cards
    int bot[28] = {0, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 3, 4, 5, 6, 4, 5, 6, 5, 6, 6}; //These are all of the bottom numbers for the cards
    for (int i = 0; i < 28; i++) {
        Bone * aBone = new Bone(top[i], bot[i]); //create the bone
        boneSet.push_back(aBone); //put it in the deck
    }
    shuffle_yard();
}

Yard::~Yard() {
    while (!boneSet.empty()) {
        Bone * tmp;
        tmp = boneSet.back();
        boneSet.pop_back();
        if (tmp) {
            delete tmp;
        }
    }
}

Yard::Yard(const Yard* obj) {
    for (auto it = obj->boneSet.begin(); it != obj->boneSet.end(); it++) {
        Bone * tmp;
        tmp = (*it);
        if (tmp) {
            this->boneSet.push_back(tmp);
        }
    }
}

int Yard::shuffle_yard() {
    for (int i = 0; i < 28; i++) //for extra shuffling 
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(boneSet.begin(), boneSet.end(), std::default_random_engine(seed));
    }
    return 1;
}

bool Yard::deal_bone(Bone *& bone) {
    if (boneSet.size() == 0)
        return false;
    else
        bone = boneSet.back();
    boneSet.pop_back();
    return true;
}

int Yard::empty() {
    if (boneSet.size() == 0) {
        cout << "Deck is empty! Please skip your turn." << endl;
        return 1;
    }
    return 0;
}

int Yard::print() {
    for (auto it = boneSet.begin(); it != boneSet.end(); it++) {
        (*it) -> print();
        cout << " ";
    }
    cout << endl << endl;
    return 1;
}