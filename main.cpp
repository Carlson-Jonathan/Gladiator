/*******************************************************************************
* main.cpp
* Author Jonathan Carlson
* Description:
*    Main driver.
*******************************************************************************/
#ifndef MAIN_CPP
#define MAIN_CPP
#include <iostream>
#include <vector>
#include "battle.h"

vector<Character> createCharacters(short numHeroes) {
   vector<Character> heroes;
   for(short i = 0; i < numHeroes; i++) {
      cout << "\tName your hero(s): ";
      string name;
      getline(cin, name);
      Character hero(name, true);
      heroes.push_back(hero);
   }

   return heroes;
}

int main() {

   vector<Character> heroes = createCharacters(3);

   //   Param 1 = create player object.
   //   Param 2 = type of monster. 
   //   Param 3 = toggles debug mode.
   //   Param 4 = Number of extra monsters per combat.
   {Battle battle(heroes, "Random", 0, 4);}

   cout << "\n\n>> End of Program. <<" << endl;

   return 0;
}

#endif // MAIN_CPP
