#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    cout << "CS261 - A02 - Brandan Lasley, Kaleb Striplin, David Platt" << endl << endl;
    Game g;
    g.setup();
    cout << endl << "Please press any key to continue..." << endl;
    cin.get();
    return 0;
}
