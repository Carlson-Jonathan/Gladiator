/******************************************************************************
* hero.h
* Author: Jonathan Carlson
* Description:
*    Generates a character object. Accepts weapon objects from weapon class.
******************************************************************************/
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "weapon.h"
#include "armor.h"
//#include "monsters.cpp"
using namespace std;

class Character {
public:

   Character() {}
   Character(string newMonster);
   Character(string name, bool hero);

   // Setters
   void setHitPoints(short change);
   void setBloodPoints(short change);
   void setEssencePoints(short change);
   void setWeapon(string weaponType);
   void setWeapon(string name, short min, short range, float cr, float ch, 
      float sl, float st, short slow);
   void setOffhand(string weaponType);
   void setOffhand(string name, short min, short range, float cr, float ch, 
      float sl, float st, short slow);
   void setArmor(string name);

   // Functions
   void displayStats();
   void generateMonstersList();

   string 
      name;

   short
      minDamage = 0, 
      rangeDamage = 0,
      hitPoints = 1000,
      bloodPoints = 1000,
      essencePoints = 1000,
      initiative = 100, // Higher is slower
      strength = 100,
      isBleeding = 0;

   bool 
      isDefending = false,
      isHero = false;

   vector<string> monsters;

   Weapon* weapon;
   Weapon* offhand;

   Armor* armor;
   
   #include "monsters.cpp"

};

#endif // CHARACTER_H
