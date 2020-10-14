/*******************************************************************************
* main.cpp
* Author Jonathan Carlson
* Description:
*    Main driver.
*******************************************************************************/
#ifndef MAIN_CPP
#define MAIN_CPP
#include <iostream>
#include "battle.h"


int main() {

   cout << "\tName your hero: ";
   string name;
   getline(cin, name);
   Character player(name, true);

   //   Param 1 = create player object.
   //   Param 2 = type of monster. 
   //   Param 3 = toggles debug mode.
   //   Param 4 = Number of extra monsters per combat.
   {Battle battle(player, "Random", 0, 3);}

   cout << "\n\n>> End of Program. <<" << endl;

   return 0;
}

#endif // MAIN_CPP
