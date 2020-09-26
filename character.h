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

   // Generates a random monster character
   Character() {
      srand(time(0));
      int x = rand() % monsters.size();
      pair<string, vector<int>> newMonster = monsters[x];
      this->name =          newMonster.first;
      this->hitPoints =     newMonster.second[0];
      this->bloodPoints =   newMonster.second[1];
      this->essencePoints = newMonster.second[2];
   }

   // Setup initial hero character.
   Character(string name) {this->name = name;}
	
   // Getters
   string getName();             
   short getHitPoints();          
   short getBloodPoints();         
   short getEssencePoints();       
   short getInitiative();
   bool isDefending();  

   AdvancedWeapon* getWeapon();
   AdvancedWeapon* getOffhand(); 

   // Setters
   void setHitPoints(short change);
   void setBloodPoints(short change);
   void setEssencePoints(short change);
   void setInitiative(short initiative);
   void setDefending(bool defending);
   void setWeapon(string weaponType);
   void setWeapon(string name, short min, short range, float st, float cr, 
      float sl, float ch, short slow);
   void setOffhand(string weaponType);
   void setOffhand(string name, short min, short range, float st, float cr, 
      float sl, float ch, short slow);

   // Functions
   void displayStats();

   // Make bare fists a weapon
   int minDamage = 0, rangeDamage = 0;

private:
   string name;

   short  
      hitPoints = 1000,
      bloodPoints = 100,
      essencePoints = 100,
      initiative = 100,
      strength = 100;

   bool defending = false;

   AdvancedWeapon* weapon;
   AdvancedWeapon* offhand;
   AdvancedArmor* armor;    


   /***************************************************************************
   * Monster character list w/stats
   ***************************************************************************/
   pair<string, vector<int>> 
   //           Monster Name    HP    BP    EP 
   skeleton =  {"Skeleton",    {200, 1000, 150} },
   slime =     {"Slime",       {800,  275, 350} },
   snake =     {"Cobra",       {300,  200, 250} },
   wolf =      {"Timber Wolf", {400,  300, 600} },
   giantWasp = {"Giant Wasp",  {350,  750, 650} },
   zombie =    {"Zombie",      {800, 1400, 500} };

   vector<pair<string, vector<int>>> monsters = {
   skeleton, slime, snake, wolf, giantWasp, zombie 
   };
};

#endif // CHARACTER_H