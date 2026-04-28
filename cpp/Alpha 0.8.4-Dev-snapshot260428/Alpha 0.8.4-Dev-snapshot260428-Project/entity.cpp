#include "./Lib/game.h"
#include "./Lib/entity.h"
#include "./Lib/map.h"
#include "./Lib/ui.h"

void update_mobs_overworld(){
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
		if (arrow[i].x != 0 && arrow[i].y != 0 && overworld[arrow[i].x + direction_x[arrow[i].facing]][arrow[i].y + direction_y[arrow[i].facing]] < 5) {
			overworld[arrow[i].x][arrow[i].y] = DIRT;
			arrow[i].x += direction_x[arrow[i].facing], arrow[i].y += direction_y[arrow[i].facing];
			overworld[arrow[i].x][arrow[i].y] = 17;
		} else if (!in(arrow[i].x + direction_x[arrow[i].facing], arrow[i].y + direction_y[arrow[i].facing]) || overworld[arrow[i].x + direction_x[arrow[i].facing]][arrow[i].y + direction_y[arrow[i].facing]]) {
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
	return ;
}
void update_mobs_nether(){
	for (int i = 1; i <= lava_zombie_sum; i++) { //熔岩僵尸移动
		if (abs(lava_zombie[i].x - x) < 4 && abs(lava_zombie[i].y - y) < 4 && lava_zombie[i].x != 0 && lava_zombie[i].y != 0) {
			int lava_zombieType = nether[lava_zombie[i].x][lava_zombie[i].y];
			nether[lava_zombie[i].x][lava_zombie[i].y] = nether_block_check(lava_zombie[i].x, lava_zombie[i].y);
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
			nether[burn_skeleton[i].x][burn_skeleton[i].y] = nether_block_check(burn_skeleton[i].x, burn_skeleton[i].y);
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
			nether[blaze[i].x][blaze[i].y] = nether_block_check(blaze[i].x, blaze[i].y);
			if (x < blaze[i].x && nether[blaze[i].x - 1][blaze[i].y] < 2) blaze[i].x--;
			else if (x > blaze[i].x && nether[blaze[i].x + 1][blaze[i].y] < 2) blaze[i].x++;
			else if (y < blaze[i].y && nether[blaze[i].x][blaze[i].y - 1] < 2) blaze[i].y--;
			else if (y > blaze[i].y && nether[blaze[i].x][blaze[i].y + 1] < 2) blaze[i].y++;
			nether[blaze[i].x][blaze[i].y] = blazeType;
		}
	}
	for (int i = 1; i <= burn_arrow_sum; i++) { //火矢移动
		if (burn_arrow[i].x != 0 && burn_arrow[i].y != 0 && nether[burn_arrow[i].x + direction_x[burn_arrow[i].facing]][burn_arrow[i].y + direction_y[burn_arrow[i].facing]] < 2) {
			nether[burn_arrow[i].x][burn_arrow[i].y] = nether_block_check(burn_arrow[i].x, burn_arrow[i].y);
			burn_arrow[i].x += direction_x[burn_arrow[i].facing], burn_arrow[i].y += direction_y[burn_arrow[i].facing];
			nether[burn_arrow[i].x][burn_arrow[i].y] = 15;
		} else if (!in(burn_arrow[i].x + direction_x[burn_arrow[i].facing], burn_arrow[i].y + direction_y[burn_arrow[i].facing]) || nether[burn_arrow[i].x + direction_x[burn_arrow[i].facing]][burn_arrow[i].y + direction_y[burn_arrow[i].facing]]) {
			nether[burn_arrow[i].x][burn_arrow[i].y] = 0;
			burn_arrow[i].x = 0, burn_arrow[i].y = 0;
		}
	}
	for (int i = 1; i <= fire_charge_sum; i++){//火焰弹移动
		if (fire_charge[i].x != 0 && fire_charge[i].y != 0 && nether[fire_charge[i].x + direction_x[fire_charge[i].facing]][fire_charge[i].y + direction_y[fire_charge[i].facing]] < 2) {
			nether[fire_charge[i].x][fire_charge[i].y] = nether_block_check(fire_charge[i].x, fire_charge[i].y);
			fire_charge[i].x += direction_x[fire_charge[i].facing], fire_charge[i].y += direction_y[fire_charge[i].facing];
			nether[fire_charge[i].x][fire_charge[i].y] = FIRE_CHARGE;
		} else if (!in(fire_charge[i].x + direction_x[fire_charge[i].facing], fire_charge[i].y + direction_y[fire_charge[i].facing]) || nether[fire_charge[i].x + direction_x[fire_charge[i].facing]][fire_charge[i].y + direction_y[fire_charge[i].facing]]) {
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
	return ;
}
void check_attack_overworld(){
	for (int i = 1; i <= zombie_sum; i++) { //检测僵尸攻击
		for (int j = 0; j < 4; j++) {
			int zo_attack_x = zombie[i].x + direction_x[j], zo_attack_y = zombie[i].y + direction_y[j];
			if (x == zo_attack_x && y == zo_attack_y) {
				health -= 2;
				if (health <= 0) {
					death_message = "Player was slain by zombie";
				}
				message_list.push_back({"玩家被僵尸攻击了", 3});
			}
		}
	}
	for (int i = 1; i <= skeleton_sum; i++) { //检测骷髅近战攻击
		for (int j = 0; j < 4; j++) {
			int sk_attack_x = skeleton[i].x + direction_x[j], sk_attack_y = skeleton[i].y + direction_y[j];
			if (x == sk_attack_x && y == sk_attack_y) {
				health -= 2;
				if (health <= 0) {
					death_message = "Player was slain by skeleton";
				}
				message_list.push_back({"玩家被骷髅攻击了", 3});
			}
		}
	}
	for (int i = 1; i <= arrow_sum; i++) { //检测箭矢攻击
		int ar_attack_x = arrow[i].x + direction_x[arrow[i].facing], ar_attack_y = arrow[i].y + direction_y[arrow[i].facing];
		if (x == ar_attack_x && y == ar_attack_y) {
			health--;
			if (health <= 0) {
				death_message = "Player was shot by skeleton";
			}
			message_list.push_back({"玩家被箭矢攻击了", 3});
			overworld[arrow[i].x][arrow[i].y] = DIRT;
			arrow[i].x = 0, arrow[i].y = 0;
			if (achievements[2] == 0) {
				achievements[2] = 1;
				printf("玩家刚刚获得了进度");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
				printf("[远处有个狙击手]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
				printf("!\n");
				Sleep(2000);
			}
		}
		for (int j = 1; j <= zombie_sum; j++) {
			if (overworld[ar_attack_x][ar_attack_y] == 9) overworld[ar_attack_x][ar_attack_y] = 12, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
			else if (overworld[ar_attack_x][ar_attack_y] == 12) overworld[ar_attack_x][ar_attack_y] = 13, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
			else if (overworld[ar_attack_x][ar_attack_y] == 13) {
				overworld[ar_attack_x][ar_attack_y] = 0, overworld[arrow[i].x][arrow[i].y] = 0, arrow[i].x = 0, arrow[i].y = 0;
			}
		}
		for (int j = 1; j <= skeleton_sum; j++) {
			if (overworld[ar_attack_x][ar_attack_y] == 14) overworld[ar_attack_x][ar_attack_y] = 15, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
			else if (overworld[ar_attack_x][ar_attack_y] == 15) overworld[ar_attack_x][ar_attack_y] = 16, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
			else if (overworld[ar_attack_x][ar_attack_y] == 16) {
				overworld[ar_attack_x][ar_attack_y] = DIRT, overworld[arrow[i].x][arrow[i].y] = DIRT, arrow[i].x = 0, arrow[i].y = 0;
			}
		}
	}
	return ;
}
void check_attack_nether(){
	for (int i = 1; i <= lava_zombie_sum; i++) { //检测熔岩僵尸攻击
		for (int j = 0; j < 4; j++) {
			int zo_attack_x = lava_zombie[i].x + direction_x[j], zo_attack_y = lava_zombie[i].y + direction_y[j];
			if (x == zo_attack_x && y == zo_attack_y) {
				health -= 2;
				if (health <= 0) {
					death_message = "Player was slain by lava zombie";
				}
				message_list.push_back({"玩家被熔岩僵尸攻击了", 3});
			}
		}
	}
	for (int i = 1; i <= burn_skeleton_sum; i++) { //检测燃烧骷髅近战攻击
		for (int j = 0; j < 4; j++) {
			int sk_attack_x = burn_skeleton[i].x + direction_x[j], sk_attack_y = burn_skeleton[i].y + direction_y[j];
			if (x == sk_attack_x && y == sk_attack_y) {
				burn_time = 3;
				if (health <= 0) {
					death_message = "Player was slain by burn skeleton";
				}
				message_list.push_back({"玩家被燃烧骷髅攻击了,开始燃烧3s", 3});
			}
		}
	}
	for (int i = 1; i <= blaze_sum; i++) { //检测烈焰人攻击
		for (int j = 0; j < 4; j++) {
			int blaze_attack_x = blaze[i].x + direction_x[j], blaze_attack_y = blaze[i].y + direction_y[j];
			if (x == blaze_attack_x && y == blaze_attack_y) {
				health -= 2;
				if (health <= 0) {
					death_message = "Player was slain by blaze";
				}
				message_list.push_back({"玩家被烈焰人攻击了", 3});
			}
		}
	}
	for (int i = 1; i <= burn_arrow_sum; i++) { //检测火矢攻击
		int ar_attack_x = burn_arrow[i].x + direction_x[burn_arrow[i].facing], ar_attack_y = burn_arrow[i].y + direction_y[burn_arrow[i].facing];
		if (x == ar_attack_x && y == ar_attack_y) {
			burn_time = 3;
			nether[burn_arrow[i].x][burn_arrow[i].y] = nether_block_check(burn_arrow[i].x, burn_arrow[i].y);
			burn_arrow[i].x = 0, burn_arrow[i].y = 0;
			message_list.push_back({"玩家被火矢攻击了,开始燃烧3s", 3});
			if (achievements[8] == 0) {
				achievements[8] = 1;
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
		int fire_charge_attack_x = fire_charge[i].x + direction_x[fire_charge[i].facing], fire_charge_attack_y = fire_charge[i].y + direction_y[fire_charge[i].facing];
		if (x == fire_charge_attack_x && y == fire_charge_attack_y) {
			health -= 1;
			burn_time = 3;
			nether[fire_charge[i].x][fire_charge[i].y] = nether_block_check(fire_charge[i].x, fire_charge[i].y);
			fire_charge[i].x = 0, fire_charge[i].y = 0;
			message_list.push_back({"玩家被火焰弹攻击了,开始燃烧3s", 3});
		}
	}
	return ;
}
