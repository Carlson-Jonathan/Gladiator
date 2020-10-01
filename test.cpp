#include <iostream>
#include "character.h"
using namespace std;


int main() {


	Character player("Stinky", true);
	player.setWeapon("Battle Axe");
    player.getWeapon()->displayStats();

	player.setArmor("ImmuneST");

	player.getArmor()->displayStats();



	return 0;
}