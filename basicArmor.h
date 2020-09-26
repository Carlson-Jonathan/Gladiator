/******************************************************************************
* basicArmor.h
* Author: Jonathan Carlson
* Last Updated: September 2020
* Description:
*    Contains basicArmor class with a list of basicWeapon and their statistics.
******************************************************************************/
#ifndef BASICARMOR_H
#define BASICARMOR_H
#include <iostream>
using namespace std;

class BasicArmor {
public:

   BasicArmor() {}

   // Getters
   float getStab()        {return stab;}
   float getCrush()       {return crush;}
   float getSlash()       {return slash;}
   float getChop()        {return chop;}

   // Setters
   void setStab(float stab)               {this->stab = stab;}
   void setCrush(float crush)             {this->crush = crush;}
   void setSlash(float slash)             {this->slash = slash;}
   void setChop(float chop)               {this->chop = chop;}


protected:
   string name;
   short weight; // Affects turn speed


   // Physical Defence values
   float stab,
         crush,
         slash,
         chop;

   // Elemental Defence Values
   float fire,
         air, 
         water,
         shock;


};
#endif // BASICARMOR_H