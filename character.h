/******************************************************************************
* hero.h
* Author: Jonathan Carlson
* Last Updated: September 2020
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

   Character() {
      srand(time(0));
      int x = rand() % monsters.size();
      pair<vector<string>, vector<short>> newMonster = monsters[x];
      this->name =          newMonster.first[0];
      this->hitPoints =     newMonster.second[0];
      this->bloodPoints =   newMonster.second[1];
      this->essencePoints = newMonster.second[2];
      this->initiative =    newMonster.second[3];
      setWeapon(newMonster.first[1]);
      getWeapon()->setAction(newMonster.first[2]);
      getWeapon()->setMinDamage(newMonster.second[4]);
      getWeapon()->setRangeDamage(newMonster.second[5]);
   }

   // Setup initial hero character.
   Character(string name) {
      this->name = name;
      this->ishero = true;
   }
	
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

   // Functions
   void displayStats();

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

   AdvancedWeapon* weapon;
   AdvancedWeapon* offhand;
   AdvancedArmor* armor;    


   /***************************************************************************
   * Monster character list w/stats. 
   *    Stats Description: 
   *       Descriptives: Monster Name, Weapon Type, Attack Description   
   *       Stats: HP, BP, EP, Slow, Min Damage, Damage Range
   ***************************************************************************/
   pair<vector<string>, vector<short>>
   skeleton =  { {"Skeleton", "Pure Slash", " claws at "},  
                 {300, 500, 150, 170, 20, 10} },
   slime =     { {"Slime", "Pure Crush", " spits at "},
                  {800, 500, 350, 170, 20, 10} },
   snake =     { {"Cobra", "Pure Stab", " strikes at "},
                 {300, 500, 250, 174, 20, 10} },
   wolf =      { {"Spider Wolf", "Pure Chop", " bites at "},
                 {400, 500, 600, 170, 20, 10} },
   giantWasp = { {"Giant Wasp", "Pure Stab", " swoops at "}, 
                 {350, 500, 650, 170, 20, 10} },
   zombie =    { {"Zombie", "Pure Crush", " hurls itself at "},      
                 {800, 500, 500, 170, 20, 10} };

   /***************************************************************************
   * Monster custom weapons
   ***************************************************************************/

   vector<pair <vector<string>, vector<short> >> monsters = {
   skeleton, slime, snake, wolf, giantWasp, zombie
   };
};

#endif // CHARACTER_H