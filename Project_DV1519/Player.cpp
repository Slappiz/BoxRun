#include "Player.h"

Player::Player(Manager & manager) : Entity (manager), _direction(Movement::NOT_MOVING)
{
	Entity::setType(ID::Type::PLAYER);
	_playerInfo.playerAlive = true;
}

Player::~Player()
{

}

void Player::update(sf::Time deltaTime)
{
	float seconds = deltaTime.asSeconds();

	// Movement
	if (_direction == Movement::UP)
	{
		Entity::getShape().move(0, -1 * MAX_PLAYER_SPEED * seconds);
	}
	if (_direction == Movement::DOWN)
	{
		Entity::getShape().move(0, MAX_PLAYER_SPEED * seconds);
	}
	if (_direction == Movement::LEFT)
	{
		Entity::getShape().move(-1 * MAX_PLAYER_SPEED * seconds, 0);
	}
	if (_direction == Movement::RIGHT)
	{
		Entity::getShape().move(MAX_PLAYER_SPEED * seconds, 0);
	}

	// Keeps player in the window
	ifOutOfBounds();
}

void Player::processEvents(sf::Window & window)
{
	// Up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_direction = Movement::UP;
	}
	// Down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_direction = Movement::DOWN;
	}
	// Left
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_direction = Movement::LEFT;
	}
	// Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_direction = Movement::RIGHT;
	}
	else
	{
		_direction = Movement::NOT_MOVING;
	}
}

void Player::isCollide(Entity & other)
{
	if (other.getType() == ID::PROJECTILE)
	{
		//todo set global gameState to lose and restart
		//_stateOfGame = GameState::LOOSE;
		//return Collision::CollisionTest(Entity::getShape(), other.getShape());
		if (Collision::CollisionTest(Entity::getShape(), other.getShape()))
		{
			_playerInfo.playerAlive = false;
		}
	}
	else if (other.getType() == ID::GOAL)
	{
		if (Collision::CollisionTest(Entity::getShape(), other.getShape()))
		{
			//todo set different bool
			_playerInfo.playerWin = true;
		}
	}
	else if (other.getType() == ID::WALL)
	{
		if (Collision::CollisionTest(Entity::getShape(), other.getShape()))
		{
			_playerInfo.playerAlive = false;
		}
	}
}

void Player::ifOutOfBounds()
{
	sf::Vector2f temp = Entity::getShape().getPosition();
	int x = temp.x;
	int y = temp.y;

	if (x < 0)
	{
		Entity::getShape().setPosition(CHARACTER_SIZE*0.5f, y);
	}
	if (x > SCREEN_WIDTH)
	{
		Entity::getShape().setPosition(SCREEN_WIDTH - CHARACTER_SIZE*0.5f, y);
	}
	if (y < 0)
	{
		Entity::getShape().setPosition(x, CHARACTER_SIZE*0.5f);
	}
	if (y > SCREEN_HEIGHT)
	{
		Entity::getShape().setPosition(x, SCREEN_HEIGHT - CHARACTER_SIZE*0.5f);
	}
}
