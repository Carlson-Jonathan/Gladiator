/******************************************************************************
* combat.cpp
* Author: Jonathan Carlson
* Last Updated: September 2020
* Description:
*  Governs the combat sequence applying stats from the Character class objects. 
******************************************************************************/
#ifndef COMBAT_H
#define COMBAT_H
#include <iostream>
#include "display.h"

bool isDefeated(short HP, short BP, short EP);
string nextAction(short pSlow, short mSlow, short& rpSlow, short & rmSlow);
void calculateDamageTypes(Character & aggressor, short damage[]);
void calculateRawDamage(Character & player, int damage[]);
bool attackCharacter(Character & victim, Character & aggressor);
void defend(Character & monster, Character & player);
void flee();
void determineAffliction(Character & aggressor, Character & victim, short damage[]);
void monsterAttack(Character & monster, Character & player);
void combat(Character & player);

/******************************************************************************
* bool isDefeated(short, short, short)
* Tells whether or not a character is dead.
******************************************************************************/
bool isDefeated(short HP, short BP, short EP) {
   return !(HP && BP && EP);
}

/******************************************************************************
* string nextAction(short, short, &short, &short)
* Determines the next character to take an action based on monster and Hero
* initiative levels.
******************************************************************************/
string nextAction(short pSlow, short mSlow, short &rpSlow, short &rmSlow) {

    if(rpSlow < rmSlow) {
        rpSlow += pSlow;
        return "Player's";
    }

    rmSlow += mSlow;
    return "Monster's";
}

/******************************************************************************
* void calculateDamageTypes(Character, short[]) 
* Calculates stab, crush, slash, and chop damage values and returns in an array
******************************************************************************/
void calculateDamageTypes(Character & aggressor, short damage[]) {
   AdvancedWeapon wep;
   wep = *aggressor.getWeapon();
	
   short baseDamage = random(
         aggressor.minDamage + wep.getMinDamage(), 
         aggressor.rangeDamage + wep.getRangeDamage()
   );

   short mStab = baseDamage * wep.getStab(),
        mCrush = baseDamage * wep.getCrush(),
        mSlash = baseDamage * wep.getSlash(),
         mChop = baseDamage * wep.getChop();

   damage[0] = mStab;
   damage[1] = mCrush;
   damage[2] = mSlash;
   damage[3] = mChop;
}

/******************************************************************************
* void calculateRawDamage(Character, int, short[])
* Accepts either the Hero or Monster type objects and uses the weapon object
* set in that type to determine the amount of damage that will be inflicted
* per combat round.
******************************************************************************/
void calculateRawDamage(Character & victim, short rawDamage[], short dT[]) {

   rawDamage[0] = dT[1] + (dT[2] * 0.34) + (dT[3] * 0.66),
   rawDamage[1] = dT[0] + (dT[2] * 0.66) + (dT[3] * 0.34),
   rawDamage[2] = 0;

   if(victim.isDefending())
      rawDamage[0] /= 2; rawDamage[1] /= 2; rawDamage[2] /= 2;
}

/******************************************************************************
* void attackMonster(Character, Character)
* Governs the 'attack' action. Calls all functions that determine the pattern
* of an attack.
******************************************************************************/
bool attackCharacter(Character & victim, Character & aggressor) {

   short damageTypes[4], rawDamage[3];
   calculateDamageTypes(aggressor, damageTypes);
   calculateRawDamage(victim, rawDamage, damageTypes);
   displayAttackMessage(victim, aggressor, rawDamage);

   victim.setHitPoints(-rawDamage[0]);
   victim.setBloodPoints(-rawDamage[1]);
   victim.setEssencePoints(-rawDamage[2]);

   if(isDefeated(victim.getHitPoints(), 
                 victim.getBloodPoints(), 
                 victim.getEssencePoints()))
      return true;

   determineAffliction(aggressor, victim, damageTypes);

   if(victim.isDefending())
      victim.setDefending(false);
}

/******************************************************************************
* void defend(Character, Character)
* Sets the player's defend status to true.
******************************************************************************/
void defend(Character & monster, Character & player) {
   player.setDefending(true);
   cout << "\t" << player.getName() << " stands guard.\n" << endl;
}

/******************************************************************************
* void flee()
* Will house the flee function.
******************************************************************************/
void flee() {
   // Based on yours and the monster's health
   cout << "\tYou run away screaming like a little girl!" << endl;
}

void determineAffliction(Character & aggressor, Character & victim, short damage[]) {
   AdvancedWeapon *wep = aggressor.getWeapon();
   if(wep->isSharp()) {
      victim.setBleeding((damage[0] * 0.2 + damage[2] * 0.1) * 10);
   }
}

bool applyBleeding(Character & victim) {
   short bleedAmt = victim.isBleeding() / 10;
   victim.setBloodPoints(-bleedAmt);
   if(victim.getBloodPoints() < 0)
      victim.setBloodPoints(0); 
   bleedingMessage(victim);
   victim.setBleeding(-bleedAmt - 2);
   if(victim.isBleeding() < 0)
      victim.setBleeding(0);
   if(isDefeated(victim.getHitPoints(), 
                 victim.getBloodPoints(), 
                 victim.getEssencePoints()))
      return true;
}

/******************************************************************************
* void combat()
* Houses the primary combat loop. Brings all other functions together to form
* a combat sequence.
******************************************************************************/
void combat(Character & player) {

   bool battle = true;
   Character monster;
   #define pHP {player.getHitPoints()}
   #define pBP {player.getBloodPoints()}
   #define pEP {player.getEssencePoints()}
   #define mHP {monster.getHitPoints()}
   #define mBP {monster.getBloodPoints()}
   #define mEP {monster.getEssencePoints()}
   short round = 1;
   short pSlow = player.getInitiative(),
         mSlow = monster.getInitiative(),
         rpSlow = pSlow,
         rmSlow = mSlow,
         option;

   
   // Placeholders
   // player.setWeapon("Spear");
   selectWeapon(player);

   
   cout << "A " << monster.getName() << " draws near!\n" << endl;
   cout << "Player Weapon:" << endl; 
   player.getWeapon()->displayStats();
   cout << "Monster Weapon:" << endl; 
   monster.getWeapon()->displayStats();

   while(battle) {

      if(nextAction(pSlow, mSlow, rpSlow, rmSlow) == "Player's") {
         if(player.isBleeding())
            if(applyBleeding(player)) 
               break;

         if(monster.isBleeding())
            if(applyBleeding(monster)) {
               combatVictory(player, monster);
               break;
         }
         displayCharacterStats(player, monster, round++);
         /*********************************************************************
         * Player's Action Block 
         *********************************************************************/
         option = getUserInput({"Attack", "Defend", "Flee"});

         // Set player action
         if (option == 1) {
            if(attackCharacter(monster, player)) {
               combatVictory(player, monster);
               break;
            }
            // Set monster affliction by your weapon
            // Set monster's retaliation to your attack
            // Set monster's retaliation afliction
         }
         else if (option == 2) {
            rpSlow = rmSlow;
            defend(monster, player);
         }
         else if(option == 3) {
            flee();
         }
      }
      else {
         /*********************************************************************
         * Monster's Action Block
         *********************************************************************/
         attackCharacter(player, monster);
         // Set affliction from monster attack
         // Set retaliation against monster attack
         // Set retaliation afliction against monster
      }

      /*********************************************************************
      * Residual Action Block
      *********************************************************************/


      // }

      // Additional affliction damage actions against monster {

      // }

      // delete player.getWeapon();
   }
}
#endif // COMBAT_H