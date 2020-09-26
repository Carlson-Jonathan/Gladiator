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
      this->name =        weaponType;
      this->minDamage =   weapons[weaponType].first[0];
      this->rangeDamage = weapons[weaponType].first[1];
      this->stab =        weapons[weaponType].second[0];
      this->crush =       weapons[weaponType].second[1];
      this->slash =       weapons[weaponType].second[2];
      this->chop =        weapons[weaponType].second[3];
   }

   // Getters
   string getName()       {return name;}
   short getMinDamage()   {return minDamage;}
   short getRangeDamage() {return rangeDamage;}
   float getStab()        {return stab;}
   float getCrush()       {return crush;}
   float getSlash()       {return slash;}
   float getChop()        {return chop;}

   // Setters
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
   string name;

   // Damage amount
   short minDamage,
         rangeDamage;

   // Damage Type
   float stab,
         crush,
         slash,
         chop;

   // Damage Distributers
   int dStab,
       dCrush,
       dSlash,
       dChop;

   int slow;

   map<string, pair<vector<int>, vector<float>>> weapons = {
   // {"name", {min damage, damage range}, {stab, crush, slash, chop}}
      {"Broad Sword", {  {40, 20},  {0.3, 0.0, 0.5, 0.2}  }},
      {"Battle Axe",  {  {45, 10},  {0.0, 0.2, 0.1, 0.7}  }},
      {"Spear",       {  {20, 60},  {0.9, 0.0, 0.1, 0.0}  }}
   };
};

#endif // BASICWEAPONS_H