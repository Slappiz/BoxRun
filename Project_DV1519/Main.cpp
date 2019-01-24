#include "Game.h"
#include "Header.h"

//Declare the static player variables in header.h
bool PlayerGlobal::PlayerInfo::playerAlive = false;
bool PlayerGlobal::PlayerInfo::playerWin = false;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.run(SCREEN_WIDTH, SCREEN_HEIGHT, MIN_FPS);
}