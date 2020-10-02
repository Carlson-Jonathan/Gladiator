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
   { 1000, 1000, 1000, 100, 100, 1 }}},

{"Slime",    
   {{ "Slime", "Pure Crush", " spits at ", "Plate" },   
   { 800, 500, 350, 190, 100, 50 }}},

{"Snake",    
   {{ "Cobra", "Pure Stab", " strikes at ", "Plate" },
   { 300, 500, 250, 40, 100, 50 }}},

{"Wolf",     
   {{ "Spider Wolf", "Pure Chop", " bites at ", "Plate" },
   { 400, 500, 600, 20, 10, 10 }}},

{"GiantWasp",
   {{ "Giant Wasp", "Pure Stab", " swoops at ", "Plate" },
   { 350, 500, 650, 40, 30, 20 }}},

{"Zombie",   
   {{ "Zombie", "Pure Crush", " hurls itself at ", "Plate" },
   { 800, 500, 500, 190, 100, 50 }}}
};

#endif // MONSTERS_CPP