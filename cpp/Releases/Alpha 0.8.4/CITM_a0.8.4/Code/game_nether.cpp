#include "../Lib/game.h"
#include "../Lib/entity.h"
#include "../Lib/map.h"
#include "../Lib/ui.h"
#include "../Lib/save.h"
#include "../Lib/game_nether.h"
#include "../Lib/player.h"

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
            int death_val = player_died();
            if (death_val == 1) break;//Respawn
            else if (death_val == 2) {nether_return = 1; return ;}//Title Screen
            else if (death_val == 3) {nether_return = 1; return ;}//Hardcore Title Screen
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
            player_attack_nether();
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
