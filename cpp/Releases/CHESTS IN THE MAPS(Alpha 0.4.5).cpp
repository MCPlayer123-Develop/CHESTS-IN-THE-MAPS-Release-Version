#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
const int N=55;
int n,a[N][N],sum[15],x,y,fx,money=0,hp=20;
int cx[4]= {0,1,0,-1};
int cy[4]= {1,0,-1,0};
bool vis[N][N],flag=0;
int thingMoney[15]= {1,5,100,100,200,300,1000,5000,10000000,50000000,30000000};
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
	if(x<5) {
		return ' ';
	}
	if(x>=5&&x<=7) {
		return 'W';
	}
	if(x==8) {
		return 'C';
	}
	if(x==9) {
		return 'G';
	}
	if(x==10) {
		return 'Y';
	}
	if(x==11) {
		return 'D';
	}
}
void mp() { //输出地图
	printf(" ╔════════════════╦═══════════════╗ \n"); 
	printf(" ║ 金钱:%9d",money);
	printf(" ║ 生命:%9d║ \n",hp);
	printf(" ╚════════════════╩═══════════════╝ \n"); 
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
	int st,en;
	memset(sum,0,sizeof(sum));
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
	while(1) {
		int shopSelect;
		printf("欢迎光临商店!\n");
		printf("请输入你要干什么:\n");
		printf("[0]买 [1]卖 [2]退出\n");
		scanf("%d",&shopSelect);
		if(shopSelect==0) {
			printf("金钱:%d\n",money);
			printf("1.末影珍珠:$1000,0000 传送至附近8*8的范围内\n");
			printf("2.治疗药水:$5000,0000 恢复至满血\n");
			printf("3.喷溅型伤害药水:$3000,0000 对4*4范围内的鬼造成10点伤害\n");
			printf("你要买那个(编号)?");
			int buy;
			scanf("%d",&buy);
			if(buy==1) {
				sum[8]++;
			} else if(buy==2) {
				sum[9]++;
			} else if(buy==3) {
				sum[10]++;
			}
		}
		if(shopSelect==1) {
			printf("金钱:%d\n",money);
			for(int i=0; i<11; i++) {
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
void quickTeach(){
	printf("教程:\n");
	printf("1.' '=空,'W'=墙,'C'=箱子,'Y'=玩家,'G'=鬼,'D'=门(出口)\n");
	printf("2.操作:");
	printf("  (1)w,a,s,d:上下左右\n");
	printf("  (2)o:开上一次方向的箱子\n");
	printf("  (3)k:攻击上一次方向的鬼\n");
	printf("  (4)r:退出\n");
	printf("  (5)e:打开背包\n");
	printf("  (6)t:查看教程\n");
}
void game() {
	printf("游戏选项:\n");
	printf("地图大小(5-20):[  ]\b\b\b");
	scanf("%d",&n);
	quickTeach();
	char c;
	c=getch();
	system("cls");
	while(1) {
		flag=0;
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
		x=2,y=2;
		a[x][y]=10;
		for(int i=1; i<=rand()%5; i++){
			int gx=rand()%(n+1),gy=rand()%(n+1);
			if(gx==0) gx++;
			if(gy==0) gy++;
			a[gx][gy]=8;
		}
		for(int i=1; i<=3; i++) {
			int gx=rand()%(n+1),gy=rand()%(n+1);
			if(gx==0) gx++;
			if(gy==0) gy++;
			a[gx][gy]=9;
		}
		a[n-1][n-1]=11;
//构建地图
		while(1) {
			if(x==n-1&&y==n-1) {
				printf("666,你到了终点!\n");
				int YN;
				printf("[0] 退出 [1]继续 [2]进入商店");
				scanf("%d",&YN);
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
			mp();
			char todo;
			todo=getch();
			int goX=x,goY=y;
			if(todo=='d'||todo=='s'||todo=='a'||todo=='w') {
				if(todo=='d') goY++,fx=0;
				if(todo=='s') goX++,fx=1;
				if(todo=='a') goY--,fx=2;
				if(todo=='w') goX--,fx=3;
				if(in(goX,goY)&&(a[goX][goY]<5||a[goX][goY]==11)) {
					a[goX][goY]=10;
					a[x][y]=0;
					x=goX,y=goY;
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
			}
			Sleep(1);
			system("cls");
		}
//游戏
	}
}
int main() {
	srand(time(0));
	system("color 03");
	printf("\n\n\n\n\n");
	printf("						CHESTS IN\n\n");
	printf("							THE MAPS\n\n");
	printf("						C++ EDITON\n");
	printf("\n\n\n\n\n");
	printf("						按任意键开始游戏...\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("Alpha 0.4.5(测试版)\n");
	char c=getch();
	system("cls");
	game();
	return 0;
}
