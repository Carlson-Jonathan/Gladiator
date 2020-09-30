#include <iostream>
#include "character.h"
using namespace std;


int main() {

	Character monster;

    cout << monster.getName() << endl;
 	monster.getWeapon()->displayStats();


	return 0;
}