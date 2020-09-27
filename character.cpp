#include "character.h"

/******************************************************************************
* Character Class Getters:
******************************************************************************/
string Character::getName()             {return name;}   
short Character::getHitPoints()         {return hitPoints;}
short Character::getBloodPoints()       {return bloodPoints;}
short Character::getEssencePoints()     {return essencePoints;}
short Character::getInitiative()        {return initiative;}
short Character::isBleeding()           {return bleeding;}
bool Character::isDefending()           {return defending;}
bool Character::isHero()                {return ishero;}
AdvancedWeapon* Character::getWeapon()  {return weapon;}
AdvancedWeapon* Character::getOffhand() {return weapon;}

/******************************************************************************
* Character Class Setters:
******************************************************************************/
void Character::setHitPoints(short change)     {
   hitPoints += change;
   if(hitPoints < 0) 
   hitPoints = 0;
}

void Character::setBloodPoints(short change)   {
   bloodPoints += change;
   if(bloodPoints < 0) bloodPoints = 0;  
}

void Character::setEssencePoints(short change) {
   essencePoints += change;
   if(essencePoints < 0) essencePoints = 0;
}

void Character::setInitiative(short change) {
	initiative += change;
}

void Character::setDefending(bool defending) {
   this->defending = defending;
}

void Character::setWeapon(string weaponType) {
   weapon = new AdvancedWeapon(weaponType);
}

void Character::setOffhand(string weaponType) {
   weapon = new AdvancedWeapon(weaponType);
}

void Character::setBleeding(short bleeding) {
  this->bleeding = bleeding;
}

void Character::setWeapon(string name, short min, short range, float st, float cr, 
   float sl, float ch, short slow) {
   weapon = new AdvancedWeapon(name, min, range, st, cr, sl, ch, slow);
}
void Character::setOffhand(string name, short min, short range, float st, float cr, 
   float sl, float ch, short slow) {
   offhand = new AdvancedWeapon(name, min, range, st, cr, sl, ch, slow);
}

/******************************************************************************
* void displayStats()
* Used mostly for testing purposes. Shows Character object's stats.
******************************************************************************/
void Character::displayStats() {
  cout << name << " stats:\n"
       << "Hit Points:\t"     << getHitPoints()     << "\n"
       << "Blood Points\t"    << getBloodPoints()   << "\n"
       << "Essence Points:\t" << getEssencePoints() << "\n\n";
}
