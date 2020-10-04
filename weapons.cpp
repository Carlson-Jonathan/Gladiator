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
* Cr = The percentage of the weapon's total damage allocated to crushing.
* Ch = The percentage of the weapon's total damage allocated to chopping.
* Sl = The percentage of the weapon's total damage allocated to slashing.
* St = The percentage of the weapon's total damage allocated to stabbing.
*******************************************************************************/
    
//      Key        Description       Min   Rg   Sp       Cr   Ch   Sl   St
{"Fists",       { " punches ",    {{   5,  10, -50 },  { 1.0, 0.0, 0.0, 0.0 }}}},
{"Broad Sword", { " slashes at ", {{  75,  25,  20 },  { 0.0, 0.2, 0.5, 0.3 }}}},
{"Katana",      { " slashes at ", {{  50,  50, -10 },  { 0.2, 0.0, 0.7, 0.1 }}}},
{"Battle Axe",  { " chops at ",   {{  45, 110,  50 },  { 0.1, 0.7, 0.1, 0.0 }}}},
{"Spear",       { " lunges at ",  {{  30,  25, -30 },  { 0.0, 0.0, 0.1, 0.9 }}}},
{"Mace",        { " swings at ",  {{  50, 100,  30 },  { 1.0, 0.0, 0.0, 0.0 }}}}};

/*
Additional weapon ideas:
   By region: Nunchucks, bow staff, katana, yari, 
*/


#endif // WEAPONS_CPP