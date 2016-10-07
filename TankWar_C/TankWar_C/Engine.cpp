#include "stdafx.h"
#include "Engine.h"
#include <conio.h>
#include <time.h>

/*
	���ļ���
		1. ʵ����Ϸ�������߼�
*/

int setWindowSize(int width, int high)
{
	width = width * 2;  //�ѿ��ַ����꣬��Ϊխ�ַ�����

	//1. ��ȡ������̨���ڴ�С
	COORD pos = GetLargestConsoleWindowSize(g_hStdOut);
	if (pos.Y <= high || pos.X <= width)
	{
		printf( "�����õĴ���̫���ˣ�װ���£� \n"); 
		printf( "�����ý�С��������¿�ʼ~ \n");
		return false;
	}
	COORD bufferSize = { pos.X,pos.Y };  //��󻺳�ȡ��С
	pos.X -= 1;	pos.Y -= 1;              //��󴰿ڴ�С

	//2. ���û�������С(������Ϊ����Ա����ô���)
	if (!SetConsoleScreenBufferSize(g_hStdOut, bufferSize)) {
		printf("���û�������Сʧ�� \n");
		return false;
	}

	//3. ȷ�����ڵ����մ�С
	width = width > pos.X ? pos.X : width;
	high = high > pos.Y ? pos.Y : high;

	//4. ���ô��ڴ�С
	SMALL_RECT windowSize = { 0,0,(short)width ,(short)high };
	if (!SetConsoleWindowInfo(g_hStdOut, true, &windowSize)) {
		printf("���ô��ڴ�Сʧ�� \n");
		return false;
	}
	//5. ���û�������С
	bufferSize = { (short)width + 1,(short)high + 1 };
	if (!SetConsoleScreenBufferSize(g_hStdOut, bufferSize)) {
		printf("���û�������Сʧ�� \n");
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
		
		//�����ͣ����
		writeChar(row + 0, col, "=========================", F_RED | B_WHITE);
		writeChar(row + 1, col, "                         ", F_RED | B_WHITE);
		writeChar(row + 2, col, "     ��  Ϸ   ��  ͣ     ", F_RED | B_WHITE);
		writeChar(row + 3, col, "                         ", F_RED | B_WHITE);
		writeChar(row + 4, col, "=========================", F_RED | B_WHITE);

		writeChar(row + 5, col, "-----��  ��   ��  ��-----", F_RED | B_GREEN);
			
		char key = _getch();
		if (key == VK_RETURN )
		{
			bPause = false;
			
			//���ԭ��Ϸ���棨�������ͼ�������̹�˺��ӵ���
			DrawMap(g_sysMap01);
			DrawTank(g_Player_Tanks[0]);
			DrawTank(g_Player_Tanks[1]);

			for (int i = 0; i < 100; i++)            //�о�̹��
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
		//1.����ϳ�
		//2.����Ҿ�
		//3.���о�
	}
	return bOver;
}

bool hitTank(int srcTankID,int desTankID)
{
	//�����ҷ�̹�ˣ�ֱ�Ӽ�Ѫ�˳�
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
			return true;  //�����ҷ�̹�ˣ�ֱ�Ӽ�Ѫ�˳�
		}
	}
	//�з�̹�˻�����в���Ѫ
	for (int i = 0; i < 100; i++)
	{
		if (g_NPC_Tanks[i].tankID == srcTankID)
		{
			return true;
		}
	}
	//��һ��вŵ�Ѫ�������ӵ÷�
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
			break;  //���ео�̹�ˣ����˳�������Ҫˢ����ҵ÷�
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
	//1.����ɹ켣
	//2.�ı��ӵ�λ��
	//3.�����¹켣
	
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
	//���ӵ���������һ�����ʵ�λ�ã�����һ���ӵ�
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

	//1.����ɹ켣
	//2.�ı�̹��λ��
	//3.�����¹켣
		
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
	//��ͣ
	if (KEY_DOWN(VK_SPACE)) { bPause = true; }

	clock_t ctrl_fast_clockFinish = clock();
	if (ctrl_fast_clockFinish - ctrl_fast_clockStart < 80) {		return false;	}
	ctrl_fast_clockStart = ctrl_fast_clockFinish;

	//����
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

	for (int i = 0; i < 100; i++)            //�о�̹��
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
	
	//1.��ʼ������              
	int playCount = 2;                 //ѡ��Ϸ����
	g_sysMap01;                        //ѡ��Ϸ��ͼ
	
	g_Player_Tanks[0].isValid = true;  //�Ҿ�̹��
	if (playCount==2)
	{
		g_Player_Tanks[1].isValid = true;
	}
	static int NPC_ID = 0x100;
	for (int i = 0;i<3;i++)            //�о�̹��
	{
		g_NPC_Tanks[i] = { NPC_ID+i,10*(i+1),2,DOWN,3,2,0,true,F_H_GREEN };
	}

	//2.��ӡ��ͼ��̹��
	DrawMap(g_sysMap01);
	DrawTank(g_Player_Tanks[0]);
	if (playCount == 2)
	{
		DrawTank(g_Player_Tanks[1]);
	}
	for (int i = 0; i < 3; i++)            //�о�̹��
	{
		DrawTank(g_NPC_Tanks[i]);
	}
	//3.��ѭ���������Ϸ����������¼���
	while (1)
	{
		/*
		4.0		�����Ϸ�Ƿ���ͣ      isPause();
		4.1		�����Ϸ�Ƿ����      isOver();
		4.2		��Ӧ��Ҳ���          playCtrl();
		4.3		�ƶ������ӵ�          moveAllMissiles();
		4.4		�ƶ����ео�̹��      moveAllNPCTanks();
		4.5		ˢ�¼Ʒ���            drawBoardView();
		4.6		�����о�̹��          reSetPlayer();
		4.7		�����ҷ�̹��          reSetNPC();
		*/
		//4.0	�����Ϸ�Ƿ���ͣ
		isPause();

		//4.1	�����Ϸ�Ƿ����
		//isOver();

		//4.2	��Ӧ��Ҳ���
		playCtrl(playCount);

		//4.3	�ƶ������ӵ�
		moveAllMissiles();

		//4.4	�ƶ����ео�̹��
		moveAllNPCTanks();

		//4.5	ˢ�¼Ʒ���
		//drawBoardView();

		//4.6	�����о�̹��
		//reSetPlayer();

		//4.7	�����ҷ�̹��
		//reSetNPC();

	}
	return 1;
}
int mainMenu()
{
	int row = (WINDOWS_HIGH - 5) / 2;
	int col = (WINDOWS_WIDTH -strlen("(1)  ��    ʼ    ��    Ϸ")/2) / 2;
	writeChar(row + 0, col, "(1)  ��    ʼ    ��    Ϸ", F_RED | B_WHITE);
	writeChar(row + 1, col, "(2)  ��    ͼ    ��    ��", F_RED | B_WHITE);
	writeChar(row + 2, col, "(3)  ��    ȡ    ��    ��", F_RED | B_WHITE);
	writeChar(row + 3, col, "(4)  ��    Ϸ    ��    ��", F_RED | B_WHITE);
	writeChar(row + 4, col, "(5)  ��    ��    ��    Ϸ", F_RED | B_WHITE);

	writeChar(row + 5, col, "-------������ѡ��--------", F_RED | B_GREEN);
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
		writeChar(row + 5, col, "--����ѡ������������ѡ--", F_RED | B_YELLOW);
		writeChar(row + 6, col, "                        ", 0);
		writeChar(row + 6, col, ">> ", F_RED | B_WHITE);
		}
	}
	
}
int run()
{
	

	while (true)
	{
		//���ݵ�ǰ���ڽ��棬���ö�Ӧ�Ľ�����
		int doWhat = mainMenu();

		switch (doWhat)
		{
		
		case GameDlg:  //��Ϸ���н���   //      ��
		{							    //    ������
			gameRun();				    //    ��  ��
		}   break;
		case EditDlg:  //�༭��ͼ����
		{
		}   break;
		case HelpDlg:  //��Ϸ��������
		{
		}	break;
		case ExitDlg:  //�˳���Ϸ����
		{
		}	break;
		}
	}
}