#include "./Lib/game.h"
#include "./Lib/entity.h"
#include "./Lib/map.h"
#include "./Lib/ui.h"

void print_map() { //输出地图
	printf(" ╔════════════════╦═══════════════╦═══════════════╗ \n");
	printf(" ║ 金钱:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	printf("%9d", money);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	printf(" ║ 生命:");
	if (health > 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	else if (health > 10 && health <= 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	else if (health <= 10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("%9d", health);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	printf("║ 饱食度:");
	if (hunger > 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	else if (hunger > 10 && hunger <= 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	else if (hunger <= 10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("%7d", hunger);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	printf("║ \n ╚════════════════╩═══════════════╩═══════════════╝ \n");
	printf("\n");
	printf("  ");
	for (int i = 1; i <= n; i++) {
		printf("%3d", i);
	}
	printf("\n");
	for (int i = 1; i <= n; i++) {
		printf("%2d ", i);
		for (int j = 1; j <= n; j++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block_color[overworld[i][j]]);
			printf("[%c]", num_to_char_print_map[overworld[i][j]]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
		}
		printf("\n");
	}
	for(int i = 0; i < (int)message_list.size(); i++){
		cout << message_list[i].message << endl;
		message_list[i].tim--;
		if(message_list[i].tim == 0) message_list.erase(message_list.begin() + i);
	}
	if (debug_screen == 1) {
		printf("\n");
		printf("Map size:%d\n", n);
		printf("Position:(%d,%d)\n", x, y);
		printf("Facing:");
		if (facing == 0) printf("East");
		if (facing == 1) printf("South");
		if (facing == 2) printf("West");
		if (facing == 3) printf("North");
		printf("(facing:%d)\n", facing);
		printf("Biome Fest:");
		cout << biome[biome_fest] << endl;
		printf("hunger step summary for hunger:%d\n", hunger_step_summary);
		printf("Map dataization:\n");
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				printf("%d ", overworld[i][j]);
			}
			printf("\n");
		}
		printf("Total item:\n");
		for (int i = 0; i < 17; i++) {
			printf("%d ", inventory[i]);
		}
		printf("\n");
		printf("Zombie Total:%d\n", zombie_sum);
		for (int i = 1; i <= zombie_sum; i++) {
			printf("Zombie Position:(%d,%d) health:%d\n", zombie[i].x, zombie[i].y, zombie[i].health);
		}
		printf("Skeleton Total:%d\n", skeleton_sum);
		for (int i = 1; i <= skeleton_sum; i++) {
			printf("Skeleton Position:(%d,%d) health:%d\n", skeleton[i].x, skeleton[i].y, skeleton[i].health);
		}
		printf("Arrow Total:%d\n", arrow_sum);
		for (int i = 1; i <= arrow_sum; i++) {
			if (arrow[i].x > 0 && arrow[i].y > 0) printf("Arrow Position:(%d,%d) facing:%d\n", arrow[i].x, arrow[i].y, arrow[i].facing);
		}
	}
}
void print_map_Nether() { //输出地图
	printf(" ╔════════════════╦═══════════════╦═══════════════╗ \n");
	printf(" ║ 金钱:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	printf("%9d", money);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf(" ║ 生命:");
	if (health > 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	else if (health > 10 && health <= 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	else if (health <= 10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("%9d", health);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("║ 饱食度:");
	if (hunger > 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	else if (hunger > 10 && hunger <= 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	else if (hunger <= 10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("%7d", hunger);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("║ \n ╚════════════════╩═══════════════╩═══════════════╝ \n");
	printf("\n");
	printf("  ");
	for (int i = 1; i <= n; i++) {
		printf("%3d", i);
	}
	printf("\n");
	for (int i = 1; i <= n; i++) {
		printf("%2d ", i);
		for (int j = 1; j <= n; j++) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), block_color_nether[nether[i][j]]);
			printf("[%c]", num_to_char_print_map_nether[nether[i][j]]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		}
		printf("\n");
	}
	for(int i = 0; i < (int)message_list.size(); i++){
		cout << message_list[i].message << endl;
		message_list[i].tim--;
		if(message_list[i].tim == 0) message_list.erase(message_list.begin() + i);
	}
	if (debug_screen == 1) {
		printf("\n");
		printf("Map size:%d\n", n);
		printf("Position:(%d,%d)\n", x, y);
		printf("Facing:");
		if (facing == 0) printf("East");
		if (facing == 1) printf("South");
		if (facing == 2) printf("West");
		if (facing == 3) printf("North");
		printf("(facing:%d)\n", facing);
		printf("Biome Fest:");
		cout << biome[biome_fest] << endl;
		printf("hunger step summary for hunger:%d\n", hunger_step_summary);
		printf("Map dataization:\n");
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				printf("%d ", nether[i][j]);
			}
			printf("\n");
		}
		printf("Lava Zombie Total:%d\n", lava_zombie_sum);
		for (int i = 1; i <= lava_zombie_sum; i++) {
			printf("Lava Zombie Position:(%d,%d) health:%d\n", lava_zombie[i].x, lava_zombie[i].y, lava_zombie[i].health);
		}
		printf("Burn Skeleton Total:%d\n", burn_skeleton_sum);
		for (int i = 1; i <= burn_skeleton_sum; i++) {
			printf("Burn Skeleton Position:(%d,%d) health:%d\n", burn_skeleton[i].x, burn_skeleton[i].y, burn_skeleton[i].health);
		}
		printf("Burn Arrow Total:%d\n", burn_arrow_sum);
		for (int i = 1; i <= burn_arrow_sum; i++) {
			if (burn_arrow[i].x > 0 && burn_arrow[i].y > 0) printf("Burn Arrow Position:(%d,%d) facing:%d\n", burn_arrow[i].x, burn_arrow[i].y, burn_arrow[i].facing);
		}
		printf("Total item:\n");
		for (int i = 0; i < 17; i++) {
			printf("%d ", inventory[i]);
		}
	}
}
void generation_wall(int x, int y) {
	vis[x][y] = 1;
	overworld[x][y] = rand() % 8;
	for (int i = 0; i < 4; i++) {
		int tx = x + direction_x[i], ty = y + direction_y[i];
		if (in(tx, ty) && overworld[tx][ty] == DIRT) {
			generation_wall(tx, ty);
		}
	}
}
void generation_world() {
	memset(overworld, DIRT, sizeof(overworld));
	memset(vis, false, sizeof(vis));
	while (1) {
		int MapX, MapY; //构建地图的起点
		MapX = rand() % n + 1, MapY = rand() % n + 1;
		if (MapX == 0) MapX++;
		if (MapY == 0) MapY++;
		generation_wall(MapX, MapY);
		checkRoad(2, 2); //是否有路能到终点
		if (flag == 1) {
			break;
		}
		flag = 0; //初始化
		memset(vis, false, sizeof(vis));
	}
	zombie_sum = n / 3;
	skeleton_sum = 2;
	for (int i = 1; i <= rand() % n; i++) {
		int gx = rand() % (n + 1), gy = rand() % (n + 1);
		if (gx == 0) gx++;
		if (gy == 0) gy++;
		overworld[gx][gy] = 8;
	}
	for (int i = 1; i <= zombie_sum; i++) { //生成僵尸
		zombie[i].x = rand() % (n + 1), zombie[i].y = rand() % (n + 1);
		if (zombie[i].x == 0) zombie[i].x++;
		if (zombie[i].y == 0) zombie[i].y++;
		if (zombie[i].x == n - 1) zombie[i].x--;
		if (zombie[i].y == n - 1) zombie[i].y--;
		overworld[zombie[i].x][zombie[i].y] = 9;
		zombie[i].health = 3;
	}
	for (int i = 1; i <= skeleton_sum; i++) { //生成骷髅
		skeleton[i].x = rand() % (n + 1), skeleton[i].y = rand() % (n + 1);
		if (skeleton[i].x == 0) skeleton[i].x++;
		if (skeleton[i].y == 0) skeleton[i].y++;
		if (skeleton[i].x == n - 1) skeleton[i].x--;
		if (skeleton[i].y == n - 1) skeleton[i].y--;
		overworld[skeleton[i].x][skeleton[i].y] = 14;
		skeleton[i].health = 3;
	}
	for (int i = 1; i <= arrow_sum; i++) {
		arrow[i].x = 0, arrow[i].y = 0;
	}
	x = 2, y = 2;
	overworld[x][y] = 10;
	overworld[n - 1][n - 1] = 11;
}
void generation_world_nether() {
	int nether_mid;
	if (n % 2 == 0) nether_mid = n / 2;
	else if (n % 2 == 1) nether_mid = (n + 1) / 2;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == nether_mid - 1 || i == nether_mid || i == nether_mid + 1 || j == nether_mid - 1 || j == nether_mid || j == nether_mid + 1) {
				nether[i][j] = 1;
			} else {
				nether[i][j] = 0;
			}
		}
	}
	nether[1][1] = 3;
	x = 1, y = 2;
	nether[x][y] = 2;
	nether[nether_mid][nether_mid] = 4;
	if (n < 10) lava_zombie_sum = 1;
	else lava_zombie_sum = 2;
	for (int i = 1; i <= lava_zombie_sum; i++) {
		lava_zombie[i].x = rand() % 3 + nether_mid - 1;
		lava_zombie[i].y = rand() % 3 + nether_mid - 1;
		if (lava_zombie[i].x == nether_mid && lava_zombie[i].y == nether_mid) {
			lava_zombie[i].x++;
		}
		lava_zombie[i].health = 5;
		nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_5;
	}
	if (n < 10) burn_skeleton_sum = 1;
	else burn_skeleton_sum = 2;
	for (int i = 1; i <= burn_skeleton_sum; i++) {
		burn_skeleton[i].x = rand() % 3 + nether_mid - 1;
		burn_skeleton[i].y = rand() % (nether_mid - 2) + 1;
		burn_skeleton[i].health = 5;
		nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_5;
	}
	if (n < 10) blaze_sum = 1;
	else blaze_sum = 2;
	for (int i = 1; i <= blaze_sum; i++) {
		blaze[i].x = rand() % 3 + nether_mid - 1;
		blaze[i].y = rand() % (nether_mid - 2) + 1 + nether_mid + 1;
		blaze[i].health = 5;
		nether[blaze[i].x][blaze[i].y] = BLAZE_5;
	}
}
