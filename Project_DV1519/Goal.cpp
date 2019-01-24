#include "Goal.h"

Goal::Goal(Manager & manager) : Entity(manager)
{
	Entity::setType(ID::Type::GOAL);
}

Goal::~Goal()
{

}

void Goal::update(sf::Time deltaTime)
{

}

void Goal::processEvents(sf::Window & window)
{

}

void Goal::isCollide(Entity & other)
{

}
