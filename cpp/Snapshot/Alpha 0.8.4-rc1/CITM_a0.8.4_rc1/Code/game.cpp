#include "../Lib/game.h"
#include "../Lib/entity.h"
#include "../Lib/map.h"
#include "../Lib/ui.h"
#include "../Lib/save.h"
using namespace std;
int n, inventory[500], x, y, facing, money = 0, health = 20, hunger = 20, hunger_step_summary = 0, biome_fest;
int overworld[N][N];
int nether[N][N];
int direction_x[4] = {0, 1, 0, -1};
int direction_y[4] = {1, 0, -1, 0};
int allow_command, is_regeneration_world, keepInventory, burn_time = 0, gamemode;
int vis[N][N], advancements[105], flag = 0, portal_status = 0, debug_screen = 0, nether_return = 0;
int item_prize[30] = {
    1, 5, 100, 100, 200, 300, 1000, 5000, 100000, 500000, 300000, 0, 0, 10, 0, 100000, 200000, 0, 0, 0, 0
};
string world_name = "";
char key_binding[30] = {
    'd', 's', 'a', 'w', 13, 'o', 'k', 'u', 'e', 'q', '/', '1', 'p'
};

int zombie_sum, skeleton_sum, lava_zombie_sum, burn_skeleton_sum, arrow_sum, burn_arrow_sum, blaze_sum, fire_charge_sum;
MobData zombie[MAXN_MOB], skeleton[MAXN_MOB];
MobData lava_zombie[MAXN_MOB], burn_skeleton[MAXN_MOB], blaze[MAXN_MOB];
MobData arrow[MAXN_MOB], burn_arrow[MAXN_MOB], fire_charge[MAXN_MOB];

vector<mssg> message_list;

vector<string> getAllDatSave() {
    vector<string> list;
    WIN32_FIND_DATA ffd;
    HANDLE hFind = FindFirstFile("../Saves/*.dat", &ffd);
    if (hFind == INVALID_HANDLE_VALUE) {
        hFind = FindFirstFile("Saves/*.dat", &ffd);
    }
    do {
        if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0) continue;
        string name = ffd.cFileName;
        size_t pos = name.rfind(".dat");
        if (pos != string::npos && pos == name.size() - 4) {
            list.push_back(name);
        }
    } while (FindNextFile(hFind, &ffd));
    FindClose(hFind);
    return list;
}

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

map<int, char> num_to_char_print_map{
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
map<int, int> block_color = {
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
map<int, int> block_color_nether{
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
map<string, int> item{
    {"chest:cobblestone", 0},
    {"chest:coal", 1},
    {"chest:iron_ingot", 2},
    {"chest:gold_ingot", 3},
    {"chest:redstone", 4},
    {"chest:lapis_lazuli", 5},
    {"chest:emerald", 6},
    {"chest:diamond", 7},
    {"chest:ender_pearl", 8},
    {"chest:potion_of_healing", 9},
    {"chest:splash_potion_of_harming", 10},
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
map<string, int> block_overworld{
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
map<string, int> block_nether{
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
map<string, int> statistics{
    {"chests_opend", 0},
    {"damage_taken", 0},
    {"damage_dealt", 0},
    {"distance_walked", 0},
    {"food_ate", 0},
    {"game_quit", 0},
    {"mob_kills", 0},
    {"tape_played", 0},
    {"ender_pearl_used", 0},
    {"potion_used", 0},
    {"command_used", 0}
};
map<int, string> statistics_name{
    {1, "chests_opend"},
    {2, "damage_taken"},
    {3, "damage_dealt"},
    {4, "distance_walked"},
    {5, "food_ate"},
    {6, "game_quit"},
    {7, "mob_kills"},
    {8, "tape_played"},
    {9, "ender_pearl_used"},
    {10, "potion_used"},
    {11, "command_used"}
};
map<string, string> lang = {};
int language = 1;
string language_name[1005] = {
    "English (US)",
    "简体中文（中国大陆）",
    "繁體中文（香港特別行政區）",
    "Français (France)",
    "Русский (Россия)",
    "العربية",
    "Español (España)",
    "portugués (Portugal)",
    "日本語 (日本語)",
    "Deutsch (Deutschland)",
    "So Far Away Language (Far Away)",
    "LOLCAT (Kingdom of Cats)",
    "文言 (華夏)",
    "Русский (СССР)"
};
string language_file_name[1005] = {
    "en_US.txt", "zh_CN.txt", "zh_HK.txt", "fr.txt", "ru.txt", "ar.txt", "sp.txt", "pr.txt", "ja.txt", "de_DE.txt", "So_Far_Away.txt", "lol_us.txt", "lzh.txt", "ru_cccp.txt"
};

bool in(int x, int y) {
    return (x >= 1 && x <= n && y >= 1 && y <= n);
}

void checkRoad(int x, int y) {
    //检测是否有路
    if (x == n - 1 && y == n - 1) {
        flag = 1;
        return;
    }
    if (overworld[x][y] > 5) {
        return;
    }
    vis[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int tx = x + direction_x[i], ty = y + direction_y[i];
        if (in(tx, ty) && (overworld[tx][ty] < 5 || overworld[tx][ty] == 11) && vis[tx][ty] == 0) {
            checkRoad(tx, ty);
        }
    }
    return;
}

int nether_block_check(int nether_x, int nether_y) {
    int nether_mid;
    if (n % 2 == 0) nether_mid = n / 2;
    else if (n % 2 == 1) nether_mid = (n + 1) / 2;
    if ((nether_x >= nether_mid - 1 && nether_x <= nether_mid + 1) || (
            nether_y >= nether_mid - 1 && nether_y <= nether_mid + 1)) {
        return NETHER_BRICK;
    } else {
        return NETHER_STONE;
    }
}

char get_key() {
    while (!_kbhit()) Sleep(1);
    return _getch();
}

string get_version(string get_version_world_name) {
    string read_path = "../Saves/" + get_version_world_name;
    FILE *fp = fopen(read_path.c_str(), "r");
    if (fp == NULL) read_path = "Saves/" + get_version_world_name, fp = fopen(read_path.c_str(), "r");
    string version = "";
    char buf[1005];
    fscanf(fp, "%s", buf);
    version = buf;
    fclose(fp);
    return version;
}
void init_game_data() {
    n = 0, x = 0, y = 0, money = 0, health = 0, hunger = 0, hunger_step_summary = 0;
    memset(overworld, 0, sizeof(overworld));
    memset(nether, 0, sizeof(nether));
    allow_command = is_regeneration_world = keepInventory = burn_time = gamemode = 0;
    memset(vis, 0, sizeof(vis));
    memset(advancements, 0, sizeof(advancements));
    memset(inventory, 0, sizeof(inventory));
    flag = portal_status = debug_screen = nether_return = 0;
    world_name = death_message = "";
    zombie_sum = skeleton_sum = lava_zombie_sum = burn_skeleton_sum = blaze_sum = arrow_sum = burn_arrow_sum = fire_charge_sum = 0;
    while (!message_list.empty()) {message_list.erase(message_list.begin());}
}

void game_nether(int regeneration) {
    system("cls");
    system("color 0C");
    system("color 5F");
    printf("\n\n\n\n\n\n                                                  ");
    printf(lang["game_overworld.download_terrain"].c_str());
    Sleep(3000);
    system("cls");
    system("color 0C");
    if (regeneration == 1) generation_world_nether();
    while (1) {
        if (gamemode == 1) health = 20, hunger = 20;
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
        if (burn_time > 0) {
            //燃烧
            burn_time--, health--;
            statistics["damage_taken"] += 1;
            statistics["damage_dealt"] += 1;
            if (health <= 0) {
                death_message = "You were burn to death.";
            }
        }
        if (hunger_step_summary == 10) {
            //更新饱食度
            hunger--, hunger_step_summary = 0;
            nether_return = 1;
            write_game_data(0);
            nether_return = 0;
        }
        if (hunger == 20) {
            health++;
            health = min(health, 20);
        }
        if (hunger == 0) {
            health--;
            statistics["damage_taken"] += 1;
            if (health <= 0) {
                death_message = "You starved to death.";
            }
        }
        if (health <= 0) {
            if (advancements[5] == 0) {
                advancements[5] = 1;
                printf(lang["game_overworld.advancement_prefix"].c_str());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
                printf(lang["view_advancements.adv5_name"].c_str());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                printf(lang["game_overworld.advancement_suffix"].c_str());
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
                printf(lang["game_overworld.death_message"].c_str());
                printf("\n\n\n");
                printf("                        ");
                cout << death_message;
                printf("\n\n\n");
                int die_select;
                printf(lang["game_overworld.death_options"].c_str());
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        overworld[i][j] = nether[i][j] = 0;
                    }
                }
                if (!keepInventory) money = 0, memset(inventory, 0, sizeof(inventory));
                write_game_data(0);
                arrow_sum = 0;
                for (int i = 1; i <= arrow_sum; i++) {
                    arrow[i].x = 0, arrow[i].y = 0;
                }
                portal_status = 0;
                cin >> die_select;
                if (die_select == 0) {
                    write_game_data(0);
                    exit(0);
                }
                if (die_select == 1) {
                    system("color 03");
                    break;
                }
                if (die_select == 2) {
                    write_game_data(0);
                    system("cls");
                    return;
                }
            } else if (gamemode == 2) {
                system("cls");
                system("color CF");
                printf("\n\n\n\n\n\n\n");
                printf(lang["game_overworld.death_hardcore"].c_str());
                printf("\n\n\n");
                printf("                        ");
                cout << death_message;
                printf("\n\n\n");
                printf(lang["game_overworld.death_hardcore_options"].c_str());
                int die_select;
                cin >> die_select;
                if (die_select == 0) {
                    string read_path = "del ../Saves/" + world_name;
                    FILE *fp = fopen(read_path.c_str(), "r");
                    if (fp == NULL) read_path = "Saves/" + world_name, fp = fopen(read_path.c_str(), "r");
                    fclose(fp);
                    system(read_path.c_str());
                    exit(0);
                } else {
                    system("cls");
                    system("color 0C");
                    print_map_Nether();
                    system("pause");
                    string read_path = "del ../Saves/" + world_name;
                    FILE *fp = fopen(read_path.c_str(), "r");
                    if (fp == NULL) read_path = "Saves/" + world_name, fp = fopen(read_path.c_str(), "r");
                    fclose(fp);
                    system(read_path.c_str());
                    nether_return = 1;
                    return;
                }
            }
        }
        if (x == 1 && y == 1) {
            system("color 5F");
            printf("\n\n\n\n\n\n                                                  ");
            printf(lang["game_overworld.download_terrain"].c_str());
            Sleep(3000);
            system("cls");
            system("color 03");
            x = 2, y = 2;
            return;
        }
        if (nether_block_check(x, y) == NETHER_BRICK) {
            biome_fest = 2;
        }
        update_mobs_nether();
        print_map_Nether();
        if (advancements[7] == 0) {
            advancements[7] = 1;
            printf(lang["game_overworld.advancement_prefix"].c_str());
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
            printf(lang["view_advancements.adv7_name"].c_str());
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
            printf(lang["game_overworld.advancement_suffix"].c_str());
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
                statistics["distance_walked"] += 1;
            }
        } else if (todo == key_binding[4]) {
            int game_menu_return_val = game_menu();
            if (game_menu_return_val == 1) {
                nether_return = 1;
                return;
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
                        else if (nether[attack_x][attack_y] == LAVA_ZOMBIE_4)
                            nether[attack_x][attack_y] = LAVA_ZOMBIE_3;
                        else if (nether[attack_x][attack_y] == LAVA_ZOMBIE_3)
                            nether[attack_x][attack_y] = LAVA_ZOMBIE_2;
                        else if (nether[attack_x][attack_y] == LAVA_ZOMBIE_2)
                            nether[attack_x][attack_y] = LAVA_ZOMBIE_1;
                        else if (nether[attack_x][attack_y] == LAVA_ZOMBIE_1) {
                            nether[lava_zombie[i].x][lava_zombie[i].y] = nether_block_check(
                                lava_zombie[i].x, lava_zombie[i].y);
                            int getZombieMeat = rand() % 5, getGoldIngot = rand() % 2;
                            lava_zombie[i].x = 0, lava_zombie[i].y = 0;
                            message_list.push_back({
                                lang["game_overworld.kill_lava_zombie"] + lang[
                                    "game_overworld.get_lava_zombie_items"] + to_string(getZombieMeat) + lang[
                                    "game_overworld.get_gold_ingot"] + to_string(getGoldIngot),
                                3
                            });
                            inventory[11] += getZombieMeat;
                            inventory[3] += getGoldIngot;
                            Sleep(1000);
                            if (advancements[1] == 0) {
                                advancements[1] = 1;
                                printf(lang["game_overworld.advancement_prefix"].c_str());
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
                                printf(lang["view_advancements.adv1_name"].c_str());
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
                                printf(lang["game_overworld.advancement_suffix"].c_str());
                                Sleep(2000);
                            }
                            statistics["mob_kills"] += 1;
                        }
                        int zombie_reinforcements = rand() % 10;
                        if (zombie_reinforcements == 0) {
                            int zombie_reinforcements_x, zombie_reinforcements_y;
                            while ((nether[zombie_reinforcements_x][zombie_reinforcements_y] != NETHER_STONE && nether[
                                        zombie_reinforcements_x][zombie_reinforcements_y] != NETHER_BRICK) ||
                                   zombie_reinforcements_x < 1 || zombie_reinforcements_x > n || zombie_reinforcements_y
                                   < 1 || zombie_reinforcements_y > n) {
                                zombie_reinforcements_x = zombie[i].x + (rand() % 5) - 10, zombie_reinforcements_y =
                                        zombie[i].y + (rand() % 10) - 5;
                                zombie_reinforcements_x = min(zombie_reinforcements_x, n);
                                zombie_reinforcements_x = max(zombie_reinforcements_x, 1);
                                zombie_reinforcements_y = min(zombie_reinforcements_y, n);
                                zombie_reinforcements_y = max(zombie_reinforcements_y, 1);
                            }
                            lava_zombie_sum++;
                            lava_zombie[zombie_sum] = {zombie_reinforcements_x, zombie_reinforcements_y, 5, 0};
                            nether[lava_zombie[lava_zombie_sum].x][lava_zombie[lava_zombie_sum].y] = LAVA_ZOMBIE_5;
                        }
                    }
                }
                for (int i = 1; i <= burn_skeleton_sum; i++) {
                    if (attack_x == burn_skeleton[i].x && attack_y == burn_skeleton[i].y) {
                        burn_skeleton[i].health--;
                        if (nether[attack_x][attack_y] == BURN_SKELETON_5) nether[attack_x][attack_y] = BURN_SKELETON_4;
                        else if (nether[attack_x][attack_y] == BURN_SKELETON_4)
                            nether[attack_x][attack_y] = BURN_SKELETON_3;
                        else if (nether[attack_x][attack_y] == BURN_SKELETON_3)
                            nether[attack_x][attack_y] = BURN_SKELETON_2;
                        else if (nether[attack_x][attack_y] == BURN_SKELETON_2)
                            nether[attack_x][attack_y] = BURN_SKELETON_1;
                        else if (nether[attack_x][attack_y] == BURN_SKELETON_1) {
                            nether[burn_skeleton[i].x][burn_skeleton[i].y] = nether_block_check(
                                burn_skeleton[i].x, burn_skeleton[i].y);
                            int getBone = rand() % 5, getFlintAndSteel = rand() % 2;
                            burn_skeleton[i].x = 0, burn_skeleton[i].y = 0;
                            message_list.push_back({
                                lang["game_overworld.kill_burn_skeleton"] + lang[
                                    "game_overworld.get_burn_skeleton_items"] + to_string(getBone) + lang[
                                    "game_overworld.get_flint_and_steel"] + to_string(getFlintAndSteel),
                                3
                            });
                            inventory[12] += getBone;
                            inventory[14] += getFlintAndSteel;
                            Sleep(1000);
                            if (advancements[1] == 0) {
                                advancements[1] = 1;
                                printf(lang["game_overworld.advancement_prefix"].c_str());
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
                                printf(lang["view_advancements.adv1_name"].c_str());
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
                                printf(lang["game_overworld.advancement_suffix"].c_str());
                                Sleep(2000);
                            }
                            statistics["mob_kills"] += 1;
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
                            if (getEndKey == 0) getEndKey = 1;
                            else getEndKey = 0;
                            blaze[i].x = 0, blaze[i].y = 0;
                            message_list.push_back({
                                lang["game_overworld.kill_blaze"] + lang["game_overworld.get_end_key"] +
                                to_string(getEndKey) + lang["game_overworld.get_flint_and_steel"] +
                                to_string(getFlintAndSteel),
                                3
                            });
                            inventory[20] += getEndKey;
                            inventory[14] += getFlintAndSteel;
                            Sleep(1000);
                            if (advancements[1] == 0) {
                                advancements[1] = 1;
                                printf(lang["game_overworld.advancement_prefix"].c_str());
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
                                printf(lang["view_advancements.adv1_name"].c_str());
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
                                printf(lang["game_overworld.advancement_suffix"].c_str());
                                Sleep(2000);
                            }
                            cout << getEndKey << endl;
                            Sleep(1000);
                            if (advancements[9] == 0 && getEndKey > 0) {
                                advancements[9] = 1;
                                printf(lang["game_overworld.advancement_prefix"].c_str());
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
                                printf(lang["view_advancements.adv1_name"].c_str());
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
                                printf(lang["game_overworld.advancement_suffix"].c_str());
                                Sleep(2000);
                            }
                            statistics["mob_kills"] += 1;
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
            return;
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
            view_advancements();
            system("color 0C");
        }
        system("cls");
    }
}

void game_overworld() {
    system("color 03");
    system("cls");
    printf(lang["game_overworld.save"].c_str());
    printf(lang["game_overworld.regenerate"].c_str());
    cin >> is_regeneration_world;
    if (is_regeneration_world == 1) {
        init_game_data();
        printf(lang["game_overworld.options"].c_str());
        printf(lang["game_overworld.world_name"].c_str());
        cin >> world_name;
        world_name += ".dat";
        printf(lang["game_overworld.map_size"].c_str());
        cin >> n;
        n = max(5, n), n = min(20, n);
        printf(lang["game_overworld.gamemode"].c_str());
        cin >> gamemode;
        if (gamemode < 0 || gamemode > 2) gamemode = 0;
        printf(lang["game_overworld.allow_command"].c_str());
        cin >> allow_command;
        printf(lang["game_overworld.game_rules"].c_str());
        printf(lang["game_overworld.keep_inventory"].c_str());
        scanf("%d", &keepInventory);
        skin_char = 'Y', skin_color = 0x9F;
        num_to_char_print_map[PLAYER] = skin_char;
        num_to_char_print_map_nether[NETHER_PLAYER] = skin_char;
        block_color[PLAYER] = skin_color;
        block_color_nether[NETHER_PLAYER] = skin_color;
        generation_world();
    } else if (is_regeneration_world == 0) {
        system("cls");
        int select_world = 0;
        while (1) {
            vector<string> saves = getAllDatSave();
            printf(lang["game_overworld.select_world"].c_str());
            for (int i = 0; i < saves.size(); i++) {
                if (select_world == i) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                cout << saves[i] << " Version:" << get_version(saves[i]) << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
            }
            char todo = getch();
            if (todo == 'w') select_world = max(0, select_world - 1);
            else if (todo == 's') select_world = min((int) saves.size() - 1, select_world + 1);
            else if (todo == 13) {
                if (get_version(saves[select_world]) != "Alpha_0.8.4-rc1") {
                    printf(lang["game_overworld.version_wrong"].c_str(), get_version(saves[select_world]));
                    printf(lang["game_overworld.version_wrong_0"].c_str());
                    printf(lang["game_overworld.version_wrong_1"].c_str());
                    char version_wrong_select = getch();
                    if (version_wrong_select == '0') {continue;}
                    else if (version_wrong_select == '1') {
                        printf(lang["game_overworld.version_wrong_confirm"].c_str());
                        system("pause");
                    }
                }
                world_name = saves[select_world];
                break;
            } else if (todo == 'q') return;
            system("cls");
        }
        read_game_data();
        num_to_char_print_map[PLAYER] = skin_char;
        num_to_char_print_map_nether[NETHER_PLAYER] = skin_char;
        block_color[PLAYER] = skin_color;
        block_color_nether[NETHER_PLAYER] = skin_color;
    }

    system("cls");
    if (is_regeneration_world == 0 && nether_return == 1) {
        nether_return = 0;
        game_nether(0);
        if (nether_return == 1) {
            write_game_data(0);
            return;
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
            if (gamemode == 1) health = 20, hunger = 20;
            for (int i = 1; i <= zombie_sum; i++) {
                //及时渲染怪物
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
            if (burn_time > 0) {
                //燃烧
                burn_time--, health--;
                statistics["damage_taken"] += 1;
                statistics["damage_dealt"] += 1;
                if (health <= 0) {
                    death_message = "You were burn to death.";
                }
            }
            if (hunger_step_summary == 10) {
                //更新饱食度
                hunger--, hunger_step_summary = 0;
                write_game_data(0);
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
                if (advancements[5] == 0) {
                    advancements[5] = 1;
                    printf(lang["game_overworld.advancement_prefix"].c_str());
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
                    printf(lang["view_advancements.adv5_name"].c_str());
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                    printf(lang["game_overworld.advancement_suffix"].c_str());
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
                    printf(lang["game_overworld.death_message"].c_str());
                    printf("\n\n\n");
                    printf("                        ");
                    cout << death_message;
                    printf("\n\n\n");
                    int die_select;
                    printf(lang["game_overworld.death_options"].c_str());
                    for (int i = 1; i <= n; i++) {
                        for (int j = 1; j <= n; j++) {
                            overworld[i][j] = nether[i][j] = 0;
                        }
                    }
                    if (!keepInventory) money = 0, memset(inventory, 0, sizeof(inventory));
                    write_game_data(true);
                    arrow_sum = 0;
                    for (int i = 1; i <= arrow_sum; i++) {
                        arrow[i].x = 0, arrow[i].y = 0;
                    }
                    portal_status = 0;
                    cin >> die_select;
                    if (die_select == 0) {
                        write_game_data(0);
                        exit(0);
                    }
                    if (die_select == 1) {
                        system("color 03");
                        break;
                    }
                    if (die_select == 2) {
                        write_game_data(true);
                        system("cls");
                        return;
                    }
                } else if (gamemode == 2) {
                    system("cls");
                    system("color CF");
                    printf("\n\n\n\n\n\n\n");
                    printf(lang["game_overworld.death_hardcore"].c_str());
                    printf("\n\n\n");
                    printf("                        ");
                    cout << death_message;
                    printf("\n\n\n");
                    printf(lang["game_overworld.death_hardcore_options"].c_str());
                    int die_select;
                    cin >> die_select;
                    if (die_select == 0) {
                        string read_path = "del ../Saves/" + world_name;
                        FILE *fp = fopen(read_path.c_str(), "r");
                        if (fp == NULL) read_path = "Saves/" + world_name, fp = fopen(read_path.c_str(), "r");
                        fclose(fp);
                        system(read_path.c_str());
                        exit(0);
                    } else {
                        system("cls");
                        system("color 03");
                        print_map();
                        system("pause");
                        string read_path = "del ../Saves/" + world_name;
                        FILE *fp = fopen(read_path.c_str(), "r");
                        if (fp == NULL) read_path = "Saves/" + world_name, fp = fopen(read_path.c_str(), "r");
                        fclose(fp);
                        system(read_path.c_str());
                        return;
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
                    statistics["game_quit"] += 1;
                    write_game_data(0);
                    return;
                }
                system("cls");
                system("color 03");
                break;
            }
            if (x == n - 1 && y == n - 1) {
                if (advancements[4] == 0) {
                    advancements[4] = 1;
                    printf(lang["game_overworld.advancement_prefix"].c_str());
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
                    printf(lang["view_advancements.adv4_name"].c_str());
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                    printf(lang["game_overworld.advancement_suffix"].c_str());
                    Sleep(2000);
                    system("cls");
                }
                printf("\n\n\n\n\n\n");
                printf(lang["game_overworld.end_message"].c_str());
                printf("\n\n\n");
                int end_select;
                printf(lang["game_overworld.end_options"].c_str());
                cin >> end_select;
                arrow_sum = 0;
                memset(arrow, 0, sizeof(arrow));
                memset(arrow, 0, sizeof(arrow));
                portal_status = 0;
                if (end_select == 0) {
                    return;
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
                if (in(goX, goY) && (overworld[goX][goY] < 5 || overworld[goX][goY] == 11 || overworld[goX][goY] == 17
                                     || overworld[goX][goY] == 18)) {
                    overworld[goX][goY] = 10;
                    overworld[x][y] = 0;
                    x = goX, y = goY;
                    hunger_step_summary++;
                    statistics["distance_walked"] += 1;
                }
            } else if (todo == key_binding[4]) {
                int game_menu_return_val = game_menu();
                if (game_menu_return_val == 1) {
                    statistics["game_quit"] += 1;
                    write_game_data(0);
                    return;
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
                    if (advancements[3] == 0) {
                        advancements[3] = 1;
                        printf(lang["game_overworld.advancement_prefix"].c_str());
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
                        printf(lang["view_advancements.adv3_name"].c_str());
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                        printf(lang["game_overworld.advancement_suffix"].c_str());
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
                            else if (overworld[attack_x][attack_y] == ZOMBIE_2)
                                overworld[attack_x][attack_y] = ZOMBIE_1;
                            else if (overworld[attack_x][attack_y] == ZOMBIE_1) {
                                overworld[attack_x][attack_y] = DIRT;
                                int getZombieMeat = rand() % 5;
                                zombie[i].x = 0, zombie[i].y = 0;
                                message_list.push_back({
                                    lang["game_overworld.kill_zombie"].c_str() + to_string(i) + lang[
                                        "game_overworld.get_rotten_flesh"].c_str() + to_string(getZombieMeat),
                                    3
                                });
                                inventory[11] += getZombieMeat;
                                Sleep(1000);
                                if (advancements[1] == 0) {
                                    advancements[1] = 1;
                                    printf(lang["game_overworld.advancement_prefix"].c_str());
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
                                    printf(lang["view_advancements.adv1_name"].c_str());
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                                    printf(lang["game_overworld.advancement_suffix"].c_str());
                                    Sleep(2000);
                                }
                                statistics["mob_kills"] += 1;
                            }
                            int zombie_reinforcements = rand() % 10;
                            if (zombie_reinforcements == 0) {
                                int zombie_reinforcements_x, zombie_reinforcements_y;
                                while (overworld[zombie_reinforcements_x][zombie_reinforcements_y] >= WALL ||
                                       zombie_reinforcements_x < 1 || zombie_reinforcements_x > n ||
                                       zombie_reinforcements_y < 1 || zombie_reinforcements_y > n) {
                                    zombie_reinforcements_x = zombie[i].x + (rand() % 5) - 10, zombie_reinforcements_y =
                                            zombie[i].y + (rand() % 10) - 5;
                                    zombie_reinforcements_x = min(zombie_reinforcements_x, n);
                                    zombie_reinforcements_x = max(zombie_reinforcements_x, 1);
                                    zombie_reinforcements_y = min(zombie_reinforcements_y, n);
                                    zombie_reinforcements_y = max(zombie_reinforcements_y, 1);
                                }
                                zombie_sum++;
                                zombie[zombie_sum] = {zombie_reinforcements_x, zombie_reinforcements_y, 3, 0};
                                overworld[zombie[zombie_sum].x][zombie[zombie_sum].y] = ZOMBIE_3;
                            }
                        }
                    }
                    for (int i = 1; i <= skeleton_sum; i++) {
                        if (attack_x == skeleton[i].x && attack_y == skeleton[i].y) {
                            skeleton[i].health--;
                            if (overworld[attack_x][attack_y] == SKELETON_3) overworld[attack_x][attack_y] = SKELETON_2;
                            else if (overworld[attack_x][attack_y] == SKELETON_2)
                                overworld[attack_x][attack_y] = SKELETON_1;
                            else if (overworld[attack_x][attack_y] == SKELETON_1) {
                                overworld[attack_x][attack_y] = DIRT;
                                int getBones = rand() % 4;
                                skeleton[i].x = 0, skeleton[i].y = 0;
                                message_list.push_back({
                                    lang["game_overworld.kill_skeleton"].c_str() + to_string(i) + lang[
                                        "game_overworld.get_bones"].c_str() + to_string(getBones),
                                    3
                                });
                                inventory[12] += getBones;
                                Sleep(1000);
                                if (advancements[1] == 0) {
                                    advancements[1] = 1;
                                    printf(lang["game_overworld.advancement_prefix"].c_str());
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
                                    printf(lang["view_advancements.adv1_name"].c_str());
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                                    printf(lang["game_overworld.advancement_suffix"].c_str());
                                    Sleep(2000);
                                }
                                statistics["mob_kills"] += 1;
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
                printf(lang["game_overworld.no_permission"].c_str());
                Sleep(1000);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
            } else if (todo == key_binding[11]) {
                debug_screen = !debug_screen;
            } else if (todo == key_binding[12]) {
                view_advancements();
            }
            Sleep(1);
            system("cls");
        }
        generation_world();
    }
}

void eggs_mcplayer123() {
    int eggs[N][N], eggs_x = 1, eggs_y = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            eggs[i][j] = 1;
        }
    }
    eggs[eggs_x][eggs_y] = 0, eggs[n][n] = 2;
    while (1) {
        if (eggs_x == n && eggs_y == n) {
            system("cls");
            printf(lang["eggs.mcplayer123_satisfaction"].c_str());
            char eggs_select = getch();
            printf(lang["eggs.mcplayer123_fee"].c_str(), money);
            system("pause");
            money = 0;
            memset(inventory, 0, sizeof(inventory));
            write_game_data(0);
            system(
                "start https://www.bilibili.com/video/BV1GJ411x7h7/?spm_id_from=333.337.search-card.all.click&vd_source=a0cef846b1c0f9cac5d8fbaabe6326e0");
            return;
        }
        system("cls");
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (eggs[i][j] == 0) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), skin_color);
                    cout << '[' << skin_char << ']';
                } else if (eggs[i][j] == 1) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xE0);
                    cout << "[C]";
                } else if (eggs[i][j] == 2) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
                    cout << "[D]";
                } else if (eggs[i][j] == 3) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
                    cout << "[ ]";
                }
            }
            cout << endl;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
        char todo;
        todo = getch();
        int goX = eggs_x, goY = eggs_y;
        if (todo == key_binding[0] || todo == key_binding[1] || todo == key_binding[2] || todo == key_binding[3]) {
            if (todo == key_binding[0]) goY++, facing = 0;
            if (todo == key_binding[1]) goX++, facing = 1;
            if (todo == key_binding[2]) goY--, facing = 2;
            if (todo == key_binding[3]) goX--, facing = 3;
            if (in(goX, goY) && (eggs[goX][goY] == 3 || eggs[goX][goY] == 2)) {
                eggs[goX][goY] = 0;
                eggs[eggs_x][eggs_y] = 3;
                eggs_x = goX, eggs_y = goY;
            }
        } else if (todo == key_binding[5]) {
            goX = eggs_x, goY = eggs_y;
            if (facing == 0) goY++, facing = 0;
            if (facing == 1) goX++, facing = 1;
            if (facing == 2) goY--, facing = 2;
            if (facing == 3) goX--, facing = 3;
            if (in(goX, goY) && (abs(goX - eggs_x) < 2 && abs(goY - eggs_y) < 2) && eggs[goX][goY] == 1.) {
                chest();
                eggs[goX][goY] = 3;
            }
        }
    }
}
