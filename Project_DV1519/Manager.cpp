#include "Manager.h"
//? Had to put them here becuse of circualar dependency
#include "Player.h"
#include "Projectile.h"
#include "Wall.h"
#include "Goal.h"

Manager::Manager(const Manager & original)
{
	MakeCopy(original);
}

Manager & Manager::operator=(const Manager & original)
{
	//Check the memory adress of this and original, so we don't have a=a

	if (this != &original)
	{
		//Free the memory, and make a copy
		FreeMemory();
		MakeCopy(original);
	}
	//Return this object
	return *this;
}

Manager::Manager(float x, float y)
{
	//? Forgot to do this and got introduced to 'heap corruption detected'
	this->_capacity = 2;
	this->_nrOfElements = 0;
	this->_arr = new Entity*[this->_capacity]{ nullptr };
}

Manager::~Manager()
{
	FreeMemory();
}

void Manager::add(ID::Type id, Manager& manager)
{
	if (this->_nrOfElements == this->_capacity)
		Expand();

	if (id == ID::Type::PLAYER)
	{
		this->_arr[this->_nrOfElements] = new Player(manager);
		this->_nrOfElements++;
	}
	else if (id == ID::Type::PROJECTILE)
	{
		this->_arr[this->_nrOfElements] = new Projectile(manager);
		this->_nrOfElements++;
	}
	else if (id == ID::Type::WALL)
	{
		this->_arr[this->_nrOfElements] = new Wall(manager);
		this->_nrOfElements++;
	}
	else if (id == ID::Type::GOAL)
	{
		this->_arr[this->_nrOfElements] = new Goal(manager);
		this->_nrOfElements++;
	}
	else {
		std::cout << "MANAGER::ADD::ERROR::UNKNOWN_TYPE" << std::endl;
		return;
	}
}

void Manager::remove()
{
	return;
}

void Manager::clear()
{
	FreeMemory();
}

int Manager::getNrOfElements()
{
	return _nrOfElements;
}

void Manager::update(sf::Time deltaTime)
{
	// update all entity objects
	for (int i = 0; i < _nrOfElements; i++)
	{
		// Use auto to store a reference for the correct type to minimize code
		auto& entity = _arr[i];
		entity->update(deltaTime);
	}

	for (int i = 0; i < _nrOfElements; i++)
	{
		auto& entity_i = _arr[i];

		for (int j = 0; j < _nrOfElements; j++)
		{
			auto& entity_j = _arr[j];
			entity_i->isCollide(*entity_j);
		}
	}
}

void Manager::processEvents(sf::Window & window)
{
	for (int i = 0; i < _nrOfElements; i++)
	{
		// Use auto to store a reference for the correct type to minimize code
		auto& entity = _arr[i];
		entity->processEvents(window);
	}
}

//bool Manager::isCollide(Entity & other)
//{
//	return false;
//}

Entity& Manager::getEntity(int index)
{
	//if (_arr[index]->getType() == ID::Type::PLAYER) { }
	return *_arr[index];
}

void Manager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// draw all entity objects
	for (int i = 0; i < _nrOfElements; i++)
	{
		// Use auto to store a reference for the correct type to minimize code
		auto& entity = _arr[i];
		target.draw(*entity, states);
	}
}

void Manager::Expand()
{
	//Create a temporary array to hold the data
	Entity **tempArr = new Entity*[this->_capacity * 2]{ nullptr };
	//Transfer all data to the temporary arr
	for (int i = 0; i < this->_capacity; i++)
	{
		tempArr[i] = this->_arr[i];
	}
	//Delete the old arrray
	delete[] this->_arr;
	//Increase the capacity
	this->_capacity = this->_capacity * 2;
	//Transfer all data to the expanded array
	this->_arr = tempArr;
}

void Manager::FreeMemory()
{
	//Delete all entity object in the array
	// eventuellt capacity
	for (int i = 0; i < this->_nrOfElements; i++)
	{
		delete this->_arr[i];
	}
	delete[] this->_arr;
}

void Manager::MakeCopy(const Manager & original)
{
	this->_capacity = original._capacity;
	this->_nrOfElements = original._nrOfElements;

	this->_arr = new Entity*[original._capacity]{ nullptr };
	//? Took me a while to figure out how to do this
	for (int i = 0; i < original._nrOfElements; i++)
	{
		if (original._arr[i]->getType() == ID::Type::PLAYER)
		{
			Player* _player = static_cast<Player*>(original._arr[i]);
			// The default copy constructor gets called for this copy
			this->_arr[i] = new Player(*_player);
		}
		else if (original._arr[i]->getType() == ID::Type::PROJECTILE)
		{
			Projectile* _projectile = static_cast<Projectile*>(original._arr[i]);
			// The default copy constructor gets called for this copy
			this->_arr[i] = new Projectile(*_projectile);
		}
		else if (original._arr[i]->getType() == ID::Type::WALL)
		{ 
			Wall* _wall = static_cast<Wall*>(original._arr[i]);
			// The default copy constructor gets called for this copy
			this->_arr[i] = new Wall(*_wall);
		}
		else if (original._arr[i]->getType() == ID::Type::GOAL)
		{
			Goal* _goal = static_cast<Goal*>(original._arr[i]);
			// The default copy constructor gets called for this copy
			this->_arr[i] = new Goal(*_goal);
		}
		else
		{
			// print error message
			std::cout << "MANAGER::MAKECOPY::ERROR::UNKNOWN_TYPE" << std::endl;
			return;
		}
	}
}
