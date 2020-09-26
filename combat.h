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
#include "character.h"
//#include "hero.h"
//#include "monster.h"
#include "general.h"

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
   return HP && BP && EP;
}

/******************************************************************************
* string nextAction(short, short, &short, &short)
* Determines the next character to take an action based on monster and Hero
* initiative levels.
******************************************************************************/
string nextAction(short pSlow, short mSlow, short & rpSlow, short & rmSlow) {

    if(rpSlow < rmSlow) {
        rpSlow += pSlow;
        return "Player attacks!";
    }

    rmSlow += mSlow;
    return "\t\t\t\tMonster attacks!";

/* This code will be included in the combat loop:
   int pSlow = 90,
        mSlow = 100,
        rpSlow = pSlow,
        rmSlow = mSlow;

    for(int i = 1; i <= 50; i++) // combat loop
        cout << "Turn " << i << ": " 
        << nextAction(pSlow, mSlow, rpSlow, rmSlow) 
        << endl;
*/
}

/******************************************************************************
* void calculateDamage(Character, int)
* Accepts either the Hero or Monster type objects and uses the weapon object
* set in that type to determine the amount of damage that will be inflicted
* per combat round.
******************************************************************************/
void calculateDamage(Character & character, int damage[]) {
   AdvancedWeapon wep;
   wep = *character.getWeapon();
	
   int baseDamage = random(
      character.minDamage + wep.getMinDamage(), 
      character.rangeDamage + wep.getRangeDamage()
   );

   // Will add vulnerabilities later:
   // mstab * monster.getVstab()
   float mStab =  baseDamage * wep.getStab(),
   mCrush =       baseDamage * wep.getCrush(),
   mSlash =       baseDamage * wep.getSlash(),
   mChop =        baseDamage * wep.getChop();

   damage[0] = mCrush + (mSlash * 0.34) + (mChop * 0.66),
   damage[1] = mStab + (mSlash * 0.66) + (mChop * 0.34),
   damage[2] = 0;
}

/******************************************************************************
* void attackMonster(Character, Character)
* Calls the calculateDamage function and other functions that will inflict an
* ailment on a monster and adjusts monter's health and status conditions.
******************************************************************************/
void attackMonster(Character & monster, Character & player) {

   int damage[3];
   calculateDamage(player, damage);

   cout << "You attack the " << monster.getName() << "\n"
        << "The " << monster.getName() << " takes damage:\n" 
        << "\tHP: " << damage[0] << "\n"
        << "\tBP: " << damage[1] << "\n"
        << "\tEP: " << damage[2] << "\n\n";

   monster.setHitPoints(-damage[0]);
   monster.setBloodPoints(-damage[1]);
   monster.setEssencePoints(-damage[2]);
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

/******************************************************************************
* void monsterAttack()
* Sets the monster's attack action.
******************************************************************************/
void monsterAttack(Character & monster, Character & player) {
   
   int damage[3];
   calculateDamage(player, damage);
   
   if(player.isDefending()) {
      damage[0] /= 2; damage[1] /= 2; damage[2] /= 2;
      player.setDefending(false);
   }

   cout << "The " << monster.getName() << monster.getWeapon()->getName() << "\n"
        << player.getName() << " takes damage:\n" 
        << "\tHP: " << damage[0] << "\n"
        << "\tBP: " << damage[1] << "\n"
        << "\tEP: " << damage[2] << "\n\n";

   player.setHitPoints(-damage[0]);
   player.setBloodPoints(-damage[1]);
   player.setEssencePoints(-damage[2]);   
}

/******************************************************************************
* void combat()
* Houses the primary combat loop. Brings all other functions together to form
* a combat sequence.
******************************************************************************/
void combat(Character & player) {

   bool battle = true;
   Character monster;
   
   monster.setWeapon(" slashes at you!", 20, 50, 0.2, .06, .01, .01, 100);
   player.setWeapon("Battle Axe");
   
   cout << "A " << monster.getName() << " draws near!\n" << endl;
   cout << "Player Weapon:" << endl; 
   player.getWeapon()->displayStats();
   cout << "Monster Weapon:" << endl; 
   monster.getWeapon()->displayStats();

   while(battle) {
      monster.displayStats();
      player.displayStats();

      short option = getUserInput({"Attack", "Defend", "Flee"});

      // Set player action
      switch (option) {
         case 1: {
            attackMonster(monster, player);
            // Check for defeat
            // Set affliction
            // Check for defeat
            // Set retaliation
            // Check for defeat
            // Set retaliation afliction
            // Check for defeat
            break; 
         }
         case 2:
            defend(monster, player);
            break;
         case 3:
            flee();
            break;
         default:;
      }

      if(monster.getHitPoints() <= 0) {
         cout << "You killed the monster!" << endl;
         delete player.getWeapon();
         break;
      }

      // Monster's action
      monsterAttack(monster, player);
      if(isDefeated(player.getHitPoints(), 
                 player.getBloodPoints(), 
                 player.getEssencePoints())) {
         cout << "You died!" << endl;
         break;
      }
      // Set affliction
      // Check for defeat
      // Set retaliation
      // Check for defeat
      // Set retaliation afliction
      // Check for defeat

      if(player.getBloodPoints() <= 0 || monster.getBloodPoints() <= 0 ||
         player.getHitPoints() <= 0 || monster.getHitPoints() <= 0 ||
         player.getEssencePoints() <= 0 || monster.getEssencePoints() <= 0) {
         battle = false;
         delete player.getWeapon();
      }
   }
}
#endif // COMBAT_H