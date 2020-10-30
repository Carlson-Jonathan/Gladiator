#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
using namespace std;


// g++ -c animations.h
// g++ -o a.out animations.h -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network


class Animations {

private:
   sf::Clock clock;
   sf::FloatRect textRect;
   sf::Font font;
   sf::Music music;
   sf::Text text;

   sf::Texture dragonTexture;
   sf::Sprite dragon;
   sf::IntRect dragonRect;

   sf::Texture backgroundTex;
   sf::Sprite backgroundSpr;
   sf::IntRect backgroundRect;

   float a = 0, b = 0;

   short 
      x = 0.f,
      y = 0.f,
      count = 0;

   short* pScreenWidth;
   short* pScreenHeight;

public:

   Animations() {}
   Animations(short* screenWidth, short* screenHeight); 

   // Looped functions
   void flyingDragon(sf::RenderWindow & window);
   bool eventListener(sf::RenderWindow & window);
   void drawBackground(sf::RenderWindow & window);


   // One-time functions
   void createDragon();
   void createBackground();
};

/*******************************************************************************
* Prototypes
*******************************************************************************/
Animations::Animations(short* screenWidth, short* screenHeight) {
   pScreenWidth = screenWidth;
   pScreenHeight = screenHeight;
   createDragon();
   createBackground();
}

/*******************************************************************************
* void flyingDragon()
* Animates dragon
*******************************************************************************/
void Animations::flyingDragon(sf::RenderWindow & window) {
   // cout << count << endl;
   count++;


   dragon.setPosition(sf::Vector2f(x, y));
   window.draw(dragon);

   // Dragon flaps its wings
   if(clock.getElapsedTime().asSeconds() > 0.2f) {
      if(dragonRect.left == 382) 
         dragonRect.left = 0;
      else
         dragonRect.left += 191;

      dragon.setTextureRect(dragonRect);
      clock.restart();
   }

   // Dragon changes direction and faces direction flying
   if(x >= *pScreenWidth - 191) {a = -4; dragonRect.top = 483;}
   if(x <= 0) {a = 4; dragonRect.top = 161;}
   if(y >= *pScreenHeight - 161) {b = -2; dragonRect.top = 0;}
   if(y <= 0) {b = 2; dragonRect.top = 322;}
   x += a; y += b;
}

bool Animations::eventListener(sf::RenderWindow & window) {
   sf::Event event;

   // Closes the window and terminates loops if the 'X' is clicked or alt + F4.
   while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
         window.close();
         return 1;
      }

      // Auto adjusts the game resolution when the screen size is dragged.
      if (event.type == sf::Event::Resized) {
         *pScreenWidth = event.size.width;
         *pScreenHeight = event.size.height;
         sf::FloatRect visibleArea(0, 0, *pScreenWidth, *pScreenHeight);
         window.setView(sf::View(visibleArea));
         // createBackground();
      }

      // More events...

   }
   return 0;
}

void Animations::createDragon() {
   if(!dragonTexture.loadFromFile("Images/dragon.png")) cout << "Error loading Images/dragon.png";  // Load texture file
   sf::IntRect dragonRect(0, 161, 191, 161);														// Set rectangle size
   this->dragonRect = dragonRect;																	// Set to member variable
   dragon.setTexture(dragonTexture);																// Give sprite the texture
   dragon.setTextureRect(dragonRect);																// Set the size/shape of sprite
}

void Animations::createBackground() {
   if(!backgroundTex.loadFromFile("Images/sampleLandscape.jpg")) cout << "Error loading Images/dragon.png";
   sf::IntRect backgroundRect(0, 0, *pScreenWidth, *pScreenHeight);
   this->backgroundRect = backgroundRect;
   backgroundSpr.setTexture(backgroundTex);
   backgroundSpr.setTextureRect(backgroundRect);
}

void Animations::drawBackground(sf::RenderWindow & window) {
   window.draw(backgroundSpr);
}

#endif // ANIMATIONS_H


