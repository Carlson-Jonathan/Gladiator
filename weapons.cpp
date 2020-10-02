/***************************************************************************
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
***************************************************************************/
#ifndef WEAPONS_CPP
#define WEAPONS_CPP
#include <iostream>
#include <vector>
#include <map>

std::map<std::string, std::pair<std::string, 
                      std::pair<std::vector<short>, std::vector<float>>>> 
                      weapons = {
/*   Legend:
{"Weapon Name", 
   { " combat text ",              - strings
   { min damage, damage range },   - shorts
   { crush, chop, slash, stab }}   - floats
*/
    
{"Fists",       
   { " punches ",    
   {{ 5 , 10 },  
   { 1.0, 0.0, 0.0, 0.0 }}}},

{"Broad Sword", 
   { " slashes at ", 
   {{ 100, 1 },  
   { 0.0, 0.2, 0.5, 0.3 }}}},

{"Katana",      
   { " slashes at ", 
   {{ 50, 50 },  
   { 0.2, 0.0, 0.7, 0.1 }}}},

{"Battle Axe",  
   { " chops at ",   
   {{ 45, 110 }, 
   { 0.1, 0.7, 0.1, 0.0 }}}},

{"Spear",       
   {" lunges at ",  
   {{ 100, 1 },  
   { 0.0, 0.0, 0.1, 0.9 }}}},

{"Mace",        
   {" swings at ",  
   {{ 1, 100 },  
   { 1.0, 0.0, 0.0, 0.0 }}}},

/*********************** Monster Weapons ***********************/

{"Pure Crush",  
   {"",  
   {{ 1, 100 }, 
   { 1.0, 0.0, 0.0, 0.0 }}}},

{"Pure Chop",   
   {"",  
   {{ 1, 100 },   
   { 0.0, 1.0, 0.0, 0.0 }}}},

{"Pure Slash",  
   {"",  
   {{ 1, 100 },   
   { 0.0, 0.0, 1.0, 0.0 }}}},

{"Pure Stab",   
   {"",  
   {{ 1, 100 },   
   { 0.0, 0.0, 0.0, 1.0 }}}}};

#endif // WEAPONS_CPP