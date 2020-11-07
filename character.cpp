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
      cout << "\tA " << newMonster << " appears!\n";
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
   this->precision =           weapon->precision;
   armor =                     new Armor(monster[newMonster]);
   this->evasion =             monster[newMonster].second.first[10];
   this->regeneration =        monster[newMonster].second.first[15];
   setMonsterSpriteAnimation(newMonster);
}

/*****************************************
* Generates Hero
/****************************************/
Character::Character(string name, bool hero) {
   this->name = name;
   this->isHero = hero;
   this->weapon = new Weapon;
   this->armor = new Armor;
   this->runningInitiative = initiative;
   setHeroSpriteAnimation();
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

void Character::setIsBleeding(short clot) {
   isBleeding -= (isBleeding / 10) - clot;
   if(isBleeding < 0)
      isBleeding = 0;
}

void Character::setWeapon(string weaponType) {
  if(weapon != NULL) delete weapon;  
  weapon = new Weapon(weaponType);
  initiative += weapon->speed;
  precision += weapon->precision;
}

void Character::setOffhand(string weaponType) { // Unused
    offhand = new Weapon(weaponType);
}

void Character::setArmor(string name) { 
   if(armor != NULL) delete armor;
   armor = new Armor(name);
   this->evasion += armor->evade;
   this->initiative += armor->speed;
   this->regeneration = armor->regeneration;
}

void Character::setMonsterSpriteAnimation(string newMonster) {
   animatedSprite = new AnimatedSprite(
      monster[newMonster].first.first[1],     // Texture File 
      monster[newMonster].second.first[18],   // x1
      monster[newMonster].second.first[19],   // y1
      monster[newMonster].second.first[20],   // x2
      monster[newMonster].second.first[21],   // y2
      monster[newMonster].second.first[22],   // Number of frames
      monster[newMonster].second.second[11]   // FPS
   );
}

void Character::setHeroSpriteAnimation() {
   animatedSprite = new AnimatedSprite("Images/Heroine.png", 0, 0, 54, 72, 5, 0.11f); 
}

/*******************************************************************************
* void generateMonstersList()
* Iterates through the map of monsters and saves all names to a vector.
*******************************************************************************/
void Character::generateMonstersList() {
      for(auto & i : monster)
         monsters.push_back(i.first);
}
