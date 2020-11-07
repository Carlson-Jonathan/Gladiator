#ifndef MAIN_CPP
#define MAIN_CPP
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "animations.h"
#include "battle.h"
using namespace std;

vector<Character> createCharacters(short numHeroes) {
   vector<Character> heroes;
   for(short i = 0; i < numHeroes; i++) {
      cout << "\tName your hero(s): ";
      string name;
      getline(cin, name);
      Character hero(name, true);
      heroes.push_back(hero);
   }
   cout << endl;

   return heroes;
}

int main() {

   short screenWidth = 1333, // 16:9 aspect ratio
         screenHeight = 750;
   short* pScreenWidth = &screenWidth;
   short* pScreenHeight = &screenHeight;

   Animations animations(pScreenWidth, pScreenHeight);
   Animations* pAnimations = &animations;
   
   sf::Music music;
   if (!music.openFromFile("Sounds/Music/preBattle.ogg"))
      cout << "Error opening file 'Sounds/Music/preBattle.ogg'!\n";
   music.setLoop(true);
   music.play();

   vector<Character> heroes = createCharacters(1);

       // heroes, monster type, debug mode, num monsters, text mode, animations
   Battle battle(heroes, "Dragon", 0, 1, 0, pAnimations);

   sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), 
      "Gladiator by Jonathan Carlson");
   window.setFramerateLimit(60);

   music.stop();
   while (window.isOpen()) {
      animations.eventListener(window);
      window.clear(sf::Color(102, 255, 255));
/******************************** Game Loop ***********************************/


      battle.combat(window);
      break;





/******************************************************************************/
      window.display();
   }
   cout << "\n\n>> End of Program. <<" << endl;
	return 0;
}

#endif // MAIN_CPP