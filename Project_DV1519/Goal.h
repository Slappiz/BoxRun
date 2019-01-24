#pragma once

#include "Entity.h"

class Goal : public Entity
{
public:
	Goal(Manager& manager);
	~Goal();

	void update(sf::Time deltaTime);
	void processEvents(sf::Window & window);

	virtual void isCollide(Entity& other);
};

