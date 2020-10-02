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
#include "advancedWeapon.h"
#include "advancedArmor.h"
//#include "monsters.cpp"
using namespace std;

class Character {
public:

   Character() {}
   Character(string newMonster);
   Character(string name, bool hero);

   // Getters
   string getName();
   short getHitPoints();
   short getBloodPoints();
   short getEssencePoints();
   short getInitiative();
   short isBleeding();
   bool isDefending();
   bool isHero();

   AdvancedWeapon* getWeapon();
   AdvancedWeapon* getOffhand();
   AdvancedArmor* getArmor();

   // Setters
   void setHitPoints(short change);
   void setBloodPoints(short change);
   void setEssencePoints(short change);
   void setInitiative(short initiative);
   void setDefending(bool defending);
   void setWeapon(string weaponType);
   void setBleeding(short bleed);
   void setWeapon(string name, short min, short range, float st, float cr, 
      float sl, float ch, short slow);
   void setOffhand(string weaponType);
   void setOffhand(string name, short min, short range, float st, float cr, 
      float sl, float ch, short slow);
   void setArmor(string name);

   // Functions
   void displayStats();
   void generateMonstersList();

   // Make bare fists a weapon
   short minDamage = 0, rangeDamage = 0;

private:
   string name;

   short
      hitPoints = 1000,
      bloodPoints = 1000,
      essencePoints = 1000,
      initiative = 100, // Higher is slower
      strength = 100,
      bleeding = 0;

   bool defending = false,
        ishero = false;

   vector<string> monsters;

   AdvancedWeapon* weapon;
   AdvancedWeapon* offhand;
   AdvancedArmor* armor;
   
   #include "monsters.cpp"

};

#endif // CHARACTER_H
