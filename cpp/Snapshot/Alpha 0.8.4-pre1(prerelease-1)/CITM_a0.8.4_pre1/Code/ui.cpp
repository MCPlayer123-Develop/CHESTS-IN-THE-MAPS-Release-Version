#include "../Lib/game.h"
#include "../Lib/entity.h"
#include "../Lib/map.h"
#include "../Lib/ui.h"
#include "../Lib/save.h"

void options() {
    read_game_settings();
    system("cls");
    while (1) {
        printf(lang["options.exit"].c_str());
        printf(lang["options.language"].c_str());
        printf(lang["options.key_binding"].c_str());
        char options_select = get_key();
        if (options_select == '0') {
            return;
        } else if (options_select == '1') {
            system("cls");
            int selecting = language;
            while (1) {
                printf(lang["options.key_binding_tips"].c_str());
                for (int i = 0; i < 10; i++) {
                    if (selecting == i) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
                    cout << language_name[i] << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                }
                char key_binding_select = get_key();
                if (key_binding_select == 'w') {
                    selecting = max(0, selecting - 1);
                } else if (key_binding_select == 's') {
                    selecting = min(9, selecting + 1);
                } else if (key_binding_select == 13) {
                    language = selecting;
                    lang.clear();
                    read_language_settings();
                } else if (key_binding_select == 'q') {
                    break;
                }
                system("cls");
            }
            save_game_settings();
        } else if (options_select == '2') {
            system("cls");
            int selecting = 0;
            while (1) {
                printf(lang["options.key_binding_tips"].c_str());
                if (selecting == 0) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_right"].c_str(), key_binding[0]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 1) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_down"].c_str(), key_binding[1]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 2) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_left"].c_str(), key_binding[2]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 3) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_up"].c_str(), key_binding[3]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 4) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_menu"].c_str(), key_binding[4]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 5) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_open_chest"].c_str(), key_binding[5]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 6) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_attack"].c_str(), key_binding[6]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 7) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_use_item"].c_str(), key_binding[7]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 8) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_open_inventory"].c_str(), key_binding[8]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 9) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_eat_food"].c_str(), key_binding[9]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 10) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_input_command"].c_str(), key_binding[10]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 11) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_debug_mode"].c_str(), key_binding[11]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                if (selecting == 12) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
                printf(lang["options.key_binding_view_achievements"].c_str(), key_binding[12]);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                char key_binding_select = get_key();
                if (key_binding_select == 'w') {
                    selecting = max(0, selecting - 1);
                } else if (key_binding_select == 's') {
                    selecting = min(12, selecting + 1);
                } else if (key_binding_select == 13) {
                    cout << lang["options.prompt_input_key"];
                    key_binding[selecting] = get_key();
                } else if (key_binding_select == 'q') {
                    break;
                }
                system("cls");
            }
            save_game_settings();
        }
        system("cls");
    }
}

int title_screen() {
    read_game_settings();
    system("cls");
    printf("\n\n\n\n\n");
    printf(lang["title_screen.border_top"].c_str());
    printf(lang["title_screen.game_name1"].c_str());
    printf(lang["title_screen.game_name2"].c_str());
    printf(lang["title_screen.game_name3"].c_str());
    printf(lang["title_screen.game_name4"].c_str());
    printf(lang["title_screen.game_name5"].c_str());
    printf(lang["title_screen.border_bottom"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0B);
    printf("                                              ");
    int slogan_p = rand() % 11;
    cout << Blue_slogan[slogan_p] << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
    printf(lang["title_screen.slogan_nether"].c_str());
    printf(lang["title_screen.slogan_nether_en"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
    printf("\n\n\n\n\n");
    printf(lang["title_screen.menu_start"].c_str());
    printf(lang["title_screen.version"].c_str());
    char title_select = get_key();
    if (title_select == '1') return 1;
    else if (title_select == '2') {
        options();
    }
    return 0;
}

void chest() {
    //开箱子
    system("cls");
    printf(lang["chest.title"].c_str());
    printf(lang["chest.border_top"].c_str());
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
        if (i == 0) printf(lang["chest.item_stone"].c_str(), Item_Total), inventory[0] += Item_Total;
        if (i == 1) printf(lang["chest.item_coal"].c_str(), Item_Total), inventory[1] += Item_Total;
        if (i == 2) printf(lang["chest.item_iron"].c_str(), Item_Total), inventory[2] += Item_Total;
        if (i == 3) printf(lang["chest.item_gold"].c_str(), Item_Total), inventory[3] += Item_Total;
        if (i == 4) printf(lang["chest.item_redstone"].c_str(), Item_Total), inventory[4] += Item_Total;
        if (i == 5) printf(lang["chest.item_lapis"].c_str(), Item_Total), inventory[5] += Item_Total;
        if (i == 6) printf(lang["chest.item_emerald"].c_str(), Item_Total), inventory[6] += Item_Total;
        if (i == 7) printf(lang["chest.item_diamond"].c_str(), Item_Total), inventory[7] += Item_Total;
    }
    int Item_Total = rand() % 4;
    if (Item_Total < 3) Item_Total = 0;
    else if (Item_Total == 3) Item_Total = 1;
    printf(lang["chest.item_flint"].c_str(), Item_Total), inventory[14] += Item_Total;
    int is_soundtrack = rand() % 10, soundtrack = rand() % 2;
    if (is_soundtrack == 0) {
        printf("\n");
        if (soundtrack == 0) printf(lang["chest.tape_happy"].c_str()), inventory[17]++;
        if (soundtrack == 1) printf(lang["chest.tape_stressful"].c_str()), inventory[18]++;
    }
    printf("\n");
    printf(lang["chest.border_bottom"].c_str());
    printf(lang["chest.finish"].c_str());
    system("pause");
    statistics["chests_opend"]++;
    return;
}

void chest_nether() {
    system("cls");
    printf(lang["chest_nether.title"].c_str());
    printf(lang["chest_nether.border_top"].c_str());
    for (int i = 15; i < 17; i++) {
        int Item_Total;
        Item_Total = rand() % 10;
        if (i == 15) printf(lang["chest_nether.item_quartz"].c_str(), Item_Total), inventory[15] += Item_Total;
        if (i == 16) printf(lang["chest_nether.item_glowstone"].c_str(), Item_Total), inventory[16] += Item_Total;
    }
    int is_soundtrack = rand() % 10;
    if (is_soundtrack == 0) {
        printf(lang["chest_nether.item_tape_lava_zombie"].c_str()), inventory[19]++;
    }
    printf(lang["chest_nether.border_bottom"].c_str());
    printf(lang["chest_nether.finish"].c_str());
    system("pause");
    statistics["chests_opend"]++;
    return;
}

void shop() {
    //商店
    system("cls");
    while (1) {
        int shopSelect;
        printf(lang["shop.welcome"].c_str());
        printf(lang["shop.menu"].c_str());
        printf(lang["shop.menu_buy"].c_str());
        scanf("%d", &shopSelect);
        if (shopSelect == 0) {
            printf(lang["shop.money"].c_str(), money);
            printf(lang["shop.item_ender_pearl"].c_str());
            printf(lang["shop.item_heal_potion"].c_str());
            printf(lang["shop.item_damage_potion"].c_str());
            printf(lang["shop.item_bread"].c_str());
            printf(lang["shop.prompt_buy"].c_str());
            int buy, buyS;
            scanf("%d%d", &buy, &buyS);
            if (buy == 1) {
                if (money >= item_prize[8] * buyS) {
                    inventory[8] += buyS, money -= item_prize[8] * buyS;
                } else {
                    printf(lang["shop.money_not_enough"].c_str());
                    Sleep(2000);
                }
            } else if (buy == 2) {
                if (money >= item_prize[9] * buyS) {
                    inventory[9] += buyS, money -= item_prize[9] * buyS;
                } else {
                    printf(lang["shop.money_not_enough"].c_str());
                    Sleep(2000);
                }
            } else if (buy == 3) {
                if (money >= item_prize[10] * buyS) {
                    inventory[10] += buyS, money -= item_prize[10] * buyS;
                } else {
                    printf(lang["shop.money_not_enough"].c_str());
                    Sleep(2000);
                }
            } else if (buy == 4) {
                if (money >= item_prize[13] * buyS) {
                    inventory[13] += buyS, money -= item_prize[13] * buyS;
                } else {
                    printf(lang["shop.money_not_enough"].c_str());
                    Sleep(2000);
                }
            }
        }
        if (shopSelect == 1) {
            printf(lang["shop.money"].c_str(), money);
            for (int i = 0; i < 8; i++) {
                money += inventory[i] * item_prize[i], inventory[i] = 0;
            }
            for (int i = 15; i < 17; i++) {
                money += inventory[i] * item_prize[i], inventory[i] = 0;
            }
            printf(lang["shop.deal_success"].c_str(), money);
            Sleep(1000);
        }
        if (shopSelect == 2) {
            return;
        }
        system("cls");
    }
}

void useItem() {
    printf(lang["useItem.title"].c_str());
    printf(lang["useItem.border_top"].c_str());
    printf(lang["useItem.item_ender_pearl"].c_str(), inventory[8]);
    printf(lang["useItem.item_heal_potion"].c_str(), inventory[9]);
    printf(lang["useItem.item_damage_potion"].c_str(), inventory[10]);
    printf(lang["useItem.item_flint"].c_str(), inventory[14]);
    printf(lang["useItem.item_tape_happy"].c_str(), inventory[17]);
    printf(lang["useItem.item_tape_stressful"].c_str(), inventory[18]);
    printf(lang["useItem.item_tape_lava_zombie"].c_str(), inventory[19]);
    printf(lang["useItem.border_bottom"].c_str());
    printf(lang["useItem.prompt_select"].c_str());
    int useSelect;
    scanf("%d", &useSelect);
    if (useSelect == 1 && inventory[8] > 0) {
        inventory[8]--;
        printf(lang["useItem.ender_pearl_prompt"].c_str());
        int Ender_Pearl_X, Ender_Pearl_Y;
        scanf("%d%d", &Ender_Pearl_X, &Ender_Pearl_Y);
        Ender_Pearl_X = min(Ender_Pearl_X, x + 4), Ender_Pearl_Y = min(Ender_Pearl_Y, y + 4);
        Ender_Pearl_X = max(Ender_Pearl_X, x - 4), Ender_Pearl_Y = max(Ender_Pearl_Y, y - 4);
        overworld[x][y] = 0;
        x = Ender_Pearl_X, y = Ender_Pearl_Y;
        printf(lang["useItem.ender_pearl_teleport"].c_str(), x, y);
        Sleep(1000);
        statistics["ender_pearl_used"] += 1;
    }
    if (useSelect == 2 && inventory[9] > 0) {
        inventory[9]--;
        health = 20;
        printf(lang["useItem.heal_potion_restore"].c_str());
        statistics["potion_used"] += 1;
    }
    if (useSelect == 3 && inventory[10] > 0) {
        inventory[10]--;
        for (int i = max(1, x - 2); i <= min(n, x + 2); i++) {
            for (int j = max(1, y - 2); j <= min(n, y + 2); j++) {
                for (int k = 1; k <= zombie_sum; k++) {
                    if (zombie[k].x == i && zombie[k].y == j) {
                        overworld[zombie[k].x][zombie[k].y] = 0;
                        zombie[k].x = 0, zombie[k].y = 0;
                        printf(lang["useItem.damage_potion_zombie"].c_str(), k);
                    }
                }
                for (int k = 1; k <= skeleton_sum; k++) {
                    if (skeleton[k].x == i && skeleton[k].y == j) {
                        overworld[skeleton[k].x][skeleton[k].y] = 0;
                        skeleton[k].x = 0, skeleton[k].y = 0;
                        printf(lang["useItem.damage_potion_skeleton"].c_str(), k);
                    }
                }
            }
        }
        Sleep(1000);
        statistics["potion_used"] += 1;
    }
    if (useSelect == 4 && inventory[14] > 0) {
        bool is_Found_Door = 0;
        for (int i = 0; i < 4; i++) {
            int tx = x + direction_x[i], ty = y + direction_y[i];
            if (overworld[tx][ty] == 11) {
                overworld[tx][ty] = 18;
                is_Found_Door = 1;
            }
        }
        if (is_Found_Door == 0) {
            printf(lang["useItem.flint_no_door"].c_str());
        } else if (is_Found_Door == 1) {
            inventory[14]--;
            printf(lang["useItem.flint_activate_portal"].c_str());
            portal_status = 1;
            if (advancements[6] == 0) {
                advancements[6] = 1;
                printf(lang["useItem.advancement_new_dimension"].c_str());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
                printf(lang["useItem.advancement_new_dimension_name"].c_str());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                printf(lang["useItem.advancement_new_dimension_suffix"].c_str());
                Sleep(2000);
            }
        }
        Sleep(1000);
    }
    if (useSelect == 5 && inventory[17] > 0) {
        system("start Happy_Chests.mp3");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["useItem.tape_playing_happy"].c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
        system("pause");
        statistics["tape_played"] += 1;
    }
    if (useSelect == 6 && inventory[18] > 0) {
        system("start Stressful.mp3");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["useItem.tape_playing_stressful"].c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
        system("pause");
        statistics["tape_played"] += 1;
    }
    if (useSelect == 7 && inventory[19] > 0) {
        system("start Lava_Zombie.wav");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["useItem.tape_playing_lava_zombie"].c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
        system("pause");
        statistics["tape_played"] += 1;
    }
}

void useItem_nether() {
    printf(lang["useItem_nether.title"].c_str());
    printf(lang["useItem_nether.border_top"].c_str());
    printf(lang["useItem_nether.item_ender_pearl"].c_str(), inventory[8]);
    printf(lang["useItem_nether.item_heal_potion"].c_str(), inventory[9]);
    printf(lang["useItem_nether.item_damage_potion"].c_str(), inventory[10]);
    printf(lang["useItem_nether.item_tape_happy"].c_str(), inventory[17]);
    printf(lang["useItem_nether.item_tape_stressful"].c_str(), inventory[18]);
    printf(lang["useItem_nether.item_tape_lava_zombie"].c_str(), inventory[19]);
    printf(lang["useItem_nether.border_bottom"].c_str());
    printf(lang["useItem_nether.prompt_select"].c_str());
    int useSelect;
    scanf("%d", &useSelect);
    if (useSelect == 1 && inventory[8] > 0) {
        inventory[8]--;
        printf(lang["useItem_nether.ender_pearl_prompt"].c_str());
        int Ender_Pearl_X, Ender_Pearl_Y;
        scanf("%d%d", &Ender_Pearl_X, &Ender_Pearl_Y);
        Ender_Pearl_X = min(Ender_Pearl_X, x + 4), Ender_Pearl_Y = min(Ender_Pearl_Y, y + 4);
        Ender_Pearl_X = max(Ender_Pearl_X, x - 4), Ender_Pearl_Y = max(Ender_Pearl_Y, y - 4);
        nether[x][y] = NETHER_STONE;
        x = Ender_Pearl_X, y = Ender_Pearl_Y;
        printf(lang["useItem_nether.ender_pearl_teleport"].c_str(), x, y);
        nether[x][y] = NETHER_PLAYER;
        Sleep(1000);
        statistics["ender_pearl_used"] += 1;
    }
    if (useSelect == 2 && inventory[9] > 0) {
        inventory[9]--;
        health = 20;
        printf(lang["useItem_nether.heal_potion_restore"].c_str());
        statistics["potion_used"] += 1;
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
                for (int k = 1; k <= blaze_sum; k++) {
                    if (blaze[k].x == i && blaze[k].y == j) {
                        nether[blaze[k].x][blaze[k].y] = 0;
                        blaze[k].x = 0, blaze[k].y = 0;
                    }
                }
            }
        }
        Sleep(1000);
        statistics["potion_used"] += 1;
    }
    if (useSelect == 4 && inventory[17] > 0) {
        system("start Happy_Chests.mp3");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["useItem_nether.tape_playing_happy"].c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
        system("pause");
        statistics["tape_played"] += 1;
    }
    if (useSelect == 5 && inventory[18] > 0) {
        system("start Stressful.mp3");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["useItem_nether.tape_playing_stressful"].c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
        system("pause");
        statistics["tape_played"] += 1;
    }
    if (useSelect == 6 && inventory[19] > 0) {
        system("start Lava_Zombie.wav");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["useItem_nether.tape_playing_lava_zombie"].c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
        system("pause");
        statistics["tape_played"] += 1;
    }
}

void view_inventory() {
    system("cls");
    int creative_mode_inventory_top = 1, creative_mode_inventory_selecting = 1;
    int materials_items[500] = {0, 1, 2, 3, 4, 5, 6, 7, 12, 15, 16};
    int available_items[500] = {8, 9, 10, 14, 20};
    int food_items[500] = {11, 13};
    while (1) {
        printf(lang["view_inventory.title"].c_str());
        if (gamemode == 1) {
            printf(lang["view_inventory.tips"].c_str());
            if (creative_mode_inventory_top == 1) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
            printf(lang["view_inventory.creative.materials"].c_str()), SetConsoleTextAttribute(
                GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
            if (creative_mode_inventory_top == 2) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
            printf(lang["view_inventory.creative.available_items"].c_str()), SetConsoleTextAttribute(
                GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
            if (creative_mode_inventory_top == 3) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
            printf(lang["view_inventory.creative.food"].c_str()), SetConsoleTextAttribute(
                GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
            if (creative_mode_inventory_top == 4) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xF0); }
            printf(lang["view_inventory.creative.survival_mode_inventory"].c_str()), SetConsoleTextAttribute(
                GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
            printf("\n");

            printf(lang["view_inventory.border_top"].c_str());
            if (creative_mode_inventory_top == 1) {
                for (int i = 0; i < 11; i++) {
                    int idx = materials_items[i];
                    if (creative_mode_inventory_selecting == i) SetConsoleTextAttribute(
                        GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
                    if (idx == 0) printf(lang["view_inventory.item_stone"].c_str(), inventory[idx]);
                    if (idx == 1) printf(lang["view_inventory.item_coal"].c_str(), inventory[idx]);
                    if (idx == 2) printf(lang["view_inventory.item_iron"].c_str(), inventory[idx]);
                    if (idx == 3) printf(lang["view_inventory.item_gold"].c_str(), inventory[idx]);
                    if (idx == 4) printf(lang["view_inventory.item_redstone"].c_str(), inventory[idx]);
                    if (idx == 5) printf(lang["view_inventory.item_lapis"].c_str(), inventory[idx]);
                    if (idx == 6) printf(lang["view_inventory.item_emerald"].c_str(), inventory[idx]);
                    if (idx == 7) printf(lang["view_inventory.item_diamond"].c_str(), inventory[idx]);
                    if (idx == 12) printf(lang["view_inventory.item_bone"].c_str(), inventory[idx]);
                    if (idx == 15) printf(lang["view_inventory.item_quartz"].c_str(), inventory[idx]);
                    if (idx == 16) printf(lang["view_inventory.item_glowstone"].c_str(), inventory[idx]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                }
            } else if (creative_mode_inventory_top == 2) {
                for (int i = 0; i < 5; i++) {
                    int idx = available_items[i];
                    if (creative_mode_inventory_selecting == i) SetConsoleTextAttribute(
                        GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
                    if (idx == 8) printf(lang["view_inventory.item_ender_pearl"].c_str(), inventory[idx]);
                    if (idx == 9) printf(lang["view_inventory.item_heal_potion"].c_str(), inventory[idx]);
                    if (idx == 10) printf(lang["view_inventory.item_damage_potion"].c_str(), inventory[idx]);
                    if (idx == 14) printf(lang["view_inventory.item_flint"].c_str(), inventory[idx]);
                    if (idx == 20) printf(lang["view_inventory.item_ender_key"].c_str(), inventory[idx]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                }
            } else if (creative_mode_inventory_top == 3) {
                for (int i = 0; i < 2; i++) {
                    int idx = food_items[i];
                    if (creative_mode_inventory_selecting == i) SetConsoleTextAttribute(
                        GetStdHandle(STD_OUTPUT_HANDLE), 0xF0);
                    if (idx == 11) printf(lang["view_inventory.item_rotten_flesh"].c_str(), inventory[idx]);
                    if (idx == 13) printf(lang["view_inventory.item_bread"].c_str(), inventory[idx]);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
                }
            } else if (creative_mode_inventory_top == 4) {
                for (int i = 0; i < 21; i++) {
                    if (i == 0) printf(lang["view_inventory.item_stone"].c_str(), inventory[i]);
                    if (i == 1) printf(lang["view_inventory.item_coal"].c_str(), inventory[i]);
                    if (i == 2) printf(lang["view_inventory.item_iron"].c_str(), inventory[i]);
                    if (i == 3) printf(lang["view_inventory.item_gold"].c_str(), inventory[i]);
                    if (i == 4) printf(lang["view_inventory.item_redstone"].c_str(), inventory[i]);
                    if (i == 5) printf(lang["view_inventory.item_lapis"].c_str(), inventory[i]);
                    if (i == 6) printf(lang["view_inventory.item_emerald"].c_str(), inventory[i]);
                    if (i == 7) printf(lang["view_inventory.item_diamond"].c_str(), inventory[i]);
                    if (i == 8) printf(lang["view_inventory.item_ender_pearl"].c_str(), inventory[i]);
                    if (i == 9) printf(lang["view_inventory.item_heal_potion"].c_str(), inventory[i]);
                    if (i == 10) printf(lang["view_inventory.item_damage_potion"].c_str(), inventory[i]);
                    if (i == 11) printf(lang["view_inventory.item_rotten_flesh"].c_str(), inventory[i]);
                    if (i == 12) printf(lang["view_inventory.item_bone"].c_str(), inventory[i]);
                    if (i == 13) printf(lang["view_inventory.item_bread"].c_str(), inventory[i]);
                    if (i == 14) printf(lang["view_inventory.item_flint"].c_str(), inventory[i]);
                    if (i == 15) printf(lang["view_inventory.item_quartz"].c_str(), inventory[i]);
                    if (i == 16) printf(lang["view_inventory.item_glowstone"].c_str(), inventory[i]);
                    if (i == 17) printf(lang["view_inventory.item_tape_happy"].c_str(), inventory[i]);
                    if (i == 18) printf(lang["view_inventory.item_tape_stressful"].c_str(), inventory[i]);
                    if (i == 19) printf(lang["view_inventory.item_tape_lava_zombie"].c_str(), inventory[i]);
                    if (i == 20) printf(lang["view_inventory.item_ender_key"].c_str(), inventory[i]);
                }
            }
            printf(lang["view_inventory.border_bottom"].c_str());
        } else {
            //生存模式物品栏
            printf(lang["view_inventory.tips"].c_str());
            printf(lang["view_inventory.border_top"].c_str());
            for (int i = 0; i < 21; i++) {
                if (i == 0) printf(lang["view_inventory.item_stone"].c_str(), inventory[i]);
                if (i == 1) printf(lang["view_inventory.item_coal"].c_str(), inventory[i]);
                if (i == 2) printf(lang["view_inventory.item_iron"].c_str(), inventory[i]);
                if (i == 3) printf(lang["view_inventory.item_gold"].c_str(), inventory[i]);
                if (i == 4) printf(lang["view_inventory.item_redstone"].c_str(), inventory[i]);
                if (i == 5) printf(lang["view_inventory.item_lapis"].c_str(), inventory[i]);
                if (i == 6) printf(lang["view_inventory.item_emerald"].c_str(), inventory[i]);
                if (i == 7) printf(lang["view_inventory.item_diamond"].c_str(), inventory[i]);
                if (i == 8) printf(lang["view_inventory.item_ender_pearl"].c_str(), inventory[i]);
                if (i == 9) printf(lang["view_inventory.item_heal_potion"].c_str(), inventory[i]);
                if (i == 10) printf(lang["view_inventory.item_damage_potion"].c_str(), inventory[i]);
                if (i == 11) printf(lang["view_inventory.item_rotten_flesh"].c_str(), inventory[i]);
                if (i == 12) printf(lang["view_inventory.item_bone"].c_str(), inventory[i]);
                if (i == 13) printf(lang["view_inventory.item_bread"].c_str(), inventory[i]);
                if (i == 14) printf(lang["view_inventory.item_flint"].c_str(), inventory[i]);
                if (i == 15) printf(lang["view_inventory.item_quartz"].c_str(), inventory[i]);
                if (i == 16) printf(lang["view_inventory.item_glowstone"].c_str(), inventory[i]);
                if (i == 17) printf(lang["view_inventory.item_tape_happy"].c_str(), inventory[i]);
                if (i == 18) printf(lang["view_inventory.item_tape_stressful"].c_str(), inventory[i]);
                if (i == 19) printf(lang["view_inventory.item_tape_lava_zombie"].c_str(), inventory[i]);
                if (i == 20) printf(lang["view_inventory.item_ender_key"].c_str(), inventory[i]);
            }
            printf(lang["view_inventory.border_bottom"].c_str());
        }

        char todo = getch();
        int idx_max[5] = {0, 11, 5, 2};
        if (todo == 'q' && gamemode == 1) {
            creative_mode_inventory_top = max(1, creative_mode_inventory_top - 1);
            creative_mode_inventory_selecting = 0;
        } else if (todo == 'e' && gamemode == 1) {
            creative_mode_inventory_top = min(4, creative_mode_inventory_top + 1);
            creative_mode_inventory_selecting = 0;
        } else if (todo == 'w' && gamemode == 1) {
            creative_mode_inventory_selecting = max(0, creative_mode_inventory_selecting - 1);
        } else if (todo == 's' && gamemode == 1) {
            creative_mode_inventory_selecting = min(idx_max[creative_mode_inventory_top] - 1,
                                                    creative_mode_inventory_selecting + 1);
        } else if (todo == 'r') {
            return;
        } else if (todo == 13) {
            printf(lang["view_inventory.creative.take_item"].c_str());
            int take_item_cnt, take_item_idx;
            cin >> take_item_cnt;
            if (creative_mode_inventory_top == 1) {take_item_idx = materials_items[creative_mode_inventory_selecting];}
            if (creative_mode_inventory_top == 2) {take_item_idx = available_items[creative_mode_inventory_selecting];}
            if (creative_mode_inventory_top == 3) {take_item_idx = food_items[creative_mode_inventory_selecting];}
            take_item_cnt = min(0, take_item_cnt);
            take_item_cnt = max(64, take_item_cnt);
            inventory[take_item_idx] = take_item_cnt;
        }
        system("cls");
    }
}

void eatFood() {
    printf(lang["eatFood.title"].c_str());
    printf(lang["eatFood.border_top"].c_str());
    printf(lang["eatFood.item_rotten_flesh"].c_str(), inventory[11]);
    printf(lang["eatFood.item_bread"].c_str(), inventory[13]);
    printf(lang["eatFood.border_bottom"].c_str());
    int foodSelect, foodS;
    printf(lang["eatFood.prompt_select"].c_str());
    scanf("%d%d", &foodSelect, &foodS);
    if (foodSelect == 1) {
        foodS = min(foodS, inventory[11]);
        inventory[11] -= foodS;
        hunger = min(20, hunger + foodS * 1);
        statistics["food_ate"] += foodS;
    }
    if (foodSelect == 2) {
        foodS = min(foodS, inventory[13]);
        inventory[13] -= foodS;
        hunger = min(20, hunger + foodS * 3);
        statistics["food_ate"] += foodS;
    }
    return;
}

void view_advancements() {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.title"].c_str());
    printf(lang["view_advancements.overworld_title"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
    printf(lang["view_advancements.adv1_name"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.adv1_desc"].c_str());
    if (advancements[1] == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["view_advancements.adv1_unlocked"].c_str());
    } else printf(lang["view_advancements.adv1_locked"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
    printf(lang["view_advancements.adv2_name"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.adv2_desc"].c_str());
    if (advancements[2] == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["view_advancements.adv2_unlocked"].c_str());
    } else printf(lang["view_advancements.adv2_locked"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
    printf(lang["view_advancements.adv3_name"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.adv3_desc"].c_str());
    if (advancements[3] == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["view_advancements.adv3_unlocked"].c_str());
    } else printf(lang["view_advancements.adv3_locked"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
    printf(lang["view_advancements.adv4_name"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.adv4_desc"].c_str());
    if (advancements[4] == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["view_advancements.adv4_unlocked"].c_str());
    } else printf(lang["view_advancements.adv4_locked"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
    printf(lang["view_advancements.adv5_name"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.adv5_desc"].c_str());
    if (advancements[5] == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["view_advancements.adv5_unlocked"].c_str());
    } else printf(lang["view_advancements.adv5_locked"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.nether_title"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
    printf(lang["view_advancements.adv6_name"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.adv6_desc"].c_str());
    if (advancements[6] == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["view_advancements.adv6_unlocked"].c_str());
    } else printf(lang["view_advancements.adv6_locked"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
    printf(lang["view_advancements.adv7_name"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.adv7_desc"].c_str());
    if (advancements[7] == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["view_advancements.adv7_unlocked"].c_str());
    } else printf(lang["view_advancements.adv7_locked"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
    printf(lang["view_advancements.adv8_name"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.adv8_desc"].c_str());
    if (advancements[8] == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["view_advancements.adv8_unlocked"].c_str());
    } else printf(lang["view_advancements.adv8_locked"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
    printf(lang["view_advancements.adv9_name"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(lang["view_advancements.adv9_desc"].c_str());
    if (advancements[9] == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
        printf(lang["view_advancements.adv9_unlocked"].c_str());
    } else printf(lang["view_advancements.adv9_locked"].c_str());
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
    system("pause");
}

void command() {
    printf(lang["command.prompt"].c_str());
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
                printf(lang["command.kill_entity_all"].c_str(), zombie_sum);
                Sleep(1000);
            } else {
                int temp = stoi(order[p]);
                overworld[zombie[temp].x][zombie[temp].y] = 0;
                zombie[temp] = {0, 0, 0, 0};
                printf(lang["command.kill_zombie"].c_str(), temp);
                Sleep(1000);
            }
        } else if (order[p] == "chest:skeleton") {
            cin >> order[++p];
            if (order[p] == "all") {
                for (int i = 1; i <= skeleton_sum; i++) {
                    overworld[skeleton[i].x][skeleton[i].y] = 0;
                    skeleton[i] = {0, 0, 0, 0};
                }
                printf(lang["command.kill_entity_all"].c_str(), skeleton_sum);
                Sleep(1000);
            } else {
                int temp = stoi(order[p]);
                overworld[skeleton[temp].x][skeleton[temp].y] = 0;
                skeleton[temp] = {0, 0, 0, 0};
                printf(lang["command.kill_skeleton"].c_str(), temp);
                Sleep(1000);
            }
        } else if (order[p] == "chest:lava_zombie") {
            cin >> order[++p];
            if (order[p] == "all") {
                for (int i = 1; i <= lava_zombie_sum; i++) {
                    nether[lava_zombie[i].x][lava_zombie[i].y] = 0;
                    lava_zombie[i] = {0, 0, 0, 0};
                }
                printf(lang["command.kill_entity_all"].c_str(), lava_zombie_sum);
                Sleep(1000);
            } else {
                int temp = stoi(order[p]);
                nether[lava_zombie[temp].x][lava_zombie[temp].y] = 0;
                lava_zombie[temp] = {0, 0, 0, 0};
                printf(lang["command.kill_lava_zombie"].c_str(), temp);
                Sleep(1000);
            }
        } else if (order[p] == "chest:burn_skeleton") {
            cin >> order[++p];
            if (order[p] == "all") {
                for (int i = 1; i <= burn_skeleton_sum; i++) {
                    nether[burn_skeleton[i].x][burn_skeleton[i].y] = 0;
                    burn_skeleton[i] = {0, 0, 0, 0};
                }
                printf(lang["command.kill_entity_all"].c_str(), burn_skeleton_sum);
                Sleep(1000);
            } else {
                int temp = stoi(order[p]);
                nether[burn_skeleton[temp].x][burn_skeleton[temp].y] = 0;
                burn_skeleton[temp] = {0, 0, 0, 0};
                printf(lang["command.kill_burn_skeleton"].c_str(), temp);
                Sleep(1000);
            }
        } else if (order[p] == "chest:blaze") {
            cin >> order[++p];
            if (order[p] == "all") {
                for (int i = 1; i <= blaze_sum; i++) {
                    nether[blaze[i].x][blaze[i].y] = 0;
                    blaze[i] = {0, 0, 0, 0};
                }
                printf(lang["command.kill_entity_all"].c_str(), blaze_sum);
                Sleep(1000);
            } else {
                int temp = stoi(order[p]);
                nether[blaze[temp].x][blaze[temp].y] = 0;
                blaze[temp] = {0, 0, 0, 0};
                printf(lang["command.kill_blaze"].c_str(), temp);
                Sleep(1000);
            }
        } else if (order[p] == "chest:player") {
            health = 0, hunger = 1, death_message = "You were been killed.";
            printf(lang["command.kill_player"].c_str());
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
            health = 0, hunger = 1, death_message = "You were been killed.";
            printf(lang["command.kill_all_total"].c_str(),
                   zombie_sum + skeleton_sum + lava_zombie_sum + burn_skeleton_sum + 1);
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
        printf(lang["command.give_item"].c_str(), item_count, order[p - 1].c_str());
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
    } else if (order[p] == "MCPlayer123" || order[p] == "mcplayer") {
        eggs_mcplayer123();
    } else if (order[p] == "help") {
        printf(lang["command.help_title"].c_str());
        printf(lang["command.help_desc1"].c_str());
        printf(lang["command.help_desc2"].c_str());
        printf(lang["command.help_desc3"].c_str());
        printf(lang["command.help_desc4"].c_str());
        printf(lang["command.help_desc5"].c_str());
        printf(lang["command.help_desc6"].c_str());
        printf(lang["command.help_bottom"].c_str());
        system("pause");
    } else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
        printf(lang["command.command_invalid"].c_str());
        Sleep(1000);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
    }
    statistics["command_used"] += 1;
}

void statistic() {
    system("cls");
    printf(lang["statistic.title_opened_chests"].c_str(), statistics["chests_opend"]);
    printf(lang["statistic.title_damage_taken"].c_str(), statistics["damage_taken"]);
    printf(lang["statistic.title_damage_dealt"].c_str(), statistics["damage_dealt"]);
    printf(lang["statistic.title_distance_walked"].c_str(), statistics["distance_walked"]);
    printf(lang["statistic.title_food_ate"].c_str(), statistics["food_ate"]);
    printf(lang["statistic.title_game_quit"].c_str(), statistics["game_quit"]);
    printf(lang["statistic.title_mob_kills"].c_str(), statistics["mob_kills"]);
    printf(lang["statistic.title_tape_played"].c_str(), statistics["tape_played"]);
    printf(lang["statistic.title_ender_pearl_used"].c_str(), statistics["ender_pearl_used"]);
    printf(lang["statistic.title_potion_used"].c_str(), statistics["potion_used"]);
    printf(lang["statistic.title_command_used"].c_str(), statistics["command_used"]);
    system("pause");
}

int game_menu() {
    system("cls");
    printf(lang["game_menu.border_top"].c_str());
    printf(lang["game_menu.title"].c_str());
    printf(lang["game_menu.resume"].c_str());
    printf(lang["game_menu.adv_stats"].c_str());
    printf(lang["game_menu.feedback_bug"].c_str());
    printf(lang["game_menu.options"].c_str());
    printf(lang["game_menu.save_quit"].c_str());
    printf(lang["game_menu.border_bottom"].c_str());
    char game_menu_select = get_key();
    if (game_menu_select == '0') { return 0; } else if (game_menu_select == '1') { view_advancements(); } else if (
        game_menu_select == '2') { statistic(); } else if (game_menu_select == '3' || game_menu_select == '4') {
        system("cls");
        printf(lang["game_menu.feedback_tip"].c_str());
        printf(lang["game_menu.feedback_menu"].c_str());
        char report_bugs_select = get_key();
        if (report_bugs_select == '0') { system("start https://www.luogu.com.cn/discuss/1284936"); }
    } else if (game_menu_select == '5') { options(); } else if (game_menu_select == '6') {
        system("cls");
        return 1;
    }
    return 0;
}
