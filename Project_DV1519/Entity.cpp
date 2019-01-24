#include "Entity.h"

Entity::Entity(Manager & manager) : _manager(manager), _id(ID::ENTITY)
{
	//? Test code
	//Entity::getShape().setFillColor(sf::Color::Green);
	//Entity::getShape().setSize(sf::Vector2f(50.f, 50.f));
	//Entity::getShape().setPosition(sf::Vector2f(300.f, 300.f));
}

Entity::~Entity()
{
}

sf::RectangleShape & Entity::getShape()
{
	return _shape;
}

ID::Type Entity::getType()
{
	return _id;
}

void Entity::setType(ID::Type id)
{
	this->_id = id;
}

//bool Entity::operator==(const Entity & original) const
//{
//	if (this->_id == original._id)
//		return true;
//
//	return false;
//}


void Entity::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_shape, states);
}
