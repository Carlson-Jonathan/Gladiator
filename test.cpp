#include <iostream>
#include "character.h"
using namespace std;


int main() {


	Character player("Stinky", true);
	player.setWeapon("Battle Axe");
    player.weapon->displayStats();

	player.setArmor("ImmuneST");

	player.armor->displayStats();



	return 0;
}