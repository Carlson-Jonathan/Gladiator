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

/*******************************************************************************
* Prototypes
*******************************************************************************/
Character* nextAction     (vector<Character*> cp);
void getDamageSum         (short damageTypes[], short block[]);
void getPhysicalDamages   (Character & victim, Character & aggressor, short damageHpBpEp[]);
void convertToHP_BP       (const Character & victim, short rawDamage[], short dT[]);
void applyDamage          (Character & victim, short rawDamage[]); 
void determineAffliction  (const Character & aggressor, Character & victim, short damageTypes[]);
bool applyBleeding        (Character & victim);
void focus                (Character & character);
void flee                 ();
bool isDefeated           (Character & victim);
void receiveHazardDamage  (Character & aggressor, const Character & victim, short (&damageHpBpEp)[3]);
short attackCharacter     (Character & aggressor, const Character & victim, short (&damageHpBpEp)[3]);
bool sorter               (Character* a, Character* b);
bool isEndOfTurn          (vector<Character*> combatParticipants);
vector<Character*> generateParticipantList(Character & player, short size, string newMonster);
void killMonster          (vector<Character*> & staticL, vector<string> & displL, vector<Character*> & cpL, short option);
bool missedAttack         (const Character & aggressor, const Character & victim);
void combat               (Character & player);

/*******************************************************************************
* Character* nextAction(vector<Character*>)
* Receives the list of combat participants, sorts it by the running initiative
* member, then returns the first participant (with the lowest value).
*******************************************************************************/
Character* nextAction(vector<Character*> cp) {
   sort(cp.begin(), cp.end(), sorter);

   if(debugMode) {
      cout << "\t\t\tInitiatives | Running Initiatives" << endl; 
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

   aggressor.weapon->setCriticalDamage(aggressor.weapon->setRandomDamageTypes());

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
* void applyDamage(Character, short[]) 
* Applies the calculated rawDamage to the victim's health.
*******************************************************************************/
void applyDamage(Character & victim, short rawDamage[]) {
   victim.setHitPoints(-rawDamage[0]);
   victim.setBloodPoints(-rawDamage[1]);
   victim.setEssencePoints(-rawDamage[2]);
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

   // Set additional afflictions

   // ...

   }
}

/*******************************************************************************
* bool applyBleeding(Character)
* Governs 1 round of character bleeding. Sets and reduces ongoing bleed effect.
*******************************************************************************/
bool applyBleeding(Character & victim) {
   short bleedAmt = victim.isBleeding / 10;
   
   victim.bloodPoints -= bleedAmt;
   if(victim.bloodPoints < 0)
      victim.bloodPoints = 0;
   
   bleedingMessage(victim);
   if(isDefeated(victim)) return true;

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
   // Potential uses:        
   // Increases damage on next strike (allows for criticals?).
   // Increases chance to apply affliction on next strike.
   // Can be used to overcome enemy strengths (tough defence).
}

/*******************************************************************************
* void flee()
* Will house the flee function. All it does right now is end the combat.
*******************************************************************************/
void flee() {
   // Based on yours and the monster's health
   cout << "\tYou run away screaming like a little girl!" << endl;
}

/*******************************************************************************
* bool isDefeated(short, short, short)
* Tells whether or not a character is dead.
*******************************************************************************/
bool isDefeated(Character & victim) {
   if(!(victim.hitPoints && victim.bloodPoints && victim.essencePoints)) {
      if(debugMode) cout << "This victim has been identified as dead!\n\n";
      victim.isDead = true; 
  }
  return false;
}

/*******************************************************************************
* void receiveHazardDamage(Character, Character, short[])
* Calculates and applies reflective damage.
*******************************************************************************/
void receiveHazardDamage(Character & aggressor, const Character & victim, 
                         short (&damageHpBpEp)[3]) {

    for(auto &i : damageHpBpEp)
        i /= victim.isHazardous;

    hazardDamageMessage(aggressor, damageHpBpEp);
    applyDamage(aggressor, damageHpBpEp);
    isDefeated(aggressor);
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
      applyDamage(victim, damageHpBpEp);
      if(isDefeated(victim)) return 1;
      determineAffliction(aggressor, victim, aggressor.weapon->damageTypes);

      if(victim.isHazardous) 
      receiveHazardDamage(aggressor, victim, damageHpBpEp);
   }
   else
      missedAttackMessage(aggressor, victim);

   return 0;
}

/*******************************************************************************
* bool sorter(Character*, Character*)
* Used in combination with the overloaded '<' operator in character.h to sort
* a vector of character object pointers.
*******************************************************************************/
bool sorter(Character* a = NULL, Character* b = NULL) {return  (*a < *b);}


/*******************************************************************************
* bool isEndOfTurn(vector<Character*>)
* The end of a combat round is marked when all characters have exceeded 200
* running initiative units. 
*******************************************************************************/
// If all participant's running initiative's exceed 200, the round is over.
bool isEndOfTurn(vector<Character*> combatParticipants) {
   for(auto i : combatParticipants)
      if(i->runningInitiative <= 200)
         return false;
   return true;
}

/*******************************************************************************
* vector<Character*> generateParticipantList(Character, short)
* Creates a vector of object pointers. Includes the player(s) and generates 
* 'size' number of random new monster objects to include. 
*******************************************************************************/
vector<Character*> generateParticipantList(Character & player, short size, 
                                           string newMonster) {
   vector<Character*> combatParticipants;
   Character* participant = NULL;
   Character* monster = NULL;
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
* Yes, I know it looks like a mess. I had to educate myself on preventing 
* memory leaks and dangling pointers, so I made a mess of "cout"s. I am leaving
* them here in debug mode just in case.
*
* This function kills a monster. It removes it from both vectors of pointers, 
* nullifies the said pointers, and deletes (destroys) the monster object.  
*******************************************************************************/
void killMonster(vector<Character*> & staticL, vector<string> & displL, 
                 vector<Character*> & cpL, short option) {
   
   if(debugMode) cout << "Calling for object removal from static list..." 
                      << endl;
   if(debugMode) cout << "The value of option is " << option << endl;
   if(debugMode) cout << "Item being deleted is " 
                      << staticL[option - 1]->name << endl;
   if(debugMode) cout << "Static list printout:" << endl;

   if(debugMode) for (auto i : staticL)
      cout << i->name << endl;

   if(debugMode) cout << endl;

   if(debugMode) cout << "Object to be erased: " 
                      << (*(staticL.begin() + (option - 1)))->name << "\n\n";
   if(debugMode) cout << "Nullifying pointer...\n";
   staticL[option - 1] = NULL;
   if(debugMode) cout << "Pointer nullified.\n";
   if(debugMode) cout << "Erasing pointer from list...\n";
   staticL.erase(staticL.begin() + (option - 1));
   if(debugMode) cout << "Pointer erased!\n";
   if(debugMode) cout << "New static list of monsters:\n";
   if(debugMode) for (auto i : staticL)
      cout << i->name << endl;
   if(debugMode) cout << "\n\n";

   if(debugMode) cout << "Moving on to removing object from cpL list:\n";
   for(int i = cpL.size() - 1; i >= 0; i--) {
      if(debugMode) cout << "Checking for defeat condition of cpL[" 
                         << i << "] : " << cpL[i]->name << "\n\n";
      if(cpL[i]->isDead) {
         if(debugMode) cout << "This object should be erased!\n"; 
         if(debugMode) cout << "The value of 'i' in this backwards loop is " 
                            << i << endl;
         if(debugMode) cout << "The objects in the list are: " << endl;
         if(debugMode) for (int j = 0; j < cpL.size(); j++) {
            cout << "object cpL[" << j << "]: ";
         	  cout << cpL[j]->name << endl; 
         }
         if(debugMode)cout << "Calling 'delete' on object in sorting list, cpL[" 
                           << (i) << "]" << endl;      	
         delete cpL[i];
         if(debugMode) cout << "Nullifying pointer...\n";
         cpL[i] = NULL;     	
         if(debugMode) cout << "Pointer nullified!\n";
         if(debugMode)cout << "Erasing object " << (*(cpL.begin() + i)) 
           << " from sorting list of monsters..." << endl;
         cpL.erase(cpL.begin() + i);
         if(debugMode) cout << "Object erased!" << endl;
         if(debugMode) cout << "Object has been destroyed! " 
                            << "All dangling pointers have been de-weaponized!\n";
         if(debugMode) cout << "Monster has been murdered! The end.\n\n";
      }
      else
        if(debugMode) cout << "Object is still alive. Moving on...\n";
   }

   if(debugMode)cout << "Erasing string from list of names..." << endl;
   displL.erase(displL.begin() + (option - 1));
}

/*******************************************************************************
* bool missedAttack(Character, Character)
* Generates a random number. If that number is higher than the aggressor's
* percision minus the victim's evasion, the attack fails.
*******************************************************************************/
bool missedAttack(const Character & aggressor, const Character & victim) {

   short willMiss = aggressor.percision - victim.evasion;
   short missed = rand() % 100;
   if(debugMode) cout << "\t\t\t" << aggressor.name << "'s accuracy: \n\t\t\t" 
   	                  << missed << " | " << willMiss << "\n\n";
   return missed >= willMiss;
}

void riposte(const Character & aggressor, Character & victim) {
   if(!victim.isHero)
      cout << "The ";
   cout << victim.name << " recoils and strikes back at ";
   if(!victim.isHero)
      cout << "the ";
   cout << aggressor.name << "!\n\n";
   short damageHpBpEp[3];
   

//    short died = attackCharacter(aggressor, victim, damageHpBpEp);
//    if(died == 1) {                             // Victim killed aggressor
//       if(!victim.isHero)
//          killMonster(staticParticipantsList, listOfMonsters, combatParticipants, option); 
//    if(!listOfMonsters.size()) {
//    combatVictory(player, *monster);
//    break;
//    }
// }
// else if(died == 2) {            // Victim died while attacking
// combatDefeat();
// break;
// }   
}

void applyRetaliationActions(const Character & aggressor, Character & victim) {

   // Defending reactions
   if(victim.isDefending) {
      if(victim.weapon->riposte > 0) 
         riposte(aggressor, victim);




   }



   // Other reactions

}






/*###  ####  ######################################################  ####  #####
#####  ####  ###################                ###################  ####  #####
#####  ####  ##############                          ##############  ####  #####
#####  ####  ###########      Main Combat Function      ###########  ####  #####
#####  ####  ##############                          ##############  ####  #####
#####  ####  ###################                ###################  ####  #####
#####  ####  ######################################################  ####  ###*/

/*******************************************************************************
* void combat(Character)
* Houses the primary combat loop. Brings all other functions together to form
* a combat sequence.
*******************************************************************************/
void combat(Character & player, string newMonster, bool debug, short size) {

   // General Setup
   debugMode = debug;                // Global variable. Toggle in main.cpp
   srand(time(0));                   // Seeds sudo random number generator
   short 
      died,
      option,
      round = 1,
      damageHpBpEp[3];

   player.initiative = 100 + player.weapon->speed; // Sets default initiative
   Character* participant = NULL;

   // Monster lists
   vector<string> listOfMonsters;
   vector<Character*> combatParticipants = 
                      generateParticipantList(player, size, newMonster);
   vector<Character*> staticParticipantsList = combatParticipants;
   staticParticipantsList[0] = NULL;
   staticParticipantsList.erase(staticParticipantsList.begin());
   for(auto i : staticParticipantsList)
      listOfMonsters.push_back(i->name);
   
   // Temporaries. Don't use these later. display.h changes character objects.
   selectWeapon(player);
   selectArmor(player);

   if(debugMode) displayStats(player);


   /******************************* Combat Loop ********************************/
   while(true) {
      participant = nextAction(combatParticipants);
      if(participant->isDefending) participant->isDefending = false;

      /*************************************************************************
      *                     Turn Ending Action Block
      * Code in this block will be executed after any turn, player or monster
      *************************************************************************/
      
      // Apply Fatigue condition
      if(participant->bloodPoints < participant->maxBloodPoints * 0.66) {
  	     short additionalInit = 
            (participant->maxBloodPoints * 0.66 - participant->bloodPoints) / 4;
         participant->runningInitiative += additionalInit;
  	     fatigueMessage(*participant, additionalInit);
  	  } 

      // Apply Daized Condition here (low HP = poor evasion and percision)
      
      /*************************************************************************
      *                        Player's Action Block
      *************************************************************************/
      if(participant->name == player.name) {        
         
         displayCharacterStats(staticParticipantsList, player, round++);

         // Set player action
         option = getUserInput({"Attack", "Defend", "Flee"});
         if (option == 1) {                                           // Attack
            if(listOfMonsters.size() > 1) 
               option = getUserInput(listOfMonsters);           // Attack what?
            else
               option = 1;                               // Only 1 monster left 
            
            // Set monster target
            Character* monster = staticParticipantsList[option - 1];

            attackCharacter(player, *monster, damageHpBpEp);
            if(monster->isDead) {                   // Player killed monster
               killMonster(staticParticipantsList, listOfMonsters, 
                           combatParticipants, option); 
               cout << "Monster has been killed\n\n" << endl;

               // Check for victory (all monsters dead)
               if(!listOfMonsters.size()) {
                  combatVictory(player, *monster);
                  break;
               }
            }
            // Player died while attacking
            else if(player.isDead) { combatDefeat(); break; }

            // Monster riposte goes here
            // Set retaliation affliction
            // Any other residual actions 

         }
         else if (option == 2) {
            focus(player);                                // Player is defending
         }
         else if(option == 3) {
            flee();                                           // Player retreats
            break;
         }
      } 
      else {
         /**********************************************************************
         *                        Monster's Action Block
         **********************************************************************/
         attackCharacter(*participant, player, damageHpBpEp);
         if(player.isDead) {                                // Monster killed player
            combatDefeat();
            break;
         }
         else if(participant->isDead) {
            killMonster(staticParticipantsList, listOfMonsters, 
                        combatParticipants, 1);

            // Check for victory (all monsters dead)
            if(!listOfMonsters.size()) {
                  combatVictory(player, *participant);
                  break;
            }
         }

         // Set retaliation against monster attack
         // Set retaliation afliction against monster
         // Set residual actions
      }

      /*************************************************************************
      *                     Round Ending Action Block
      * This block is called after 200 time units (initiative) has passed.
      * Afflictions such as bleeding should be placed in this block of code.
      *************************************************************************/
      if(isEndOfTurn(combatParticipants)) {
         
         // Reset running initiative and apply bleeding damage
         for(short i = combatParticipants.size() - 1; i >= 0; i--) {
            combatParticipants[i]->runningInitiative -= 200;
      
	          if(combatParticipants[i]->isBleeding) 
	             applyBleeding(*combatParticipants[i]);
         }
         
         if(player.isDead) { combatDefeat(); break; } // Did they bleed to death?

         for(short i = combatParticipants.size() - 1; i >= 0; i--) 
            if(combatParticipants[i]->isDead) 
               killMonster(staticParticipantsList, listOfMonsters, combatParticipants, i); 

	       if(!listOfMonsters.size()) {
            combatVictory(player, *participant);
	          break;	
         }
      }
   }    // End of combat loop

   if(debugMode) {
      cout << "\nDont forget to reset world affecting stats at the end of combat!" 
         << endl;
      displayStats(player);
   }    
}

/******************************************************************************/

#endif // COMBAT_H

/*******************************************************************************
* To do as of 10/08/2020:
* Create a riposte ability and assign to rapier.
* Create evasion ability and coresponding low HP penalty.
* Regeneration
* Make 'defend' do something (increase damage (implements riposte?))
*   Generate ability points when attacked the do super moves
*      Hemorage - low direct damage, high bleed.
*      Multi-strike - Hits multiple enemies or single enemy.
*      Charm - Enemies attack eachother.
*      Freeze - Enemy running initiative *= 3-6
*      
*
* Misc Ides:
*   Smoke bomb. Dissapear. Enemy stops attacking.
*   Experience with individual weapon types allow training abilities which 
*      can be used with skill points aquired from defending.
*******************************************************************************/
