#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<algorithm>
#include<fstream>
using namespace std;
const int N=55;
int n,a[N][N],sum[30],x,y,fx,money=0,hp=20,full=20,step=0,Biome_Fest;
int zombieX[100],zombieY[100],zombieHp[100],zombieS;
int skeletonX[100],skeletonY[100],skeletonHp[100],skeletonS;
int arrowX[200005],arrowY[200005],arrowFx[200005],arrowS;
int nether[N][N];
int lava_zombieX[100],lava_zombieY[100],lava_zombieHp[100],lava_zombieS;
int burn_skeletonX[100],burn_skeletonY[100],burn_skeletonHp[100],burn_skeletonS;
int burn_arrowX[200005],burn_arrowY[200005],burn_arrowFx[200005],burn_arrowS;
int cx[4]= {0,1,0,-1};
int cy[4]= {1,0,-1,0};
int is_order,is_rebuild,is_save_thing,burn_time=0;
int skin_num=1;
bool vis[N][N],progress[105],flag=0,is_act_door=0,is_debug=0,is_first_level=1,nether_return=0;
int thingMoney[30]= {1,5,100,100,200,300,1000,5000,100000,500000,300000,0,0,10,0,100000,200000,0,0,0};
string died_Information="";
string Blue_slogan[11]{
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
string biome[10]={
	"chest:Overworld",
	"chest:Nether",
	"chest:Nether Fortress"
};
int skin_color[20]={
	0,0x9F,0xFF,0x45,0xAF,0xF0,0x08,0xC0
};
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
void read_dat(){
	FILE *fp = fopen("chest-game-data.dat", "r");
	if (fp != NULL) {
		fscanf(fp,"map size = %d\n",&n);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				fscanf(fp,"%d ",&a[i][j]);
			}
			fscanf(fp,"\n");
		}
		for(int i=0;i<=19;i++) fscanf(fp,"%d,",&sum[i]);
		fscanf(fp,"\n");
		fscanf(fp,"Coordinate = %d,%d(Direction:%d)\n",&x,&y,&fx);
		fscanf(fp,"money = %d\n",&money);
		fscanf(fp,"hp = %d\n",&hp);
		fscanf(fp,"full = %d\n",&full);
		fscanf(fp,"step = %d\n",&step);
		fscanf(fp,"biome = %d\n",&Biome_Fest);
		fscanf(fp,"zombieS = %d\n",&zombieS);
		for(int i=1;i<=zombieS;i++){
			fscanf(fp,"(%d,%d) Hp = %d\n",&zombieX[i],&zombieY[i],&zombieHp[i]);
		}
		fscanf(fp,"skeletonS = %d\n",&skeletonS);
		for(int i=1;i<=skeletonS;i++){
			fscanf(fp,"(%d,%d) Hp = %d\n",&skeletonX[i],&skeletonY[i],&skeletonHp[i]);
		}
		fscanf(fp,"arrowS = %d\n",&arrowS);
		for(int i=1;i<=arrowS;i++){
			fscanf(fp,"(%d,%d) Fancing = %d\n",&arrowX[i],&arrowY[i],&arrowFx[i]);
		}
		fscanf(fp,"progress:");
		for(int i=1;i<=8;i++){
			int temp;
			fscanf(fp,"%d,",&temp);
			if(temp==1) progress[i]=1;
			else progress[i]=0;
		}
		fscanf(fp,"\n");
		int temp;
		fscanf(fp,"is act door:%d\n",&temp);
		if(temp==1) is_act_door=1;
		else is_act_door=0;
		fscanf(fp,"is debug:%d\n",&temp);
		if(temp==1) is_debug=1;
		else is_debug=0;
		fscanf(fp,"is order:%d\n",&is_order);
		fscanf(fp,"skin = %d\n",&skin_num);
		if(Biome_Fest>=1&&Biome_Fest<=2){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					fscanf(fp,"%d ",&nether[i][j]);
				}
				fscanf(fp,"\n");
			}
			fscanf(fp,"lava_zombieS = %d\n",&lava_zombieS);
			for(int i=1;i<=lava_zombieS;i++){
				fscanf(fp,"(%d,%d) Hp = %d\n",&lava_zombieX[i],&lava_zombieY[i],&lava_zombieHp[i]);
			}
			fscanf(fp,"burn_skeletonS = %d\n",&burn_skeletonS);
			for(int i=1;i<=burn_skeletonS;i++){
				fscanf(fp,"(%d,%d) Hp = %d\n",&burn_skeletonX[i],&burn_skeletonY[i],&burn_skeletonHp[i]);
			}
			fscanf(fp,"burn_arrowS = %d\n",&burn_arrowS);
			for(int i=1;i<=burn_arrowS;i++){
				fscanf(fp,"(%d,%d) Fancing = %d\n",&burn_arrowX[i],&burn_arrowY[i],&burn_arrowFx[i]);
			}
		}
		if (fclose(fp) == 0) {
			
		} else {
			perror("关闭失败"); // 输出错误信息
		}
	}
}
void write_dat(){
	system("del chest-game-data.dat");
	FILE *fl = fopen("chest-game-data.dat", "w");
	if (fl != NULL) {
		fprintf(fl,"map size = %d\n",n);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				fprintf(fl,"%d ",a[i][j]);
			}
			fprintf(fl,"\n");
		}
		for(int i=0;i<=19;i++) fprintf(fl,"%d,",sum[i]);
		fprintf(fl,"\n");
		fprintf(fl,"Coordinate = %d,%d(Direction:%d)\n",x,y,fx);
		fprintf(fl,"money = %d\n",money);
		fprintf(fl,"hp = %d\n",hp);
		fprintf(fl,"full = %d\n",full);
		fprintf(fl,"step = %d\n",step);
		fprintf(fl,"biome = %d\n",Biome_Fest);
		fprintf(fl,"zombieS = %d\n",zombieS);
		for(int i=1;i<=zombieS;i++){
			fprintf(fl,"(%d,%d) Hp = %d\n",zombieX[i],zombieY[i],zombieHp[i]);
		}
		fprintf(fl,"skeletonS = %d\n",skeletonS);
		for(int i=1;i<=skeletonS;i++){
			fprintf(fl,"(%d,%d) Hp = %d\n",skeletonX[i],skeletonY[i],skeletonHp[i]);
		}
		fprintf(fl,"arrowS = %d\n",arrowS);
		for(int i=1;i<=arrowS;i++){
			fprintf(fl,"(%d,%d) Fancing = %d\n",arrowX[i],arrowY[i],arrowFx[i]);
		}
		fprintf(fl,"progress:");
		for(int i=1;i<=8;i++){
			int temp;
			if(progress[i]==1) temp=1;
			else temp=0;
			fprintf(fl,"%d,",temp);
		}
		fprintf(fl,"\n");
		int temp;
		if(is_act_door==1) temp=1;
		else temp=0;
		fprintf(fl,"is act door:%d\n",temp);
		if(is_debug==1) temp=1;
		else temp=0;
		fprintf(fl,"is debug:%d\n",temp);
		fprintf(fl,"is order:%d\n",is_order);
		fprintf(fl,"skin = %d\n",skin_num);
		if(nether_return==1){
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++){
					fprintf(fl,"%d ",nether[i][j]);
				}
				fprintf(fl,"\n");
			}
			fprintf(fl,"lava_zombieS = %d\n",lava_zombieS);
			for(int i=1;i<=lava_zombieS;i++){
				fprintf(fl,"(%d,%d) Hp = %d\n",lava_zombieX[i],lava_zombieY[i],lava_zombieHp[i]);
			}
			fprintf(fl,"burn_skeletonS = %d\n",burn_skeletonS);
			for(int i=1;i<=burn_skeletonS;i++){
				fprintf(fl,"(%d,%d) Hp = %d\n",burn_skeletonX[i],burn_skeletonY[i],burn_skeletonHp[i]);
			}
			fprintf(fl,"burn_arrowS = %d\n",burn_arrowS);
			for(int i=1;i<=burn_arrowS;i++){
				fprintf(fl,"(%d,%d) Fancing = %d\n",burn_arrowX[i],burn_arrowY[i],burn_arrowFx[i]);
			}
		}
		if (fclose(fl) == 0) {
			
		} else {
			perror("关闭失败"); // 输出错误信息
		}
	}
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xAF);
		return 'Z';
	}
	if(x==10){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),skin_color[skin_num]);
		return 'Y';
	}
	if(x==11){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x80);
		return 'D';
	}
	if(x==12){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xAF);
		return '2';
	}
	if(x==13){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xAF);
		return '1';
	}
	if(x==14){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xF0);
		return 'S';
	}
	if(x==15){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xF0);
		return '2'; 
	}
	if(x==16){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xF0);
		return '1';
	}
	if(x==17){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xF0);
		return 'A';
	}
	if(x==18){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x50);
		return 'D';
	}
	return '#';//未知纹理
}
char printChar_nether(int x){
	if(x==0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xC0);
		return ' ';
	}
	if(x==1){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
		return 'N';
	}
	if(x==2){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),skin_color[skin_num]);
		return 'Y';
	}
	if(x==3){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x50);
		return 'D';
	}
	if(x==4){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0xE0);
		return 'C';
	}
	if(x==5){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x45);
		return 'Z';
	}
	if(x==6){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x45);
		return '4';
	}
	if(x==7){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x45);
		return '3';
	}
	if(x==8){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x45);
		return '2';
	}
	if(x==9){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x45);
		return '1';
	}
	if(x==10){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x08);
		return 'S';
	}
	if(x==11){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x08);
		return '4';
	}
	if(x==12){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x08);
		return '3';
	}
	if(x==13){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x08);
		return '2';
	}
	if(x==14){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x08);
		return '1';
	}
	if(x==15){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
		return 'A';
	}
	return '#';//未知纹理
}
void mp() { //输出地图
	printf(" ╔════════════════╦═══════════════╦═══════════════╗ \n");
	printf(" ║ 金钱:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
	printf("%9d",money);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
	printf(" ║ 生命:");
	if(hp>15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
	else if(hp>10&&hp<=15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
	else if(hp<=10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
	printf("%9d",hp);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
	printf("║ 饱食度:");
	if(full>15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
	else if(full>10&&full<=15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
	else if(full<=10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
	printf("%7d",full);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
	printf("║ \n ╚════════════════╩═══════════════╩═══════════════╝ \n"); 
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
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
		}
		printf("\n");
	}
	if(is_debug==1){
		printf("\n");
		printf("Map size:%d\n",n);
		printf("Coordinate:(%d,%d)\n",x,y);
		printf("Direction:");
		if(fx==0) printf("East");
		if(fx==1) printf("South");
		if(fx==2) printf("West");
		if(fx==3) printf("North");
		printf("(Fancing:%d)\n",fx);
		printf("Biome Fest:");
		cout<<biome[Biome_Fest]<<endl;
		printf("Step for Full:%d\n",step);
		printf("Map dataization:\n");
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				printf("%d ",a[i][j]);
			}
			printf("\n");
		}
		printf("Total thing:\n");
		for(int i=0;i<17;i++){
			printf("%d ",sum[i]);
		}
		printf("\n");
		printf("Zombie Total:%d\n",zombieS);
		for(int i=1;i<=zombieS;i++){
			printf("Zombie Coordinate:(%d,%d) Hp:%d\n",zombieX[i],zombieY[i],zombieHp[i]);
		}
		printf("Skeleton Total:%d\n",skeletonS);
		for(int i=1;i<=skeletonS;i++){
			printf("Skeleton Coordinate:(%d,%d)\n",skeletonX[i],skeletonY[i]);
		}
		printf("Arrow Total:%d\n",arrowS);
		for(int i=1;i<=arrowS;i++){
			if(arrowX[i]>0&&arrowY[i]>0) printf("Arrow Coordinate:(%d,%d) Fancing:%d\n",arrowX[i],arrowY[i],arrowFx[i]);
		}
	}
}
void mp_Nether() { //输出地图
	printf(" ╔════════════════╦═══════════════╦═══════════════╗ \n");
	printf(" ║ 金钱:");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
	printf("%9d",money);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
	printf(" ║ 生命:");
	if(hp>15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
	else if(hp>10&&hp<=15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
	else if(hp<=10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
	printf("%9d",hp);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
	printf("║ 饱食度:");
	if(full>15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
	else if(full>10&&full<=15) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
	else if(full<=10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
	printf("%7d",full);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
	printf("║ \n ╚════════════════╩═══════════════╩═══════════════╝ \n"); 
	printf("\n");
	printf("  ");
	for(int i=1; i<=n; i++) {
		printf("%3d",i);
	}
	printf("\n");
	for(int i=1; i<=n; i++) {
		printf("%2d ",i);
		for(int j=1; j<=n; j++) {
			printf("[%c]",printChar_nether(nether[i][j]));
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
		}
		printf("\n");
	}
	if(is_debug==1){
		printf("\n");
		printf("Map size:%d\n",n);
		printf("Coordinate:(%d,%d)\n",x,y);
		printf("Direction:");
		if(fx==0) printf("East");
		if(fx==1) printf("South");
		if(fx==2) printf("West");
		if(fx==3) printf("North");
		printf("(Fancing:%d)\n",fx);
		printf("Biome Fest:");
		cout<<biome[Biome_Fest]<<endl;
		printf("Step for Full:%d\n",step);
		printf("Map dataization:\n");
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				printf("%d ",nether[i][j]);
			}
			printf("\n");
		}
		printf("Lava Zombie Total:%d\n",lava_zombieS);
		for(int i=1;i<=lava_zombieS;i++){
			printf("Lava Zombie Coordinate:(%d,%d) Hp:%d\n",lava_zombieX[i],lava_zombieY[i],lava_zombieHp[i]);
		}
		printf("Burn Skeleton Total:%d\n",burn_skeletonS);
		for(int i=1;i<=burn_skeletonS;i++){
			printf("Burn Skeleton Coordinate:(%d,%d) Hp:%d\n",burn_skeletonX[i],burn_skeletonY[i],burn_skeletonHp[i]);
		}
		printf("Burn Arrow Total:%d\n",burn_arrowS);
		for(int i=1;i<=burn_arrowS;i++){
			if(burn_arrowX[i]>0&&burn_arrowY[i]>0) printf("Burn Arrow Coordinate:(%d,%d) Fancing:%d\n",burn_arrowX[i],burn_arrowY[i],burn_arrowFx[i]);
		}
		printf("Total thing:\n");
		for(int i=0;i<17;i++){
			printf("%d ",sum[i]);
		}
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
void makeMp_nether(){
	int nether_mid;
	if(n%2==0) nether_mid=n/2;
	else if(n%2==1) nether_mid=(n+1)/2;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==nether_mid-1||i==nether_mid||i==nether_mid+1||j==nether_mid-1||j==nether_mid||j==nether_mid+1){
				nether[i][j]=1;
			}
			else{
				nether[i][j]=0;
			}
		}
	}
	nether[1][1]=3;
	x=1,y=2;
	nether[x][y]=2;
	nether[nether_mid][nether_mid]=4;
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
		printf("\n╠═══════════════════════╣ \n");
	}
	int ChestMoney=rand()%4;
	if(ChestMoney<3) ChestMoney=0;
	else if(ChestMoney==3) ChestMoney=1;
	printf("║ 打火石:%2d             ║ ",ChestMoney),sum[14]+=ChestMoney;
	int is_soundtrack=rand()%10,soundtrack=rand()%2;
	if(is_soundtrack==0){
		printf("\n╠═══════════════════════╣ \n");
		if(soundtrack==0) printf("║ 录音带-Happy Chests   ║ "),sum[17]++;
		if(soundtrack==1) printf("║ 录音带-Stressful      ║ "),sum[18]++;
	}
	printf("\n╚═══════════════════════╝ \n");
	printf("搜刮完毕！\n");
	system("pause");
	return ;
}
void chest_nether(){
	system("cls");
	printf("箱子\n");
	printf("╔═══════════════════════╗ \n");
	for(int i=15; i<17; i++) {
		int ChestMoney;
		ChestMoney=rand()%10;
		if(i==15) printf("║ 下界石英:%2d           ║ ",ChestMoney),sum[15]+=ChestMoney;
		if(i==16) printf("║ 萤石:%2d               ║ ",ChestMoney),sum[16]+=ChestMoney;
		if(i<16) printf("\n╠═══════════════════════╣ \n");
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
					Sleep(2000);
				}
			}
		}
		if(shopSelect==1) {
			printf("金钱:%d\n",money);
			for(int i=0; i<8; i++) {
				money+=sum[i]*thingMoney[i],sum[i]=0;
			}
			for(int i=15 ;i<17; i++){
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
	printf(" ╔═════════════════════════════════════════════════════════════════════════════╗ \n");
	printf(" ║ 教程:                                                                       ║ \n");
	printf(" ║ 1.画面:                                                                     ║ \n");
	printf(" ║   主世界:' '=泥土,'W'=墙,'C'=箱子,'Y'=玩家,'Z'=僵尸,'S'=骷髅,'D'=门,'A'=箭矢║ \n");
	printf(" ║   下界:' '=下界岩,'N'=下界砖,'D'=下界门,'C'=箱子,'Z'=熔岩僵尸               ║ \n");
	printf(" ║ 2.操作:                                                                     ║ \n");
	printf(" ║   (1)w,a,s,d:上下左右                                                       ║ \n");
	printf(" ║   (2)o:开上一次方向的箱子                                                   ║ \n");
	printf(" ║   (3)k:攻击四周的怪物                                                       ║ \n");
	printf(" ║   (4)r:退出                                                                 ║ \n");
	printf(" ║   (5)e:打开背包                                                             ║ \n");
	printf(" ║   (6)t:查看教程                                                             ║ \n");
	printf(" ║   (7)u:使用道具                                                             ║ \n");
	printf(" ║   (8)q:吃东西                                                               ║ \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf(" ║ 悄悄告诉你,金钱大于100000,命令输入eggs可以进入彩蛋关卡！                    ║ \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
	printf(" ╚═════════════════════════════════════════════════════════════════════════════╝ \n"); 
}
void useThing(){
	printf("背包道具:\n");
	printf(" ╔═══════════════════════╗ \n");
	printf(" ║ 1.末影珍珠:%2d         ║ \n",sum[8]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 2.治疗药水:%2d         ║ \n",sum[9]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 3.喷溅型伤害药水:%2d   ║ \n",sum[10]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 4.打火石:%2d           ║ \n",sum[14]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 5.录音带-Happy-Chests ║ \n");
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 6.录音带-Stessful     ║ \n");
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 7.录音带-Lava Zombie  ║ \n");
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
				for(int k=1;k<=zombieS;k++){
					if(zombieX[k]==i&&zombieY[k]==j){
						a[zombieX[k]][zombieY[k]]=0;
						zombieX[k]=0,zombieY[k]=0;
						printf("玩家 使用 喷溅型伤害药水,chest:zombie %d被杀死了\n",k);
					}
				}
				for(int k=1;k<=skeletonS;k++){
					if(skeletonX[k]==i&&skeletonY[k]==j){
						a[skeletonX[k]][skeletonY[k]]=0;
						skeletonX[k]=0,skeletonY[k]=0;
						printf("玩家 使用 喷溅型伤害药水,chest:skeleton %d被杀死了\n",k);
					}
				}
			}
		}
		Sleep(1000);
	}
	if(useSelect==4&&sum[14]>0){
		bool is_Found_Door=0;
		for(int i=0;i<4;i++){
			int tx=x+cx[i],ty=y+cy[i];
			if(a[tx][ty]==11){
				a[tx][ty]=18;
				is_Found_Door=1;
			}
		}
		if(is_Found_Door==0){
			printf("未找到门(chest:door)!");
		} else if(is_Found_Door==1){
			sum[14]--;
			printf("玩家 使用 打火石 激活了 下界传送门(chest:Nether_Door)\n");
			is_act_door=1;
			if(progress[6]==0){
				progress[6]=1;
				printf("玩家刚刚获得了进度");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x05);
				printf("[准备去新的维度]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
				printf("!\n");
				Sleep(2000);
			}
		}
		Sleep(1000);
	}
	if(useSelect==5&&sum[17]>0){
		system("start Happy_Chests.mp3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
		printf("正在播放-Happy Chests\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
		system("pause");
	}
	if(useSelect==6&&sum[18]>0){
		system("start Stressful.mp3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
		printf("正在播放-Stressful\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
		system("pause");
	}
	if(useSelect==7&&sum[19]>0){
		system("start Lava_Zombie.wav");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
		printf("正在播放-Lava Zombie\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
		system("pause");
	}
}
void useThing_nether(){
	printf("背包道具:\n");
	printf(" ╔═══════════════════════╗ \n");
	printf(" ║ 1.末影珍珠:%2d         ║ \n",sum[8]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 2.治疗药水:%2d         ║ \n",sum[9]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 3.喷溅型伤害药水:%2d   ║ \n",sum[10]);
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 4.录音带-Happy-Chests ║ \n");
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 5.录音带-Stessful     ║ \n");
	printf(" ╠═══════════════════════╣ \n");
	printf(" ║ 6.录音带-Lava Zombie  ║ \n");
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
		nether[x][y]=0;
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
				for(int k=1;k<=lava_zombieS;k++){
					if(lava_zombieX[k]==i&&lava_zombieY[k]==j){
						nether[lava_zombieX[k]][lava_zombieY[k]]=0;
						lava_zombieX[k]=0,lava_zombieY[k]=0;
						printf("玩家 使用 喷溅型伤害药水,chest:lava zombie %d被杀死了\n",k);
					}
				}
			}
		}
		Sleep(1000);
	}
	if(useSelect==4&&sum[17]>0){
		system("start Happy_Chests.mp3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
		printf("正在播放-Happy Chests\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
		system("pause");
	}
	if(useSelect==5&&sum[18]>0){
		system("start Stressful.mp3");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
		printf("正在播放-Stressful\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
		system("pause");
	}
	if(useSelect==6&&sum[19]>0){
		system("start Lava_Zombie.wav");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
		printf("正在播放-Lava_Zombie\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
		system("pause");
	}
}
void seeBag(){
	system("cls");
	printf("背包\n");
	printf("╔═══════════════════════╗ \n");
	for(int i=0; i<20; i++) {
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
		if(i==11) printf("║ 腐肉:%2d               ║ ",sum[i]);
		if(i==12) printf("║ 骨头:%2d               ║ ",sum[i]);
		if(i==13) printf("║ 面包:%2d               ║ ",sum[i]);
		if(i==14) printf("║ 打火石:%2d             ║ ",sum[i]);
		if(i==15) printf("║ 下界石英:%2d           ║ ",sum[i]);
		if(i==16) printf("║ 萤石:%2d               ║ ",sum[i]);
		if(i==17) printf("║ 录音带-Happy Chests:%2d║ ",sum[i]);
		if(i==18) printf("║ 录音带-Stressful:%2d   ║ ",sum[i]);
		if(i==19) printf("║ 录音带-Lava Zombie:%2d ║ ",sum[i]);
		if(i<19){
			printf("\n╠═══════════════════════╣ \n");
		}
	}
	printf("\n╚═══════════════════════╝ \n");
	system("pause");
}
void eatFood(){
	printf("食物:\n");
	printf("╔═══════════════════════╗ \n");
	printf("║ 1.腐肉:%2d             ║ \n",sum[11]);
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
void seeProgress(){
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("成就\n");
	printf("主世界\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
	printf("[小小怪物，轻松拿捏]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("击杀任意一只怪物 ");
	if(progress[1]==0){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);printf("未获得！\n");}
	else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
	printf("[远处有个狙击手]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("让骷髅的箭射中你 ");
	if(progress[2]==0){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);printf("未获得！\n");}
	else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
	printf("[这是什么？箱子！]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("打开一个箱子 ");
	if(progress[3]==0){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);printf("未获得！\n");}
	else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
	printf("[抵达终点]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("到达终点 ");
	if(progress[4]==0){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);printf("未获得！\n");}
	else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
	printf("[哦，不！]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("死亡一次 ");
	if(progress[5]==0){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);printf("未获得！\n");}
	else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("下界\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x05);
	printf("[准备去新的维度]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("激活下界传送门 ");
	if(progress[6]==0){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);printf("未获得！\n");}
	else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x05);
	printf("[勇闯下界]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("进入下界 ");
	if(progress[7]==0){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);printf("未获得！\n");}
	else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x05);
	printf("[燃起来了]\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
	printf("燃烧骷髅的火矢真的很热！ ");
	if(progress[8]==0){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);printf("未获得！\n");}
	else printf("已获得！\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
	system("pause");
}
void skin_shop(){
	system("cls");
	while(1){
		printf("欢迎来到皮肤商城!这里有许多皮肤!按w,s键上下选择,按r键确认!\n");
		for(int i=1;i<=7;i++){//0,0x9F,0xFF,0xC5,0xAF,0xF0,0x08,0xC0
			if(skin_num==i){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0E);
				printf("->   ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
			} else{
				printf("     ");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),skin_color[i]);
			printf("[Y]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
			if(i==1) printf("   正常款");
			else if(i==2) printf("   隐身款");
			else if(i==3) printf("   惊悚恐怖熔岩僵尸款");
			else if(i==4) printf("   僵尸款");
			else if(i==5) printf("   骷髅款");
			else if(i==6) printf("   炽热燃烧骷髅款");
			else if(i==7) printf("   血腥残暴款");
			printf("\n");
		}
		char skin_shop_select=getch();
		if(skin_shop_select=='r'){
			return ;
		} else if(skin_shop_select=='w'){
			skin_num--;
			skin_num=max(1,skin_num);
		} else if(skin_shop_select=='s'){
			skin_num++;
			skin_num=min(7,skin_num);
		}
		system("cls");
	}
}
void game_nether(){
	system("cls");
	system("color 0C");
	int nether_mid;
	if(n%2==0) nether_mid=n/2;
	else if(n%2==1) nether_mid=(n+1)/2;
	if((is_rebuild==1)||(is_rebuild==0&&is_first_level==0)){
		system("color 5F");
		for(int i=0;i<=99;i++){
			system("cls");
			printf("\n\n\n\n\n\n                                                  下载地形中...\n\n                                                     ");
			printf("[%d%%]",i);
			Sleep(10);
		}
		Sleep(1000);
		system("cls");
		printf("\n\n\n\n\n\n                                                  下载地形中...\n\n                                                     ");
		printf("[100%%]");//下载地形动画
		Sleep(1000);
		system("cls");
		system("color 0C");
		makeMp_nether();
		if(n<10) lava_zombieS=1;
		else lava_zombieS=2;
		for(int i=1;i<=lava_zombieS;i++){
			lava_zombieX[i]=rand()%3+nether_mid-1;
			lava_zombieY[i]=rand()%3+nether_mid-1;
			if(lava_zombieX[i]==nether_mid&&lava_zombieY[i]==nether_mid){
				lava_zombieX[i]++;
			}
			lava_zombieHp[i]=5;
			nether[lava_zombieX[i]][lava_zombieY[i]]=5;
		}
		if(n<10) burn_skeletonS=1;
		else burn_skeletonS=2;
		for(int i=1;i<=burn_skeletonS;i++){
			burn_skeletonX[i]=rand()%3+nether_mid-1;
			burn_skeletonY[i]=rand()%(nether_mid-2)+1;
			burn_skeletonHp[i]=5;
			nether[burn_skeletonX[i]][burn_skeletonY[i]]=10;
		}
	}
	while(1){
		for(int i=1;i<=lava_zombieS;i++){
			if(lava_zombieHp[i]==5) nether[lava_zombieX[i]][lava_zombieY[i]]=5;
			else if(lava_zombieHp[i]==4) nether[lava_zombieX[i]][lava_zombieY[i]]=6;
			else if(lava_zombieHp[i]==3) nether[lava_zombieX[i]][lava_zombieY[i]]=7;
			else if(lava_zombieHp[i]==2) nether[lava_zombieX[i]][lava_zombieY[i]]=8;
			else if(lava_zombieHp[i]==1) nether[lava_zombieX[i]][lava_zombieY[i]]=9;
		}
		if(burn_time>0){//燃烧
			burn_time--,hp--;
			if(hp<=0){
				died_Information="You were burn to death.";
			}
		}
		if(step>0&&step%10==0&&full>0){//更新饱食度
			full--;
		}
		if(full==20){
			hp++;
			hp=min(hp,20);
		}
		if(full==0){
			hp--;
			if(hp<=0){
				died_Information="You starved to death.";
			}
		}
		if(hp<=0){
			if(progress[5]==0){
				progress[5]=1;
				printf("玩家刚刚获得了进度");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
				printf("[哦，不！！！]");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
				printf("!\n");
				Sleep(2000);
				system("cls");
			}
			memset(sum,0,sizeof(sum));
			money=0;
			hp=20;
			nether[x][y]=0;
			system("cls");
			system("color CF");
			printf("\n\n\n\n\n\n\n");
			printf("                                    你死了！\n\n\n");
			printf("   The information of you dies:");
			cout<<died_Information;
			printf("\n\n\n");
			int YN;
			printf("                      [0]退出游戏 [1]重生 [2]返回标题屏幕");
			arrowS=0;
			memset(arrowX,0,sizeof(arrowX));
			memset(arrowY,0,sizeof(arrowY));
			is_act_door=0;
			scanf("%d",&YN);
			if(YN==0) {
				return ;
			}
			if(YN==1) {
				system("color 03");
				break;
			}
			if(YN==2) {
				system("cls");
				return ;
			}
		}
		if(x==1&&y==1){
			system("color 5F");
			for(int i=0;i<=99;i++){
				system("cls");
				printf("\n\n\n\n\n\n                                                  下载地形中...\n\n                                                     ");
				printf("[%d%%]",i);
				Sleep(10);
			}
			Sleep(1000);
			system("cls");
			printf("\n\n\n\n\n\n                                                  下载地形中...\n\n                                                     ");
			printf("[100%%]");//下载地形动画
			Sleep(1000);
			x=2,y=2;
			return ;
		}
		if((x>=nether_mid-1&&x<=nether_mid+1)||(y>=nether_mid-1&&y<=nether_mid+1)){
			Biome_Fest=2;
		}
		for(int i=1;i<=lava_zombieS;i++){//熔岩僵尸移动 
			if(abs(lava_zombieX[i]-x)<4&&abs(lava_zombieY[i]-y)<4&&lava_zombieX[i]!=0&&lava_zombieY[i]!=0){
				int lava_zombieType=nether[lava_zombieX[i]][lava_zombieY[i]];
				int temp;
				if((lava_zombieX[i]>=nether_mid-1&&lava_zombieX[i]<=nether_mid+1)||(lava_zombieY[i]>=nether_mid-1&&lava_zombieY[i]<=nether_mid+1)){
					temp=1;
				} else{
					temp=0;
				}
				nether[lava_zombieX[i]][lava_zombieY[i]]=temp;
				if(x<lava_zombieX[i]&&nether[lava_zombieX[i]-1][lava_zombieY[i]]<2) lava_zombieX[i]--;
				else if(x>lava_zombieX[i]&&nether[lava_zombieX[i]+1][lava_zombieY[i]]<2) lava_zombieX[i]++;
				else if(y<lava_zombieY[i]&&nether[lava_zombieX[i]][lava_zombieY[i]-1]<2) lava_zombieY[i]--;
				else if(y>lava_zombieY[i]&&nether[lava_zombieX[i]][lava_zombieY[i]+1]<2) lava_zombieY[i]++;
				nether[lava_zombieX[i]][lava_zombieY[i]]=lava_zombieType;
			}
		}
		for(int i=1;i<=burn_skeletonS;i++){//燃烧骷髅移动 
			if(abs(burn_skeletonX[i]-x)<4&&abs(burn_skeletonY[i]-y)<4&&burn_skeletonX[i]!=0&&burn_skeletonY[i]!=0){
				int burn_skeletonType=nether[burn_skeletonX[i]][burn_skeletonY[i]];
				int temp;
				if((burn_skeletonX[i]>=nether_mid-1&&burn_skeletonX[i]<=nether_mid+1)||(burn_skeletonY[i]>=nether_mid-1&&burn_skeletonY[i]<=nether_mid+1)){
					temp=1;
				} else{
					temp=0;
				}
				nether[burn_skeletonX[i]][burn_skeletonY[i]]=temp;
				if(x<burn_skeletonX[i]&&nether[burn_skeletonX[i]-1][burn_skeletonY[i]]<2) burn_skeletonX[i]--;
				else if(x>burn_skeletonX[i]&&nether[burn_skeletonX[i]+1][burn_skeletonY[i]]<2) burn_skeletonX[i]++;
				else if(y<burn_skeletonY[i]&&nether[burn_skeletonX[i]][burn_skeletonY[i]-1]<2) burn_skeletonY[i]--;
				else if(y>burn_skeletonY[i]&&nether[burn_skeletonX[i]][burn_skeletonY[i]+1]<2) burn_skeletonY[i]++;
				nether[burn_skeletonX[i]][burn_skeletonY[i]]=burn_skeletonType;
			}
		}
		for(int i=1;i<=burn_arrowS;i++){//火矢移动
			if(burn_arrowX[i] != 0&&burn_arrowY[i] != 0&&nether[burn_arrowX[i]+cx[burn_arrowFx[i]]][burn_arrowY[i]+cy[burn_arrowFx[i]]]<2){
				int temp;
				if((burn_arrowX[i]>=nether_mid-1&&burn_arrowX[i]<=nether_mid+1)||(burn_arrowY[i]>=nether_mid-1&&burn_arrowY[i]<=nether_mid+1)){
					temp=1;
				} else{
					temp=0;
				}
				nether[burn_arrowX[i]][burn_arrowY[i]]=temp;
				burn_arrowX[i]+=cx[burn_arrowFx[i]],burn_arrowY[i]+=cy[burn_arrowFx[i]];
				nether[burn_arrowX[i]][burn_arrowY[i]]=15;
			}
			else if(!in(burn_arrowX[i]+cx[burn_arrowFx[i]],burn_arrowY[i]+cy[burn_arrowFx[i]])||nether[burn_arrowX[i]+cx[burn_arrowFx[i]]][burn_arrowY[i]+cy[burn_arrowFx[i]]]){
				nether[burn_arrowX[i]][burn_arrowY[i]]=0;
				burn_arrowX[i]=0,burn_arrowY[i]=0;
			}
		}
		for(int i=1;i<=burn_skeletonS;i++){//燃烧骷髅射火矢 
			if(burn_skeletonX[i]==x){
				if(burn_skeletonY[i]<y&&nether[burn_skeletonX[i]][burn_skeletonY[i]+1]<2&&abs(burn_skeletonX[i]-x)<3&&abs(burn_skeletonY[i]-y)<3){
					burn_arrowS++;
					burn_arrowX[burn_arrowS]=burn_skeletonX[i],burn_arrowY[burn_arrowS]=burn_skeletonY[i]+1,burn_arrowFx[burn_arrowS]=0;
					nether[burn_arrowX[burn_arrowS]][burn_arrowY[burn_arrowS]]=15;
				}
				else if(burn_skeletonY[i]>y&&nether[burn_skeletonX[i]][burn_skeletonY[i]-1]<2&&abs(burn_skeletonX[i]-x)<3&&abs(burn_skeletonY[i]-y)<3){
					burn_arrowS++;
					burn_arrowX[burn_arrowS]=burn_skeletonX[i],burn_arrowY[burn_arrowS]=burn_skeletonY[i]-1,burn_arrowFx[burn_arrowS]=2;
					nether[burn_arrowX[burn_arrowS]][burn_arrowY[burn_arrowS]]=15;
				}
			}
			else if(burn_skeletonY[i]==y){
				if(burn_skeletonX[i]<x&&nether[burn_skeletonX[i]+1][burn_skeletonY[i]]<2&&abs(burn_skeletonX[i]-x)<3&&abs(burn_skeletonY[i]-y)<3){
					burn_arrowS++;
					burn_arrowX[burn_arrowS]=burn_skeletonX[i]+1,burn_arrowY[burn_arrowS]=burn_skeletonY[i],burn_arrowFx[burn_arrowS]=1;
					nether[burn_arrowX[burn_arrowS]][burn_arrowY[burn_arrowS]]=15;
				}
				else if(burn_skeletonX[i]>x&&nether[burn_skeletonX[i]-1][burn_skeletonY[i]]<2&&abs(burn_skeletonX[i]-x)<3&&abs(burn_skeletonY[i]-y)<3){
					burn_arrowS++;
					burn_arrowX[burn_arrowS]=burn_skeletonX[i]-1,burn_arrowY[burn_arrowS]=burn_skeletonY[i],burn_arrowFx[burn_arrowS]=3;
					nether[burn_arrowX[burn_arrowS]][burn_arrowY[burn_arrowS]]=15;
				}
			}
		}
		mp_Nether();
		if(progress[7]==0){
			progress[7]=1;
			printf("玩家刚刚获得了进度");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x05);
			printf("[勇闯下界]");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
			printf("!\n");
			Sleep(2000);
		}
		for(int i=1;i<=lava_zombieS;i++){//检测熔岩僵尸攻击 
			for(int j=0;j<4;j++){
				int zo_killX=lava_zombieX[i]+cx[j],zo_killY=lava_zombieY[i]+cy[j];
				if(x==zo_killX&&y==zo_killY){
					hp-=2;
					if(hp<=0){
						died_Information="You were killed by the lava zombie.";
					}
					printf("玩家 被 熔岩僵尸%d(chest:lava zombie %d) 攻击了\n",i,i);
				}
			}
		}
		for(int i=1;i<=burn_skeletonS;i++){//检测燃烧骷髅近战攻击
			for(int j=0;j<4;j++){
				int sk_killX=burn_skeletonX[i]+cx[j],sk_killY=burn_skeletonY[i]+cy[j];
				if(x==sk_killX&&y==sk_killY){
					burn_time=3;
					if(hp<=0){
						died_Information="You were killed by the skeleton.";
					}
					printf("玩家 被 燃烧骷髅%d(chest:burn_skeleton %d) 攻击了,开始燃烧[3s]\n",i,i);
				}
			}
		}
		for(int i=1;i<=burn_arrowS;i++){//检测火矢攻击
			int ar_killX=burn_arrowX[i]+cx[burn_arrowFx[i]],ar_killY=burn_arrowY[i]+cy[burn_arrowFx[i]];
			if(x==ar_killX&&y==ar_killY){
				burn_time=3;
				int temp;
				if((burn_arrowX[i]>=nether_mid-1&&burn_arrowX[i]<=nether_mid+1)||(burn_arrowY[i]>=nether_mid-1&&burn_arrowY[i]<=nether_mid+1)){
					temp=1;
				} else{
					temp=0;
				}
				nether[burn_arrowX[i]][burn_arrowY[i]]=temp;
				burn_arrowX[i]=0,burn_arrowY[i]=0;
				printf("玩家 被 火矢%d(chest:burn_arrow %d) 攻击了,开始燃烧[3s]\n",i,i);
				if(progress[8]==0){
					progress[8]=1;
					printf("玩家刚刚获得了进度");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x05);
					printf("[燃起来了]");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
					printf("!\n");
					Sleep(2000);
				}
			}
		}
		Biome_Fest=1;
		nether[x][y]=2;
		char todo=getch();
		if(todo=='d'||todo=='s'||todo=='a'||todo=='w') {
			int goX=x,goY=y;
			if(todo=='d') goY++,fx=0;
			if(todo=='s') goX++,fx=1;
			if(todo=='a') goY--,fx=2;
			if(todo=='w') goX--,fx=3;
			if(in(goX,goY)&&(nether[goX][goY]==0||nether[goX][goY]==1||nether[goX][goY]==3)) {
				int temp;
				if((x>=nether_mid-1&&x<=nether_mid+1)||(y>=nether_mid-1&&y<=nether_mid+1)){
					temp=1;
				} else{
					temp=0;
				}
				nether[goX][goY]=2;
				nether[x][y]=temp;
				x=goX,y=goY;
				step++;
			}
		} else if(todo=='o') {
			int goX,goY;
			goX=x,goY=y;
			if(fx==0) goY++,fx=0;
			if(fx==1) goX++,fx=1;
			if(fx==2) goY--,fx=2;
			if(fx==3) goX--,fx=3;
			if(in(goX,goY)&&(abs(goX-x)<2&&abs(goY-y)<2)&&nether[goX][goY]==4) {
				chest_nether();
				int temp;
				if((goX>=nether_mid-1&&goX<=nether_mid+1)||(goX>=nether_mid-1&&goX<=nether_mid+1)){
					temp=1;
				} else{
					temp=0;
				}
				nether[goX][goY]=temp;
			}
		} else if(todo=='1'){
			is_debug=!is_debug;
		} else if(todo=='t'){
			quickTeach();
			system("pause");
		} else if(todo=='k'){
			for(int i=0;i<4;i++){
				int killX=x+cx[i],killY=y+cy[i];
				if(nether[killX][killY]>=5&&nether[killX][killY]<=9){
					if(nether[killX][killY]==9){
						for(int j=1;j<=lava_zombieS;j++){
							if(killX==lava_zombieX[j]&&killY==lava_zombieY[j]){
								int temp;
								if((lava_zombieX[j]>=nether_mid-1&&lava_zombieX[j]<=nether_mid+1)||(lava_zombieY[j]>=nether_mid-1&&lava_zombieY[j]<=nether_mid+1)){
									temp=1;
								} else{
									temp=0;
								}
								nether[lava_zombieX[j]][lava_zombieY[j]]=temp;
								int getZombieMeat=rand()%5,getGoldIrgot=rand()%2;
								lava_zombieX[j]=0,lava_zombieY[j]=0;
								printf("玩家 击杀了 熔岩僵尸 %d,获取 腐肉 * %d,金锭 * %d\n",j,getZombieMeat,getGoldIrgot);
								sum[11]+=getZombieMeat;
								sum[3]+=getGoldIrgot;
								Sleep(1000);
								break;
							}
						}
					}
					else nether[killX][killY]++;
					for(int j=1;j<=lava_zombieS;j++){
						if(killX==lava_zombieX[j]&&killY==lava_zombieY[j]){
							lava_zombieHp[j]--;
						}
					}
				} else if(nether[killX][killY]>=10&&nether[killX][killY]<=14){
					if(nether[killX][killY]==14){
						for(int j=1;j<=burn_skeletonS;j++){
							if(killX==burn_skeletonX[j]&&killY==burn_skeletonY[j]){
								int temp;
								if((burn_skeletonX[j]>=nether_mid-1&&burn_skeletonY[j]<=nether_mid+1)||(burn_skeletonX[j]>=nether_mid-1&&burn_skeletonY[j]<=nether_mid+1)){
									temp=1;
								} else{
									temp=0;
								}
								nether[burn_skeletonX[j]][burn_skeletonY[j]]=temp;
								int getBone=rand()%5,getFlintAndSteel=rand()%2;
								burn_skeletonX[j]=0,burn_skeletonY[j]=0;
								printf("玩家 击杀了 燃烧骷髅 %d,获取 骨头 * %d,打火石 * %d\n",j,getBone,getFlintAndSteel);
								sum[12]+=getBone;
								sum[14]+=getFlintAndSteel;
								Sleep(1000);
								break;
							}
						}
					} else nether[killX][killY]++;
					for(int j=1;j<=burn_arrowS;j++){
						if(killX==burn_skeletonX[j]&&killY==burn_skeletonY[j]){
							burn_skeletonHp[j]--;
						}
					}
				}
			}
		} else if(todo=='e'){
			seeBag();
		} else if(todo=='q'){
			eatFood();
		} else if(todo=='r'){
			nether_return=1;
			return ;
		} else if(todo=='/'&&is_order==1){
			string order;
			printf("/");
			getline(cin,order);
			if(order.substr(0,4) == "kill"){
				if(order.substr(11,17) == "chest:lava_zombie"){
					if(order[29]>='1'&&order[29]<='6'){
						int temp;
						if((lava_zombieX[order[29]-'0']>=nether_mid-1&&lava_zombieX[order[29]-'0']<=nether_mid+1)||(lava_zombieY[order[29]-'0']>=nether_mid-1&&lava_zombieY[order[29]-'0']<=nether_mid+1)){
							temp=1;
						} else{
							temp=0;
						}
						nether[lava_zombieX[order[29]-'0']][lava_zombieY[order[29]-'0']]=temp;
						lava_zombieX[order[29]-'0']=0,lava_zombieY[order[29]-'0']=0;
						printf("已杀死 chest:lava_zombie %c\n",order[29]);
						Sleep(1000);
					} else if(order.substr(29,3) == "all"){
						for(int i=1;i<=lava_zombieS;i++){
							int temp;
							if((lava_zombieX[i]>=nether_mid-1&&lava_zombieX[i]<=nether_mid+1)||(lava_zombieY[i]>=nether_mid-1&&lava_zombieY[i]<=nether_mid+1)){
								temp=1;
							} else{
								temp=0;
							}
							nether[lava_zombieX[i]][lava_zombieY[i]]=temp;
							lava_zombieX[i]=0,lava_zombieY[i]=0;
							printf("已杀死 chest:lava_zombie %d\n",i);
							Sleep(1000);
						}
					}
				} else if(order.substr(11,12) == "chest:player"){
					hp=0,full=1;
					died_Information="You have been killed.";
				} else if(order.substr(11,3) == "all"){
					for(int i=1;i<=lava_zombieS;i++){
						nether[lava_zombieX[i]][lava_zombieY[i]]=0;
						lava_zombieX[i]=0,lava_zombieY[i]=0;
						printf("已杀死 chest:lava_zombie %d\n",i);
						Sleep(1000);
					}
					hp=0,full=1;
					died_Information="You have been killed.";
				}
			} else if(order.substr(0,2) == "tp"){
				nether[x][y]=0;
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
				if(beta_name.substr(0,6) == "nether"){
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
					nether[change_x][change_y]=set_temp;
				} else if(beta_name.substr(0,1) == "x"){
					nether[x][y]=0,x=set_temp,nether[x][y]=10;
				} else if(beta_name.substr(0,1) == "y"){
					nether[x][y]=0,y=set_temp,nether[x][y]=10;
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
			} else if(order.substr(0,4)=="help"){
				printf(" ╔═════════════════════════════════════════════════════════════════════════════╗ \n");
				printf(" ║ 指令的使用(先在'游戏选项-作弊'中输入1)                                      ║ \n");
				printf(" ║   (1)/kill [type=<entity name>] 杀死某种实体                                ║ \n");
				printf(" ║     可用实体名称:                                                           ║ \n");
				printf(" ║     1.chest:zombie                                                          ║ \n");
				printf(" ║     2.chest:skeleton                                                        ║ \n");
				printf(" ║     3.chest:player                                                          ║ \n");
				printf(" ║     4.chest:lava_zombie                                                     ║ \n");
				printf(" ║     5.chest:burn_skeleton                                                   ║ \n");
				printf(" ║     6.all                                                                   ║ \n");
				printf(" ║   (2)/tp <x> <y> 将玩家传送到(行,列)                                        ║ \n");
				printf(" ║   (3)/beta_set <Beta Name> <beta> 修改游戏数据                              ║ \n");
				printf(" ║     数据名称:                                                               ║ \n");
				printf(" ║     1.a[x][y]                                                               ║ \n");
				printf(" ║     2.nether[x][y]                                                          ║ \n");
				printf(" ║     3.x                                                                     ║ \n");
				printf(" ║     4.y                                                                     ║ \n");
				printf(" ║     5.money                                                                 ║ \n");
				printf(" ║     6.hp                                                                    ║ \n");
				printf(" ║     7.full                                                                  ║ \n");
				printf(" ║     8.sum[i]                                                                ║ \n");
				printf(" ╚═════════════════════════════════════════════════════════════════════════════╝ \n");
				system("pause");
			} else if(order.substr(0,4)=="eggs"&&money>=100000){
				system("start https://www.bilibili.com/video/BV1GJ411x7h7/?spm_id_from=333.337.search-card.all.click");
				hp=0,full=1;
				died_Information="You have been tricked.That's fun!Haha!";
			} else{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
				printf("指令无效!\n");
				Sleep(1000);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
			}
		} else if(todo=='/'&&is_order==0){
			string order;
			printf("/");
			getline(cin,order);
			if(order.substr(0,4)=="eggs"&&money>=100000){
				system("start https://www.bilibili.com/video/BV1GJ411x7h7/?spm_id_from=333.337.search-card.all.click");
				hp=0,full=1;
				died_Information="You have been tricked.That's fun!Haha!";
			} else{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
				printf("你没有作弊的权限!\n");
				Sleep(1000);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
			}
		} else if(todo=='u'){
			useThing_nether();
		} else if(todo=='p'){
			seeProgress();
			system("color 0C");
		}
		system("cls");
	}
}
void game() {
	system("color 03");
	printf("\n\n\n\n\n");
	printf("                                          ╔═════════════════════════╗ \n");
	printf("					  ║       CHESTS IN         ║\n");
	printf("					  ║                         ║\n");
	printf("					  ║            THE MAPS     ║\n");
	printf("					  ║                         ║\n");
	printf("					  ║       C++ EDITION       ║\n");
	printf("                                          ╚═════════════════════════╝ \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0B);
	printf("                                              ");
	int slogan_p=rand()%11;
	cout<<Blue_slogan[slogan_p]<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
	printf("                                                   勇闯下界\n");
	printf("                                             Through the Nether\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
	printf("\n\n\n\n\n");
	printf("						按任意键开始游戏...\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("Alpha 0.8.2(测试版)\n");
	system("pause");
	system("cls");
	int title_page_select;
	printf("您要做什么?([1]进入游戏 [2]进入皮肤商城):[ ]\b\b");
	scanf("%d",&title_page_select);
	if(title_page_select==2){
		skin_shop();
	}
	system("cls");
	printf("存档\n");
	printf("是否重建世界([0]读取存档 [1]重建世界):[ ]\b\b");
	scanf("%d",&is_rebuild);
	if(is_rebuild==1){
		printf("游戏选项\n");
		printf("地图大小(5-20):[  ]\b\b\b");
		scanf("%d",&n);
		n=max(5,n),n=min(20,n);
		printf("作弊([0]否 [1]是):[ ]\b\b");
		scanf("%d",&is_order);
	} else if(is_rebuild==0){
		read_dat();
	}
	printf("游戏规则\n");
	printf("死亡后保留物品栏([0]否 [1]是):[ ]\b\b");
	scanf("%d",&is_save_thing);
	quickTeach();
	system("pause");
	system("cls");
	if(is_rebuild==0&&Biome_Fest>=1&&Biome_Fest<=2){
		game_nether();
		if(nether_return==1){
			return ;
		}
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
		zombieS=n/3;
		skeletonS=2;
		for(int i=1; i<=rand()%n; i++){
			int gx=rand()%(n+1),gy=rand()%(n+1);
			if(gx==0) gx++;
			if(gy==0) gy++;
			a[gx][gy]=8;
		}
		for(int i=1; i<=zombieS; i++) {//生成僵尸  
			zombieX[i]=rand()%(n+1),zombieY[i]=rand()%(n+1);
			if(zombieX[i]==0) zombieX[i]++;
			if(zombieY[i]==0) zombieY[i]++;
			if(zombieX[i]==n-1) zombieX[i]--;
			if(zombieY[i]==n-1) zombieY[i]--;
			a[zombieX[i]][zombieY[i]]=9;
			zombieHp[i]=3;
		}
		for(int i=1; i<=skeletonS; i++){//生成骷髅 
			skeletonX[i]=rand()%(n+1),skeletonY[i]=rand()%(n+1);
			if(skeletonX[i]==0) skeletonX[i]++;
			if(skeletonY[i]==0) skeletonY[i]++;
			if(skeletonX[i]==n-1) skeletonX[i]--;
			if(skeletonY[i]==n-1) skeletonY[i]--;
			a[skeletonX[i]][skeletonY[i]]=14;
		}
		memset(arrowX,0,sizeof(arrowX));
		memset(arrowY,0,sizeof(arrowY));
		x=2,y=2;
		a[x][y]=10;
		a[n-1][n-1]=11;
		system("color 03");
	}
	while(1) {
		hp=20;
		full=20;
		flag=0;
		if((is_rebuild==1)||(is_rebuild==0&&is_first_level==0)){
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
			zombieS=n/3;
			skeletonS=2;
			for(int i=1; i<=rand()%n; i++){
				int gx=rand()%(n+1),gy=rand()%(n+1);
				if(gx==0) gx++;
				if(gy==0) gy++;
				a[gx][gy]=8;
			}
			for(int i=1; i<=zombieS; i++) {//生成僵尸  
				zombieX[i]=rand()%(n+1),zombieY[i]=rand()%(n+1);
				if(zombieX[i]==0) zombieX[i]++;
				if(zombieY[i]==0) zombieY[i]++;
				if(zombieX[i]==n-1) zombieX[i]--;
				if(zombieY[i]==n-1) zombieY[i]--;
				a[zombieX[i]][zombieY[i]]=9;
				zombieHp[i]=3;
			}
			for(int i=1; i<=skeletonS; i++){//生成骷髅 
				skeletonX[i]=rand()%(n+1),skeletonY[i]=rand()%(n+1);
				if(skeletonX[i]==0) skeletonX[i]++;
				if(skeletonY[i]==0) skeletonY[i]++;
				if(skeletonX[i]==n-1) skeletonX[i]--;
				if(skeletonY[i]==n-1) skeletonY[i]--;
				a[skeletonX[i]][skeletonY[i]]=14;
			}
			memset(arrowX,0,sizeof(arrowX));
			memset(arrowY,0,sizeof(arrowY));
			x=2,y=2;
			a[x][y]=10;
			a[n-1][n-1]=11;
		}
		is_first_level=0;
//构建地图 
		while(1) {
			for(int i=1;i<=zombieS;i++) {//及时渲染怪物
				if(zombieHp[i]==3) a[zombieX[i]][zombieY[i]]=9;
				else if(zombieHp[i]==2) a[zombieX[i]][zombieY[i]]=12;
				else if(zombieHp[i]==1) a[zombieX[i]][zombieY[i]]=13;
			}
			for(int i=1;i<=skeletonS;i++){
				if(skeletonHp[i]==3) a[skeletonX[i]][skeletonY[i]]=14;
				else if(skeletonHp[i]==2) a[skeletonX[i]][skeletonY[i]]=15;
				else if(skeletonHp[i]==1) a[skeletonX[i]][skeletonY[i]]=16;
			}
			if(step>0&&step%10==0&&full>0){//更新饱食度
				full--;
			}
			if(full==20){
				hp++;
				hp=min(hp,20);
			}
			if(full==0){
				hp--;
				if(hp<=0){
					died_Information="You starved to death.";
				}
			}
			if(hp<=0){
				if(progress[5]==0){
					progress[5]=1;
					printf("玩家刚刚获得了进度");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
					printf("[哦，不！！！]");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
					printf("!\n");
					Sleep(2000);
					system("cls");
				}
				if(is_save_thing==0){
					memset(sum,0,sizeof(sum));
					money=0;
				}
				hp=20;
				a[x][y]=0;
				system("cls");
				system("color CF");
				printf("\n\n\n\n\n\n\n");
				printf("                                    你死了！\n\n\n");
				printf("   The information of you dies:");
				cout<<died_Information;
				printf("\n\n\n");
				int YN;
				printf("                      [0]退出游戏 [1]重生 [2]返回标题屏幕");
				arrowS=0;
				memset(arrowX,0,sizeof(arrowX));
				memset(arrowY,0,sizeof(arrowY));
				is_act_door=0;
				scanf("%d",&YN);
				if(YN==0) {
					return ;
				}
				if(YN==1) {
					system("color 03");
					break;
				}
				if(YN==2) {
					system("cls");
					game();
					return ;
				}
			}
			if(x==n-1&&y==n-1&&is_act_door==1){
				a[x][y]=0;
				arrowS=0;
				memset(arrowX,0,sizeof(arrowX));
				memset(arrowY,0,sizeof(arrowY));
				is_act_door=0;
				game_nether();
				if(nether_return==1){
					return ;
				}
				system("cls");
				system("color 03");
				break;
			}
			if(x==n-1&&y==n-1) {
				if(progress[4]==0){
					progress[4]=1;
					printf("玩家刚刚获得了进度");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
					printf("[抵达终点]");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
					printf("!\n");
					Sleep(2000);
					system("cls");
				}
				printf("\n\n\n\n\n\n");
				printf("                           666,你到了终点!\n\n\n");
				int YN;
				printf("                      [0]退出 [1]继续 [2]进入商店\n");
				scanf("%d",&YN);
				arrowS=0;
				memset(arrowX,0,sizeof(arrowX));
				memset(arrowY,0,sizeof(arrowY));
				is_act_door=0;
				if(YN==0) {
					return ;
				}
				if(YN==1) {
					x=2,y=2;
					break;
				}
				if(YN==2) {
					shop();
					x=2,y=2;
					break;
				}
			}
			system("cls");
			a[x][y]=10;
			Biome_Fest=0;
			for(int i=1;i<=zombieS;i++){//僵尸移动 
				if(abs(zombieX[i]-x)<3&&abs(zombieY[i]-y)<3&&zombieX[i]!=0&&zombieY[i]!=0){
					int zombieType=a[zombieX[i]][zombieY[i]];
					a[zombieX[i]][zombieY[i]]=0;
					if(x<zombieX[i]&&a[zombieX[i]-1][zombieY[i]]<5) zombieX[i]--;
					else if(x>zombieX[i]&&a[zombieX[i]+1][zombieY[i]]<5) zombieX[i]++;
					else if(y<zombieY[i]&&a[zombieX[i]][zombieY[i]-1]<5) zombieY[i]--;
					else if(y>zombieY[i]&&a[zombieX[i]][zombieY[i]+1]<5) zombieY[i]++;
					a[zombieX[i]][zombieY[i]]=zombieType;
				}
			}
			for(int i=1;i<=skeletonS;i++){//骷髅移动  
				if((skeletonX[i]!=x || skeletonY[i]!=y)&&skeletonX[i]!=0&&skeletonY[i]!=0){
					int skeletonType=a[skeletonX[i]][skeletonY[i]];
					a[skeletonX[i]][skeletonY[i]]=0;
					if(skeletonX[i]>x && a[skeletonX[i]-1][skeletonY[i]]<5) skeletonX[i]--;
					else if(skeletonX[i]<x && a[skeletonX[i]+1][skeletonY[i]]<5) skeletonX[i]++;
					else if(skeletonY[i]>y && a[skeletonX[i]][skeletonY[i]-1]<5) skeletonY[i]--;
					else if(skeletonY[i]<y && a[skeletonX[i]][skeletonY[i]+1]<5) skeletonY[i]++;
					a[skeletonX[i]][skeletonY[i]]=skeletonType;
				}
			}
			for(int i=1;i<=arrowS;i++){//箭矢移动 
				if(arrowX[i]!=0&&arrowY[i]!=0&&a[arrowX[i]+cx[arrowFx[i]]][arrowY[i]+cy[arrowFx[i]]]<5){
					a[arrowX[i]][arrowY[i]]=0;
					arrowX[i]+=cx[arrowFx[i]],arrowY[i]+=cy[arrowFx[i]];
					a[arrowX[i]][arrowY[i]]=17;
				}
				else if(!in(arrowX[i]+cx[arrowFx[i]],arrowY[i]+cy[arrowFx[i]])||a[arrowX[i]+cx[arrowFx[i]]][arrowY[i]+cy[arrowFx[i]]]){
					a[arrowX[i]][arrowY[i]]=0;
					arrowX[i]=0,arrowY[i]=0;
				}
			}
			for(int i=1;i<=skeletonS;i++){//骷髅射箭 
				if(skeletonX[i]==x){
					if(skeletonY[i]<y&&a[skeletonX[i]][skeletonY[i]+1]<5&&abs(skeletonX[i]-x)<3&&abs(skeletonY[i]-y)<3){
						arrowS++;
						arrowX[arrowS]=skeletonX[i],arrowY[arrowS]=skeletonY[i]+1,arrowFx[arrowS]=0;
						a[arrowX[arrowS]][arrowY[arrowS]]=17;
					}
					else if(skeletonY[i]>y&&a[skeletonX[i]][skeletonY[i]-1]<5&&abs(skeletonX[i]-x)<3&&abs(skeletonY[i]-y)<3){
						arrowS++;
						arrowX[arrowS]=skeletonX[i],arrowY[arrowS]=skeletonY[i]-1,arrowFx[arrowS]=2;
						a[arrowX[arrowS]][arrowY[arrowS]]=17;
					}
				}
				else if(skeletonY[i]==y){
					if(skeletonX[i]<x&&a[skeletonX[i]+1][skeletonY[i]]<5&&abs(skeletonX[i]-x)<3&&abs(skeletonY[i]-y)<3){
						arrowS++;
						arrowX[arrowS]=skeletonX[i]+1,arrowY[arrowS]=skeletonY[i],arrowFx[arrowS]=1;
						a[arrowX[arrowS]][arrowY[arrowS]]=17;
					}
					else if(skeletonX[i]>x&&a[skeletonX[i]-1][skeletonY[i]]<5&&abs(skeletonX[i]-x)<3&&abs(skeletonY[i]-y)<3){
						arrowS++;
						arrowX[arrowS]=skeletonX[i]-1,arrowY[arrowS]=skeletonY[i],arrowFx[arrowS]=3;
						a[arrowX[arrowS]][arrowY[arrowS]]=17;
					}
				}
			}
			mp();
			for(int i=1;i<=zombieS;i++){//检测僵尸攻击 
				for(int j=0;j<4;j++){
					int zo_killX=zombieX[i]+cx[j],zo_killY=zombieY[i]+cy[j];
					if(x==zo_killX&&y==zo_killY){
						hp-=2;
						if(hp<=0){
							died_Information="You were killed by the zombie.";
						}
						printf("玩家 被 僵尸%d(chest:zombie %d) 攻击了\n",i,i);
					}
				}
			}
			for(int i=1;i<=skeletonS;i++){//检测骷髅近战攻击
				for(int j=0;j<4;j++){
					int sk_killX=skeletonX[i]+cx[j],sk_killY=skeletonY[i]+cy[j];
					if(x==sk_killX&&y==sk_killY){
						hp-=2;
						if(hp<=0){
							died_Information="You were killed by the skeleton.";
						}
						printf("玩家 被 骷髅%d(chest:skeleton %d) 攻击了\n",i,i);
					}
				}
			}
			for(int i=1;i<=arrowS;i++){//检测箭矢攻击 
				int ar_killX=arrowX[i]+cx[arrowFx[i]],ar_killY=arrowY[i]+cy[arrowFx[i]];
				if(x==ar_killX&&y==ar_killY){
					hp--;
					if(hp<=0){
						died_Information="You were killed by the arrow of the skeleton.";
					}
					printf("玩家 被 箭矢%d(chest:arrow %d) 攻击了\n",i,i);
					a[arrowX[i]][arrowY[i]]=0;
					arrowX[i]=0,arrowY[i]=0;
					if(progress[2]==0){
						progress[2]=1;
						printf("玩家刚刚获得了进度");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
						printf("[远处有个狙击手]");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
						printf("!\n");
						Sleep(2000);
					}
				}
				for(int j=1;j<=zombieS;j++){
					if(a[ar_killX][ar_killY]==9) a[ar_killX][ar_killY]=12,a[arrowX[i]][arrowY[i]]=0,arrowX[i]=0,arrowY[i]=0;
					else if(a[ar_killX][ar_killY]==12) a[ar_killX][ar_killY]=13,a[arrowX[i]][arrowY[i]]=0,arrowX[i]=0,arrowY[i]=0;
					else if(a[ar_killX][ar_killY]==13){
						a[ar_killX][ar_killY]=0,a[arrowX[i]][arrowY[i]]=0,arrowX[i]=0,arrowY[i]=0;
					}
				}
				for(int j=1;j<=skeletonS;j++){
					if(a[ar_killX][ar_killY]==14) a[ar_killX][ar_killY]=15,a[arrowX[i]][arrowY[i]]=0,arrowX[i]=0,arrowY[i]=0;
					else if(a[ar_killX][ar_killY]==15) a[ar_killX][ar_killY]=16,a[arrowX[i]][arrowY[i]]=0,arrowX[i]=0,arrowY[i]=0;
					else if(a[ar_killX][ar_killY]==16){
						a[ar_killX][ar_killY]=0,a[arrowX[i]][arrowY[i]]=0,arrowX[i]=0,arrowY[i]=0;
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
				if(in(goX,goY)&&(a[goX][goY]<5||a[goX][goY]==11||a[goX][goY]==17||a[goX][goY]==18)) {
					a[goX][goY]=10;
					a[x][y]=0;
					x=goX,y=goY;
					step++;
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
					if(progress[3]==0){
						progress[3]=1;
						printf("玩家刚刚获得了进度");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
						printf("[这是什么？箱子！]");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
						printf("!\n");
						Sleep(2000);
					}
				}
			} else if(todo=='t'){
				quickTeach();
				system("pause");
			} else if(todo=='k'){
				for(int i=0;i<4;i++){
					int killX=x+cx[i],killY=y+cy[i];
					if(a[killX][killY]==9){
						a[killX][killY]=12;
						for(int j=1;j<=zombieS;j++){
							if(killX==zombieX[j]&&killY==zombieY[j]){
								zombieHp[j]--;
							}
						}
					}
					else if(a[killX][killY]==12){
						a[killX][killY]=13;
						for(int j=1;j<=zombieS;j++){
							if(killX==zombieX[j]&&killY==zombieY[j]){
								zombieHp[j]--;
							}
						}
					}
					else if(a[killX][killY]==13){
						a[killX][killY]=0;
						for(int j=1;j<=zombieS;j++){
							if(killX==zombieX[j]&&killY==zombieY[j]){
								int getZombieMeat=rand()%5;
								zombieX[j]=0,zombieY[j]=0;
								printf("玩家 击杀了 僵尸 %d,获取 腐肉 * %d\n",j,getZombieMeat);
								sum[11]+=getZombieMeat;
								Sleep(1000);
								if(progress[1]==0){
									progress[1]=1;
									printf("玩家刚刚获得了进度");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
									printf("[小小怪物，轻松拿捏]");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
									printf("!\n");
									Sleep(2000);
								}
								break;
							}
						}
					}
					else if(a[killX][killY]==14){
						for(int j=1;j<=skeletonS;j++){
							if(killX==skeletonX[j]&&killY==skeletonY[j]){
								skeletonHp[j]--;
							}
						}
						a[killX][killY]=15;
					}
					else if(a[killX][killY]==15){
						for(int j=1;j<=skeletonS;j++){
							if(killX==skeletonX[j]&&killY==skeletonY[j]){
								skeletonHp[j]--;
							}
						}
						a[killX][killY]=16;
					}
					else if(a[killX][killY]==16){
						a[killX][killY]=0;
						for(int j=1;j<=skeletonS;j++){
							if(killX==skeletonX[j]&&killY==skeletonY[j]){
								int getBones=rand()%4;
								skeletonX[j]=0,skeletonY[j]=0;
								printf("玩家 击杀了 骷髅 %d,获取 骨头 * %d\n",j,getBones);
								sum[12]+=getBones;
								Sleep(1000);
								if(progress[1]==0){
									progress[1]=1;
									printf("玩家刚刚获得了进度");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0A);
									printf("[小小怪物，轻松拿捏]");
									SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
									printf("!");
									Sleep(2000);
								}
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
					if(order.substr(11,12) == "chest:zombie"){
						if(order[24]>='1'&&order[24]<='6'){
							a[zombieX[order[24]-'0']][zombieY[order[24]-'0']]=0;
							zombieX[order[24]-'0']=0,zombieY[order[24]-'0']=0;
							printf("已杀死 chest:zombie %c\n",order[24]);
							Sleep(1000);
						} else if(order.substr(24,3) == "all"){
							for(int i=1;i<=zombieS;i++){
								a[zombieX[i]][zombieY[i]]=0;
								zombieX[i]=0,zombieY[i]=0;
								printf("已杀死 chest:zombie %d\n",i);
								Sleep(1000);
							}
						}
					} else if(order.substr(11,14) == "chest:skeleton"){
						if(order[26]>='1'&&order[26]<='6'){
							a[skeletonX[order[26]-'0']][skeletonY[order[26]-'0']]=0;
							skeletonX[order[26]-'0']=0,skeletonY[order[26]-'0']=0;
							printf("已杀死 chest:skeleton %c\n",order[26]);
							Sleep(1000);
						} else if(order.substr(26,3) == "all"){
							for(int i=1;i<=skeletonS;i++){
								a[skeletonX[i]][skeletonY[i]]=0;
								skeletonX[i]=0,skeletonY[i]=0;
								printf("已杀死 chest:skeleton %d\n",i);
								Sleep(1000);
							}
						}
					} else if(order.substr(11,12) == "chest:player"){
						hp=0,full=1;
						died_Information="You have been killed.";
					} else if(order.substr(11,3) == "all"){
						for(int i=1;i<=zombieS;i++){
							a[zombieX[i]][zombieY[i]]=0;
							zombieX[i]=0,zombieY[i]=0;
							printf("已杀死 chest:zombie %d\n",i);
							Sleep(1000);
						}
						for(int i=1;i<=skeletonS;i++){
							a[skeletonX[i]][skeletonY[i]]=0;
							skeletonX[i]=0,skeletonY[i]=0;
							printf("已杀死 chest:skeleton %d\n",i);
							Sleep(1000);
						}
						hp=0,full=1;
						died_Information="You have been killed.";
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
				} else if(order.substr(0,4)=="help"){
					printf(" ╔═════════════════════════════════════════════════════════════════════════════╗ \n");
					printf(" ║ 指令的使用(先在'游戏选项-作弊'中输入1)                                      ║ \n");
					printf(" ║   (1)/kill [type=<entity name>] 杀死某种实体                                ║ \n");
					printf(" ║     可用实体名称:                                                           ║ \n");
					printf(" ║     1.chest:zombie                                                          ║ \n");
					printf(" ║     2.chest:skeleton                                                        ║ \n");
					printf(" ║     3.chest:player                                                          ║ \n");
					printf(" ║     4.chest:lava_zombie                                                     ║ \n");
					printf(" ║     5.chest:burn_skeleton                                                   ║ \n");
					printf(" ║     6.all                                                                   ║ \n");
					printf(" ║   (2)/tp <x> <y> 将玩家传送到(行,列)                                        ║ \n");
					printf(" ║   (3)/beta_set <Beta Name> <beta> 修改游戏数据                              ║ \n");
					printf(" ║     数据名称:                                                               ║ \n");
					printf(" ║     1.a[x][y]                                                               ║ \n");
					printf(" ║     2.nether[x][y]                                                          ║ \n");
					printf(" ║     3.x                                                                     ║ \n");
					printf(" ║     4.y                                                                     ║ \n");
					printf(" ║     5.money                                                                 ║ \n");
					printf(" ║     6.hp                                                                    ║ \n");
					printf(" ║     7.full                                                                  ║ \n");
					printf(" ║     8.sum[i]                                                                ║ \n");
					printf(" ╚═════════════════════════════════════════════════════════════════════════════╝ \n");
					system("pause");
				} else if(order.substr(0,4)=="eggs"&&money>=100000){
					system("start https://www.bilibili.com/video/BV1GJ411x7h7/?spm_id_from=333.337.search-card.all.click");
					hp=0,full=1;
					died_Information="You have been tricked.That's fun!Haha!";
				} else{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
					printf("指令无效!\n");
					Sleep(1000);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
				}
			} else if(todo=='/'&&is_order==0){
				string order;
				printf("/");
				getline(cin,order);
				if(order.substr(0,4)=="eggs"&&money>=100000){
					system("start https://www.bilibili.com/video/BV1GJ411x7h7/?spm_id_from=333.337.search-card.all.click");
					hp=0,full=1;
					died_Information="You have been tricked.That's fun!Haha!";
				} else{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0C);
					printf("你没有作弊的权限!\n");
					Sleep(1000);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x03);
				}
			} else if(todo=='1'){
				is_debug=!is_debug;
			} else if(todo=='p'){
				seeProgress();
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
	write_dat();
	return 0;
}
