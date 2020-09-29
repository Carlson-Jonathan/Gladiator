/******************************************************************************
* basicWeapon.h
* Author: Jonathan Carlson
* Last Updated: September 2020
* Description:
*    Contains basicWeapon class with a list of basicWeapon and their statistics.
******************************************************************************/
#ifndef BASICWEAPON_H
#define BASICWEAPON_H
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class BasicWeapon {
public:

   // Constructors
   BasicWeapon() {}

   // Set weapon damage
   BasicWeapon(string weaponType) {
      this->name =              weaponType;
      this->actionDescription = weapons[weaponType].first;
      this->minDamage =         weapons[weaponType].second.first[0];
      this->rangeDamage =       weapons[weaponType].second.first[1];
      this->stab =              weapons[weaponType].second.second[0];
      this->crush =             weapons[weaponType].second.second[1];
      this->slash =             weapons[weaponType].second.second[2];
      this->chop =              weapons[weaponType].second.second[3];
   }

   // Getters
   string getName()       {return name;}
   string getAction()     {return actionDescription;}
   short getMinDamage()   {return minDamage;}
   short getRangeDamage() {return rangeDamage;}
   float getStab()        {return stab;}
   float getCrush()       {return crush;}
   float getSlash()       {return slash;}
   float getChop()        {return chop;}

   // Setters
   void setAction(string action)          {this->actionDescription = action;}
   void setMinDamage(short minDamage)     {this->minDamage = minDamage;}
   void setRangeDamage(short rangeDamage) {this->rangeDamage = rangeDamage;}
   void setStab(float stab)               {this->stab = stab;}
   void setCrush(float crush)             {this->crush = crush;}
   void setSlash(float slash)             {this->slash = slash;}
   void setChop(float chop)               {this->chop = chop;}

   ~BasicWeapon() {}

   void displayStats() {
      cout << "Weapon: " << name << "\n"
           << "Damage: " << minDamage << " - " 
           << (minDamage + rangeDamage) << "\n"
           << "Stab: "  << stab  << "\n"
           << "Crush: "	<< crush << "\n"
           << "Slash: " << slash << "\n"
           << "Chop: "  << chop  << "\n" << endl;
   }

protected:	
   string name,
          actionDescription = " attacks ";

   // Damage amount
   short minDamage,
         rangeDamage;

   // Damage Distributers
   short dStab,
         dCrush,
         dSlash,
         dChop,
         slow;
   
   // Damage Type
   float stab,
         crush,
         slash,
         chop;


   map<string, pair<string, pair<vector<short>, vector<float>>>> weapons = {
   // {"name", "combat text", {min damage, damage range}, {stab, crush, slash, chop}}
      {"Broad Sword", {" slashes at ", {  {100, 1},  {0.3, 0.0, 0.5, 0.2}  }}},
      {"Katana",      {" slashes at ", {  {50,  50},  {0.2, 0.0, 0.7, 0.1}  }}},
      {"Battle Axe",  {" chops at ",   {  {45, 110},  {0.0, 0.2, 0.1, 0.7}  }}},
      {"Spear",       {" lunges at ",  {  {100, 1},  {0.9, 0.0, 0.1, 0.0}  }}},
      {"Mace",        {" swings at ",  {  {1,  100},  {0.0, 1.0, 0.0, 0.0}  }}},

      
      // Monster weapons
      {"Pure Stab",   {"",  {  {1, 100},   {1.0, 0.0, 0.0, 0.0}  }}},
      {"Pure Crush",  {"",  {  {1, 100},   {0.0, 1.0, 0.0, 0.0}  }}},
      {"Pure Slash",  {"",  {  {1, 100},   {0.0, 0.0, 1.0, 0.0}  }}},
      {"Pure Chop",   {"",  {  {1, 100},   {0.0, 0.0, 0.0, 1.0}  }}}
   };
};

#endif // BASICWEAPONS_H