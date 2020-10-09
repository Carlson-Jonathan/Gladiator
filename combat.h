/*******************************************************************************
* combat.h
* Author: Jonathan Carlson
* Description:
*  Governs the combat sequence applying stats from the Character class objects.
*******************************************************************************/
#ifndef COMBAT_H
#define COMBAT_H
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "display.h"

bool debugMode;

Character* nextAction(vector<Character*> cp);
void getDamageSum(short damageTypes[], short block[]);
void getPhysicalDamages(Character, Character);
void convertToHP_BP(const Character & victim, short rawDamage[], short dT[]);
bool applyDamage(Character & victim, short rawDamage[]); 
void determineAffliction(const Character & aggressor, Character & victim, 
                         short damage[]);
bool applyBleeding(Character & victim);
void focus(Character & character);
void flee();
bool isDefeated(short HP, short BP, short EP);
bool receiveHazardDamage(Character & aggressor, const Character & victim, 
                         short (&damageHpBpEp)[3]);
bool attackCharacter(Character & aggressor, Character & victim, 
                     short (&damageHpBpEp));
bool inline sorter(Character* a, Character* b);
bool executeEOTactions(vector<Character*> combatParticipants);
vector<Character*> generateParticipantList(Character & player, short size);
void combat(Character & player);
void killMonster(vector<Character*> & staticL, vector<string> & displL, 
                 vector<Character*> & cpL, short option);
bool missedAttack(const Character & aggressor, const Character & victim);

/*******************************************************************************
* Character* nextAction(vector<Character*>)
* Receives the list of combat participants, sorts it by the running initiative
* member, then returns the first participant (with the lowest value).
*******************************************************************************/
Character* nextAction(vector<Character*> cp) {
   sort(cp.begin(), cp.end(), sorter);

   if(debugMode) {
      cout << "\t\t\t\t\tInitiatives | Running Initiatives" << endl; 
      for(auto i : cp) {
         cout.width(40);
         cout << right << i->name << ": " << i->initiative 
              << " | " << i->runningInitiative << endl;
      }
      cout << endl;    
   }

   cp[0]->runningInitiative += cp[0]->initiative;

   return cp[0];
}

/*******************************************************************************
* void getDamageSum(short, short[])
* Applies the damage reduction of the armor assuring that it does not go below 
* 0. The formula applied is to reduce each damage type by the block damage
* type as a percentage.
*******************************************************************************/
void getDamageSum(short damageTypes[], short block[]) {
   for(short i = 0; i < 4; i++) {
      damageTypes[i] *= (1.0 - ((float)block[i] / 100));
      if(damageTypes[i] < 0)
         damageTypes[i] = 0;
   }
}

/*******************************************************************************
* void getPhysicalDamages(Character, Character, short[])
* Gets the damage types generated by the aggressor's weapon, gets the defence
* values generated by the victim's armor, sums them, converts them to HP/BP/EP,
* and sets them to the address of a short[]; 
*******************************************************************************/
void getPhysicalDamages(Character & victim, Character & aggressor, 
                        short damageHpBpEp[]) {

   if(aggressor.weapon->getRandomDamageTypes())
      cout << "Critical Strike!" << "\n\n";

   if(debugMode) cout << "\t\t\t" << aggressor.name << " damage Types:" << endl;
   if(debugMode) cout << "\t\t\t" << "Cr: " << aggressor.weapon->damageTypes[0] 
                      << " | Ch: " 
        << aggressor.weapon->damageTypes[1]  << " | Sl: " 
        << aggressor.weapon->damageTypes[2]  << " | St: " 
        << aggressor.weapon->damageTypes [3] << "\n\n";

   if(debugMode) cout << "\t\t\t" << victim.name 
                      << " armor block values based on defence power: " 
                      << victim.armor->defencePower << endl;
   if(debugMode) cout << "\t\t\tCrush: " << victim.armor->damageReduce[0] 
                      << " | Chop: "  << victim.armor->damageReduce[1] 
                      << " | Slash: " << victim.armor->damageReduce[2] 
                      << " | Stab: "  << victim.armor->damageReduce[3] << "\n\n";

   getDamageSum(aggressor.weapon->damageTypes, victim.armor->damageReduce);
   if(debugMode) cout << "\t\t\t" << aggressor.name << " modified Damage Types:"
                      << endl;
   if(debugMode) cout << "\t\t\tCr: " << aggressor.weapon->damageTypes[0] 
                      << " | Ch: " 
                      << aggressor.weapon->damageTypes[1] << " | Sl: " 
                      << aggressor.weapon->damageTypes[2] << " | St: " 
                      << aggressor.weapon->damageTypes [3] << "\n\n";

   convertToHP_BP(victim, damageHpBpEp, aggressor.weapon->damageTypes);
   if(debugMode) cout << "\t\t\t" << "Raw Damage using modified types:" << endl;
   if(debugMode) cout << "\t\t\tHP: " << damageHpBpEp[0] << " | BP: "
                      << damageHpBpEp[1] << " | EP: " << damageHpBpEp[2] 
                      << "\n\n";
}

/*******************************************************************************
* void convertToHP_BP(Character, int, short[])
* Accepts either the Hero or Monster type objects and uses the weapon object
* set in that type to determine the amount of damage that will be inflicted
* per combat round. Basically it splits the 4 damage types into 3 health types.
*******************************************************************************/
void convertToHP_BP(const Character & victim, short rawDamage[], short dT[]) {

       // dT[0] = Crush, dT[1] = Chop, dT[2] = Slash, dT[3] = Stab            
   rawDamage[0] = dT[0] + ceil(dT[2] * 0.34) + ceil(dT[1] * 0.66),   // HP
   rawDamage[1] = dT[3] + ceil(dT[2] * 0.66) + ceil(dT[1] * 0.34),   // BP
   rawDamage[2] = 0;                                                 // EP

   if(victim.isDefending) 
      rawDamage[0] /= 2; rawDamage[1] /= 2; rawDamage[2] /= 2;
   
}

/*******************************************************************************
* int applyDamage(Character, short[]) 
* Applies the calculated rawDamage to the victim's health and determines if
* the victim has been defeated.
*******************************************************************************/
bool applyDamage(Character & victim, short rawDamage[]) {
   victim.setHitPoints(-rawDamage[0]);
   victim.setBloodPoints(-rawDamage[1]);
   victim.setEssencePoints(-rawDamage[2]);

   if(isDefeated(victim.hitPoints, victim.bloodPoints, victim.essencePoints)) 
      return true;
   return false;
}

/*******************************************************************************
* void determineAffliction(Character, Character, short[])
* Extracts weapon information to determine which types of afflictions apply.
*******************************************************************************/
void determineAffliction(const Character & aggressor, Character & victim, 
                         short damageTypes[]) {

   Weapon *wep = aggressor.weapon;

   // Afflictions that apply only if the victim is not defending
   if(!victim.isDefending) {

      // Sets a bleeding affliction 
      if(wep->isSharp) {
         victim.isBleeding += ceil(damageTypes[3] * 0.2 + damageTypes[2] * 
         0.1) * 10;
      }
      
      // Sets a stun affliction (skips the victim's next turn).
      if(wep->canStun)
         if(damageTypes[0] > aggressor.weapon->minDamage + 
            aggressor.weapon->rangeDamage / 2) { // Damge > than 50% of potential
            stunMessage(aggressor, victim);
            victim.runningInitiative += wep->canStun;
         }

      // Slows base initiative by venom stat
      if(wep->venomous) {
         victim.initiative += wep->venomous;   
         cout << victim.name << "'s movement is slowed by the " << aggressor.name 
              << "'s attack!\n\n";
      }

   // Set Affliction


   // ...
   }
}

/*******************************************************************************
* void applyBleeding(Character)
* Governs 1 round of character bleeding. Sets and reduces ongoing bleed effect.
*******************************************************************************/
bool applyBleeding(Character & victim) {
   short bleedAmt = victim.isBleeding / 10;
   
   victim.bloodPoints -= bleedAmt;
   if(victim.bloodPoints < 0)
      victim.bloodPoints = 0;
   
   bleedingMessage(victim);
   if(isDefeated(victim.hitPoints, victim.bloodPoints, victim.essencePoints)) 
      return true;

   victim.isBleeding -= bleedAmt - 2;
   if(victim.isBleeding < 0)
      victim.isBleeding = 0;
   return false;
}

/*******************************************************************************
* void focus(Character, Character)
* Sets the player's defend status to true.
*******************************************************************************/
void focus(Character & character) {
   character.isDefending = true;
   cout << "\t" << character.name 
        << " raises their guard and plans their next strike.\n" << endl;
   // Increases damage on next strike (allows for criticals?).
   // Increases chance to apply affliction on next strike.
   // Can be used to overcome enemy strengths (tough defence).
}

/*******************************************************************************
* void flee()
* Will house the flee function.
*******************************************************************************/
void flee() {
   // Based on yours and the monster's health
   cout << "\tYou run away screaming like a little girl!" << endl;
}

/*******************************************************************************
* bool isDefeated(short, short, short)
* Tells whether or not a character is dead.
*******************************************************************************/
bool isDefeated(short HP, short BP, short EP) {
   return !(HP && BP && EP);
}

/*******************************************************************************
* bool receiveHazardDamage(Character, Character, short[])
* Calculates and applies reflective damage.
*******************************************************************************/
bool receiveHazardDamage(Character & aggressor, const Character & victim, 
                         short (&damageHpBpEp)[3]) {

    for(auto &i : damageHpBpEp)
        i /= victim.isHazardous;

    hazardDamageMessage(aggressor, damageHpBpEp);
    if(applyDamage(aggressor, damageHpBpEp)) return true;

    return false;
}

/*******************************************************************************
* bool attackCharacter(Character, Character, short[])
* Performs all functions in an attack action ending with receiving reflect dmg.
*******************************************************************************/
short attackCharacter(Character & aggressor, Character & victim, 
                     short (&damageHpBpEp)[3]) {

   if(!missedAttack(aggressor, victim)) {
      getPhysicalDamages(victim, aggressor, damageHpBpEp);
      displayAttackMessage(victim, aggressor, damageHpBpEp);
      if(applyDamage(victim, damageHpBpEp)) return 1;
      determineAffliction(aggressor, victim, aggressor.weapon->damageTypes);

      if(victim.isHazardous) 
         if(receiveHazardDamage(aggressor, victim, damageHpBpEp))
            return 2;
   }
   else
      cout << aggressor.name << aggressor.weapon->actionDescription 
           << victim.name << " but misses!\n\n";
       
   return 0;
}

/*******************************************************************************
* bool sorter(Character*, Character*)
* Used in combination with the overloaded '<' operator in character.h to sort
* a vector of character object pointers.
*******************************************************************************/
bool inline sorter(Character* a, Character* b) {return  (*a < *b);}

// If all participant's running initiative's exceed 200, the round is over.
bool isEndOfTurn(vector<Character*> combatParticipants) {
   for(auto i : combatParticipants)
      if(i->runningInitiative <= 200)
         return false;
   return true;
}

/*******************************************************************************
* bool executeEOTactions(vector<Character*>)
* Perform all turn ending actions at the end of a combat round. The end of turn
* is defined as when all combat participants have a running initiative greater 
* than 200. Initiatives are reset, and relevant afflictions are applied.
*******************************************************************************/
bool executeEOTactions(vector<Character*> combatParticipants) {
   for(auto participant : combatParticipants) { 
      participant->runningInitiative -= 200;
      if(participant->isBleeding) 
         if(applyBleeding(*participant)) 
            return true;
   }
   return false;
}

/*******************************************************************************
* vector<Character*> generateParticipantList(Character, short)
* Creates a vecotr of object pointers. Includes the player(s) and generates 
* 'size' number of random new monster objects to include. 
*******************************************************************************/
vector<Character*> generateParticipantList(Character & player, short size, 
                                           string newMonster) {
   vector<Character*> combatParticipants;
   Character* participant;
   Character* monster;
   participant = &player;
   combatParticipants.push_back(participant);
   for(short i = 0; i < size; i++) {
      participant = new Character(newMonster);
      combatParticipants.push_back(participant);
      monster = participant;
   }
   return combatParticipants;
}

/*******************************************************************************
* void killMonster(vector<Character*>, vector<string>, vectorCharacter*>, short)
* When monster is defeated, this function is called to remove the monster from 
* the 3 lists used in the combat function. It also deletes the associated 
* pointers/objects. 
*******************************************************************************/
void killMonster(vector<Character*> & staticL, vector<string> & displL, 
                 vector<Character*> & cpL, short option) {
   delete staticL[option - 1];
   staticL.erase(staticL.begin() + option - 1);
   displL.erase(displL.begin() + option - 1);
   for(int i = 0; i < cpL.size(); i++)
      if(isDefeated(cpL[i]->hitPoints, cpL[i]->bloodPoints, cpL[i]->essencePoints)) {
         cpL.erase(cpL.begin() + i);
      }
}

bool missedAttack(const Character & aggressor, const Character & victim) {
   short willMiss = aggressor.percision - victim.evasion;
   return (rand() % 100) >= willMiss;
}




/*##############################################################################
################################################################################
################################################################################
################################################################################
################################################################################
################################################################################
################################################################################
##############################################################################*/





/*******************************************************************************
* void combat(Character)
* Houses the primary combat loop. Brings all other functions together to form
* a combat sequence.
*******************************************************************************/
void combat(Character & player, string newMonster, bool debug, short size) {

   srand(time(0));
   debugMode = debug;          // Toggle in main.cpp
   srand(time(0));             // Seeds sudo random number generator
   bool battle = true;
   Character* participant;
   player.initiative = 100 + player.weapon->speed; // Sets default initiative
   short 
      died,
      option,
      round = 1,
      damageHpBpEp[3];

   vector<Character*> combatParticipants = 
                      generateParticipantList(player, size, newMonster);
   vector<Character*> staticParticipantsList = combatParticipants;
   staticParticipantsList.erase(staticParticipantsList.begin());
   vector<string> listOfMonsters;
   for(auto i : staticParticipantsList)
      listOfMonsters.push_back(i->name);
   
   // Temporaries. Don't use these later. display.h changes character objects.
   selectWeapon(player);
   selectArmor(player);

   if(debugMode) displayStats(player);

   while(battle) {
      participant = nextAction(combatParticipants);
      if(participant->isDefending) participant->isDefending = false;

      /**********************************************************************
      *                     Turn Ending Action Block
      * Code in this block will be executed after any turn, player or monster
      **********************************************************************/
      if(participant->bloodPoints < participant->maxBloodPoints * 0.66) {
  	     short additionalInit = 
            (participant->maxBloodPoints * 0.66 - participant->bloodPoints) / 4;

         participant->runningInitiative += additionalInit;
  	     fatigueMessage(*participant, additionalInit);
  	  } 
      
      /**********************************************************************
      *                        Player's Action Block
      **********************************************************************/
      if(participant->name == player.name) {        
         
         // Displays player and monster stats for testing.
         displayCharacterStats(staticParticipantsList, player, round++);
         option = getUserInput({"Attack", "Defend", "Flee"});

         // Set player action
         if (option == 1) {
            if(listOfMonsters.size() > 1) 
               option = getUserInput(listOfMonsters); 
            else
               option = 1;
            Character* monster = staticParticipantsList[option - 1];

            // Player could kill a monster or themselves while attacking 
            died = attackCharacter(player, *monster, damageHpBpEp);
            if(died == 1) {
               killMonster(staticParticipantsList, listOfMonsters, 
                           combatParticipants, option); 
               if(!listOfMonsters.size()) {
                  combatVictory(player, *monster);
                  break;
               }
            }
            else if(died == 2) {
               combatDefeat();
               break;
            }
         }
         else if (option == 2) {
            focus(player);
         }
         else if(option == 3) {
            flee();
         }

      } 
      else {
         /**********************************************************************
         *                        Monster's Action Block
         **********************************************************************/
         died = attackCharacter(*participant, player, damageHpBpEp);
         if(died == 1) {
            combatDefeat();
            break;
         }
         else if(died == 2) {
            combatVictory(player, *participant);
            break;
         }

         // Set retaliation against monster attack
         // Set retaliation afliction against monster
         // Set residual actions
      }

   /**********************************************************************
   *                     Round Ending Action Block
   * This block is called after 200 time units (initiative) has passed.
   * Afflictions such as bleeding should be placed in this block of code.
   **********************************************************************/
   if(isEndOfTurn(combatParticipants)) 
       if(executeEOTactions(combatParticipants)) {
          cout << "\tSomething just bled to death." << endl;
          break;
       }
   }

   cout << "\nDont forget to reset world affecting stats at the end of combat!" 
        << endl;
   displayStats(player);
}

/******************************************************************************/

#endif // COMBAT_H

/*******************************************************************************
* To do as of 10/08/2020:
* Chop can inflict critical damage
* Create a riposte ability and assign to rapier.
* Create evasion ability and coresponding low HP penalty.
* Create perscision stat.
* Make 'defend' do something (increase damage (implements riposte?))
*******************************************************************************/
