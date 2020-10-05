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
void getDamageSum(short damageTypes[], short block[]);
void getPhysicalDamages(Character, Character);
void convertToHP_BP(const Character & victim, short rawDamage[], short dT[]);
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

   cout << "\t\t\tPlayer/Monster Initiatives: " << rpSlow << " | " << rmSlow << "\n\n";
   if(rpSlow <= rmSlow) {
       rpSlow += pSlow;
       return "Player's";
   }

   rmSlow += mSlow;
   return "Monster's";
}

/*******************************************************************************
* void getDamageSum(short, short[])
* Applies the damage reduction of the armor assuring that it does not go below 
* 0. The formula applied is to reduce each damage type by the block damage
* type as a percentage.
*******************************************************************************/
void getDamageSum(short damageTypes[], short block[]) {
   for(short i = 0; i < 4; i++) {
      damageTypes[i] *= (1.0 - ((float)block[i] / 100));
      if(damageTypes[i] < 0)
         damageTypes[i] = 0;
   }
}

/*******************************************************************************
* void getPhysicalDamages(Character, Character, short[])
* Gets the damage types generated by the aggressor's weapon, gets the defence
* values generated by the victim's armor, sums them, converts them to HP/BP/EP,
* and sets them to the address of a short[]; 
*******************************************************************************/
void getPhysicalDamages(Character & victim, Character & aggressor, short damageHpBpEp[]) {

   aggressor.weapon->getRandomDamageTypes();
   cout << "\t\t\t" << aggressor.name << " damage Types:" << endl;
   cout << "\t\t\t" << "Cr: " << aggressor.weapon->damageTypes[0] << " | Ch: " 
        << aggressor.weapon->damageTypes[1]  << " | Sl: " 
        << aggressor.weapon->damageTypes[2]  << " | St: " 
        << aggressor.weapon->damageTypes [3] << "\n\n";

   cout << "\t\t\t" << victim.name << " armor block values based on defence power: " 
        << victim.armor->defencePower << endl;
   cout << "\t\t\tCrush: " << victim.armor->damageReduce[0] 
        <<    " | Chop: "  << victim.armor->damageReduce[1] 
        <<    " | Slash: " << victim.armor->damageReduce[2] 
        <<    " | Stab: "  << victim.armor->damageReduce[3] << "\n\n";

   getDamageSum(aggressor.weapon->damageTypes, victim.armor->damageReduce);
   cout << "\t\t\t" << aggressor.name << " modified Damage Types:" << endl;
   cout << "\t\t\tCr: " << aggressor.weapon->damageTypes[0] << " | Ch: " 
        << aggressor.weapon->damageTypes[1] << " | Sl: " << aggressor.weapon->damageTypes[2] 
        << " | St: " << aggressor.weapon->damageTypes [3] << "\n\n";

   convertToHP_BP(victim, damageHpBpEp, aggressor.weapon->damageTypes);
   cout << "\t\t\t" << "Raw Damage using modified types:" << endl;
   cout << "\t\t\tHP: " << damageHpBpEp[0] << " | BP: " << damageHpBpEp[1] << " | EP: " << damageHpBpEp[2] << "\n\n";
}

/*******************************************************************************
* void convertToHP_BP(Character, int, short[])
* Accepts either the Hero or Monster type objects and uses the weapon object
* set in that type to determine the amount of damage that will be inflicted
* per combat round. Basically it splits the 4 damage types into 3 health types.
*******************************************************************************/
void convertToHP_BP(const Character & victim, short rawDamage[], short dT[]) {

       // dT[0] = Crush, dT[1] = Chop, dT[2] = Slash, dT[3] = Stab            
   rawDamage[0] = dT[0] + ceil(dT[2] * 0.34) + ceil(dT[1] * 0.66),   // HP
   rawDamage[1] = dT[3] + ceil(dT[2] * 0.66) + ceil(dT[1] * 0.34),   // BP
   rawDamage[2] = 0;                                                 // EP

   if(victim.isDefending) {
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
      if(wep->isSharp) {
         victim.isBleeding += ceil(damageTypes[3] * 0.2 + damageTypes[2] * 0.1) * 10;
         // cout << victim.name << " begins hemorrhaging from their wound!" << "\n\n";
      }
      
      // Sets a stun affliction (skips the victim's next turn).
      if(wep->canStun)
         if(damageTypes[0] > aggressor.weapon->minDamage + 
            aggressor.weapon->rangeDamage / 2) {    // Damge > than 50% of potential
            stunMessage(aggressor, victim);
            victim.runningInitiative += wep->canStun;
         }

      if(wep->venomous) {
         victim.initiative += wep->venomous;   
         cout << victim.name << "'s movement is slowed by the " << aggressor.name 
              << "'s attack!\n\n";
         cout << "\t\t\t" << victim.name << "'s base initiative: " << victim.initiative << "\n\n";
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

/*******************************************************************************
* bool receiveHazardDamage(Character, Character, short[])
* Calculates and applies reflective damage.
*******************************************************************************/
bool receiveHazardDamage(Character & aggressor, const Character & victim, short (&damageHpBpEp)[3]) {
    for(auto &i : damageHpBpEp)
        i /= victim.isHazardous;

    hazardDamageMessage(aggressor, damageHpBpEp);
    if(applyDamage(aggressor, damageHpBpEp)) return true;

    return false;
}

bool attackCharacter(Character & aggressor, Character & victim, short (&damageHpBpEp)[3]) {
    getPhysicalDamages(victim, aggressor, damageHpBpEp);
    displayAttackMessage(victim, aggressor, damageHpBpEp);
    if(applyDamage(victim, damageHpBpEp)) return true;
    determineAffliction(aggressor, victim, aggressor.weapon->damageTypes);

    if(victim.isHazardous) 
        receiveHazardDamage(aggressor, victim, damageHpBpEp);

    return false;
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
         option,
         damageHpBpEp[3];


   displayStats(player);
   displayStats(monster);

   cout << "\tA " << monster.name << " draws near!\n" << endl;

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
             if(attackCharacter(player, monster, damageHpBpEp)) {
                 combatVictory(player, monster);
                 break;
             }
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
         if(attackCharacter(monster, player, damageHpBpEp)) {
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
