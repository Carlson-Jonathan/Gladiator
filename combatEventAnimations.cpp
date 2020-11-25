/*******************************************************************************
* void animationSelect()
* Just a switch statement function. Picks which animation to display based on 
* the lineupIndex. The '0' case resets the combat sequence and starts a new turn
*******************************************************************************/
void Animations::animationSelect(bool & go, bool & go2, sf::RenderWindow & window) {

   if(lineupIndex == 88) { 
   	  lineupIndex = getLineupIndex();
   	  animationClock.restart();
   }

   switch(lineupIndex) {
      case 1:
         animationFatigue(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 2:
         animationDazed(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;            
      case 3:
         animationHerosTurn(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 4:
         drawTargetWheel(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 5:
         animationDefend(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 6:
         animationRetreat(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 7:
         animationAttack(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 8:
         animationMiss(window, targetCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 9:
         animationApplyDamage(window, targetCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 10:
         animationDeath(window, targetCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 11:
         stopCharacterSprites();
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;   
      case 12:
         animationCombatDefeat(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 13:
         animationCombatVictory(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;   
      case 14:
         animationWounded(window, targetCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;  
      case 15:
         animationStun(window, targetCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break; 
      case 16:
         animationSlow(window, targetCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break; 
      case 17:
         animationHazardDamage(window, activeCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break; 
      case 18:
         animationDeath(window, activeCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break; 
      case 19:
         stopCharacterSprites();
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 20:
         animationCombatDefeat(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;     
      case 21:
         animationCombatVictory(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 22:
         animationRetaliation(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 23:
         animationMiss(window, activeCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 24:
         animationApplyDamage(window, activeCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 25:
         animationDeath(window, activeCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 26:
         stopCharacterSprites();
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;         
      case 27:
         animationCombatDefeat(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 28:
         animationCombatVictory(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 29:
         animationWounded(window, activeCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 30:
         animationStun(window, activeCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 31:
         animationSlow(window, activeCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;
      case 32:
         animationHazardDamage(window, targetCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break; 
      case 33:
         animationDeath(window, targetCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break; 
      case 34:
         stopCharacterSprites();
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;         
      case 35:
         animationCombatDefeat(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break; 
      case 36:
         animationCombatVictory(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break; 
      case 37:
         animationBleeding(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;  
      case 38:
         animationDeath(window, activeCharacterPos);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }          
         break;
      case 39:
         stopCharacterSprites();
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;           
      case 40:
         animationCombatDefeat(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }          
         break;  
      case 41:
         animationCombatVictory(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break;  
      case 42:
         animationRegeneration(window);
         if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
            lineupIndex = getLineupIndex();
            animationClock.restart();
         }         
         break; 
      case 0:
         getNewLineup(go, go2);
         break;
      default:;
   }
}

/*******************************************************************************
* Ordered animation functions.
*******************************************************************************/
void Animations::animationFatigue(sf::RenderWindow & window) {
   cout << "\t*** Fatigue Animation ***\n";
   displayActionText(window, "Fatigued!", activeCharacterPos);
}

void Animations::animationDazed(sf::RenderWindow & window) {
   cout << "\t*** Dazed Animation ***\n";
   displayActionText(window, "Dazed!", activeCharacterPos);
}

void Animations::animationHerosTurn(sf::RenderWindow & window) {
   drawMenuWheel(window);
   drawTargetWheel(window);
   cout << "\t*** Select Monster/menu options ***\n";
}

void Animations::animationDefend(sf::RenderWindow & window) {
   cout << "\t*** Character defending animation ***\n";
   displayActionText(window, "Defending", activeCharacterPos);
}

void Animations::animationRetreat(sf::RenderWindow & window) {
   cout << "\t*** Character is running away ***\n";
   displayActionText(window, "Retreat!", activeCharacterPos);
}

void Animations::animationAttack(sf::RenderWindow & window) {
   cout << "\t*** Character executes a primary attack ***\n";
   displayActionText(window, "Attack Animation", activeCharacterPos);
}

void Animations::animationMiss(sf::RenderWindow & window, sf::Vector2f pos) {
   cout << "\t*** Character's attack misses the target ***\n";
   displayActionText(window, "Missed!", pos);
}

void Animations::animationApplyDamage(sf::RenderWindow & window, sf::Vector2f pos) {
   cout << "\t*** Damage numbers appear over victim ***\n";
   displayActionText(window, "Damage Numbers", pos);
}

void Animations::animationDeath(sf::RenderWindow & window, sf::Vector2f pos) {
   cout << "\t*** This character has died! ***\n";
   displayActionText(window, "D E A D ! ! !", pos);
}

void Animations::stopCharacterSprites() {
   cout << "\t*** Character animation dissapears ***\n";
   for(short i = heroParticipants.size() - 1; i >= 0; i--) {
      if(heroParticipants[i]->isDead) {
         heroParticipants[i] = NULL;
         heroParticipants.erase(heroParticipants.begin() + i);      	
      }
   }

   for(short i = monsterParticipants.size() - 1; i >= 0; i--) {
      if(monsterParticipants[i]->isDead) {
         monsterParticipants[i] = NULL;
         monsterParticipants.erase(monsterParticipants.begin() + (i));
      }
   }
}

void Animations::animationCombatDefeat(sf::RenderWindow & window) {
   cout << "\t*** Your party is wiped! You are defeated! ***\n";
   deleteCharacterObjects();
}

void Animations::animationCombatVictory(sf::RenderWindow & window) {
   cout << "\t*** All enemies are dead! You are victorious! ***\n";
   deleteCharacterObjects();
}

void Animations::animationWounded(sf::RenderWindow & window, sf::Vector2f pos) {
   cout << "\t*** This character is wounded and will bleed each turn. ***\n";
   displayActionText(window, "Wounded!", pos);
}

void Animations::animationStun(sf::RenderWindow & window, sf::Vector2f pos) {
   cout << "\t*** This character is stunned (running initiative +) ***\n";
   displayActionText(window, "Stunned!", pos);
}

void Animations::animationSlow(sf::RenderWindow & window, sf::Vector2f pos) {
   cout << "\t*** This character is slowed (initiative -) ***\n";
   displayActionText(window, "Slowed!", pos);
}

void Animations::animationHazardDamage(sf::RenderWindow & window, sf::Vector2f pos) {
   cout << "\t*** Hazard damage taken for kicking a cactus ***\n";
   displayActionText(window, "Hazard Damage!", pos);
}

void Animations::animationRetaliation(sf::RenderWindow & window) {
   cout << "\t*** Character recoils and strikes back ***\n";
   displayActionText(window, "Retaliation Attack!", targetCharacterPos);
}

void Animations::animationBleeding(sf::RenderWindow & window) {
   cout << "\t*** Bleeding damage is applied to this character ***\n";
   for(auto i : monsterParticipants) {
      if(i->isBleeding) {
         sf::Vector2f pos = i->animatedSprite->sprite.getPosition();
         short sprWidth = i->animatedSprite->rectangle.width;
         short sprHeight = i->animatedSprite->rectangle.height;
         pos.x += sprWidth / 2;
         pos.y += sprHeight / 2;
         displayActionText(window, "Bleed Damage", pos);
      }
   }

   for(auto i : heroParticipants) {
      if(i->isBleeding) {
         sf::Vector2f pos = i->animatedSprite->sprite.getPosition();
         short sprWidth = i->animatedSprite->rectangle.width;
         short sprHeight = i->animatedSprite->rectangle.height;
         pos.x += sprWidth / 2;
         pos.y += sprHeight / 2;
         displayActionText(window, "Bleed Damage", pos);
      }
   }
}

void Animations::animationRegeneration(sf::RenderWindow & window) {
   cout << "\t*** Character is regenerating blood points ***\n";
   for(auto i : monsterParticipants) {
      if(i->regeneration) {
         sf::Vector2f pos = i->animatedSprite->sprite.getPosition();
         short sprWidth = i->animatedSprite->rectangle.width;
         short sprHeight = i->animatedSprite->rectangle.height;
         pos.x += sprWidth / 2;
         pos.y += sprHeight / 2;
         displayActionText(window, "Regeneration", pos);
      }
   }

   for(auto i : heroParticipants) {
      if(i->regeneration) {
         sf::Vector2f pos = i->animatedSprite->sprite.getPosition();
         short sprWidth = i->animatedSprite->rectangle.width;
         short sprHeight = i->animatedSprite->rectangle.height;
         pos.x += sprWidth / 2;
         pos.y += sprHeight / 2;
         displayActionText(window, "Regeneration", pos);
      }
   }
}