#include "stdafx.h"
#include "Draw.h"

/*
	此文件：
		1. 定义图像绘制的函数
*/

HANDLE g_hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);    //获取标准输出句柄

void writeChar(int row, int col, const char* pszChar, WORD wArr)
{
	// 设置光标属性
	CONSOLE_CURSOR_INFO cci;                    //控制台光标信息结构类型
	cci.dwSize = 1;                             //光标大小
	cci.bVisible = FALSE;                       //是否显示光标
	COORD loc;                                  //坐标结构类型
	loc.X = col * 2;                            //宽度必须*2
	loc.Y = row;                                //高度
	SetConsoleCursorInfo(g_hStdOut, &cci);      //设置指定控制台屏幕缓冲区光标大小和可见性
	SetConsoleCursorPosition(g_hStdOut, loc);   //设置指定控制台屏幕缓冲区中光标的位置
	SetConsoleTextAttribute(g_hStdOut, wArr);   //设置颜色
												//函数对函数调用后输出的文本产生影响
	printf(pszChar);                            //打印特殊字符占两个字节
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
			int y = tank.posY + row; //行坐标
			int x = tank.posX + col; //列坐标
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
			int y = tank.posY + row; //行坐标
			int x = tank.posX + col; //列坐标

			int style = tank.style;
			int orientation = tank.orientation;
			char * pic = tank_pic[tank_style[style][orientation][i][j]];
			writeChar(y, x, pic, tank.color);
			
			//草地的显示等级比坦克高（地图元素封装成类后，可以直接查看其显示等级）
			if (g_sysMap01[y][x] == WALL_E) //草地
			{
				DrawMapCell(y, x, WALL_E, wall_color[WALL_E]| tank.color);
			}

			g_sysMap00[y][x] = tank.tankID;
		}
	}
	//血量
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
	int y = missile.posY; //行坐标
	int x = missile.posX; //列坐标

	if (g_sysMap00[y][x] == missile.tankID) //坦克
	{
		return true;
	}
	DrawMapCell(y, x, g_sysMap01[y][x], 0);

	return 0;
}

int DrawMissile(MISSILE missile)
{
	int y = missile.posY ; //行坐标
	int x = missile.posX ; //列坐标

	if (g_sysMap00[y][x] == missile.tankID) //坦克
	{
		return true;
	}

	int orientation = missile.orientation;
	char * pic = missile_pic[missile.level];
	writeChar(y, x, pic, F_H_WHITE);

	//草地的显示等级比坦克高（地图元素封装成类后，可以直接查看其显示等级）
	if (g_sysMap01[y][x] == WALL_E) //草地
	{
		DrawMapCell(y, x, WALL_E, wall_color[WALL_E] | F_H_WHITE);
	}
	if (g_sysMap01[y][x] == WALL_D) //河流
	{
		writeChar(y, x, pic,  wall_color[WALL_D] | F_H_WHITE);
	}
	
	return true;
}
