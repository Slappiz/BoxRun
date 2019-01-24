#pragma once

#include <SFML\Graphics.hpp>

#include <iostream>
#include <sstream>
#include <fstream>

#define OVERLAY_SIZE 16

class Overlay : public sf::Drawable
{
public:
	Overlay(int x, int y)
	{
		std::ifstream myFile("Assets/Text/highscore.txt");

		if (myFile.is_open())
		{
			getline(myFile, _line);
			std::cout << _line << std::endl;
			/*		
			while (getline(myFile, _line))
			{
				std::cout << _line << '\n';
			}*/
			myFile.close();
		}
		else {
			std::cout << "OVERLAY::ERROR::LOADING::FILE" << std::endl;
		}

		this->_time = 0.00f;

		setFont();
		_text.setFont(_font);
		_text.setCharacterSize(OVERLAY_SIZE);
		_text.setOrigin(OVERLAY_SIZE * .5f, OVERLAY_SIZE * .5f);
		_text.setPosition(x*.02f, y*.02f);
		//text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		//text.setColor(sf::Color::White);
		_bestTime = strtof((_line).c_str(), 0);
	}

	~Overlay()
	{

	}

	void update()
	{
		std::stringstream ss1;
		std::stringstream ss2;
		std::stringstream ss3;

		_time = _myClock.getElapsedTime().asSeconds();

		ss1 << _time;
		ss2 << _bestTime;
		ss3 << _last;

		_text.setString("Time " + ss1.str() + "\n" + "Best " + ss2.str() + "\n" + "Last " + ss3.str());
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		target.draw(_text, states);
	}

	void restartClock()
	{
		_myClock.restart();
	}

	void saveTime()
	{
		// String to float
		if (_time < _bestTime)
		{
			_bestTime = _time;

			std::ofstream myFile("Assets/Text/highscore.txt");

			if (myFile.is_open())
			{
				myFile << std::to_string(_time);
				myFile.close();
			}
		}
	}

	void setLastTime()
	{
		this->_last = _time;
	}

private:
	sf::Font _font;
	sf::Text _text;
	sf::Clock _myClock;
	std::string _line;

	float _time;
	float _last;
	float _bestTime;

	void setFont()
	{
		if (!_font.loadFromFile("Assets/Fonts/square-deal.ttf"))
			std::cout << "ERROR::FONT" << std::endl;
	}
};