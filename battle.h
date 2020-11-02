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
#include <cstdlib>  // sleep
#include <unistd.h> // sleep
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "display.h"
#include "character.h"
#include "animations.h"

class Battle {

public:
   Battle() {}
   Battle(vector<Character> & heroes, string newMonster, bool debugMode, 
      short numMonsters, bool textMode, Animations* animations) {
      this->debugMode = debugMode; 
      this->numMonsters = numMonsters;
      this->newMonster = newMonster;
      this->heroes = heroes;
      this->textMode = textMode;
      this->animations = animations;
      for(auto & i : this->heroes) {
         selectWeapon(i);
         selectArmor(i);
      }
         
      srand(time(0));       
      generateParticipantLists();
   }

   void combat (sf::RenderWindow & window);


//******************************************************************************
private:

   bool 
      debugMode = false,
      battleOver = false, 
      textMode = false,
      go = true,
      animationLineup[36] = {
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0
      };

   short 
      died = 0,
      option = 1,
      target = 1,
      round = 1,
      damageHpBpEp[3],
      willMiss = 0,
      missed = 0,
      damageTypes[4],
      block[4],
      numMonsters = 1,
      randNum = 1,
      lineupIndex = 88, 
      diedCount = 0,
      missedCount = 0,
      damageCount = 0,
      bleedCount = 0,
      stunCount = 0,
      slowCount = 0, 
      hazardCount = 0;

   string 
      newMonster,
      battleMusic[3] = {"Sounds/Music/battle1.ogg", 
                        "Sounds/Music/battle2.ogg", 
                        "Sounds/Music/battle3.ogg"};

   Character* monster = NULL;
   Character* participant = NULL;
   Animations* animations;
   sf::Clock clock;
   sf::Music music;

   vector<Character> heroes;
   vector<string> listOfMonsters;
   vector<Character*> heroParticipants;
   vector<Character*> monsterParticipants;
   vector<Character*> allCombatParticipants;


   //============================ Prototypes ===================================

   Character* nextAction();
   void getDamageSum         (const Character & vicitm);
   void getPhysicalDamages   (Character & victim, Character & aggressor);
   void convertToHP_BP       (const Character & victim, short dT[]);
   void applyDamage          (Character & victim); 
   void determineAffliction  (const Character & aggressor, Character & victim);
   void applyBleeding        (Character & victim);
   void applyRegeneration    (Character & character);
   void focus                (Character & character);
   void flee                 ();
   bool isDefeated           (Character & victim);
   void receiveHazardDamage  (Character & aggressor, const Character & victim);
   short attackCharacter     (Character & aggressor, Character & victim);
   static bool sorter        (Character* a, Character* b);
   bool isEndOfTurn          ();
   bool endOfTurnActions     ();
   void generateParticipantLists();
   void killCharacter          ();
   bool missedAttack         (const Character & aggressor, const Character & victim);
   void riposte              (Character & aggressor, Character & victim);
   void applyRetaliationActions(Character & aggressor, Character & victim);
   bool burnTheBodies        ();
   void applyFatigue         (Character & victim);
   void applyDazed           (Character & victim);
   void applyDefendBonuses   (Character & character);
   void removeDefendBonuses  (Character & character);
   bool completeOption1      (Character & activeCharacter, Character & targetCharacter);
   bool applyCharacterAction (Character* character);
   void getCharacterAction   (Character* character);
   void playBattleMusic      ();
   short getLineupIndex      ();
   void resetStuff           ();
};


//==============================================================================
//========================== Function Definitions ==============================
//==============================================================================


/*******************************************************************************
* Character* nextAction()
* Receives the list of combat participants, sorts it by the running initiative
* member, then returns the first participant (with the lowest value).
*******************************************************************************/
Character* Battle::nextAction() {
   sort(allCombatParticipants.begin(), allCombatParticipants.end(), sorter);
   if(debugMode) displayInitiatives(allCombatParticipants);
   allCombatParticipants[0]->runningInitiative += 
   allCombatParticipants[0]->initiative;
   return allCombatParticipants[0];
}

/*******************************************************************************
* void getDamageSum(const Character)
* Applies the damage reduction of the armor assuring that it does not go below 
* 0. The formula applied is to reduce each damage type by the block damage
* type as a percentage.
*******************************************************************************/
void Battle::getDamageSum(const Character & victim) {
   victim.armor->setDamageReduce();
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

   aggressor.weapon->setRandomDamageTypes(debugMode);
   if(debugMode) {
      displayRawDamageAmounts(aggressor);
      displayArmorValues(victim);
   }

   for(short i = 0; i < 4; i++) {
      damageTypes[i] = aggressor.weapon->damageTypes[i];
      block[i] = victim.armor->damageReduce[i]; 
   }

   getDamageSum(victim);
   if(debugMode) displayModifiedDamage(aggressor, damageTypes);

   convertToHP_BP(victim, damageTypes);
   if(debugMode) displayHP_BP_EPdamage(damageHpBpEp);
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
   if(damageCount == 0) animationLineup[7] = true;
   else if(damageCount == 1) animationLineup[20] = true;
   ++damageCount;
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
         victim.isBleeding += aggressor.weapon->isSharp;
         if(bleedCount == 0) animationLineup[11] = true;
         else if(bleedCount == 1) animationLineup[24] = true;
         ++bleedCount;
      }
      
      // Sets a stun affliction (skips the victim's next turn).
      if(wep->canStun)
         if(damageTypes[0] > aggressor.weapon->minDamage + 
            aggressor.weapon->rangeDamage / 2) { // Damge > than 50% of potential
            if(textMode) stunMessage(aggressor, victim);
            if(stunCount == 0) animationLineup[12] = true;
            else if(stunCount == 1) animationLineup[25] = true;
            ++stunCount;
            victim.runningInitiative += wep->canStun;
         }

      // Slows base initiative by venom stat
      if(wep->isVenomous) {
         victim.initiative += wep->isVenomous;   
         if(textMode) slowMessage(aggressor, victim);
         if(slowCount == 0) animationLineup[14] = true;
         else if(slowCount == 1) animationLineup[26] = true;
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
   
   victim.setBloodPoints(-victim.isBleeding);
   if(textMode) bleedingMessage(victim);
   animationLineup[31] = true;
   isDefeated(victim);

   victim.setIsBleeding(-2);
}

/*******************************************************************************
* bool applyRegeneration(Character)
* Governs 1 round of character regeneration.
*******************************************************************************/
void Battle::applyRegeneration(Character & character) {
   character.setBloodPoints(character.regeneration);
   if(character.bloodPoints < character.maxBloodPoints - character.regeneration) {
      regenerationMessage(character);
      animationLineup[35] = true; 
   }
}

/*******************************************************************************
* void focus(Character)
* Sets the player's defend status to true.
*******************************************************************************/
void Battle::focus(Character & character) {
   if(textMode) defendingMessage(character);
   animationLineup[3] = true;
   character.isDefending = true;
   applyDefendBonuses(character);

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
   animationLineup[4] = true;
   fleeCombatMessage();
}

/*******************************************************************************
* bool isDefeated(Character)
* Tells whether or not a character is dead.
*******************************************************************************/
bool Battle::isDefeated(Character & victim) {
   if(!(victim.hitPoints && victim.bloodPoints && victim.essencePoints)) {
      if(textMode) characterDiedMessage(victim); 
      switch(diedCount) {
         case 0:
            animationLineup[8] = true;
            break;
         case 1:
            animationLineup[15] = true;
            break;
         case 2:
            animationLineup[21] = true;
            break;
         case 3:
            animationLineup[28] = true;
            break;
         case 4:
            animationLineup[32] = true;
            break;
      }
      victim.isDead = true; 
      return true;
   }
   ++diedCount;
   return false;
}

/*******************************************************************************
* void receiveHazardDamage(Character, Character)
* Calculates and applies reflective damage.
*******************************************************************************/
void Battle::receiveHazardDamage(Character & aggressor, const Character & victim) {

    for(auto & i : damageHpBpEp)
        i /= victim.isHazardous;

    if(textMode) hazardDamageMessage(aggressor, damageHpBpEp);
    if(hazardCount == 0) animationLineup[14] = true;
    else if(hazardCount == 1) animationLineup[27] = true;
    applyDamage(aggressor);
    isDefeated(aggressor);
}

/*******************************************************************************
* bool attackCharacter(Character, Character)
* Performs all functions in an attack action ending with receiving reflect dmg.
*******************************************************************************/
short Battle::attackCharacter(Character & aggressor, Character & victim) {

   animationLineup[5] = true;
   if(!missedAttack(aggressor, victim)) {
      getPhysicalDamages(victim, aggressor);
      if(textMode) displayAttackMessage(victim, aggressor, damageHpBpEp);
      applyDamage(victim);
      if(isDefeated(victim)) return 1;
      determineAffliction(aggressor, victim);

      if(victim.isHazardous) 
      receiveHazardDamage(aggressor, victim);
   }
   else {
      if(textMode) missedAttackMessage(aggressor, victim);
      if(missedCount == 0) animationLineup[6] = true;
      else if(missedCount == 1) animationLineup[19] = true;
      ++missedCount;
   }

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
bool Battle::isEndOfTurn() {
   for(const auto & i : allCombatParticipants)
      if(i->runningInitiative <= 200)
         return false;
   return true;
}

/*******************************************************************************
* void endofTurnActions()
* Groups and executes all actions that should happen at the end of each combat
* round. isEndOfTurn() dictates the length of a combat round. Actions include:
*    - Reducing running initiative of all characters by 200.
*    - Applying bleed damage to all characters afflicted.
*    - To be determined...
*******************************************************************************/
bool Battle::endOfTurnActions() {
   for(short i = allCombatParticipants.size() - 1; i >= 0; i--) {
      allCombatParticipants[i]->runningInitiative -= 200;
      
      if(allCombatParticipants[i]->isBleeding) 
         applyBleeding(*allCombatParticipants[i]);

      if(allCombatParticipants[i]->regeneration)
         applyRegeneration(*allCombatParticipants[i]);
   }
         
   if(burnTheBodies()) return 1;

   return 0;
}

/*******************************************************************************
* vector<Character*> generateParticipantLists(Character)
* Creates a vector of object pointers. Includes the player(s) and generates 
* 'size' number of random new monster objects to include. 
*******************************************************************************/
void Battle::generateParticipantLists() {
   
   for(auto & i : heroes) {
       Character* hero = &i;
       allCombatParticipants.push_back(hero);
       heroParticipants.push_back(hero);
   }
   
   for(short i = 0; i < numMonsters; i++) {
      participant = new Character(newMonster);
      allCombatParticipants.push_back(participant);
      monsterParticipants.push_back(participant);
      listOfMonsters.push_back(participant->name);
   }
}

/*******************************************************************************
* void killCharacter()
* This function kills a character. It removes it from both vectors of pointers, 
* nullifies the said pointers, and, if it is a monster object, deletes 
* (destroys) the object.  
*******************************************************************************/
void Battle::killCharacter() {

   // Clean the monsterParticipants lists	
   for(short i = monsterParticipants.size() - 1; i >= 0; i--) {
      if(monsterParticipants[i]->isDead) {
         listOfMonsters.erase(listOfMonsters.begin() + (i));
         monsterParticipants[i] = NULL;
         monsterParticipants.erase(monsterParticipants.begin() + (i));
      }
   }

   // Clean the heroParticipants list.
   for(short i = heroParticipants.size() - 1; i >= 0; i--) {
      if(heroParticipants[i]->isDead) {
         heroParticipants[i] = NULL;
         heroParticipants.erase(heroParticipants.begin() + i);      	
      }
   }

   // Clean the allCombatParticipants list.
   for(short i = allCombatParticipants.size() - 1; i >= 0; i--) {
      if(allCombatParticipants[i]->isDead) {
         if(allCombatParticipants[i]->isHero) {
            allCombatParticipants[i] = NULL;
            allCombatParticipants.erase(allCombatParticipants.begin() + i);
         }
         else 
         {
            delete allCombatParticipants[i]->weapon;
            allCombatParticipants[i]->weapon = NULL;
            delete allCombatParticipants[i]->armor;
            allCombatParticipants[i]->armor = NULL;
            delete allCombatParticipants[i];
            allCombatParticipants[i] = NULL;    
            allCombatParticipants.erase(allCombatParticipants.begin() + i);
         }
      }
   }
}

/*******************************************************************************
* bool missedAttack(Character, Character)
* Generates a random number. If that number is higher than the aggressor's
* precision minus the victim's evasion, the attack fails.
*******************************************************************************/
bool Battle::missedAttack(const Character & aggressor, const Character & victim) {
   willMiss = aggressor.precision - victim.evasion + victim.evasionPenalty -
   aggressor.precisionPenalty;
   missed = rand() % 100;
   if(debugMode) displayAccuracy(aggressor, missed, willMiss);
   return missed >= willMiss;
}

/*******************************************************************************
* void riposte(Character, Character)
* Victim attacks aggressor.
*******************************************************************************/
void Battle::riposte(Character & aggressor, Character & victim) {
   riposteMessage(victim, aggressor);
   animationLineup[18] = true;
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

   // Other reactions go here.
}

/*******************************************************************************
* void burnTheBodies()
* Scan the combat participants list. If any participant is dead, invokes either
* kill monster or defeat.
*******************************************************************************/
bool Battle::burnTheBodies() {
   bool corpseExists = false;
   short deathCount = 0;
   for(const auto & i: allCombatParticipants) {
      if(i->isDead) 
      	  corpseExists = true;
   }

   for(const auto i : heroParticipants) {
      if(i->isDead)
         deathCount++;
      if(deathCount == heroParticipants.size()) {
         if(textMode) combatDefeat();
         switch(diedCount) {
         case 0:
            animationLineup[9] = true;
            break;
         case 1:
            animationLineup[16] = true;
            break;
         case 2:
            animationLineup[22] = true;
            break;
         case 3:
            animationLineup[29] = true;
            break;
         case 4:
            animationLineup[33] = true;
            break;
      }
         battleOver = true;
         return 1;
      }
   }

   if(corpseExists) killCharacter();

   if(!listOfMonsters.size()) {
      if(textMode) combatVictory(heroes[0]);
      switch(diedCount) {
      case 0:
         animationLineup[10] = true;
         break;
      case 1:
         animationLineup[17] = true;
         break;
      case 2:
         animationLineup[23] = true;
         break;
      case 3:
         animationLineup[30] = true;
         break;
      case 4:
         animationLineup[34] = true;
         break;
   }
      battleOver = true;
   }
   return battleOver;
}

/****************************************************************************
* void applyFatigue(Character)
* If the character's BP falls below 2/3 maximum, reduces speed and damage. 
****************************************************************************/
void Battle::applyFatigue(Character & victim) {

   short limit = victim.maxBloodPoints * 0.66, difference, additionalInit;

   if(victim.bloodPoints < limit) {
      difference = (limit - victim.bloodPoints);

      additionalInit = (float)difference / (float)limit * 200.0;
      victim.runningInitiative += additionalInit;
      
      victim.weapon->basePenalty = 1 - ((float)difference / (float)limit / 2);

      if(textMode) fatigueMessage(victim, additionalInit);
      animationLineup[0] = true;
   } 
   else {
  	   victim.weapon->basePenalty = 1;
   }
}

/****************************************************************************
* void applyDazed(Character)
* If the character's BP falls below 2/3 maximum, reduces aim and evade.
****************************************************************************/
void Battle::applyDazed(Character & victim) {

   short limit = victim.maxHitPoints * 0.66;

   if(victim.hitPoints < limit) {
      short difference = (limit - victim.hitPoints); 
      
      victim.evasionPenalty   = (float)difference / (float)limit * 50.0;
      victim.precisionPenalty = (float)difference / (float)limit * 50.0;

      if(textMode) dazedMessage(victim, victim.precisionPenalty, victim.evasionPenalty);
      animationLineup[1] = true;
   }
   else {
      victim.evasionPenalty = 0;
      victim.precisionPenalty = 0;
   }
}

/****************************************************************************
* void applyDefendBonuses(Character)
* Takes the bonus values granted to characters when defending, and applies
* them to their weapons, armor and character stats;
****************************************************************************/
void Battle::applyDefendBonuses(Character & character) {
   character.weapon->criticalChance += character.weapon->criticalBonus;
   character.precision += character.weapon->precisionBonus;
   character.evasion += character.armor->evadeBonus;
   character.armor->defencePower += character.armor->defendBonus;
}

/****************************************************************************
* void removeDefendBonuses(Character)
* Removes all bonuses granted by defending.
****************************************************************************/
void Battle::removeDefendBonuses(Character & character) {
   character.weapon->criticalChance -= character.weapon->criticalBonus;
   character.precision -= character.weapon->precisionBonus;
   character.evasion -= character.armor->evadeBonus;
   character.armor->defencePower -= character.armor->defendBonus;
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
      removeDefendBonuses(activeCharacter);
   }

   return 0;
}

/*******************************************************************************
* void applyCharacterAction() 
* Uses the 'option' variable to make a selection for a turn action.
*******************************************************************************/
bool Battle::applyCharacterAction(Character* character) {
   if(option == 1) {
      if(character->isHero) {
         if(completeOption1(*character, *monsterParticipants[target - 1])) {
            return 1;
         }
      }
      else {
         if(completeOption1(*character, *heroParticipants[rand() % heroParticipants.size()])) 
            return 1;
      }
   }
   else if (option == 2) {
      focus(*character);
   }
   else if(option == 3) {
      flee();                                           // Player retreats
      return 1;
   }
   return 0;
}

/*******************************************************************************
* void getCharacterAction() 
* Sets the option and target variables to the user's selection.
*******************************************************************************/
void Battle::getCharacterAction(Character* character) {

   // Get action for hero character 
   if(character->isHero) {
      if(textMode) displayCharacterStats(monsterParticipants, heroParticipants, round++);
      if(textMode) showWhosTurn(*participant);
      animationLineup[2] = true;
      if(textMode) option = getUserInput({"Attack", "Defend", "Flee"});

      if (option == 1)                                           // Attack
         if(listOfMonsters.size() > 1) {
            target = getUserInput(listOfMonsters);           // Attack what?
            if(!textMode) target = 1;
         }
       else
           target = 1;                 // Auto attack if only 1 monster left 
   }

   // Get action for monster AI 
   else {
      randNum = rand() % 10;
      if(randNum > 7) {
         option = 2;
      }
      else {
         option = 1;
      }
   }
}

/*******************************************************************************
* void playBattleMusic() 
* Randomly selects 1 of 3 battle themes and plays it on a loop.
*******************************************************************************/
void Battle::playBattleMusic() {
   randNum = rand() % 3;
   if (!music.openFromFile(battleMusic[randNum]))
      cout << "Error opening file '" << battleMusic[randNum] << "'!\n";
   music.setLoop(true);
   music.play();
}

/*******************************************************************************
* short getLineupIndex() 
* Returns the index + 1 of the next animation in the list. If there are no true
* booleans in the lineup, returns 0.
*******************************************************************************/
short Battle::getLineupIndex() {
   for(short i = 0; i < sizeof(animationLineup); i++) {
      if(animationLineup[i]) {
         animationLineup[i] = false;
         return i + 1;
      }
   }

   return 0;
}

/*******************************************************************************
* void resetStuff()
* Sets various combat variables back to their default at the end of each turn.
*******************************************************************************/
void Battle::resetStuff() {
   diedCount = 0;
   missedCount = 0;
   damageCount = 0;
   bleedCount = 0;
   stunCount = 0;
   slowCount = 0,
   hazardCount = 0;
}



/*###  ####  ######################################################  ####  #####
#####  ####  ###################                ###################  ####  #####
#####  ####  ##############                          ##############  ####  #####
#####  ####  ###########      Main Combat Function      ###########  ####  #####
#####  ####  ##############                          ##############  ####  #####
#####  ####  ###################                ###################  ####  #####
#####  ####  ######################################################  ####  #####
#
# void combat()
# Houses the primary combat loop. Brings all other functions together to form
# a combat sequence. Only stops when it hits a 'break' statement.
#
##############################################################################*/
void Battle::combat(sf::RenderWindow & window) {

   playBattleMusic();

   short count = 0;
   while(true) {

      window.clear(sf::Color(102, 255, 255));
      usleep(16666); // 60 FPS = 16666
      
      // FPS tester
      count++;
      if(!textMode) cout << "\nBattle in progress... FPS Counter: " << count << endl;

      if(animations->eventListener(window)) break;

      // Determines who's turn it is based on the lowest running initiative. 
      if(go) participant = nextAction();
      if(go) resetStuff();

      /*************************************************************************
      *                        Turn Ending Action Block
      * Code in this block will be executed after any turn, hero's or monster's.
      *************************************************************************/
      if(go) applyFatigue(*participant);                                    // Activate booleans to run animations.
      if(go) applyDazed(*participant);
      
      /*************************************************************************
      *                    Characters' Primary Action Block
      *************************************************************************/
      if(go) getCharacterAction(participant);
      if(go) if(applyCharacterAction(participant)) break;

      /*************************************************************************
      *                       Round Ending Action Block
      * A round ends after each character exceeds 200 running initiative.
      *************************************************************************/
      if(go) if(isEndOfTurn()) 
         if(endOfTurnActions()) break; 
      go = false;

      /*************************************************************************
      *                          Battle Drawings
      * Sprites that are always re-drawn each loop.
      *************************************************************************/
      animations->drawBackground(window);
      animations->flyingDragon(window);
      // Characters
      // Environmental overdraws
      // Menu and text boxes

      /*************************************************************************
      *                          Animation Functions
      * These are activated by booleans. The combat functions indicate which 
      * animations should be activated and deactivated at any given time.
      *************************************************************************/
      
      if(debugMode) cout << "Participant: " << participant->name << endl;
      if(debugMode) cout << "Current lineup index: " << lineupIndex << endl;
      if(debugMode) for(bool i : animationLineup)
         cout << i << ", ";
      if(debugMode) cout << endl; 

      if(!textMode) animations->animationSelect(animationLineup, go);
      else go = 1;

      window.display();
   }   

   cout << "End of battle." << endl;

   // if(debugMode) 
   //    cout << "\nDont forget to reset world affecting stats at the end of combat!" 
   //         << endl;
}
#endif // BATTLE_H



// Bugs to fix:
   // Make defeat/victory ANIMATIONS break the combat loop when called and remove other breaks.


// Refactors:

   // Change "isEndOfTurn" to "isEndOfRound"
   // Move animation switch statement to animations.h
   // Call damage numbers animation before wounded (bleeding).

/*********************************************************************************************/

// Currenlty working on: Creating individual animations.
   // Tie the animations to the character objects. Each Character object will have an 
   // animation function with parameters that set the different properties. Create a pointer
   // to the charcter object in the animations.h file. When killCharacter() is called, make it
   // nullify the pointer in the compat participants lists and remove them, but keep the 
   // object. After the defeat animation finishes, nullify the animation.h pointer, remove it,
   // and delete the character object from that file.

/*******************************************************************************
* To do:
* Regeneration
*   Generate ability points when attacked the do super moves
*      Hemorage - low direct damage, high bleed.
*      Multi-strike - Hits multiple enemies or single enemy.
*      Charm - Enemies attack eachother.
*      Freeze - Enemy running initiative *= 3-6
*   Implement multi-hero gameplay.
*   Allow monsters and heros to combine skills for additional/new effects.
*   Character stats 
*      strength - More health, damage, resistance to stun/dazed
*      agility  - More initiative, evasion, resistance to fatigue
*      dexterity - More percision, critical chance, resist fatigue
*      
*
* Misc Ides:
*   Smoke bomb. Dissapear. Enemy stops attacking.
*   Experience with individual weapon types allow training abilities which 
*      can be used with skill points aquired from defending.
*   Excalibur. (Has all affliction attributes)
*   Insta-death weapon/ability.
*   Equipment durability is the same as attack/defense power.
*   Flee only affects 1 character.
*   Elemental magics options: Execute, channel
*       Execute casts directly whatever affect it Has
*       Channel creates an interactable sphere the other casters can channel into
*       to create new spells. On subequent turns, execute performs the spell.
*       Weapons fighters can interact with channels to receive enchants, etc;
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
*    Precision/Evade calculates and executes correctly.
*    Critical damage is correct. Chance % is correct.
*    
*
*******************************************************************************/
