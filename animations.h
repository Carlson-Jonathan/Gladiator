#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <iostream>
#include <vector>
#include <stdio.h>     // rand()
#include <stdlib.h>    // rand()
#include <time.h>      // rand()
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
// #include <SFML/System.hpp>
// #include <SFML/Network.hpp>
#include "character.h"
using namespace std;


// g++ -c animations.h
// g++ -o a.out animations.h -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network


class Animations {
public:

   Animations                 () {}
   Animations                 (short* screenWidth, short* screenHeight); 

   void animateBattlescape    (sf::RenderWindow & window, bool & go, bool & go2);
   bool eventListener         (sf::RenderWindow & window);
   void setCharacterPositions ();

   vector<Character*> heroParticipants;   
   vector<Character*> monsterParticipants;
   Character* targetCharacter;
   Character* activeCharacter;
   sf::Vector2f activeCharacterPos;
   sf::Vector2f targetCharacterPos;

   bool animationLineup[36] = {
   	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   	0, 0, 0, 0, 0, 0
   };

   short 
      lineupSize = 36,
      lineupIndex = 88,
      selection = 88;

private:

   sf::Event event;
   sf::Clock animationClock;
   sf::Font font;
   sf::Music music;
   sf::Text text;
   sf::FloatRect textRect;

   /************* Battlescape Sprites *************/

   sf::Texture backgroundTex;
   sf::IntRect backgroundRect;
   sf::Sprite backgroundSpr;

   sf::Texture mWheel;
   sf::IntRect menuRect;
   sf::Sprite menuSprite;

   /************* Battlescape Sounds *************/
   sf::SoundBuffer menuTick_b;
   sf::Sound menuTick;


   /**********************************************/

   // '88' means 'no selection made' and is usually default.
   short 
      count = 0,
      wheelRotate = 0,
      menuOption = 1,
      rotation[4] = {0, 90, 180, 270};

   short* pScreenWidth;
   short* pScreenHeight;

   bool animationFinished = true;

   // One-time functions (create sprites)
   void createScapeSprite(string fileName, short x, short y, 
      sf::Texture & texture, sf::IntRect & rectangle, sf::Sprite & sprite);
   void createSound(string filename, sf::SoundBuffer & buffer, sf::Sound & sound);

   // Looped functions
   void MaintainAspectRatio(sf::RenderWindow & window);
   void drawMenuWheel(sf::RenderWindow & window);
   void displayActionText(sf::RenderWindow & window, string message, sf::Vector2f);
   void getNewLineup(bool & go, bool & go2);
   void displayInfoInConsole(); 

   // Ordered animations
   short getLineupIndex();
   void animationSelect(bool & go, bool & go2, sf::RenderWindow & window);
   void animationFatigue(sf::RenderWindow & window);
   void animationDazed(sf::RenderWindow & window);
   void animationHerosTurn(sf::RenderWindow & window);
   void animationDefend(sf::RenderWindow & window);
   void animationRetreat(sf::RenderWindow & window);
   void animationAttack(sf::RenderWindow & window);
   void animationMiss(sf::RenderWindow & window, sf::Vector2f pos);
   void animationApplyDamage(sf::RenderWindow & window, sf::Vector2f pos);
   void animationDeath(sf::RenderWindow & window, sf::Vector2f pos);
   void animationCombatDefeat(sf::RenderWindow & window);
   void animationCombatVictory(sf::RenderWindow & window);
   void animationWounded(sf::RenderWindow & window, sf::Vector2f pos);
   void animationStun(sf::RenderWindow & window, sf::Vector2f pos);
   void animationSlow(sf::RenderWindow & window, sf::Vector2f pos);
   void animationHazardDamage(sf::RenderWindow & window, sf::Vector2f pos);
   void animationRetaliation(sf::RenderWindow & window);
   void animationBleeding(sf::RenderWindow & window);
   void animationRegeneration(sf::RenderWindow & window);
};


/*##############################################################################
################################# Functions ####################################
##############################################################################*/


/*******************************************************************************
* Constructor. All 'create sprite' functions should be included here.
*******************************************************************************/
Animations::Animations(short* screenWidth, short* screenHeight) {
   pScreenWidth = screenWidth;
   pScreenHeight = screenHeight;

   createScapeSprite("Images/meadow.png", 1920, 1080, backgroundTex, 
   	                 backgroundRect, backgroundSpr);

   createScapeSprite("Images/MenuWheel.png", 140, 140, mWheel, menuRect, menuSprite);
   menuSprite.setOrigin(70.f, 70.f);

   // Sounds
   createSound("Sounds/Effects/tick.ogg", menuTick_b, menuTick);

   // Fonts and text
   if(!font.loadFromFile("Fonts/Robusta-Regular.ttf")) 
   	  cout << "Robusta font not found" << endl;
   this->text.setCharacterSize(20);
   this->text.setFont(font);
   this->text.setFillColor(sf::Color::Yellow);
   this->text.setOutlineColor(sf::Color::Black);
   this->text.setOutlineThickness(2);
}

/*******************************************************************************
* bool eventListener(window)
* This is the event listener- detects user interaction with the game.
*******************************************************************************/
bool Animations::eventListener(sf::RenderWindow & window) {

   while (window.pollEvent(event)) {

      // Closes the window/terminates loops if 'X', F4, etc.
      if (event.type == sf::Event::Closed) {
         window.close();
         return 1;
      }

      // Controls
      if(animationFinished) {
         switch(event.key.code) {
            case sf::Keyboard::Left:
      	       animationFinished = false;
               wheelRotate = -6.0f;
               menuTick.play();
               menuOption--;
               if(menuOption < 0) menuOption = 3;
               break;
            case sf::Keyboard::Right:
               animationFinished = false;
               wheelRotate = 6.0f;
               menuTick.play();
               menuOption++;
               if(menuOption > 3) menuOption = 0;
               break;
            case sf::Keyboard::Return:
               selection = menuOption;
               menuOption = 1;
               wheelRotate = 0.0f;
               lineupIndex = 88;
               break;
         }
      }

      // Auto adjusts the screen resolution when dragged. (Partially works)
      if (event.type == sf::Event::Resized) {
         *pScreenWidth = event.size.width;
         *pScreenHeight = event.size.height;
         // cout << "Screen Width: " << event.size.width << endl;
         // cout << "Screen Height: " << event.size.height << endl;         
         sf::FloatRect visibleArea(0, 0, *pScreenWidth, *pScreenHeight);
         window.setView(sf::View(visibleArea));
         MaintainAspectRatio(window);
      }

      // More events...

   }
   return 0;
}

/*******************************************************************************
* animateBattleScape(window, Character*, Character*)
* Public function. This is what battle.h calls to create the entire battlescape
* (background, static characters, misc sprites, etc.) as opposed to the specific
* animations called when an event is triggered (attack, bleed, die, etc.).
*******************************************************************************/
void Animations::animateBattlescape(sf::RenderWindow & window, bool & go, bool & go2) {

   // Background
   window.draw(backgroundSpr);

   // Draw Heroes to screen
   for(auto i : heroParticipants) 
      i->animatedSprite->placeSpriteAnimation(window);

   // Draw monsters to screen
   for(auto i : monsterParticipants) 
      i->animatedSprite->placeSpriteAnimation(window);

   // Draw other animated sprites to screen
   // futureFunction(); 

   // Draw event animations. This must be called LAST in this function!
   animationSelect(go, go2, window);
}

/*******************************************************************************
* void createScapeSprite(texture file, rect dimensions, file, spite obj)
* Creates a sprite object. Should be called only once per sprite per battle.
*******************************************************************************/
void Animations::createScapeSprite(string fileName, short x, short y,
   sf::Texture & texture, sf::IntRect & rectangle, sf::Sprite & sprite) {
   
   if(!texture.loadFromFile(fileName)) cout << "Error loading " << fileName;
   rectangle.width = x;
   rectangle.height = y;
   sprite.setTexture(texture);
   sprite.setTextureRect(rectangle);
}

/*******************************************************************************
* void createSound(string, Soundbuffer, Sound) 
* Creates a sound effect. 
*******************************************************************************/
void Animations::createSound(string filename, sf::SoundBuffer & buffer, 
	                         sf::Sound & sound) {
   if (!buffer.loadFromFile(filename)) 
   	  cout << "Error loading sound: " << filename << endl;
   sound.setBuffer(buffer);
}

/*******************************************************************************
* void setCharacterPositions()
* Sets the position of the current active character to a member variable.
* Origin is automatically adjusted to the center of the sprite.
* Note: this is a potential source of segmentation faults.
*******************************************************************************/
void Animations::setCharacterPositions() {
   this->activeCharacterPos = activeCharacter->animatedSprite->sprite.getPosition();
   this->activeCharacterPos.x += activeCharacter->animatedSprite->rectangle.width / 2;
   this->activeCharacterPos.y += activeCharacter->animatedSprite->rectangle.height / 2;
   this->targetCharacterPos = targetCharacter->animatedSprite->sprite.getPosition();
   this->targetCharacterPos.x += targetCharacter->animatedSprite->rectangle.width / 2;
   this->targetCharacterPos.y += targetCharacter->animatedSprite->rectangle.height / 2;
}

/*******************************************************************************
* MaintainAspectRatio(window)
* An attempt to get the aspect ratio to stay 16:9 when the window is dragged
* and re-sized with the mouse. It kinda works, but not really.
*******************************************************************************/
void Animations::MaintainAspectRatio(sf::RenderWindow & window)
{
        //first we check our new aspect width to see if it changed
        float newAspectWidth = window.getSize().x;
        float newAspectHeight = window.getSize().y;
        float currentAspectWidth = 1333;
        float currentAspectHeight = 750;
        float aspectRatio = 1.7777;

        if(newAspectWidth != currentAspectWidth) {
           //width changed, maintain the aspect ratio and adjust the height
           currentAspectWidth = newAspectWidth;
           currentAspectHeight = currentAspectWidth / aspectRatio;
        }
        else if(newAspectHeight != currentAspectHeight) {
           //height changed, maintain aspect ratio and change the width
           currentAspectHeight = newAspectHeight;
           currentAspectWidth = currentAspectHeight * aspectRatio;
        }

        window.setSize(sf::Vector2u(currentAspectWidth, currentAspectHeight));
}

/*******************************************************************************
* void drawMenuWheel()
* Creates an animated menu wheel. During a hero's turn, this is drawn around
* the hero. On key-press, the menu rotates to change the active action selected.
*******************************************************************************/
void Animations::drawMenuWheel(sf::RenderWindow & window) {
   menuSprite.setPosition(activeCharacterPos);

   if(menuSprite.getRotation() == rotation[menuOption]) {
      wheelRotate = 0.f;
      animationFinished = true;
   }

   menuSprite.rotate(wheelRotate);
   window.draw(menuSprite);
}

/*******************************************************************************
* void getLineupIndex()
* Iterates through the animation lineup array and returns the index of the first
* true boolean. The order of the lineup is the order that the animations get
* displayed, so they must be in the correct order. The parameter represents the
* number of seconds delay before the new index is retrieved.
*******************************************************************************/
short Animations::getLineupIndex() {

   // if(animationClock.getElapsedTime().asSeconds() > seconds && lineupIndex != 3) {

      for(short i = 0; i < lineupSize; i++) {
         if(animationLineup[i]) {
            animationLineup[i] = false;
            return i + 1;
         }
      }

      // animationClock.restart();
   // }
   return 0;
}

/*******************************************************************************
* void displayActionText
* Give it a string and Vector2f position and it will display it to the screen.
*******************************************************************************/
void Animations::displayActionText(sf::RenderWindow & window, string message, 
   sf::Vector2f pos) {
   text.setString(message);
   text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f,
                  text.getLocalBounds().top  + text.getLocalBounds().height / 2.0f);
   text.setPosition(pos);
   window.draw(text);
}

/*******************************************************************************
* void getNewLineup()
* Sends the signals to battle.h to propogate a new turn animation lineup.
*******************************************************************************/
void Animations::getNewLineup(bool & go, bool & go2) {
   cout << "************************** New Combat Turn ****************************" << endl;
   go = true;
   go2 = true;
   lineupIndex = 88; 
}

/*******************************************************************************
* void displayInfoInConsole()
* Used for debugging. Displays the information in the console that is happening
* in the animations.
*******************************************************************************/
void Animations::displayInfoInConsole() {
   cout << "Active character: " << activeCharacter->name << endl;
   cout << "Target character: " << targetCharacter->name << endl;
   cout << "animationLineup:\n";
   for(short i = 0; i < lineupSize; i++)
   	  cout << this->animationLineup[i] << ", ";
   cout << endl;
   cout << "Clock: " << animationClock.getElapsedTime().asSeconds() << endl;
   cout << endl;
}





/*###  ####  ######################################################  ####  #####
#####  ####  ###################                ###################  ####  #####
#####  ####  ##############                          ##############  ####  #####
#####  ####  ###########      Animation Switch Hub      ###########  ####  #####
#####  ####  ##############                          ##############  ####  #####
#####  ####  ###################                ###################  ####  #####
#####  ####  ######################################################  ####  #####

/*******************************************************************************
* void animationSelect()
* Just a switch statement function. Picks which animation to display based on 
* the lineupIndex. The '0' case resets the combat sequence and starts a new turn
*******************************************************************************/
void Animations::animationSelect(bool & go, bool & go2, sf::RenderWindow & window) {

   // Sets a time delay for all animations across the board. Temporary until
   // all animations are created and have their own execution time.
   if(animationClock.getElapsedTime().asSeconds() > 1.0f && lineupIndex != 3) {
      lineupIndex = getLineupIndex();
      animationClock.restart();
   }

   // getLineupIndex(1.0f);

   displayInfoInConsole();

   switch(lineupIndex) {
      case 1:
         animationFatigue(window);
         break;
      case 2:
         animationDazed(window);
         break;            
      case 3:
         animationHerosTurn(window);
         break;
      case 4:
         animationDefend(window);
         break;
      case 5:
         animationRetreat(window);
         break;
      case 6:
         animationAttack(window);
         break;
      case 7:
         animationMiss(window, targetCharacterPos);
         break;
      case 8:
         animationApplyDamage(window, targetCharacterPos);
         break;
      case 9:
         animationDeath(window, targetCharacterPos);
         break;
      case 10:
         animationCombatDefeat(window);
         break;
      case 11:
         animationCombatVictory(window);
         break;   
      case 12:
         animationWounded(window, targetCharacterPos);
         break;  
      case 13:
         animationStun(window, targetCharacterPos);
         break; 
      case 14:
         animationSlow(window, targetCharacterPos);
         break; 
      case 15:
         animationHazardDamage(window, activeCharacterPos);
         break; 
      case 16:
         animationDeath(window, activeCharacterPos);
         break; 
      case 17:
         animationCombatDefeat(window);
         break;     
      case 18:
         animationCombatVictory(window);
         break;
      case 19:
         animationRetaliation(window);
         break;
      case 20:
         animationMiss(window, activeCharacterPos);
         break;
      case 21:
         animationApplyDamage(window, activeCharacterPos);
         break;
      case 22:
         animationDeath(window, activeCharacterPos);
         break;
      case 23:
         animationCombatDefeat(window);
         break;
      case 24:
         animationCombatVictory(window);
         break;
      case 25:
         animationWounded(window, activeCharacterPos);
         break;
      case 26:
         animationStun(window, activeCharacterPos);
         break;
      case 27:
         animationSlow(window, activeCharacterPos);
         break;
      case 28:
         animationHazardDamage(window, targetCharacterPos);
         break; 
      case 29:
         animationDeath(window, targetCharacterPos);
         break; 
      case 30:
         animationCombatDefeat(window);
         break; 
      case 31:
         animationCombatVictory(window);
         break; 
      case 32:
         animationBleeding(window);
         break;  
      case 33:
         animationDeath(window, activeCharacterPos); // Bleed death- needs Active/Target character
         break;  
      case 34:
         animationCombatDefeat(window); 
         break;  
      case 35:
         animationCombatVictory(window);
         break;  
      case 36:
         animationRegeneration(window);
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

void Animations::animationCombatDefeat(sf::RenderWindow & window) {
   cout << "\t*** Your party is wiped! You are defeated! ***\n";
}

void Animations::animationCombatVictory(sf::RenderWindow & window) {
   cout << "\t*** All enemies are dead! You are victorious! ***\n";
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

#endif // ANIMATIONS_H