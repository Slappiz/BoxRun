#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(Manager& manager);
	~Player();

	void update(sf::Time deltaTime);
	void processEvents(sf::Window & window);

	void isCollide(Entity& other);

private:
	PlayerGlobal::PlayerInfo _playerInfo;

	Movement::Direction _direction;
	static GameState::State stateOfGame;

	void ifOutOfBounds();
};

