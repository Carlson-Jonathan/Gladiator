/******************************************************************************
* combat.cpp
* Author: Jonathan Carlson
* Last Updated: September 2020
* Description:
*  Governs the combat sequence applying stats from the Character class objects. 
******************************************************************************/
#ifndef DISPLAY_H
#define DISPLAY_H
#include <iostream>
#include <iomanip>
#include <cstdlib>  // sleep
#include <unistd.h> // sleep
#include <stdlib.h> // Clear screen
#include "character.h"
#include "general.h"
using namespace std;


/******************************************************************************
* void getUserInput(vector<string>)
* Aquires and validates user input. Parameter is a list of options.
******************************************************************************/
short getUserInput(vector<string> options) {
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

/******************************************************************************
* void anyKeyToContinue
* Pauses until the user presses a key.
******************************************************************************/
void anyKeyToContinue() {
   cout << setw(42) << "...\n\n";
   string x;
   getline(cin, x);
   cin.clear(); 
   cin.ignore(std::numeric_limits<int>::max(),'\n');
}

/******************************************************************************
* void writeMessage(string)
* Prints the message to the screen one letter at a time at a specified pace.
******************************************************************************/
string writeMessage(string message) {
	cout << "\t";
	for(char i : message) {
		cout << i;
		cout.flush();
		usleep(10000);
	}
	return "\t";
}

/******************************************************************************
* combatVictory
* Prints the message to the screen one letter at a time at a specified pace.
******************************************************************************/
void combatVictory(Character player, Character monster) {
	string message = "\t";
	message += "The "; message += monster.getName(); 
	message += " drops to the ground writhing in agony.";
	
	message = writeMessage(message);
	usleep(1000000);
	cout << endl;

	cout << "======================================="
	     << "=======================================\n"
	     << setw(59) << "Y O U   A R E   V I C T O R I O U S !\n"
	     << "======================================="
	     << "=======================================\n";	
	usleep(1000000);

	cout << "\n\t***************\n" << "\tRewards:\n" << "\tCash + $0.23\n" 
	     << "\tPopularity + 10\n" << "\tLoose women + 0\n" 
	     << "\t***************\n"; 
}

/******************************************************************************
* void displayAttackMessage(Character, Character)
* Used in combat.h
* Prints the attack action, eg. "The Cobra strikes at <player>"
******************************************************************************/
void displayAttackMessage(Character & victim, Character & aggressor, short damage[]) {
   
   string message = "", x;
   if(!aggressor.isHero())
      message += "The ";
   message += aggressor.getName() += aggressor.getWeapon()->getAction();
   if(aggressor.isHero())
      message += "the ";
   message += victim.getName();
   if(aggressor.isHero()) {
      message += " with the "; 
      message += aggressor.getWeapon()->getName();
   }
   message += "!\n";

   message = writeMessage(message);
   usleep(300000);

   if(!aggressor.isHero())
      message += "The ";
   message += victim.getName() += " takes damage:";
   writeMessage(message);

   cout << "\n\t\tHP: -" << damage[0] << "  |  " << "BP: -" << damage[1] << "  |  "
        << "EP: -" << damage[2] << "\n";

   usleep(700000);
   cout << endl;
}

/******************************************************************************
* void displayCharacterStats(Character, Character)
* Used in combat.h
* Prints both character's stats side by side.
******************************************************************************/
void displayCharacterStats(Character player, Character monster, short round) { 
   cout << "******************************* Combat Round " << round 
        << " ********************************\n"
        << setw(20) << player.getName() << setw(46) 
        << monster.getName() << "\n"
        << setw(17) << "HP: " << player.getHitPoints() << setw(43) 
        << "HP: " << monster.getHitPoints() << "\n"
        << setw(17) << "BP: " << player.getBloodPoints() << setw(43)
        << "BP: " << monster.getBloodPoints() << "\n"
        << setw(17) << "EP: " << player.getEssencePoints() << setw(43)
        << "EP: " << monster.getEssencePoints() << "\n"
        << "***************************************"
        << "****************************************" 
        << endl;
}


#endif // DISPLAY_H