#include <thread>
#include "GameManager.h"

int main()
{
	srand((int)time(NULL));

	GameManager game;
	game.Run();

	return EXIT_SUCCESS;
}
