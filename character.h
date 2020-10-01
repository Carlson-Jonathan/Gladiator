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
   void setArmor(string name) {armor = new AdvancedArmor(name);}

   // Functions
   void displayStats();
   void generateMonstersList();

   // Make bare fists a weapon
   short minDamage = 0, rangeDamage = 0;

private:
   string name;

   short
      hitPoints = 800,
      bloodPoints = 800,
      essencePoints = 800,
      initiative = 100, // Higher is slower
      strength = 100,
      bleeding = 0;

   bool defending = false,
        ishero = false;

   vector<string> monsters;

   AdvancedWeapon* weapon;
   AdvancedWeapon* offhand;
   AdvancedArmor* armor;

   /***************************************************************************
   * Monster character list w/stats.
   *    Stats Description:
   *       Descriptives: Monster Name, Weapon Type, Attack Description
   *       Stats: HP, BP, EP, Slow, Min Damage, Damage Range
   ***************************************************************************/
   map<string, pair<vector<string>, vector<short>>> monster = {
   {"Skeleton", {{ "Skeleton", "Pure Slash", " claws at " }, 
                 { 300, 500, 150, 40, 30, 20 }}},
   {"Slime",    {{ "Slime", "Pure Crush", " spits at " },   
                 { 800, 500, 350, 190, 100, 50 }}},
   {"Snake",    {{ "Cobra", "Pure Stab", " strikes at " },
                 { 300, 500, 250, 40, 100, 50 }}},
   {"Wolf",     {{ "Spider Wolf", "Pure Chop", " bites at " },
                 { 400, 500, 600, 20, 10, 10 }}},
   {"GiantWasp",{{ "Giant Wasp", "Pure Stab", " swoops at " },
                 { 350, 500, 650, 40, 30, 20 }}},
   {"Zombie",   {{ "Zombie", "Pure Crush", " hurls itself at "},
                 { 800, 500, 500, 190, 100, 50 }}}
   };

};

#endif // CHARACTER_H
