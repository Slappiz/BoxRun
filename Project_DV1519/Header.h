#pragma once

#define SCREEN_WIDTH 600 
#define SCREEN_HEIGHT 600
#define MIN_FPS 30

// Size of the character rectangle
#define CHARACTER_SIZE 30
// Max speed float value for the player class
#define MAX_PLAYER_SPEED 100.0f
// Speed of projectile float value
#define PROJECTILE_SPEED_MIN 130.0f
// Speed of projectile float value
#define PROJECTILE_SPEED_MAX 200.0f
// Size of the projectile
#define PROJECTILE_SIZE 30.0f
// Start Position for player
#define PLAYER_START 50
// Projectiles in scene
#define NR_PROJECTILES 5
// Walls
#define NR_WALLS 4

namespace ID
{
	enum Type
	{
		PLAYER, PROJECTILE, WALL, GOAL, ENTITY
	};
}

namespace Movement
{
	enum Direction
	{
		UP, DOWN, LEFT, RIGHT, NOT_MOVING
	};
}

namespace GameState
{
	enum State
	{
		UNINITIALIZED, MAIN_MENU, GAME, WIN, LOOSE
	};
	static State stateOfGame;
}

namespace PlayerGlobal
{
	struct PlayerInfo
	{
		static bool playerAlive;
		static bool playerWin;
	};
}

#include <ctime>
// Used to calculate random number
inline void rand_init() { srand(time(NULL)); };
inline float random(float min, float max) { return (rand() / float(RAND_MAX))*(max - min) + min; }
inline int random(int min, int max) { return rand() % (max - min + 1) + min; }