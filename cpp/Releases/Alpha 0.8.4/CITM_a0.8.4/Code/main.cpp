#include "../Lib/game.h"
#include "../Lib/entity.h"
#include "../Lib/map.h"
#include "../Lib/ui.h"
#include "../Lib/save.h"
#include "../Lib/game_nether.h"
#include "../Lib/player.h"

int main() {
	SetConsoleOutputCP(65001);//设为UTF-8(国际通用)
	srand((unsigned int)time(nullptr));
	read_game_settings();
	read_language_settings();
	while (true) {
		system("color 03");
		while (true) {
			if(title_screen() == 1) break;
		}
		game_overworld();
	}
	return 0;
}

