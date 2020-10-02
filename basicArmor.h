/******************************************************************************
* basicArmor.h
* Author: Jonathan Carlson
* Description:
*    Contains basicArmor class with a list of basicWeapon and their statistics.
******************************************************************************/
#ifndef BASICARMOR_H
#define BASICARMOR_H
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class BasicArmor {
public:

   BasicArmor() {}
   BasicArmor(string name) {
      this->name = name;
      this->weight = armor[name].second.first[0];
      this->volume = armor[name].second.first[1];
      this->defencePower = armor[name].second.first[2];
      this->crush = armor[name].second.second[0];
      this->chop = armor[name].second.second[1];
      this->slash = armor[name].second.second[2];
      this->stab = armor[name].second.second[3];
      this->damageReduce = armor[name].second.second[4];
   }

   // Getters
   float getCrush()        {return crush;}
   float getChop()         {return chop;}
   float getSlash()        {return slash;}
   float getStab()         {return stab;}
   float getDamageReduce() {return damageReduce;}
   short getWeight()       {return weight;}
   short getVolume()       {return volume;}
   short getDefencePower() {return defencePower;}


   // Setters
   void setWeight(short weight)   {this->weight = weight;}
   void getVolume(short volume)   {this->volume = volume;}
   void setDefencePower(short db) {this->defencePower = db;}
   void setCrush(float crush)     {this->crush = crush;}
   void setChop(float chop)       {this->chop = chop;}
   void setSlash(float slash)     {this->slash = slash;}
   void setStab(float stab)       {this->stab = stab;}
   void setDamageReduce(float dr) {this->damageReduce = dr;}

   void displayStats() {
      cout << "Armor:\t\t" << name << "\n"
           << "Weight:\t\t" << weight  << "\n"
           << "Volume:\t\t" << volume << "\n"
           << "Defence Power:\t" << defencePower << "\n"
           << "Crush:\t\t" << crush << "\n"
           << "Chop:\t\t" << chop << "\n"
           << "Slash:\t\t" << slash << "\n"
           << "Stab:\t\t" << stab << "\n"
           << "Reduction:\t" << damageReduce << "\n\n";
   }

protected:
   string name;
   short weight, // Affects turn speed
         volume,
         defencePower;

   // Physical Defence values
   float crush,
         chop,
         slash,
         stab,
         damageReduce;

   // Elemental Defence Values
   float fire,
         air, 
         water,
         shock;

   #include "armors.cpp"

};
#endif // BASICARMOR_H