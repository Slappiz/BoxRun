#pragma once

#include <SFML\Graphics.hpp>

#include "Manager.h"
#include "Intro.h"
#include "Overlay.h"

class Game
{
public:
	// Non copyable class
	Game(const Game&) = delete;
	Game & operator = (const Game&) = delete;

	Game(int x = 600, int y = 600);
	~Game();

	void run(int screenWidth, int screenHeight, int min_fps);

private:
	/*GameState::GlobalGameInfo _gameInfo;*/

	void init(); // Populates the manager with entity objects
	void processEvents(); // updates events in application
	void processState(); //? remove i guess
	void update(sf::Time deltaTime); // updates the application
	void render(); // draws everything to the screen

	sf::RenderWindow _window;				// the application window
	Manager _manager;						// A container for entity objects
	PlayerGlobal::PlayerInfo _playerInfo;	// Static bools to trigger states in main loop
	Overlay _overlay;						// timer

	//start screens
	void showIntro();		//intro screen
	void showTutorial();	//tutorial screen
	void showExit();		//exit screen

	// init functions
	void addPlayer();		//add player object
	void addWalls();		//add wall obejcts
	void addProjectiles();	//add projectile objects
	void addGoal();			//add goal object
};

