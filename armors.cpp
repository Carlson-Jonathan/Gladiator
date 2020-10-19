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
* Rg = Regeneration. Restores Rg of BP per combat round.
* Cr = Defence against crushing.
* Ch = Defence against chopping.
* Sl = Defence against slashing.
* St = Defence against stabbing.
*******************************************************************************/ 
//                 Placeholders
//               strings   bools                  Shorts                           Floats
//  Key                                 Wt  Vol  DP    Ev  Eb  Db   Sp  Rg      Cr   Ch   Sl   St
{"Naked"      , {{{ "" },  { 0 }},  {{   0,   0,   0,  60, 30,  0, -40, 0  },  { 0.3, 0.3, 0.3, 0.1 }}}},
{"Fighting Gi", {{{ "" },  { 0 }},  {{  20, 200,  20,  50, 25, 50, -30, 0  },  { 0.1, 0.3, 0.3, 0.3 }}}},
{"Pads",        {{{ "" },  { 0 }},  {{  70, 200,  80,  20, 20, 50, -20, 0  },  { 0.7, 0.3, 0.0, 0.0 }}}},
{"Leather",     {{{ "" },  { 0 }},  {{  50, 200,  90,  30, 15, 60, -10, 0  },  { 0.3, 0.2, 0.2, 0.3 }}}},
{"Ring",        {{{ "" },  { 0 }},  {{  75, 200, 140,  10, 10, 70,   0, 0  },  { 0.1, 0.7, 0.3, 0.1 }}}},
{"Chain",       {{{ "" },  { 0 }},  {{ 125, 200, 190, -10, 10, 80,  10, 0  },  { 0.0, 0.2, 0.7, 0.1 }}}},
{"Blood Scale", {{{ "" },  { 0 }},  {{ 150, 200, 220, -20,  5, 90,  20, 20 },  { 0.0, 0.1, 0.2, 0.7 }}}},
{"Plate",       {{{ "" },  { 0 }},  {{ 250, 200, 300, -30,  0, 100, 30, 0  },  { .25, .25, .25, .25 }}}}}; 

#endif // ARMORS_CPP