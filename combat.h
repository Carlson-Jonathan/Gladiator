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

void calculateDamage(Character & player, int damage[]);
void attackMonster(Character & monster, Character & player);
void defend(Character & monster, Character & player);
void flee();
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
* void calculateDamage(Character, int)
* Accepts either the Hero or Monster type objects and uses the weapon object
* set in that type to determine the amount of damage that will be inflicted
* per combat round.
******************************************************************************/
void calculateDamage(Character & aggressor, Character & victim, short damage[]) {
   AdvancedWeapon wep;
   wep = *aggressor.getWeapon();
	
   int baseDamage = random(
      aggressor.minDamage + wep.getMinDamage(), 
      aggressor.rangeDamage + wep.getRangeDamage()
   );

   float mStab =  baseDamage * wep.getStab(),
   mCrush =       baseDamage * wep.getCrush(),
   mSlash =       baseDamage * wep.getSlash(),
   mChop =        baseDamage * wep.getChop();

   damage[0] = mCrush + (mSlash * 0.34) + (mChop * 0.66),
   damage[1] = mStab + (mSlash * 0.66) + (mChop * 0.34),
   damage[2] = 0;

   /*
   Damage afflictions:
   4.) burn
   5.) bleed
   6.) venom
   7.) stun
   8.) blind
   9.) slow
   10.) freeze
   11.) parry
   */



   if(victim.isDefending()) {
      damage[0] /= 2; damage[1] /= 2; damage[2] /= 2;
      victim.setDefending(false);
   }
}

/******************************************************************************
* void attackMonster(Character, Character)
* Governs the 'attack' action. Calls all functions that determine the pattern
* of an attack:
******************************************************************************/
void attackCharacter(Character & victim, Character & aggressor) {

   short damage[11];

   calculateDamage(aggressor, victim, damage);
   displayAttackMessage(victim, aggressor, damage);

   victim.setHitPoints(-damage[0]);
   victim.setBloodPoints(-damage[1]);
   victim.setEssencePoints(-damage[2]);
}

/******************************************************************************
* void defend(Character, Character)
* Sets the player's defend status to true.
******************************************************************************/
void defend(Character & monster, Character & player) {
   player.setDefending(true);
   cout << player.getName() << " stands guard.\n" << endl;
}

/******************************************************************************
* void flee()
* Will house the flee function.
******************************************************************************/
void flee() {
   // Based on yours and the monster's health
   cout << "You run away screaming like a little girl!" << endl;
}

void determineAffliction(Character aggressor, Character & victim, short damage[]) {
   // if aggressor's weapon is(affliction)
   //    Determine if damage qualifies for affliction
   //    calculate affliction damage
   //    apply affliction to victim




}

void setBleeding(short damage) {


}

void applyBleedingDamage(Character & victim) {

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
         displayCharacterStats(player, monster, round++);
         /*********************************************************************
         * Player's Action Block 
         *********************************************************************/
         option = getUserInput({"Attack", "Defend", "Flee"});

         // Set player action
         if (option == 1) {
            attackCharacter(monster, player);
            if(isDefeated(mHP, mBP, mEP)){
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

      // Additional affliction damage actions against player {

      // }

      // Additional affliction damage actions against monster {

      // }

      // delete player.getWeapon();
   }
}
#endif // COMBAT_H