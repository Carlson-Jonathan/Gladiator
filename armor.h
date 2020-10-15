/*******************************************************************************
* armor.h
* Author: Jonathan Carlson
* Description:
*    Contains armor class with a list of armors and their statistics.
*******************************************************************************/
#ifndef ARMOR_H
#define ARMOR_H
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
using namespace std;

class Armor {
public:

   Armor() { this->name = "NULL"; }
   ~Armor() { /*cout << "\tThe armor explodes into bits.\n";*/ }

   /*****************************************
   * Player armor constructor
   *****************************************/
   Armor(string name) {
      this->name =         name;
      this->weight =       armor[name].second.first[0];
      this->volume =       armor[name].second.first[1];
      this->defencePower = armor[name].second.first[2];
      this->crush =        armor[name].second.second[0];
      this->chop =         armor[name].second.second[1];
      this->slash =        armor[name].second.second[2];
      this->stab =         armor[name].second.second[3];
      this->evade =        armor[name].second.first[3];
      this->evadeBonus =   armor[name].second.first[4];
      this->defendBonus =  armor[name].second.first[5];
      this->speed =        armor[name].second.first[6];
      setDamageReduce();
   }

   /*****************************************
   * Monsters' armor constructor
   *****************************************/
   Armor(const auto & monsterArmor) {
      this->name =         "unholy shielding";
      this->crush =        monsterArmor.second.second[4];
      this->chop =         monsterArmor.second.second[5];
      this->slash =        monsterArmor.second.second[6];
      this->stab =         monsterArmor.second.second[7];
      this->evadeBonus =   monsterArmor.second.first[13];
      this->defendBonus =  monsterArmor.second.second[11];
      setDamageReduce();
   }

   /****************************************************************************
   * void setDamageReduce()
   * Divides the total defence power into the 4 relevant catagories.
   ****************************************************************************/
   void setDamageReduce() {
      damageReduce[0] = ceil(defencePower * crush);
      damageReduce[1] = ceil(defencePower * chop);
      damageReduce[2] = ceil(defencePower * slash);
      damageReduce[3] = ceil(defencePower * stab);
   }

   string name;
   short 
      weight = 0, // Affects turn speed
      volume = 0,
      defencePower = 0,
      evade = 0,
      evadeBonus = 0,
      defendBonus = 1, // Multiply this by the defence power.
      speed = 0;
      
   // The percentage of damage reduction to be applied [crush, chop, slash, stab]
   short damageReduce[4];

   // Physical Defence values
   float 
      crush,
      chop,
      slash,
      stab;

   // Elemental Defence Values
   float 
      fire,
      air, 
      water,
      shock;

   #include "armors.cpp"

};
#endif // ARMOR_H