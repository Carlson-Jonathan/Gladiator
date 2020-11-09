#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
using namespace std;

class AnimatedSprite {
public:

   AnimatedSprite() {}
   ~AnimatedSprite() { cout << "The Sprite animation just died\n\n";}
   AnimatedSprite(string textureFile, short x1, short y1, 
   	              short x2, short y2, short frames, float speed) {
      this->textureFile = textureFile;
      this->x1 = x1;
      this->y1 = y1;
      this->x2 = x2;
      this->y2 = y2; 
      this->frames = frames;
      this->speed = speed;
      createSprite();
   }

   short x1, y1, x2, y2, frames;
   float speed;
   sf::Texture texture;
   sf::IntRect rectangle;
   sf::Sprite sprite;
   sf::Clock clock;
   string textureFile;

   void createSprite() {
      if(!texture.loadFromFile(textureFile)) cout << "Error loading " << textureFile << "!\n";
      sf::IntRect rectangle(x1, y1, x2, y2);
      this->rectangle = rectangle;
      sprite.setTexture(texture);
      sprite.setTextureRect(rectangle);
   }

   // Loopable function
   void placeSpriteAnimation(sf::RenderWindow & window) {
      window.draw(sprite);
      if(clock.getElapsedTime().asSeconds() > speed) {
         if(rectangle.left == x2 * (frames - 1)) 
            rectangle.left = 0;
         else
            rectangle.left += x2;

         sprite.setTextureRect(rectangle);
         clock.restart();
      }
   }
};


#endif // ANIMATEDSPRITE_H

/*
Animations.h will set animation order, sprite placement, event listening, misc diplay stuff
Animated sprites will govern all moving sprite animations.
Remove the 'delete' statement from killCharacter()
Convert all character objects to pointers.

Create an animated sprite objects in combat.h that creates a pointer to the character objects
When a character dies, nullify the characterParticipants pointers and remove them from the combat lists.
After the animation sprite is done displaying death, delete the character object using the animation sprite, then delete the animation sprite.
*/