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

// Just a last ditch effort to prevent my table from getting too wide. 
// Variable 'a' stands for 'attack' description.
string a[8] = {" claws at ", " spits at ", " strikes at ", " bites at ", 
" swoops at ", " hurls itself at ", " pecks at ", " flails its tenticles at "};

/******************************** Glossary *************************************
* AD = Attack Description, what displays when the monster attacks. 
* HP = Hit Points
* BP = Blood Points
* EP = Essence Points
* Init = Character initiative (higher is slower)
* Min = Minimum damage on attack
* Rg = Range of damage. Min 50 + Rg 100 = 50 - 150 damage range.
* Vnm = Venemous. Adds to players base initiative if active.
* Stn = Stun caused on attack. Number is added to the player's running initiative.
* Hz = Hazard damage. The damage the attacker takes (like kicking a cactus).
*    Divide attacker damage by this number to get hazard damage.
* Cr, Ch, Sl, St = Crush, chop, slash, stab. For Attack, the damage range is
*    distributed to each by its percentage. For armor, damage is reduced by the 
*    percentage. Negative percentages increase damage (vulerabilities).
*******************************************************************************/ 
std::map<std::string, std::pair<std::pair<std::vector<std::string>, 
std::vector<bool>>, std::pair<std::vector<short>, std::vector<float>>>> 
monster {
//            |Strings |    bools    |                Shorts                      |   |                    Floats                      
//            |        |             |                                            |   |      Attack         |          Armor         |  
//  Key       |    AD  | placeholder |  HP    BP    EP   Init Min   Rg Vnm Stn Hz |   | Cr   Ch   Sl   St   |  Cr    Ch    Sl    St  |
{"Skeleton",  {{{ a[0] },  { 0 }},  {{ 1000, 1000, 1000,  80, 100,  50, 0,  0,  0 },  { 0.0, 0.1, 0.7, 0.2,   -1.0, -0.5,  0.4,  1.0 }}}},
{"Slime",     {{{ a[1] },  { 0 }},  {{ 1000, 1000, 1000, 160, 100, 200, 10, 0,  0 },  { 1.0, 0.0, 0.0, 0.0,    0.7, -0.2, -0.5,  0.0 }}}},
{"Snake",     {{{ a[2] },  { 0 }},  {{ 1000, 1000, 1000, 100, 100, 100, 10, 0,  0 },  { 0.0, 0.0, 0.1, 0.9,    0.6, -0.6, -0.3,  0.5 }}}},
{"Wolf",      {{{ a[3] },  { 0 }},  {{ 1000, 1000, 1000, 100, 100, 100, 0,  0,  0 },  { 0.1, 0.7, 0.1, 0.1,    0.4,  0.5,  0.2, -0.7 }}}},
{"Giant Wasp",{{{ a[4] },  { 0 }},  {{ 1000, 1000, 1000, 100, 100, 100, 20, 0,  0 },  { 0.0, 0.0, 0.1, 0.9,   -0.7,  0.2,  0.1,  0.0 }}}},
{"Zombie",    {{{ a[5] },  { 0 }},  {{ 1000, 1000, 1000, 100, 100, 100, 0,  0,  0 },  { 0.7, 0.3, 0.0, 0.0,    0.7, -0.7,  0.6,  0.8 }}}},
{"Duckling",  {{{ a[6] },  { 0 }},  {{   25,   25, 1000,  30,  25,  50, 0,  0,  0 },  { 0.0, 0.0, 0.0, 1.0,    0.9,  0.9,  0.9,  0.9 }}}},
{"Cactopus",  {{{ a[7] },  { 0 }},  {{ 1000, 1000, 1000, 150,  20,  30, 0,  0,  2 },  { 0.3, 0.0, 0.3, 0.4,    0.3, -0.5, -0.2,  0.5 }}}},

};

#endif // MONSTERS_CPP