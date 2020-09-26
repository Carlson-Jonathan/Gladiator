/******************************************************************************
* advancedWeapon.h
* Author: Jonathan Carlson
* Last Updated: September 2020
* Description:
*    Contains advancedWeapon class with a list of advancedWeapon and their 
* statistics.
******************************************************************************/
#ifndef ADVANCEDWEAPON_H
#define ADVANCEDWEAPON_H
#include "basicWeapon.h"

class AdvancedWeapon : public BasicWeapon {

public:

   AdvancedWeapon() {}
   AdvancedWeapon(string weaponType) {
      this->name =      weaponType;
      this->actionDescription = weapons[weaponType].first;
      this->minDamage = weapons[weaponType].second.first[0];
      this->rangeDamage = weapons[weaponType].second.first[1];
      this->stab =      weapons[weaponType].second.second[0];
      this->crush =     weapons[weaponType].second.second[1];
      this->slash =     weapons[weaponType].second.second[2];
      this->chop =      weapons[weaponType].second.second[3];
   }

   // Custom monster damage
   AdvancedWeapon(string attack, short min, short range, float stab, 
   	float crush, float slash, float chop, short slow) {
       this->actionDescription = attack;
       this->minDamage = min;
       this->rangeDamage = range;
       this->stab = stab;
       this->crush = crush;
       this->slash = slash;
       this->chop = chop;
       this->slow = slow;
   }

   // Getters
   short getMaxMulti()  {return maxMulti;}
   bool isFlaming()     {return burn;}
   bool isSharp()       {return bleed;}
   bool isHeavy()       {return stun;}
   bool isBright()      {return blind;}
   bool isParalyzing()  {return slow;}
   bool isPoisonous()   {return poison;}
   bool isCold()        {return freeze;}
   bool isSafe()        {return parry;}

   // Setters
   void setMaxMulti(short maxMulti)   {this->maxMulti = maxMulti;}
   void setBurn(bool burn)            {this->burn = burn;}
   void setBleed(bool bleed)          {this->bleed = bleed;}
   void setPoison(bool poison)        {this->poison = poison;}
   void setStun(bool stun)            {this->stun = stun;}
   void setBlind(bool blind)          {this->blind = blind;}
   void setSlow(bool slow)            {this->slow = slow;}
   void setFreeze(bool freeze)        {this-> freeze = freeze;}
   void setParry(bool parry)          {this-> parry = parry;}

   // ~AdvancedWeapon() {cout << "Deleting weapon object...";}

private:

   // Special Damage Modifiers
   bool burn = false,
        bleed = false,
        poison = false,
        stun = false,
        blind = false,
        slow = false,
        freeze = false,
        parry = false;

   short maxMulti;

};

#endif // ADVANCEDWEAPONS_H