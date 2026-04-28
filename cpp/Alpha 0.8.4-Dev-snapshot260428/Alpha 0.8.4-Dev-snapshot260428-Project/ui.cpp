#include "./Lib/game.h"
#include "./Lib/entity.h"
#include "./Lib/map.h"
#include "./Lib/ui.h"

void options(){
	system("cls");
	while(1){
		printf("[0]退出\n");
		printf("[1]语言\n");
		printf("[2]按键绑定\n");
		char options_select = getch();
		if(options_select == '0'){
			return ;
		} else if(options_select == '1'){
			printf("We will add language options in Alpha 0.8.4 soon... By CHESTS IN THE MAPS 游戏开发团队");
			Sleep(1000);
		} else if(options_select == '2'){
			system("cls");
			int selecting = 0;
			while(1){
				printf("[w]向上选择 [s]向下选择 [Enter]设置 [q]退出\n");
				if(selecting == 0){printf("-> ");}printf("向右走 [%c]\n", key_binding[0]);
				if(selecting == 1){printf("-> ");}printf("向下走 [%c]\n", key_binding[1]);
				if(selecting == 2){printf("-> ");}printf("向右走 [%c]\n", key_binding[2]);
				if(selecting == 3){printf("-> ");}printf("向上走 [%c]\n", key_binding[3]);
				if(selecting == 4){printf("-> ");}printf("退出游戏并存档 [%c]\n", key_binding[4]);
				if(selecting == 5){printf("-> ");}printf("打开箱子 [%c]\n", key_binding[5]);
				if(selecting == 6){printf("-> ");}printf("攻击 [%c]\n", key_binding[6]);
				if(selecting == 7){printf("-> ");}printf("使用物品 [%c]\n", key_binding[7]);
				if(selecting == 8){printf("-> ");}printf("打开物品栏 [%c]\n", key_binding[8]);
				if(selecting == 9){printf("-> ");}printf("吃食物 [%c]\n", key_binding[9]);
				if(selecting == 10){printf("-> ");}printf("输入指令 [%c]\n", key_binding[10]);
				if(selecting == 11){printf("-> ");}printf("进入调试模式 [%c]\n", key_binding[11]);
				if(selecting == 12){printf("-> ");}printf("查看成就 [%c]\n", key_binding[12]);
				char key_binding_select = getch();
				if(key_binding_select == 'w'){
					selecting = max (0, selecting - 1);
				} else if(key_binding_select == 's'){
					selecting = min (12, selecting + 1);
				} else if(key_binding_select == 13){
					cout << "请键入按键...";
					key_binding[selecting] = getch();
				} else if(key_binding_select == 'q'){
					break;
				}
				system("cls");
			}
		}
		system("cls");
	}
}
int title_screen(){
	system("cls");
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
	printf("						     [1]开始游戏 [2]选项...\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("Alpha 0.8.4-Dev-snapshot260424(测试版)\n");
	char title_select = getch();
	if(title_select == '1') return 1;
	else if(title_select == '2'){
		options();
	}
	return 0;
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
				if (money >= item_prize[8]*buyS) {
					inventory[8] += buyS, money -= item_prize[8] * buyS;
				} else {
					printf("您的金钱不足！\n");
					Sleep(2000);
				}
			} else if (buy == 2) {
				if (money >= item_prize[9]*buyS) {
					inventory[9] += buyS, money -= item_prize[9] * buyS;
				} else {
					printf("您的金钱不足！\n");
					Sleep(2000);
				}
			} else if (buy == 3) {
				if (money >= item_prize[10]*buyS) {
					inventory[10] += buyS, money -= item_prize[10] * buyS;
				} else {
					printf("您的金钱不足！\n");
					Sleep(2000);
				}
			} else if (buy == 4) {
				if (money >= item_prize[13]*buyS) {
					inventory[13] += buyS, money -= item_prize[13] * buyS;
				} else {
					printf("您的金钱不足！\n");
					Sleep(2000);
				}
			}
		}
		if (shopSelect == 1) {
			printf("金钱:%d\n", money);
			for (int i = 0; i < 8; i++) {
				money += inventory[i] * item_prize[i], inventory[i] = 0;
			}
			for (int i = 15 ; i < 17; i++) {
				money += inventory[i] * item_prize[i], inventory[i] = 0;
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
void useItem() {
	printf("背包道具:\n");
	printf(" ╔══════════════════════════════════════╗ \n");
	printf(" ║ 1.末影珍珠:%26d║ \n", inventory[8]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 2.治疗药水:%26d║ \n", inventory[9]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 3.喷溅型伤害药水:%20d║ \n", inventory[10]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 4.打火石:%28d║ \n", inventory[14]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 5.录音带-Happy-Chests:%15d║ \n", inventory[17]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 6.录音带-Stressful:%18d║ \n", inventory[18]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 7.录音带-Lava Zombie:%16d║ \n", inventory[19]);
	printf(" ╚══════════════════════════════════════╝ \n");
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
		printf("玩家使用末影珍珠,已将玩家传送到(%d,%d)\n", x, y);
		Sleep(1000);
	}
	if (useSelect == 2 && inventory[9] > 0) {
		inventory[9]--;
		health = 20;
		printf("玩家使用治疗药水,生命值恢复至20\n");
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
			int tx = x + direction_x[i], ty = y + direction_y[i];
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
			portal_status = 1;
			if (achievements[6] == 0) {
				achievements[6] = 1;
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
		system("start Happy_Chests.print_map3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("正在播放-Happy Chests\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
		system("pause");
	}
	if (useSelect == 6 && inventory[18] > 0) {
		system("start Stressful.print_map3");
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
void useItem_nether() {
	printf("背包道具:\n");
	printf(" ╔══════════════════════════════════════╗ \n");
	printf(" ║ 1.末影珍珠:%26d║ \n", inventory[8]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 2.治疗药水:%26d║ \n", inventory[9]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 3.喷溅型伤害药水:%20d║ \n", inventory[10]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 4.录音带-Happy-Chests:%15d║ \n", inventory[17]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 5.录音带-Stressful:%18d║ \n", inventory[18]);
	printf(" ╠══════════════════════════════════════╣ \n");
	printf(" ║ 6.录音带-Lava Zombie:%16d║ \n", inventory[19]);
	printf(" ╚══════════════════════════════════════╝ \n");
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
		health = 20;
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
				for (int k = 1; k <= blaze_sum; k++) {
					if (blaze[k].x == i && blaze[k].y == j) {
						nether[blaze[k].x][blaze[k].y] = 0;
						blaze[k].x = 0, blaze[k].y = 0;
					}
				}
			}
		}
		Sleep(1000);
	}
	if (useSelect == 4 && inventory[17] > 0) {
		system("start Happy_Chests.print_map3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("正在播放-Happy Chests\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
		system("pause");
	}
	if (useSelect == 5 && inventory[18] > 0) {
		system("start Stressful.print_map3");
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
void view_inventory() {
	system("cls");
	printf("背包\n");
	printf("╔════════════════════════════════════╗ \n");
	for (int i = 0; i < 21; i++) {
		if (i == 0) printf("║ 原石:%30d║ ", inventory[i]);
		if (i == 1) printf("║ 煤炭:%30d║ ", inventory[i]);
		if (i == 2) printf("║ 铁锭:%30d║ ", inventory[i]);
		if (i == 3) printf("║ 金锭:%30d║ ", inventory[i]);
		if (i == 4) printf("║ 红石:%30d║ ", inventory[i]);
		if (i == 5) printf("║ 青金石:%28d║ ", inventory[i]);
		if (i == 6) printf("║ 绿宝石:%28d║ ", inventory[i]);
		if (i == 7) printf("║ 钻石:%30d║ ", inventory[i]);
		if (i == 8) printf("║ 末影珍珠:%26d║ ", inventory[i]);
		if (i == 9) printf("║ 治疗药水:%26d║ ", inventory[i]);
		if (i == 10) printf("║ 喷溅型伤害药水:%20d║ ", inventory[i]);
		if (i == 11) printf("║ 腐肉:%30d║ ", inventory[i]);
		if (i == 12) printf("║ 骨头:%30d║ ", inventory[i]);
		if (i == 13) printf("║ 面包:%30d║ ", inventory[i]);
		if (i == 14) printf("║ 打火石:%28d║ ", inventory[i]);
		if (i == 15) printf("║ 下界石英:%26d║ ", inventory[i]);
		if (i == 16) printf("║ 萤石:%30d║ ", inventory[i]);
		if (i == 17) printf("║ 录音带-Happy Chests:%15d║ ", inventory[i]);
		if (i == 18) printf("║ 录音带-Stressful:%18d║ ", inventory[i]);
		if (i == 19) printf("║ 录音带-Lava Zombie:%16d║ ", inventory[i]);
		if (i == 20) printf("║ 末地钥匙:%26d║ ", inventory[i]);
		if (i < 20) {
			printf("\n╠════════════════════════════════════╣ \n");
		}
	}
	printf("\n╚════════════════════════════════════╝ \n");
	system("pause");
}
void eatFood() {
	printf("食物:\n");
	printf("╔══════════════════════════════════════╗ \n");
	printf("║ 1.腐肉:%30d║ \n", inventory[11]);
	printf("╠══════════════════════════════════════╣ \n");
	printf("║ 2.面包:%30d║ \n", inventory[13]);
	printf("╚══════════════════════════════════════╝ \n");
	int foodSelect, foodS;
	printf("吃哪一个食物,吃多少?");
	scanf("%d%d", &foodSelect, &foodS);
	if (foodSelect == 1) {
		foodS = min(foodS, inventory[11]);
		inventory[11] -= foodS;
		hunger = min(20, hunger + foodS * 1);
	}
	if (foodSelect == 2) {
		foodS = min(foodS, inventory[13]);
		inventory[13] -= foodS;
		hunger = min(20, hunger + foodS * 3);
	}
	return ;
}
void seeachievements() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("成就\n");
	printf("主世界\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[小小怪物，轻松拿捏]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("击杀任意一只怪物 ");
	if (achievements[1] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[远处有个狙击手]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("让骷髅的箭射中你 ");
	if (achievements[2] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[这是什么？箱子！]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("打开一个箱子 ");
	if (achievements[3] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[抵达终点]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("到达终点 ");
	if (achievements[4] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
	printf("[哦，不！]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("死亡一次 ");
	if (achievements[5] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("下界\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
	printf("[准备去新的维度]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("激活下界传送门 ");
	if (achievements[6] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
	printf("[勇闯下界]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("进入下界 ");
	if (achievements[7] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
	printf("[燃起来了]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("被燃烧骷髅的火矢射中 ");
	if (achievements[8] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x05);
	printf("[与火共舞]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
	printf("获取末地钥匙 ");
	if (achievements[9] == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		printf("未获得！\n");
	} else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
	system("pause");
}
void command() {
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
			health = 0, hunger = 1, death_message = "You were been killed.";
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
			health = 0, hunger = 1, death_message = "You were been killed.";
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

