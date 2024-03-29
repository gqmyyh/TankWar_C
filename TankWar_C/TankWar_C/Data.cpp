#include "stdafx.h"
#include "Data.h"

/*
	此文件：
		1. 定义全局变量
*/
//墙体图片以及颜色数组
char * wall_pic[] =   { "  ","▓","卍","〓","≈","≡","☆","§" };
int  wall_color[] =   { 0,B_H_RED,B_RED,B_H_WHITE,B_H_BLUE,B_H_GREEN,B_H_YELLOW };
char * tank_pic[] =   { "  ","■","□","◇","○" };
char * blood_pic[]=   { "  ","①","②","③","④","⑤","⑥","⑦","⑧","⑨" };
char * missile_pic[] = { "  ","○", "●", "¤", "◇", "◎", "↑", "↓", "←", "→", };
int tank_style[][4][3][3] ={
								{/*****样式一坦克*******/
									 //四个方向的造型						
									{//向上
										{ 0,1,0 },
										{ 1,4,1 },
										{ 1,0,1 }
									},
									{//向下
										{ 1,0,1 },
										{ 1,4,1 },
										{ 0,1,0 }
									},
									{//向左
										{ 0,1,1 },
										{ 1,4,0 },
										{ 0,1,1 }
									},
									{//向右
										{ 1,1,0 },
										{ 0,4,1 },
										{ 1,1,0 }
									}
								},
								{/*****样式二坦克*******/
									//四个方向的造型						
									{//向上
										{ 0,2,0 },
										{ 2,4,2 },
										{ 2,0,2 }
									},
									{//向下
										{ 2,0,2 },
										{ 2,4,2 },
										{ 0,2,0 }
									},
									{//向左
										{ 0,2,2 },
										{ 2,4,0 },
										{ 0,2,2 }
									},
									{//向右
										{ 2,2,0 },
										{ 0,4,2 },
										{ 2,2,0 }
									}
								}
							};

//定义玩家信息
PLAYERINFO g_player_Info[2] = {0};

//定义我军坦克数组
TANK g_Player_Tanks[2] = { { 1,17,37,UP,3,2,0,false,F_H_YELLOW } , { 2,21,37,UP,3,2,0,false,F_WHITE } };

//定义敌军坦克数组
TANK g_NPC_Tanks[100] = {0};

//定义子弹数组
MISSILE g_Missile[300] = {0};

//定义地图数组
int g_sysMap00[MAP_HIGH][MAP_WIDTH] = {
	WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C
};

int g_sysMap01[MAP_HIGH][MAP_WIDTH] = {
	WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_E,WALL_E,WALL_E,WALL_E,WALL_E,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_E,WALL_E,WALL_E,WALL_E,WALL_E,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_E,WALL_E,WALL_E,WALL_E,WALL_E,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_E,WALL_E,WALL_E,WALL_E,WALL_E,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_E,WALL_E,WALL_E,WALL_E,WALL_E,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,WALL_B,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_E,WALL_E,WALL_E,WALL_E,WALL_E,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_E,WALL_E,WALL_E,WALL_E,WALL_E,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,     0,     0,     0,     0,     0,     0,WALL_A,WALL_A,WALL_A,WALL_A,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_E,WALL_E,WALL_E,WALL_E,WALL_E,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,WALL_D,     0,     0,     0,     0,     0,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_A,     0,     0,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_A,     0,     0,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_A,     0,     0,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_A,     0,     0,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_A,     0,     0,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_A,WALL_A,WALL_C,     0,     0,     0,WALL_C,WALL_A,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,WALL_A,     0,     0,WALL_A,WALL_A,WALL_A,     0,WALL_A,WALL_A,     0,     0,WALL_A,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_A,WALL_A,     0,     0,WALL_A,     0,     0,     0,WALL_A,     0,WALL_A,     0,WALL_A,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,WALL_A,     0,     0,WALL_A,     0,     0,     0,WALL_A,     0,WALL_A,     0,WALL_A,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,WALL_A,     0,     0,WALL_A,WALL_A,     0,     0,WALL_A,     0,WALL_A,     0,WALL_A,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,WALL_A,     0,     0,     0,     0,WALL_A,     0,WALL_A,WALL_A,     0,     0,WALL_A,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,WALL_A,     0,     0,     0,     0,WALL_A,     0,WALL_A,     0,     0,     0,WALL_A,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,WALL_A,     0,     0,     0,     0,WALL_A,     0,WALL_A,     0,     0,     0,WALL_A,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,WALL_A,     0,     0,     0,     0,WALL_A,     0,WALL_A,     0,     0,     0,WALL_A,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,WALL_A,     0,     0,WALL_A,     0,WALL_A,     0,WALL_A,     0,     0,     0,WALL_A,     0,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,WALL_A,WALL_A,WALL_A,     0,     0,WALL_A,     0,     0,WALL_A,     0,     0,     0,WALL_A,WALL_A,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,WALL_C, \
	WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C,WALL_C
};