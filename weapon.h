/******************************************************************************
* weapon.h
* Author: Jonathan Carlson
* Description:
*    Contains the weapon class with a list of weapons and their statistics.
******************************************************************************/
#ifndef WEAPON_H
#define WEAPON_H
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Weapon {
public:

   // Constructors
   Weapon() {}
   Weapon(string weaponType) {
      this->name =              weaponType;
      this->actionDescription = weapons[weaponType].first;
      this->minDamage =         weapons[weaponType].second.first[0];
      this->rangeDamage =       weapons[weaponType].second.first[1];
      this->crush =             weapons[weaponType].second.second[0];
      this->chop =              weapons[weaponType].second.second[1];
      this->slash =             weapons[weaponType].second.second[2];
      this->stab =              weapons[weaponType].second.second[3];
      this->sharp = ((stab >= 0.4) || (slash >= 0.5));
   }

   // Custom monster damage
   Weapon(string attack, short min, short range, float stab, 
    float crush, float slash, float chop, short slow) {
       this->actionDescription = attack;
       this->minDamage = min;
       this->rangeDamage = range;
       this->crush = crush;
       this->chop = chop;
       this->slash = slash;
       this->stab = stab;
       this->slow = slow;
   }

   ~Weapon() {}

   string 
      name,
      actionDescription = " attacks ";

   // Damage amount
   short 
      minDamage,
      rangeDamage,
      maxMulti;

   // Damage Type
   float 
      crush,
      chop,
      slash,
      stab;

   bool 
      burn = false,
      sharp = false,
      venom = false,
      stun = false,
      blind = false,
      slow = false,
      freeze = false,
      parry = false;

   void displayStats() {
      cout << "Weapon: " << name << "\n"
           << "Damage: " << minDamage << " - " 
           << (minDamage + rangeDamage) << "\n"
           << "Crush: " << crush << "\n"
           << "Chop: "  << chop  << "\n"
           << "Slash: " << slash << "\n"
           << "Stab: "  << stab  << "\n" << endl;
   }

   // List of all pre-set weapons
   #include "weapons.cpp"
   
};

#endif // BASICWEAPONS_H