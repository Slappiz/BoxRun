#pragma once

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(Manager& manager);
	~Projectile();

	void update(sf::Time deltaTime);
	void processEvents(sf::Window & window);

	virtual void isCollide(Entity& other);

private:
	Movement::Direction _direction;

	int randomSpeed;
	void ifOutOfBounds();
	void ifEdge();
};

