#include "character.h"

/*******************************************************************************
* Character Class Constructors:
*******************************************************************************/
// Generate new monster. Is also the default constructor.
Character::Character(string newMonster) {
   // If no monster provided, select one at random.
   if(newMonster == "Random") {
      if (!monsters.size()) generateMonstersList();
      int x = rand() % monsters.size();
      newMonster = monsters[x];
      cout << "\t\tA " << newMonster << " appears!\n";
   }

   this->name =                newMonster;
   this->maxHitPoints =        monster[newMonster].second.first[0];
   this->maxBloodPoints =      monster[newMonster].second.first[1];
   this->maxEssencePoints =    monster[newMonster].second.first[2];
   this->initiative =          monster[newMonster].second.first[3];
   this->isHazardous =         monster[newMonster].second.first[8];
   this->runningInitiative =   initiative;
   this->hitPoints =           maxHitPoints; 
   this->bloodPoints =         maxBloodPoints; 
   weapon =                    new Weapon(monster[newMonster]);
   armor =                     new Armor(monster[newMonster]);
   essencePoints =             maxEssencePoints;
   this->percision =           weapon->percision;
   this->evasion =             monster[newMonster].second.first[10];
}

// Setup initial hero character.
Character::Character(string name, bool hero) {
   this->name = name;
   this->isHero = hero;
}

/*******************************************************************************
* Character Class Setters:
*******************************************************************************/
void Character::setHitPoints(short change) {
   hitPoints += change;
   if(hitPoints < 0)
      hitPoints = 0;
   if(hitPoints > maxHitPoints)
      hitPoints = maxHitPoints;
}

void Character::setBloodPoints(short change) {
   bloodPoints += change;
   if(bloodPoints < 0)
      bloodPoints = 0;
   if(bloodPoints > maxBloodPoints)
      bloodPoints = maxBloodPoints;	
}

void Character::setEssencePoints(short change) {
   essencePoints += change;
   if(essencePoints < 0)
      essencePoints = 0;
   if(essencePoints > maxEssencePoints)
      essencePoints = maxEssencePoints;	
}

void Character::setWeapon(string weaponType) {
  weapon = new Weapon(weaponType);
  initiative += weapon->speed;
  runningInitiative = initiative;
}

void Character::setOffhand(string weaponType) {offhand = new Weapon(weaponType);}
void Character::setArmor(string name) { 
   armor = new Armor(name);
   this->evasion += armor->evade;
}

/*******************************************************************************
* void generateMonstersList()
* Iterates through the map of monsters and saves all names to a vector.
*******************************************************************************/
void Character::generateMonstersList() {
      for(auto & i : monster)
         monsters.push_back(i.first);
}

/*******************************************************************************
* void displayStats()
* Used mostly for testing purposes. Shows Character object's stats.
*******************************************************************************/
void Character::displayStats() {
  cout << name << " stats:\n"
       << "Hit Points:\t"     << hitPoints     << "\n"
       << "Blood Points\t"    << bloodPoints   << "\n"
       << "Essence Points:\t" << essencePoints << "\n\n";
}

