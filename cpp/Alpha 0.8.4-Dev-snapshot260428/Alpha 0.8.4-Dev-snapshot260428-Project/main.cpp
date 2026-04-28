#include "./Lib/game.h"

int main() {
	SetConsoleOutputCP(65001);//设为UTF-8(国际通用)
	srand((unsigned int)time(nullptr));
	game_overworld();
	write_game_data();
	return 0;
}