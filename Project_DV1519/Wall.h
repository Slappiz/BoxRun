#pragma once

#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(Manager& manager);
	~Wall();

	void update(sf::Time deltaTime);
	void processEvents(sf::Window & window);

	virtual void isCollide(Entity& other);
};

