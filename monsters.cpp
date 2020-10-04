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

std::map<std::string, std::pair<std::pair<std::vector<std::string>, 
std::vector<bool>>, std::pair<std::vector<short>, std::vector<float>>>> 
monster {

/******************************** Glossary *************************************
* Attack Description = What displays when the monster attacks. 
* DP  = Defence Power. Determines overall effectiveness of armor.
* Cr  = Offence or Defence with crushing (Attack/Armor).
* Ch  = Offence or Defence with chopping (Attack/Armor).
* Sl  = Offence or Defence with slashing (Attack/Armor).
* St  = Offence or Defence with stabbing (Attack/Armor).
*    Note: Leave monster DP at 100. Armor values are percentage reductions of
*    damage taken. Negative values increase damage taken (vulnerabilities).
*    1.0 means immune, 0.5 is half damage, -1.0 take double damage.
*******************************************************************************/ 
//                                                                                                           Floats
//                     Strings            bools                   Shorts                          Attack                 Armor
//  Key          Attack Description                    HP    BP    EP  Slow  Min Range      Cr   Ch   Sl   St     Cr   Ch   Sl   St
{"Skeleton",  {{{ " claws at "        },  { 0 }},  {{ 1000, 1000, 1000,  80, 100,  50 },  { 0.0, 0.1, 0.7, 0.2,   -1.0, -0.5, 0.4, 1.0 }}}},
{"Slime",     {{{ " spits at "        },  { 0 }},  {{ 1000, 1000, 1000, 160, 100, 200 },  { 1.0, 0.0, 0.0, 0.0,   0.7, -0.2, -0.5, 0.0 }}}},
{"Snake",     {{{ " strikes at "      },  { 0 }},  {{ 1000, 1000, 1000, 100, 100, 100 },  { 0.0, 0.0, 0.1, 0.9,   0.6, -0.6, -0.3, 0.5 }}}},
{"Wolf",      {{{ " bites at "        },  { 0 }},  {{ 1000, 1000, 1000, 100, 100, 100 },  { 0.1, 0.7, 0.1, 0.1,   0.4, 0.5, 0.2, -0.7 }}}},
{"GiantWasp", {{{ " swoops at "       },  { 0 }},  {{ 1000, 1000, 1000, 100, 100, 100 },  { 0.0, 0.0, 0.1, 0.9,   -0.7, 0.2, 0.1, 0.0 }}}},
{"Zombie",    {{{ " hurls itself at " },  { 0 }},  {{ 1000, 1000, 1000, 100, 100, 100 },  { 0.7, 0.3, 0.0, 0.0,   0.7, -0.7, 0.6, 0.8 }}}},
{"Duckling",  {{{ " pecks at "        },  { 0 }},  {{   25,   25, 1000,  30,  25, 50  },  { 0.0, 0.0, 0.0, 1.0,   0.9,  0.9, 0.9, 0.9 }}}},


};

#endif // MONSTERS_CPP