#pragma once

#include <SFML\Graphics.hpp>

#include "Manager.h"

//Type is used to identify which type of entity we are trying to copy in the manager
class Manager;

class Entity : public sf::Drawable
{
public:
	// Non copyable class
	//Entity(const Entity&) = delete;
	//Entity& operator=(const Entity&) = delete;
	Entity(Manager& manager);
	virtual ~Entity();

	// Get shape - used for everything related to the shape
	virtual sf::RectangleShape& getShape();

	// Type specifier for the manager class
	virtual ID::Type getType();
	// Every subclass need to call this function and use the correct type
	virtual void setType(ID::Type id);

	virtual void update(sf::Time deltaTime) = 0;
	virtual void processEvents(sf::Window & window) = 0;
	//bool operator==(const Entity &original)const;
	virtual void isCollide(Entity& other) = 0;

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	sf::RectangleShape _shape;
	Manager& _manager;

	ID::Type _id;
};

