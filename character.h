/*******************************************************************************
* hero.h
* Author: Jonathan Carlson
* Description:
*    Generates a character object. Accepts weapon objects from weapon class.
*******************************************************************************/
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>  // sleep
#include <unistd.h> // sleep
#include <memory> // shared pointers
#include "weapon.h"
#include "armor.h"
using namespace std;

class Character {
public:

   Character() {}
   ~Character() { 
      if(!isHero)
         cout << "\tThe "; 
      cout << name << " drops dead.\n";
   }
   Character(string newMonster);
   Character(string name, bool hero);

   // Setters
   void setHitPoints(short change);
   void setBloodPoints(short change);
   void setEssencePoints(short change);
   void setWeapon(string weaponType);
   void setOffhand(string weaponType);
   void setArmor(string name);

   // Functions
   void displayStats();
   void generateMonstersList();
   void applyDefendBonuses();
   void removeDefendBonuses();

   bool operator < (const Character & other) const {
     return runningInitiative < other.runningInitiative;
   }

   string 
      name;

   short
      maxHitPoints = 1000,
      hitPoints = 1000,
      maxBloodPoints = 1000,
      bloodPoints = 1000,
      maxEssencePoints = 1000,
      essencePoints = 1000,
      strength = 100,
      isBleeding = 0,
      isHazardous = 0,          // Returns damage to an attacker
      initiative = 100,         // Higher is slower
      initiativePenalty = 0,
      evasion = 0,
      evasionPenalty = 0,
      precision = 90,
      precisionPenalty = 0;   

   unsigned short runningInitiative;

   bool 
      isDefending = false,
      isHero = false,
      canRegenerate = false,
      isDead = false;

   vector<string> monsters;

   Weapon* weapon;
   Weapon* offhand;

   Armor* armor;
   
   #include "monsters.cpp"

};

#endif // CHARACTER_H