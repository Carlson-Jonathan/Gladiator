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

   short screenWidth = 900;
   short screenHeight = 600;
   
   vector<Character> heroes = createCharacters(1);
   Battle battle(heroes, "Random", 1, 1);

   Animations animations(screenWidth, screenHeight);

   sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), 
      "Gladiator by Jonathan Carlson");
   window.setFramerateLimit(60);


   while (window.isOpen()) {
      animations.eventListener(window);
      window.clear(sf::Color(102, 255, 255));
/******************************** Game Loop ***********************************/



      animations.flyingDragon(window);
      battle.combat(window);











/******************************************************************************/
      window.display();
   }
   cout << "\n\n>> End of Program. <<" << endl;
	return 0;
}

#endif // MAIN_CPP