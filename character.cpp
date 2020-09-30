#include "character.h"

/******************************************************************************
* Character Class Constructors:
******************************************************************************/
// Generate new monster. Is also the default constructor.
Character::Character(string newMonster) {
   // If no monster provided, select one at random.
   if(newMonster == "None") {
      generateMonstersList();
      srand(time(0));
      int x = rand() % monsters.size();
      newMonster = monsters[x];
   }

   this->name =          newMonster;
   this->hitPoints =     monster[newMonster].second[0];
   this->bloodPoints =   monster[newMonster].second[1];
   this->essencePoints = monster[newMonster].second[2];
   this->initiative =    monster[newMonster].second[3];
   setWeapon(monster[newMonster].first[1]);
   getWeapon()->setAction(monster[newMonster].first[2]);
   getWeapon()->setMinDamage(monster[newMonster].second[4]);
   getWeapon()->setRangeDamage(monster[newMonster].second[5]);
}

// Setup initial hero character.
Character::Character(string name, bool hero) {
   this->name = name;
   this->ishero = hero;
}

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
void Character::setHitPoints(short change) {
   hitPoints += change;
   if(hitPoints < 0) 
   hitPoints = 0;
}

void Character::setBloodPoints(short change) {
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
  this->bleeding += bleeding;
}

void Character::setWeapon(string name, short min, short range, float st, 
   float cr, float sl, float ch, short slow) {
   weapon = new AdvancedWeapon(name, min, range, st, cr, sl, ch, slow);
}

void Character::setOffhand(string name, short min, short range, float st, 
   float cr, float sl, float ch, short slow) {
   offhand = new AdvancedWeapon(name, min, range, st, cr, sl, ch, slow);
}

/******************************************************************************
* void generateMonstersList()
* Iterates through the map of monsters and saves all names to a vector.
******************************************************************************/
void Character::generateMonstersList() {
      for(auto & i : monster)
         monsters.push_back(i.first);
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