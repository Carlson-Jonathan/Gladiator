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

private:
   /***************************************
   * Private variables
   ***************************************/
   bool 
      debugMode = false,
      battleOver = false, 
      textMode = false,

      // 0 = nextAction, applyFatigue/Bleeding
      code[10] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},

      // 0 = Bleeding animation
      // 1 = Dazed animation
      animation[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
      numMonsters,
      randNum;

   string 
      newMonster,
      battleMusic[3] = {"Sounds/Music/battle1.ogg", "Sounds/Music/battle2.ogg", "Sounds/Music/battle3.ogg"};

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
   sort(allCombatParticipants.begin(), allCombatParticipants.end(), sorter);
   if(debugMode) displayInitiatives(allCombatParticipants);
   allCombatParticipants[0]->runningInitiative += allCombatParticipants[0]->initiative;
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
   animation[5] = true;
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
      if(wep->isSharp) 
         victim.isBleeding += aggressor.weapon->isSharp;
      
      // Sets a stun affliction (skips the victim's next turn).
      if(wep->canStun)
         if(damageTypes[0] > aggressor.weapon->minDamage + 
            aggressor.weapon->rangeDamage / 2) { // Damge > than 50% of potential
            if(textMode) stunMessage(aggressor, victim);
            animation[7] = true;
            victim.runningInitiative += wep->canStun;
         }

      // Slows base initiative by venom stat
      if(wep->isVenomous) {
         victim.initiative += wep->isVenomous;   
         if(textMode) slowMessage(aggressor, victim);
         animation[8] = true;
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

   bleedingMessage(victim);
   isDefeated(victim);

   victim.setIsBleeding(-2);
}

/*******************************************************************************
* bool applyRegeneration(Character)
* Governs 1 round of character regeneration.
*******************************************************************************/
void Battle::applyRegeneration(Character & character) {
   character.setBloodPoints(character.regeneration);
   if(character.bloodPoints < character.maxBloodPoints - character.regeneration)
      regenerationMessage(character);
}

/*******************************************************************************
* void focus(Character)
* Sets the player's defend status to true.
*******************************************************************************/
void Battle::focus(Character & character) {
   defendingMessage(character);
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
   fleeCombatMessage();
}

/*******************************************************************************
* bool isDefeated(Character)
* Tells whether or not a character is dead.
*******************************************************************************/
bool Battle::isDefeated(Character & victim) {
   if(!(victim.hitPoints && victim.bloodPoints && victim.essencePoints)) {
      if(textMode) characterDiedMessage(victim); 
      victim.isDead = true; 
      animation[6] = true;
      return true;
   }
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
    animation[9] = true;
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
      if(textMode) displayAttackMessage(victim, aggressor, damageHpBpEp);
      animation[4] = true;
      applyDamage(victim);
      if(isDefeated(victim)) return 1;
      determineAffliction(aggressor, victim);

      if(victim.isHazardous) 
      receiveHazardDamage(aggressor, victim);
   }
   else
      animation[10] = true;
      if(textMode) missedAttackMessage(aggressor, victim);

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
         combatDefeat();
         battleOver = true;
         return 1;
      }
   }

   if(corpseExists) killCharacter();

   if(!listOfMonsters.size()) {
      combatVictory(heroes[0]);
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
      animation[0] = true;
      difference = (limit - victim.bloodPoints);

      additionalInit = (float)difference / (float)limit * 200.0;
      victim.runningInitiative += additionalInit;
      
      victim.weapon->basePenalty = 1 - ((float)difference / (float)limit / 2);

      if(textMode) fatigueMessage(victim, additionalInit);
   } 
   else {
  	   victim.weapon->basePenalty = 1;
      animation[0] = false;
      code[2] = true;
   }
}

/****************************************************************************
* void applyDazed(Character)
* If the character's BP falls below 2/3 maximum, reduces aim and evade.
****************************************************************************/
void Battle::applyDazed(Character & victim) {

   short limit = victim.maxHitPoints * 0.66;

   if(victim.hitPoints < limit) {
      animation[1] = true;
      short difference = (limit - victim.hitPoints); 
      
      victim.evasionPenalty   = (float)difference / (float)limit * 50.0;
      victim.precisionPenalty = (float)difference / (float)limit * 50.0;

      if(textMode) dazedMessage(victim, victim.precisionPenalty, victim.evasionPenalty);
   }
   else {
      victim.evasionPenalty = 0;
      victim.precisionPenalty = 0;
      animation[1] = false;
      code[3] = true;
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
   // if(burnTheBodies()) return 1;

   // applyRetaliationActions(activeCharacter, targetCharacter);
   // if(burnTheBodies()) return 1;

   // if(activeCharacter.isDefending) {
   //    activeCharacter.isDefending = false;
   //    removeDefendBonuses(activeCharacter);
   // }

   return 0;
}

/*******************************************************************************
* void applyCharacterAction() 
* Uses the 'option' variable to make a selection for a turn action.
*******************************************************************************/
bool Battle::applyCharacterAction(Character* character) {
   if(option == 1) {
      if(character->isHero) {
         if(completeOption1(*character, *monsterParticipants[target - 1])) 
            return 1;
      }
      else {
         if(completeOption1(*character, *heroParticipants[rand() % heroParticipants.size()])) 
            return 1;
      }
   }
   else if (option == 2) {
      focus(*character);                                // Player is defending
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
      // if(textMode) option = getUserInput({"Attack", "Defend", "Flee"}); 
      option = 1;
      animation[2] = true; 

      if (option == 1)                                           // Attack
         if(listOfMonsters.size() > 1) {
            // target = getUserInput(listOfMonsters);           // Attack what?
            target = 1;
         }
       else
           target = 1;                 // Auto attack if only 1 monster left 
   }

   // Get action for monster AI 
   else {
      randNum = rand() % 10;
      if(randNum > 7)
         option = 2;
      else
         option = 1;
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






/*###  ####  ######################################################  ####  #####
#####  ####  ###################                ###################  ####  #####
#####  ####  ##############                          ##############  ####  #####
#####  ####  ###########      Main Combat Function      ###########  ####  #####
#####  ####  ##############                          ##############  ####  #####
#####  ####  ###################                ###################  ####  #####
#####  ####  ######################################################  ####  #####
*
* void combat()
* Houses the primary combat loop. Brings all other functions together to form
* a combat sequence. Only stops when it hits a 'break' statement.
*
*******************************************************************************/
void Battle::combat(sf::RenderWindow & window) {

   playBattleMusic();

   short count = 0;
   while(true) {
      window.clear(sf::Color(102, 255, 255));
      usleep(500000); // 60 FPS = 16666
      
      // FPS tester
      count++;
      cout << "\nBattle in progress... FPS Counter: " << count << endl;

      if(animations->eventListener(window)) break;

      // Determines who's turn it is based on the lowest running initiative. 
      if(code[0]) participant = nextAction();                                    // Needs to be reactivated at end of turn
      code[0] = false;   

      /*************************************************************************
      *                        Turn Ending Action Block
      * Code in this block will be executed after any turn, hero's or monster's.
      *************************************************************************/
      if(code[1]) applyFatigue(*participant);                                    // Activate booleans to run animations.
      code[1] = false;
      if(code[2]) applyDazed(*participant);
      code[2] = false; 
      
      /*************************************************************************
      *                    Characters' Primary Action Block
      *************************************************************************/
      if(code[3]) getCharacterAction(participant);
      code[3] = false;

      if(code[4]) if(applyCharacterAction(participant)) break;
      code[4] = false;

      /*************************************************************************
      *                       Round Ending Action Block
      * A round ends after each character exceeds 200 running initiative.
      *************************************************************************/
      // if(isEndOfTurn()) 
      //    if(endOfTurnActions()) break; 

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
      cout << "Current Display(s)" << endl;

      if(animation[0]) {
         // This will just throw a "fatigued message over their head"
         cout << "\tFatigue animation is executed." << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[0] = false;
            code[2] = true;
            clock.restart();
         }
      }

      if(animation[1]) {
         // This will just throw a "dazed" message over their head.
         cout << "\tDazed animation is executed." << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[1] = false;
            code[3] = true;
            clock.restart();
         }
      }

      if(animation[2]) {
         cout << "\tAnimation: Character stats" << endl;                 // animation[2] needs to set itself to false when an option is selected
         cout << "\tAnimation: Next turn arrow" << endl;
         cout << "\tAnimation: Get user input (listen event)" << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[2] = false;
            animation[3] = true;
            clock.restart();
         }
      }

      if(animation[3]) {
         cout << "\tSelect which monster to attack" << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[3] = false;
            code[4] = true;
            clock.restart();
         }  
      }

      if(animation[4]) {
         cout << "\tDisplay attack animation/message" << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[4] = false;
            clock.restart();
         }           
      }

      if(animation[5]) {
         cout << "\tDisplay damage numbers." << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[5] = false;
            clock.restart();
            code[1] = true;
         }  
      }

      if(animation[6]) {
         cout << "\tDisplay character defeat animation." << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[6] = false;
            clock.restart();
         }  
      }
      
      if(animation[7]) {
         cout << "\tDisplay stun animation." << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[7] = false;
            clock.restart();
         }  
      }
      
      if(animation[8]) {
         cout << "\tDisplay venom animation." << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[8] = false;
            clock.restart();
         }  
      }
      
      if(animation[9]) {
         cout << "\tDisplay hazard damage taken." << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[9] = false;
            clock.restart();
         }  
      }

      if(animation[10]) {
         cout << "\tDisplay missed attack message." << endl;
         if(clock.getElapsedTime().asSeconds() > 5.0f) {
            animation[10] = false;
            clock.restart();
            code[1] = true;
         }  
      }


      window.display();
   }   

   cout << "End of battle." << endl;

   // if(debugMode) 
   //    cout << "\nDont forget to reset world affecting stats at the end of combat!" 
   //         << endl;
}
#endif // BATTLE_H



// Bugs to fix:


// Refactors:
   // To create animations, let an entire combat round happen with no pauses or animations.
   // Go through the code line by line and determine if an animation could be triggered.
   // Create an animation lineup list (vector<bool>) where each element represents a 
   // specific animation in the order they would occur. After the lineup list has been 
   // populated, shut off the combat mechanics with an if(boolean) statement (it should
   // only cycle through once anyway). Similar to the lineup list, create coresponding
   // animation functions in logical order. Each function should be preceeded by an 
   // if(lineupList[index]). Start the animation cycle by iterating through the lineup list 
   // calling only the first true element, then break the loop. The coresponding function
   // will be called. At the end of each function (a certain amount of time has passed), 
   // the same loop will be called to determine the next animation function and so on. The
   // last animation function will reactivate the combat mechanics to start a new round.
   // If the combat round includes a prompt for player input, deactivate all other combat
   // mechanics and animations except for the player prompt animation. Once that animation
   // is complete (the player has made their selections), the other combat mechanics will 
   // reactivate and continue to populate the next animation lineup list.

// Currenlty working on:
//   Implementing SFML game platform.

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
