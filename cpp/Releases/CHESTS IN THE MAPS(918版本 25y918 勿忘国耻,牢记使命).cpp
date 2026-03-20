#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
const int N=55;
int n,a[N][N],sum[20],x,y,fx,money=0,hp=20,full=20,step=0;
int Japanese_1X[5],Japanese_1Y[5],Japanese_1S;
int Japanese_2X[5],Japanese_2Y[5],Japanese_2S; 
int bulletX[200005],bulletY[200005],bulletFx[200005],bulletS;
int cx[4]= {0,1,0,-1};
int cy[4]= {1,0,-1,0};
int is_order;
bool vis[N][N],flag=0;
int thingMoney[20]= {1,5,100,100,200,300,1000,5000,100000,500000,300000,0,0,10};
bool in(int x,int y) {
	return (x>=1&&x<=n&&y>=1&&y<=n);
}
void checkRoad(int x,int y) { //检测是否有路
	if(x==n-1&&y==n-1) {
		flag=1;
		return ;
	}
	if(a[x][y]>5) {
		return ;
	}
	vis[x][y]=1;
	for(int i=0; i<4; i++) {
		int tx=x+cx[i],ty=y+cy[i];
		if(in(tx,ty)&&(a[tx][ty]<5||a[tx][ty]==11)&&vis[tx][ty]==0) {
			checkRoad(tx,ty);
		}
	}
	return ;
}
char printChar(int x) { //数转字符
	if(x<5){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xF0);
		return ' ';
	}
	if(x>=5&&x<=7){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xCF);
		return 'W';
	}
	if(x==8){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xE0);
		return 'C';
	}
	if(x==9){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xC0);
		return 'J';
	}
	if(x==10){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x9F);
		return 'Y';
	}
	if(x==11){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x80);
		return 'D';
	}
	if(x==12){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xC0);
		return '2';
	}
	if(x==13){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xC0);
		return '1';
	}
	if(x==14){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
		return 'J';
	}
	if(x==15){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
		return '2'; 
	}
	if(x==16){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
		return '1';
	}
	if(x==17){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xF0);
		return 'B';
	}
}
void mp() { //输出地图
	printf(" ╔════════════════╦═══════════════╦═══════════════╗ \n"); 
	printf(" ║ 金钱:%9d",money);
	printf(" ║ 生命:%9d",hp);
	printf("║ 饱食度:%7d║ \n",full);
	printf(" ╚════════════════╩═══════════════╩═══════════════╝ \n"); 
	printf("\n");
	printf("  ");
	for(int i=1; i<=n; i++) {
		printf("%3d",i);
	}
	printf("\n");
	for(int i=1; i<=n; i++) {
		printf("%2d ",i);
		for(int j=1; j<=n; j++) {
			printf("[%c]",printChar(a[i][j]));
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
		}
		printf("\n");
	}
}
void makeMp(int x,int y) { //构建地图
	vis[x][y]=1;
	a[x][y]=rand()%8;
	for(int i=0; i<4; i++) {
		int tx=x+cx[i],ty=y+cy[i];
		if(in(tx,ty)&&a[tx][ty]==0) {
			makeMp(tx,ty);
		}
	}
}
void chest() { //开箱子
	system("cls");
	printf("箱子\n");
	printf("╔═══════════════════════╗ \n");
	for(int i=0; i<8; i++) {
		int ChestMoney;
		if(i==1){
			ChestMoney=rand()%64;
		}
		if(i<=3) {
			ChestMoney=rand()%20;
		}
		if(i>3&&i<=5) {
			ChestMoney=rand()%10;
		}
		if(i>5){
			ChestMoney=rand()%3;
		}
		if(i==0) printf("║ 原石:%2d               ║ ",ChestMoney),sum[0]+=ChestMoney;
		if(i==1) printf("║ 煤炭:%2d               ║ ",ChestMoney),sum[1]+=ChestMoney;
		if(i==2) printf("║ 铁锭:%2d               ║ ",ChestMoney),sum[2]+=ChestMoney;
		if(i==3) printf("║ 金锭:%2d               ║ ",ChestMoney),sum[3]+=ChestMoney;
		if(i==4) printf("║ 红石:%2d               ║ ",ChestMoney),sum[4]+=ChestMoney;
		if(i==5) printf("║ 青金石:%2d             ║ ",ChestMoney),sum[5]+=ChestMoney;
		if(i==6) printf("║ 绿宝石:%2d             ║ ",ChestMoney),sum[6]+=ChestMoney;
		if(i==7) printf("║ 钻石:%2d               ║ ",ChestMoney),sum[7]+=ChestMoney;
		if(i<7){
			printf("\n╠═══════════════════════╣ \n");
		}
	}
	printf("\n╚═══════════════════════╝ \n");
	printf("搜刮完毕！\n");
	system("pause");
	return ;
}
void shop() { //商店 
	system("cls");
	while(1) {
		int shopSelect;
		printf("欢迎光临商店!\n");
		printf("请输入你要干什么:\n");
		printf("[0]买 [1]卖 [2]退出\n");
		scanf("%d",&shopSelect);
		if(shopSelect==0) {
			printf("金钱:%d\n",money);
			printf("1.末影珍珠:$10,0000 传送至附近9*9的范围内\n");
			printf("2.治疗药水:$50,0000 恢复至满血\n");
			printf("3.喷溅型伤害药水:$30,0000 对5*5范围内的鬼造成10点伤害\n");
			printf("4.面包:$10 恢复3点饱食度\n");
			printf("你要买那个(编号)?买多少?");
			int buy,buyS;
			scanf("%d%d",&buy,&buyS);
			if(buy==1) {
				if(money>=thingMoney[8]*buyS){
					sum[8]+=buyS,money-=thingMoney[8]*buyS;
				} else{
					printf("老板:买不起就滚吧!开你的箱子去!\n");
					Sleep(2000);
				}
			} else if(buy==2) {
				if(money>=thingMoney[9]*buyS){
					sum[9]+=buyS,money-=thingMoney[9]*buyS;
				} else{
					printf("老板:买不起就滚吧!开你的箱子去!\n");
					Sleep(2000);
				}
			} else if(buy==3) {
				if(money>=thingMoney[10]*buyS){
					sum[10]+=buyS,money-=thingMoney[10]*buyS;
				} else{
					printf("老板:买不起就滚吧!开你的箱子去!\n");
					Sleep(2000);
				}
			} else if(buy==4){
				if(money>=thingMoney[13]*buyS){
					sum[13]+=buyS,money-=thingMoney[13]*buyS;
				} else{
					printf("老板:面包都买不起,去开你的箱子去!\n");
				}
			}
		}
		if(shopSelect==1) {
			printf("金钱:%d\n",money);
			for(int i=0; i<8; i++) {
				money+=sum[i]*thingMoney[i],sum[i]=0;
			}
			printf("成交! 金钱:%d\n",money);
			Sleep(1000);
		}
		if(shopSelect==2){
			return ;
		}
		system("cls");
	}
}
void quickTeach(){//快速教学 
	system("cls");
	printf(" ╔═══════════════════════════════════════════════════════════════════╗ \n");
	printf(" ║ 教程:                                                             ║ \n");
	printf(" ║ 1.' '=空,'W'=墙,'C'=抗战物资,'Y'=玩家,'J'=日本鬼子,'D'=门(出口)   ║ \n");
	printf(" ║ 2.操作:                                                           ║ \n");
	printf(" ║   (1)w,a,s,d:上下左右                                             ║ \n");
	printf(" ║   (2)o:开上一次方向的箱子                                         ║ \n");
	printf(" ║   (3)k:攻击四周的鬼子                                             ║ \n");
	printf(" ║   (4)r:退出                                                       ║ \n");
	printf(" ║   (5)e:打开背包                                                   ║ \n");
	printf(" ║   (6)t:查看教程                                                   ║ \n");
	printf(" ║   (7)u:使用道具                                                   ║ \n");
	printf(" ║   (8)q:吃东西                                                     ║ \n");
	printf(" ║ 3.指令的使用(先在'游戏选项-作弊'中输入1)                          ║ \n");
	printf(" ║   (1)/kill [type=[实体名]] 杀死某种实体                           ║ \n");
	printf(" ║     实体名称:                                                     ║ \n");
	printf(" ║     1.chest:Japanese [编号/All(所有)]:第[编号]个鬼子/所有鬼子     ║ \n");
	printf(" ║     2.chest:player:玩家(你)                                       ║ \n");
	printf(" ║     3.chest:all:所有实体                                          ║ \n");
	printf(" ║   (2)/tp 行 列 将玩家传送到(行,列)                                ║ \n");
	printf(" ║   (3)/beta_set [数据名] [数值] 修改游戏数据                       ║ \n");
	printf(" ║     数据名称:                                                     ║ \n");
	printf(" ║     1.a[x][y]         地图数组                                    ║ \n");
	printf(" ║     2.x               玩家所在行                                  ║ \n");
	printf(" ║     3.y               玩家所在列                                  ║ \n");
	printf(" ║     4.money           玩家金钱                                    ║ \n");
	printf(" ║     5.hp              玩家生命                                    ║ \n");
	printf(" ║     6.full            玩家饱食度                                  ║ \n");
	printf(" ║     7.sum[i]           物品栏数据                                 ║ \n");
	printf(" ╚═══════════════════════════════════════════════════════════════════╝ \n"); 
}
void useThing(){
	printf("背包道具:\n");
	printf(" ╔═══════════════════════╗ \n");
	printf(" ║ 1.末影珍珠:%2d         ║ \n",sum[8]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 2.治疗药水:%2d         ║ \n",sum[9]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 3.喷溅型伤害药水:%2d   ║ \n",sum[10]);
	printf(" ╚═══════════════════════╝ \n");
	printf("你要使用第几个道具?\n");
	int useSelect;
	scanf("%d",&useSelect);
	if(useSelect==1&&sum[8]>0){
		sum[8]--;
		printf("你要传送到?:");
		int Ender_Pearl_X,Ender_Pearl_Y;
		scanf("%d%d",&Ender_Pearl_X,&Ender_Pearl_Y);
		Ender_Pearl_X=min(Ender_Pearl_X,x+4),Ender_Pearl_Y=min(Ender_Pearl_Y,y+4);
		Ender_Pearl_X=max(Ender_Pearl_X,x-4),Ender_Pearl_Y=max(Ender_Pearl_Y,y-4);
		a[x][y]=0;
		x=Ender_Pearl_X,y=Ender_Pearl_Y;
		printf("玩家 使用 末影珍珠,已将 玩家 传送到 %d %d\n",x,y);
		Sleep(1000);
	}
	if(useSelect==2&&sum[9]>0){
		sum[9]--;
		hp=20;
		printf("玩家 使用 治疗药水,生命值 恢复至 20/20\n");
	}
	if(useSelect==3&&sum[10]>0){
		sum[10]--;
		for(int i=max(1,x-2);i<=min(n,x+2);i++){
			for(int j=max(1,y-2);j<=min(n,y+2);j++){
				for(int k=1;k<=Japanese_1S;k++){
					if(Japanese_1X[k]==i&&Japanese_1Y[k]==j){
						a[Japanese_1X[k]][Japanese_1Y[k]]=0;
						Japanese_1X[k]=0,Japanese_1Y[k]=0;
						printf("玩家 使用 喷溅型伤害药水,chest:Japanese_1 %d被杀死了\n",k);
					}
				}
				for(int k=1;k<=Japanese_2S;k++){
					if(Japanese_2X[k]==i&&Japanese_2Y[k]==j){
						a[Japanese_2X[k]][Japanese_2Y[k]]=0;
						Japanese_2X[k]=0,Japanese_2Y[k]=0;
						printf("玩家 使用 喷溅型伤害药水,chest:Japanese_2 %d被杀死了\n",k);
					}
				}
			}
		}
		Sleep(1000);
	}
}
void seeBag(){
	system("cls");
	printf("背包\n");
	printf("╔═══════════════════════╗ \n");
	for(int i=0; i<13; i++) {
		if(i==0) printf("║ 原石:%2d               ║ ",sum[i]);
		if(i==1) printf("║ 煤炭:%2d               ║ ",sum[i]);
		if(i==2) printf("║ 铁锭:%2d               ║ ",sum[i]);
		if(i==3) printf("║ 金锭:%2d               ║ ",sum[i]);
		if(i==4) printf("║ 红石:%2d               ║ ",sum[i]);
		if(i==5) printf("║ 青金石:%2d             ║ ",sum[i]);
		if(i==6) printf("║ 绿宝石:%2d             ║ ",sum[i]);
		if(i==7) printf("║ 钻石:%2d               ║ ",sum[i]);
		if(i==8) printf("║ 末影珍珠:%2d           ║ ",sum[i]);
		if(i==9) printf("║ 治疗药水:%2d           ║ ",sum[i]);
		if(i==10) printf("║ 喷溅型伤害药水:%2d     ║ ",sum[i]);
		if(i==11) printf("║ 敌人的碎片:%2d         ║ ",sum[i]);
		if(i==12) printf("║ 敌人的骨头:%2d         ║ ",sum[i]);
		if(i<12){
			printf("\n╠═══════════════════════╣ \n");
		}
	}
	printf("\n╚═══════════════════════╝ \n");
	system("pause");
}
void eatFood(){
	printf("食物:\n");
	printf("╔═══════════════════════╗ \n");
	printf("║ 1.树根:%2d             ║ \n",sum[11]);
	printf("╠═══════════════════════╣ \n");
	printf("║ 2.面包:%2d             ║ \n",sum[13]);
	printf("╚═══════════════════════╝ \n");
	int foodSelect,foodS;
	printf("吃哪一个食物,吃多少?");
	scanf("%d%d",&foodSelect,&foodS);
	if(foodSelect==1){
		foodS=min(foodS,sum[11]);
		sum[11]-=foodS;
		full=min(20,full+foodS*1);
	}
	if(foodSelect==2){
		foodS=min(foodS,sum[13]);
		sum[13]-=foodS;
		full=min(20,full+foodS*3);
	}
	return ;
}
void alive_People_Exp(){
	system("cls");
	printf("这是？......7......3......1???");
	Sleep(3000);
	system("cls");
	Sleep(5000);
	printf("很不幸，你被毒气熏晕了，你现在正在731部队里，正在接受活人实验，祝你能安全回来！勿忘国耻，牢记使命！中国共产主义万岁！\n");
	Sleep(5000);
	system("cls");
	int Exp[10][10];
	for(int i=1;i<=5;i++){//监狱
		for(int j=1;j<=5;j++){
			if(i==1||i==5||j==1||j==5){
				Exp[i][j]=6;
			}
			else{
				Exp[i][j]=0;
			}
		}
	}
	Exp[3][3]=10;
	printf("你:我现在在哪里?.....731???\n");
	Sleep(1000);
	printf("日本鬼子:这个'马路大'就给他进行毒气实验吧!哟西!\n");
	Sleep(1000);
	printf("嘶~~~日本鬼子:很好,哟西!\n");
	printf(" ╔════════════════╦═══════════════╦═══════════════╗ \n"); 
	printf(" ║ 金钱:%9d",money);
	printf(" ║ 生命:%9d",hp);
	printf("║ 饱食度:%7d║ \n",full);
	printf(" ╚════════════════╩═══════════════╩═══════════════╝ \n"); 
	printf("\n");
	printf("  ");
	for(int i=1; i<=5; i++) {
		printf("%3d",i);
	}
	printf("\n");
	for(int i=1; i<=5; i++) {
		printf("%2d ",i);
		for(int j=1; j<=5; j++) {
			printf("[%c]",printChar(Exp[i][j]));
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
		}
		printf("\n");
	}
	printf("你现在在毒气里,你中毒了。勿忘国耻，牢记使命！中国共产主义万岁！\n");
	hp-=8;
	Sleep(5000);
}
void game() {
	system("color 0C");
	printf("\n\n\n\n\n");
	printf("                                          ╔═════════════════════════╗ \n");
	printf("					  ║       CHESTS IN         ║\n");
	printf("					  ║                         ║\n");
	printf("					  ║            THE MAPS     ║\n");
	printf("					  ║                         ║\n");
	printf("					  ║       C++ EDITON        ║\n");
	printf("                                          ╚═════════════════════════╝ \n");
	printf("\n\n\n\n\n");
	printf("						按任意键开始游戏...\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("抗日战争 25y918 (918版本)\n");
	system("pause");
	system("cls");
	printf("游戏选项:\n");
	printf("地图大小(5-20):[  ]\b\b\b");
	scanf("%d",&n);
	n=max(5,n),n=min(20,n);
	printf("作弊([0]否 [1]是):[ ]\b\b");
	scanf("%d",&is_order);
	quickTeach();
	system("pause");
	system("cls");
	while(1) {
		hp=20;
		full=20;
		flag=0;
		memset(a,0,sizeof(a));
		memset(vis,false,sizeof(vis));
		while(1) {
			int MapX,MapY;//构建地图的起点
			MapX=rand()%(n+1),MapY=rand()%(n+1);
			if(MapX==0) MapX++;
			if(MapY==0) MapY++;
			makeMp(MapX,MapY);
			checkRoad(2,2);//是否有路能到终点
			if(flag==1) {
				break;
			}
			flag=0;//初始化
			memset(vis,false,sizeof(vis));
		}
		Japanese_1S=n/3;
		Japanese_2S=2;
		for(int i=1; i<=rand()%n; i++){
			int gx=rand()%(n+1),gy=rand()%(n+1);
			if(gx==0) gx++;
			if(gy==0) gy++;
			a[gx][gy]=8;
		}
		for(int i=1; i<=Japanese_1S; i++) {//生成日本鬼子1  
			Japanese_1X[i]=rand()%(n+1),Japanese_1Y[i]=rand()%(n+1);
			if(Japanese_1X[i]==0) Japanese_1X[i]++;
			if(Japanese_1Y[i]==0) Japanese_1Y[i]++;
			if(Japanese_1X[i]==n-1) Japanese_1X[i]--;
			if(Japanese_1Y[i]==n-1) Japanese_1Y[i]--;
			a[Japanese_1X[i]][Japanese_1Y[i]]=9;
		}
		for(int i=1; i<=Japanese_2S; i++){//生成日本鬼子2 
			Japanese_2X[i]=rand()%(n+1),Japanese_2Y[i]=rand()%(n+1);
			if(Japanese_2X[i]==0) Japanese_2X[i]++;
			if(Japanese_2Y[i]==0) Japanese_2Y[i]++;
			if(Japanese_2X[i]==n-1) Japanese_2X[i]--;
			if(Japanese_2Y[i]==n-1) Japanese_2Y[i]--;
			a[Japanese_2X[i]][Japanese_2Y[i]]=14;
		}
		memset(bulletX,0,sizeof(bulletX));
		memset(bulletY,0,sizeof(bulletY));
		x=2,y=2;
		a[x][y]=10;
		a[n-1][n-1]=11;
//构建地图 
		while(1) {
			if(step>0&&step%10==0&&full>0){//更新饱食度
				full--;
			}
			if(full==20){
				hp++;
				hp=min(hp,20);
			}
			if(full==0){
				hp--;
			}
			if(hp<=0){
				memset(sum,0,sizeof(sum));
				money=0;
				hp=20;
				a[x][y]=0;
				system("cls");
				system("color CF");
				printf("\n\n\n\n\n\n\n");
				printf("                                    你牺牲了！\n\n\n\n\n\n");
				int YN;
				printf("                      [0]退出游戏 [1]重生 [2]返回标题屏幕");
				bulletS=0;
				memset(bulletX,0,sizeof(bulletX));
				memset(bulletY,0,sizeof(bulletY));
				scanf("%d",&YN);
				if(YN==0) {
					return ;
				}
				if(YN==1) {
					system("color 0C");
					break;
				}
				if(YN==2) {
					game();
					return ;
				}
			}
			if(x==n-1&&y==n-1) {
				printf("\n\n\n\n\n\n");
				printf("                   加油,抗战战士,你要进入下一个战场了!\n\n\n");
				int YN;
				printf("                      [0]退出 [1]继续 [2]进入商店\n");
				scanf("%d",&YN);
				bulletS=0;
				memset(bulletX,0,sizeof(bulletX));
				memset(bulletY,0,sizeof(bulletY));
				if(YN==0) {
					return ;
				}
				if(YN==1) {
					break;
				}
				if(YN==2) {
					shop();
					break;
				}
			}
			system("cls");
			a[x][y]=10;
			for(int i=1;i<=Japanese_1S;i++){//日本鬼子1移动 
				if(abs(Japanese_1X[i]-x)<3&&abs(Japanese_1Y[i]-y)<3&&Japanese_1X[i]!=0&&Japanese_1Y[i]!=0){
					int Japanese_1Type=a[Japanese_1X[i]][Japanese_1Y[i]];
					a[Japanese_1X[i]][Japanese_1Y[i]]=0;
					if(x<Japanese_1X[i]&&a[Japanese_1X[i]-1][Japanese_1Y[i]]<5) Japanese_1X[i]--;
					else if(x>Japanese_1X[i]&&a[Japanese_1X[i]+1][Japanese_1Y[i]]<5) Japanese_1X[i]++;
					else if(y<Japanese_1Y[i]&&a[Japanese_1X[i]][Japanese_1Y[i]-1]<5) Japanese_1Y[i]--;
					else if(y>Japanese_1Y[i]&&a[Japanese_1X[i]][Japanese_1Y[i]+1]<5) Japanese_1Y[i]++;
					a[Japanese_1X[i]][Japanese_1Y[i]]=Japanese_1Type;
				}
			}
			for(int i=1;i<=Japanese_2S;i++){//日本鬼子2移动  
				if((Japanese_2X[i]!=x || Japanese_2Y[i]!=y)&&Japanese_2X[i]!=0&&Japanese_2Y[i]!=0){
					int Japanese_2Type=a[Japanese_2X[i]][Japanese_2Y[i]];
					a[Japanese_2X[i]][Japanese_2Y[i]]=0;
					if(Japanese_2X[i]>x && a[Japanese_2X[i]-1][Japanese_2Y[i]]<5) Japanese_2X[i]--;
					else if(Japanese_2X[i]<x && a[Japanese_2X[i]+1][Japanese_2Y[i]]<5) Japanese_2X[i]++;
					else if(Japanese_2Y[i]>y && a[Japanese_2X[i]][Japanese_2Y[i]-1]<5) Japanese_2Y[i]--;
					else if(Japanese_2Y[i]<y && a[Japanese_2X[i]][Japanese_2Y[i]+1]<5) Japanese_2Y[i]++;
					a[Japanese_2X[i]][Japanese_2Y[i]]=Japanese_2Type;
				}
			}
			for(int i=1;i<=bulletS;i++){//子弹移动 
				if(bulletX[i]!=0&&bulletY[i]!=0&&a[bulletX[i]+cx[bulletFx[i]]][bulletY[i]+cy[bulletFx[i]]]<5){
					a[bulletX[i]][bulletY[i]]=0;
					bulletX[i]+=cx[bulletFx[i]],bulletY[i]+=cy[bulletFx[i]];
					a[bulletX[i]][bulletY[i]]=17;
				}
				else if(!in(bulletX[i]+cx[bulletFx[i]],bulletY[i]+cy[bulletFx[i]])||a[bulletX[i]+cx[bulletFx[i]]][bulletY[i]+cy[bulletFx[i]]]){
					a[bulletX[i]][bulletY[i]]=0;
					bulletX[i]=0,bulletY[i]=0;
				}
			}
			for(int i=1;i<=Japanese_2S;i++){//日本鬼子2射箭 
				if(Japanese_2X[i]==x){
					if(Japanese_2Y[i]<y&&a[Japanese_2X[i]][Japanese_2Y[i]+1]<5&&abs(Japanese_2X[i]-x)<3&&abs(Japanese_2Y[i]-y)<3){
						bulletS++;
						bulletX[bulletS]=Japanese_2X[i],bulletY[bulletS]=Japanese_2Y[i]+1,bulletFx[bulletS]=0;
						a[bulletX[bulletS]][bulletY[bulletS]]=17;
					}
					else if(Japanese_2Y[i]>y&&a[Japanese_2X[i]][Japanese_2Y[i]-1]<5){
						bulletS++;
						bulletX[bulletS]=Japanese_2X[i],bulletY[bulletS]=Japanese_2Y[i]-1,bulletFx[bulletS]=2;
						a[bulletX[bulletS]][bulletY[bulletS]]=17;
					}
				}
				else if(Japanese_2Y[i]==y){
					if(Japanese_2X[i]<x&&a[Japanese_2X[i]+1][Japanese_2Y[i]]<5&&abs(Japanese_2X[i]-x)<3&&abs(Japanese_2Y[i]-y)<3){
						bulletS++;
						bulletX[bulletS]=Japanese_2X[i]+1,bulletY[bulletS]=Japanese_2Y[i],bulletFx[bulletS]=1;
						a[bulletX[bulletS]][bulletY[bulletS]]=17;
					}
					else if(Japanese_2X[i]>x&&a[Japanese_2X[i]-1][Japanese_2Y[i]]<5){
						bulletS++;
						bulletX[bulletS]=Japanese_2X[i]-1,bulletY[bulletS]=Japanese_2Y[i],bulletFx[bulletS]=3;
						a[bulletX[bulletS]][bulletY[bulletS]]=17;
					}
				}
			}
			mp();
			for(int i=1;i<=Japanese_1S;i++){//检测日本鬼子1攻击 
				for(int j=Japanese_1X[i]-2;j<=Japanese_1X[i]+2;j++){
					for(int k=Japanese_1Y[i]-2;k<=Japanese_1Y[i]+2;k++){
						if(x==j&&y==k){
							hp-=2;
							printf("玩家 被 日本鬼子1%d的毒气(chest:Japanese_1 %d) 攻击了\n",i,i);
							int is_Exp=rand()%15;
							if(is_Exp<14) is_Exp=0;
							else if(is_Exp==14) is_Exp=1;
							if(is_Exp==1){
								Japanese_1X[i]=0,Japanese_1Y[i]=0;
								a[Japanese_1X[i]][Japanese_1Y[i]]=0;
								alive_People_Exp();
							}
						}
					}
				}
			}
			for(int i=1;i<=bulletS;i++){//检测子弹攻击 
				int ar_killX=bulletX[i]+cx[bulletFx[i]],ar_killY=bulletY[i]+cy[bulletFx[i]];
				if(x==ar_killX&&y==ar_killY){
					hp--;
					printf("玩家 被 子弹%d(chest:bullet %d) 攻击了\n",i,i);
					a[bulletX[i]][bulletY[i]]=0;
					bulletX[i]=0,bulletY[i]=0;
				}
				for(int j=1;j<=Japanese_1S;j++){
					if(a[ar_killX][ar_killY]==9) a[ar_killX][ar_killY]=12,a[bulletX[i]][bulletY[i]]=0,bulletX[i]=0,bulletY[i]=0;
					else if(a[ar_killX][ar_killY]==12) a[ar_killX][ar_killY]=13,a[bulletX[i]][bulletY[i]]=0,bulletX[i]=0,bulletY[i]=0;
					else if(a[ar_killX][ar_killY]==13){
						a[ar_killX][ar_killY]=0,a[bulletX[i]][bulletY[i]]=0,bulletX[i]=0,bulletY[i]=0;
					}
				}
				for(int j=1;j<=Japanese_2S;j++){
					if(a[ar_killX][ar_killY]==14) a[ar_killX][ar_killY]=15,a[bulletX[i]][bulletY[i]]=0,bulletX[i]=0,bulletY[i]=0;
					else if(a[ar_killX][ar_killY]==15) a[ar_killX][ar_killY]=16,a[bulletX[i]][bulletY[i]]=0,bulletX[i]=0,bulletY[i]=0;
					else if(a[ar_killX][ar_killY]==16){
						a[ar_killX][ar_killY]=0,a[bulletX[i]][bulletY[i]]=0,bulletX[i]=0,bulletY[i]=0;
					}
				}
			}
			char todo;
			todo=getch();
			int goX=x,goY=y;
			if(todo=='d'||todo=='s'||todo=='a'||todo=='w') {
				if(todo=='d') goY++,fx=0;
				if(todo=='s') goX++,fx=1;
				if(todo=='a') goY--,fx=2;
				if(todo=='w') goX--,fx=3;
				if(in(goX,goY)&&(a[goX][goY]<5||a[goX][goY]==11||a[goX][goY]==17)) {
					a[goX][goY]=10;
					a[x][y]=0;
					x=goX,y=goY;
					step++;
				} else {
					printf("无效指令!\n");
					Sleep(500);
				}
			} else if(todo=='r') {
				return ;
			} else if(todo=='o') {
				goX=x,goY=y;
				if(fx==0) goY++,fx=0;
				if(fx==1) goX++,fx=1;
				if(fx==2) goY--,fx=2;
				if(fx==3) goX--,fx=3;
				if(in(goX,goY)&&(abs(goX-x)<2&&abs(goY-y)<2)&&a[goX][goY]==8) {
					chest();
					a[goX][goY]=0;
				} else {
					printf("无效指令!\n");
					Sleep(500);
				}
			} else if(todo=='t'){
				quickTeach();
				system("pause");
			} else if(todo=='k'){
				for(int i=0;i<4;i++){
					int killX=x+cx[i],killY=y+cy[i];
					if(a[killX][killY]==9) a[killX][killY]=12;
					else if(a[killX][killY]==12) a[killX][killY]=13;
					else if(a[killX][killY]==13){
						a[killX][killY]=0;
						for(int j=1;j<=Japanese_1S;j++){
							if(killX==Japanese_1X[j] && killY==Japanese_1Y[j]){
								int getJapanese_1Meat=rand()%6;
								Japanese_1X[j]=0,Japanese_1Y[j]=0;
								printf("玩家 击杀了 日本鬼子1 %d,获取 敌人的碎片 * %d\n",j,getJapanese_1Meat);
								printf("英勇的抗战战士们,加油,把所有日本鬼子都愤怒的撕碎吧!");
								sum[11]+=getJapanese_1Meat;
								Sleep(1000);
								break;
							}
						}
					}
					else if(a[killX][killY]==14) a[killX][killY]=15;
					else if(a[killX][killY]==15) a[killX][killY]=16;
					else if(a[killX][killY]==16){
						a[killX][killY]=0;
						for(int j=1;j<=Japanese_2S;j++){
							if(killX==Japanese_2X[j]&&killY==Japanese_2Y[j]){
								int getBones=rand()%4;
								Japanese_2X[j]=0,Japanese_2Y[j]=0;
								printf("玩家 击杀了 日本鬼子2 %d,获取 敌人的骨头 * %d\n",j,getBones);
								printf("英勇的抗战战士们,加油,把所有日本鬼子都愤怒的撕碎吧!");
								sum[12]+=getBones;
								Sleep(1000);
								break;
							}
						}
					}
					else{
						continue;
					}
				}
			} else if(todo=='u'){
				system("cls");
				useThing();
			} else if(todo=='e'){
				seeBag();
			} else if(todo=='q'){
				eatFood();
			} else if(todo=='/'&&is_order==1){
				string order;
				printf("/");
				getline(cin,order);
				if(order.substr(0,4) == "kill"){
					if(order.substr(11,16) == "chest:Japanese_1"){
						if(order[28]>='1'&&order[28]<='6'){
							a[Japanese_1X[order[28]-'0']][Japanese_1Y[order[28]-'0']]=0;
							Japanese_1X[order[28]-'0']=0,Japanese_1Y[order[28]-'0']=0;
							printf("已杀死 chest:Japanese_1 %c\n",order[28]);
							Sleep(1000);
						} else if(order.substr(28,3) == "all"){
							for(int i=1;i<=Japanese_1S;i++){
								a[Japanese_1X[i]][Japanese_1Y[i]]=0;
								Japanese_1X[i]=0,Japanese_1Y[i]=0;
								printf("已杀死 chest:Japanese_1 %d\n",i);
								Sleep(1000);
							}
						}
					} else if(order.substr(11,16) == "chest:Japanese_2"){
						if(order[28]>='1'&&order[28]<='6'){
							a[Japanese_2X[order[28]-'0']][Japanese_2Y[order[28]-'0']]=0;
							Japanese_2X[order[28]-'0']=0,Japanese_2Y[order[28]-'0']=0;
							printf("已杀死 chest:Japanese_2 %c\n",order[28]);
							Sleep(1000);
						} else if(order.substr(28,3) == "all"){
							for(int i=1;i<=Japanese_2S;i++){
								a[Japanese_2X[i]][Japanese_2Y[i]]=0;
								Japanese_2X[i]=0,Japanese_2Y[i]=0;
								printf("已杀死 chest:Japanese_2 %d\n",i);
								Sleep(1000);
							}
						}
					} else if(order.substr(11,12) == "chest:player"){
						hp=0,full=0;
					} else if(order.substr(11,3) == "all"){
						for(int i=1;i<=Japanese_1S;i++){
							a[Japanese_1X[i]][Japanese_1Y[i]]=0;
							Japanese_1X[i]=0,Japanese_1Y[i]=0;
							printf("已杀死 chest:Japanese_1 %d\n",i);
							Sleep(1000);
						}
						for(int i=1;i<=Japanese_2S;i++){
							a[Japanese_2X[i]][Japanese_2Y[i]]=0;
							Japanese_2X[i]=0,Japanese_2Y[i]=0;
							printf("已杀死 chest:Japanese_2 %d\n",i);
							Sleep(1000);
						}
						hp=0,full=0;
					}
				} else if(order.substr(0,2) == "tp"){
					a[x][y]=0;
					x=0,y=0;
					int order_p;
					for(order_p=3;;order_p++){//提取x 
						if(order[order_p]>='0'&&order[order_p]<='9'){
							x=x*10+int(order[order_p]-'0');
						}
						else{
							break;
						}
					}
					order_p=order_p+1;
					for(;;order_p++){//提取y 
						if(order[order_p]>='0'&&order[order_p]<='9'){
							y=y*10+int(order[order_p]-'0');
						}
						else{
							break;
						}
					}
				} else if(order.substr(0,8) == "beta_set"){
					int order_p,set_temp=0;
					string beta_name="";
					for(order_p=9;;order_p++){//提取beta_name 
						if(order[order_p]!=' '){
							beta_name+=order[order_p];
						}
						else{
							break;
						}
					}
					for(order_p=9+beta_name.size()+1;;order_p++){//提取set_temp 
						if(order[order_p]>='0'&&order[order_p]<='9'){
							set_temp=set_temp*10+int(order[order_p]-'0');
						}
						else{
							break;
						}
					}
					if(beta_name.substr(0,1) == "a"){
						int change_x=0,change_y=0;
						bool flag=0;
						for(int i=2;;i++){
							if(beta_name[i]>='0'&&beta_name[i]<='9'&&flag==0){
								change_x=change_x*10+(beta_name[i]-'0');
							} else if(beta_name[i]>='0'&&beta_name[i]<='9'&&flag==1){
								change_y=change_y*10+(beta_name[i]-'0');
							}
							if(beta_name[i]==']'&&flag==0){
								flag=1;
							} else if(beta_name[i]==']'&&flag==1){
								break;
							}
						}
						a[change_x][change_y]=set_temp;
					} else if(beta_name.substr(0,1) == "x"){
						a[x][y]=0,x=set_temp,a[x][y]=10;
					} else if(beta_name.substr(0,1) == "y"){
						a[x][y]=0,y=set_temp,a[x][y]=10;
					} else if(beta_name.substr(0,5) == "money"){
						money=set_temp;
					} else if(beta_name.substr(0,2) == "hp"){
						hp=set_temp;
					} else if(beta_name.substr(0,4) == "full"){
						full=set_temp;
					} else if(beta_name.substr(0,3) == "sum"){
						int change_x=0;
						for(int i=4;;i++){
							if(beta_name[i]>='0'&&beta_name[i]<='9'){
								change_x=change_x*10+(beta_name[i]-'0');
							} else{
								break;
							}
						}
						sum[change_x]=set_temp;
					}
				}
			}
			else if(todo=='/'&&is_order==0){
				printf("你没有作弊的权限!\n");
				Sleep(3000);
			}
			Sleep(1);
			system("cls");
		}
//游戏
	}
}
int main() {
	srand(time(0));
	game();
	return 0;
}
