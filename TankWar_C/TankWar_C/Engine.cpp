#include "stdafx.h"
#include "Engine.h"
#include <conio.h>
#include <time.h>

/*
	此文件：
		1. 实现游戏的所有逻辑
*/

int setWindowSize(int width, int high)
{
	width = width * 2;  //把宽字符坐标，变为窄字符坐标

	//1. 获取最大控制台窗口大小
	COORD pos = GetLargestConsoleWindowSize(g_hStdOut);
	if (pos.Y <= high || pos.X <= width)
	{
		printf( "你设置的窗口太大了，装不下！ \n"); 
		printf( "请设置较小字体后，重新开始~ \n");
		return false;
	}
	COORD bufferSize = { pos.X,pos.Y };  //最大缓冲取大小
	pos.X -= 1;	pos.Y -= 1;              //最大窗口大小

	//2. 设置缓冲区大小(先设置为最大，以便设置窗口)
	if (!SetConsoleScreenBufferSize(g_hStdOut, bufferSize)) {
		printf("设置缓冲区大小失败 \n");
		return false;
	}

	//3. 确定窗口的最终大小
	width = width > pos.X ? pos.X : width;
	high = high > pos.Y ? pos.Y : high;

	//4. 设置窗口大小
	SMALL_RECT windowSize = { 0,0,(short)width ,(short)high };
	if (!SetConsoleWindowInfo(g_hStdOut, true, &windowSize)) {
		printf("设置窗口大小失败 \n");
		return false;
	}
	//5. 设置缓冲区大小
	bufferSize = { (short)width + 1,(short)high + 1 };
	if (!SetConsoleScreenBufferSize(g_hStdOut, bufferSize)) {
		printf("设置缓冲区大小失败 \n");
		return false;
	}

	return true;
}
int setAppName(char * name)
{
	return SetConsoleTitleA(name);
}
int init(char * name, int width, int high)
{
	setAppName(name);
	setWindowSize(width, high);
	return 0;
}



bool bPause = false;
bool isPause() {
	while (bPause)
	{
		int row = (WINDOWS_HIGH - 5) / 2;
		int col = (WINDOWS_WIDTH - strlen("=========================") / 2) / 2;
		
		//输出暂停界面
		writeChar(row + 0, col, "=========================", F_RED | B_WHITE);
		writeChar(row + 1, col, "                         ", F_RED | B_WHITE);
		writeChar(row + 2, col, "     游  戏   暂  停     ", F_RED | B_WHITE);
		writeChar(row + 3, col, "                         ", F_RED | B_WHITE);
		writeChar(row + 4, col, "=========================", F_RED | B_WHITE);

		writeChar(row + 5, col, "-----回  车   继  续-----", F_RED | B_GREEN);
			
		char key = _getch();
		if (key == VK_RETURN )
		{
			bPause = false;
			
			//输出原游戏界面（先输出地图，再输出坦克和子弹）
			DrawMap(g_sysMap01);
			DrawTank(g_Player_Tanks[0]);
			DrawTank(g_Player_Tanks[1]);

			for (int i = 0; i < 100; i++)            //敌军坦克
			{
				if (g_NPC_Tanks[i].isValid)
				{
					DrawTank(g_NPC_Tanks[i]);
				}
			}
			
		}
	}
	return bPause;
}
bool bOver = false;
bool isOver() {
	if (bOver)
	{
		//1.检查老巢
		//2.检查我军
		//3.检查敌军
	}
	return bOver;
}

bool hitTank(int srcTankID,int desTankID)
{
	//击中我方坦克，直接减血退出
	for (int i = 0;i<2;i++)
	{
		if (g_Player_Tanks[i].tankID == desTankID)
		{
			if (g_Player_Tanks[i].blood > 0)
			{
				g_Player_Tanks[i].blood--;
				DrawTank(g_Player_Tanks[i]);
			}else {
				g_Player_Tanks[i].isValid = false;
				ClsTank(g_Player_Tanks[i]);
			}
			return true;  //击中我方坦克，直接减血退出
		}
	}
	//敌方坦克互相击中不掉血
	for (int i = 0; i < 100; i++)
	{
		if (g_NPC_Tanks[i].tankID == srcTankID)
		{
			return true;
		}
	}
	//玩家击中才掉血，并增加得分
	for (int i = 0; i < 100; i++)
	{
		if (g_NPC_Tanks[i].tankID == desTankID)
		{
			if (g_NPC_Tanks[i].blood > 0)
			{
				g_NPC_Tanks[i].blood--;
				DrawTank(g_NPC_Tanks[i]);
			}
			else {
				g_NPC_Tanks[i].isValid = false;
				ClsTank(g_NPC_Tanks[i]);
			}
			break;  //击中敌军坦克，不退出，还需要刷新玩家得分
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (g_Player_Tanks[i].tankID == srcTankID)
		{
			g_player_Info[i].score += 3;
			return true; 
		}
	}
	return true;
}
bool hitWall(int row,int col)
{
	int wallType = g_sysMap01[row][col];
	
	switch (wallType)
	{
	case WALL_A:
		g_sysMap01[row][col] = WALL_B;
		writeChar(row, col, wall_pic[WALL_B], wall_color[WALL_B]); break;
	case WALL_B:
		g_sysMap01[row][col] = WALL__; 
		writeChar(row, col, wall_pic[WALL__], wall_color[WALL__]); break;
	case WALL_G:
		g_sysMap01[row][col] = WALL__;
		writeChar(row, col, wall_pic[WALL__], wall_color[WALL__]); break;
	case WALL_H:
		bOver = true;
		break;
	}
	return true;
}

bool checkMissile(MISSILE missile)
{
	int y = missile.posY;
	int x = missile.posX;
	if (g_sysMap01[y][x] != WALL__ &&
		g_sysMap01[y][x] != WALL_D &&
		g_sysMap01[y][x] != WALL_E)
	{
		hitWall(y, x);
		return false;
	}else if (g_sysMap00[y][x]!=0&&
				g_sysMap00[y][x] < 0x10000 && 
				g_sysMap00[y][x] != missile.tankID)
	{
		hitTank(missile.tankID,g_sysMap00[y][x]);
		return false;
	}
	return true;
}
void moveMissile(PMISSILE pMissile)
{
	//1.清除旧轨迹
	//2.改变子弹位置
	//3.画出新轨迹
	
	MISSILE temp = *pMissile;
	
	switch (temp.orientation)
	{
	case UP:    temp.posY--; break;
	case DOWN:  temp.posY++; break;
	case LEFT:  temp.posX--; break;
	case RIGHT: temp.posX++; break;
	}

	if (checkMissile(temp))
	{
		ClsMissile(*pMissile);
		*pMissile = temp;
		DrawMissile(*pMissile);
	}else{

		ClsMissile(*pMissile);
		pMissile->isValid = false;

	}
}
bool fireTank(PTANK pTank) {
	static int missileID = 0x10000;
	//到子弹数组中找一个合适的位置，生成一颗子弹
	for (int i = 0;i<300;i++)
	{
		if (g_Missile[i].isValid == false)
		{
 			g_Missile[i].missileID = missileID++;
			g_Missile[i].posX = pTank->posX;
			g_Missile[i].posY = pTank->posY;
			g_Missile[i].orientation = pTank->orientation;
			g_Missile[i].level = pTank->level;
			g_Missile[i].style = pTank->style;
			g_Missile[i].isValid = pTank->isValid;

			g_Missile[i].tankID = pTank->tankID;

			return true;
		}
	}
	return false;
}
bool checkTank(TANK tank) {

	for (int row = -1;row<2;row++)
	{
		for (int col = -1;col<2;col++)
		{
			int y = row + tank.posY;
			int x = col + tank.posX;
			if (g_sysMap01[y][x] != WALL__ &&
				g_sysMap01[y][x] != WALL_E)
			{
				return false;
			}
			if (g_sysMap00[y][x] !=0 &&
				g_sysMap00[y][x] != tank.tankID)
			{
				return false;
			}
		}
	}
	return true;
}
void moveTank(PTANK pTank, int orientation) {

	//1.清除旧轨迹
	//2.改变坦克位置
	//3.画出新轨迹
		
	TANK temp = *pTank;

	if (orientation!= temp.orientation)
	{
		temp.orientation = orientation;
	}else{
		switch (orientation)
		{
		case UP:    temp.posY--; break;
		case DOWN:  temp.posY++; break;
		case LEFT:  temp.posX--; break;
		case RIGHT: temp.posX++; break;
		}
	}
	if (checkTank(temp))
	{
		ClsTank(*pTank);
		*pTank = temp;
		DrawTank(*pTank);
	}
}
static clock_t ctrl_fast_clockStart = clock();
static clock_t ctrl_slow_clockStart = clock();
bool playCtrl(int playCount)
{
	//暂停
	if (KEY_DOWN(VK_SPACE)) { bPause = true; }

	clock_t ctrl_fast_clockFinish = clock();
	if (ctrl_fast_clockFinish - ctrl_fast_clockStart < 80) {		return false;	}
	ctrl_fast_clockStart = ctrl_fast_clockFinish;

	//操作
	if (g_Player_Tanks[0].isValid)
	{
		if (KEY_DOWN('W')) { moveTank(&g_Player_Tanks[0], UP); }
		if (KEY_DOWN('S')) { moveTank(&g_Player_Tanks[0], DOWN); }
		if (KEY_DOWN('A')) { moveTank(&g_Player_Tanks[0], LEFT); }
		if (KEY_DOWN('D')) { moveTank(&g_Player_Tanks[0], RIGHT); }
	}
	
	if (playCount==2 && g_Player_Tanks[1].isValid)
	{
		if (KEY_DOWN(VK_UP))    { moveTank(&g_Player_Tanks[1], UP);    }
		if (KEY_DOWN(VK_DOWN))  { moveTank(&g_Player_Tanks[1], DOWN);  }
		if (KEY_DOWN(VK_LEFT))  { moveTank(&g_Player_Tanks[1], LEFT);  }
		if (KEY_DOWN(VK_RIGHT)) { moveTank(&g_Player_Tanks[1], RIGHT); }
	}

	clock_t ctrl_slow_clockFinish = clock();
	if (ctrl_slow_clockFinish - ctrl_slow_clockStart <100) { return false; }
	ctrl_slow_clockStart = ctrl_slow_clockFinish;

	if (KEY_DOWN('F')) { fireTank(&g_Player_Tanks[0]); }
	if (playCount)
	{
		if (KEY_DOWN('M')) { fireTank(&g_Player_Tanks[1]); }
	}
	return 0;
}
static clock_t missiles_clockStart = clock();
bool moveAllMissiles()
{
	clock_t missiles_clockFinish = clock();
	if (missiles_clockFinish - missiles_clockStart < 50) { return false; }
	missiles_clockStart = missiles_clockFinish;

	for (int i = 0; i < 300; i++)
	{
		if (g_Missile[i].isValid == true)
		{
 			moveMissile(&g_Missile[i]);
		}
	}
	return false;
}
static clock_t NPC_clockStart = clock();
bool moveAllNPCTanks() 
{
	clock_t NPC_clockFinish = clock();
	if (NPC_clockFinish - NPC_clockStart < 100) { return false; }
	NPC_clockStart = NPC_clockFinish;

	for (int i = 0; i < 100; i++)            //敌军坦克
	{
		if (g_NPC_Tanks[i].isValid)
		{
			int oper = rand()%20;

			switch (oper)
			{
			case UP:    moveTank(&g_NPC_Tanks[i], UP);   break;
			case DOWN:  moveTank(&g_NPC_Tanks[i], DOWN);   break;
			case LEFT:	moveTank(&g_NPC_Tanks[i], LEFT);   break;
			case RIGHT:	moveTank(&g_NPC_Tanks[i], RIGHT);   break;
			case 5:     fireTank(&g_NPC_Tanks[i]);   break;
			default:
				moveTank(&g_NPC_Tanks[i], g_NPC_Tanks[i].orientation);
			}
		}
	}
	return true;
}
bool drawBoardView();
bool reSetPlayer();
bool reSetNPC();

int gameRun() {

	srand((unsigned)time(nullptr));
	
	//1.初始化数据              
	int playCount = 2;                 //选游戏人数
	g_sysMap01;                        //选游戏地图
	
	g_Player_Tanks[0].isValid = true;  //我军坦克
	if (playCount==2)
	{
		g_Player_Tanks[1].isValid = true;
	}
	static int NPC_ID = 0x100;
	for (int i = 0;i<3;i++)            //敌军坦克
	{
		g_NPC_Tanks[i] = { NPC_ID+i,10*(i+1),2,DOWN,3,2,0,true,F_H_GREEN };
	}

	//2.打印地图与坦克
	DrawMap(g_sysMap01);
	DrawTank(g_Player_Tanks[0]);
	if (playCount == 2)
	{
		DrawTank(g_Player_Tanks[1]);
	}
	for (int i = 0; i < 3; i++)            //敌军坦克
	{
		DrawTank(g_NPC_Tanks[i]);
	}
	//3.大循环（完成游戏里面的所有事件）
	while (1)
	{
		/*
		4.0		检查游戏是否暂停      isPause();
		4.1		检查游戏是否结束      isOver();
		4.2		响应玩家操作          playCtrl();
		4.3		移动所有子弹          moveAllMissiles();
		4.4		移动所有敌军坦克      moveAllNPCTanks();
		4.5		刷新计分牌            drawBoardView();
		4.6		重生敌军坦克          reSetPlayer();
		4.7		重生我方坦克          reSetNPC();
		*/
		//4.0	检查游戏是否暂停
		isPause();

		//4.1	检查游戏是否结束
		//isOver();

		//4.2	响应玩家操作
		playCtrl(playCount);

		//4.3	移动所有子弹
		moveAllMissiles();

		//4.4	移动所有敌军坦克
		moveAllNPCTanks();

		//4.5	刷新计分牌
		//drawBoardView();

		//4.6	重生敌军坦克
		//reSetPlayer();

		//4.7	重生我方坦克
		//reSetNPC();

	}
	return 1;
}
int mainMenu()
{
	int row = (WINDOWS_HIGH - 5) / 2;
	int col = (WINDOWS_WIDTH -strlen("(1)  开    始    游    戏")/2) / 2;
	writeChar(row + 0, col, "(1)  开    始    游    戏", F_RED | B_WHITE);
	writeChar(row + 1, col, "(2)  地    图    编    辑", F_RED | B_WHITE);
	writeChar(row + 2, col, "(3)  读    取    存    档", F_RED | B_WHITE);
	writeChar(row + 3, col, "(4)  游    戏    帮    助", F_RED | B_WHITE);
	writeChar(row + 4, col, "(5)  退    出    游    戏", F_RED | B_WHITE);

	writeChar(row + 5, col, "-------请输入选项--------", F_RED | B_GREEN);
	writeChar(row + 6, col, ">> ", F_RED | B_WHITE);
	
	int index = 0;
	while (true)
	{

		scanf_s("%d", &index);
		if (index>=1 && index<=5)
		{
			cls();
			return index;
		}else{
		writeChar(row + 5, col, "--错误选项请重新输入选--", F_RED | B_YELLOW);
		writeChar(row + 6, col, "                        ", 0);
		writeChar(row + 6, col, ">> ", F_RED | B_WHITE);
		}
	}
	
}
int run()
{
	

	while (true)
	{
		//根据当前窗口界面，调用对应的界面类
		int doWhat = mainMenu();

		switch (doWhat)
		{
		
		case GameDlg:  //游戏运行界面   //      ■
		{							    //    ■□■
			gameRun();				    //    ■  ■
		}   break;
		case EditDlg:  //编辑地图界面
		{
		}   break;
		case HelpDlg:  //游戏帮助界面
		{
		}	break;
		case ExitDlg:  //退出游戏界面
		{
		}	break;
		}
	}
}