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
      this->criticalM =         weapons[weaponType].second.second[4];
      this->criticalC =         weapons[weaponType].second.first[5];
      this->percision +=        weapons[weaponType].second.first[6];
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
       this->criticalM =         newMonsterWeapon.second.second[8];
       this->criticalC =         newMonsterWeapon.second.second[9];
       this->percision =         newMonsterWeapon.second.first[9];
   }

   ~Weapon() {}

   /****************************************************************************
   * bool randomDamageTypes(short[])
   * Generates random short damage values for crush/chop/slash/stab based on the
   * min/range damage range. Also calculates critical strike damage.
   ****************************************************************************/
   bool getRandomDamageTypes() {

      srand(time(0));
      short baseDamage = rand() % rangeDamage + minDamage;
      bool criticalStrike = false; 
      
      if (criticalM) 
         if(!(baseDamage % criticalC)) {     // C = 'Chance'
            baseDamage *= ceil(criticalM);   // M = 'Multiplier'
            criticalStrike = true;  
         }

      damageTypes[0] = ceil(baseDamage * crush);
      damageTypes[1] = ceil(baseDamage * chop);
      damageTypes[2] = ceil(baseDamage * slash);
      damageTypes[3] = ceil(baseDamage * stab);

      if(criticalStrike) return true;

      return false;
   }


   string 
      name = "attack",
      actionDescription = " attacks ";

   // Damage amount
   short 
      minDamage,      // Minimum damage that will be inflicted.
      rangeDamage,    // Range of damage starting with minDamage.
      maxMulti,       // Some weapons may use multiple strikes 
      speed,          // Adds to player's base initiative. 
      venomous,       // Slows base initiative during combat.
      canStun,        // Adds to running initiative during combat.
      damageTypes[4], // Crush, Chop, Slash, Stab values
      percision,      // Determines how likely an attack is to miss.
      criticalC = 0;   // The chance for a critical strike (1 in criticalC)

   // Damage Type
   float 
      crush,
      chop,
      slash,
      stab,
      criticalM = 0; // Critical hit multiplier.

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