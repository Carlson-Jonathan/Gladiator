/******************************************************************************
* main.cpp
* Author Jonathan Carlson
* Created: September 2020
* Description:
*    Main driver.
******************************************************************************/
#include <iostream>
#include "combat.h"

int main() {

   cout << "\tName your hero: ";
   string name;
   getline(cin, name);
   Character player(name);

   combat(player);

   cout << "\n\n>> End of Program. <<" << endl;

   return 0;
}