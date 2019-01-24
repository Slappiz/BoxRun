#pragma once
#include "Header.h"
#include <SFML\Graphics.hpp>

class Intro
{
public:
	Intro() {}
	~Intro() {}

	void show(sf::RenderWindow &window, std::string filePath)
	{
		// Get window size
		sf::Vector2f targetsize(window.getView().getSize());

		sf::Texture texture;
		if(!texture.loadFromFile(filePath))
			std::cout << "INTRO::ERROR::TEXTURE" << std::endl;

		// todo add texture to sprite, add file path in show like the original function
		sf::Sprite sprite;
		sprite.setTexture(texture);

		// ReSize the sprite to  fit the screen
		sprite.scale((targetsize.x / sprite.getLocalBounds().width), (targetsize.y / sprite.getLocalBounds().height));

		// Draw sprite
		window.draw(sprite);
		window.display();

		sf::Event currentEvent;

		while (true)
		{
			while (window.pollEvent(currentEvent))
			{
				// Close the screen if close is clicked
				if (currentEvent.type == sf::Event::Closed) {
					exit(0);
				}

				if (currentEvent.type == sf::Event::EventType::KeyPressed
					|| currentEvent.type == sf::Event::EventType::Closed)
				{
					return;
				}
			}
		}
	}

};

