/******************************************************************************
* advancedWeapon.h
* Author: Jonathan Carlson
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
      this->sharp = ((stab >= 0.4) || (slash >= 0.5));
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
   bool isSharp()       {return sharp;}
   bool isHeavy()       {return stun;}
   bool isBright()      {return blind;}
   bool isParalyzing()  {return slow;}
   bool isVenomous()    {return venom;}
   bool isCold()        {return freeze;}
   bool isSafe()        {return parry;}

   // Setters
   void setMaxMulti(short maxMulti)   {this->maxMulti = maxMulti;}
   void setBurn(bool burn)            {this->burn = burn;}
   void setBleed(bool sharp)          {this->sharp = sharp;}
   void setVenom(bool venom)          {this->venom = venom;}
   void setStun(bool stun)            {this->stun = stun;}
   void setBlind(bool blind)          {this->blind = blind;}
   void setSlow(bool slow)            {this->slow = slow;}
   void setFreeze(bool freeze)        {this-> freeze = freeze;}
   void setParry(bool parry)          {this-> parry = parry;}

private:

   // Special Damage Modifiers
   bool burn = false,
        sharp = false,
        venom = false,
        stun = false,
        blind = false,
        slow = false,
        freeze = false,
        parry = false;

   short maxMulti;

};

#endif // ADVANCEDWEAPONS_H