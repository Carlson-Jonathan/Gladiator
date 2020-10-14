/*******************************************************************************
* combat.h
* Author: Jonathan Carlson
* Description:
*  Governs the combat sequence applying stats from the Character class objects.
*******************************************************************************/
#ifndef BATTLE_H
#define BATTLE_H
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "display.h"
#include "character.h"

class Battle {

public:
   Battle() {}
   Battle(Character & player, string newMonster, bool debugMode, short groupSize) {
      combat(player, newMonster, debugMode, groupSize);
   }


private:
   /***************************************
   * Private variables
   ***************************************/
   bool 
      debugMode,
      battleOver = false;

   short 
      died,
      option,
      target,
      round = 1,
      damageHpBpEp[3],
      willMiss,
      missed,
      damageTypes[4],
      block[4],
      groupSize;

   string newMonster;

   Character player;
   Character* monster = NULL;
   Character* participant = NULL;


   vector<string> listOfMonsters;
   vector<Character*> combatParticipants;
   vector<Character*> staticParticipantsList;

   /***************************************
   * Private Prototypes
   ***************************************/
   Character* nextAction();
   void getDamageSum         (const Character & vicitm);
   void getPhysicalDamages   (Character & victim, Character & aggressor);
   void convertToHP_BP       (const Character & victim, short dT[]);
   void applyDamage          (Character & victim); 
   void determineAffliction  (const Character & aggressor, Character & victim);
   void applyBleeding        (Character & victim);
   void focus                (Character & character);
   void flee                 ();
   bool isDefeated           (Character & victim);
   void receiveHazardDamage  (Character & aggressor, const Character & victim);
   short attackCharacter     (Character & aggressor, Character & victim);
   static bool sorter        (Character* a, Character* b);
   bool isEndOfTurn          ();
   vector<Character*> generateParticipantList(Character & player);
   void killMonster          ();
   bool missedAttack         (const Character & aggressor, const Character & victim);
   void riposte              (Character & aggressor, Character & victim);
   void applyRetaliationActions(Character & aggressor, Character & victim);
   bool burnTheBodies        ();
   void applyFatigue         (Character & victim);
   void applyDazed           (Character & victim);
   bool completeOption1(Character & activeCharacter, Character & targetCharacter);
   void combat               (Character & player, string newMonster, bool debugMode, short groupSize);
};

   /***************************************
   * Function definitions that for some
   * reason cannot be placed into a '.cpp'.
   ***************************************/

/*******************************************************************************
* Character* nextAction()
* Receives the list of combat participants, sorts it by the running initiative
* member, then returns the first participant (with the lowest value).
*******************************************************************************/
Character* Battle::nextAction() {
   sort(combatParticipants.begin(), combatParticipants.end(), sorter);
   if(debugMode) {
      cout << "\t\t\tInitiatives | Running Initiatives" << endl; 
      for(auto i : combatParticipants) {
         cout.width(40);
         cout << right << i->name << ": " << i->initiative 
              << " | " << i->runningInitiative << endl;
      }
      cout << endl;    
   }
    combatParticipants[0]->runningInitiative += combatParticipants[0]->initiative;
    return combatParticipants[0];
}

/*******************************************************************************
* void getDamageSum(const Character)
* Applies the damage reduction of the armor assuring that it does not go below 
* 0. The formula applied is to reduce each damage type by the block damage
* type as a percentage.
*******************************************************************************/
void Battle::getDamageSum(const Character & victim) {
   for(short i = 0; i < 4; i++) {
      damageTypes[i] *= (1.0 - ((float)victim.armor->damageReduce[i] / 100));
      if(damageTypes[i] < 0)
         damageTypes[i] = 0;
   }
}

/*******************************************************************************
* void getPhysicalDamages(Character, Character)
* Gets the damage types generated by the aggressor's weapon, gets the defence
* values generated by the victim's armor, sums them, converts them to HP/BP/EP,
* and sets them to the address of a short[]; 
*******************************************************************************/
void Battle::getPhysicalDamages(Character & victim, Character & aggressor) {

   aggressor.weapon->setRandomDamageTypes();

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

   for(short i = 0; i < 4; i++) {
      damageTypes[i] = aggressor.weapon->damageTypes[i];
      block[i] = victim.armor->damageReduce[i]; 
   }

   getDamageSum(victim);
   if(debugMode) cout << "\t\t\t" << aggressor.name << " modified Damage Types:"
                      << endl;
   if(debugMode) cout << "\t\t\tCr: " << damageTypes[0] 
                      << " | Ch: " 
                      << damageTypes[1] << " | Sl: " 
                      << damageTypes[2] << " | St: " 
                      << damageTypes[3] << "\n\n";

   convertToHP_BP(victim, damageTypes);
   if(debugMode) cout << "\t\t\t" << "Raw Damage using modified types:" << endl;
   if(debugMode) cout << "\t\t\tHP: " << damageHpBpEp[0] << " | BP: "
                      << damageHpBpEp[1] << " | EP: " << damageHpBpEp[2] 
                      << "\n\n";
}

/*******************************************************************************
* void convertToHP_BP(Character, short[])
* Accepts either the Hero or Monster type objects and uses the weapon object
* set in that type to determine the amount of damage that will be inflicted
* per combat round. Basically it splits the 4 damage types into 3 health types.
*******************************************************************************/
void Battle::convertToHP_BP(const Character & victim, short dT[]) {

        // dT[0] = Crush, dT[1] = Chop, dT[2] = Slash, dT[3] = Stab            
   damageHpBpEp[0] = dT[0] + ceil(dT[2] * 0.34) + ceil(dT[1] * 0.66),   // HP
   damageHpBpEp[1] = dT[3] + ceil(dT[2] * 0.66) + ceil(dT[1] * 0.34),   // BP
   damageHpBpEp[2] = 0;                                                 // EP

   if(victim.isDefending) 
      damageHpBpEp[0] /= 2; damageHpBpEp[1] /= 2; damageHpBpEp[2] /= 2;
}

/*******************************************************************************
* void applyDamage(Character) 
* Applies the calculated damage to the victim's health.
*******************************************************************************/
void Battle::applyDamage(Character & victim) {
   victim.setHitPoints(-damageHpBpEp[0]);
   victim.setBloodPoints(-damageHpBpEp[1]);
   victim.setEssencePoints(-damageHpBpEp[2]);
}

/*******************************************************************************
* void determineAffliction(Character, Character)
* Extracts weapon information to determine which types of afflictions apply.
*******************************************************************************/
void Battle::determineAffliction(const Character & aggressor, Character & victim) {

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
void Battle::applyBleeding(Character & victim) {
   short bleedAmt = victim.isBleeding / 10;
   
   victim.setBloodPoints(-bleedAmt);
   if(victim.bloodPoints < 0)
      victim.bloodPoints = 0;
   
   bleedingMessage(victim);
   isDefeated(victim);

   victim.isBleeding -= bleedAmt - 2;
   if(victim.isBleeding < 0)
      victim.isBleeding = 0;
}

/*******************************************************************************
* void focus(Character)
* Sets the player's defend status to true.
*******************************************************************************/
void Battle::focus(Character & character) {
   if(!character.isDefending) {
      character.isDefending = true;
      character.applyDefendBonuses();
      defendingMessage(character);
   }
   else
      cout << character.name << " continues to stand guard.\n\n"; 

   // if(debugMode) cout << "Debug focus:" << endl;
   // if(debugMode) displayCharacterStats(staticParticipantsList, player, round++);

   // Potential uses:        
   // Increases damage on next strike (allows for criticals?).
   // Increases chance to apply affliction on next strike.
   // Can be used to overcome enemy strengths (tough defence).
}

/******************************************************************************
* void flee()
* Will house the flee function. All it does right now is end the combat.
******************************************************************************/
void Battle::flee() {
   // Based on yours and the monster's health
   cout << "\tYou run away screaming like a little girl!" << endl;
}

/*******************************************************************************
* bool isDefeated(Character)
* Tells whether or not a character is dead.
*******************************************************************************/
bool Battle::isDefeated(Character & victim) {
   if(!(victim.hitPoints && victim.bloodPoints && victim.essencePoints)) {
      if(debugMode) cout << "This victim has been identified as dead!\n\n";
      victim.isDead = true; 
  }
  return false;
}

/*******************************************************************************
* void receiveHazardDamage(Character, Character)
* Calculates and applies reflective damage.
*******************************************************************************/
void Battle::receiveHazardDamage(Character & aggressor, const Character & victim) {

    for(auto &i : damageHpBpEp)
        i /= victim.isHazardous;

    hazardDamageMessage(aggressor, damageHpBpEp);
    applyDamage(aggressor);
    isDefeated(aggressor);
}

/*******************************************************************************
* bool attackCharacter(Character, Character)
* Performs all functions in an attack action ending with receiving reflect dmg.
*******************************************************************************/
short Battle::attackCharacter(Character & aggressor, Character & victim) {

   if(!missedAttack(aggressor, victim)) {
      getPhysicalDamages(victim, aggressor);
      displayAttackMessage(victim, aggressor, damageHpBpEp);
      applyDamage(victim);
      if(isDefeated(victim)) return 1;
      determineAffliction(aggressor, victim);

      if(victim.isHazardous) 
      receiveHazardDamage(aggressor, victim);
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
bool Battle::sorter(Character* a = NULL, Character* b = NULL) {return  (*a < *b);}


/*******************************************************************************
* bool isEndOfTurn()
* The end of a combat round is marked when all characters have exceeded 200
* running initiative units. 
*******************************************************************************/
// If all participant's running initiative's exceed 200, the round is over.
bool Battle::isEndOfTurn() {
   for(auto i : combatParticipants)
      if(i->runningInitiative <= 200)
         return false;
   return true;
}

/*******************************************************************************
* vector<Character*> generateParticipantList(Character)
* Creates a vector of object pointers. Includes the player(s) and generates 
* 'size' number of random new monster objects to include. 
*******************************************************************************/
vector<Character*> Battle::generateParticipantList(Character & player) {
   combatParticipants.push_back(&player);
   for(short i = 0; i < groupSize; i++) {
      participant = new Character(newMonster);
      combatParticipants.push_back(participant);
      monster = participant;
   }
   return combatParticipants;
}

/*******************************************************************************
* void killMonster()
* Yes, I know it looks like a mess. I had to educate myself on preventing 
* memory leaks and dangling pointers, so I made a mess of "cout"s. I am leaving
* them here in debug mode just in case.
*
* This function kills a monster. It removes it from both vectors of pointers, 
* nullifies the said pointers, and deletes (destroys) the monster object.  
*******************************************************************************/
void Battle::killMonster() {
   for(short i = staticParticipantsList.size() - 1; i >= 0; i--) {
      if(staticParticipantsList[i]->isDead) {
                if(debugMode)cout << "Erasing string from list of names.\nBefore: " << endl;
                if(debugMode) for(auto i : listOfMonsters)
                   cout << i << ", ";
                if(debugMode) cout << endl;
         listOfMonsters.erase(listOfMonsters.begin() + (i));
                if(debugMode) cout << "After: ";
                if(debugMode) for(auto i : listOfMonsters)
                   cout << i << ", ";
                if(debugMode) cout << endl;
                if(debugMode) cout << "Calling for object removal from static list..."  << endl;
                if(debugMode) cout << "The value of i is " << i << endl;
                if(debugMode) cout << "Item being deleted is " << staticParticipantsList[i]->name << endl;
                if(debugMode) cout << "Static list printout:" << endl;
                if(debugMode) for (auto i : staticParticipantsList) cout << i->name << endl;
                if(debugMode) cout << endl;
                if(debugMode) cout << "Object to be erased: " << (*(staticParticipantsList.begin() + (i)))->name << "\n\n";
                if(debugMode) cout << "Nullifying pointer...\n";
         staticParticipantsList[i] = NULL;
                if(debugMode) cout << "Pointer nullified.\n";
                if(debugMode) cout << "Erasing pointer from list...\n";
         staticParticipantsList.erase(staticParticipantsList.begin() + (i));
                if(debugMode) cout << "Pointer erased!\n";
                if(debugMode) cout << "New static list of monsters:\n";
                if(debugMode) for (auto i : staticParticipantsList) cout << i->name << endl;
                if(debugMode) cout << "\n\n";
      }
   }
                if(debugMode) cout << "Moving on to removing object from combatParticipants list:\n";
   for(int i = combatParticipants.size() - 1; i >= 0; i--) {
                  if(debugMode) cout << "Checking for defeat condition of combatParticipants[" << i << "] : " << combatParticipants[i]->name << "\n\n";
      if(combatParticipants[i]->isDead) {
         if(combatParticipants[i]->isHero) {
                     if(debugMode) cout << "WARNING! Hero object is flagged as 'dead'.\n\n"; 
         break;
      }
                    if(debugMode) cout << "This object should be erased!\n"; 
                    if(debugMode) cout << "The value of 'i' in this backwards loop is " << i << endl;
                    if(debugMode) cout << "The objects in the list are: " << endl;
                    if(debugMode) for (int j = 0; j < combatParticipants.size(); j++) {
               cout << "object combatParticipants[" << j << "]: ";
         	   cout << combatParticipants[j]->name << endl; 
            }
                    if(debugMode) cout << "Destroying " << combatParticipants[i]->name << "'s weapon...\n";
      delete combatParticipants[i]->weapon;
      combatParticipants[i]->weapon = NULL;
                    if(debugMode) cout << "Weapon pointer nullified.\n";
                    if(debugMode) cout << "Destroying " << combatParticipants[i]->name << "'s armor...\n";
      delete combatParticipants[i]->armor;
      combatParticipants[i]->armor = NULL;
                    if(debugMode) cout << "Armor pointer nullified.\n";
                    if(debugMode)cout << "Calling 'delete' on object in sorting list, combatParticipants[" << (i) << "]" << endl; 
      delete combatParticipants[i];
                    if(debugMode) cout << "Nullifying pointer...\n";
      combatParticipants[i] = NULL;    
                    if(debugMode) cout << "Pointer nullified!\n";
                    if(debugMode)cout << "Erasing object " << (*(combatParticipants.begin() + i)) << " from sorting list of monsters..." << endl;
      combatParticipants.erase(combatParticipants.begin() + i);
                    if(debugMode) cout << "Object erased!" << endl;
                    if(debugMode) cout << "Object has been destroyed! " << "All dangling pointers have been de-weaponized!\n";
                    if(debugMode) cout << "New combatParticipants list:\n";
                    if(debugMode) for(auto i : combatParticipants) cout << i->name << endl;
                    if(debugMode) cout << "Monster has been murdered! The end.\n\n";
      }
      else
                    if(debugMode) cout << "Object is still alive. Moving on...\n";
   }
   if(debugMode) cout << "*** End of killMonster() ***\n\n";
}

/*******************************************************************************
* bool missedAttack(Character, Character)
* Generates a random number. If that number is higher than the aggressor's
* percision minus the victim's evasion, the attack fails.
*******************************************************************************/
bool Battle::missedAttack(const Character & aggressor, const Character & victim) {
   willMiss = aggressor.percision - victim.evasion;
   missed = rand() % 100;
   if(debugMode) cout << "\t\t\t" << aggressor.name << "'s accuracy: \n\t\t\t" 
   	                  << missed << " | " << willMiss << "\n\n";
   return missed >= willMiss;
}

/*******************************************************************************
* void riposte(Character, Character)
* Victim attacks aggressor.
*******************************************************************************/
void Battle::riposte(Character & aggressor, Character & victim) {
   riposteMessage(victim, aggressor);
   attackCharacter(victim, aggressor);
}

/*******************************************************************************
* void applyRetaliationActions(Character, Character)
* Contains the calls to retaliatory functions.
*******************************************************************************/
void Battle::applyRetaliationActions(Character & aggressor, Character & victim) {

   // Defending reactions
   if(victim.isDefending) {
      if(victim.weapon->riposte > 0) 
         riposte(aggressor, victim);
   }

   // Other reactions
}

/*******************************************************************************
* void burnTheBodies()
* Scan the combat participants list. If any participant is dead, invokes either
* kill monster or defeat.
*******************************************************************************/
bool Battle::burnTheBodies() {
   bool corpseExists = false;
   for(auto i: combatParticipants)
      if(i->isDead) {
      	  corpseExists = true;
          if(i->isHero) {
             battleOver = true;
             combatDefeat();
             return 1;
          }
      }   

   if(corpseExists) killMonster();

   if(!listOfMonsters.size()) {
      combatVictory(player);
      battleOver = true;
   }
   return battleOver;
}

/****************************************************************************
* void applyFatigue(Character)
* If the character's BP falls below 2/3 maximum, reduces speed and damage. 
****************************************************************************/
void Battle::applyFatigue(Character & victim) {
   if(victim.bloodPoints < victim.maxBloodPoints * 0.66) {
      short difference = (victim.maxBloodPoints * 0.66 - victim.bloodPoints),
      additionalInit = difference / 4;
      victim.runningInitiative += additionalInit;
      
      victim.weapon->basePenalty = 
      ((victim.maxBloodPoints * 0.66) - difference) / 
      (victim.maxBloodPoints * 0.66);
      fatigueMessage(victim, additionalInit);
   } 
}

/****************************************************************************
* void applyDazed(Character)
* If the character's BP falls below 2/3 maximum, reduces aim and evade.
****************************************************************************/
void Battle::applyDazed(Character & victim) {
   if(victim.hitPoints < victim.maxHitPoints * 0.66) {
      short difference = (victim.maxHitPoints * 0.66 - victim.hitPoints); 
      victim.armor->evadePenalty = 
      ((victim.maxHitPoints * 0.66) - difference) / 
      (victim.maxHitPoints * 0.66);
      victim.evasion *= victim.armor->evadePenalty;
      dazedMessage(victim, 21, (short)((1 - victim.armor->evadePenalty) * 100));
   }
}

/*******************************************************************************
* void completeOption1()
* Groups all function calls for player option 1 - 'attack'. This includes
* attacking a target, applying hazardous reflective damage conditions, 
* applying retaliation actions, applying afflictions, and all the while 
* checking for defeat and victory conditions that would end the combat.
*******************************************************************************/
bool Battle::completeOption1(Character & activeCharacter, Character & targetCharacter) {
   attackCharacter(activeCharacter, targetCharacter);
   if(burnTheBodies()) return 1;

   applyRetaliationActions(activeCharacter, targetCharacter);
   if(burnTheBodies()) return 1;

   if(activeCharacter.isDefending) {
      activeCharacter.isDefending = false;
      activeCharacter.removeDefendBonuses();
   }

   return 0;
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
void Battle::combat(Character & player, string newMonster, 
                    bool debugMode, short groupSize) {

   // General Setup
   this->debugMode = debugMode; 
   this->groupSize = groupSize;
   this->newMonster = newMonster;
   this->player = player;

   srand(time(0));                   // Seeds sudo random number generator

   player.initiative = 100 + player.weapon->speed; // Sets default initiative

   // Monster lists
   combatParticipants = generateParticipantList(player);
   staticParticipantsList = combatParticipants;
   
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
      participant = nextAction();

      /*************************************************************************
      *                     Turn Ending Action Block
      * Code in this block will be executed after any turn, player or monster
      *************************************************************************/
      applyFatigue(*participant);
      applyDazed(*participant);
      // Apply Daized Condition here (low HP = poor evasion and percision)
      
      /*************************************************************************
      *                        Player's Action Block
      *************************************************************************/
      if(participant->name == player.name) {        
         displayCharacterStats(staticParticipantsList, player, round++);
         
         /******************* Setup ***********************/
         option = getUserInput({"Attack", "Defend", "Flee"});

         if (option == 1) {                                           // Attack
            if(listOfMonsters.size() > 1) 
               target = getUserInput(listOfMonsters);           // Attack what?
            else
               target = 1;                               // Only 1 monster left 
            
            if(completeOption1(player, *staticParticipantsList[target - 1])) break;

         } // end if(option == 1)
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
         if(completeOption1(*participant, player)) break;
      }

      /*************************************************************************
      *                     Round Ending Action Block
      * This block is called after 200 time units (initiative) has passed.
      * Afflictions such as bleeding should be placed in this block of code.
      *************************************************************************/
      if(isEndOfTurn()) {
         
         // Reset running initiative and apply bleeding damage
         for(short i = combatParticipants.size() - 1; i >= 0; i--) {
            combatParticipants[i]->runningInitiative -= 200;
      
	        if(combatParticipants[i]->isBleeding) 
	           applyBleeding(*combatParticipants[i]);
         }
         
         if(debugMode) cout << "Applying bleed deaths:\n\n";
         if(burnTheBodies()) break;
      }
   }    // End of combat loop

   if(debugMode) {
      cout << "\nDont forget to reset world affecting stats at the end of combat!" 
           << endl;
      displayStats(player);
   }    

/******************************************************************************/

}

#endif // BATTLE_H

// Bugs to fix:
//    None known at present.

// Refactors:
//   Change percisionBonuse and any bonuses for defending to "modifiers".
//   Remove penalty functions from character.cpp

// Currenlty working on:
//   Dazed condition

/*******************************************************************************
* To do as of 10/14/2020:
* Create evasion ability and coresponding low HP penalty.
* Regeneration
*   Generate ability points when attacked the do super moves
*      Hemorage - low direct damage, high bleed.
*      Multi-strike - Hits multiple enemies or single enemy.
*      Charm - Enemies attack eachother.
*      Freeze - Enemy running initiative *= 3-6
*   Implement multi-hero gameplay.
*   Allow monsters and heros to combine skills for additional/new effects.
*      
*
* Misc Ides:
*   Smoke bomb. Dissapear. Enemy stops attacking.
*   Experience with individual weapon types allow training abilities which 
*      can be used with skill points aquired from defending.
*   High bleed, low damage weapon.
*   Excalibur. Omni-beast. (Have all affliction attributes)
*   Insta-death weapon/ability.
*   Equipment durability is the same as attack/defense power.
*
*
* Test Checklist:
*    Regular attack deaths.
*    Monsters and player can bleed to death with no crashes.
*    Simultaneous character deaths cause no crashing.
*    Hazard damage death.
*    Riposte death.
*    Damage amounts are correct
*    Bleed amounts are correct
*    Defence reduces correctly.
*    Percision/Evade calculates and executes correctly.
*    Critical damage is correct. Chance % is correct.
*    
*
*******************************************************************************/
