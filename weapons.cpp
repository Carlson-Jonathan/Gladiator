/*******************************************************************************
* weapons.cpp
* Author: Jonathan Carlson
* Description:
*    This file contains the reference data for pre-made weapons.
*    Essentially this is a custom data type that resembles a Python
*    dictionary for the purpose of creating a table of information.
*    This single variable is included in the advancedWeapons.h file under 
*    the list of private variables as "#include 'weapons.cpp'".
*    NO! I don't want to use a struct for this! This is supposed to provide
*    a table of data from which I can create objects, not the actual objects
*******************************************************************************/
#ifndef WEAPONS_CPP
#define WEAPONS_CPP
#include <iostream>
#include <vector>
#include <map>

std::map<std::string, std::pair<std::string, std::pair<std::vector<short>, 
std::vector<float>>>> weapons = {

/********************************* Glossary ************************************
* Description = The text that is displayed when an attack is executed.
* Min = The minimum amount of damage done by the weapon.
* Rg = The weapon's range of damage. Min 100 and Range 50 = 100-150 damage.
* Sp = Weapon speed. This is added to the player's total initiative.
* Vnm = Venomous. Applied poisons. Amount is added to victim's base initiative.
* Stn = Stun amount. Is added to victim's running initiative.
* CC = Critical Chance - Has a 1 in 'CC' chance to do 'CM' times more damage.
* Pr = Percision. Higher = better aim and less missing on attack.
* Pb = Percision bonus. Add this to player percision when isDefending().
* Cb = Critical bonus. Divide CC by this to increase chance to land critical.
* Sh = Sharp. The amount of base bleeding this weapon causes.
* Cr = The percentage of the weapon's total damage allocated to crushing.
* Ch = The percentage of the weapon's total damage allocated to chopping.
* Sl = The percentage of the weapon's total damage allocated to slashing.
* St = The percentage of the weapon's total damage allocated to stabbing.
* CM = Critical damage multiplier 
* Rp = Riposte - Reaction strike damage multiplier. 
*******************************************************************************/

//      Key        Description       Min   Rg   Sp  Vnm Stn  CC,  Pr  Pb, Cb Sh       Cr   Ch   Sl   St   CM  Rp
{"Fists",       { " punches ",    {{   5,  10, -50,  0,   0,  5,  50, 30, 2,  0 },  { 1.0, 0.0, 0.0, 0.0, 20,  0 }}}},
{"Broad Sword", { " slashes at ", {{  75,  25,   0,  0,   0,  2,   0, 40, 2, 10 },  { 0.0, 0.2, 0.5, 0.3,  3,  0 }}}},
{"Katana",      { " slashes at ", {{  50,  50, -20,  0,   0,  2,  20, 30, 2, 10 },  { 0.2, 0.0, 0.7, 0.1,  3, .5 }}}},
{"Battle Axe",  { " chops at ",   {{  10, 290,  50,  0,   0,  4, -20, 30, 4,  5 },  { 0.1, 0.8, 0.1, 0.0,  4,  0 }}}},
{"Spear",       { " lunges at ",  {{  30,  25, -30, 20,   0,  2, -15, 45, 2, 20 },  { 0.0, 0.0, 0.1, 0.9,  3,  0 }}}},
{"Mace",        { " swings at ",  {{  50,  40,  20,  0, 200,  3, -10, 25, 3,  0 },  { 1.0, 0.0, 0.0, 0.0,  3,  0 }}}},
{"Rapier",      { " lunges at ",  {{  20,  20, -30,  0,   0,  2,  15, 40, 2,  7 },  { 0.0, 0.0, 0.3, 0.7,  3, .7 }}}},
{"Morning Star",{ " swings at ",  {{ 100,  50,  40,  0, 120,  3, -15, 35, 3,  5 },  { 0.6, 0.0, 0.0, 0.4,  3,  0 }}}}

};

/*
Additional weapon ideas:
   By region: Nunchucks, bow staff, katana, yari, 
*/


#endif // WEAPONS_CPP