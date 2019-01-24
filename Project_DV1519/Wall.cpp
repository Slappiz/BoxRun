#include "Wall.h"

Wall::Wall(Manager & manager) : Entity(manager)
{
	Entity::setType(ID::Type::WALL);
}

Wall::~Wall()
{

}

void Wall::update(sf::Time deltaTime)
{

}

void Wall::processEvents(sf::Window & window)
{

}

void Wall::isCollide(Entity & other)
{

}
