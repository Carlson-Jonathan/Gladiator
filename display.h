/*******************************************************************************
* combat.cpp
* Author: Jonathan Carlson
* Description:
*  Governs the combat sequence applying stats from the Character class objects.
*  This entire file is temporary and only used for display in plain text format
*  on the terminal. It will be outsourced when a game engine is implemented. 
*******************************************************************************/
#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <iomanip>
#include <cstdlib>  // sleep
#include <unistd.h> // sleep
#include <stdlib.h> // Clear screen
#include <sstream>
#include <bits/stdc++.h>
#include "character.h"
#include "general.h"
using namespace std;

/*******************************************************************************
* Prototypes
*******************************************************************************/
short getUserInput(const vector<string> options);
void anyKeyToContinue();
string writeMessage(const string message);
void writeMessageScroll(const string message);
void combatVictory(const Character & player, const Character & monster);
void combatDefeat();
void displayAttackMessage(const Character & victim, const Character & aggressor, 
	                      const short damage[]);
void displayCharacterStats(const Character & player, const Character & monster, 
	                       const short round);
void selectWeapon(Character & player);   // To be deleted
void selectArmor(Character & player);    // To be deleted
void bleedingMessage(const Character & victim);
void displayStats(const Character & character);
void stunMessage(const Character & aggressor, const Character & victim);

/*******************************************************************************
* void getUserInput(vector<string>)
* Aquires and validates user input. Parameter is a list of options.
*******************************************************************************/
short getUserInput(const vector<string> options) {
   short userSelection;
	
   cout << "\tMake your selection:\n";
   for(int i = 0; i < options.size(); i++)
      cout << "\t" << (i + 1) << ".) " << options[i] << endl;

   do {
      cout << "\t>> ";
      cin >> userSelection;	    
      while(cin.fail()) {
         cin.clear();
         cin.ignore(std::numeric_limits<int>::max(),'\n');
         userSelection = 0;
      }
   } while(userSelection < 1 || userSelection > options.size());
   cout << endl;
   
   return userSelection;
}

/*******************************************************************************
* void anyKeyToContinue
* Pauses until the user presses a key. Probably won't be using this soon.
*******************************************************************************/
void anyKeyToContinue() {
   cout << setw(42) << "...\n\n";
   string x;
   getline(cin, x);
   cin.clear(); 
   cin.ignore(std::numeric_limits<int>::max(),'\n');
}

/*******************************************************************************
* void writeMessage(string)
* Prints the message to the screen one letter at a time at a specified pace.
*******************************************************************************/
string writeMessage(const string message) {
	cout << "\t";
	for(char i : message) {
		cout << i;
		cout.flush();
		usleep(10000);
	}
	return "\t";
}

/*******************************************************************************
* void writeMessageScroll(string)
* Prints the message to the screen one line at a time at a specified pace.
*******************************************************************************/
void writeMessageScroll(const string message) {
    
   int n = message.length(); 
   char char_array[n + 1]; 
   strcpy(char_array, message.c_str());

   stringstream ss(char_array);
   string to;

   if (char_array != NULL) 
      while(getline(ss,to,'\n')) {
         cout << to << endl;
         cout.flush();
         usleep(50000);
      }
   
   usleep(700000);
}


/*******************************************************************************
* combatVictory
* Displays victory message at the end of combat. 
*******************************************************************************/
void combatVictory(const Character & player, const Character & monster) {
   
   string message = "\t";
   message += "The "; message += monster.name; 
   message += " drops to the ground writhing in agony.";
	
   message = writeMessage(message);
   usleep(1000000);
   cout << endl;

   cout << "========================================"
	    << "=======================================\n";

   message = player.name + " is victorious!";
   short length = message.length();
   
   for(int i = 0; i < 36 - message.length() / 2; i++)
      cout << " ";

   writeMessage(message);
   cout << "\n======================================="
	    << "========================================\n";	
   usleep(1000000);

   cout << "\n\t***************\n" << "\tRewards:\n" << "\tCash + $0.23\n" 
	    << "\tPopularity + 10\n" << "\tChocolate + 1\n" 
	    << "\t***************\n"; 
}

/*******************************************************************************
* void combatDefeat()
* Displays defeat message at the end of combat. 
*******************************************************************************/
void combatDefeat() {
	writeMessage("Y O U   H A V E   B E E N   D E F E A T E D !");
}

/*******************************************************************************
* void displayAttackMessage(Character, Character)
* Used in combat.h
* Prints the attack action, eg. "The Cobra strikes at <player>"
*******************************************************************************/
void displayAttackMessage(const Character & victim, 
	                      const Character & aggressor, const short damage[]) {
   
   string message = "", x;
   if(!aggressor.isHero)
      message += "The ";
   message += aggressor.name + aggressor.weapon->actionDescription;
   if(aggressor.isHero)
      message += "the ";
   message += victim.name;
   if(aggressor.isHero) {
      message += " with the "; 
      message += aggressor.weapon->name;
   }
   message += "!\n";

   message = writeMessage(message);
   usleep(300000);

   if(aggressor.isHero)
      message += "The ";
   message += victim.name + " takes damage:";
   writeMessage(message);

   cout << "\n\t\tHP: -" << damage[0] << "  |  " << "BP: -" << damage[1] << "  |  "
        << "EP: -" << damage[2] << "\n";

   usleep(700000);
   cout << endl;
}

/*******************************************************************************
* void displayCharacterStats(Character, Character)
* Used in combat.h
* Prints both character's stats side by side.
*******************************************************************************/
void displayCharacterStats(const Character & player, const Character & monster, 
	                       const short round) { 
   
   string text = 
      "******************************* Combat Round " + to_string(round) +
      " ********************************\n" + 
      "                 " + player.name +
      "                                        " + monster.name + "\n" + 
      "                 HP: " + to_string(player.hitPoints) +
      "                                      HP: " + 
      to_string(monster.hitPoints) + "\n" + "                 BP: " +
      to_string(player.bloodPoints) + 
      "                                      " + 
      "BP: " + to_string(monster.bloodPoints) + "\n" + 
      "                 EP: " + 
      to_string(player.essencePoints) + 
      "                                      " + 
      "EP: " + to_string(monster.essencePoints) + "\n" + 
      "***************************************" +
      "****************************************\n"; 

      writeMessageScroll(text);
}

/*******************************************************************************
* void selectWeapon(Character)
* Temporary function that sets the players weapon for testing purposes.
*******************************************************************************/
void selectWeapon(Character & player) {

	vector<string> wep = {"Broad Sword", "Battle Axe", "Spear", "Mace"};
	short selection = getUserInput(wep);

    player.setWeapon(wep[selection - 1]);
}

/*******************************************************************************
* void selectWeapon(Character)
* Temporary function that sets the players armor for testing purposes.
*******************************************************************************/
void selectArmor(Character & player) {

	vector<string> arm = {"Padding", "Leather", "Ring", "Chain", "Scale", "Plate"};
	short selection = getUserInput(arm);
    player.setArmor(arm[selection - 1]);
}

/*******************************************************************************
* void bleedingMessage(Character)
* Displays the damage amount if beeding is in affect.
*******************************************************************************/
void bleedingMessage(const Character & victim) {
   string message = "";
   if(!victim.isHero)
      message += "The ";
   message += victim.name + " is bleeding from ";
   if(!victim.isHero)
      message += "its ";
   else
   	  message += "their "; 
   message += "wounds\n\tand takes " + 
   to_string(victim.isBleeding / 10) + " blood point damage!\n\n";
   writeMessage(message); 
}

/*******************************************************************************
* void displayStats(Character)
* Displays character statistics. Used for testing.
*******************************************************************************/
void displayStats(const Character & character) {
   short min = character.weapon->minDamage;
   short range = character.weapon->rangeDamage;
   cout << "***** " << character.name << "'s Stats *****\n"
        << "Weapon:\t\t" << character.weapon->name << "\n"
        << "Damage:\t\t" << min << " - " 
        << (min + range) << "\n"
        << "Crush:\t\t" << character.weapon->crush << "\n"
        << "Chop:\t\t"  << character.weapon->chop  << "\n"
        << "Slash:\t\t" << character.weapon->slash << "\n"
        << "Stab:\t\t"  << character.weapon->stab  << "\n"
        << "Initiative:\t" << character.initiative << "\n"
        << "Armor:\t\t" << character.armor->name << "\n"
        << "Weight:\t\t" << character.armor->weight  << "\n"
        << "Volume:\t\t" << character.armor->volume << "\n"
        << "Defence Power:\t" << character.armor->defencePower << "\n"
        << "Crush:\t\t" << character.armor->crush << "\n"
        << "Chop:\t\t" << character.armor->chop << "\n"
        << "Slash:\t\t" << character.armor->slash << "\n"
        << "Stab:\t\t" << character.armor->stab << "\n"
        << "Weapon Speed:\t" << character.weapon->speed << "\n\n";
}

void stunMessage(const Character & aggressor, const Character & victim) {
   cout << victim.name << " is staggered by the blow of " 
        << aggressor.name << "'s " << aggressor.weapon->name << "!\n\n";
}


#endif // DISPLAY_H