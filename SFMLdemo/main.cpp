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

	short screenWidth = 850;
	short screenHeight = 600;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML works!");
    sf::Music music;
	sf::Text text;
	sf::Font font; 
	sf::Texture texture;
	sf::Sprite sprite;
	window.setFramerateLimit(60);

	// Used for animations
	short x = 0.f,
		  y = 0.f;


	// Images
	if (!texture.loadFromFile("jon2.png")) cout << "unable to load image" << endl;
	sprite.setTexture(texture);

	// Shapes
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    // Fonts and text
	if (!font.loadFromFile("Fonts/Sweet Maple.otf")) cout << "Font not found" <<	endl; 
	text.setFont(font); 
	text.setString("Holy crap SFML is easy to use!");
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


	shape.setPosition(sf::Vector2f(screenWidth / 2, screenHeight / 2));
	float a = 0, b = 0;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        /**********************************************************************/
        // All stuff gets drawn between these lines

		sprite.setPosition(sf::Vector2f(x, y));
        window.draw(shape);
		window.draw(sprite);
		window.draw(text);

		if(x >= screenWidth - 300) a = -4;
		if(x <= 0) a = 4;
		if(y >= screenHeight - 316) b = -4;
		if(y <= 0) b = 4;


		x += a;
		y += b;

        /**********************************************************************/
        window.display();
    }

    return 0;
}