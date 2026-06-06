#include "../Lib/game.h"
#include "../Lib/entity.h"
#include "../Lib/map.h"
#include "../Lib/ui.h"
#include "../Lib/save.h"

void read_game_data() {
    string read_path = "../Saves/" + world_name;
    FILE *fp = fopen(read_path.c_str(), "r");
    if (fp == NULL) read_path = "Saves/" + world_name, fp = fopen(read_path.c_str(), "r");
    if (fp != NULL) {
        fscanf(fp, "Alpha_0.8.4-Dev-snapshot260511\n");
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
        fscanf(fp, "advancements = ");
        for (int i = 1; i <= 8; i++) {
            fscanf(fp, "%d,", &advancements[i]);
        }
        fscanf(fp, "\n");
        fscanf(fp, "Portal status = %d\n", &portal_status);
        fscanf(fp, "Debug screen = %d\n", &debug_screen);
        fscanf(fp, "Allow command = %d\n", &allow_command);
        fscanf(fp, "Keep Inventory = %d\n", &keepInventory);
        fscanf(fp, "Gamemode = %d\n", &gamemode);
        fscanf(fp, "Nether Return = %d\n", &nether_return);
        fscanf(fp, "Statistics = \n");
        for (int i = 1; i <= 11; i++) { fscanf(fp, "%d ", &statistics[statistics_name[i]]); }
        fscanf(fp, "\n");
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
        if (fclose(fp) != 0) {
            perror("Close File Failed."); // 输出错误信息
        }
    }
    string read_skin_path = "../Saves/skin_" + world_name + ".txt";
    FILE *fp_skin = fopen(read_skin_path.c_str(), "r");
    if (fp_skin == NULL)
        read_skin_path = "Saves/skin_" + world_name + ".txt", fp_skin = fopen(
            read_skin_path.c_str(), "r");
    if (fp_skin != NULL) {
        fscanf(fp_skin, "%x\n%c", &skin_color, &skin_char);
        if (fclose(fp_skin) != 0) {
            perror("Close File Failed."); // 输出错误信息
        }
    }
}

void write_game_data() {
    if (health <= 0) {
        return;
    }
    string save_path = "../Saves/" + world_name;
    FILE *fl = fopen(save_path.c_str(), "w");
    if (fl == NULL) save_path = "Saves/" + world_name, fl = fopen(save_path.c_str(), "w");
    if (fl != NULL) {
        fprintf(fl, "Alpha_0.8.4-Dev-snapshot260511\n");
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
        fprintf(fl, "advancements = ");
        for (int i = 1; i <= 8; i++) {
            int temp;
            if (advancements[i] == 1) temp = 1;
            else temp = 0;
            fprintf(fl, "%d,", temp);
        }
        fprintf(fl, "\n");
        fprintf(fl, "\n");
        fprintf(fl, "Portal status = %d\n", portal_status);
        fprintf(fl, "Debug screen = %d\n", debug_screen);
        fprintf(fl, "Allow command = %d\n", allow_command);
        fprintf(fl, "Keep Inventory = %d\n", keepInventory);
        fprintf(fl, "Gamemode = %d\n", gamemode);
        fprintf(fl, "Nether Return = %d\n", nether_return);
        fprintf(fl, "Statistics = ");
        for (int i = 1; i <= 11; i++) { fprintf(fl, "%d ", statistics[statistics_name[i]]); }
        fprintf(fl, "\n");
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
        if (fclose(fl) != 0) {
            perror("Close File Failed."); // 输出错误信息
        }
    }
    string write_skin_path = "../Saves/skin_" + world_name + ".txt";
    FILE *fl_skin = fopen(write_skin_path.c_str(), "w");
    if (fl_skin == NULL)
        write_skin_path = "Saves/skin_" + world_name + ".txt", fl_skin = fopen(
            write_skin_path.c_str(), "w");
    if (fl_skin != NULL) {
        fprintf(fl_skin, "%x", skin_color);
        fprintf(fl_skin, "%c", skin_char);
        if (fclose(fl_skin) != 0) {
            perror("Close File Failed."); // 输出错误信息
        }
    }
}

void read_game_settings() {
    string read_path = "../Saves/game_settings.txt";
    FILE *fp = fopen(read_path.c_str(), "r");
    if (fp == NULL) read_path = "Saves/game_settings.txt", fp = fopen(read_path.c_str(), "r");
    if (fp != NULL) {
        fscanf(fp, "Key Binding:");
        for (int i = 0; i < 13; i++) fscanf(fp, "%c", &key_binding[i]);
        fscanf(fp, "\n");
        fscanf(fp, "Language:%d", &language);
        if (fclose(fp) != 0) {
            perror("Close File Failed."); // 输出错误信息
        }
    }
}

void save_game_settings() {
    string save_path = "../Saves/game_settings.txt";
    FILE *fl = fopen(save_path.c_str(), "w");
    if (fl == NULL) save_path = "Saves/game_settings.txt", fl = fopen(save_path.c_str(), "w");
    if (fl != NULL) {
        fprintf(fl, "Key Binding:");
        for (int i = 0; i < 13; i++) fprintf(fl, "%c", key_binding[i]);
        fprintf(fl, "\n");
        fprintf(fl, "Language:%d", language);
        if (fclose(fl) != 0) {
            perror("Close File Failed."); // 输出错误信息
        }
    }
}

void read_language_settings() {
    string read_path = "../Language/" + language_file_name[language];
    FILE *fp = fopen(read_path.c_str(), "r");
    if (fp == NULL) read_path = "Language/" + language_file_name[language], fp = fopen(read_path.c_str(), "r");
    if (fp != NULL) {
        char buf[10005];
        string lang_key = "", lang_content = "", lang_line = "";
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            lang_line = buf;
            if (!lang_line.empty() && (lang_line.back() == '\n' || lang_line.back() == '\r')) lang_line.pop_back();
            if (!lang_line.empty() && lang_line.back() == '\r') lang_line.pop_back();
            if (lang_line.empty()) continue;

            size_t pos = 0;
            while ((pos = lang_line.find("\\n", pos)) != string::npos) {
                lang_line.replace(pos, 2, "\n");
                pos += 1;
            }
            pos = 0;
            while ((pos = lang_line.find("\\b", pos)) != string::npos) {
                lang_line.replace(pos, 2, "\b");
                pos += 1;
            }

            int lang_p = -1;
            for (int i = 0; i < lang_line.length(); i++) {
                if (lang_line[i] == '=') {
                    lang_p = i;
                    break;
                }
            }
            lang_key = lang_line.substr(0, lang_p);
            lang_content = lang_line.substr(lang_p + 1);
            lang[lang_key] = lang_content;
        }
    }
    if (fclose(fp) != 0) {
        perror("Close File Failed."); // 输出错误信息
    }
}
