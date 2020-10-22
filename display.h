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
using namespace std;

/*******************************************************************************
* Prototypes
*******************************************************************************/
short getUserInput          (const vector<string> options);
string writeMessage         (const string message);
void writeMessageScroll     (const string message);
void combatVictory          (const Character & player);
void combatDefeat           ();
void displayAttackMessage   (const Character & victim, const Character & aggressor, const short damage[]);
void displayCharacterStats  (const Character & player, const Character & monster, const short round);
void selectWeapon           (Character & player);   // To be deleted
void selectArmor            (Character & player);    // To be deleted
void bleedingMessage        (const Character & victim);
void displayStats           (const vector<Character> & heroes);
void stunMessage            (const Character & aggressor, const Character & victim);
void hazardDamageMessage    (const Character & aggressor, short damageHpBpEp[]);
void fatigueMessage         (const Character & victim,    short init);
void missedAttackMessage    (const Character & aggressor, const Character & victim);
void riposteMessage         (const Character & victim,    const Character & aggressor);
void defendingMessage       (const Character & character);
void regenerationMessage    (const Character & character);

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

//    if (char_array != NULL) 
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
void combatVictory(const Character & player) {
   
   string message = "\t";
   message += "All monsters have been defeated!"; 
	
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
	writeMessage("Y O U   H A V E   B E E N   D E F E A T E D !\n\n");
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

   if(aggressor.weapon->isCritical) {
      aggressor.weapon->isCritical = false;
      writeMessage("\tC R I T I C A L   S T R I K E !\n");
   }

   if(aggressor.isHero)
      message += "The ";
   message += victim.name + " takes damage:";
   writeMessage(message);

   cout << "\n\t\tHP: -" << damage[0] << "  |  " << "BP: -" << damage[1] 
        << "  |  " << "EP: -" << damage[2] << "\n";

   usleep(700000);
   cout << endl;
}

/*******************************************************************************
* void displayCharacterStats(vector<Character*>)
* Used in combat.h
* Prints characters' in rows.
*******************************************************************************/
void displayCharacterStats(const vector<Character*> & listOfMonsters, 
                           const vector<Character*> & heroes, const short round) { 
   
   short pEvasion, mEvasion, pPrecision, mPrecision;

   cout << "================================ Combat Turn " << round 
        << " ===============================\n";

   cout << setw(12) << "Name:" << setw(10) << right << "HP:" << setw(10) 
        << right << "BP:" << setw(10) << right << "EP:" << setw(10) << right
        << "Speed:" << setw(10) << "Aim:" << setw(10) << "Evade" << endl;
   for(const auto & i : heroes) {      
      pEvasion = i->evasion - i->evasionPenalty;
      pPrecision = i->precision - i->precisionPenalty;
      cout << setw(12) << right << i->name << setw(10) << i->hitPoints
           << setw(10) << i->bloodPoints << setw(10) << i->essencePoints
           << setw(10) << i->initiative << setw(10) << pPrecision 
           << setw(10) << pEvasion << endl;
   }
   cout << 
   "       -----------------------------------------------------------------\n";
   for(const auto & i : listOfMonsters) {
      mEvasion = i->evasion - i->evasionPenalty;
      mPrecision = i->precision - i->precisionPenalty;
      cout << setw(12) << i->name << setw(10) << right << setw(10) << right
           << i->hitPoints << setw(10) << right << i->bloodPoints << setw(10)
           << right << i->essencePoints << setw(10) << right 
           << i->initiative << setw(10) << mPrecision << setw(10)
           << mEvasion;
      if(i != listOfMonsters.back()) 
         cout << endl;
   }

   cout << "\n=======================================" 
        << "========================================\n"; 
}

/*******************************************************************************
* void selectWeapon(Character)
* Temporary function that sets the players weapon for testing purposes.
*******************************************************************************/
void selectWeapon(Character & hero) {

    cout << "Select weapon for " << hero.name << endl;
	vector<string> wep = 
	   {"Broad Sword", 
	    "Battle Axe", 
	    "Spear", 
	    "Mace",
	    "Morning Star",
	    "Katana",
	    "Fists",
        "Rapier"};
	short selection = getUserInput(wep);

    hero.setWeapon(wep[selection - 1]);
}

/*******************************************************************************
* void selectWeapon(Character)
* Temporary function that sets the players armor for testing purposes.
*******************************************************************************/
void selectArmor(Character & hero) {

    cout << "Select armor for " << hero.name << endl;
	vector<string> arm = {"Naked",
                          "Fighting Gi",
                          "Pads", 
                          "Leather", 
                          "Ring", 
                          "Chain", 
                          "Blood Scale", 
                          "Plate"};
	short selection = getUserInput(arm);
    hero.setArmor(arm[selection - 1]);
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
* void displayStats(vector<Character>)
* Displays character statistics. Used for testing.
*******************************************************************************/
void displayStats(const vector<Character> & heroes) {
   short min, range;
   for(const auto & i : heroes) {
      min = i.weapon->minDamage;
      range = i.weapon->rangeDamage;
      cout << "***** " << i.name << "'s Stats *****\n"
           << "Weapon:\t\t" << i.weapon->name << "\n"
           << "Damage:\t\t" << min << " - " 
           << (min + range) << "\n"
           << "Crush:\t\t" << i.weapon->crush << "\n"
           << "Chop:\t\t"  << i.weapon->chop  << "\n"
           << "Slash:\t\t" << i.weapon->slash << "\n"
           << "Stab:\t\t"  << i.weapon->stab  << "\n"
           << "Initiative:\t" << i.initiative << "\n"
           << "Armor:\t\t" << i.armor->name << "\n"
           << "Weight:\t\t" << i.armor->weight  << "\n"
           << "Volume:\t\t" << i.armor->volume << "\n"
           << "Defence Power:\t" << i.armor->defencePower << "\n"
           << "Crush:\t\t" << i.armor->crush << "\n"
           << "Chop:\t\t" << i.armor->chop << "\n"
           << "Slash:\t\t" << i.armor->slash << "\n"
           << "Stab:\t\t" << i.armor->stab << "\n"
           << "Weapon Speed:\t" << i.weapon->speed << "\n\n";
   }
}

/*******************************************************************************
* void stunMessage(const Character&, const Character&)
* When stun applies, displays this.
*******************************************************************************/
void stunMessage(const Character & aggressor, const Character & victim) {
   cout << victim.name << " is staggered by the blow of " 
        << aggressor.name << "'s " << aggressor.weapon->name << "!\n\n";
}

/*******************************************************************************
* void hazardDamageMessage(const Character&, short[])
* Displays character statistics. Used for testing.
*******************************************************************************/
void hazardDamageMessage(const Character & aggressor, short damageHpBpEp[]) {
    string message = aggressor.name + 
    " was injured durring the attack and takes damage!\n";
    writeMessage(message);
    cout << "\t\tHP: -" << damageHpBpEp[0] << "  |  BP: -" << damageHpBpEp[1] 
    << "  |  EP: -" << damageHpBpEp[2] << "\n\n";
}

/*******************************************************************************
* void fatigueMessage
* Displays message if character BP < 2/3 max.
*******************************************************************************/
void fatigueMessage(const Character & victim, short init) {
   string message = "\t" + victim.name + " is fatigued from loss of blood.\n\t\t\t+" +
   to_string(init) + " slow\n\t\t\t-" + to_string((short)((1 - 
   	victim.weapon->basePenalty) * 100)) + "% damage\n\n";
   writeMessage(message);
}

/*******************************************************************************
* void dazedMessage
* Displays message if character HP < 2/3 max.
*******************************************************************************/
void dazedMessage(const Character & victim, short aim, short evade) {
   string message = "\t" + victim.name + " is dazed from blunt trauma.\n\t\t\t-" +
   to_string(aim) + " precision\n\t\t\t-" + to_string(evade) + " evasion\n\n";
   writeMessage(message);
}

/*******************************************************************************
* void missedAttackMessage(const Character&, const Character&)
* Displays when attacker's precision is less than random+defender's evasion.
*******************************************************************************/
void missedAttackMessage(const Character & aggressor, const Character & victim) {
   string message = "\t";
   if(!aggressor.isHero)
      message += "The ";
   message += aggressor.name + aggressor.weapon->actionDescription + victim.name +
   " but misses!\n\n";
   writeMessage(message);
}

/*******************************************************************************
* riposte(Character, Character)
* Displays riposte message.
*******************************************************************************/
void riposteMessage(const Character & victim, const Character & aggressor) {
   string message = "\t";
   if(!victim.isHero)
      message += "The ";
   message += victim.name + " recoils and strikes back at ";
   if(!victim.isHero)
      message += "the ";
   message += aggressor.name + "!\n\n";
   writeMessage(message);
}

/*******************************************************************************
* void defendingMessage(Character)
* Displays defend message.
*******************************************************************************/
void defendingMessage(const Character & character) {
   string message = "";
      if(!character.isHero)
         message += "The ";
   message += character.name + 
   " raises their guard and prepares for the next attack.\n";
   message += "\t\t\tPrecision +" + to_string(character.weapon->precisionBonus) +
   "\n\t\t\tDefence +" + to_string(character.armor->defendBonus) + "\n\t\t\t" +
   "Evasion +" + to_string(character.armor->evadeBonus) + 
   "\n\t\t\t+New affliction immunity" + "\n\t\t\tCritical Chance +" + 
   to_string(character.weapon->criticalBonus);
   if(character.weapon->riposte)
      message += "\n\t\t\t+Riposte";
   message += "\n\n"; 
   writeMessage(message); 
}

void regenerationMessage(const Character & character) {
    string message = "\t";
    if(!character.isHero)
         message += "The ";
    message += character.name + " feels revitalized and gains " + 
    to_string(character.regeneration) + " blood points!\n\n";
    writeMessage(message);
}

/******************************************************************************/

#endif // DISPLAY_H