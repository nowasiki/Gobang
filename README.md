# 五子棋GogoBang!

## 简介

本游戏采用C/C++编写，是我学习C语言的第三个项目。

## 游玩方式

普通的五子棋。分为黑棋和白棋，先到五颗子相连的玩家胜利。

## Download

在`release`中找到`GogoBang.exe`，在本地进行安装即可。

## EasyX库

EasyX Graphics Library 是针对 Visual C++ 的免费绘图库。如果要编译源代码的话，需要安装这个库。

## 有待修改之处

在输赢判断的部分，我大量使用了循环结构，这样的时间复杂度是很高的，可以将其修改为以当前棋子为中心的附近判断。

## 音乐

音乐是颜人中-晚安，`mmsystem.h`库中的`comment(lib, "winmm.lib")`负责连接多媒体库。

## 程序打包

本项目通过`Inno Setup Complier`打包，这是一个非商业免费项目。

## 个人信息

作者：曾祥龙

- 学校：宁波工程学院 统计与数据科学学院
- 专业：信息与计算科学
- 年级：2025级
- 邮箱：[zengxianglong@nbut.edu.cn](mailto:zengxianglong@nbut.edu.cn)
- GitHub： [nowasiki · GitHub](https://github.com/nowasiki)

> 欢迎 Star ⭐ 和 Fork！如果代码有问题或建议，欢迎提 Issue～

感谢查看我的项目！