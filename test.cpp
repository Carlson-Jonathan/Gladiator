// #ifndef MAIN_CPP
// #define MAIN_CPP
#include <iostream>
#include "animations.h"
using namespace std;

int main() {

	short screenWidth = 900;
	short screenHeight = 600;
   	Animations animations(screenWidth, screenHeight);
   	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), 
   		"Gladiator by Jonathan Carlson");
   	window.setFramerateLimit(60);
   	
   	while (window.isOpen()) {
       animations.eventListener(window);
       window.clear(sf::Color(102, 255, 255));
/******************************** Game Loop ***********************************/



       animations.flyingDragon(window);












/******************************************************************************/
         window.display();
     }
	return 0;
}

// #endif // MAIN_CPP