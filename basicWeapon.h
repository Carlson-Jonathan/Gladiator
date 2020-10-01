/******************************************************************************
* basicWeapon.h
* Author: Jonathan Carlson
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

   // Damage Type
   float stab,
         crush,
         slash,
         chop;

   #include "weapons.cpp"
   
};

#endif // BASICWEAPONS_H