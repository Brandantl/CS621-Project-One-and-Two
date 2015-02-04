#include "Player.h"

/*
 ================== WARNING! =====================
 * THIS CLASS IS NOW OWNED BY BRANDAN
 * 
 * DO NOT TOUCH IT, I'LL REVERT *ALL* CHANGES.
 * ===============================================
 */

Player::Player() : score(0), player_name("Player") {
    hand = NULL;
    tail = NULL;
}

void Player::setName(string name) {
    player_name = name;
}

Player::~Player() {
    node * curr = hand;
    while (hand) {
        curr = hand->next;
        if (hand->bone) {
            delete hand->bone;
        }
        delete hand;
        hand = curr;
    }
}

Player::Player(const Player* obj) {
    this->player_name = obj->player_name;
    this->score = obj->score;

    if (obj->hand) {
        node * current = obj->hand;
        while (current) {
            if (hand) {
                node * tmp = new node;
                tmp -> bone = current->bone;
                tmp -> next = NULL;
                this->tail->next = tmp;
                tail = tmp->next;
            } else {
                hand = new node;
                hand -> bone = current->bone;
                hand -> next = NULL;
            }
        }
    } else {
        hand = NULL;
        tail = NULL;
    }

}

void Player::give_name() {
    cout << this->player_name;
}

int Player::display_hand() {
    if (hand) {
        node * current = hand;
        while (current) {
            current->bone -> print(); //bone has a print function
            current = current->next;
        }
        cout << endl;
    }
    return 1;
}

int Player::highest_double() {
    int num = -1;
    if (hand) {
        node * current = hand;
        while (current) {
            if (current -> bone -> getDouble() && current -> bone -> getTopNum() > num)
                num = current -> bone -> getTopNum();
            current = current -> next;
        }
    }
    return num;
}

int Player::draw_card(Yard *& yard) {
    if (!yard->empty()) {
        node * current = hand;
        Bone * tmp = NULL;
        if ((hand) && (!current -> bone)) {
            yard->deal_bone(tmp); //yard has a deal card function that gives the bone parameter something to point to
            current -> bone = tmp;
            return 1;
        } else {
            if (hand) {
                while (current -> next) {
                    current = current -> next; //traverse to the last card in the hand (LLL)
                }

                current -> next = new node;
                yard->deal_bone(tmp); //add the card at the end
                current -> next -> bone = tmp;
                current -> next -> next = NULL;
                tail = current -> next;
            } else {
                hand = new node;
                yard->deal_bone(tmp); //add the card at the end
                hand -> bone = tmp;
                hand -> next = NULL;
                tail = hand;
                return 1;
            }
        }

    }
    return 0;
}

int Player::calculate_score() {
    score = 0;
    if (hand) {
        node * current = hand;
        while (current) {
            score = score + current -> bone -> getTopNum() + current -> bone -> getBottomNum();
            current = current -> next; //the score plus the top number plus the bottom number of the current card
        }
    }
    return score;
}

bool Player::isNull() {
    if (!hand) {
        return true;
    }
    return false;
}

int Player::play_card(Bone *& aBone, int top, int bot) {
    // This... do not touch this. Its redundant and it runs extremely well... and I'm OK with that.
    if (hand) {
        node *pPre = NULL, *pDel = NULL;
        if ((hand -> bone -> getTopNum() == top) && (hand -> bone -> getBottomNum() == bot)) {
            aBone = hand -> bone;
            pDel = hand;
            hand = pDel->next;
            delete pDel;
            return 1;
        } else if ((hand -> bone -> getTopNum() == bot) && (hand -> bone -> getBottomNum() == top)) {
            aBone = hand -> bone;
            pDel = hand;
            hand = pDel->next;
            delete pDel;
            return 1;
        }

        pPre = hand;
        pDel = hand->next;

        // traverse the list and check the value of each node
        while (pDel != NULL) {
            if ((pDel -> bone -> getTopNum() == top) && (pDel -> bone -> getBottomNum() == bot)) {
                aBone = pDel -> bone;
                pPre->next = pDel->next;
                if (pDel == tail) {
                    tail = pPre;
                }
                delete pDel;
                return 1;
            } else if ((pDel -> bone -> getTopNum() == bot) && (pDel -> bone -> getBottomNum() == top)) {
                aBone = pDel -> bone;
                pPre->next = pDel->next;
                if (pDel == tail) {
                    tail = pPre;
                }
                delete pDel;
                return 1;
            }
            pPre = pDel;
            pDel = pDel->next;
        }
    }
    return 0;
}
