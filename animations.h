#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "character.h"
using namespace std;


// g++ -c animations.h
// g++ -o a.out animations.h -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network


class Animations {
public:
   Animations() {}
   Animations(short* screenWidth, short* screenHeight); 
   void animateBattlescape(sf::RenderWindow & window, 
   vector<Character*> & heroParticipants, 
   vector<Character*> & monsterParticipants, bool (&animationLineup)[36], 
   bool & go);
   bool eventListener(sf::RenderWindow & window);

private:
   sf::Clock animationClock;
   sf::FloatRect textRect;
   sf::Font font;
   sf::Music music;
   sf::Text text;

   sf::Texture mWheel;
   sf::Texture backgroundTex;

   sf::IntRect menuRect;
   sf::IntRect backgroundRect;

   sf::Sprite menuSprite;
   sf::Sprite backgroundSpr;

   float a = 0, b = 0;

   short 
      x = 0.f,
      y = 0.f,
      count = 0,
      lineupIndex = 88;

   short* pScreenWidth;
   short* pScreenHeight;

   // One-time functions (create sprites)
   void createBackground();
   void createMenuWheel();

   // Looped functions
   void drawBackground(sf::RenderWindow & window);
   void MaintainAspectRatio(sf::RenderWindow & window);
   void drawMenuWheel(sf::RenderWindow & window);

   // Ordered animations
   short getLineupIndex(bool animationLineup[], short size);
   void animationSelect(bool (&animationLineup)[36], bool & go, sf::RenderWindow & window);
   void animationFatigue();
   void animationDazed();
   void animationHerosTurn(sf::RenderWindow & window);
   void animationDefend();
   void animationRetreat();
   void animationAttack();
   void animationMiss();
   void animationApplyDamage();
   void animationDeath();
   void animationCombatDefeat();
   void animationCombatVictory();
   void animationWounded();
   void animationStun();
   void animationSlow();
   void animationHazardDamage();
   void animationRetaliation();
   void animationBleeding();
   void animationRegeneration();

};




/*******************************************************************************
* Constructor. All the 'create sprite' functions should be included here.
*******************************************************************************/
Animations::Animations(short* screenWidth, short* screenHeight) {
   pScreenWidth = screenWidth;
   pScreenHeight = screenHeight;
   createBackground();
   createMenuWheel();
}

/*******************************************************************************
* bool eventListener(window)
* This is the event listener- detects user interaction with the game.
*******************************************************************************/
bool Animations::eventListener(sf::RenderWindow & window) {
   sf::Event event;

   // Closes the window and terminates loops if the 'X' is clicked or alt + F4.
   while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
         window.close();
         return 1;
      }

      // Auto adjusts the game resolution when the screen size is dragged.
      // This will likely need to be fixed- does not work as needed.
      if (event.type == sf::Event::Resized) {
         *pScreenWidth = event.size.width;
         *pScreenHeight = event.size.height;
         cout << "Screen Width: " << event.size.width << endl;
         cout << "Screen Height: " << event.size.height << endl;         
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
void Animations::animateBattlescape(sf::RenderWindow & window, 
   vector<Character*> & heroParticipants, 
   vector<Character*> & monsterParticipants, bool (&animationLineup)[36], 
   bool & go) {

   // eventListener(window);
   drawBackground(window);
   for(auto i : monsterParticipants) {
      i->animatedSprite->sprite.setPosition(sf::Vector2f(1000.f, 500.f));
      i->animatedSprite->placeSpriteAnimation(window);
   }
   animationSelect(animationLineup, go, window);
}

/*******************************************************************************
* void createBackground()
* Creates the battlescape background sprite.
*******************************************************************************/
void Animations::createBackground() {
   if(!backgroundTex.loadFromFile("Images/BackgroundPineforest.png")) 
      cout << "Error loading Images/dragon.png";
   sf::IntRect backgroundRect(0, 0, 1920, 1080);
   this->backgroundRect = backgroundRect;
   backgroundSpr.setTexture(backgroundTex);
   backgroundSpr.setTextureRect(backgroundRect);
}

/*******************************************************************************
* void createMenuWheel()
* Creates the menu wheel sprite (character options menu).
*******************************************************************************/
void Animations::createMenuWheel() {
   if(!mWheel.loadFromFile("Images/MenuWheel.png")) 
      cout << "unable to load image 'MenuWheel.png'" << endl;
   sf::IntRect menuRect(0, 0, 140, 140);
   this->menuRect = menuRect;
   menuSprite.setTexture(mWheel);
   menuSprite.setTextureRect(menuRect);
   menuSprite.setOrigin(70.f, 70.f);
}


/*##############################################################################
############################## Looped Functions ################################
##############################################################################*/


/*******************************************************************************
* Function stubs for the different animations.
*******************************************************************************/
void Animations::drawBackground(sf::RenderWindow & window) {
   window.draw(backgroundSpr);
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

        if(newAspectWidth != currentAspectWidth)
        {
                //width changed, maintain the aspect ratio and adjust the height
                currentAspectWidth = newAspectWidth;
                currentAspectHeight = currentAspectWidth / aspectRatio;
        }
        else if(newAspectHeight != currentAspectHeight)
        {
                //height changed, maintain aspect ratio and change the width
                currentAspectHeight = newAspectHeight;
                currentAspectWidth = currentAspectHeight * aspectRatio;
        }
        std::cout << "width: " << currentAspectWidth << " height: " << currentAspectHeight;
        window.setSize(sf::Vector2u(currentAspectWidth, currentAspectHeight));
}

/*******************************************************************************
* void drawMenuWheel()
* Creates an animated menu wheel. During a hero's turn, this is drawn around
* the hero. On key-press, the menu rotates to change the active action selected.
*******************************************************************************/
void Animations::drawMenuWheel(sf::RenderWindow & window) {
   menuSprite.setPosition(sf::Vector2f(*pScreenWidth / 2 - 70, *pScreenHeight / 2 - 70));
   window.draw(menuSprite);
   menuSprite.rotate(-2.f);
}



/*##############################################################################
############################## Combat Animations ###############################
##############################################################################*/

/*******************************************************************************
* void getLineupIndex()
* Iterates through the animation lineup array and returns the index of the frist
* true boolean.
*******************************************************************************/
short Animations::getLineupIndex(bool animationLineup[], short size) {
   for(short i = 0; i < size; i++) {
      if(animationLineup[i]) {
         animationLineup[i] = false;
         return i + 1;
      }
   }
   return 0;
}

/*******************************************************************************
* void animationSelect()
* Just a switch statement function. Picks which animation to display based on 
* the lineupIndex. The '0' case resets the combat sequence and starts a new turn
*******************************************************************************/
void Animations::animationSelect(bool (&animationLineup)[36], bool & go, sf::RenderWindow & window) {

   short size = sizeof(animationLineup);
   if(animationClock.getElapsedTime().asSeconds() > 3.0f) {
      lineupIndex = getLineupIndex(animationLineup, size);
      animationClock.restart();
   }

   switch(lineupIndex) {
      case 1:
         animationFatigue();
         break;
      case 2:
         animationDazed();
         break;            
      case 3:
         animationHerosTurn(window);
         break;
      case 4:
         animationDefend();
         break;
      case 5:
         animationRetreat();
         break;
      case 6:
         animationAttack();
         break;
      case 7:
         animationMiss();
         break;
      case 8:
         animationApplyDamage();
         break;
      case 9:
         animationDeath();
         break;
      case 10:
         animationCombatDefeat();
         break;
      case 11:
         animationCombatVictory();
         break;   
      case 12:
         animationWounded();
         break;  
      case 13:
         animationStun();
         break; 
      case 14:
         animationSlow();
         break; 
      case 15:
         animationHazardDamage();
         break; 
      case 16:
         animationDeath();
         break; 
      case 17:
         animationCombatDefeat();
         break;     
      case 18:
         animationCombatVictory();
         break;
      case 19:
         animationRetaliation();
         break;
      case 20:
         animationMiss();
         break;
      case 21:
         animationApplyDamage();
         break;
      case 22:
         animationDeath();
         break;
      case 23:
         animationCombatDefeat();
         break;
      case 24:
         animationCombatVictory();
         break;
      case 25:
         animationWounded();
         break;
      case 26:
         animationStun();
         break;
      case 27:
         animationSlow();
         break;
      case 28:
         animationHazardDamage();
         break; 
      case 29:
         animationDeath();
         break; 
      case 30:
         animationCombatDefeat();
         break; 
      case 31:
         animationCombatVictory();
         break; 
      case 32:
         animationBleeding();
         break;  
      case 33:
         animationDeath();
         break;  
      case 34:
         animationCombatDefeat();
         break;  
      case 35:
         animationCombatVictory();
         break;  
      case 36:
         animationRegeneration();
        break; 
      case 0:
         cout << "************************** New Combat Turn ****************************" << endl;
         go = true;
         lineupIndex = 88;
         for(bool & i : animationLineup)
            i = 0;
         break;
      default:;
   }
}



/*******************************************************************************
* Ordered animation functions.
*******************************************************************************/
void Animations::animationFatigue() {
   cout << "\t*** Fatigue Animation ***\n";
}

void Animations::animationDazed() {
   cout << "\t*** Dazed Animation ***\n";
}

void Animations::animationHerosTurn(sf::RenderWindow & window) {
   drawMenuWheel(window);
   cout << "\t*** Display Hero stats ***\n";
   cout << "\t*** Who's turn arrow ***\n";
   cout << "\t*** Listen for user input ***\n";
   cout << "\t*** Select Monster/menu options ***\n";
}

void Animations::animationDefend() {
   cout << "\t*** Character defending animation ***\n";
}

void Animations::animationRetreat() {
   cout << "\t*** Character is running away ***\n";
}

void Animations::animationAttack() {
   cout << "\t*** Character executes a primary attack ***\n";
}

void Animations::animationMiss() {
   cout << "\t*** Character's attack misses the target ***\n";
}

void Animations::animationApplyDamage() {
   cout << "\t*** Damage numbers appear over victim ***\n";
}

void Animations::animationDeath() {
   cout << "\t*** This character has died! ***\n";
}

void Animations::animationCombatDefeat() {
   cout << "\t*** Your party is wiped! You are defeated! ***\n";
}

void Animations::animationCombatVictory() {
   cout << "\t*** All enemies are dead! You are victorious! ***\n";
}

void Animations::animationWounded() {
   cout << "\t*** This character is wounded and will bleed each turn. ***\n";
}

void Animations::animationStun() {
   cout << "\t*** This character is stunned (running initiative +) ***\n";
}

void Animations::animationSlow() {
   cout << "\t*** This character is stunned (initiative -) ***\n";
}

void Animations::animationHazardDamage() {
   cout << "\t*** Hazard damage taken for kicking a cactus ***\n";
}

void Animations::animationRetaliation() {
   cout << "\t*** Character recoils and strikes back ***\n";
}

void Animations::animationBleeding() {
   cout << "\t*** Bleeding damage is applied to this character ***\n";
}

void Animations::animationRegeneration() {
   cout << "\t*** Character is regenerating blood points ***\n";
}

#endif // ANIMATIONS_H