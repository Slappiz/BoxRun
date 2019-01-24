#include "Collision.h"
#include <iostream>

bool Collision::CollisionTest(const sf::RectangleShape& object1, const sf::RectangleShape& object2)
{
	sf::FloatRect a(object1.getPosition(), object1.getSize());
	sf::FloatRect b(object2.getPosition(), object2.getSize());
	
	// Works on projectiles and objective
	if (a.intersects(b))
		return true;

	else
		return false;
}

