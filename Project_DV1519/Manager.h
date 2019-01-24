#pragma once

#include <iostream>

#include "Header.h"

#include "Entity.h"
#include "Collision.h"
// Manager need to know about the subclasses to decide which type
// of entity to create when expanding the array of entity pointers
//? So this does not work, but putting them in the cpp does the trick
//#include "Player.h"
//#include "Projectile.h"
//#include "Wall.h"
//#include "Goal.h"

class Entity;

class Manager : public sf::Drawable
{
public:
	Manager(const Manager & original);
	Manager & operator=(const Manager & original);
	//Manager(const Manager&) = delete;
	//Manager& operator=(const Manager&) = delete;
	Manager(float x = 600, float y = 600);
	~Manager();

	// Add needs the ID for the subclass and a reference to the world object in Game
	void add(ID::Type id, Manager& manager);	// Add new entity 
	void remove();							// delete all entity objects
	void clear();
	int getNrOfElements();					// number of entity objects

	//
	void update(sf::Time deltaTime);
	void processEvents(sf::Window & window);
	/*bool isCollide(Entity & other);*/

	//todo need a function to set textures and positions etc. of the entity objects
	//? not sure if i can just return a entity reference instead. 
	//? using auto for now since we know that it's going to be a subclass. 
	/*If the type of an entity with an undeduced placeholder type is needed to determine 
	the type of an expression, the program is ill-formed.*/
	Entity& getEntity(int index); // Not that easy to manage, but it will do for this project.

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Entity** _arr;
	int _capacity;
	int _nrOfElements;

	void Expand();
	void FreeMemory();
	void MakeCopy(const Manager & original);
};

