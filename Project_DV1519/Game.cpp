#include "Game.h"

Game::Game(int x, int y) : _window(sf::VideoMode(x, y), "Project_DV1519", sf::Style::Close), _overlay(x, y)
{
	GameState::stateOfGame = GameState::UNINITIALIZED;
}

Game::~Game()
{

}

void Game::run(int screenWidth, int screenHeight, int min_fps)
{
	_window.setSize(sf::Vector2u(screenWidth, screenHeight));
	sf::Clock clock; // clock object
	sf::Time timeSinceLastUpdate; //
	sf::Time timePerFrame = sf::seconds(1.0f / min_fps); // time for each frame. 
	//todo Main Menu
	//todo Overlay with timer and previous best time
	showIntro();
	showTutorial();
	init();
	_overlay.restartClock();
	while (_window.isOpen())
	{

		if (!_playerInfo.playerAlive)
		{
			_manager.getEntity(0).getShape().setPosition(sf::Vector2f(PLAYER_START, PLAYER_START));
			_playerInfo.playerAlive = true;
		}
		if (_playerInfo.playerWin)
		{
			_overlay.setLastTime();
			_overlay.saveTime();
			_overlay.restartClock();
			_manager.getEntity(0).getShape().setPosition(sf::Vector2f(PLAYER_START, PLAYER_START));
			_playerInfo.playerWin = false;
		}

		processEvents();
		timeSinceLastUpdate = clock.restart(); //restart clock for each loop.

		while (timeSinceLastUpdate > timePerFrame) // checks if the current frames time is greater than the time per frame value 
		{
			timeSinceLastUpdate -= timePerFrame; // adjust to keep steady fps
			update(timePerFrame); // update 
		}
		update(timeSinceLastUpdate);
		render();
	}
}

void Game::init()
{
	rand_init();
	// add Entity
	//? Could have been done with a level class and switch levels with states but that would also require a implementation of a remove entity function in the manager
	addPlayer();
	addWalls();
	addProjectiles();
	addGoal();
}

void Game::processEvents()
{
	sf::Event _event;
	while (_window.pollEvent(_event))
	{
		// If escape or X on window is pressed.
		if ((_event.type == sf::Event::Closed) || ((_event.type == sf::Event::KeyPressed) && (_event.key.code == sf::Keyboard::Escape)))
		{
			_window.close(); // close window and exit program
		}
	}
	// processEvents
	_manager.processEvents(_window);
}

void Game::processState()
{
}

void Game::update(sf::Time deltaTime)
{
	_manager.update(deltaTime);
	_overlay.update();
}

void Game::render()
{
	_window.clear(sf::Color::Black);

	//draw
	_window.draw(_manager);
	_window.draw(_overlay);

	_window.setView(_window.getDefaultView());
	_window.display();
}

void Game::showIntro()
{
	Intro intro;
	std::string sintro = "Assets/Textures/Intro/Intro_1.png";
	intro.show(_window, sintro);
}

void Game::showTutorial()
{
	Intro tutorial;
	std::string stutorial = "Assets/Textures/Intro/Tutorial_1.png";
	tutorial.show(_window, stutorial);
}

void Game::showExit()
{
	//Intro exit;
	//exit.show(_window);
}

void Game::addPlayer()
{
	// Add
	_manager.add(ID::PLAYER, _manager);
	// Set shape
	_manager.getEntity(0).getShape().setFillColor(sf::Color::Green);
	_manager.getEntity(0).getShape().setSize(sf::Vector2f(CHARACTER_SIZE, CHARACTER_SIZE));
	//_manager.getEntity(0).getShape().setOrigin(sf::Vector2f(CHARACTER_SIZE*0.5f, CHARACTER_SIZE*0.5f));
	_manager.getEntity(0).getShape().setPosition(sf::Vector2f(PLAYER_START, PLAYER_START));
}

void Game::addWalls()
{
	for (int i = 0; i < NR_WALLS; i++)
	{
		_manager.add(ID::WALL, _manager);
	}
	// Wall 1
	_manager.getEntity(1).getShape().setFillColor(sf::Color::White);
	_manager.getEntity(1).getShape().setSize(sf::Vector2f(50, SCREEN_HEIGHT *0.4f));
	_manager.getEntity(1).getShape().setPosition(sf::Vector2f(SCREEN_WIDTH*0.5f, 0));
	// Wall 2
	_manager.getEntity(2).getShape().setFillColor(sf::Color::Magenta);
	_manager.getEntity(2).getShape().setSize(sf::Vector2f(SCREEN_WIDTH - 100, 50));
	_manager.getEntity(2).getShape().setPosition(sf::Vector2f(0, SCREEN_HEIGHT*0.5f));
	// Wall 3
	_manager.getEntity(3).getShape().setFillColor(sf::Color::Blue);
	_manager.getEntity(3).getShape().setSize(sf::Vector2f(50, SCREEN_HEIGHT * 0.6f));
	_manager.getEntity(3).getShape().setPosition(sf::Vector2f((SCREEN_WIDTH*0.75f), SCREEN_HEIGHT*0.25f));
	// Wall 4
	_manager.getEntity(4).getShape().setFillColor(sf::Color::Cyan);
	_manager.getEntity(4).getShape().setSize(sf::Vector2f(50, SCREEN_HEIGHT * 0.6f));
	_manager.getEntity(4).getShape().setPosition(sf::Vector2f((SCREEN_WIDTH*0.4f), SCREEN_HEIGHT*0.75f));
}

void Game::addProjectiles()
{
	// Add
	for (int i = 0; i < NR_PROJECTILES; i++)
	{
		_manager.add(ID::PROJECTILE, _manager);
	}
	// Position
	//? Maybe use random for all of this but need a new offset for each entity
	_manager.getEntity(5).getShape().setPosition(sf::Vector2f(SCREEN_WIDTH, 75));
	_manager.getEntity(6).getShape().setPosition(sf::Vector2f(0, 150));
	_manager.getEntity(7).getShape().setPosition(sf::Vector2f(SCREEN_WIDTH, 225));
	_manager.getEntity(8).getShape().setPosition(sf::Vector2f(250, SCREEN_HEIGHT));
	_manager.getEntity(9).getShape().setPosition(sf::Vector2f(450, 0));
}

void Game::addGoal()
{
	// Add
	_manager.add(ID::GOAL, _manager);
	// Set shape
	_manager.getEntity(10).getShape().setFillColor(sf::Color::Yellow);
	_manager.getEntity(10).getShape().setSize(sf::Vector2f(CHARACTER_SIZE, CHARACTER_SIZE));
	//_manager.getEntity(10).getShape().setOrigin(sf::Vector2f(CHARACTER_SIZE*0.5f, CHARACTER_SIZE*0.5f));
	_manager.getEntity(10).getShape().setPosition(sf::Vector2f(SCREEN_WIDTH *0.1f, SCREEN_HEIGHT * 0.9f));
}
