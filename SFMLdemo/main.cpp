#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
using namespace std;

// Get it all here: https://www.sfml-dev.org/

int main()
{

	short screenWidth = 1400;
	short screenHeight = 900;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Examples");
    sf::Music music;
	sf::Text text;
	sf::Font font; 
	sf::Texture dragonTex;
	sf::Clock clock;
	window.setFramerateLimit(60);

	// Used for animations
	short x = 0.f,
		  y = 0.f;


	// Images
	if (!dragonTex.loadFromFile("dragon.png")) cout << "unable to load image" << endl;
	sf::IntRect dragonSourceSprite(0, 161, 191, 161);
 	sf::Sprite sprite(dragonTex, dragonSourceSprite);



	// Shapes
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);


    // Fonts and text
	if (!font.loadFromFile("Fonts/Sweet Maple.otf")) cout << "Font not found" <<	endl; 
	text.setFont(font); 
	text.setString("SFML Examples by Jonathan Carlson");
	text.setCharacterSize(48); 
	text.setFillColor(sf::Color::Yellow);
	// text.setStyle(sf::Text::Bold | sf::Text::Underlined);


	// Music
	if (!music.openFromFile("song.ogg"))
        return -1; // error
	music.play();



	text.setPosition(sf::Vector2f(screenWidth / 4, 0));
	//center text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
	               textRect.top  + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(screenWidth / 2, 100));


	shape.setPosition(sf::Vector2f(screenWidth / 2 - 100.f, screenHeight / 2 - 100.f));
	float a = 0, b = 0;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(102, 255, 255));
        /**********************************************************************/
        // All stuff gets drawn between these lines

		sprite.setPosition(sf::Vector2f(x, y));

        window.draw(shape);
		window.draw(text);
		window.draw(sprite);

		if(clock.getElapsedTime().asSeconds() > 0.2f) {
			
			if(dragonSourceSprite.left == 382) 
				dragonSourceSprite.left = 0;
			else
				dragonSourceSprite.left += 191;

			sprite.setTextureRect(dragonSourceSprite);
			clock.restart();

		}


		if(x >= screenWidth - 191) {
			dragonSourceSprite.top = 483;
			a = -4;
		}

		if(x <= 0) {
			dragonSourceSprite.top = 161;
			a = 4;
		}

		if(y >= screenHeight - 161) {
			b = -2;
			dragonSourceSprite.top = 0;
		}

		if(y <= 0) {
			b = 2;
			dragonSourceSprite.top = 322;
		}


		x += a;
		y += b;

        /**********************************************************************/
        window.display();
    }

    return 0;
}