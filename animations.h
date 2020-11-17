#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>     // rand()
#include <stdlib.h>    // rand()
#include <time.h>      // rand()
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "character.h"
using namespace std;


// g++ -c animations.h
// g++ -o a.out animations.h -lsfml-graphics -lsfml-window -lsfml-audio


class Animations {
public:

   Animations                 () {}
   ~Animations 				  () { cout << "Animations object is destroyed!\n"; }
   Animations                 (short* screenWidth, short* screenHeight); 

   void animateBattlescape    (sf::RenderWindow & window, bool & go, bool & go2);
   bool eventListener         (sf::RenderWindow & window);
   void setCharacterPositions ();
   void deleteCharacterObjects();

   vector<Character*> heroParticipants;   
   vector<Character*> monsterParticipants;
   Character* targetCharacter;
   Character* activeCharacter;
   sf::Vector2f activeCharacterPos;
   sf::Vector2f targetCharacterPos;

   // Order is unimportant since maps auto-sort by key.
   map<string, bool> animationLineup = {
      {"fatigue",		0},
      {"dazed", 		0},
      {"heroesTurn",	0},
      {"defend",		0},
      {"flee",			0},
      {"attack",		0},
      {"missed1",		0},
      {"applyDamage1",	0}, 
      {"charDead1",		0},
      {"combatDefeat1",	0},
      {"combatVictory1",0},
      {"setBleeding1",	0},
      {"stun1",			0},
      {"slow1",			0},
      {"hazardDamage1",	0},
      {"charDead2",		0},
      {"combatDefeat2",	0},
      {"combatVictory2",0},
      {"retaliation",	0},
      {"missed2",		0},
      {"applyDamage2",	0},
      {"charDead3",		0},
      {"combatDefeat3",	0},
      {"combatVictory3",0},
      {"setBleeding2",	0},
      {"stun2",			0},
      {"slow2",			0},
      {"hazardDamage2",	0},
      {"charDead4",		0},
      {"combatDefeat4",	0},
      {"combatVictory4",0},
      {"applyBleed",	0},
      {"charDead5",		0},
      {"combatDefeat5",	0},
      {"combatVictory5",0},
      {"regeneration",	0},
      {"stopSprites1",	0},
      {"stopSprites2",	0},
      {"stopSprites3",	0},
      {"stopSprites4",	0},
      {"stopSprites5",	0}
   };

   // Since maps auto-sort by key value, this vector is needed to preserve the
   // execution order of the animation lineup.
   vector<string> lineupOrder = {
      "fatigue", 		// 1
      "dazed", 			// 2
      "heroesTurn",		// 3
      "defend",			// 4
      "flee",			// 5
      "attack",			// 6
      "missed1",		// 7
      "applyDamage1",	// 8
      "charDead1",		// 9
      "stopSprites1",	// 10
      "combatDefeat1",	// 11
      "combatVictory1", // 12
      "setBleeding1",	// 13
      "stun1",			// 14
      "slow1",			// 15
      "hazardDamage1",	// 16
      "charDead2",		// 17
      "stopSprites2",	// 18     
      "combatDefeat2",	// 19
      "combatVictory2", // 20
      "retaliation",	// 21
      "missed2",		// 22
      "applyDamage2",	// 23
      "charDead3",		// 24
      "stopSprites3",	// 25     
      "combatDefeat3",	// 26
      "combatVictory3", // 27
      "setBleeding2",	// 28
      "stun2",			// 29
      "slow2",			// 30
      "hazardDamage2",	// 31
      "charDead4",		// 32
      "stopSprites4",	// 33     
      "combatDefeat4",	// 34
      "combatVictory4", // 35
      "applyBleed",		// 36
      "charDead5",		// 37
      "stopSprites5",	// 38   
      "combatDefeat5",	// 39
      "combatVictory5",	// 40
      "regeneration"	// 41
   };

   short 
      lineupSize = lineupOrder.size(),
      lineupIndex = 88,
      selection = 88;

   sf::Clock animationClock;

private:

   sf::Event event;
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

   bool keyHasBeenReleased = true;

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
   void drawTargetWheel();

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
   void stopCharacterSprites();
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
      if(keyHasBeenReleased) {
         switch(event.key.code) {
            case sf::Keyboard::Left:
      	       keyHasBeenReleased = false;
               wheelRotate = -6.0f;
               menuTick.play();
               menuOption--;
               if(menuOption < 1) menuOption = 4;
               break;
            case sf::Keyboard::Right:
               keyHasBeenReleased = false;
               wheelRotate = 6.0f;
               menuTick.play();
               menuOption++;
               if(menuOption > 4) menuOption = 1;
               break;
            case sf::Keyboard::Return:
               keyHasBeenReleased = false;
               selection = menuOption;
               menuOption = 1;
               menuSprite.setRotation(0.0f);
               lineupIndex = 88;
               break;
         }
      }

      if(event.type == sf::Event::KeyReleased) 
      	 keyHasBeenReleased = true;

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

   if(menuSprite.getRotation() == rotation[menuOption - 1]) 
      wheelRotate = 0.f;

   menuSprite.rotate(wheelRotate);
   window.draw(menuSprite);
}

/*******************************************************************************
* void drawTargetWheel()
* Creates an animated menu wheel. If there are more than 1 monster, after making
* a selection on the menu wheel, the target wheel will appear over a monster,
* which the character will be able to move and make the target selection.
*******************************************************************************/
void Animations::drawTargetWheel() {
   short highlightTarget;
   // Create targeting sprite
   // Create an animation lineup occurence for this function.
   // draw targeting sprite at monsterParticipants[highlightTarget]->animatedSprite.sprite.getPosition()
   // Set left/right, up/down arrow keys to increment/decrement higlightedTarget.
   // Enter key saves highligtedTarget to 'selection' variable.
   // battle.h checks for a selection variable that != 88 to continue.
   // battle.h sets target to monsterParticipants[selection - 1].
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
         if(animationLineup[lineupOrder[i]]) {
            animationLineup[lineupOrder[i]] = false;
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
   // cout << "Active character: " << activeCharacter->name << endl;
   // cout << "Target character: " << targetCharacter->name << endl;
   // cout << "animationLineup:\n";
   // for(short i = 0; i < lineupSize; i++)
   // 	  cout << this->animationLineup[lineupOrder[i]] << ", ";
   // cout << "lineupIndex = " << lineupIndex << endl;
   // cout << endl;
   // cout << "Clock: " << animationClock.getElapsedTime().asSeconds() << endl;
   // cout << endl;
}

/*******************************************************************************
* void deleteCharacterObjects()
* Garbage collections. 
*******************************************************************************/
void Animations::deleteCharacterObjects() {
   for(auto i : monsterParticipants) {
   	  delete i->animatedSprite;
   	  delete i->weapon;
   	  delete i->armor;
      delete i;
   }

   for(auto i : heroParticipants) {
   	  if(i->isDead) {
   	     delete i->animatedSprite;
   	     delete i->weapon;
   	     delete i->armor;
   	     delete i;
   	  }
   }
}


#include "combatEventAnimations.cpp"

#endif // ANIMATIONS_H