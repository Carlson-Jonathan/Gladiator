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
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Weapon {
public:

   // Player weapon
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
      this->speed =             weapons[weaponType].second.first[2];
      this->canStun =           weapons[weaponType].second.first[4];
      this->isSharp =           ((stab >= 0.4) || (slash >= 0.5));
   }

   // Custom monster weapon damage
   Weapon(pair<pair<vector<string>, vector<bool>>, 
          pair<vector<short>, vector<float>>> newMonsterWeapon) {
       this->actionDescription = newMonsterWeapon.first.first[0];
       this->minDamage =         newMonsterWeapon.second.first[4];
       this->rangeDamage =       newMonsterWeapon.second.first[5];
       this->crush =             newMonsterWeapon.second.second[0];
       this->chop =              newMonsterWeapon.second.second[1];
       this->slash =             newMonsterWeapon.second.second[2];
       this->stab =              newMonsterWeapon.second.second[3];
       this->isSharp =           ((stab >= 0.4) || (slash >= 0.5));
       this->venomous =          newMonsterWeapon.second.first[6];
       this->canStun =           newMonsterWeapon.second.first[7];
   }

   ~Weapon() {}

   /****************************************************************************
   * void randomDamageTypes(short[])
   * Generates random short damage values for crush/chop/slash/stab based on the
   * min/range damage range.
   ****************************************************************************/
   void getRandomDamageTypes() {

      srand(time(0));
      short baseDamage = rand() % rangeDamage + minDamage;

      damageTypes[0] = ceil(baseDamage * crush);
      damageTypes[1] = ceil(baseDamage * chop);
      damageTypes[2] = ceil(baseDamage * slash);
      damageTypes[3] = ceil(baseDamage * stab);
   }


   string 
      name = "attack",
      actionDescription = " attacks ";

   // Damage amount
   short 
      minDamage,
      rangeDamage,
      maxMulti,
      speed,          // Adds to player's base initiative. 
      venomous,       // Slows base initiative during combat.
      canStun,        // Adds to running initiative during combat.
      damageTypes[4], // Crush, Chop, Slash, Stab values
      percision;      // Determines how likely an attack is to miss.

   // Damage Type
   float 
      crush,
      chop,
      slash,
      stab;

   bool 
      burn = false,
      isSharp = false,     // Bleed
      isBlunt = false,     // Stun
      blind = false,
      isCold = false,
      canParry = false;

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