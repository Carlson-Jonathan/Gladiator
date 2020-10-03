/***************************************************************************
* monsters.cpp
* Author: Jonathan Carlson
* Description:
*    This file contains the reference data for pre-made monsters.
*    Essentially this is a custom data type that resembles a Python
*    dictionary for the purpose of creating a table of information.
*    This single variable is included in the character.h file under the 
*    list of private variables as "#include 'monsters.cpp'".
*    NO! I don't want to use a struct for this! This is supposed to provide
*    a table of data from which I can create objects, not the actual objects
***************************************************************************/
#ifndef MONSTERS_CPP
#define MONSTERS_CPP
#include <iostream>
#include <vector>
#include <map>

std::map<std::string, std::pair<std::vector<std::string>, 
                                std::vector<short>>> monster = {
/*
Strings: Creature's name | Attack type | Attack Description | Armor
Shorts:  HP | BP | EP | Speed | Min Damage | Damage Range       */

{"Skeleton", 
   {{ "Skeleton", "Pure Slash", " claws at ", "ImmuneST" }, 
   { 1000, 1000, 1000, 100, 100, 100 }}},

{"Slime",    
   {{ "Slime", "Pure Crush", " spits at ", "Plate" },   
   { 1000, 1000, 1000, 100, 100, 100 }}},

{"Snake",    
   {{ "Cobra", "Pure Stab", " strikes at ", "Plate" },
   { 1000, 1000, 1000, 100, 100, 100 }}},

{"Wolf",     
   {{ "Spider Wolf", "Pure Chop", " bites at ", "Plate" },
   { 1000, 1000, 1000, 100, 100, 100 }}},

{"GiantWasp",
   {{ "Giant Wasp", "Pure Stab", " swoops at ", "Plate" },
   { 1000, 1000, 1000, 100, 100, 100 }}},

{"Zombie",   
   {{ "Zombie", "Pure Crush", " hurls itself at ", "Plate" },
   { 1000, 1000, 1000, 100, 100, 100 }}}
};

#endif // MONSTERS_CPP