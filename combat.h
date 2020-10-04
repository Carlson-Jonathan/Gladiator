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
#include "display.h"

string nextAction(const short pSlow, const short mSlow, short & rpSlow, short & rmSlow);
void preventNegativeDamage(short damageTypes[], short block[]);
bool attackCharacter(Character & victim, Character & aggressor);
void calculateDamageTypes(const Character & aggressor, short damage[]);
void calculateDamageBlock(const Character & victim, short block[]);
void calculateRawDamage(const Character & victim, short rawDamage[], short dT[]);
int applyDamage(Character & victim, short rawDamage[]); 
void determineAffliction(const Character & aggressor, Character & victim, short damage[]);
bool applyBleeding(Character & victim);
void focus(Character & character);
void flee();
bool isDefeated(short HP, short BP, short EP);
void combat(Character & player);

/*******************************************************************************
* string nextAction(short, short, &short, &short)
* Determines the next character to take an action based on monster and Hero
* initiative levels. The player wins ties.
*******************************************************************************/
string nextAction(const short pSlow, const short mSlow, 
                        short & rpSlow, short & rmSlow) {

   cout << "Player/Monster Initiatives: " << rpSlow << " | " << rmSlow << "\n\n";
   if(rpSlow <= rmSlow) {
       rpSlow += pSlow;
       return "Player's";
   }

   rmSlow += mSlow;
   return "Monster's";
}

/*******************************************************************************
* void preventNegativeDamage(short, short[])
* Applies the damage reduction of the armor assuring that it does not go below 
* 0. The formula applied is to reduce each damage type by the block damage
* type as a percentage.
*******************************************************************************/
void preventNegativeDamage(short damageTypes[], short block[]) {
   for(short i = 0; i < 4; i++) {
      damageTypes[i] *= (1.0 - ((float)block[i] / 100));
      if(damageTypes[i] < 0)
         damageTypes[i] = 0;
   }
}

/*******************************************************************************
* void attackCharacter(Character, Character)
* Governs the 'attack' action. Calls all functions that determine the pattern
* of an attack. Anything printed in this section is just for testing.
*******************************************************************************/
bool attackCharacter(Character & victim, Character & aggressor) {

   short damageTypes[4], rawDamage[3], block[4]; 
   calculateDamageTypes(aggressor, damageTypes);
   cout << aggressor.name << " damage Types:" << endl;
   cout << "Cr: " << damageTypes[0] << " | Ch: " << damageTypes[1] << " | Sl: " << damageTypes[2] << " | St: " << damageTypes [3] << "\n\n";

   calculateDamageBlock(victim, block);
   cout << victim.name << " armor block values based on defence power: " << victim.armor->defencePower << endl;
   cout << "Crush: " << block[0] << " | Chop: " << block[1] << " | Slash: " << block[2] << " | Stab: " << block[3] << "\n\n";

   preventNegativeDamage(damageTypes, block);
   cout << aggressor.name << " modified Damage Types:" << endl;
   cout << "Cr: " << damageTypes[0] << " | Ch: " << damageTypes[1] << " | Sl: " << damageTypes[2] << " | St: " << damageTypes [3] << "\n\n";

   calculateRawDamage(victim, rawDamage, damageTypes);
   cout << "Raw Damage using modified types:" << endl;
   cout << "HP: " << rawDamage[0] << " | BP: " << rawDamage[1] << " | EP: " << rawDamage[2] << "\n\n";

   displayAttackMessage(victim, aggressor, rawDamage);
   if(applyDamage(victim, rawDamage)) return true;
   determineAffliction(aggressor, victim, damageTypes);

   return false;
}

/*******************************************************************************
* void calculateDamageTypes(Character, Character, short[])
* Generates stab, crush, slash, and chop damage values and returns in an array.
*******************************************************************************/
void calculateDamageTypes(const Character & aggressor, short damage[]) {

   short baseDamage = random(aggressor.weapon->minDamage, 
                             aggressor.weapon->rangeDamage);

   damage[0] = ceil(baseDamage * aggressor.weapon->crush);
   damage[1] = ceil(baseDamage * aggressor.weapon->chop);
   damage[2] = ceil(baseDamage * aggressor.weapon->slash);
   damage[3] = ceil(baseDamage * aggressor.weapon->stab);
}

/*******************************************************************************
* void calculateDamageBlock(Character, short[])
* Calculates the damage reduction provided by various armors. Each block[]
* value (shorts) represent the amount to reduce the damage type by.
*******************************************************************************/
void calculateDamageBlock(const Character & victim, short block[]) {
   Armor armor = *victim.armor;

   // To do: Figure out how to implement a vulnerability that increases 
   // damage if the armor.(damageType) value is negative.         

   block[0] = ceil(armor.defencePower * armor.crush);
   block[1] = ceil(armor.defencePower * armor.chop);
   block[2] = ceil(armor.defencePower * armor.slash);
   block[3] = ceil(armor.defencePower * armor.stab);
}

/*******************************************************************************
* void calculateRawDamage(Character, int, short[])
* Accepts either the Hero or Monster type objects and uses the weapon object
* set in that type to determine the amount of damage that will be inflicted
* per combat round. Basically it splits the 4 damage types into 3 health types.
*******************************************************************************/
void calculateRawDamage(const Character & victim, short rawDamage[], short dT[]) {

       // dT[0] = Crush, dT[1] = Chop, dT[2] = Slash, dT[3] = Stab            
   rawDamage[0] = dT[0] + ceil(dT[2] * 0.34) + ceil(dT[1] * 0.66),   // HP
   rawDamage[1] = dT[3] + ceil(dT[2] * 0.66) + ceil(dT[1] * 0.34),   // BP
   rawDamage[2] = 0;                                                 // EP

   if(victim.isDefending) {
      cout << victim.name << " defends, cutting damage in half!\n\n";
      rawDamage[0] /= 2; rawDamage[1] /= 2; rawDamage[2] /= 2;
   }
}

/*******************************************************************************
* int applyDamage(Character, short[]) 
* Applies the calculated rawDamage to the victim's health and determines if
* the victim has been defeated.
*******************************************************************************/
int applyDamage(Character & victim, short rawDamage[]) {
   victim.setHitPoints(-rawDamage[0]);
   victim.setBloodPoints(-rawDamage[1]);
   victim.setEssencePoints(-rawDamage[2]);

   if(isDefeated(victim.hitPoints, victim.bloodPoints, victim.essencePoints)) 
      return true;
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
      if(wep->sharp) {
         victim.isBleeding += ceil(damageTypes[3] * 0.2 + damageTypes[2] * 0.1) * 10;
         // cout << victim.name << " begins hemorrhaging from their wound!" << "\n\n";
      }
      
      // Sets a stun affliction (skips the victim's next turn).
      if(wep->blunt)
         if(damageTypes[0] > aggressor.weapon->minDamage + 
            aggressor.weapon->rangeDamage / 2) {
            stunMessage(aggressor, victim);
            victim.runningInitiative += victim.initiative;
         }

   // Set Affliction


   // ...
   }
}

/*******************************************************************************
* void applyBleeding(Character)
* Governs 1 round of character bleeding. Sets and reduces ongoing bleed effect.
*******************************************************************************/
bool applyBleeding(Character & victim) {
   short bleedAmt = victim.isBleeding / 10;
   victim.bloodPoints -= bleedAmt;
   if(victim.bloodPoints < 0)
      victim.bloodPoints = 0;
   bleedingMessage(victim);
   victim.isBleeding -= bleedAmt - 2;
   if(victim.isBleeding < 0)
      victim.isBleeding = 0;
   if(isDefeated(victim.hitPoints, victim.bloodPoints, victim.essencePoints)) 
      return true;
}

/*******************************************************************************
* void defend(Character, Character)
* Sets the player's defend status to true.
*******************************************************************************/
void focus(Character & character) {
   character.isDefending = true;
   cout << "\t" << character.name 
        << " raises their guard and plans their next strike.\n" << endl;
   // Increases damage on next strike (allows for criticals?).
   // Increases chance to apply affliction on next strike.
   // Can be used to overcome enemy strengths (tough defence).
}

/*******************************************************************************
* void flee()
* Will house the flee function.
*******************************************************************************/
void flee() {
   // Based on yours and the monster's health
   cout << "\tYou run away screaming like a little girl!" << endl;
}

/*******************************************************************************
* bool isDefeated(short, short, short)
* Tells whether or not a character is dead.
*******************************************************************************/
bool isDefeated(short HP, short BP, short EP) {
   return !(HP && BP && EP);
}





/*##############################################################################
################################################################################
################################################################################
################################################################################
################################################################################
################################################################################
################################################################################
##############################################################################*/





/*******************************************************************************
* void combat(Character)
* Houses the primary combat loop. Brings all other functions together to form
* a combat sequence.
*******************************************************************************/
void combat(Character & player, string newMonster) {

   bool battle = true;
   Character monster(newMonster);
   
   // Temporaries. Don't use these later. display.h changes character objects.
   selectWeapon(player);
   selectArmor(player);
   
   short round = 1,
         option;

   displayStats(player);
   displayStats(monster);

   cout << "A " << monster.name << " draws near!\n" << endl;

   while(battle) {
      
      if(nextAction(player.initiative, monster.initiative, 
                    player.runningInitiative, 
                    monster.runningInitiative) == "Player's") {
         
         /**********************************************************************
         *                     Round Ending Action Block
         * This block is called after all players and monsters have taken at 
         * least 1 action (this is what defines a 'combat round').
         * Actions that occur once per round should be placed here, such as
         * bleeding, resetting defend status, etc.
         **********************************************************************/
         // Apply bleeding
         if(player.isBleeding)
            if(applyBleeding(player))
               break;
         if(monster.isBleeding)
            if(applyBleeding(monster)) {
               combatVictory(player, monster);
               break;
         }

         // Displays player and monster stats for testing.
         displayCharacterStats(player, monster, round++);

         // Reset Stats
         monster.isDefending = false; player.isDefending = false;

         /**********************************************************************
         *                        Player's Action Block
         **********************************************************************/
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
            focus(player);
         }
         else if(option == 3) {
            flee();
         }
      }

      else {
         /**********************************************************************
         *                        Monster's Action Block
         **********************************************************************/
         if(attackCharacter(player, monster)) {        // Returns 1 if defeated
            combatDefeat();
            break;
         }
         
         // Set retaliation against monster attack
         // Set retaliation afliction against monster

         // Set residual actions
      }

      /*************************************************************************
      *                        Residual Action Block
      * The code in this block will be called after ever action by any
      * character (rapid DOT afflictions).
      *************************************************************************/

      
      // Action code goes here.

   }
   player.initiative = 0; monster.initiative = 0;
}
#endif // COMBAT_H
