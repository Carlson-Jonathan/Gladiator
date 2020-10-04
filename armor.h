/*******************************************************************************
* armor.h
* Author: Jonathan Carlson
* Description:
*    Contains armor class with a list of armors and their statistics.
*******************************************************************************/
#ifndef ARMOR_H
#define ARMOR_H
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Armor {
public:

   Armor() {}
   ~Armor() {}

   // Player's armor (see 'armors.cpp').
   Armor(string name) {
      this->name =         name;
      this->weight =       armor[name].second.first[0];
      this->volume =       armor[name].second.first[1];
      this->defencePower = armor[name].second.first[2];
      this->crush =        armor[name].second.second[0];
      this->chop =         armor[name].second.second[1];
      this->slash =        armor[name].second.second[2];
      this->stab =         armor[name].second.second[3];
   }

   // Custom monster armor (see 'monsters.cpp').
   Armor(pair<pair<vector<string>, vector<bool>>, pair<vector<short>, 
         vector<float>>> monsterArmor) {
      this->crush = monsterArmor.second.second[4];
      this->chop =  monsterArmor.second.second[5];
      this->slash = monsterArmor.second.second[6];
      this->stab =  monsterArmor.second.second[7];
   }

   string name;
   short weight, // Affects turn speed
         volume,
         defencePower = 100;

   // Physical Defence values
   float crush,
         chop,
         slash,
         stab;

   // Elemental Defence Values
   float fire,
         air, 
         water,
         shock;

   #include "armors.cpp"

};
#endif // ARMOR_H