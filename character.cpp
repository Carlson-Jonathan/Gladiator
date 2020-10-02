#include "character.h"

/******************************************************************************
* Character Class Constructors:
******************************************************************************/
// Generate new monster. Is also the default constructor.
Character::Character(string newMonster) {
   // If no monster provided, select one at random.
   if(newMonster == "Random") {
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
   setArmor(monster[newMonster].first[3]);
   weapon->actionDescription = monster[newMonster].first[2];
   weapon->minDamage = monster[newMonster].second[4];
   weapon->rangeDamage = monster[newMonster].second[5];
}

// Setup initial hero character.
Character::Character(string name, bool hero) {
   this->name = name;
   this->isHero = hero;
}

/******************************************************************************
* Character Class Setters:
******************************************************************************/
void Character::setHitPoints(short change) {
   hitPoints - change < 0 ? hitPoints = 0 : hitPoints += change;
}

void Character::setBloodPoints(short change) {
   bloodPoints < 0 ? bloodPoints = 0: bloodPoints += change;
}

void Character::setEssencePoints(short change) {
   essencePoints < 0 ? essencePoints = 0 : essencePoints += change;
}

void Character::setWeapon(string weaponType) {
   weapon = new Weapon(weaponType);
}

void Character::setWeapon(string name, short min, short range, float cr, 
   float ch, float sl, float st, short slow) {
   weapon = new Weapon(name, min, range, cr, ch, sl, st, slow);
}

void Character::setOffhand(string weaponType) {
   weapon = new Weapon(weaponType);
}

void Character::setOffhand(string name, short min, short range, float cr, 
   float ch, float sl, float st, short slow) {
   offhand = new Weapon(name, min, range, cr, ch, sl, st, slow);
}

void Character::setArmor(string name) {armor = new Armor(name);}

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
       << "Hit Points:\t"     << hitPoints     << "\n"
       << "Blood Points\t"    << bloodPoints   << "\n"
       << "Essence Points:\t" << essencePoints << "\n\n";
}