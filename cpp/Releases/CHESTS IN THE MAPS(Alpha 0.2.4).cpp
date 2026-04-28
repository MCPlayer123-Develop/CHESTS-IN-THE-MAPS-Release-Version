#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
const int N=55;
int n,a[N][N],sum[10],x,y,fx,money=0,hp=20;
int cx[4]={0,1,0,-1};
int cy[4]={1,0,-1,0};
bool vis[N][N],flag=0;
int thingMoney[10]={1,5,100,150,1000,1000,100000,1000000};
bool in(int x,int y){ 
	return (x>=1&&x<=n&&y>=1&&y<=n);
}
void checkRoad(int x,int y){//检测是否有路 
	if(x==n-1&&y==n-1){
		flag=1;
		return ;
	} 
	if(a[x][y]>5){
		return ;
	}
	vis[x][y]=1;
	for(int i=0;i<4;i++){
		int tx=x+cx[i],ty=y+cy[i];
		if(in(tx,ty)&&(a[tx][ty]<5||a[tx][ty]==11)&&vis[tx][ty]==0){
			checkRoad(tx,ty);
		} 
	}
	return ;
}
char printChar(int x){//数转字符 
	if(x<5){
		return ' ';
	}
	if(x>=5&&x<=7){
		return 'W';
	}
	if(x==8){
		return 'C';
	} 
	if(x==9){
		return 'G';
	}
	if(x==10){
		return 'Y';
	}
	if(x==11){
		return 'D';
	}
}
void mp(){//输出地图
	printf("金钱:%d\n",money);
	printf("生命:%d\n",hp);
	printf("  ");
	for(int i=1;i<=n;i++){
		printf("%2d",i);
	}
	printf("\n");
	for(int i=1;i<=n;i++){
		printf("%2d",i);
		for(int j=1;j<=n;j++){
			printf("%2c",printChar(a[i][j]));
		}
		printf("\n");
	}
}
void makeMp(int x,int y){//构建地图 
	vis[x][y]=1;
	a[x][y]=rand()%9;
	for(int i=0;i<4;i++){
		int tx=x+cx[i],ty=y+cy[i];
		if(in(tx,ty)&&a[tx][ty]==0){
			makeMp(tx,ty);
		}
	}
}
void chest(){//开箱子 
	int st,en;
	memset(sum,0,sizeof(sum));
	printf("箱子\n");
	printf("-------------------------------\n");
	for(int i=0;i<8;i++){
		int ChestMoney;
		if(i<=3){
			ChestMoney=rand()%64;
		}
		if(i>3){
			ChestMoney=rand()%10;
		}
		if(i==0) printf("原石:%d",ChestMoney),sum[0]+=ChestMoney;
		if(i==1) printf("煤炭:%d",ChestMoney),sum[1]+=ChestMoney;
		if(i==2) printf("铁锭:%d",ChestMoney),sum[2]+=ChestMoney;
		if(i==3) printf("红石:%d",ChestMoney),sum[3]+=ChestMoney;
		if(i==4) printf("青金石:%d",ChestMoney),sum[4]+=ChestMoney;
		if(i==5) printf("绿宝石:%d",ChestMoney),sum[5]+=ChestMoney;
		if(i==6) printf("金锭:%d",ChestMoney),sum[6]+=ChestMoney;
		if(i==7) printf("钻石:%d",ChestMoney),sum[7]+=ChestMoney;
		printf("\n-------------------------------\n");
	}
	printf("搜刮完毕！\n");
	Sleep(5000);
	return ;
}
void game(){
	printf("游戏选项:\n");
	printf("地图大小(4-20):[  ]\b\b\b");
	scanf("%d",&n);
	printf("教程:\n");
	printf("1.' '=空,'W'=墙,'C'=箱子,'Y'=玩家,'G'=鬼,'D'=门(出口)\n");
	printf("2.操作:");
	printf("  (1)w,a,s,d:上下左右\n");
	printf("  (2)o:开上一次方向的箱子\n");
	printf("  (3)k:攻击上一次方向的鬼\n");
	printf("  (4)r:退出\n");
	printf("  (5)e:打开背包\n");
	printf("请按任意键继续...");
	char c;
	c=getch();
	system("cls");
	while(1){
		flag=0;
		memset(vis,false,sizeof(vis));
		while(1){
			int MapX,MapY;//构建地图的起点 
			MapX=rand()%(n+1),MapY=rand()%(n+1);
			if(MapX==0) MapX++;
			if(MapY==0) MapY++;
			makeMp(MapX,MapY);
			checkRoad(2,2);//是否有路能到终点 
			if(flag==1){
				break;
			}
			flag=0;//初始化 
			memset(vis,false,sizeof(vis));
		}
		x=2,y=2;
		a[x][y]=10;
		a[n-1][n-1]=11;
		for(int i=1;i<=3;i++){
			int gx=rand()%(n+1),gy=rand()%(n+1);
			if(gx==0) gx++;
			if(gy==0) gy++;
			a[gx][gy]=9;
		}
		//构建地图 
		while(1){
			if(x==n-1&&y==n-1){
				printf("666,你到了终点!\n");
				int YN;
				printf("0:退出 1:继续");
				scanf("%d",&YN);
				if(YN==0){
					return ;
				}
				if(YN==1){
					break;
				}
			}
			a[x][y]=10;
			mp();
			char todo;
			todo=getchar();
			int goX=x,goY=y;
			if(todo=='d'||todo=='s'||todo=='a'||todo=='w'){
				if(todo=='d') goY++,fx=0;
				if(todo=='s') goX++,fx=1;
				if(todo=='a') goY--,fx=2;
				if(todo=='w') goX--,fx=3;
				if(in(goX,goY)&&(a[goX][goY]<5||a[goX][goY]==11)){
					a[goX][goY]=10;
					a[x][y]=0;
					x=goX,y=goY;
				}
				else{
					printf("无效指令!\n");
					Sleep(500);
				}
			}
			else if(todo=='r'){
				return ;
			} 
			else if(todo=='o'){
				goX=x,goY=y;
				if(fx==0) goY++,fx=0;
				if(fx==1) goX++,fx=1;
				if(fx==2) goY--,fx=2;
				if(fx==3) goX--,fx=3;
				if(in(goX,goY)&&(abs(goX-x)<2&&abs(goY-y)<2)&&a[goX][goY]==8){
					chest();
					a[goX][goY]=0;
				}
				else{
					printf("无效指令!\n");
					Sleep(500);
				}
			}
			Sleep(1);
			system("cls");
		} 
		//游戏 
	}
}
int main(){
	srand(time(0));
	system("color 03");
	printf("\n\n\n\n\n");
	printf("						CHESTS IN\n\n");
	printf("							THE MAPS\n\n");
	printf("						C++ EDITON\n");
	printf("\n\n\n\n\n");
	printf("						按任意键开始游戏...\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("Alpha 0.2.4(测试版)\n");
	char c=getch();
	system("cls");
	game();
	return 0;
}
