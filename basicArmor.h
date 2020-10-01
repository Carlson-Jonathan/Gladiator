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
      this->damageBlock = armor[name].second.first[2];
      this->stab = armor[name].second.second[0];
      this->crush = armor[name].second.second[1];
      this->slash = armor[name].second.second[2];
      this->chop = armor[name].second.second[3];
      this->damageReduce = armor[name].second.second[4];
   }

   // Getters
   float getStab()         {return stab;}
   float getCrush()        {return crush;}
   float getSlash()        {return slash;}
   float getChop()         {return chop;}
   float getDamageReduce() {return damageReduce;}
   short getWeight()       {return weight;}
   short getVolume()       {return volume;}
   short getdamageBlock()  {return damageBlock;}
   

   // Setters
   void setWeight(short weight) {this->weight = weight;}
   void getVolume(short volume) {this->volume = volume;}
   void setDamageBlock(short db) {this->damageBlock = db;}
   void setStab(float stab)   {this->stab = stab;}
   void setCrush(float crush) {this->crush = crush;}
   void setSlash(float slash) {this->slash = slash;}
   void setChop(float chop)   {this->chop = chop;}
   void setDamageReduce(float dr) {this->damageReduce = dr;}

   void displayStats() {
      cout << "Armor:\t\t" << name << "\n"
           << "Weight:\t\t" << weight  << "\n"
           << "Volume:\t\t" << volume << "\n"
           << "Damage Block:\t" << damageBlock << "\n"
           << "Stab:\t\t" << stab << "\n"
           << "Crush:\t\t" << crush << "\n"
           << "Slash:\t\t" << slash << "\n"
           << "Chop:\t\t" << chop << "\n"
           << "Reduction:\t" << damageReduce << "\n";
   }

protected:
   string name;
   short weight, // Affects turn speed
         volume,
         damageBlock;

   // Physical Defence values
   float stab,
         crush,
         slash,
         chop,
         damageReduce;

   // Elemental Defence Values
   float fire,
         air, 
         water,
         shock;

   #include "armors.cpp"

//    map<string, pair<pair<vector<string>, vector<bool>>, pair<vector<short>, vector<float>>>> armor {

//    //  key          Name         ?        ?      ?        Wt   Vol  blk   st   cr   sl   ch   dr
//    {"Padding", {{{"", ""}, {true, false}}, {{100, 200, 20}, {0.1, 0.5, 0.2, 0.2, 0.1 }}}},
//    {"Leather", {{{"", ""}, {true, false}}, {{1, 2, 3}, {0.1, 0.2, 0.3}}}},
//    {"Brigindine", {{{"", ""}, {true, false}}, {{1, 2, 3}, {0.1, 0.2, 0.3}}}},
//    {"Chain", {{{"", ""}, {true, false}}, {{1, 2, 3}, {0.1, 0.2, 0.3}}}},
//    {"Scale", {{{"", ""}, {true, false}}, {{1, 2, 3}, {0.1, 0.2, 0.3}}}},
//    {"Plate", {{{"", ""}, {true, false}}, {{1, 2, 3}, {0.1, 0.2, 0.3}}}},

//    // Monster armors
//    {"ImmuneST", {{{"Chainmail", "str2"}, {true, false}}, {{1, 2, 3}, {0.1, 0.2, 0.3, 0.4, 0.5}}}},
//    {"UmmuneCR", {{{"Chainmail", "str2"}, {true, false}}, {{1, 2, 3}, {0.1, 0.2, 0.3}}}},
//    {"ImmuneSL", {{{"Chainmail", "str2"}, {true, false}}, {{1, 2, 3}, {0.1, 0.2, 0.3}}}},
//    {"ImmuneCH", {{{"Chainmail", "str2"}, {true, false}}, {{1, 2, 3}, {0.1, 0.2, 0.3}}}}};

};
#endif // BASICARMOR_H