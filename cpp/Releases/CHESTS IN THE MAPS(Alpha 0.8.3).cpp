#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<algorithm>
#include<fstream>
#include<map>
#define INF 0x3f3f3f3f
using namespace std;
const int N = 55, MAXN_MOB = 20 * 20 + 100;
int n, inventory[30], x, y, fx, money = 0, hp = 20, full = 20, step = 0, Biome_Fest;
int overworld[N][N];
int nether[N][N];
int cx[4] = {0, 1, 0, -1};
int cy[4] = {1, 0, -1, 0};
int is_order, is_rebuild, keepInventory, burn_time = 0, gamemode;
bool vis[N][N], progress[105], flag = 0, is_act_door = 0, is_debug = 0, is_first_level = 1, nether_return = 0;
int thingMoney[30] = {1, 5, 100, 100, 200, 300, 1000, 5000, 100000, 500000, 300000, 0, 0, 10, 0, 100000, 200000, 0, 0, 0, 0};

struct MobData {
	int x, y, hp, facing;
};
int zombie_sum, skeleton_sum, lava_zombie_sum, burn_skeleton_sum, arrow_sum, burn_arrow_sum, blaze_sum, fire_charge_sum;
MobData zombie[MAXN_MOB], skeleton[MAXN_MOB];
MobData lava_zombie[MAXN_MOB], burn_skeleton[MAXN_MOB], blaze[MAXN_MOB];
MobData arrow[MAXN_MOB], burn_arrow[MAXN_MOB], fire_charge[MAXN_MOB];

string died_Information = "";
string Blue_slogan[11] {
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
bool in(int x, int y) {
	return (x >= 1 && x <= n && y >= 1 && y <= n);
}
map< int, char > num_to_char_mp{
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
}, num_to_char_mp_nether{
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
	{"chest:carrion", 11},
	{"chest:bone", 12},
	{"chest:bread", 13},
	{"chest:flint_and_steel", 14},
	{"chest:nether_quartz", 15},
	{"chest:glowstone", 16},
	{"chest:tape_happy_chests", 17},
	{"chest:tape_stressful", 18},
	{"chest:tape_lava_zombie", 19}
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
	{"chest:lava_zomibe_1", 9},
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
	NETHER_DOOR_OVERWORLD = 18
};
enum blocks_nether {
	NETHER_STONE = 0,
	NETHER_BRICK = 1,
	NETHER_PLAYER = 2,
	NETHER_DOOR_NETHER = 3,
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
void read_dat() {
	FILE *fp = fopen("chest-game-data.dat", "r");
	if (fp != NULL) {
		fscanf(fp, "map size = %d\n", &n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fscanf(fp, "%d ", &overworld[i][j]);
			}
			fscanf(fp, "\n");
		}
		for (int i = 0; i <= 19; i++) fscanf(fp, "%d,", &inventory[i]);
		fscanf(fp, "\n");
		fscanf(fp, "Coordinate = %d,%d(Direction:%d)\n", &x, &y, &fx);
		fscanf(fp, "money = %d\n", &money);
		fscanf(fp, "hp = %d\n", &hp);
		fscanf(fp, "full = %d\n", &full);
		fscanf(fp, "step = %d\n", &step);
		fscanf(fp, "biome = %d\n", &Biome_Fest);
		fscanf(fp, "zombie_sum = %d\n", &zombie_sum);
		for (int i = 1; i <= zombie_sum; i++) {
			fscanf(fp, "(%d,%d) Hp = %d\n", &zombie[i].x, &zombie[i].y, &zombie[i].hp);
		}
		fscanf(fp, "skeleton_sum = %d\n", &skeleton_sum);
		for (int i = 1; i <= skeleton_sum; i++) {
			fscanf(fp, "(%d,%d) Hp = %d\n", &skeleton[i].x, &skeleton[i].y, &skeleton[i].hp);
		}
		fscanf(fp, "arrow_sum = %d\n", &arrow_sum);
		for (int i = 1; i <= arrow_sum; i++) {
			fscanf(fp, "(%d,%d) facing = %d\n", &arrow[i].x, &arrow[i].y, &arrow[i].facing);
		}
		fscanf(fp, "progress:");
		for (int i = 1; i <= 8; i++) {
			int temp;
			fscanf(fp, "%d,", &temp);
			if (temp == 1) progress[i] = 1;
			else progress[i] = 0;
		}
		fscanf(fp, "\n");
		int temp;
		fscanf(fp, "is act door:%d\n", &temp);
		if (temp == 1) is_act_door = 1;
		else is_act_door = 0;
		fscanf(fp, "is debug:%d\n", &temp);
		if (temp == 1) is_debug = 1;
		else is_debug = 0;
		fscanf(fp, "is order:%d\n", &is_order);
		fscanf(fp, "gamemode:%d\n", &gamemode);
		if (Biome_Fest >= 1 && Biome_Fest <= 2) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					fscanf(fp, "%d ", &nether[i][j]);
				}
				fscanf(fp, "\n");
			}
			fscanf(fp, "lava_zombie_sum = %d\n", &lava_zombie_sum);
			for (int i = 1; i <= lava_zombie_sum; i++) {
				fscanf(fp, "(%d,%d) Hp = %d\n", &lava_zombie[i].x, &lava_zombie[i].y, &lava_zombie[i].hp);
			}
			fscanf(fp, "burn_skeleton_sum = %d\n", &burn_skeleton_sum);
			for (int i = 1; i <= burn_skeleton_sum; i++) {
				fscanf(fp, "(%d,%d) Hp = %d\n", &burn_skeleton[i].x, &burn_skeleton[i].y, &burn_skeleton[i].hp);
			}
			fscanf(fp, "burn_arrow_sum = %d\n", &burn_arrow_sum);
			for (int i = 1; i <= burn_arrow_sum; i++) {
				fscanf(fp, "(%d,%d) facing = %d\n", &burn_arrow[i].x, &burn_arrow[i].y, &burn_arrow[i].facing);
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
void write_dat() {
	if (hp <= 0 && gamemode == 2) {
		return ;
	}
	system("del chest-game-data.dat");
	FILE *fl = fopen("chest-game-data.dat", "w");
	if (fl != NULL) {
		fprintf(fl, "map size = %d\n", n);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fprintf(fl, "%d ", overworld[i][j]);
			}
			fprintf(fl, "\n");
		}
		for (int i = 0; i <= 19; i++) fprintf(fl, "%d,", inventory[i]);
		fprintf(fl, "\n");
		fprintf(fl, "Coordinate = %d,%d(Direction:%d)\n", x, y, fx);
		fprintf(fl, "money = %d\n", money);
		fprintf(fl, "hp = %d\n", hp);
		fprintf(fl, "full = %d\n", full);
		fprintf(fl, "step = %d\n", step);
		fprintf(fl, "biome = %d\n", Biome_Fest);
		fprintf(fl, "zombie_sum = %d\n", zombie_sum);
		for (int i = 1; i <= zombie_sum; i++) {
			fprintf(fl, "(%d,%d) Hp = %d\n", zombie[i].x, zombie[i].y, zombie[i].hp);
		}
		fprintf(fl, "skeleton_sum = %d\n", skeleton_sum);
		for (int i = 1; i <= skeleton_sum; i++) {
			fprintf(fl, "(%d,%d) Hp = %d\n", skeleton[i].x, skeleton[i].y, skeleton[i].hp);
		}
		fprintf(fl, "arrow_sum = %d\n", arrow_sum);
		for (int i = 1; i <= arrow_sum; i++) {
			fprintf(fl, "(%d,%d) facing = %d\n", arrow[i].x, arrow[i].y, arrow[i].facing);
		}
		fprintf(fl, "progress:");
		for (int i = 1; i <= 8; i++) {
			int temp;
			if (progress[i] == 1) temp = 1;
			else temp = 0;
			fprintf(fl, "%d,", temp);
		}
		fprintf(fl, "\n");
		int temp;
		if (is_act_door == 1) temp = 1;
		else temp = 0;
		fprintf(fl, "is act door:%d\n", temp);
		if (is_debug == 1) temp = 1;
		else temp = 0;
		fprintf(fl, "is debug:%d\n", temp);
		fprintf(fl, "is order:%d\n", is_order);
		fprintf(fl, "gamemode:%d\n", gamemode);
		if (nether_return == 1) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					fprintf(fl, "%d ", nether[i][j]);
				}
				fprintf(fl, "\n");
			}
			fprintf(fl, "lava_zombie_sum = %d\n", lava_zombie_sum);
			for (int i = 1; i <= lava_zombie_sum; i++) {
				fprintf(fl, "(%d,%d) Hp = %d\n", lava_zombie[i].x, lava_zombie[i].y, lava_zombie[i].hp);
			}
			fprintf(fl, "burn_skeleton_sum = %d\n", burn_skeleton_sum);
			for (int i = 1; i <= burn_skeleton_sum; i++) {
				fprintf(fl, "(%d,%d) Hp = %d\n", burn_skeleton[i].x, burn_skeleton[i].y, burn_skeleton[i].hp);
			}
			fprintf(fl, "burn_arrow_sum = %d\n", burn_arrow_sum);
			for (int i = 1; i <= burn_arrow_sum; i++) {
				fprintf(fl, "(%d,%d) facing = %d\n", burn_arrow[i].x, burn_arrow[i].y, burn_arrow[i].facing);
			}
		}
		if (fclose(fl) == 0) {
			
		} else {
			perror("Close File Failed."); // 输出错误信息
		}
	}
	FILE *fl_skin = fopen("skin.txt", "r");
	if (fl_skin != NULL) {
		fprintf(fl_skin, "%x", skin_color);
		fprintf(fl_skin, "%c", skin_char);
		if (fclose(fl_skin) == 0) {
			
		} else {
			perror("Close File Failed.");
		}
	}
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
		int tx = x + cx[i], ty = y + cy[i];
		if (in(tx, ty) && (overworld[tx][ty] < 5 || overworld[tx][ty] == 11) && vis[tx][ty] == 0) {
			checkRoad(tx, ty);
		}
	}
	return ;
}
void mp() { //输出地图
	printf(" ╔════════════════╦═══════════════╦═══════════════╗ \n");
	printf(" ║ 金钱:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	printf("%9d", money);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	printf(" ║ 生命:");
	if (hp > 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	else if (hp > 10 && hp <= 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	else if (hp <= 10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("%9d", hp);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	printf("║ 饱食度:");
	if (full > 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	else if (full > 10 && full <= 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	else if (full <= 10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("%7d", full);
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
			printf("[%c]", num_to_char_mp[overworld[i][j]]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
		}
		printf("\n");
	}
	if (is_debug == 1) {
		printf("\n");
		printf("Map size:%d\n", n);
		printf("Coordinate:(%d,%d)\n", x, y);
		printf("Direction:");
		if (fx == 0) printf("East");
		if (fx == 1) printf("South");
		if (fx == 2) printf("West");
		if (fx == 3) printf("North");
		printf("(facing:%d)\n", fx);
		printf("Biome Fest:");
		cout << biome[Biome_Fest] << endl;
		printf("Step for Full:%d\n", step);
		printf("Map dataization:\n");
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				printf("%d ", overworld[i][j]);
			}
			printf("\n");
		}
		printf("Total thing:\n");
		for (int i = 0; i < 17; i++) {
			printf("%d ", inventory[i]);
		}
		printf("\n");
		printf("Zombie Total:%d\n", zombie_sum);
		for (int i = 1; i <= zombie_sum; i++) {
			printf("Zombie Coordinate:(%d,%d) Hp:%d\n", zombie[i].x, zombie[i].y, zombie[i].hp);
		}
		printf("Skeleton Total:%d\n", skeleton_sum);
		for (int i = 1; i <= skeleton_sum; i++) {
			printf("Skeleton Coordinate:(%d,%d) Hp:%d\n", skeleton[i].x, skeleton[i].y, skeleton[i].hp);
		}
		printf("Arrow Total:%d\n", arrow_sum);
		for (int i = 1; i <= arrow_sum; i++) {
			if (arrow[i].x > 0 && arrow[i].y > 0) printf("Arrow Coordinate:(%d,%d) facing:%d\n", arrow[i].x, arrow[i].y, arrow[i].facing);
		}
	}
}
void mp_Nether() { //输出地图
	printf(" ╔════════════════╦═══════════════╦═══════════════╗ \n");
	printf(" ║ 金钱:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	printf("%9d", money);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf(" ║ 生命:");
	if (hp > 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	else if (hp > 10 && hp <= 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	else if (hp <= 10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("%9d", hp);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("║ 饱食度:");
	if (full > 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	else if (full > 10 && full <= 15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
	else if (full <= 10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("%7d", full);
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
			printf("[%c]", num_to_char_mp_nether[nether[i][j]]);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		}
		printf("\n");
	}
	if (is_debug == 1) {
		printf("\n");
		printf("Map size:%d\n", n);
		printf("Coordinate:(%d,%d)\n", x, y);
		printf("Direction:");
		if (fx == 0) printf("East");
		if (fx == 1) printf("South");
		if (fx == 2) printf("West");
		if (fx == 3) printf("North");
		printf("(facing:%d)\n", fx);
		printf("Biome Fest:");
		cout << biome[Biome_Fest] << endl;
		printf("Step for Full:%d\n", step);
		printf("Map dataization:\n");
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				printf("%d ", nether[i][j]);
			}
			printf("\n");
		}
		printf("Lava Zombie Total:%d\n", lava_zombie_sum);
		for (int i = 1; i <= lava_zombie_sum; i++) {
			printf("Lava Zombie Coordinate:(%d,%d) Hp:%d\n", lava_zombie[i].x, lava_zombie[i].y, lava_zombie[i].hp);
		}
		printf("Burn Skeleton Total:%d\n", burn_skeleton_sum);
		for (int i = 1; i <= burn_skeleton_sum; i++) {
			printf("Burn Skeleton Coordinate:(%d,%d) Hp:%d\n", burn_skeleton[i].x, burn_skeleton[i].y, burn_skeleton[i].hp);
		}
		printf("Burn Arrow Total:%d\n", burn_arrow_sum);
		for (int i = 1; i <= burn_arrow_sum; i++) {
			if (burn_arrow[i].x > 0 && burn_arrow[i].y > 0) printf("Burn Arrow Coordinate:(%d,%d) facing:%d\n", burn_arrow[i].x, burn_arrow[i].y, burn_arrow[i].facing);
		}
		printf("Total thing:\n");
		for (int i = 0; i < 17; i++) {
			printf("%d ", inventory[i]);
		}
	}
}
void make_wall(int x, int y) {
	vis[x][y] = 1;
	overworld[x][y] = rand() % 8;
	for (int i = 0; i < 4; i++) {
		int tx = x + cx[i], ty = y + cy[i];
		if (in(tx, ty) && overworld[tx][ty] == DIRT) {
			make_wall(tx, ty);
		}
	}
}
void make_world() {
	memset(overworld, DIRT, sizeof(overworld));
	memset(vis, false, sizeof(vis));
	while (1) {
		int MapX, MapY; //构建地图的起点
		MapX = rand() % (n + 1), MapY = rand() % (n + 1);
		if (MapX == 0) MapX++;
		if (MapY == 0) MapY++;
		make_wall(MapX, MapY);
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
		zombie[i].hp = 3;
	}
	for (int i = 1; i <= skeleton_sum; i++) { //生成骷髅
		skeleton[i].x = rand() % (n + 1), skeleton[i].y = rand() % (n + 1);
		if (skeleton[i].x == 0) skeleton[i].x++;
		if (skeleton[i].y == 0) skeleton[i].y++;
		if (skeleton[i].x == n - 1) skeleton[i].x--;
		if (skeleton[i].y == n - 1) skeleton[i].y--;
		overworld[skeleton[i].x][skeleton[i].y] = 14;
		skeleton[i].hp = 3;
	}
	for (int i = 1; i <= arrow_sum; i++) {
		arrow[i].x = 0, arrow[i].y = 0;
	}
	x = 2, y = 2;
	overworld[x][y] = 10;
	overworld[n - 1][n - 1] = 11;
}
void make_world_nether() {
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
		lava_zombie[i].hp = 5;
		nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_5;
	}
	if (n < 10) burn_skeleton_sum = 1;
	else burn_skeleton_sum = 2;
	for (int i = 1; i <= burn_skeleton_sum; i++) {
		burn_skeleton[i].x = rand() % 3 + nether_mid - 1;
		burn_skeleton[i].y = rand() % (nether_mid - 2) + 1;
		burn_skeleton[i].hp = 5;
		nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_5;
	}
	if (n < 10) blaze_sum = 1;
	else blaze_sum = 2;
	for (int i = 1; i <= blaze_sum; i++) {
		blaze[i].x = rand() % 3 + nether_mid - 1;
		blaze[i].y = rand() % (nether_mid - 2) + 1 + nether_mid + 1;
		blaze[i].hp = 5;
		nether[blaze[i].x][blaze[i].y] = BLAZE_5;
	}
}
void chest() { //开箱子
	system("cls");
	printf("箱子\n");
	printf("╔═══════════════════════╗ \n");
	for (int i = 0; i < 8; i++) {
		int Item_Total;
		if (i == 1) {
			Item_Total = rand() % 64;
		}
		if (i <= 3) {
			Item_Total = rand() % 20;
		}
		if (i > 3 && i <= 5) {
			Item_Total = rand() % 10;
		}
		if (i > 5) {
			Item_Total = rand() % 3;
		}
		if (i == 0) printf("║ 原石:%2d               ║ ", Item_Total), inventory[0] += Item_Total;
		if (i == 1) printf("║ 煤炭:%2d               ║ ", Item_Total), inventory[1] += Item_Total;
		if (i == 2) printf("║ 铁锭:%2d               ║ ", Item_Total), inventory[2] += Item_Total;
		if (i == 3) printf("║ 金锭:%2d               ║ ", Item_Total), inventory[3] += Item_Total;
		if (i == 4) printf("║ 红石:%2d               ║ ", Item_Total), inventory[4] += Item_Total;
		if (i == 5) printf("║ 青金石:%2d             ║ ", Item_Total), inventory[5] += Item_Total;
		if (i == 6) printf("║ 绿宝石:%2d             ║ ", Item_Total), inventory[6] += Item_Total;
		if (i == 7) printf("║ 钻石:%2d               ║ ", Item_Total), inventory[7] += Item_Total;
		printf("\n╠═══════════════════════╣ \n");
	}
	int Item_Total = rand() % 4;
	if (Item_Total < 3) Item_Total = 0;
	else if (Item_Total == 3) Item_Total = 1;
	printf("║ 打火石:%2d             ║ ", Item_Total), inventory[14] += Item_Total;
	int is_soundtrack = rand() % 10, soundtrack = rand() % 2;
	if (is_soundtrack == 0) {
		printf("\n╠═══════════════════════╣ \n");
		if (soundtrack == 0) printf("║ 录音带-Happy Chests   ║ "), inventory[17]++;
		if (soundtrack == 1) printf("║ 录音带-Stressful      ║ "), inventory[18]++;
	}
	printf("\n╚═══════════════════════╝ \n");
	printf("搜刮完毕！\n");
	system("pause");
	return ;
}
void chest_nether() {
	system("cls");
	printf("箱子\n");
	printf("╔═══════════════════════╗ \n");
	for (int i = 15; i < 17; i++) {
		int Item_Total;
		Item_Total = rand() % 10;
		if (i == 15) printf("║ 下界石英:%2d           ║ ", Item_Total), inventory[15] += Item_Total;
		if (i == 16) printf("║ 萤石:%2d               ║ ", Item_Total), inventory[16] += Item_Total;
		if (i < 16) printf("\n╠═══════════════════════╣ \n");
	}
	int is_soundtrack = rand() % 10;
	if (is_soundtrack == 0) {
		printf("\n╠═══════════════════════╣ \n");
		printf("║ 录音带-Lava_Zombie    ║ "), inventory[19]++;
	}
	printf("\n╚═══════════════════════╝ \n");
	printf("搜刮完毕！\n");
	system("pause");
	return ;
}
void shop() { //商店
	system("cls");
	while (1) {
		int shopSelect;
		printf("欢迎光临商店!\n");
		printf("请输入你要干什么:\n");
		printf("[0]买 [1]卖 [2]退出\n");
		scanf("%d", &shopSelect);
		if (shopSelect == 0) {
			printf("金钱:%d\n", money);
			printf("1.末影珍珠:$10,0000 传送至附近9*9的范围内\n");
			printf("2.治疗药水:$50,0000 恢复至满血\n");
			printf("3.喷溅型伤害药水:$30,0000 对5*5范围内的怪物造成10点伤害\n");
			printf("4.面包:$10 恢复3点饱食度\n");
			printf("你要买那个(编号)?买多少?");
			int buy, buyS;
			scanf("%d%d", &buy, &buyS);
			if (buy == 1) {
				if (money >= thingMoney[8]*buyS) {
					inventory[8] += buyS, money -= thingMoney[8] * buyS;
				} else {
					printf("老板:买不起就滚吧!开你的箱子去!\n");
					Sleep(2000);
				}
			} else if (buy == 2) {
				if (money >= thingMoney[9]*buyS) {
					inventory[9] += buyS, money -= thingMoney[9] * buyS;
				} else {
					printf("老板:买不起就滚吧!开你的箱子去!\n");
					Sleep(2000);
				}
			} else if (buy == 3) {
				if (money >= thingMoney[10]*buyS) {
					inventory[10] += buyS, money -= thingMoney[10] * buyS;
				} else {
					printf("老板:买不起就滚吧!开你的箱子去!\n");
					Sleep(2000);
				}
			} else if (buy == 4) {
				if (money >= thingMoney[13]*buyS) {
					inventory[13] += buyS, money -= thingMoney[13] * buyS;
				} else {
					printf("老板:面包都买不起,去开你的箱子去!\n");
					Sleep(2000);
				}
			}
		}
		if (shopSelect == 1) {
			printf("金钱:%d\n", money);
			for (int i = 0; i < 8; i++) {
				money += inventory[i] * thingMoney[i], inventory[i] = 0;
			}
			for (int i = 15 ; i < 17; i++) {
				money += inventory[i] * thingMoney[i], inventory[i] = 0;
			}
			printf("成交! 金钱:%d\n", money);
			Sleep(1000);
		}
		if (shopSelect == 2) {
			return ;
		}
		system("cls");
	}
}
void useThing() {
	printf("背包道具:\n");
	printf(" ╔═══════════════════════╗ \n");
	printf(" ║ 1.末影珍珠:%2d         ║ \n", inventory[8]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 2.治疗药水:%2d         ║ \n", inventory[9]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 3.喷溅型伤害药水:%2d   ║ \n", inventory[10]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 4.打火石:%2d           ║ \n", inventory[14]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 5.录音带-Happy-Chests ║ \n");
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 6.录音带-Stessful     ║ \n");
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 7.录音带-Lava Zombie  ║ \n");
	printf(" ╚═══════════════════════╝ \n");
	printf("你要使用第几个道具?\n");
	int useSelect;
	scanf("%d", &useSelect);
	if (useSelect == 1 && inventory[8] > 0) {
		inventory[8]--;
		printf("你要传送到?:");
		int Ender_Pearl_X, Ender_Pearl_Y;
		scanf("%d%d", &Ender_Pearl_X, &Ender_Pearl_Y);
		Ender_Pearl_X = min(Ender_Pearl_X, x + 4), Ender_Pearl_Y = min(Ender_Pearl_Y, y + 4);
		Ender_Pearl_X = max(Ender_Pearl_X, x - 4), Ender_Pearl_Y = max(Ender_Pearl_Y, y - 4);
		overworld[x][y] = 0;
		x = Ender_Pearl_X, y = Ender_Pearl_Y;
		printf("玩家 使用 末影珍珠,已将 玩家 传送到 %d %d\n", x, y);
		Sleep(1000);
	}
	if (useSelect == 2 && inventory[9] > 0) {
		inventory[9]--;
		hp = 20;
		printf("玩家 使用 治疗药水,生命值 恢复至 20/20\n");
	}
	if (useSelect == 3 && inventory[10] > 0) {
		inventory[10]--;
		for (int i = max(1, x - 2); i <= min(n, x + 2); i++) {
			for (int j = max(1, y - 2); j <= min(n, y + 2); j++) {
				for (int k = 1; k <= zombie_sum; k++) {
					if (zombie[k].x == i && zombie[k].y == j) {
						overworld[zombie[k].x][zombie[k].y] = 0;
						zombie[k].x = 0, zombie[k].y = 0;
						printf("玩家使用喷溅型伤害药水,僵尸%d被杀死了\n", k);
					}
				}
				for (int k = 1; k <= skeleton_sum; k++) {
					if (skeleton[k].x == i && skeleton[k].y == j) {
						overworld[skeleton[k].x][skeleton[k].y] = 0;
						skeleton[k].x = 0, skeleton[k].y = 0;
						printf("玩家使用喷溅型伤害药水,骷髅%d被杀死了\n", k);
					}
				}
			}
		}
		Sleep(1000);
	}
	if (useSelect == 4 && inventory[14] > 0) {
		bool is_Found_Door = 0;
		for (int i = 0; i < 4; i++) {
			int tx = x + cx[i], ty = y + cy[i];
			if (overworld[tx][ty] == 11) {
				overworld[tx][ty] = 18;
				is_Found_Door = 1;
			}
		}
		if (is_Found_Door == 0) {
			printf("未找到门!");
		} else if (is_Found_Door == 1) {
			inventory[14]--;
			printf("玩家使用打火石激活了下界传送门\n");
			is_act_door = 1;
			if (progress[6] == 0) {
				progress[6] = 1;
				printf("玩家刚刚获得了进度");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
				printf("[准备去新的维度]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
				printf("!\n");
				Sleep(2000);
			}
		}
		Sleep(1000);
	}
	if (useSelect == 5 && inventory[17] > 0) {
		system("start Happy_Chests.mp3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("正在播放-Happy Chests\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
		system("pause");
	}
	if (useSelect == 6 && inventory[18] > 0) {
		system("start Stressful.mp3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("正在播放-Stressful\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
		system("pause");
	}
	if (useSelect == 7 && inventory[19] > 0) {
		system("start Lava_Zombie.wav");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("正在播放-Lava Zombie\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
		system("pause");
	}
}
void useThing_nether() {
	printf("背包道具:\n");
	printf(" ╔═══════════════════════╗ \n");
	printf(" ║ 1.末影珍珠:%2d         ║ \n", inventory[8]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 2.治疗药水:%2d         ║ \n", inventory[9]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 3.喷溅型伤害药水:%2d   ║ \n", inventory[10]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 4.录音带-Happy-Chests ║ \n");
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 5.录音带-Stessful     ║ \n");
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 6.录音带-Lava Zombie  ║ \n");
	printf(" ╚═══════════════════════╝ \n");
	printf("你要使用第几个道具?\n");
	int useSelect;
	scanf("%d", &useSelect);
	if (useSelect == 1 && inventory[8] > 0) {
		inventory[8]--;
		printf("你要传送到?:");
		int Ender_Pearl_X, Ender_Pearl_Y;
		scanf("%d%d", &Ender_Pearl_X, &Ender_Pearl_Y);
		Ender_Pearl_X = min(Ender_Pearl_X, x + 4), Ender_Pearl_Y = min(Ender_Pearl_Y, y + 4);
		Ender_Pearl_X = max(Ender_Pearl_X, x - 4), Ender_Pearl_Y = max(Ender_Pearl_Y, y - 4);
		nether[x][y] = NETHER_STONE;
		x = Ender_Pearl_X, y = Ender_Pearl_Y;
		printf("玩家使用末影珍珠,已将玩家传送到 %d %d\n", x, y);
		nether[x][y] = NETHER_PLAYER;
		Sleep(1000);
	}
	if (useSelect == 2 && inventory[9] > 0) {
		inventory[9]--;
		hp = 20;
		printf("玩家使用治疗药水,生命值恢复至20\n");
	}
	if (useSelect == 3 && inventory[10] > 0) {
		inventory[10]--;
		for (int i = max(1, x - 2); i <= min(n, x + 2); i++) {
			for (int j = max(1, y - 2); j <= min(n, y + 2); j++) {
				for (int k = 1; k <= lava_zombie_sum; k++) {
					if (lava_zombie[k].x == i && lava_zombie[k].y == j) {
						nether[lava_zombie[k].x][lava_zombie[k].y] = 0;
						lava_zombie[k].x = 0, lava_zombie[k].y = 0;
					}
				}
				for (int k = 1; k <= burn_skeleton_sum; k++) {
					if (burn_skeleton[k].x == i && burn_skeleton[k].y == j) {
						nether[burn_skeleton[k].x][burn_skeleton[k].y] = 0;
						burn_skeleton[k].x = 0, burn_skeleton[k].y = 0;
					}
				}
			}
		}
		Sleep(1000);
	}
	if (useSelect == 4 && inventory[17] > 0) {
		system("start Happy_Chests.mp3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("正在播放-Happy Chests\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		system("pause");
	}
	if (useSelect == 5 && inventory[18] > 0) {
		system("start Stressful.mp3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("正在播放-Stressful\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		system("pause");
	}
	if (useSelect == 6 && inventory[19] > 0) {
		system("start Lava_Zombie.wav");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("正在播放-Lava_Zombie\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		system("pause");
	}
}
void seeInventory() {
	system("cls");
	printf("背包\n");
	printf("╔═══════════════════════╗ \n");
	for (int i = 0; i < 21; i++) {
		if (i == 0) printf("║ 原石:%2d               ║ ", inventory[i]);
		if (i == 1) printf("║ 煤炭:%2d               ║ ", inventory[i]);
		if (i == 2) printf("║ 铁锭:%2d               ║ ", inventory[i]);
		if (i == 3) printf("║ 金锭:%2d               ║ ", inventory[i]);
		if (i == 4) printf("║ 红石:%2d               ║ ", inventory[i]);
		if (i == 5) printf("║ 青金石:%2d             ║ ", inventory[i]);
		if (i == 6) printf("║ 绿宝石:%2d             ║ ", inventory[i]);
		if (i == 7) printf("║ 钻石:%2d               ║ ", inventory[i]);
		if (i == 8) printf("║ 末影珍珠:%2d           ║ ", inventory[i]);
		if (i == 9) printf("║ 治疗药水:%2d           ║ ", inventory[i]);
		if (i == 10) printf("║ 喷溅型伤害药水:%2d     ║ ", inventory[i]);
		if (i == 11) printf("║ 腐肉:%2d               ║ ", inventory[i]);
		if (i == 12) printf("║ 骨头:%2d               ║ ", inventory[i]);
		if (i == 13) printf("║ 面包:%2d               ║ ", inventory[i]);
		if (i == 14) printf("║ 打火石:%2d             ║ ", inventory[i]);
		if (i == 15) printf("║ 下界石英:%2d           ║ ", inventory[i]);
		if (i == 16) printf("║ 萤石:%2d               ║ ", inventory[i]);
		if (i == 17) printf("║ 录音带-Happy Chests:%2d║ ", inventory[i]);
		if (i == 18) printf("║ 录音带-Stressful:%2d   ║ ", inventory[i]);
		if (i == 19) printf("║ 录音带-Lava Zombie:%2d ║ ", inventory[i]);
		if (i == 20) printf("║ 末地钥匙:%2d           ║ ", inventory[i]);
		if (i < 20) {
			printf("\n╠═══════════════════════╣ \n");
		}
	}
	printf("\n╚═══════════════════════╝ \n");
	system("pause");
}
void eatFood() {
	printf("食物:\n");
	printf("╔═══════════════════════╗ \n");
	printf("║ 1.腐肉:%2d             ║ \n", inventory[11]);
	printf("╠═══════════════════════╣ \n");
	printf("║ 2.面包:%2d             ║ \n", inventory[13]);
	printf("╚═══════════════════════╝ \n");
	int foodSelect, foodS;
	printf("吃哪一个食物,吃多少?");
	scanf("%d%d", &foodSelect, &foodS);
	if (foodSelect == 1) {
		foodS = min(foodS, inventory[11]);
		inventory[11] -= foodS;
		full = min(20, full + foodS * 1);
	}
	if (foodSelect == 2) {
		foodS = min(foodS, inventory[13]);
		inventory[13] -= foodS;
		full = min(20, full + foodS * 3);
	}
	return ;
}
void seeProgress() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("成就\n");
	printf("主世界\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[小小怪物，轻松拿捏]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("击杀任意一只怪物 ");
	if (progress[1] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[远处有个狙击手]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("让骷髅的箭射中你 ");
	if (progress[2] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[这是什么？箱子！]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("打开一个箱子 ");
	if (progress[3] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[抵达终点]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("到达终点 ");
	if (progress[4] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[哦，不！]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("死亡一次 ");
	if (progress[5] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("下界\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
	printf("[准备去新的维度]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("激活下界传送门 ");
	if (progress[6] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
	printf("[勇闯下界]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("进入下界 ");
	if (progress[7] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
	printf("[燃起来了]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("燃烧骷髅的火矢真的很热！ ");
	if (progress[8] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	system("pause");
}
void do_order() {
	printf("/");
	string order[50];
	int p = 0;
	cin >> order[++p];
	if (order[p] == "kill") {
		cin >> order[++p];
		if (order[p] == "chest:zombie") {
			cin >> order[++p];
			if (order[p] == "all") {
				for (int i = 1; i <= zombie_sum; i++) {
					overworld[zombie[i].x][zombie[i].y] = 0;
					zombie[i] = {0, 0, 0, 0};
				}
				printf("杀死了 %d 个实体\n", zombie_sum);
				Sleep(1000);
			} else {
				int temp = stoi(order[p]);
				overworld[zombie[temp].x][zombie[temp].y] = 0;
				zombie[temp] = {0, 0, 0, 0};
				printf("杀死了僵尸 %d \n", temp);
				Sleep(1000);
			}
		} else if (order[p] == "chest:skeleton") {
			cin >> order[++p];
			if (order[p] == "all") {
				for (int i = 1; i <= skeleton_sum; i++) {
					overworld[skeleton[i].x][skeleton[i].y] = 0;
					skeleton[i] = {0, 0, 0, 0};
				}
				printf("杀死了 %d 个实体\n", skeleton_sum);
				Sleep(1000);
			} else {
				int temp = stoi(order[p]);
				overworld[skeleton[temp].x][skeleton[temp].y] = 0;
				skeleton[temp] = {0, 0, 0, 0};
				printf("杀死了骷髅 %d \n", temp);
				Sleep(1000);
			}
		} else if (order[p] == "chest:lava_zombie") {
			cin >> order[++p];
			if (order[p] == "all") {
				for (int i = 1; i <= lava_zombie_sum; i++) {
					nether[lava_zombie[i].x][lava_zombie[i].y] = 0;
					lava_zombie[i] = {0, 0, 0, 0};
				}
				printf("杀死了 %d 个实体\n", lava_zombie_sum);
				Sleep(1000);
			} else {
				int temp = stoi(order[p]);
				nether[lava_zombie[temp].x][lava_zombie[temp].y] = 0;
				lava_zombie[temp] = {0, 0, 0, 0};
				printf("杀死了熔岩僵尸 %d \n", temp);
				Sleep(1000);
			}
		} else if (order[p] == "chest:burn_skeleton") {
			cin >> order[++p];
			if (order[p] == "all") {
				for (int i = 1; i <= burn_skeleton_sum; i++) {
					nether[burn_skeleton[i].x][burn_skeleton[i].y] = 0;
					burn_skeleton[i] = {0, 0, 0, 0};
				}
				printf("杀死了 %d 个实体\n", burn_skeleton_sum);
				Sleep(1000);
			} else {
				int temp = stoi(order[p]);
				nether[burn_skeleton[temp].x][burn_skeleton[temp].y] = 0;
				burn_skeleton[temp] = {0, 0, 0, 0};
				printf("杀死了燃烧骷髅 %d \n", temp);
				Sleep(1000);
			}
		} else if (order[p] == "chest:blaze") {
			cin >> order[++p];
			if (order[p] == "all") {
				for (int i = 1; i <= blaze_sum; i++) {
					nether[blaze[i].x][blaze[i].y] = 0;
					blaze[i] = {0, 0, 0, 0};
				}
				printf("杀死了 %d 个实体\n", blaze_sum);
				Sleep(1000);
			} else {
				int temp = stoi(order[p]);
				nether[blaze[temp].x][blaze[temp].y] = 0;
				blaze[temp] = {0, 0, 0, 0};
				printf("杀死了烈焰人 %d \n", temp);
				Sleep(1000);
			}
		} else if (order[p] == "chest:player") {
			hp = 0, full = 1, died_Information = "You were been killed.";
			printf("杀死了玩家\n");
			Sleep(1000);
		} else if (order[p] == "all") {
			for (int i = 1; i <= zombie_sum; i++) {
				overworld[zombie[i].x][zombie[i].y] = 0;
				zombie[i] = {0, 0, 0, 0};
			}
			for (int i = 1; i <= skeleton_sum; i++) {
				overworld[skeleton[i].x][skeleton[i].y] = 0;
				skeleton[i] = {0, 0, 0, 0};
			}
			for (int i = 1; i <= lava_zombie_sum; i++) {
				nether[lava_zombie[i].x][lava_zombie[i].y] = 0;
				lava_zombie[i] = {0, 0, 0, 0};
			}
			for (int i = 1; i <= burn_skeleton_sum; i++) {
				nether[burn_skeleton[i].x][burn_skeleton[i].y] = 0;
				burn_skeleton[i] = {0, 0, 0, 0};
			}
			for (int i = 1; i <= blaze_sum; i++) {
				nether[blaze[i].x][blaze[i].y] = 0;
				blaze[i] = {0, 0, 0, 0};
			}
			hp = 0, full = 1, died_Information = "You were been killed.";
			printf("杀死了 %d 个实体", zombie_sum + skeleton_sum + lava_zombie_sum + burn_skeleton_sum + 1);
			Sleep(1000);
		}
	} else if (order[p] == "tp") {
		cin >> order[++p];
		cin >> order[++p];
		int tpx = stoi(order[p - 1]), tpy = stoi(order[p]);
		overworld[x][y] = 0, nether[x][y] = 0;
		x = tpx, y = tpy;
		overworld[x][y] = PLAYER, nether[x][y] = NETHER_PLAYER;
	} else if (order[p] == "give") {
		cin >> order[++p];
		cin >> order[++p];
		int item_count = stoi(order[p]);
		inventory[item[order[p - 1]]] += item_count;
		cout << "给予玩家" << item_count << "个" << order[p - 1];
		Sleep(1000);
	} else if (order[p] == "gamerule") {
		cin >> order[++p];
		cin >> order[++p];
		if (order[p - 1] == "keepInventory") {
			keepInventory = order[p] == "true" ? 1 : 0;
		}
	} else if (order[p] == "setblock") {
		cin >> order[++p];
		if (order[p] == "chest:overworld") {
			cin >> order[++p];
			cin >> order[++p];
			int setblock_x = stoi(order[p - 1]), setblock_y = stoi(order[p]);
			cin >> order[++p];
			overworld[setblock_x][setblock_y] = block_overworld[order[p]];
		} else if (order[p] == "chest:nether") {
			cin >> order[++p];
			cin >> order[++p];
			int setblock_x = stoi(order[p - 1]), setblock_y = stoi(order[p]);
			cin >> order[++p];
			nether[setblock_x][setblock_y] = block_nether[order[p]];
		}
	} else if (order[p] == "gamemode") {
		cin >> order[++p];
		if (order[p] == "survival") {
			gamemode = 0;
		} else if (order[p] == "creative") {
			gamemode = 1;
		} else if (order[p] == "adventure") {
			gamemode = 2;
		}
	} else if (order[p] == "help") {
		printf(" ╔═════════════════════════════════════════════════════════════════════════════╗ \n");
		printf(" ║ 指令的使用(先在'游戏选项-作弊'中输入1)                                      ║ \n");
		printf(" ║   (1)/kill <entity name> <id/all> 杀死某种实体                              ║ \n");
		printf(" ║   (2)/tp <x> <y> 将玩家传送到(行,列)                                        ║ \n");
		printf(" ║   (3)/give <item> <value> 给予物品                                          ║ \n");
		printf(" ║   (4)/gamerule <gamerulerule> <value> 修改游戏规则                          ║ \n");
		printf(" ║   (5)/setblock <dimension> <x> <y> <block> 设置方块                         ║ \n");
		printf(" ║   (6)/gamemode <gamemode> 设置游戏模式                                      ║ \n");
		printf(" ╚═════════════════════════════════════════════════════════════════════════════╝ \n");
		system("pause");
	} else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		printf("指令无效!\n");
		Sleep(1000);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	}
}
int nether_block_check_is(int nether_x, int nether_y) {
	int nether_mid;
	if (n % 2 == 0) nether_mid = n / 2;
	else if (n % 2 == 1) nether_mid = (n + 1) / 2;
	if ((nether_x >= nether_mid - 1 && nether_x <= nether_mid + 1) || (nether_y >= nether_mid - 1 && nether_y <= nether_mid + 1)) {
		return NETHER_BRICK;
	} else {
		return NETHER_STONE;
	}
}
void game_nether() {
	system("cls");
	system("color 0C");
	if ((is_rebuild == 1) || (is_rebuild == 0 && is_first_level == 0)) {
		system("color 5F");
		printf("\n\n\n\n\n\n                                                  下载地形中...");
		Sleep(3000);
		system("cls");
		system("color 0C");
		make_world_nether();
	}
	while (1) {
		if (gamemode == 1) hp = 20, full = 20, memset(inventory, INF, sizeof(inventory));
		for (int i = 1; i <= lava_zombie_sum; i++) {
			if (lava_zombie[i].hp == 5) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_5;
			else if (lava_zombie[i].hp == 4) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_4;
			else if (lava_zombie[i].hp == 3) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_3;
			else if (lava_zombie[i].hp == 2) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_2;
			else if (lava_zombie[i].hp == 1) nether[lava_zombie[i].x][lava_zombie[i].y] = LAVA_ZOMBIE_1;
		}
		for (int i = 1; i <= burn_skeleton_sum; i++) {
			if (burn_skeleton[i].hp == 5) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_5;
			else if (burn_skeleton[i].hp == 4) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_4;
			else if (burn_skeleton[i].hp == 3) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_3;
			else if (burn_skeleton[i].hp == 2) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_2;
			else if (burn_skeleton[i].hp == 1) nether[burn_skeleton[i].x][burn_skeleton[i].y] = BURN_SKELETON_1;
		}
		for (int i = 1; i <= burn_arrow_sum; i++) {
			nether[burn_arrow[i].x][burn_arrow[i].y] = BURN_ARROW;
		}
		for (int i = 1; i <= blaze_sum; i++) {
			if (blaze[i].hp == 5) nether[blaze[i].x][blaze[i].y] = BLAZE_5;
			else if (blaze[i].hp == 4) nether[blaze[i].x][blaze[i].y] = BLAZE_4;
			else if (blaze[i].hp == 3) nether[blaze[i].x][blaze[i].y] = BLAZE_3;
			else if (blaze[i].hp == 2) nether[blaze[i].x][blaze[i].y] = BLAZE_2;
			else if (blaze[i].hp == 1) nether[blaze[i].x][blaze[i].y] = BLAZE_1;
		}
		for (int i = 1; i <= fire_charge_sum; i++) {
			nether[fire_charge[i].x][fire_charge[i].y] = FIRE_CHARGE;
		}
		if (burn_time > 0) { //燃烧
			burn_time--, hp--;
			if (hp <= 0) {
				died_Information = "You were burn to death.";
			}
		}
		if (step > 0 && step % 10 == 0 && full > 0) { //更新饱食度
			full--;
		}
		if (full == 20) {
			hp++;
			hp = min(hp, 20);
		}
		if (full == 0) {
			hp--;
			if (hp <= 0) {
				died_Information = "You starved to death.";
			}
		}
		if (hp <= 0) {
			if (progress[5] == 0) {
				progress[5] = 1;
				printf("玩家刚刚获得了进度");
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
				hp = 20;
				nether[x][y] = 0;
				system("cls");
				system("color CF");
				printf("\n\n\n\n\n\n\n");
				printf("                                    你死了！\n\n\n");
				printf("   The information of you dies:");
				cout << died_Information;
				printf("\n\n\n");
				int die_select;
				printf("                      [0]退出游戏 [1]重生 [2]返回标题屏幕");
				burn_arrow_sum = 0;
				for (int i = 1; i <= burn_arrow_sum; i++) {
					burn_arrow[i].x = 0, burn_arrow[i].y = 0;
				}
				is_act_door = 0;
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
					return ;
				}
			} else if (gamemode == 2) {
				system("cls");
				system("color CF");
				printf("\n\n\n\n\n\n\n");
				printf("                               你死了，游戏结束！\n\n\n");
				printf("   The information of you dies:");
				cout << died_Information;
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
					mp_Nether();
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
		if (nether_block_check_is(x, y) == NETHER_BRICK) {
			Biome_Fest = 2;
		}
		for (int i = 1; i <= lava_zombie_sum; i++) { //熔岩僵尸移动
			if (abs(lava_zombie[i].x - x) < 4 && abs(lava_zombie[i].y - y) < 4 && lava_zombie[i].x != 0 && lava_zombie[i].y != 0) {
				int lava_zombieType = nether[lava_zombie[i].x][lava_zombie[i].y];
				nether[lava_zombie[i].x][lava_zombie[i].y] = nether_block_check_is(lava_zombie[i].x, lava_zombie[i].y);
				if (x < lava_zombie[i].x && nether[lava_zombie[i].x - 1][lava_zombie[i].y] < 2) lava_zombie[i].x--;
				else if (x > lava_zombie[i].x && nether[lava_zombie[i].x + 1][lava_zombie[i].y] < 2) lava_zombie[i].x++;
				else if (y < lava_zombie[i].y && nether[lava_zombie[i].x][lava_zombie[i].y - 1] < 2) lava_zombie[i].y--;
				else if (y > lava_zombie[i].y && nether[lava_zombie[i].x][lava_zombie[i].y + 1] < 2) lava_zombie[i].y++;
				nether[lava_zombie[i].x][lava_zombie[i].y] = lava_zombieType;
			}
		}
		for (int i = 1; i <= burn_skeleton_sum; i++) { //燃烧骷髅移动
			if (abs(burn_skeleton[i].x - x) < 4 && abs(burn_skeleton[i].y - y) < 4 && burn_skeleton[i].x != 0 && burn_skeleton[i].y != 0) {
				int burn_skeletonType = nether[burn_skeleton[i].x][burn_skeleton[i].y];
				nether[burn_skeleton[i].x][burn_skeleton[i].y] = nether_block_check_is(burn_skeleton[i].x, burn_skeleton[i].y);
				if (x < burn_skeleton[i].x && nether[burn_skeleton[i].x - 1][burn_skeleton[i].y] < 2) burn_skeleton[i].x--;
				else if (x > burn_skeleton[i].x && nether[burn_skeleton[i].x + 1][burn_skeleton[i].y] < 2) burn_skeleton[i].x++;
				else if (y < burn_skeleton[i].y && nether[burn_skeleton[i].x][burn_skeleton[i].y - 1] < 2) burn_skeleton[i].y--;
				else if (y > burn_skeleton[i].y && nether[burn_skeleton[i].x][burn_skeleton[i].y + 1] < 2) burn_skeleton[i].y++;
				nether[burn_skeleton[i].x][burn_skeleton[i].y] = burn_skeletonType;
			}
		}
		for (int i = 1; i <= blaze_sum; i++) { //烈焰人移动
			if (abs(blaze[i].x - x) < 4 && abs(blaze[i].y - y) < 4 && blaze[i].x != 0 && blaze[i].y != 0) {
				int blazeType = nether[blaze[i].x][blaze[i].y];
				nether[blaze[i].x][blaze[i].y] = nether_block_check_is(blaze[i].x, blaze[i].y);
				if (x < blaze[i].x && nether[blaze[i].x - 1][blaze[i].y] < 2) blaze[i].x--;
				else if (x > blaze[i].x && nether[blaze[i].x + 1][blaze[i].y] < 2) blaze[i].x++;
				else if (y < blaze[i].y && nether[blaze[i].x][blaze[i].y - 1] < 2) blaze[i].y--;
				else if (y > blaze[i].y && nether[blaze[i].x][blaze[i].y + 1] < 2) blaze[i].y++;
				nether[blaze[i].x][blaze[i].y] = blazeType;
			}
		}
		for (int i = 1; i <= burn_arrow_sum; i++) { //火矢移动
			if (burn_arrow[i].x != 0 && burn_arrow[i].y != 0 && nether[burn_arrow[i].x + cx[burn_arrow[i].facing]][burn_arrow[i].y + cy[burn_arrow[i].facing]] < 2) {
				nether[burn_arrow[i].x][burn_arrow[i].y] = nether_block_check_is(burn_arrow[i].x, burn_arrow[i].y);
				burn_arrow[i].x += cx[burn_arrow[i].facing], burn_arrow[i].y += cy[burn_arrow[i].facing];
				nether[burn_arrow[i].x][burn_arrow[i].y] = 15;
			} else if (!in(burn_arrow[i].x + cx[burn_arrow[i].facing], burn_arrow[i].y + cy[burn_arrow[i].facing]) || nether[burn_arrow[i].x + cx[burn_arrow[i].facing]][burn_arrow[i].y + cy[burn_arrow[i].facing]]) {
				nether[burn_arrow[i].x][burn_arrow[i].y] = 0;
				burn_arrow[i].x = 0, burn_arrow[i].y = 0;
			}
		}
		for (int i = 1; i <= fire_charge_sum; i++){//火焰弹移动
			if (fire_charge[i].x != 0 && fire_charge[i].y != 0 && nether[fire_charge[i].x + cx[fire_charge[i].facing]][fire_charge[i].y + cy[fire_charge[i].facing]] < 2) {
				nether[fire_charge[i].x][fire_charge[i].y] = nether_block_check_is(fire_charge[i].x, fire_charge[i].y);
				fire_charge[i].x += cx[fire_charge[i].facing], fire_charge[i].y += cy[fire_charge[i].facing];
				nether[fire_charge[i].x][fire_charge[i].y] = FIRE_CHARGE;
			} else if (!in(fire_charge[i].x + cx[fire_charge[i].facing], fire_charge[i].y + cy[fire_charge[i].facing]) || nether[fire_charge[i].x + cx[fire_charge[i].facing]][fire_charge[i].y + cy[fire_charge[i].facing]]) {
				nether[fire_charge[i].x][fire_charge[i].y] = 0;
				fire_charge[i].x = 0, fire_charge[i].y = 0;
			}
		}
		for (int i = 1; i <= burn_skeleton_sum; i++) { //燃烧骷髅射火矢
			if (burn_skeleton[i].x == x) {
				if (burn_skeleton[i].y < y && nether[burn_skeleton[i].x][burn_skeleton[i].y + 1] < 2 && abs(burn_skeleton[i].x - x) < 3 && abs(burn_skeleton[i].y - y) < 3) {
					burn_arrow_sum++;
					burn_arrow[burn_arrow_sum].x = burn_skeleton[i].x, burn_arrow[burn_arrow_sum].y = burn_skeleton[i].y + 1, burn_arrow[burn_arrow_sum].facing = 0;
					nether[burn_arrow[burn_arrow_sum].x][burn_arrow[burn_arrow_sum].y] = 15;
				} else if (burn_skeleton[i].y > y && nether[burn_skeleton[i].x][burn_skeleton[i].y - 1] < 2 && abs(burn_skeleton[i].x - x) < 3 && abs(burn_skeleton[i].y - y) < 3) {
					burn_arrow_sum++;
					burn_arrow[burn_arrow_sum].x = burn_skeleton[i].x, burn_arrow[burn_arrow_sum].y = burn_skeleton[i].y - 1, burn_arrow[burn_arrow_sum].facing = 2;
					nether[burn_arrow[burn_arrow_sum].x][burn_arrow[burn_arrow_sum].y] = 15;
				}
			} else if (burn_skeleton[i].y == y) {
				if (burn_skeleton[i].x < x && nether[burn_skeleton[i].x + 1][burn_skeleton[i].y] < 2 && abs(burn_skeleton[i].x - x) < 3 && abs(burn_skeleton[i].y - y) < 3) {
					burn_arrow_sum++;
					burn_arrow[burn_arrow_sum].x = burn_skeleton[i].x + 1, burn_arrow[burn_arrow_sum].y = burn_skeleton[i].y, burn_arrow[burn_arrow_sum].facing = 1;
					nether[burn_arrow[burn_arrow_sum].x][burn_arrow[burn_arrow_sum].y] = 15;
				} else if (burn_skeleton[i].x > x && nether[burn_skeleton[i].x - 1][burn_skeleton[i].y] < 2 && abs(burn_skeleton[i].x - x) < 3 && abs(burn_skeleton[i].y - y) < 3) {
					burn_arrow_sum++;
					burn_arrow[burn_arrow_sum].x = burn_skeleton[i].x - 1, burn_arrow[burn_arrow_sum].y = burn_skeleton[i].y, burn_arrow[burn_arrow_sum].facing = 3;
					nether[burn_arrow[burn_arrow_sum].x][burn_arrow[burn_arrow_sum].y] = 15;
				}
			}
		}
		for (int i = 1; i <= blaze_sum; i++) { //烈焰人射火焰弹
			if (blaze[i].x == x) {
				if (blaze[i].y < y && nether[blaze[i].x][blaze[i].y + 1] < 2 && abs(blaze[i].x - x) < 3 && abs(blaze[i].y - y) < 3) {
					fire_charge_sum++;
					fire_charge[fire_charge_sum].x = blaze[i].x, fire_charge[fire_charge_sum].y = blaze[i].y + 1, fire_charge[fire_charge_sum].facing = 0;
					nether[fire_charge[fire_charge_sum].x][fire_charge[fire_charge_sum].y] = FIRE_CHARGE;
				} else if (blaze[i].y > y && nether[blaze[i].x][blaze[i].y - 1] < 2 && abs(blaze[i].x - x) < 3 && abs(blaze[i].y - y) < 3) {
					fire_charge_sum++;
					fire_charge[fire_charge_sum].x = blaze[i].x, fire_charge[fire_charge_sum].y = blaze[i].y - 1, fire_charge[fire_charge_sum].facing = 2;
					nether[fire_charge[fire_charge_sum].x][fire_charge[fire_charge_sum].y] = FIRE_CHARGE;
				}
			} else if (blaze[i].y == y) {
				if (blaze[i].x < x && nether[blaze[i].x + 1][blaze[i].y] < 2 && abs(blaze[i].x - x) < 3 && abs(blaze[i].y - y) < 3) {
					fire_charge_sum++;
					fire_charge[fire_charge_sum].x = blaze[i].x + 1, fire_charge[fire_charge_sum].y = blaze[i].y, fire_charge[fire_charge_sum].facing = 1;
					nether[fire_charge[fire_charge_sum].x][fire_charge[fire_charge_sum].y] = FIRE_CHARGE;
				} else if (blaze[i].x > x && nether[blaze[i].x - 1][blaze[i].y] < 2 && abs(blaze[i].x - x) < 3 && abs(blaze[i].y - y) < 3) {
					fire_charge_sum++;
					fire_charge[fire_charge_sum].x = blaze[i].x - 1, fire_charge[fire_charge_sum].y = blaze[i].y, fire_charge[fire_charge_sum].facing = 3;
					nether[fire_charge[fire_charge_sum].x][fire_charge[fire_charge_sum].y] = FIRE_CHARGE;
				}
			}
		}
		mp_Nether();
		if (progress[7] == 0) {
			progress[7] = 1;
			printf("玩家刚刚获得了进度");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
			printf("[勇闯下界]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
			printf("!\n");
			Sleep(2000);
		}
		for (int i = 1; i <= lava_zombie_sum; i++) { //检测熔岩僵尸攻击
			for (int j = 0; j < 4; j++) {
				int zo_killX = lava_zombie[i].x + cx[j], zo_killY = lava_zombie[i].y + cy[j];
				if (x == zo_killX && y == zo_killY) {
					hp -= 2;
					if (hp <= 0) {
						died_Information = "You were killed by the lava zombie.";
					}
					printf("玩家被熔岩僵尸攻击了\n");
				}
			}
		}
		for (int i = 1; i <= burn_skeleton_sum; i++) { //检测燃烧骷髅近战攻击
			for (int j = 0; j < 4; j++) {
				int sk_killX = burn_skeleton[i].x + cx[j], sk_killY = burn_skeleton[i].y + cy[j];
				if (x == sk_killX && y == sk_killY) {
					burn_time = 3;
					if (hp <= 0) {
						died_Information = "You were killed by the skeleton.";
					}
					printf("玩家被燃烧骷髅攻击了,开始燃烧3s\n");
				}
			}
		}
		for (int i = 1; i <= blaze_sum; i++) { //检测烈焰人攻击
			for (int j = 0; j < 4; j++) {
				int blaze_killX = blaze[i].x + cx[j], blaze_killY = blaze[i].y + cy[j];
				if (x == blaze_killX && y == blaze_killY) {
					hp -= 2;
					if (hp <= 0) {
						died_Information = "You were killed by the blaze.";
					}
					printf("玩家被烈焰人攻击了\n");
				}
			}
		}
		for (int i = 1; i <= burn_arrow_sum; i++) { //检测火矢攻击
			int ar_killX = burn_arrow[i].x + cx[burn_arrow[i].facing], ar_killY = burn_arrow[i].y + cy[burn_arrow[i].facing];
			if (x == ar_killX && y == ar_killY) {
				burn_time = 3;
				nether[burn_arrow[i].x][burn_arrow[i].y] = nether_block_check_is(burn_arrow[i].x, burn_arrow[i].y);
				burn_arrow[i].x = 0, burn_arrow[i].y = 0;
				printf("玩家被火矢攻击了,开始燃烧3s\n");
				if (progress[8] == 0) {
					progress[8] = 1;
					printf("玩家刚刚获得了进度");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
					printf("[燃起来了]");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
					printf("!\n");
					Sleep(2000);
				}
			}
		}
		for (int i = 1; i <= fire_charge_sum; i++) { //检测火焰弹攻击
			int fire_charge_killX = fire_charge[i].x + cx[fire_charge[i].facing], fire_charge_killY = fire_charge[i].y + cy[fire_charge[i].facing];
			if (x == fire_charge_killX && y == fire_charge_killY) {
				hp -= 1;
				burn_time = 3;
				nether[fire_charge[i].x][fire_charge[i].y] = nether_block_check_is(fire_charge[i].x, fire_charge[i].y);
				fire_charge[i].x = 0, fire_charge[i].y = 0;
				printf("玩家被火焰弹攻击了,开始燃烧3s\n");
			}
		}
		Biome_Fest = 1;
		nether[x][y] = 2;
		char todo = getch();
		if (todo == 'd' || todo == 's' || todo == 'a' || todo == 'w') {
			int goX = x, goY = y;
			if (todo == 'd') goY++, fx = 0;
			if (todo == 's') goX++, fx = 1;
			if (todo == 'a') goY--, fx = 2;
			if (todo == 'w') goX--, fx = 3;
			if (in(goX, goY) && (nether[goX][goY] == 0 || nether[goX][goY] == 1 || nether[goX][goY] == 3)) {
				nether[goX][goY] = 2;
				nether[x][y] = nether_block_check_is(x, y);
				x = goX, y = goY;
				step++;
			}
		} else if (todo == 'o') {
			int goX, goY;
			goX = x, goY = y;
			if (fx == 0) goY++, fx = 0;
			if (fx == 1) goX++, fx = 1;
			if (fx == 2) goY--, fx = 2;
			if (fx == 3) goX--, fx = 3;
			if (in(goX, goY) && (abs(goX - x) < 2 && abs(goY - y) < 2) && nether[goX][goY] == 4) {
				chest_nether();
				nether[goX][goY] = nether_block_check_is(goX, goY);
			}
		} else if (todo == '1') {
			is_debug = !is_debug;
		} else if (todo == 'k') {
			for (int dir = 0; dir < 4; dir++) {
				int killX = x + cx[dir], killY = y + cy[dir];
				for (int i = 1; i <= lava_zombie_sum; i++) {
					if (killX == lava_zombie[i].x && killY == lava_zombie[i].y) {
						lava_zombie[i].hp--;
						if (nether[killX][killY] == LAVA_ZOMBIE_5) nether[killX][killY] = LAVA_ZOMBIE_4;
						else if (nether[killX][killY] == LAVA_ZOMBIE_4) nether[killX][killY] = LAVA_ZOMBIE_3;
						else if (nether[killX][killY] == LAVA_ZOMBIE_3) nether[killX][killY] = LAVA_ZOMBIE_2;
						else if (nether[killX][killY] == LAVA_ZOMBIE_2) nether[killX][killY] = LAVA_ZOMBIE_1;
						else if (nether[killX][killY] == LAVA_ZOMBIE_1) {
							nether[lava_zombie[i].x][lava_zombie[i].y] = nether_block_check_is(lava_zombie[i].x, lava_zombie[i].y);
							int getZombieMeat = rand() % 5, getGoldIrgot = rand() % 2;
							lava_zombie[i].x = 0, lava_zombie[i].y = 0;
							printf("玩家击杀了熔岩僵尸,获取 腐肉 * %d,金锭 * %d\n", getZombieMeat, getGoldIrgot);
							inventory[11] += getZombieMeat;
							inventory[3] += getGoldIrgot;
							Sleep(1000);
							if (progress[1] == 0) {
								progress[1] = 1;
								printf("玩家刚刚获得了进度");
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
					if (killX == burn_skeleton[i].x && killY == burn_skeleton[i].y) {
						burn_skeleton[i].hp--;
						if (nether[killX][killY] == BURN_SKELETON_5) nether[killX][killY] = BURN_SKELETON_4;
						else if (nether[killX][killY] == BURN_SKELETON_4) nether[killX][killY] = BURN_SKELETON_3;
						else if (nether[killX][killY] == BURN_SKELETON_3) nether[killX][killY] = BURN_SKELETON_2;
						else if (nether[killX][killY] == BURN_SKELETON_2) nether[killX][killY] = BURN_SKELETON_1;
						else if (nether[killX][killY] == BURN_SKELETON_1) {
							nether[burn_skeleton[i].x][burn_skeleton[i].y] = nether_block_check_is(burn_skeleton[i].x, burn_skeleton[i].y);
							int getBone = rand() % 5, getFlintAndSteel = rand() % 2;
							burn_skeleton[i].x = 0, burn_skeleton[i].y = 0;
							printf("玩家击杀了燃烧骷髅,获取骨头 * %d,打火石 * %d\n", getBone, getFlintAndSteel);
							inventory[12] += getBone;
							inventory[14] += getFlintAndSteel;
							Sleep(1000);
							if (progress[1] == 0) {
								progress[1] = 1;
								printf("玩家刚刚获得了进度");
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
					if (killX == blaze[i].x && killY == blaze[i].y) {
						blaze[i].hp--;
						if (nether[killX][killY] == BLAZE_5) nether[killX][killY] = BLAZE_4;
						else if (nether[killX][killY] == BLAZE_4) nether[killX][killY] = BLAZE_3;
						else if (nether[killX][killY] == BLAZE_3) nether[killX][killY] = BLAZE_2;
						else if (nether[killX][killY] == BLAZE_2) nether[killX][killY] = BLAZE_1;
						else if (nether[killX][killY] == BLAZE_1) {
							nether[blaze[i].x][blaze[i].y] = nether_block_check_is(blaze[i].x, blaze[i].y);
							int getEndKey = rand() % 10, getFlintAndSteel = rand() % 2;
							if(getEndKey == 0) getEndKey = 1;
							else getEndKey = 0;
							blaze[i].x = 0, blaze[i].y = 0;
							printf("玩家击杀了烈焰人,获取末地钥匙 * %d,打火石 * %d\n", getEndKey, getFlintAndSteel);
							inventory[20] += getEndKey;
							inventory[14] += getFlintAndSteel;
							Sleep(1000);
							if (progress[1] == 0) {
								progress[1] = 1;
								printf("玩家刚刚获得了进度");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
								printf("[小小怪物，轻松拿捏]");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
								printf("!\n");
								Sleep(2000);
							}
						}
					}
				}
			}
		} else if (todo == 'e') {
			seeInventory();
		} else if (todo == 'q') {
			eatFood();
		} else if (todo == 'r') {
			nether_return = 1;
			return ;
		} else if (todo == '/' && is_order == 1) {
			do_order();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		} else if (todo == '/' && is_order == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
			printf("你没有作弊的权限!\n");
			Sleep(1000);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		} else if (todo == 'u') {
			system("cls");
			useThing_nether();
		} else if (todo == 'p') {
			seeProgress();
			system("color 0C");
		}
		system("cls");
	}
}
void game_overworld() {
	system("color 03");
	printf("\n\n\n\n\n");
	printf("                                          ╔═════════════════════════╗ \n");
	printf("					  ║       CHESTS IN         ║\n");
	printf("					  ║                         ║\n");
	printf("					  ║            THE MAPS     ║\n");
	printf("					  ║                         ║\n");
	printf("					  ║       C++ EDITION       ║\n");
	printf("                                          ╚═════════════════════════╝ \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B);
	printf("                                              ");
	int slogan_p = rand() % 11;
	cout << Blue_slogan[slogan_p] << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
	printf("                                                   勇闯下界\n");
	printf("                                             Through the Nether\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	printf("\n\n\n\n\n");
	printf("						按任意键开始游戏...\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("Alpha 0.8.3(测试版)\n");
	system("pause");
	system("cls");
	printf("存档\n");
	printf("是否重建世界([0]读取存档 [1]重建世界):[ ]\b\b");
	scanf("%d", &is_rebuild);
	if (is_rebuild == 1) {
		printf("游戏选项\n");
		printf("地图大小(5-20):[  ]\b\b\b");
		cin >> n;
		n = max(5, n), n = min(20, n);
		printf("游戏模式(生存:0,创造1,冒险2):[ ]\b\b");
		cin >> gamemode;
		if (gamemode < 0 || gamemode > 2) gamemode = 0;
		printf("作弊([0]否 [1]是):[ ]\b\b");
		cin >> is_order;
		skin_char = 'Y', skin_color = 0x9F;
		num_to_char_mp[PLAYER] = skin_char;
		num_to_char_mp_nether[NETHER_PLAYER] = skin_char;
		block_color[PLAYER] = skin_color;
		block_color_nether[NETHER_PLAYER] = skin_color;
	} else if (is_rebuild == 0) {
		read_dat();
		num_to_char_mp[PLAYER] = skin_char;
		num_to_char_mp_nether[NETHER_PLAYER] = skin_char;
		block_color[PLAYER] = skin_color;
		block_color_nether[NETHER_PLAYER] = skin_color;
	}
	printf("游戏规则\n");
	printf("死亡后保留物品栏([0]否 [1]是):[ ]\b\b");
	scanf("%d", &keepInventory);
	system("cls");
	if (is_rebuild == 0 && Biome_Fest >= 1 && Biome_Fest <= 2) {
		game_nether();
		if (nether_return == 1) {
			return ;
		}
		system("color 03");
		make_world();
	}
	while (1) {
		hp = 20;
		full = 20;
		flag = 0;
		if ((is_rebuild == 1) || (is_rebuild == 0 && is_first_level == 0)) {
			make_world();
		}
		is_first_level = 0;
//构建地图
		while (1) {
			if (gamemode == 1) hp = 20, full = 20, memset(inventory, INF, sizeof(inventory));
			for (int i = 1; i <= zombie_sum; i++) { //及时渲染怪物
				if (zombie[i].hp == 3) overworld[zombie[i].x][zombie[i].y] = ZOMBIE_3;
				else if (zombie[i].hp == 2) overworld[zombie[i].x][zombie[i].y] = ZOMBIE_2;
				else if (zombie[i].hp == 1) overworld[zombie[i].x][zombie[i].y] = ZOMBIE_1;
			}
			for (int i = 1; i <= skeleton_sum; i++) {
				if (skeleton[i].hp == 3) overworld[skeleton[i].x][skeleton[i].y] = SKELETON_3;
				else if (skeleton[i].hp == 2) overworld[skeleton[i].x][skeleton[i].y] = SKELETON_2;
				else if (skeleton[i].hp == 1) overworld[skeleton[i].x][skeleton[i].y] = SKELETON_1;
			}
			for (int i = 1; i <= arrow_sum; i++) {
				overworld[arrow[i].x][arrow[i].y] = ARROW;
			}
			if (step > 0 && step % 10 == 0 && full > 0) { //更新饱食度
				full--;
			}
			if (full == 20) {
				hp++;
				hp = min(hp, 20);
			}
			if (full == 0) {
				hp--;
				if (hp <= 0) {
					died_Information = "You starved to death.";
				}
			}
			if (hp <= 0) {
				if (progress[5] == 0) {
					progress[5] = 1;
					printf("玩家刚刚获得了进度");
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
					hp = 20;
					overworld[x][y] = 0;
					system("cls");
					system("color CF");
					printf("\n\n\n\n\n\n\n");
					printf("                                    你死了！\n\n\n");
					printf("   The information of you dies:");
					cout << died_Information;
					printf("\n\n\n");
					int die_select;
					printf("                      [0]退出游戏 [1]重生 [2]返回标题屏幕");
					arrow_sum = 0;
					for (int i = 1; i <= arrow_sum; i++) {
						arrow[i].x = 0, arrow[i].y = 0;
					}
					is_act_door = 0;
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
					printf("   The information of you dies:");
					cout << died_Information;
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
						mp();
						system("pause");
						system("del chest-game-data.dat");
						return ;
					}
				}
			}
			if (x == n - 1 && y == n - 1 && is_act_door == 1) {
				overworld[x][y] = 0;
				arrow_sum = 0;
				for (int i = 1; i <= arrow_sum; i++) {
					arrow[i].x = 0, arrow[i].y = 0;
				}
				is_act_door = 0;
				game_nether();
				if (nether_return == 1) {
					return ;
				}
				system("cls");
				system("color 03");
				break;
			}
			if (x == n - 1 && y == n - 1) {
				if (progress[4] == 0) {
					progress[4] = 1;
					printf("玩家刚刚获得了进度");
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
				is_act_door = 0;
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
			Biome_Fest = 0;
			for (int i = 1; i <= zombie_sum; i++) { //僵尸移动
				if (abs(zombie[i].x - x) < 3 && abs(zombie[i].y - y) < 3 && zombie[i].x != 0 && zombie[i].y != 0) {
					int zombieType = overworld[zombie[i].x][zombie[i].y];
					overworld[zombie[i].x][zombie[i].y] = DIRT;
					if (x < zombie[i].x && overworld[zombie[i].x - 1][zombie[i].y] < 5) zombie[i].x--;
					else if (x > zombie[i].x && overworld[zombie[i].x + 1][zombie[i].y] < 5) zombie[i].x++;
					else if (y < zombie[i].y && overworld[zombie[i].x][zombie[i].y - 1] < 5) zombie[i].y--;
					else if (y > zombie[i].y && overworld[zombie[i].x][zombie[i].y + 1] < 5) zombie[i].y++;
					overworld[zombie[i].x][zombie[i].y] = zombieType;
				}
			}
			for (int i = 1; i <= skeleton_sum; i++) { //骷髅移动
				if ((skeleton[i].x != x || skeleton[i].y != y) && skeleton[i].x != 0 && skeleton[i].y != 0) {
					int skeletonType = overworld[skeleton[i].x][skeleton[i].y];
					overworld[skeleton[i].x][skeleton[i].y] = DIRT;
					if (skeleton[i].x > x && overworld[skeleton[i].x - 1][skeleton[i].y] < 5) skeleton[i].x--;
					else if (skeleton[i].x < x && overworld[skeleton[i].x + 1][skeleton[i].y] < 5) skeleton[i].x++;
					else if (skeleton[i].y > y && overworld[skeleton[i].x][skeleton[i].y - 1] < 5) skeleton[i].y--;
					else if (skeleton[i].y < y && overworld[skeleton[i].x][skeleton[i].y + 1] < 5) skeleton[i].y++;
					overworld[skeleton[i].x][skeleton[i].y] = skeletonType;
				}
			}
			for (int i = 1; i <= arrow_sum; i++) { //箭矢移动
				if (arrow[i].x != 0 && arrow[i].y != 0 && overworld[arrow[i].x + cx[arrow[i].facing]][arrow[i].y + cy[arrow[i].facing]] < 5) {
					overworld[arrow[i].x][arrow[i].y] = DIRT;
					arrow[i].x += cx[arrow[i].facing], arrow[i].y += cy[arrow[i].facing];
					overworld[arrow[i].x][arrow[i].y] = 17;
				} else if (!in(arrow[i].x + cx[arrow[i].facing], arrow[i].y + cy[arrow[i].facing]) || overworld[arrow[i].x + cx[arrow[i].facing]][arrow[i].y + cy[arrow[i].facing]]) {
					overworld[arrow[i].x][arrow[i].y] = DIRT;
					arrow[i].x = 0, arrow[i].y = 0;
				}
			}
			for (int i = 1; i <= skeleton_sum; i++) { //骷髅射箭
				if (skeleton[i].x == x) {
					if (skeleton[i].y < y && overworld[skeleton[i].x][skeleton[i].y + 1] < 5 && abs(skeleton[i].x - x) < 3 && abs(skeleton[i].y - y) < 3) {
						arrow_sum++;
						arrow[arrow_sum].x = skeleton[i].x, arrow[arrow_sum].y = skeleton[i].y + 1, arrow[arrow_sum].facing = 0;
						overworld[arrow[arrow_sum].x][arrow[arrow_sum].y] = 17;
					} else if (skeleton[i].y > y && overworld[skeleton[i].x][skeleton[i].y - 1] < 5 && abs(skeleton[i].x - x) < 3 && abs(skeleton[i].y - y) < 3) {
						arrow_sum++;
						arrow[arrow_sum].x = skeleton[i].x, arrow[arrow_sum].y = skeleton[i].y - 1, arrow[arrow_sum].facing = 2;
						overworld[arrow[arrow_sum].x][arrow[arrow_sum].y] = 17;
					}
				} else if (skeleton[i].y == y) {
					if (skeleton[i].x < x && overworld[skeleton[i].x + 1][skeleton[i].y] < 5 && abs(skeleton[i].x - x) < 3 && abs(skeleton[i].y - y) < 3) {
						arrow_sum++;
						arrow[arrow_sum].x = skeleton[i].x + 1, arrow[arrow_sum].y = skeleton[i].y, arrow[arrow_sum].facing = 1;
						overworld[arrow[arrow_sum].x][arrow[arrow_sum].y] = 17;
					} else if (skeleton[i].x > x && overworld[skeleton[i].x - 1][skeleton[i].y] < 5 && abs(skeleton[i].x - x) < 3 && abs(skeleton[i].y - y) < 3) {
						arrow_sum++;
						arrow[arrow_sum].x = skeleton[i].x - 1, arrow[arrow_sum].y = skeleton[i].y, arrow[arrow_sum].facing = 3;
						overworld[arrow[arrow_sum].x][arrow[arrow_sum].y] = 17;
					}
				}
			}
			mp();
			for (int i = 1; i <= zombie_sum; i++) { //检测僵尸攻击
				for (int j = 0; j < 4; j++) {
					int zo_killX = zombie[i].x + cx[j], zo_killY = zombie[i].y + cy[j];
					if (x == zo_killX && y == zo_killY) {
						hp -= 2;
						if (hp <= 0) {
							died_Information = "You were killed by the zombie.";
						}
						printf("玩家被僵尸攻击了\n");
					}
				}
			}
			for (int i = 1; i <= skeleton_sum; i++) { //检测骷髅近战攻击
				for (int j = 0; j < 4; j++) {
					int sk_killX = skeleton[i].x + cx[j], sk_killY = skeleton[i].y + cy[j];
					if (x == sk_killX && y == sk_killY) {
						hp -= 2;
						if (hp <= 0) {
							died_Information = "You were killed by the skeleton.";
						}
						printf("玩家被骷髅攻击了\n");
					}
				}
			}
			for (int i = 1; i <= arrow_sum; i++) { //检测箭矢攻击
				int ar_killX = arrow[i].x + cx[arrow[i].facing], ar_killY = arrow[i].y + cy[arrow[i].facing];
				if (x == ar_killX && y == ar_killY) {
					hp--;
					if (hp <= 0) {
						died_Information = "You were killed by the arrow of the skeleton.";
					}
					printf("玩家被箭矢攻击了\n");
					overworld[arrow[i].x][arrow[i].y] = DIRT;
					arrow[i].x = 0, arrow[i].y = 0;
					if (progress[2] == 0) {
						progress[2] = 1;
						printf("玩家刚刚获得了进度");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
						printf("[远处有个狙击手]");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
						printf("!\n");
						Sleep(2000);
					}
				}
				for (int j = 1; j <= zombie_sum; j++) {
					if (overworld[ar_killX][ar_killY] == 9) overworld[ar_killX][ar_killY] = 12, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
					else if (overworld[ar_killX][ar_killY] == 12) overworld[ar_killX][ar_killY] = 13, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
					else if (overworld[ar_killX][ar_killY] == 13) {
						overworld[ar_killX][ar_killY] = 0, overworld[arrow[i].x][arrow[i].y] = 0, arrow[i].x = 0, arrow[i].y = 0;
					}
				}
				for (int j = 1; j <= skeleton_sum; j++) {
					if (overworld[ar_killX][ar_killY] == 14) overworld[ar_killX][ar_killY] = 15, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
					else if (overworld[ar_killX][ar_killY] == 15) overworld[ar_killX][ar_killY] = 16, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
					else if (overworld[ar_killX][ar_killY] == 16) {
						overworld[ar_killX][ar_killY] = DIRT, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
					}
				}
			}
			char todo;
			todo = getch();
			int goX = x, goY = y;
			if (todo == 'd' || todo == 's' || todo == 'a' || todo == 'w') {
				if (todo == 'd') goY++, fx = 0;
				if (todo == 's') goX++, fx = 1;
				if (todo == 'a') goY--, fx = 2;
				if (todo == 'w') goX--, fx = 3;
				if (in(goX, goY) && (overworld[goX][goY] < 5 || overworld[goX][goY] == 11 || overworld[goX][goY] == 17 || overworld[goX][goY] == 18)) {
					overworld[goX][goY] = 10;
					overworld[x][y] = 0;
					x = goX, y = goY;
					step++;
				}
			} else if (todo == 'r') {
				return ;
			} else if (todo == 'o') {
				goX = x, goY = y;
				if (fx == 0) goY++, fx = 0;
				if (fx == 1) goX++, fx = 1;
				if (fx == 2) goY--, fx = 2;
				if (fx == 3) goX--, fx = 3;
				if (in(goX, goY) && (abs(goX - x) < 2 && abs(goY - y) < 2) && overworld[goX][goY] == 8) {
					chest();
					overworld[goX][goY] = 0;
					if (progress[3] == 0) {
						progress[3] = 1;
						printf("玩家刚刚获得了进度");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
						printf("[这是什么？箱子！]");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
						printf("!\n");
						Sleep(2000);
					}
				}
			} else if (todo == 'k') {
				for (int dir = 0; dir < 4; dir++) {
					int killX = x + cx[dir], killY = y + cy[dir];
					for (int i = 1; i <= zombie_sum; i++) {
						if (killX == zombie[i].x && killY == zombie[i].y) {
							zombie[i].hp--;
							if (overworld[killX][killY] == ZOMBIE_3) overworld[killX][killY] = ZOMBIE_2;
							else if (overworld[killX][killY] == ZOMBIE_2) overworld[killX][killY] = ZOMBIE_1;
							else if (overworld[killX][killY] == ZOMBIE_1) {
								overworld[killX][killY] = DIRT;
								int getZombieMeat = rand() % 5;
								zombie[i].x = 0, zombie[i].y = 0;
								printf("玩家 击杀了 僵尸 %d,获取 腐肉 * %d\n", i, getZombieMeat);
								inventory[11] += getZombieMeat;
								Sleep(1000);
								if (progress[1] == 0) {
									progress[1] = 1;
									printf("玩家刚刚获得了进度");
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
						if (killX == skeleton[i].x && killY == skeleton[i].y) {
							skeleton[i].hp--;
							if (overworld[killX][killY] == SKELETON_3) overworld[killX][killY] = SKELETON_2;
							else if (overworld[killX][killY] == SKELETON_2) overworld[killX][killY] = SKELETON_1;
							else if (overworld[killX][killY] == SKELETON_1) {
								overworld[killX][killY] = DIRT;
								int getBones = rand() % 4;
								skeleton[i].x = 0, skeleton[i].y = 0;
								printf("玩家 击杀了 骷髅 %d,获取 骨头 * %d\n", i, getBones);
								inventory[12] += getBones;
								Sleep(1000);
								if (progress[1] == 0) {
									progress[1] = 1;
									printf("玩家刚刚获得了进度");
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
			} else if (todo == 'u') {
				system("cls");
				useThing();
			} else if (todo == 'e') {
				seeInventory();
			} else if (todo == 'q') {
				eatFood();
			} else if (todo == '/' && is_order == 1) {
				do_order();
			} else if (todo == '/' && is_order == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
				printf("你没有作弊的权限!\n");
				Sleep(1000);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
			} else if (todo == '1') {
				is_debug = !is_debug;
			} else if (todo == 'p') {
				seeProgress();
			}
			Sleep(1);
			system("cls");
		}
	}
}
int main() {
	srand(time(0));
	game_overworld();
	write_dat();
	return 0;
}
