# 项目背景
2048是一个风靡全球的益智类小游戏，通过上下左右控制来合并盘子里的数字，直到盘子里出现2048。

[原版体验地址]( http://gabrielecirulli.github.io/2048/)

# 依赖库
curses

# 开发环境
MacOS 10.14.3 Mojave 

# 编译命令
Linux/Mac: g++ main.cpp -l ncurses -o 2048

Windows: g++ main.cpp C:\pdcurs36\wincon\pdcurses.a -I C:\pdcurs36\ -o 2048
