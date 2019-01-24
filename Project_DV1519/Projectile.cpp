#include "Projectile.h"

Projectile::Projectile(Manager & manager) : Entity(manager)
{
	Entity::setType(ID::Type::PROJECTILE);

	Entity::getShape().setFillColor(sf::Color::Red);
	Entity::getShape().setSize(sf::Vector2f(PROJECTILE_SIZE, PROJECTILE_SIZE));
	Entity::getShape().setOrigin(sf::Vector2f(PROJECTILE_SIZE*0.5f, PROJECTILE_SIZE*0.5f));

	this->_direction = static_cast<Movement::Direction>(random(Movement::UP, Movement::RIGHT));
	this->randomSpeed = random(PROJECTILE_SPEED_MIN, PROJECTILE_SPEED_MAX);
}

Projectile::~Projectile()
{

}

void Projectile::update(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();

	if (_direction == Movement::UP)
	{
		Entity::getShape().move(0, -1 * randomSpeed * seconds);
	}
	if (_direction == Movement::DOWN)
	{
		Entity::getShape().move(0, randomSpeed * seconds);
	}
	if (_direction == Movement::LEFT)
	{
		Entity::getShape().move(-1 * randomSpeed * seconds, 0);
	}
	if (_direction == Movement::RIGHT)
	{
		Entity::getShape().move(randomSpeed * seconds, 0);
	}
	
	ifOutOfBounds();
	ifEdge();
}

void Projectile::processEvents(sf::Window & window)
{
}

void Projectile::isCollide(Entity & other)
{
	//if (Collision::CollisionTest(Entity::getShape(), other.getShape()))
	//{
	//	if(other.getType() == ID::PROJECTILE)
	//		this->_direction = static_cast<Movement::Direction>(random(Movement::UP, Movement::RIGHT));
	//}
}

void Projectile::ifOutOfBounds()
{
	if (Entity::getShape().getPosition().x < 0 -10 ||
		Entity::getShape().getPosition().x > SCREEN_WIDTH + 10)
	{
		Entity::getShape().setPosition(0, random(0, SCREEN_HEIGHT));
		this->_direction = static_cast<Movement::Direction>(random(Movement::UP, Movement::RIGHT));
		this->randomSpeed = random(PROJECTILE_SPEED_MIN, PROJECTILE_SPEED_MAX);
	}


	if (Entity::getShape().getPosition().y < 0 -10 ||
		Entity::getShape().getPosition().y > SCREEN_HEIGHT + 10)
	{
		Entity::getShape().setPosition(random(0, SCREEN_WIDTH), 0);
		//this->_direction = static_cast<Movement::Direction>(rand() % Movement::RIGHT);
		this->_direction = static_cast<Movement::Direction>(random(Movement::UP, Movement::RIGHT));
		this->randomSpeed = random(PROJECTILE_SPEED_MIN, PROJECTILE_SPEED_MAX);
	}
}

void Projectile::ifEdge()
{
	if(Entity::getShape().getPosition().x == 0 || Entity::getShape().getPosition().x == SCREEN_WIDTH)
		if (_direction == Movement::UP || _direction == Movement::DOWN)
		{
			this->_direction = static_cast<Movement::Direction>(random(Movement::UP, Movement::RIGHT));
		}
	if (Entity::getShape().getPosition().y == 0 || Entity::getShape().getPosition().y == SCREEN_HEIGHT)
		if (_direction == Movement::LEFT || _direction == Movement::RIGHT)
		{
			this->_direction = static_cast<Movement::Direction>(random(Movement::UP, Movement::RIGHT));
		}
}
