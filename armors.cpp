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

/*                    Legend:
Key/Name
   Reserved                                     -Strings
   Reserved                                     -Booleans
   Weight, Volume, Block value                  -Shorts
   % Reductions for Stab, Crush, Slash, Chop    -Floats
*/

{"Padding", 
   {{{ "", "" }, 
   { true, false }}, 
   {{ 100, 200, 10 }, 
   { 0.1, 0.5, 0.2, 0.1 }}}},

{"Leather", 
   {{{ "" , "" }, 
   { true, false }}, 
   {{ 1, 2, 3 }, 
   { 0.2, 0.2, 0.3, 0.3 }}}},

{"Ring", 
   {{{ "", "" }, 
   { true, false }}, 
   {{ 1, 2, 3 }, 
   { 0.1, 0.3, 0.3, 0.3 }}}},

{"Chain", 
   {{{ "" , "" }, 
   { true, false }}, 
   {{ 1, 2, 3 }, 
   { 0.1, 0.1, 0.6, 0.2 }}}},

{"Scale", 
   {{{ "", "" }, 
   { true, false }}, 
   {{ 1, 2, 3 },
   { 0.5, 0.1, 0.3, 0.1 }}}},

{"Plate",  
   {{{ "" , "" }, 
   { true, false }}, 
   {{ 1, 2, 3 }, 
   { 0.1, 0.5, 0.1, 0.3 }}}},

// Monster armors
{"ImmuneST", 
   {{{ "" }, 
   { true }}, 
   {{1, 2, 3}, 
   {1.0, -0.5, 0.5, -0.2}}}},

{"UmmuneCR", 
   {{{ "Chainmail", "str2" }, 
   { true, false }}, 
   {{ 1, 2, 3 }, { 0.1, 0.2, 0.3 }}}},

{"ImmuneSL", 
   {{{ "Chainmail", "str2" }, 
   { true, false }}, 
   {{ 1, 2, 3 }, { 0.1, 0.2, 0.3 }}}},

{"ImmuneCH", 
   {{{ "Chainmail", "str2" }, 
   { true, false }}, 
   {{ 1, 2, 3 }, 
   { 0.1, 0.2, 0.3 }}}}};

#endif // ARMORS_CPP