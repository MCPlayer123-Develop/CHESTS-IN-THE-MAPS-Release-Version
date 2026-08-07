#include "../Lib/game.h"
#include "../Lib/entity.h"
#include "../Lib/map.h"
#include "../Lib/ui.h"
#include "../Lib/save.h"
#include "../Lib/game_nether.h"
#include "../Lib/player.h"

int player_died() {
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
            return 1;
        }
        if (die_select == 2) {
            write_game_data(true);
            system("cls");
            return 2;
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
            return 3;
        }
    }
    return -1;
}

void player_attack_overworld() {
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
}

void player_attack_nether() {
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
}
