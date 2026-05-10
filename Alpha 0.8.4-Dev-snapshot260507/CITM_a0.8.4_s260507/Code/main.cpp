#include "../Lib/game.h"
#include "../Lib/entity.h"
#include "../Lib/map.h"
#include "../Lib/ui.h"

int main() {
	SetConsoleOutputCP(65001);//设为UTF-8(国际通用)
	srand((unsigned int)time(nullptr));
	while (1) {
		system("color 03");
		while(1){
			if(title_screen() == 1) break;
		}
		game_overworld();
	}
	return 0;
}
