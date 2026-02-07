#include <graphics.h>
#include <stdio.h>
#include "gobang.h"

char board[ROW][COL]; //棋盘状态，' '表示空格，'*'表示玩家1（黑棋），'$'表示玩家2（白棋）

void initBoard() {
	initgraph(WIN_WIDTH, WIN_HEIGHT); //初始化图形窗口
	/*
	IMAGE img;
	loadimage(&img, "bk.png"); //加载图片
	putimage(0, 0, &img); //显示图片
	*/
	loadimage(NULL, "bk.png"); //加载背景图片
	setlinecolor(BLACK); //设置线条颜色为黑色
	setbkmode(0);

	//绘制棋盘
	for (int i = 0; i <= 8; i++) {
		line(30, 30 + i * 50, 430, 30 + i * 50); //绘制横线
		line(30 + i * 50, 30, 30 + i * 50, 430); //绘制竖线
	}
	settextcolor(BLACK); //设置文字颜色为黑色
	outtextxy(450, 8, "五子棋 ByNowasiki"); //显示标题
	outtextxy(450, 100, "玩家1：黑棋"); //显示玩家1信息
	settextcolor(BLACK); //设置文字颜色为黑色
	outtextxy(450, 150, "玩家2：白棋"); //显示玩家2信息
}

int* input(int* site) {
	while (1) {
		double relativeX = 0, relativeY = 0; //相对坐标
		MOUSEMSG msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN || msg.uMsg == WM_RBUTTONDOWN) {
			relativeX = msg.x - 30;
			relativeY = msg.y - 30;
			relativeX /= 50.0;
			relativeY /= 50.0;
		}
		else continue;
		if (relativeX < 0 || relativeX > 8 || relativeY < 0 || relativeY > 8) {
			printf("点击位置超出棋盘范围，请重新点击！\n");
			continue;
		}
		int x = (int)(relativeX + 0.5);
		int y = (int)(relativeY + 0.5);
		if ((x - relativeX) * (x - relativeX) + (y - relativeY) * (y - relativeY) < 0.2) {
			//printf("落子位置：(%d, %d)\n", x, y);
			site[0] = x;
			site[1] = y;
			return site;
		}
		else printf("点击位置距离棋盘格点过远，请重新点击！\n");
	}
}
void drawChessPiece(int x, int y, int turn) {
	if (turn == 1) {
		//玩家1落子
		setfillcolor(BLACK);
		solidcircle(30 + x * 50, 30 + y * 50, 14);
	}
	else {
		//玩家2落子
		setfillcolor(WHITE);
		solidcircle(30 + x * 50, 30 + y * 50, 14);
	}
}

// 0:继续 1:黑棋赢 2:白棋赢 3:平局
int judge(char board[ROW][COL], int row, int col, int num) {
	//n为连续棋子数量，id为当前棋子类型
	int i = 0, j = 0, n = 0, id = 1; //id = 0:白棋, id = 1:黑棋
	char m[2] = { '$', '*' };//棋子标识，0表示白棋，1表示黑棋

	for (i = 0; i < row; i++) {
		n = 0;
		//检查行
		for (j = 0; j < col; j++) {
			if (board[i][j] == ' ') n = 0;
			else if (n == 0) {
				if (board[i][j] == '$') id = 0;
				else id = 1;
				n++;
			}
			else if (board[i][j] == m[id]) {
				n++;
				if (n == num) {
					if (board[i][j] == '*') return 1; //黑棋赢
					else return 2; //白棋赢
				}
			}
			else {
				n = 1;
				if (board[i][j] == '$') id = 0;
				else id = 1;
			}
		}
	}
	
	//check col
	for (j = 0; j < row; j++) {
		n = 0;
		for (i = 0; i < col; i++) {
			if (board[i][j] == ' ') n = 0;
			else if (n == 0) {
				if (board[i][j] == '$') id = 0;
				else id = 1;
				n++;
			}
			else if (board[i][j] == m[id]) {
				n++;
				if (n == num) {
					if (board[i][j] == '*') return 1; //黑棋赢
					else return 2; //白棋赢
				}
			}
			else {
				n = 1;
				if (board[i][j] == '$') id = 0;
				else id = 1;
			}
		}
	}
	// 检查主对角线（左上到右下）：以第一列和第一行为起点
	// 从第一列的每个格子开始往右下检查
	for (i = 0; i < row; i++) {
		int x = i, y = 0;
		n = 0;
		while (x < row && y < col) {
			if (board[x][y] == ' ') n = 0;
			else if (n == 0) {
				if (board[x][y] == '$') id = 0;
				else id = 1;
				n++;
			}
			else if (board[x][y] == m[id]) {
				n++;
				if (n == num) {
					if (board[x][y] == '*') return 1;
					else return 2;
				}
			}
			else {
				n = 1;
				if (board[x][y] == '$') id = 0;
				else id = 1;
			}
			x++; y++; // 往右下移动
		}
	}

	// 从第一行的每个格子开始往右下检查（跳过第一个已经检查过的）
	for (j = 1; j < col; j++) {
		int x = 0, y = j;
		n = 0;
		while (x < row && y < col) {
			if (board[x][y] == ' ') n = 0;
			else if (n == 0) {
				if (board[x][y] == '$') id = 0;
				else id = 1;
				n++;
			}
			else if (board[x][y] == m[id]) {
				n++;
				if (n == num) {
					if (board[x][y] == '*') return 1;
					else return 2;
				}
			}
			else {
				n = 1;
				if (board[x][y] == '$') id = 0;
				else id = 1;
			}
			x++; y++;
		}
	}

	// 检查副对角线（右上到左下）：以第一列和最后一列为起点
	// 从第一列的每个格子开始往右上检查
	for (i = 0; i < row; i++) {
		int x = i, y = col - 1;
		n = 0;
		while (x < row && y >= 0) {
			if (board[x][y] == ' ') n = 0;
			else if (n == 0) {
				if (board[x][y] == '$') id = 0;
				else id = 1;
				n++;
			}
			else if (board[x][y] == m[id]) {
				n++;
				if (n == num) {
					if (board[x][y] == '*') return 1;
					else return 2;
				}
			}
			else {
				n = 1;
				if (board[x][y] == '$') id = 0;
				else id = 1;
			}
			x++; y--; // 往右上移动（行增加，列减少）
		}
	}

	// 从最后一列的每个格子开始往右上检查（跳过第一个已经检查过的）
	for (j = col - 2; j >= 0; j--) {
		int x = 0, y = j;
		n = 0;
		while (x < row && y >= 0) {
			if (board[x][y] == ' ') n = 0;
			else if (n == 0) {
				if (board[x][y] == '$') id = 0;
				else id = 1;
				n++;
			}
			else if (board[x][y] == m[id]) {
				n++;
				if (n == num) {
					if (board[x][y] == '*') return 1;
					else return 2;
				}
			}
			else {
				n = 1;
				if (board[x][y] == '$') id = 0;
				else id = 1;
			}
			x++; y--;
		}
	}
	//检查整个棋盘是否还有空格，如果没有则平局，否则继续游戏
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (board[i][j] == ' ') return 0; //继续
		}
	}
	//平局
	return 3;
}

void initBoardArray(char board[ROW][COL], int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			board[i][j] = ' '; //初始化棋盘状态为全空格
		}
	}
}

void displayBoard(char board[ROW][COL], int row, int col) {
	int i, j;
	printf("\n");
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			// 如果格子是空格（或特定字符），显示 N，否则显示原内容
			if (board[i][j] == ' ' || board[i][j] == '\0') {
				printf(" N ");
			}
			else {
				printf(" %c ", board[i][j]);
			}
		}
		printf("\n");  // 每行结束后换行
	}
	printf("\n");
}