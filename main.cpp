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

   combat(player, "Slime");

   cout << "\n\n>> End of Program. <<" << endl;

   return 0;
}