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
std::string a[11] = {" claws at ", " spits at ", " strikes at ", " bites at ", 
" swoops at ", " hurls itself at ", " pecks at ", " flails its tenticles at ",
" thrashes at ", " charges flailing at ", " blasts flames at " };

// Texture files used to create sprite animations.
std::string b[11] = {
	"", 						// 1. Skeleton
	"", 						// 2. Slime
	"", 						// 3. Snake
	"", 						// 4. Wolf
	"", 						// 5. Waps
	"", 						// 6. Zombie
	"", 						// 7. Duckling
	"Images/CactoSprite.png",	// 8. Catcopus
	"", 						// 9. Troll
	"",  						// 10. Omnibeast
    "Images/dragonLeft.png"		// 11. Dragon
};

/******************************** Glossary *************************************
* AD = Attack Description, what displays when the monster attacks. 
* Tex = Texture file for sprites.
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
* Bl = Bleed amount inflicted on attack.
* CrC = Critical chance. Chance to land a critical is '1 in CrC'.
* x1, x2, y1, y2 = Corners of rectangle used to make sprites.
* Fr = Number of frames (images to flip through) in sprite sheet.
* Cr, Ch, Sl, St = Crush, chop, slash, stab. For Attack, the damage range is
*    distributed to each by its percentage. For armor, damage is reduced by the 
*    percentage. Negative percentages increase damage (vulerabilities).
* Db = Defence bonus when character is defending. Multiply defencePower by this.
* CrM = Critical Multiplier. 
* Rp = Riposte ability.
* Db = Defence Bonus. Stack on DP when character is defending.
* Fs = Frame speed (how fast to render sprite animations).
*******************************************************************************/ 
std::map<std::string, std::pair<std::pair<std::vector<std::string>, 
std::vector<bool>>, std::pair<std::vector<short>, std::vector<float>>>> 
monster {
//            |   Strings   |    bools    |                                        Shorts                                                            |   |                                    Floats                      
//            |             |             |                                                                                                          |   |       Attack        |          Armor         | Misc Abilities
//  Key       |    AD   Tex | placeholder |  HP    BP    EP   Init Min   Rn Vnm Stn Hz  Pr   Ev   Pb  Cb   Eb  Dp   Rg  Bl CRC  x1   y1   x2   y2  Fr|   | Cr   Ch   Sl   St   |  Cr    Ch    Sl    St  | CrM  Rp  Db  Fs
{"Skeleton",  {{{ a[0], b[0] },  { 0 }},  {{ 1000, 1000, 1000,  80, 100,  50, 0,  0,  0, 80,   0,  25,  2, 20, 100,  0, 10, 2,   0,   0,   0,   0, 0 },  { 0.0, 0.1, 0.7, 0.2,   -1.0, -0.5,  0.4,  1.0,   3,  0,  50, 1.0 }}}},
{"Slime",     {{{ a[1], b[1] },  { 0 }},  {{ 1000, 1000, 1000, 160, 100,  50, 10, 0,  0, 80, -30,  25,  2, 20, 100,  0,  0, 2,   0,   0,   0,   0, 0 },  { 1.0, 0.0, 0.0, 0.0,    0.7, -0.2, -0.5,  0.0,   3,  0,  50, 1.0 }}}},
{"Snake",     {{{ a[2], b[2] },  { 0 }},  {{ 1000, 1000, 1000, 100,  30,  20, 10, 0,  0, 90,  20,  25,  2, 20, 100,  0, 10, 2,   0,   0,   0,   0, 0 },  { 0.0, 0.0, 0.1, 0.9,    0.6, -0.6, -0.3,  0.5,   3,  0,  50, 1.0 }}}},
{"Wolf",      {{{ a[3], b[3] },  { 0 }},  {{ 1000,  100, 1000, 100,  50,  50, 0,  0,  0, 70,  10,  25,  2, 20, 100,  0,100, 5,   0,   0,   0,   0, 0 },  { 0.1, 0.7, 0.1, 0.1,    0.4,  0.5,  0.2, -0.7,   4,  0,  50, 1.0 }}}},
{"Wasp",      {{{ a[4], b[4] },  { 0 }},  {{ 1000, 1000, 1000,  70,  20,  20, 0,  0,  0, 80,  40,  25,  2, 20, 100,  0,  0, 4,   0,   0,   0,   0, 0 },  { 0.0, 0.0, 0.1, 0.9,   -0.7,  0.2,  0.1,  0.0, 3.5,  0,  50, 1.0 }}}},
{"Zombie",    {{{ a[5], b[5] },  { 0 }},  {{ 1000, 1000, 1000, 200, 200,  50, 0,  0,  0, 60, -25,  25,  2, 20, 100,  0,  0, 2,   0,   0,   0,   0, 0 },  { 0.7, 0.3, 0.0, 0.0,    0.7, -0.7,  0.6,  0.8,   3,  0,  50, 1.0 }}}},
{"Duckling",  {{{ a[6], b[6] },  { 0 }},  {{   15,   20, 1000,  50,  10,  30, 0,  0,  0, 90,  50,  25,  2, 20, 100,  0,  5, 2,   0,   0,   0,   0, 0 },  { 0.0, 0.0, 0.0, 1.0,   0.95, 0.95, 0.95, 0.95,   3,  0,  50, 1.0 }}}},
{"Cactopus",  {{{ a[7], b[7] },  { 0 }},  {{   10,   10, 1000, 100,  20,  30, 0,  0,  2, 80, -10,  25,  2, 20, 100,  0, 10, 2,   0,   0, 131, 100, 6 },  { 0.3, 0.0, 0.3, 0.4,    0.3, -0.5, -0.2,  0.5,   3,  0,  50, 0.4 }}}},
{"Troll",     {{{ a[8], b[8] },  { 0 }},  {{ 1000, 1000, 1000, 110,  60,  40, 0, 100, 0, 80,   0,  25,  2, 20, 100, 40,  0, 3,   0,   0,   0,   0, 0 },  { 0.3, 0.2, 0.2, 0.1,    0.4,    0, -0.7, -0.3,   4,  0,  50, 1.0 }}}},
{"Omnibeast", {{{ a[9], b[9] },  { 0 }},  {{ 1000, 1000, 1000, 110,  30,  30, 5, 100, 4, 80,  20,  25,  2, 20, 100, 20, 20, 3,   0,   0,   0,   0, 0 },  { 0.6, 0.6, 0.6, 0.6,    0.5,  0.5,  0.5,  0.5,   6, .5, 100, 1.0 }}}},
{"Dragon",    {{{ a[10],b[10]},  { 0 }},  {{ 1000, 1000, 1000, 110,  30,  30, 5, 100, 4, 80,  20,  25,  2, 20, 100, 20, 20, 3,   0,   0, 191, 161, 3 },  { 0.6, 0.6, 0.6, 0.6,    0.5,  0.5,  0.5,  0.5,   6, .5, 100, 0.2 }}}},

};

/*
Other monster ideas:
   Skelementalist, Shadow Lisk, Ent, Omni demon (all attributes), 
*/

#endif // MONSTERS_CPP