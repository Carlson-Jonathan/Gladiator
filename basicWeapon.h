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
      this->crush =             weapons[weaponType].second.second[0];
      this->chop =              weapons[weaponType].second.second[1];
      this->slash =             weapons[weaponType].second.second[2];
      this->stab =              weapons[weaponType].second.second[3];
   }

   // Getters
   string getName()       {return name;}
   string getAction()     {return actionDescription;}
   short getMinDamage()   {return minDamage;}
   short getRangeDamage() {return rangeDamage;}
   float getCrush()       {return crush;}
   float getChop()        {return chop;}
   float getSlash()       {return slash;}
   float getStab()        {return stab;}

   // Setters
   void setAction(string action)          {this->actionDescription = action;}
   void setMinDamage(short minDamage)     {this->minDamage = minDamage;}
   void setRangeDamage(short rangeDamage) {this->rangeDamage = rangeDamage;}
   void setCrush(float crush)             {this->crush = crush;}
   void setChop(float chop)               {this->chop = chop;}
   void setSlash(float slash)             {this->slash = slash;}
   void setStab(float stab)               {this->stab = stab;}

   ~BasicWeapon() {}

   void displayStats() {
      cout << "Weapon: " << name << "\n"
           << "Damage: " << minDamage << " - " 
           << (minDamage + rangeDamage) << "\n"
           << "Crush: "	<< crush << "\n"
           << "Chop: "  << chop  << "\n"
           << "Slash: " << slash << "\n"
           << "Stab: "  << stab  << "\n" << endl;
   }

protected:	
   string name,
      actionDescription = " attacks ";

   // Damage amount
   short minDamage,
         rangeDamage;

   // Damage Type
   float crush,
         chop,
         slash,
         stab;

   #include "weapons.cpp"
   
};

#endif // BASICWEAPONS_H