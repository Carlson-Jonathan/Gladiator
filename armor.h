/******************************************************************************
* armor.h
* Author: Jonathan Carlson
* Description:
*    Contains armor class with a list of armors and their statistics.
******************************************************************************/
#ifndef ARMOR_H
#define ARMOR_H
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Armor {
public:

   Armor() {}
   Armor(string name) {
      this->name = name;
      this->weight = armor[name].second.first[0];
      this->volume = armor[name].second.first[1];
      this->defencePower = armor[name].second.first[2];
      this->crush = armor[name].second.second[0];
      this->chop = armor[name].second.second[1];
      this->slash = armor[name].second.second[2];
      this->stab = armor[name].second.second[3];
      this->damageReduce = armor[name].second.second[4];
   }

   void displayStats() {
      cout << "Armor:\t\t" << name << "\n"
           << "Weight:\t\t" << weight  << "\n"
           << "Volume:\t\t" << volume << "\n"
           << "Defence Power:\t" << defencePower << "\n"
           << "Crush:\t\t" << crush << "\n"
           << "Chop:\t\t" << chop << "\n"
           << "Slash:\t\t" << slash << "\n"
           << "Stab:\t\t" << stab << "\n"
           << "Reduction:\t" << damageReduce << "\n\n";
   }

   string name;
   short weight, // Affects turn speed
         volume,
         defencePower;

   // Physical Defence values
   float crush,
         chop,
         slash,
         stab,
         damageReduce;

   // Elemental Defence Values
   float fire,
         air, 
         water,
         shock;

   #include "armors.cpp"

};
#endif // ARMOR_H