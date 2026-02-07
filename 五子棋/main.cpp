#include <graphics.h>
#include <stdio.h>
#include "gobang.h"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib") //链接多媒体库
int main() {
	initBoard();
	initBoardArray(board, ROW, COL);
	int turn = 1; //1表示玩家1（黑棋），-1表示玩家2（白棋）
	int site[2];
	mciSendString("play music.mp3", NULL, 0, 0);
	while (true) {
		//PlaySound(TEXT("click.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (input(site)) {
			//处理落子
			if (board[site[1]][site[0]] != ' ') {
				MessageBox(GetHWnd(), "该位置已经有棋子了，请重新选择！", "无效落子", MB_OK);
				continue;
			}
			drawChessPiece(site[0], site[1], turn);
			board[site[1]][site[0]] = (turn == 1) ? '*' : '$'; //更新棋盘状态
			displayBoard(board, ROW, COL);
			turn = -turn; //切换玩家
			int ret = judge(board, ROW, COL, 5);
			if (ret == 1) {
				MessageBox(GetHWnd(), "玩家1（黑棋）获胜！", "游戏结束", MB_OK);
				break;
			
			}
			else if (ret == 2) {
				MessageBox(GetHWnd(), "玩家2（白棋）获胜！", "游戏结束", MB_OK);
				break;
			}
			else if (ret == 3) {
				MessageBox(GetHWnd(), "平局！", "游戏结束", MB_OK);
				break;
			}
		}
	}
	closegraph();
	return 0;
}