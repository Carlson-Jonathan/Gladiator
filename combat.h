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

void preventNegativeDamage(short damageTypes[], short block[]) {
   for(short i = 0; i < 4; i++) {
      damageTypes[i] -= block[i];
      if(damageTypes[i] < 0)
         damageTypes[i] = 0;
   }
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
   cout << "Armor block values based on defence power: " << victim.armor->defencePower << endl;
   cout << "Crush: " << block[0] << " | Chop: " << block[1] << " | Slash: " << block[2] << " | Stab: " << block[3] << "\n\n";

   preventNegativeDamage(damageTypes, block);
   cout << "Modified Damage Types:" << endl;
   cout << "Cr: " << damageTypes[0] << " | Ch: " << damageTypes[1] << " | Sl: " << damageTypes[2] << " | St: " << damageTypes [3] << "\n\n";

   calculateRawDamage(victim, rawDamage, damageTypes);
   cout << "Raw Damage using modified types:" << endl;
   cout << "HP: " << rawDamage[0] << " | BP: " << rawDamage[1] << " | EP: " << rawDamage[2] << "\n\n";

   displayAttackMessage(victim, aggressor, rawDamage);

   short damageHP = rawDamage[0] - block[0],
         damageBP = rawDamage[1] - block[1],
         damageEP = rawDamage[2] - block[2];

   victim.hitPoints -= rawDamage[0];
   victim.bloodPoints -= rawDamage[1];
   victim.essencePoints -= rawDamage[2];

   if(isDefeated(victim.hitPoints,
                 victim.bloodPoints,
                 victim.essencePoints))
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
   Weapon wep;
   wep = *aggressor.weapon;

   short baseDamage = random(
         aggressor.minDamage + wep.minDamage,
         aggressor.rangeDamage + wep.rangeDamage
   );

   short mStab = baseDamage * wep.stab,
        mCrush = baseDamage * wep.crush,
        mSlash = baseDamage * wep.slash,
         mChop = baseDamage * wep.chop;

   damage[0] = mCrush;
   damage[1] = mChop;
   damage[2] = mSlash;
   damage[3] = mStab;
}

/******************************************************************************
* void calculateDamageBlock(Character, short[])
* Calculates the damage reduction provided by various armors. Each block[]
* value (shorts) represent the amount to reduce the damage type by.
******************************************************************************/
void calculateDamageBlock(Character & victim, short block[]) {
   Armor armor = *victim.armor;

   short dCrush = armor.defencePower * armor.crush,
         dChop = armor.defencePower  * armor.chop,
         dSlash = armor.defencePower * armor.slash,
         dStab = armor.defencePower  * armor.stab;

   // To do: Figure out how to implement a vulnerability that increases 
   // damage if the armor.(damageType) value is negative.         

   block[0] = dCrush;
   block[1] = dChop;
   block[2] = dSlash;
   block[3] = dStab;

}

/******************************************************************************
* void calculateRawDamage(Character, int, short[])
* Accepts either the Hero or Monster type objects and uses the weapon object
* set in that type to determine the amount of damage that will be inflicted
* per combat round. Basically it splits the 4 damage types into 3 health types.1
******************************************************************************/
void calculateRawDamage(Character & victim, short rawDamage[], short dT[]) {

       // dT[0] = Crush, dT[1] = Chop, dT[2] = Slash, dT[3] = Stab            
   rawDamage[0] = dT[0] + (dT[2] * 0.34) + (dT[1] * 0.66),   // HP
   rawDamage[1] = dT[3] + (dT[2] * 0.66) + (dT[1] * 0.34),   // BP
   rawDamage[2] = 0;                                         // EP

   if(victim.isDefending) {
      cout << victim.name << " defends, cutting damage in half!\n\n";
      rawDamage[0] /= 2; rawDamage[1] /= 2; rawDamage[2] /= 2;
   }
}

/******************************************************************************
* void determineAffliction(Character, Character, short[])
* Extracts weapon information to determine which types of afflictions apply.
******************************************************************************/
void determineAffliction(Character & aggressor, Character & victim, short damage[]) {
   Weapon *wep = aggressor.weapon;

   // Afflictions that apply only if the victim is not defending
   if(!victim.isDefending) {

      if(wep->sharp) 
         victim.isBleeding = (damage[0] * 0.2 + damage[2] * 0.1) * 10;
      


   }
}

/******************************************************************************
* void applyBleeding(Character)
* Governs 1 round of character bleeding. Sets and reduces ongoing bleed effect.
******************************************************************************/
bool applyBleeding(Character & victim) {
   short bleedAmt = victim.isBleeding / 10;
   victim.bloodPoints -= bleedAmt;
   if(victim.bloodPoints < 0)
      victim.bloodPoints = 0;
   bleedingMessage(victim);
   victim.isBleeding = (-bleedAmt - 2);
   if(victim.isBleeding < 0)
      victim.isBleeding = 0;
   if(isDefeated(victim.hitPoints,
                 victim.bloodPoints,
                 victim.essencePoints)) 
      return true;
}

/******************************************************************************
* void defend(Character, Character)
* Sets the player's defend status to true.
******************************************************************************/
void defend(Character & character) {
   character.isDefending = true;
   cout << "\t" << character.name << " stands guard.\n" << endl;
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
         pSlow = player.initiative,
         mSlow = monster.initiative,
         rpSlow = pSlow,
         rmSlow = mSlow,
         option;
   
   // Temporaries
   selectWeapon(player);
   selectArmor(player);

   cout << "A " << monster.name << " draws near!\n" << endl;
   cout << "Player Weapon:" << endl;
   displayStats(player);
   cout << "Player Armor:" << endl;
   player.armor->displayStats();
   cout << "Monster Weapon:" << endl;
   displayStats(monster);
   cout << "Monster Armor:" << endl;
   monster.armor->displayStats();


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
         if(player.isBleeding)
            if(applyBleeding(player))
               break;
         if(monster.isBleeding)
            if(applyBleeding(monster)) {
               combatVictory(player, monster);
               break;
         }

         displayCharacterStats(player, monster, round++);

         // Reset Stats
         monster.isDefending = false; player.isDefending = false;

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
