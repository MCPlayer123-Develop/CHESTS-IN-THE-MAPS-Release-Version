#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<algorithm>
#include<fstream>
#include<map>
#include<ctime>
#include<cstring>
#include<cmath>
#include<vector>
#include<cstdlib>
using namespace std;
const int N = 55, MAXN_MOB = 20 * 20 + 100;
extern int n, inventory[500], x, y, facing, money, health, hunger, hunger_step_summary, biome_fest;
extern int overworld[N][N];
extern int nether[N][N];
extern int direction_x[4];
extern int direction_y[4];
extern int allow_command, is_regeneration_world, keepInventory, burn_time, gamemode;
extern int vis[N][N], advencements[105], flag, portal_status, debug_screen, nether_return;
extern int item_prize[30];
extern string world_name;
extern char key_binding[30];

struct MobData {
	int x, y, health, facing;
};
extern int zombie_sum, skeleton_sum, lava_zombie_sum, burn_skeleton_sum, arrow_sum, burn_arrow_sum, blaze_sum, fire_charge_sum;
extern MobData zombie[MAXN_MOB], skeleton[MAXN_MOB];
extern MobData lava_zombie[MAXN_MOB], burn_skeleton[MAXN_MOB], blaze[MAXN_MOB];
extern MobData arrow[MAXN_MOB], burn_arrow[MAXN_MOB], fire_charge[MAXN_MOB];
struct mssg {
	string message;
	int tim;
	int color[100005];
};
extern vector < mssg > message_list;

extern string death_message;
extern string Blue_slogan[11];
extern string biome[10];
extern int skin_color;
extern char skin_char;

extern map<int, char> num_to_char_print_map, num_to_char_print_map_nether;
extern map<int, int> block_color, block_color_nether;
extern map<string, int> item, block_overworld, block_nether;
extern map<string, int> statistics;
extern map<int, string> statistics_name;

extern vector<string> getAllDatSave();

enum blocks_overworld {
	DIRT = 0,
	WALL = 5,
	CHEST = 8,
	ZOMBIE_3 = 9,
	PLAYER = 10,
	DOOR = 11,
	ZOMBIE_2 = 12,
	ZOMBIE_1 = 13,
	SKELETON_3 = 14,
	SKELETON_2 = 15,
	SKELETON_1 = 16,
	ARROW = 17,
	NETHER_PORTAL_OVERWORLD = 18
};
enum blocks_nether {
	NETHER_STONE = 0,
	NETHER_BRICK = 1,
	NETHER_PLAYER = 2,
	NETHER_PORTAL_NETHER = 3,
	NETHER_CHEST = 4,
	LAVA_ZOMBIE_5 = 5,
	LAVA_ZOMBIE_4 = 6,
	LAVA_ZOMBIE_3 = 7,
	LAVA_ZOMBIE_2 = 8,
	LAVA_ZOMBIE_1 = 9,
	BURN_SKELETON_5 = 10,
	BURN_SKELETON_4 = 11,
	BURN_SKELETON_3 = 12,
	BURN_SKELETON_2 = 13,
	BURN_SKELETON_1 = 14,
	BURN_ARROW = 15,
	BLAZE_5 = 16,
	BLAZE_4 = 17,
	BLAZE_3 = 18,
	BLAZE_2 = 19,
	BLAZE_1 = 20,
	FIRE_CHARGE = 21
};

bool in(int x, int y);
void checkRoad(int x, int y);
int nether_block_check(int nether_x, int nether_y);
void mobs_find_way();

void game_overworld();
void game_nether(int regeneration);

void read_game_data();
void write_game_data();

void eggs_mcplayer123();

#endif
