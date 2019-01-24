#include <SFML/Graphics.hpp>

class Collision
{
public:
	Collision() = delete;
	Collision(const Collision&) = delete;
	Collision& operator=(const Collision&) = delete;

	static bool CollisionTest(const sf::RectangleShape& Object1, const sf::RectangleShape& Object2);
};
