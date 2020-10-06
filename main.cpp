/******************************************************************************
* main.cpp
* Author Jonathan Carlson
* Description:
*    Main driver.
******************************************************************************/
#include <iostream>
#include "combat.h"

int main() {

   cout << "\tName your hero: ";
   string name;
   getline(cin, name);
   Character player(name, true);

   // Param1 creates player object. Param 2 = type of monster. Param3 = debug mode.
   combat(player, "Wolf", 0);

   cout << "\n\n>> End of Program. <<" << endl;

   return 0;
}