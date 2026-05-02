#include "./Lib/game.h"
#include "./Lib/entity.h"
#include "./Lib/map.h"
#include "./Lib/ui.h"
using namespace std;
int n, inventory[500], x, y, facing, money = 0, health = 20, hunger = 20, hunger_step_summary = 0, biome_fest;
int overworld[N][N];
int nether[N][N];
int direction_x[4] = {0, 1, 0, -1};
int direction_y[4] = {1, 0, -1, 0};
int allow_command, is_regeneration_world, keepInventory, burn_time = 0, gamemode;
int vis[N][N], advencements[105], flag = 0, portal_status = 0, debug_screen = 0, nether_return = 0;
int item_prize[30] = {1, 5, 100, 100, 200, 300, 1000, 5000, 100000, 500000, 300000, 0, 0, 10, 0, 100000, 200000, 0, 0, 0, 0};
char key_binding[30] = {
	'd', 's', 'a', 'w', 13, 'o', 'k', 'u', 'e', 'q', '/', '1', 'p'
};

int zombie_sum, skeleton_sum, lava_zombie_sum, burn_skeleton_sum, arrow_sum, burn_arrow_sum, blaze_sum, fire_charge_sum;
MobData zombie[MAXN_MOB], skeleton[MAXN_MOB];
MobData lava_zombie[MAXN_MOB], burn_skeleton[MAXN_MOB], blaze[MAXN_MOB];
MobData arrow[MAXN_MOB], burn_arrow[MAXN_MOB], fire_charge[MAXN_MOB];

vector < mssg > message_list;

string death_message = "";
string Blue_slogan[11] = {
	"The Next Level!It's the Nether!",
	"Will you open chests again?",
	"Open Chests,kill Mobs!",
	"Made By hezhibao!",
	"Canary Made By ZycNotFound!",
	"Publicize By kaikaikaihuaya!",
	"Inspiration By Heletong!",
	"Noooooooooooo!I want to play CHESTS IN THE MAPS!",
	"Where is the door???",
	"There's a chest!",
	"The colorful world!"
};
string biome[10] = {
	"chest:Overworld",
	"chest:Nether",
	"chest:Nether Fortress"
};
int skin_color;
char skin_char;

map< int, char > num_to_char_print_map{
	{0, ' '},
	{1, ' '},
	{2, ' '},
	{3, ' '},
	{4, ' '},
	{5, 'W'},
	{6, 'W'},
	{7, 'W'},
	{8, 'C'},
	{9, 'Z'},
	{10, skin_char},
	{11, 'D'},
	{12, '2'},
	{13, '1'},
	{14, 'S'},
	{15, '2'},
	{16, '1'},
	{17, 'A'},
	{18, 'D'}
}, num_to_char_print_map_nether{
	{0, ' '},
	{1, 'N'},
	{2, skin_char},
	{3, 'D'},
	{4, 'C'},
	{5, 'Z'},
	{6, '4'},
	{7, '3'},
	{8, '2'},
	{9, '1'},
	{10, 'S'},
	{11, '4'},
	{12, '3'},
	{13, '2'},
	{14, '1'},
	{15, 'A'},
	{16, 'B'},
	{17, '4'},
	{18, '3'},
	{19, '2'},
	{20, '1'},
	{21, 'F'}
};
map< int, int > block_color = {
	{0, 0xF0},
	{1, 0xF0},
	{2, 0xF0},
	{3, 0xF0},
	{4, 0xF0},
	{5, 0xCF},
	{6, 0xCF},
	{7, 0xCF},
	{8, 0xE0},
	{9, 0xAF},
	{10, skin_color},
	{11, 0x80},
	{12, 0xAF},
	{13, 0xAF},
	{14, 0xF0},
	{15, 0xF0},
	{16, 0xF0},
	{17, 0xF0},
	{18, 0x50}
};
map< int, int > block_color_nether{
	{0, 0xC0},
	{1, 0x0C},
	{2, skin_color},
	{3, 0x50},
	{4, 0xE0},
	{5, 0x45},
	{6, 0x45},
	{7, 0x45},
	{8, 0x45},
	{9, 0x45},
	{10, 0x08},
	{11, 0x08},
	{12, 0x08},
	{13, 0x08},
	{14, 0x08},
	{15, 0x0F},
	{16, 0x64},
	{17, 0x64},
	{18, 0x64},
	{19, 0x64},
	{20, 0x64},
	{21, 0x60}
};
map< string, int > item{
	{"chest:cobblestone", 0},
	{"chest:coal", 1},
	{"chest:iron_ingot", 2},
	{"chest:gold_ingot", 3},
	{"chest:redstone", 4},
	{"chest:lapis", 5},
	{"chest:emerald", 6},
	{"chest:diamond", 7},
	{"chest:ender_pearl", 8},
	{"chest:health_potion", 9},
	{"chest:splash_hurt_potion", 10},
	{"chest:rotten_flesh", 11},
	{"chest:bone", 12},
	{"chest:bread", 13},
	{"chest:flint_and_steel", 14},
	{"chest:nether_quartz", 15},
	{"chest:glowstone", 16},
	{"chest:tape_happy_chests", 17},
	{"chest:tape_stressful", 18},
	{"chest:tape_lava_zombie", 19},
	{"chest:end_key", 20}
};
map< string, int > block_overworld{
	{"chest:dirt", 0},
	{"chest:wall", 5},
	{"chest:chest", 8},
	{"chest:zombie_3", 9},
	{"chest:player", 10},
	{"chest:door", 11},
	{"chest:zombie_2", 12},
	{"chest:zombie_1", 13},
	{"chest:skeleton_3", 14},
	{"chest:skeleton_2", 15},
	{"chest:skeleton_1", 16},
	{"chest:arrow", 17},
	{"chest:nether_door_overworld", 18}
};
map< string, int > block_nether{
	{"chest:nether_stone", 0},
	{"chest:nether_brick", 1},
	{"chest:nether_player", 2},
	{"chest:nether_door_nether", 3},
	{"chest:nether_chest", 4},
	{"chest:lava_zombie_5", 5},
	{"chest:lava_zombie_4", 6},
	{"chest:lava_zombie_3", 7},
	{"chest:lava_zombie_2", 8},
	{"chest:lava_zombie_1", 9},
	{"chest:burn_skeleton_1", 10},
	{"chest:burn_skeleton_2", 11},
	{"chest:burn_skeleton_3", 12},
	{"chest:burn_skeleton_4", 13},
	{"chest:burn_skeleton_5", 14},
	{"chest:burn_arrow", 15},
	{"chest:blaze_5", 16},
	{"chest:blaze_4", 17},
	{"chest:blaze_3", 18},
	{"chest:blaze_2", 19},
	{"chest:blaze_1", 20},
	{"chest:fire_charge", 21}
};

bool in(int x, int y) {
	return (x >= 1 && x <= n && y >= 1 && y <= n);
}
void checkRoad(int x, int y) { //检测是否有路
	if (x == n - 1 && y == n - 1) {
		flag = 1;
		return ;
	}
	if (overworld[x][y] > 5) {
		return ;
	}
	vis[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int tx = x + direction_x[i], ty = y + direction_y[i];
		if (in(tx, ty) && (overworld[tx][ty] < 5 || overworld[tx][ty] == 11) && vis[tx][ty] == 0) {
			checkRoad(tx, ty);
		}
	}
	return ;
}
int nether_block_check(int nether_x, int nether_y) {
	int nether_mid;
	if (n % 2 == 0) nether_mid = n / 2;
	else if (n % 2 == 1) nether_mid = (n + 1) / 2;
	if ((nether_x >= nether_mid - 1 && nether_x <= nether_mid + 1) || (nether_y >= nether_mid - 1 && nether_y <= nether_mid + 1)) {
		return NETHER_BRICK;
	} else {
		return NETHER_STONE;
	}
}

void game_nether(int regeneration) {
	system("cls");
	system("color 0C");
	system("color 5F");
	printf("\n\n\n\n\n\n                                                  下载地形中...");
	Sleep(3000);
	system("cls");
	system("color 0C");
	if (regeneration == 1) generation_world_nether();
	while (1) {
		if (gamemode == 1) health = 20, hunger = 20, fill(inventory, inventory + 500, 1);
		for (int i = 1; i <= lava_zombie_sum; i++) {
			if (lava_zombie[i].health == 5) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_5;
			else if (lava_zombie[i].health == 4) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_4;
			else if (lava_zombie[i].health == 3) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_3;
			else if (lava_zombie[i].health == 2) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_2;
			else if (lava_zombie[i].health == 1) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_1;
		}
		for (int i = 1; i <= burn_skeleton_sum; i++) {
			if (burn_skeleton[i].health == 5) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_5;
			else if (burn_skeleton[i].health == 4) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_4;
			else if (burn_skeleton[i].health == 3) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_3;
			else if (burn_skeleton[i].health == 2) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_2;
			else if (burn_skeleton[i].health == 1) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_1;
		}
		for (int i = 1; i <= burn_arrow_sum; i++) {
			nether[burn_arrow[i].x][burn_arrow[i].y] = BURN_ARROW;
		}
		for (int i = 1; i <= blaze_sum; i++) {
			if (blaze[i].health == 5) nether[blaze[i].x][blaze[i].y] = BLAZE_5;
			else if (blaze[i].health == 4) nether[blaze[i].x][blaze[i].y] = BLAZE_4;
			else if (blaze[i].health == 3) nether[blaze[i].x][blaze[i].y] = BLAZE_3;
			else if (blaze[i].health == 2) nether[blaze[i].x][blaze[i].y] = BLAZE_2;
			else if (blaze[i].health == 1) nether[blaze[i].x][blaze[i].y] = BLAZE_1;
		}
		for (int i = 1; i <= fire_charge_sum; i++) {
			nether[fire_charge[i].x][fire_charge[i].y] = FIRE_CHARGE;
		}
		if (burn_time > 0) { //燃烧
			burn_time--, health--;
			if (health <= 0) {
				death_message = "You were burn to death.";
			}
		}
		if (hunger_step_summary == 10) { //更新饱食度
			hunger--, hunger_step_summary = 0;
		}
		if (hunger == 20) {
			health++;
			health = min(health, 20);
		}
		if (hunger == 0) {
			health--;
			if (health <= 0) {
				death_message = "You starved to death.";
			}
		}
		if (health <= 0) {
			if (advencements[5] == 0) {
				advencements[5] = 1;
				printf("玩家获得了进度");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
				printf("[哦，不！！！]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
				printf("!\n");
				Sleep(2000);
				system("cls");
			}
			if (gamemode != 2) {
				if (keepInventory == 0) {
					memset(inventory, 0, sizeof(inventory));
					money = 0;
				}
				health = 20;
				nether[x][y] = 0;
				system("cls");
				system("color CF");
				printf("\n\n\n\n\n\n\n");
				printf("                                    你死了！\n\n\n");
				printf("                        ");
				cout << death_message;
				printf("\n\n\n");
				int die_select;
				printf("                      [0]退出游戏 [1]重生 [2]返回标题屏幕");
				burn_arrow_sum = 0;
				for (int i = 1; i <= burn_arrow_sum; i++) {
					burn_arrow[i].x = 0, burn_arrow[i].y = 0;
				}
				portal_status = 0;
				cin >> die_select;
				if (die_select == 0) {
					exit(0);
				}
				if (die_select == 1) {
					system("color 03");
					break;
				}
				if (die_select == 2) {
					system("cls");
					exit(0);
				}
			} else if (gamemode == 2) {
				system("cls");
				system("color CF");
				printf("\n\n\n\n\n\n\n");
				printf("                               你死了，游戏结束！\n\n\n");
				printf("                        ");
				cout << death_message;
				printf("\n\n\n");
				printf("                       [0]退出游戏并删除世界 [1]观察世界");
				int die_select;
				cin >> die_select;
				if (die_select == 0) {
					system("del chest-game-data.dat");
					nether_return = 1;
					return ;
				} else {
					system("cls");
					system("color 0C");
					print_map_Nether();
					system("pause");
					system("del chest-game-data.dat");
					nether_return = 1;
					return ;
				}
			}
		}
		if (x == 1 && y == 1) {
			system("color 5F");
			printf("\n\n\n\n\n\n                                                  下载地形中...");
			Sleep(3000);
			system("cls");
			system("color 03");
			x = 2, y = 2;
			return ;
		}
		if (nether_block_check(x, y) == NETHER_BRICK) {
			biome_fest = 2;
		}
		update_mobs_nether();
		print_map_Nether();
		if (advencements[7] == 0) {
			advencements[7] = 1;
			printf("玩家获得了进度");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
			printf("[勇闯下界]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
			printf("!\n");
			Sleep(2000);
		}
		check_attack_nether();
		biome_fest = 1;
		nether[x][y] = 2;
		char todo = getch();
		if (todo == key_binding[0] || todo == key_binding[1] || todo == key_binding[2] || todo == key_binding[3]) {
			int goX = x, goY = y;
			if (todo == key_binding[0]) goY++, facing = 0;
			if (todo == key_binding[1]) goX++, facing = 1;
			if (todo == key_binding[2]) goY--, facing = 2;
			if (todo == key_binding[3]) goX--, facing = 3;
			if (in(goX, goY) && (nether[goX][goY] == 0 || nether[goX][goY] == 1 || nether[goX][goY] == 3)) {
				nether[goX][goY] = 2;
				nether[x][y] = nether_block_check(x, y);
				x = goX, y = goY;
				hunger_step_summary++;
			}
		} else if (todo == key_binding[4]) {
			int game_menu_return_val = game_menu();
			if (game_menu_return_val == 1) {
				nether_return = 1;
				return ;
			}
		} else if (todo == key_binding[5]) {
			int goX, goY;
			goX = x, goY = y;
			if (facing == 0) goY++, facing = 0;
			if (facing == 1) goX++, facing = 1;
			if (facing == 2) goY--, facing = 2;
			if (facing == 3) goX--, facing = 3;
			if (in(goX, goY) && (abs(goX - x) < 2 && abs(goY - y) < 2) && nether[goX][goY] == 4) {
				chest_nether();
				nether[goX][goY] = nether_block_check(goX, goY);
			}
		} else if (todo == key_binding[11]) {
			debug_screen = !debug_screen;
		} else if (todo == key_binding[6]) {
			for (int dir = 0; dir < 4; dir++) {
				int attack_x = x + direction_x[dir], attack_y = y + direction_y[dir];
				for (int i = 1; i <= lava_zombie_sum; i++) {
					if (attack_x == lava_zombie[i].x && attack_y == lava_zombie[i].y) {
						lava_zombie[i].health--;
						if (nether[attack_x][attack_y] == LAVA_ZOMBIE_5) nether[attack_x][attack_y] = LAVA_ZOMBIE_4;
						else if (nether[attack_x][attack_y] == LAVA_ZOMBIE_4) nether[attack_x][attack_y] = LAVA_ZOMBIE_3;
						else if (nether[attack_x][attack_y] == LAVA_ZOMBIE_3) nether[attack_x][attack_y] = LAVA_ZOMBIE_2;
						else if (nether[attack_x][attack_y] == LAVA_ZOMBIE_2) nether[attack_x][attack_y] = LAVA_ZOMBIE_1;
						else if (nether[attack_x][attack_y] == LAVA_ZOMBIE_1) {
							nether[lava_zombie[i].x][lava_zombie[i].y] = nether_block_check(lava_zombie[i].x, lava_zombie[i].y);
							int getZombieMeat = rand() % 5, getGoldIngot = rand() % 2;
							lava_zombie[i].x = 0, lava_zombie[i].y = 0;
							message_list.push_back({"玩家击杀了熔岩僵尸,获取腐肉*" + to_string(getZombieMeat) +",金锭*" + to_string(getGoldIngot), 3});
							inventory[11] += getZombieMeat;
							inventory[3] += getGoldIngot;
							Sleep(1000);
							if (advencements[1] == 0) {
								advencements[1] = 1;
								printf("玩家获得了进度");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
								printf("[小小怪物，轻松拿捏]");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
								printf("!\n");
								Sleep(2000);
							}
						}
					}
				}
				for (int i = 1; i <= burn_skeleton_sum; i++) {
					if (attack_x == burn_skeleton[i].x && attack_y == burn_skeleton[i].y) {
						burn_skeleton[i].health--;
						if (nether[attack_x][attack_y] == BURN_SKELETON_5) nether[attack_x][attack_y] = BURN_SKELETON_4;
						else if (nether[attack_x][attack_y] == BURN_SKELETON_4) nether[attack_x][attack_y] = BURN_SKELETON_3;
						else if (nether[attack_x][attack_y] == BURN_SKELETON_3) nether[attack_x][attack_y] = BURN_SKELETON_2;
						else if (nether[attack_x][attack_y] == BURN_SKELETON_2) nether[attack_x][attack_y] = BURN_SKELETON_1;
						else if (nether[attack_x][attack_y] == BURN_SKELETON_1) {
							nether[burn_skeleton[i].x][burn_skeleton[i].y] = nether_block_check(burn_skeleton[i].x, burn_skeleton[i].y);
							int getBone = rand() % 5, getFlintAndSteel = rand() % 2;
							burn_skeleton[i].x = 0, burn_skeleton[i].y = 0;
							message_list.push_back({"玩家击杀了燃烧骷髅,获取骨头*" + to_string(getBone) + ",打火石*" + to_string(getFlintAndSteel), 3});
							inventory[12] += getBone;
							inventory[14] += getFlintAndSteel;
							Sleep(1000);
							if (advencements[1] == 0) {
								advencements[1] = 1;
								printf("玩家获得了进度");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
								printf("[小小怪物，轻松拿捏]");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
								printf("!\n");
								Sleep(2000);
							}
						}
					}
				}
				for (int i = 1; i <= blaze_sum; i++) {
					if (attack_x == blaze[i].x && attack_y == blaze[i].y) {
						blaze[i].health--;
						if (nether[attack_x][attack_y] == BLAZE_5) nether[attack_x][attack_y] = BLAZE_4;
						else if (nether[attack_x][attack_y] == BLAZE_4) nether[attack_x][attack_y] = BLAZE_3;
						else if (nether[attack_x][attack_y] == BLAZE_3) nether[attack_x][attack_y] = BLAZE_2;
						else if (nether[attack_x][attack_y] == BLAZE_2) nether[attack_x][attack_y] = BLAZE_1;
						else if (nether[attack_x][attack_y] == BLAZE_1) {
							nether[blaze[i].x][blaze[i].y] = nether_block_check(blaze[i].x, blaze[i].y);
							int getEndKey = rand() % 10, getFlintAndSteel = rand() % 2;
							if(getEndKey == 0) getEndKey = 1;
							else getEndKey = 0;
							blaze[i].x = 0, blaze[i].y = 0;
							message_list.push_back({"玩家击杀了烈焰人,获取末地钥匙*" + to_string(getFlintAndSteel) + ",打火石*" + to_string(getEndKey), 3});
							inventory[20] += getEndKey;
							inventory[14] += getFlintAndSteel;
							Sleep(1000);
							if (advencements[1] == 0) {
								advencements[1] = 1;
								printf("玩家获得了进度");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
								printf("[小小怪物，轻松拿捏]");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
								printf("!\n");
								Sleep(2000);
							}
							if (advencements[9] == 0) {
								advencements[9] = 1;
								printf("玩家获得了进度");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
								printf("[与火共舞]");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
								printf("!\n");
								Sleep(2000);
							}
						}
					}
				}
			}
		} else if (todo == key_binding[8]) {
			view_inventory();
		} else if (todo == key_binding[9]) {
			eatFood();
		} else if (todo == key_binding[4]) {
			nether_return = 1;
			return ;
		} else if (todo == key_binding[10] && allow_command == 1) {
			command();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		} else if (todo == key_binding[10] && allow_command == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
			printf("你没有作弊的权限!\n");
			Sleep(1000);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		} else if (todo == key_binding[7]) {
			system("cls");
			useItem_nether();
		} else if (todo == key_binding[12]) {
			view_advencements();
			system("color 0C");
		}
		system("cls");
	}
}
void game_overworld() {
	system("color 03");
	system("cls");
	printf("存档\n");
	printf("是否重建世界([0]读取存档 [1]重建世界):[ ]\b\b");
	cin >> is_regeneration_world;
	if (is_regeneration_world == 1) {
		printf("游戏选项\n");
		printf("地图大小(5-20):[  ]\b\b\b");
		cin >> n;
		n = max(5, n), n = min(20, n);
		printf("游戏模式(生存:0,创造1,极限2):[ ]\b\b");
		cin >> gamemode;
		if (gamemode < 0 || gamemode > 2) gamemode = 0;
		printf("作弊([0]否 [1]是):[ ]\b\b");
		cin >> allow_command;
		skin_char = 'Y', skin_color = 0x9F;
		num_to_char_print_map[PLAYER] = skin_char;
		num_to_char_print_map_nether[NETHER_PLAYER] = skin_char;
		block_color[PLAYER] = skin_color;
		block_color_nether[NETHER_PLAYER] = skin_color;
		generation_world();
	} else if (is_regeneration_world == 0) {
		read_game_data();
		num_to_char_print_map[PLAYER] = skin_char;
		num_to_char_print_map_nether[NETHER_PLAYER] = skin_char;
		block_color[PLAYER] = skin_color;
		block_color_nether[NETHER_PLAYER] = skin_color;
	}
	printf("游戏规则\n");
	printf("死亡后保留物品栏([0]否 [1]是):[ ]\b\b");
	scanf("%d", &keepInventory);
	system("cls");
	if (is_regeneration_world == 0 && biome_fest >= 1 && biome_fest <= 2) {
		game_nether(0);
		if (nether_return == 1) {
			write_game_data();
			return ;
		}
		system("color 03");
		generation_world();
	}
	while (1) {
		health = 20;
		hunger = 20;
		flag = 0;
//构建地图
		while (1) {
			if (gamemode == 1) health = 20, hunger = 20, fill(inventory, inventory + 500, 1);
			for (int i = 1; i <= zombie_sum; i++) { //及时渲染怪物
				if (zombie[i].health == 3) overworld[zombie[i].x][zombie[i].y] = ZOMBIE_3;
				else if (zombie[i].health == 2) overworld[zombie[i].x][zombie[i].y] = ZOMBIE_2;
				else if (zombie[i].health == 1) overworld[zombie[i].x][zombie[i].y] = ZOMBIE_1;
			}
			for (int i = 1; i <= skeleton_sum; i++) {
				if (skeleton[i].health == 3) overworld[skeleton[i].x][skeleton[i].y] = SKELETON_3;
				else if (skeleton[i].health == 2) overworld[skeleton[i].x][skeleton[i].y] = SKELETON_2;
				else if (skeleton[i].health == 1) overworld[skeleton[i].x][skeleton[i].y] = SKELETON_1;
			}
			for (int i = 1; i <= arrow_sum; i++) {
				overworld[arrow[i].x][arrow[i].y] = ARROW;
			}
			if (hunger_step_summary == 10) { //更新饱食度
				hunger--, hunger_step_summary = 0;
			}
			if (hunger == 20) {
				health++;
				health = min(health, 20);
			}
			if (hunger == 0) {
				health--;
				if (health <= 0) {
					death_message = "You starved to death.";
				}
			}
			if (health <= 0) {
				if (advencements[5] == 0) {
					advencements[5] = 1;
					printf("玩家获得了进度");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
					printf("[哦，不！！！]");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
					printf("!\n");
					Sleep(2000);
					system("cls");
				}
				if (gamemode != 2) {
					if (keepInventory == 0) {
						memset(inventory, 0, sizeof(inventory));
						money = 0;
					}
					health = 20;
					overworld[x][y] = 0;
					system("cls");
					system("color CF");
					printf("\n\n\n\n\n\n\n");
					printf("                                    你死了！\n\n\n");
					printf("                        ");
					cout << death_message;
					printf("\n\n\n");
					int die_select;
					printf("                      [0]退出游戏 [1]重生 [2]返回标题屏幕");
					arrow_sum = 0;
					for (int i = 1; i <= arrow_sum; i++) {
						arrow[i].x = 0, arrow[i].y = 0;
					}
					portal_status = 0;
					cin >> die_select;
					if (die_select == 0) {
						return ;
					}
					if (die_select == 1) {
						system("color 03");
						break;
					}
					if (die_select == 2) {
						system("cls");
						game_overworld();
						return ;
					}
				} else if (gamemode == 2) {
					system("cls");
					system("color CF");
					printf("\n\n\n\n\n\n\n");
					printf("                               你死了，游戏结束！\n\n\n");
					printf("                        ");
					cout << death_message;
					printf("\n\n\n");
					printf("                       [0]退出游戏并删除世界 [1]观察世界");
					int die_select;
					cin >> die_select;
					if (die_select == 0) {
						system("del chest-game-data.dat");
						return ;
					} else {
						system("cls");
						system("color 03");
						print_map();
						system("pause");
						system("del chest-game-data.dat");
						return ;
					}
				}
			}
			if (x == n - 1 && y == n - 1 && portal_status == 1) {
				overworld[x][y] = 0;
				arrow_sum = 0;
				for (int i = 1; i <= arrow_sum; i++) {
					arrow[i].x = 0, arrow[i].y = 0;
				}
				portal_status = 0;
				game_nether(1);
				if (nether_return == 1) {
					write_game_data();
					return ;
				}
				system("cls");
				system("color 03");
				break;
			}
			if (x == n - 1 && y == n - 1) {
				if (advencements[4] == 0) {
					advencements[4] = 1;
					printf("玩家获得了进度");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
					printf("[抵达终点]");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
					printf("!\n");
					Sleep(2000);
					system("cls");
				}
				printf("\n\n\n\n\n\n");
				printf("                           666,你到了终点!\n\n\n");
				int end_select;
				printf("                      [0]退出 [1]继续 [2]进入商店\n");
				cin >> end_select;
				arrow_sum = 0;
				memset(arrow, 0, sizeof(arrow));
				memset(arrow, 0, sizeof(arrow));
				portal_status = 0;
				if (end_select == 0) {
					return ;
				}
				if (end_select == 1) {
					x = 2, y = 2;
					break;
				}
				if (end_select == 2) {
					shop();
					x = 2, y = 2;
					break;
				}
			}
			system("cls");
			overworld[x][y] = 10;
			biome_fest = 0;
			update_mobs_overworld();
			print_map();
			check_attack_overworld();
			char todo;
			todo = getch();
			int goX = x, goY = y;
			if (todo == key_binding[0] || todo == key_binding[1] || todo == key_binding[2] || todo == key_binding[3]) {
				if (todo == key_binding[0]) goY++, facing = 0;
				if (todo == key_binding[1]) goX++, facing = 1;
				if (todo == key_binding[2]) goY--, facing = 2;
				if (todo == key_binding[3]) goX--, facing = 3;
				if (in(goX, goY) && (overworld[goX][goY] < 5 || overworld[goX][goY] == 11 || overworld[goX][goY] == 17 || overworld[goX][goY] == 18)) {
					overworld[goX][goY] = 10;
					overworld[x][y] = 0;
					x = goX, y = goY;
					hunger_step_summary++;
				}
			} else if (todo == key_binding[4]) {
				int game_menu_return_val = game_menu();
				if (game_menu_return_val == 1) {
					write_game_data();
					return ;
				}
			} else if (todo == key_binding[5]) {
				goX = x, goY = y;
				if (facing == 0) goY++, facing = 0;
				if (facing == 1) goX++, facing = 1;
				if (facing == 2) goY--, facing = 2;
				if (facing == 3) goX--, facing = 3;
				if (in(goX, goY) && (abs(goX - x) < 2 && abs(goY - y) < 2) && overworld[goX][goY] == 8) {
					chest();
					overworld[goX][goY] = 0;
					if (advencements[3] == 0) {
						advencements[3] = 1;
						printf("玩家获得了进度");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
						printf("[这是什么？箱子！]");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
						printf("!\n");
						Sleep(2000);
					}
				}
			} else if (todo == key_binding[6]) {
				for (int dir = 0; dir < 4; dir++) {
					int attack_x = x + direction_x[dir], attack_y = y + direction_y[dir];
					for (int i = 1; i <= zombie_sum; i++) {
						if (attack_x == zombie[i].x && attack_y == zombie[i].y) {
							zombie[i].health--;
							if (overworld[attack_x][attack_y] == ZOMBIE_3) overworld[attack_x][attack_y] = ZOMBIE_2;
							else if (overworld[attack_x][attack_y] == ZOMBIE_2) overworld[attack_x][attack_y] = ZOMBIE_1;
							else if (overworld[attack_x][attack_y] == ZOMBIE_1) {
								overworld[attack_x][attack_y] = DIRT;
								int getZombieMeat = rand() % 5;
								zombie[i].x = 0, zombie[i].y = 0;
								message_list.push_back({"玩家击杀了僵尸" + to_string(i) + ",获取腐肉*" + to_string(getZombieMeat), 3});
								inventory[11] += getZombieMeat;
								Sleep(1000);
								if (advencements[1] == 0) {
									advencements[1] = 1;
									printf("玩家获得了进度");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
									printf("[小小怪物，轻松拿捏]");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
									printf("!\n");
									Sleep(2000);
								}
							}
						}
					}
					for (int i = 1; i <= skeleton_sum; i++) {
						if (attack_x == skeleton[i].x && attack_y == skeleton[i].y) {
							skeleton[i].health--;
							if (overworld[attack_x][attack_y] == SKELETON_3) overworld[attack_x][attack_y] = SKELETON_2;
							else if (overworld[attack_x][attack_y] == SKELETON_2) overworld[attack_x][attack_y] = SKELETON_1;
							else if (overworld[attack_x][attack_y] == SKELETON_1) {
								overworld[attack_x][attack_y] = DIRT;
								int getBones = rand() % 4;
								skeleton[i].x = 0, skeleton[i].y = 0;
								message_list.push_back({"玩家击杀了骷髅" + to_string(i) + ",获取骨头" + to_string(getBones) + "\n", 3});
								inventory[12] += getBones;
								Sleep(1000);
								if (advencements[1] == 0) {
									advencements[1] = 1;
									printf("玩家获得了进度");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
									printf("[小小怪物，轻松拿捏]");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
									printf("!\n");
									Sleep(2000);
								}
							}
						}
					}
				}
			} else if (todo == key_binding[7]) {
				system("cls");
				useItem();
			} else if (todo == key_binding[8]) {
				view_inventory();
			} else if (todo == key_binding[9]) {
				eatFood();
			} else if (todo == key_binding[10] && allow_command == 1) {
				command();
			} else if (todo == key_binding[10] && allow_command == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
				printf("你没有作弊的权限!\n");
				Sleep(1000);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
			} else if (todo == key_binding[11]) {
				debug_screen = !debug_screen;
			} else if (todo == key_binding[12]) {
				view_advencements();
			}
			Sleep(1);
			system("cls");
		}
		generation_world();
	}
}

void read_game_data() {
	FILE *fp = fopen("chest-game-data.dat", "r");
	if (fp != NULL) {
		fscanf(fp, "Map size = %d\n", &n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fscanf(fp, "%d ", &overworld[i][j]);
			}
			fscanf(fp, "\n");
		}
		for (int i = 0; i <= 19; i++) fscanf(fp, "%d ", &inventory[i]);
		fscanf(fp, "\n");
		fscanf(fp, "Position = %d,%d (Facing:%d)\n", &x, &y, &facing);
		fscanf(fp, "Money = %d\n", &money);
		fscanf(fp, "Health = %d\n", &health);
		fscanf(fp, "Hunger = %d\n", &hunger);
		fscanf(fp, "Hunger step summary = %d\n", &hunger_step_summary);
		fscanf(fp, "Biome = %d\n", &biome_fest);
		fscanf(fp, "Zombie_sum = %d\n", &zombie_sum);
		for (int i = 1; i <= zombie_sum; i++) {
			fscanf(fp, "(%d,%d) Health = %d\n", &zombie[i].x, &zombie[i].y, &zombie[i].health);
		}
		fscanf(fp, "Skeleton_sum = %d\n", &skeleton_sum);
		for (int i = 1; i <= skeleton_sum; i++) {
			fscanf(fp, "(%d,%d) Health = %d\n", &skeleton[i].x, &skeleton[i].y, &skeleton[i].health);
		}
		fscanf(fp, "Arrow_sum = %d\n", &arrow_sum);
		for (int i = 1; i <= arrow_sum; i++) {
			fscanf(fp, "(%d,%d) Facing = %d\n", &arrow[i].x, &arrow[i].y, &arrow[i].facing);
		}
		fscanf(fp, "Advencements = ");
		for (int i = 1; i <= 8; i++) {
			fscanf(fp, "%d,", &advencements[i]);
		}
		fscanf(fp, "\n");
		fscanf(fp, "Portal status = %d\n", &portal_status);
		fscanf(fp, "Debug screen = %d\n", &debug_screen);
		fscanf(fp, "Allow command = %d\n", &allow_command);
		fscanf(fp, "Gamemode = %d\n", &gamemode);
		if (nether_return == 1) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					fscanf(fp, "%d ", &nether[i][j]);
				}
				fscanf(fp, "\n");
			}
			fscanf(fp, "Lava_zombie_sum = %d\n", &lava_zombie_sum);
			for (int i = 1; i <= lava_zombie_sum; i++) {
				fscanf(fp, "(%d,%d) health = %d\n", &lava_zombie[i].x, &lava_zombie[i].y, &lava_zombie[i].health);
			}
			fscanf(fp, "Burn_skeleton_sum = %d\n", &burn_skeleton_sum);
			for (int i = 1; i <= burn_skeleton_sum; i++) {
				fscanf(fp, "(%d,%d) Health = %d\n", &burn_skeleton[i].x, &burn_skeleton[i].y, &burn_skeleton[i].health);
			}
			fscanf(fp, "Blaze_sum = %d\n", &blaze_sum);
			for (int i = 1; i <= blaze_sum; i++) {
				fscanf(fp, "(%d,%d) Health = %d\n", &blaze[i].x, &blaze[i].y, &blaze[i].health);
			}
			fscanf(fp, "Burn_arrow_sum = %d\n", &burn_arrow_sum);
			for (int i = 1; i <= burn_arrow_sum; i++) {
				fscanf(fp, "(%d,%d) Facing = %d\n", &burn_arrow[i].x, &burn_arrow[i].y, &burn_arrow[i].facing);
			}
		}
		if (fclose(fp) == 0) {
			
		} else {
			perror("Close File Failed."); // 输出错误信息
		}
	}
	FILE *fp_skin = fopen("skin.txt", "r");
	if (fp_skin != NULL) {
		fscanf(fp_skin, "%x\n%c", &skin_color, &skin_char);
		if (fclose(fp_skin) == 0) {
			
		} else {
			perror("Close File Failed.");
		}
	}
}
void write_game_data() {
	if (health <= 0 && gamemode == 2) {
		return ;
	}
	system("del chest-game-data.dat");
	FILE *fl = fopen("chest-game-data.dat", "w");
	if (fl != NULL) {
		fprintf(fl, "Map size = %d\n", n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fprintf(fl, "%d ", overworld[i][j]);
			}
			fprintf(fl, "\n");
		}
		for (int i = 0; i <= 19; i++) fprintf(fl, "%d ", inventory[i]);
		fprintf(fl, "\n");
		fprintf(fl, "Position = %d,%d (Facing:%d)\n", x, y, facing);
		fprintf(fl, "Money = %d\n", money);
		fprintf(fl, "Health = %d\n", health);
		fprintf(fl, "Hunger = %d\n", hunger);
		fprintf(fl, "Hunger step summary = %d\n", hunger_step_summary);
		fprintf(fl, "Biome = %d\n", biome_fest);
		fprintf(fl, "Zombie_sum = %d\n", zombie_sum);
		for (int i = 1; i <= zombie_sum; i++) {
			fprintf(fl, "(%d,%d) Health = %d\n", zombie[i].x, zombie[i].y, zombie[i].health);
		}
		fprintf(fl, "Skeleton_sum = %d\n", skeleton_sum);
		for (int i = 1; i <= skeleton_sum; i++) {
			fprintf(fl, "(%d,%d) Health = %d\n", skeleton[i].x, skeleton[i].y, skeleton[i].health);
		}
		fprintf(fl, "Arrow_sum = %d\n", arrow_sum);
		for (int i = 1; i <= arrow_sum; i++) {
			fprintf(fl, "(%d,%d) Facing = %d\n", arrow[i].x, arrow[i].y, arrow[i].facing);
		}
		fprintf(fl, "Advencements = ");
		for (int i = 1; i <= 8; i++) {
			int temp;
			if (advencements[i] == 1) temp = 1;
			else temp = 0;
			fprintf(fl, "%d,", temp);
		}
		fprintf(fl, "\n");
		fprintf(fl, "Portal status = %d\n", portal_status);
		fprintf(fl, "Debug screen = %d\n", debug_screen);
		fprintf(fl, "Allow command = %d\n", allow_command);
		fprintf(fl, "Gamemode = %d\n", gamemode);
		if (nether_return == 1) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					fprintf(fl, "%d ", nether[i][j]);
				}
				fprintf(fl, "\n");
			}
			fprintf(fl, "Lava_zombie_sum = %d\n", lava_zombie_sum);
			for (int i = 1; i <= lava_zombie_sum; i++) {
				fprintf(fl, "(%d,%d) health = %d\n", lava_zombie[i].x, lava_zombie[i].y, lava_zombie[i].health);
			}
			fprintf(fl, "Burn_skeleton_sum = %d\n", burn_skeleton_sum);
			for (int i = 1; i <= burn_skeleton_sum; i++) {
				fprintf(fl, "(%d,%d) Health = %d\n", burn_skeleton[i].x, burn_skeleton[i].y, burn_skeleton[i].health);
			}
			fprintf(fl, "Blaze_sum = %d\n", blaze_sum);
			for (int i = 1; i <= blaze_sum; i++) {
				fprintf(fl, "(%d,%d) Health = %d\n", blaze[i].x, blaze[i].y, blaze[i].health);
			}
			fprintf(fl, "Burn_arrow_sum = %d\n", burn_arrow_sum);
			for (int i = 1; i <= burn_arrow_sum; i++) {
				fprintf(fl, "(%d,%d) Facing = %d\n", burn_arrow[i].x, burn_arrow[i].y, burn_arrow[i].facing);
			}
		}
		if (fclose(fl) == 0) {
			
		} else {
			perror("Close File Failed."); // 输出错误信息
		}
	}
	FILE *fl_skin = fopen("skin.txt", "w");
	if (fl_skin != NULL) {
		fprintf(fl_skin, "%x", skin_color);
		fprintf(fl_skin, "%c", skin_char);
		if (fclose(fl_skin) == 0) {
			
		} else {
			perror("Close File Failed.");
		}
	}
}
