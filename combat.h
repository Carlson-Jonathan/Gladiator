/******************************************************************************
* combat.cpp
* Author: Jonathan Carlson
* Description:
*  Governs the combat sequence applying stats from the Character class objects.
******************************************************************************/
#ifndef COMBAT_H
#define COMBAT_H
#include <iostream>
#include "display.h"

string nextAction(short pSlow, short mSlow, short& rpSlow, short & rmSlow);
bool attackCharacter(Character & victim, Character & aggressor);
void calculateDamageTypes(Character & aggressor, Character victim, short damage[]);
void calculateDamageBlock(Character & victim, short block[]);
void calculateRawDamage(Character & victim, short rawDamage[], short dT[]);
void determineAffliction(Character & aggressor, Character & victim, short damage[]);
bool applyBleeding(Character & victim);
void defend(Character & monster, Character & player);
void flee();
bool isDefeated(short HP, short BP, short EP);
void combat(Character & player);

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
* void attackCharacter(Character, Character)
* Governs the 'attack' action. Calls all functions that determine the pattern
* of an attack.
******************************************************************************/
bool attackCharacter(Character & victim, Character & aggressor) {

   short damageTypes[4], rawDamage[3], block[4];
   
   calculateDamageTypes(aggressor, victim, damageTypes);
   cout << "Damage Types:" << endl;
      cout << "Cr: " << damageTypes[0] << " | Ch: " << damageTypes[1] << " | Sl: " << damageTypes[2] << " | St: " << damageTypes [3] << "\n\n";

   calculateDamageBlock(victim, block);
   cout << "Armor block values based on defence power: " << victim.getArmor()->getDefencePower() << endl;
   cout << "Crush: " << block[0] << " | Chop: " << block[1] << " | Slash: " << block[2] << " | Stab: " << block[3] << "\n\n";

   for(short i = 0; i < 4; i++) {
      damageTypes[i] -= block[i];
      if(damageTypes[i] < 0)
         damageTypes[i] = 0;
   }

   cout << "Modified Damage Types:" << endl;
   cout << "Cr: " << damageTypes[0] << " | Ch: " << damageTypes[1] << " | Sl: " << damageTypes[2] << " | St: " << damageTypes [3] << "\n\n";

   calculateRawDamage(victim, rawDamage, damageTypes);
   cout << "Raw Damage using modified types:" << endl;
   cout << "HP: " << rawDamage[0] << " | BP: " << rawDamage[1] << " | EP: " << rawDamage[2] << "\n\n";

   displayAttackMessage(victim, aggressor, rawDamage);

   short damageHP = rawDamage[0] - block[0],
         damageBP = rawDamage[1] - block[1],
         damageEP = rawDamage[2] - block[2];

   victim.setHitPoints(-rawDamage[0]);
   victim.setBloodPoints(-rawDamage[1]);
   victim.setEssencePoints(-rawDamage[2]);

   if(isDefeated(victim.getHitPoints(),
                 victim.getBloodPoints(),
                 victim.getEssencePoints()))
      return true;

   determineAffliction(aggressor, victim, damageTypes);

   return false;
}

/******************************************************************************
* void calculateDamageTypes(Character, Character, short[])
* Calculates stab, crush, slash, and chop damage values and returns in an array
******************************************************************************/
void calculateDamageTypes(Character & aggressor, Character victim, 
                          short damage[]) {
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

   damage[0] = mCrush;
   damage[1] = mSlash;
   damage[2] = mChop;
   damage[3] = mStab;
}

/******************************************************************************
* void calculateDamageBlock(Character, short[])
* Calculates the damage reduction provided by various armors. Each block[]
* value (shorts) represent the amount to reduce the damage type by.
******************************************************************************/
void calculateDamageBlock(Character & victim, short block[]) {
   AdvancedArmor armor = *victim.getArmor();

   short dCrush = armor.getDefencePower() * armor.getCrush(),
         dChop = armor.getDefencePower()  * armor.getChop(),
         dSlash = armor.getDefencePower() * armor.getSlash(),
         dStab = armor.getDefencePower()  * armor.getStab();

   block[0] = dCrush;
   block[1] = dChop;
   block[2] = dSlash;
   block[3] = dStab;

}

/******************************************************************************
* void calculateRawDamage(Character, int, short[])
* Accepts either the Hero or Monster type objects and uses the weapon object
* set in that type to determine the amount of damage that will be inflicted
* per combat round.
******************************************************************************/
void calculateRawDamage(Character & victim, short rawDamage[], short dT[]) {


   // Reduce for Armor/Immunity
   // dT[0] = dT[0] * (1.0 - victim.getArmor()->getStab());
   // dT[1] = dT[1] * (1.0 - victim.getArmor()->getCrush());
   // dT[2] = dT[2] * (1.0 - victim.getArmor()->getSlash());
   // dT[3] = dT[3] * (1.0 - victim.getArmor()->getChop());
   
   // cout << "Damage after armor reductions:" << endl;
   // cout << "2- St: " << dT[0] << " Cr: " << dT[1] << " Sl: " << dT[2] << " Ch: " << dT [3] << "\n\n";

   // SPlit Damages (HP/BP/EP)
   rawDamage[0] = dT[1] + (dT[2] * 0.34) + (dT[3] * 0.66),
   rawDamage[1] = dT[0] + (dT[2] * 0.66) + (dT[3] * 0.34),
   rawDamage[2] = 0;

   if(victim.isDefending()) {
      cout << victim.getName() << " defends, cutting damage in half!\n\n";
      rawDamage[0] /= 2; rawDamage[1] /= 2; rawDamage[2] /= 2;
   }
}

/******************************************************************************
* void determineAffliction(Character, Character, short[])
* Extracts weapon information to determine which types of afflictions apply.
******************************************************************************/
void determineAffliction(Character & aggressor, Character & victim, short damage[]) {
   AdvancedWeapon *wep = aggressor.getWeapon();

   // Afflictions that apply only if the victim is not defending
   if(!victim.isDefending()) {

      if(wep->isSharp()) 
         victim.setBleeding((damage[0] * 0.2 + damage[2] * 0.1) * 10);
      


   }
}

/******************************************************************************
* void applyBleeding(Character)
* Governs 1 round of character bleeding. Sets and reduces ongoing bleed effect.
******************************************************************************/
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
* void defend(Character, Character)
* Sets the player's defend status to true.
******************************************************************************/
void defend(Character & character) {
   character.setDefending(true);
   cout << "\t" << character.getName() << " stands guard.\n" << endl;
}

/******************************************************************************
* void flee()
* Will house the flee function.
******************************************************************************/
void flee() {
   // Based on yours and the monster's health
   cout << "\tYou run away screaming like a little girl!" << endl;
}

/******************************************************************************
* bool isDefeated(short, short, short)
* Tells whether or not a character is dead.
******************************************************************************/
bool isDefeated(short HP, short BP, short EP) {
   return !(HP && BP && EP);
}



//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================



/******************************************************************************
* void combat(Character)
* Houses the primary combat loop. Brings all other functions together to form
* a combat sequence.
******************************************************************************/
void combat(Character & player, string newMonster) {

   bool battle = true;
   Character monster(newMonster);
   short round = 1,
         pSlow = player.getInitiative(),
         mSlow = monster.getInitiative(),
         rpSlow = pSlow,
         rmSlow = mSlow,
         option;
   
   // Temporaries
   selectWeapon(player);
   selectArmor(player);

   cout << "A " << monster.getName() << " draws near!\n" << endl;
   cout << "Player Weapon:" << endl;
   displayStats(player);
   cout << "Player Armor:" << endl;
   player.getArmor()->displayStats();
   cout << "Monster Weapon:" << endl;
   displayStats(monster);
   cout << "Monster Armor:" << endl;
   monster.getArmor()->displayStats();


   while(battle) {
      
      if(nextAction(pSlow, mSlow, rpSlow, rmSlow) == "Player's") {
         
         /*********************************************************************
         *                     Round Ending Action Block
         * This block is called after all players and monsters have taken at 
         * least 1 action (this is what defines a 'combat round').
         * Actions that occur once per round should be placed here, such as
         * bleeding, resetting defend status, etc.
         *********************************************************************/
         // Apply bleeding
         if(player.isBleeding())
            if(applyBleeding(player))
               break;
         if(monster.isBleeding())
            if(applyBleeding(monster)) {
               combatVictory(player, monster);
               break;
         }

         displayCharacterStats(player, monster, round++);

         // Reset Stats
         monster.setDefending(0); player.setDefending(0);

         /*********************************************************************
         *                        Player's Action Block
         *********************************************************************/
         option = getUserInput({"Attack", "Defend", "Flee"});

         // Set player action
         if (option == 1) {
            if(attackCharacter(monster, player)) {
               combatVictory(player, monster);
               break;
            }
            // Set monster's retaliation to your attack
            // Set monster's retaliation afliction
            // Set residual actions
         }
         else if (option == 2) {
            defend(player);
         }
         else if(option == 3) {
            flee();
         }
      }

      else {
         /*********************************************************************
         *                        Monster's Action Block
         *********************************************************************/
         if(attackCharacter(player, monster)) {        // Returns 1 if defeated
            combatDefeat();
            break;
         }
         
         // Set retaliation against monster attack
         // Set retaliation afliction against monster

         // Set residual actions
      }

      /************************************************************************
      *                        Residual Action Block
      * The code in this block will be called after ever action by any
      * character (rapid DOT afflictions).
      ************************************************************************/

      
      // Action code goes here.

   }
}
#endif // COMBAT_H
