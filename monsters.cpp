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
std::string a[10] = {" claws at ", " spits at ", " strikes at ", " bites at ", 
" swoops at ", " hurls itself at ", " pecks at ", " flails its tenticles at ",
" thrashes at ", " charges flailing at " };

/******************************** Glossary *************************************
* AD = Attack Description, what displays when the monster attacks. 
* HP = Hit Points
* BP = Blood Points
* EP = Essence Points
* Init = Character initiative (higher is slower)
* Min = Minimum damage on attack
* Rn = Range of damage. Min 50 + Rg 100 = 50 - 150 damage range.
* Vnm = Venemous. Adds to players base initiative if active.
* Stn = Stun caused on attack. Number is added to the player's running initiative.
* Hz = Hazard damage. The damage the attacker takes (like kicking a cactus).
*    Divide attacker damage by this number to get hazard damage.
* Pr = Percision. Governs chance to miss (100 - Pr).
* Ev = Evasion chance.
* Pb = Percision bonus. Add this to character percision when isDefending().
* Cb = Critical bonus. Divide CC by this to increase chance to land critical.
* Eb = Evade bonus applied when character is defending.
* Dp = Defence power. 
* Rg = Regeneration. Character gains this much BP per combat round.
* Cr, Ch, Sl, St = Crush, chop, slash, stab. For Attack, the damage range is
*    distributed to each by its percentage. For armor, damage is reduced by the 
*    percentage. Negative percentages increase damage (vulerabilities).
* Db = Defence bonus when character is defending. Multiply defencePower by this.
* CrM = Critical Multiplier. 
* CrC = Critical chance. Chance to land a critical is '1 in CrC'.
* Rp = Riposte ability.
* Db = Defence Bonus. Stack on DP when character is defending.
*******************************************************************************/ 
std::map<std::string, std::pair<std::pair<std::vector<std::string>, 
std::vector<bool>>, std::pair<std::vector<short>, std::vector<float>>>> 
monster {
//            |Strings |    bools    |                                        Shorts                            |   |                                           Floats                      
//            |        |             |                                                                          |   |       Attack        |          Armor         |     Misc Abilities
//  Key       |    AD  | placeholder |  HP    BP    EP   Init Min   Rn Vnm Stn Hz  Pr   Ev   Pb  Cb  Eb, Dp  Rg |   | Cr   Ch   Sl   St   |  Cr    Ch    Sl    St  | CrM  CrC  Rp  Db
{"Skeleton",  {{{ a[0] },  { 0 }},  {{ 1000, 1000, 1000,  80, 100,  50, 0,  0,  0, 80,   0,  25,  2, 20, 100,  0 },  { 0.0, 0.1, 0.7, 0.2,   -1.0, -0.5,  0.4,  1.0,    3,  10,  0,  50  }}}},
{"Slime",     {{{ a[1] },  { 0 }},  {{ 1000, 1000, 1000, 160, 100,  50, 10, 0,  0, 80, -30,  25,  2, 20, 100,  0 },  { 1.0, 0.0, 0.0, 0.0,    0.7, -0.2, -0.5,  0.0,    3,  10,  0,  50  }}}},
{"Snake",     {{{ a[2] },  { 0 }},  {{ 1000, 1000, 1000, 100,  30,  20, 10, 0,  0, 90,  20,  25,  2, 20, 100,  0 },  { 0.0, 0.0, 0.1, 0.9,    0.6, -0.6, -0.3,  0.5,    3,  10,  0,  50  }}}},
{"Wolf",      {{{ a[3] },  { 0 }},  {{ 1000,  100, 1000, 100,  50,  50, 0,  0,  0, 70,  10,  25,  2, 20, 100,  0 },  { 0.1, 0.7, 0.1, 0.1,    0.4,  0.5,  0.2, -0.7,    4,   2,  0,  50  }}}},
{"Wasp",      {{{ a[4] },  { 0 }},  {{ 1000, 1000, 1000,  70,  20,  20, 0,  0,  0, 80,  40,  25,  2, 20, 100,  0 },  { 0.0, 0.0, 0.1, 0.9,   -0.7,  0.2,  0.1,  0.0,  3.5,   4,  0,  50  }}}},
{"Zombie",    {{{ a[5] },  { 0 }},  {{ 1000, 1000, 1000, 200, 200,  50, 0,  0,  0, 60, -25,  25,  2, 20, 100,  0 },  { 0.7, 0.3, 0.0, 0.0,    0.7, -0.7,  0.6,  0.8,    3,  10,  0,  50  }}}},
{"Duckling",  {{{ a[6] },  { 0 }},  {{   15,   20, 1000,  50,  10,  30, 0,  0,  0, 90,  50,  25,  2, 20, 100,  0 },  { 0.0, 0.0, 0.0, 1.0,   0.95, 0.95, 0.95, 0.95,    3,  10,  0,  50  }}}},
{"Cactopus",  {{{ a[7] },  { 0 }},  {{ 1000, 1000, 1000, 150,  20,  30, 0,  0,  2, 80, -10,  25,  2, 20, 100,  0 },  { 0.3, 0.0, 0.3, 0.4,    0.3, -0.5, -0.2,  0.5,    3,  10,  0,  50  }}}},
{"Troll",     {{{ a[8] },  { 0 }},  {{ 1000, 1000, 1000, 110,  60,  40, 0, 100, 0, 80,   0,  25,  2, 20, 100, 40 },  { 0.3, 0.2, 0.2, 0.1,    0.4,    0, -0.7, -0.3,    4,   7,  0,  50  }}}},
{"Omnibeast", {{{ a[9] },  { 0 }},  {{ 1000, 1000, 1000, 110,  30,  30, 5, 100, 4, 80,  20,  25,  2, 20, 100, 20 },  { 0.6, 0.6, 0.6, 0.6,    0.5,  0.5,  0.5,  0.5,    6,   8, .5,  100 }}}},

};

/*
Other monster ideas:
   Skelementalist, Shadow Lisk, Ent, Omni demon (all attributes), 
*/

#endif // MONSTERS_CPP