#include "stdafx.h"
#include "Draw.h"

/*
	���ļ���
		1. ����ͼ����Ƶĺ���
*/

HANDLE g_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);    //��ȡ��׼������

void writeChar(int row, int col, const char* pszChar, WORD wArr)
{
	// ���ù������
	CONSOLE_CURSOR_INFO cci;                    //����̨�����Ϣ�ṹ����
	cci.dwSize = 1;                             //����С
	cci.bVisible = FALSE;                       //�Ƿ���ʾ���
	COORD loc;                                  //����ṹ����
	loc.X = col * 2;                            //��ȱ���*2
	loc.Y = row;                                //�߶�
	SetConsoleCursorInfo(g_hStdOut, &cci);      //����ָ������̨��Ļ����������С�Ϳɼ���
	SetConsoleCursorPosition(g_hStdOut, loc);   //����ָ������̨��Ļ�������й���λ��
	SetConsoleTextAttribute(g_hStdOut, wArr);   //������ɫ
												//�����Ժ������ú�������ı�����Ӱ��
	printf(pszChar);                            //��ӡ�����ַ�ռ�����ֽ�
}

void cls()
{
	writeChar(0, 0, " ", 0);
	system("cls");
}

void DrawMapCell(int row, int col, int wallType, int color)
{
	if (color==0)
	{
		color = wall_color[wallType];
	}
	switch (wallType)
	{
	case WALL__:writeChar(row, col, wall_pic[WALL__], color); break;
	case WALL_A:writeChar(row, col, wall_pic[WALL_A], color); break;
	case WALL_B:writeChar(row, col, wall_pic[WALL_B], color); break;
	case WALL_C:writeChar(row, col, wall_pic[WALL_C], color); break;
	case WALL_D:writeChar(row, col, wall_pic[WALL_D], color); break;
	case WALL_E:writeChar(row, col, wall_pic[WALL_E], color); break;
	case WALL_G:writeChar(row, col, wall_pic[WALL_G], color); break;
	}
}
int DrawMap(int map[MAP_HIGH][MAP_WIDTH])
{
	for (int row = 0; row<MAP_HIGH;row++)
	{
		for (int col = 0;col<MAP_WIDTH;col++)
		{
			DrawMapCell(row,col, map[row][col],0);
		}
	}
	return 0;
}

int ClsTank(TANK tank)
{
	for (int row = -1;row<2;row++)
	{
		for (int col = -1;col<2;col++)
		{
			int y = tank.posY + row; //������
			int x = tank.posX + col; //������
			DrawMapCell(y, x, g_sysMap01[y][x], 0);

			g_sysMap00[y][x] = 0;
		}
	}
	return 0;
}

int DrawTank(TANK tank)
{
	for (int row = -1, i = 0; row <= 1; row++, i++)
	{
		for (int col = -1, j = 0; col <= 1; col++, j++)
		{
			int y = tank.posY + row; //������
			int x = tank.posX + col; //������

			int style = tank.style;
			int orientation = tank.orientation;
			char * pic = tank_pic[tank_style[style][orientation][i][j]];
			writeChar(y, x, pic, tank.color);
			
			//�ݵص���ʾ�ȼ���̹�˸ߣ���ͼԪ�ط�װ����󣬿���ֱ�Ӳ鿴����ʾ�ȼ���
			if (g_sysMap01[y][x] == WALL_E) //�ݵ�
			{
				DrawMapCell(y, x, WALL_E, wall_color[WALL_E]| tank.color);
			}

			g_sysMap00[y][x] = tank.tankID;
		}
	}
	//Ѫ��
	switch (tank.orientation)
	{
	case UP:    tank.posY++; break;
	case DOWN:  tank.posY--; break;
	case LEFT:  tank.posX++; break;
	case RIGHT: tank.posX--; break;
	}
	writeChar(tank.posY, tank.posX, blood_pic[tank.blood], tank.color);
	return 0;
}

int ClsMissile(MISSILE missile)
{
	int y = missile.posY; //������
	int x = missile.posX; //������

	if (g_sysMap00[y][x] == missile.tankID) //̹��
	{
		return true;
	}
	DrawMapCell(y, x, g_sysMap01[y][x], 0);

	return 0;
}

int DrawMissile(MISSILE missile)
{
	int y = missile.posY ; //������
	int x = missile.posX ; //������

	if (g_sysMap00[y][x] == missile.tankID) //̹��
	{
		return true;
	}

	int orientation = missile.orientation;
	char * pic = missile_pic[missile.level];
	writeChar(y, x, pic, F_H_WHITE);

	//�ݵص���ʾ�ȼ���̹�˸ߣ���ͼԪ�ط�װ����󣬿���ֱ�Ӳ鿴����ʾ�ȼ���
	if (g_sysMap01[y][x] == WALL_E) //�ݵ�
	{
		DrawMapCell(y, x, WALL_E, wall_color[WALL_E] | F_H_WHITE);
	}
	if (g_sysMap01[y][x] == WALL_D) //����
	{
		writeChar(y, x, pic,  wall_color[WALL_D] | F_H_WHITE);
	}
	
	return true;
}
