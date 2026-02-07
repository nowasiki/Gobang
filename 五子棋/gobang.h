#pragma once

#define WIN_WIDTH 600
#define WIN_HEIGHT 500

#define COL 9
#define ROW 9

void initBoard(); //初始化棋盘
int* input(int* site); //处理鼠标输入
void drawChessPiece(int x, int y, int turn); //绘制棋子
void displayBoard(char board[ROW][COL], int row, int col); //显示棋盘状态
void initBoardArray(char board[ROW][COL], int row, int col); //初始化棋盘状态
int judge(char board[ROW][COL], int row, int col, int num);

extern char board[9][9]; //棋盘状态，' '表示空格，'*'表示玩家1（黑棋），'$'表示玩家2（白棋）