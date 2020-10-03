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
*   Wt  = Weight of armor. Affects initiative.
*   Vol = Volume of armor. Even light equipment can be cumbersome.
*   DP  = Defence Power. Determines overall effectiveness of armor.
*   Cr  = Defence against crushing.
*   Ch  = Defence against chopping.
*   Sl  = Defence against slashing.
*   St  = Defence against stabbing.
*******************************************************************************/ 
//             Placeholders
//           strings   bools           Shorts                Floats
//  Key                             Wt  Vol  DP        Cr   Ch   Sl   St   
{"Padding", {{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 0.7, 0.2, 0.1, 0.0 }}}},
{"Leather", {{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 0.2, 0.3, 0.3, 0.2 }}}},
{"Ring",    {{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 0.3, 0.3, 0.3, 0.1 }}}},
{"Chain",   {{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 0.1, 0.1, 0.6, 0.2 }}}},
{"Scale",   {{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 0.1, 0.1, 0.3, 0.5 }}}},
{"Plate",   {{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 0.3, 0.3, 0.2, 0.2 }}}}, 

// Monster armors                   Wt  Vol  DP        Cr   Ch   Sl   St
{"ImmuneST",{{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 1.0, 0.5, 0.5, 0.2 }}}},
{"UmmuneCR",{{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 0.1, 0.2, 0.3, 0.4 }}}},
{"ImmuneSL",{{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 0.1, 0.2, 0.3, 0.4 }}}},
{"ImmuneCH",{{{ "" },  { 0 }},  {{ 100, 200, 100 },  { 0.1, 0.2, 0.3, 0.4 }}}}};

#endif // ARMORS_CPP