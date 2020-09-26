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

   cout << "Name your hero: ";
   string name;
   getline(cin, name);
   Character player(name);

   combat(player);

   cout << "End of line." << endl;

   return 0;
}