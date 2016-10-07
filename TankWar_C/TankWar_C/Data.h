#pragma once
/*
	此文件：
		1. 定义数据类型
		2. 声明全局变量
*/

#pragma region 常用文字颜色定义

// 字体显示相关
#define REVERSE    COMMON_LVB_REVERSE_VIDEO	 // 反色
#define UNDER_SCORE COMMON_LVB_UNDERSCORE    // 下划线

// 文字前景色
#define F_BLUE     FOREGROUND_BLUE      // 深蓝
#define F_H_BLUE   0x0001|0x0008        // 亮蓝
#define F_GREEN    0x0002               // 深绿
#define F_H_GREEN  0x0002|0x0008        // 亮绿
#define F_RED      0x0004               // 深红
#define F_H_RED    0x0004|0x0008        // 亮红
#define F_YELLOW   0x0002|0x0004        // 深黄
#define F_H_YELLOW 0x0002|0x0004|0x0008 // 亮黄
#define F_PURPLE   0x0001|0x0004        // 深紫
#define F_H_PURPLE 0x0001|0x0004|0x0008 // 亮紫
#define F_CYAN     0x0002|0x0004        // 深青
#define F_H_CYAN   0x0002|0x0004|0x0008 // 亮青
#define F_WHITE    0x0004|0x0002|0x0001
#define F_H_WHITE  0x0004|0x0002|0x0001|0x0008

// 文字背景色
#define B_BLUE     BACKGROUND_BLUE      // 深蓝
#define B_H_BLUE   0x0010|0x0080        // 亮蓝
#define B_GREEN    0x0020               // 深绿
#define B_H_GREEN  0x0020|0x0080        // 亮绿
#define B_RED      0x0040               // 深红
#define B_H_RED    0x0040|0x0080        // 亮红
#define B_YELLOW   0x0020|0x0040        // 深黄
#define B_H_YELLOW 0x0020|0x0040|0x0080 // 亮黄
#define B_PURPLE   0x0010|0x0040        // 深紫
#define B_H_PURPLE 0x0010|0x0040|0x0080 // 亮紫
#define B_CYAN     0x0020|0x0040        // 深青
#define B_H_CYAN   0x0020|0x0040|0x0080 // 亮青
#define B_WHITE    0x0010|0x0020|0x0040
#define B_H_WHITE  0x0010|0x0020|0x0040|0x0080

#pragma endregion

#pragma region 常用图案

#define WALL__      0x00  // "  " 空道（不可破话，  可通过）				
#define WALL_A      0x01  // "▓" 土墙（  可破坏，不可通过）		
#define WALL_B      0x02  // "卍" 土墙（  可破坏, 不可通过，土墙的破坏形态）
#define WALL_C      0x03  // "〓" 铁墙 (不可破坏, 不可通过)
#define WALL_D      0x04  // "≈" 河流（不可破坏,   子弹可通过，坦克不可通过）
#define WALL_E      0x05  // "≡" 丛林（不可破坏，  可通过，可以隐身）	
#define WALL_G      0x06  // "☆" 箱子（不可破坏，  可拾取，加属性）
#define WALL_H      0x07  // "§" 基地（  可破坏，不可通过)

#define TANK_A      0x00  //  "  "
#define TANK_B      0x01  //  "■"
#define TANK_C      0x02  //  "□"
#define TANK_D      0x03  //  "◇"
#define TANK_E      0x04  //  "○"

#define BLOOD_0     0x0   //  "  "
#define BLOOD_1     0x1	  //  "①"
#define BLOOD_2     0x2   //  "②"
#define BLOOD_3     0x3   //  "③"
#define BLOOD_4     0x4   //  "④"
#define BLOOD_5     0x5   //  "⑤"
#define BLOOD_6     0x6   //  "⑥"
#define BLOOD_7     0x7	  //  "⑦"
#define BLOOD_8     0x8   //  "⑧"
#define BLOOD_9     0x9   //  "⑨"

#define MISSIL_0    0x0	  //  "  "
#define MISSIL_1    0x1	  //  "○"
#define MISSIL_2    0x2   //  "●"
#define MISSIL_3    0x3   //  "¤"
#define MISSIL_4    0x4   //  "◇"
#define MISSIL_5    0x5   //  "◎"
#define MISSIL_6    0x6   //  "↑"
#define MISSIL_7    0x7	  //  "↓"
#define MISSIL_8    0x8   //  "←"
#define MISSIL_9    0x9   //  "→"
#pragma endregion

#pragma region 全局参数定义

//窗口大小
#define WINDOWS_WIDTH 50
#define WINDOWS_HIGH  40

//地图大小
#define MAP_WIDTH 40					//地图宽
#define MAP_HIGH  40					//地图高

//默认窗口标题
#define AUTO_CONSOLE_TITLE "TankWar_C"

//方向
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

#pragma endregion

//定义玩家信息
typedef struct _PLAYERINFO
{
	char name[20];
	int  score;
	char note[20];
}PLAYERINFO,*PPLAYERINFO;
//定义坦克结构体
typedef struct _TANK 
{
	int tankID;             //坦克编号
	int posX;               //所在地图x坐标（水平轴）
	int posY;               //所在地图x坐标（垂直轴）
	int orientation;        //朝向
	int blood;              //血量
	int level;              //导弹等级
	int style;              //坦克样式
	bool isValid;           //是否有效
	int color;
}TANK,*PTANK;
//定义子弹结构体
typedef struct _MISSILE
{
	int missileID;          //导弹编号
	int posX;				//所在地图x坐标（水平轴）
	int posY;				//所在地图x坐标（垂直轴）
	int orientation;		//朝向
	int level;				//血量
	int style;              //子弹样式
	bool isValid;           //是否有效

	int tankID;				//坦克编号（记录这颗导弹是谁发射的）

}MISSILE, *PMISSILE;

//物体的样式和颜色 墙体图片以及颜色数组
extern char * wall_pic[];             //墙体的图片库
extern int  wall_color[];             //墙体的颜色库
extern int tank_style[][4][3][3];     //坦克的样式库(点阵)(每种样式的坦克有上下左右四个造型，每个造型需要9个点描述)
extern char * tank_pic[];             //坦克的图片库
extern char * blood_pic[];            //血量的图片库
extern char * missile_pic[];          //子弹的图片库

//声明玩家信息
extern PLAYERINFO g_player_Info[2];
//声明我军坦克数组
extern TANK g_Player_Tanks[2];
//声明敌军坦克数组
extern TANK g_NPC_Tanks[100];
//声明子弹数组
extern MISSILE g_Missile[300];
//声明地图数组
extern int g_sysMap00[MAP_HIGH][MAP_WIDTH]; //地图数组里面可以存位段结构体
extern int g_sysMap01[MAP_HIGH][MAP_WIDTH];