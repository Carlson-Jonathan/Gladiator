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
   return !(HP && BP && EP);
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
* Gets the calculated damage and applies it against a character. This function
* is used for both monster and hero attacks.
******************************************************************************/
void attackCharacter(Character & victim, Character & aggressor) {

   int damage[3];
   calculateDamage(aggressor, damage);

   if(victim.isDefending()) {
      damage[0] /= 2; damage[1] /= 2; damage[2] /= 2;
      victim.setDefending(false);
   }

   if(!aggressor.isHero())
      cout << "The ";
   cout << aggressor.getName() << aggressor.getWeapon()->getAction();
   if(aggressor.isHero())
      cout << "the ";
   cout << victim.getName();
   if(aggressor.isHero())
      cout << " with the " << aggressor.getWeapon()->getName();
   cout << "!\n";

   cout << "The " << victim.getName() << " takes damage:\n" 
        << "\tHP: " << damage[0] << "\n"
        << "\tBP: " << damage[1] << "\n"
        << "\tEP: " << damage[2] << "\n\n";

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
   
   monster.setWeapon(" slashes at ", 20, 50, 0.2, .06, .01, .01, 100);
   player.setWeapon("Spear");
   
   cout << "A " << monster.getName() << " draws near!\n" << endl;
   cout << "Player Weapon:" << endl; 
   player.getWeapon()->displayStats();
   cout << "Monster Weapon:" << endl; 
   monster.getWeapon()->displayStats();

   //player.getBloodPoints(), player.getEssencePoints()(!(HP && BP && EP))

   while(battle) {
      monster.displayStats();
      player.displayStats();

      short option = getUserInput({"Attack", "Defend", "Flee"});

      // Set player action
      if (option == 1) {
         attackCharacter(monster, player);
         if(isDefeated(mHP, mBP, mEP)) {
            cout << "The monster died!";
            break;
         }
         // Set monster affliction by your weapon
         if(isDefeated(mHP, mBP, mEP)) {
            cout << "The monster died!";
            break;
         }
         // Set monster's retaliation to your attack
         if(isDefeated(pHP, pBP, pEP)) {
            cout << "You died!";
            break;
         }
         // Set monster's retaliation afliction
         if(isDefeated(pHP, pBP, pEP)) {
            cout << "You died!";
            break;
         }
      }
      else if (option == 2) {
         defend(monster, player);
      }
      else if(option == 3) {
         flee();
      }

      // Monster's action
      attackCharacter(player, monster);
      if(isDefeated(pHP, pBP, pEP)) {
         cout << "You died!" << endl;
         break;
      }
      // Set affliction from monster attack
      if(isDefeated(pHP, pBP, pEP))
         cout << "You died!";
      // Set retaliation against monster attack
      if(isDefeated(mHP, mBP, mEP))
         cout << "The monster died!";
      // Set retaliation afliction against monster
      if(isDefeated(mHP, mBP, mEP))
         cout << "The monster died!";

      if(player.getBloodPoints() <= 0 || monster.getBloodPoints() <= 0 ||
         player.getHitPoints() <= 0 || monster.getHitPoints() <= 0 ||
         player.getEssencePoints() <= 0 || monster.getEssencePoints() <= 0) {
         battle = false;
         delete player.getWeapon();
      }

      // Additional affliction damage actions against player {

      // }

      // Additional affliction damage actions against monster {

      // }
   }
}
#endif // COMBAT_H