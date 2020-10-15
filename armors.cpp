/***************************************************************************
* armors.cpp
* Author: Jonathan Carlson
* Description:
*    This file contains the reference data for pre-made armors.
*    Essentially this is a custom data type that resembles a Python
*    dictionary for the purpose of creating a table of information.
*    This single variable is included in the advancedArmor.h file under 
*    the list of private variables as "#include 'armors.cpp'".
*    NO! I don't want to use a struct for this! This is supposed to provide
*    a table of data from which I can create objects, not the actual 
*    objects. And yes, I know it looks like MongoDB. Thats what I envisioned
***************************************************************************/
#ifndef ARMORS_CPP
#define ARMORS_CPP
#include <iostream>
#include <vector>
#include <map>

std::map<std::string, std::pair<std::pair<std::vector<std::string>, 
std::vector<bool>>, std::pair<std::vector<short>, std::vector<float>>>> 
armor {

/******************************** Glossary *************************************
* Wt = Weight of armor. Affects initiative.
* Vol = Volume of armor. Even light equipment can be cumbersome.
* DP = Defence Power. Determines overall effectiveness of armor.
* Ev = Armor's evasion.
* Eb = Evade bonus applied when character is defending.
* Db = Defence bonus when character is defending. Multiply defencePower by this.
* Sp = Speed modifier. Add this to base initiative.
* Cr = Defence against crushing.
* Ch = Defence against chopping.
* Sl = Defence against slashing.
* St = Defence against stabbing.
*******************************************************************************/ 
//             Placeholders
//           strings   bools               Shorts                       Floats
//  Key                             Wt  Vol  DP    Ev  Eb  Db   Sp       Cr   Ch   Sl   St
{"Padding", {{{ "" },  { 0 }},  {{  70, 200, 100,  20, 20, 50, -10 },  { 0.7, 0.2, 0.1, 0.0 }}}},
{"Leather", {{{ "" },  { 0 }},  {{  50, 200, 100,  30, 30, 60, -20 },  { 0.2, 0.3, 0.3, 0.2 }}}},
{"Ring",    {{{ "" },  { 0 }},  {{  75, 200, 100,  10, 20, 70,   0 },  { 0.3, 0.3, 0.3, 0.1 }}}},
{"Chain",   {{{ "" },  { 0 }},  {{ 125, 200, 100, -10, 10, 80,  10 },  { 0.1, 0.1, 0.6, 0.2 }}}},
{"Scale",   {{{ "" },  { 0 }},  {{ 150, 200, 100, -15, 10, 90,  20 },  { 0.1, 0.1, 0.3, 0.5 }}}},
{"Plate",   {{{ "" },  { 0 }},  {{ 200, 200, 100, -20,  5, 100, 30 },  { 0.3, 0.3, 0.2, 0.2 }}}}}; 

#endif // ARMORS_CPP