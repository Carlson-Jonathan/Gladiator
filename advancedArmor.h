/******************************************************************************
* advancedArmor.h
* Author: Jonathan Carlson
* Description:
*    Contains advancedArmor class with a list of armor and their statistics.
******************************************************************************/
#ifndef ADVANCEDARMOR_H
#define ADVANCEDARMOR_H
#include "basicArmor.h"
using namespace std;

class AdvancedArmor : public BasicArmor {
public:

   AdvancedArmor() {}
   AdvancedArmor(string name) {
      this->name = name;
      this->weight = armor[name].second.first[0];
      this->volume = armor[name].second.first[1];
      this->damageBlock = armor[name].second.first[2];
      this->stab = armor[name].second.second[0];
      this->crush = armor[name].second.second[1];
      this->slash = armor[name].second.second[2];
      this->chop = armor[name].second.second[3];
      this->damageReduce = armor[name].second.second[4];
   }   

   // Getters
   

   // Setters
   


protected:
   


   // Defence values
   

};
#endif // ADVANCEDARMOR_H