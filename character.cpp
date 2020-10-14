#include "character.h"

/*******************************************************************************
* Character Class Constructors:
*******************************************************************************/

/*****************************************
* Generates Monster
/****************************************/
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
   essencePoints =             maxEssencePoints;

   weapon =                    new Weapon(monster[newMonster]);
   this->percision =           weapon->percision;

   armor =                     new Armor(monster[newMonster]);
   this->evasion =             monster[newMonster].second.first[10];
}

/*****************************************
* Generates Hero
/****************************************/
Character::Character(string name, bool hero) {
   this->name = name;
   this->isHero = hero;
   this->weapon = new Weapon;
   this->armor = new Armor;
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
  if(weapon != NULL) delete weapon;  
  weapon = new Weapon(weaponType);
  initiative += weapon->speed;
  runningInitiative = initiative;
}

void Character::setOffhand(string weaponType) {offhand = new Weapon(weaponType);}

void Character::setArmor(string name) { 
   if(armor != NULL) delete armor;
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

/****************************************************************************
* void applyDefendBonuses()
* Takes the bonus values granted to characters when defending, and applies
* them to their weapons, armor and character stats;
****************************************************************************/
void Character::applyDefendBonuses() {
   weapon->criticalChance /= weapon->criticalBonus;
   this->percision += weapon->percisionBonus;
   this->evasion += armor->evadeBonus;
   armor->defencePower += armor->defendBonus;
}

/****************************************************************************
* void removeDefendBonuses()
* Removes all bonuses granted by defending.
****************************************************************************/
void Character::removeDefendBonuses() {
   weapon->criticalChance *= 2;
   this->percision -= weapon->percisionBonus;
   this->evasion -= armor->evadeBonus;
   armor->defencePower -= armor->defendBonus;
}