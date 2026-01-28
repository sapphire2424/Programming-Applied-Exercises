/* 2025年度 プログラミング応用演習 第12回 演習プログラム(1) - PAE12_exer1
====================================================================================================
■迷路探索プログラム
・迷路はmaze_mapで定義されている．
・スタート(S)からランダムに上下左右に移動して，ゴール(G)するのに何回移動するか数える．
  - 移動しようとした方向が壁('X')だった場合は，移動回数に加えないこと．
・ゴールしたら，またスタートから探索する．これを10000回繰り返し試行する．
・全試行における移動回数から，最大移動回数と平均移動回数を求めて表示する．
・#if 1で迷路A，#if 0で迷路Bで実行する．
==================================================================================================*/
#include <iostream>
#include <vector>
#include <string>
#include <random>

// 試行回数
#define TRIALS  10000

// 迷路データ ('X':壁, ' ':通路, 'S':スタート, 'G':ゴール)
#if 0
// 迷路A
#define MAZEX  10
#define MAZEY  10

const char *maze_map[MAZEY] = {   // 17
    "XXXXXXXXXX",
    "XSX  X   X",
    "X XX   X X",
    "X XXX XXXX",
    "X        X",
    "X XXXX XXX",
    "X X X  X X",
    "XXX X XX X",
    "XG        X",
    "XXXXXXXXXX"
};
#else
// 迷路B
#define MAZEX  7
#define MAZEY  7

const char *maze_map[MAZEY] = {    // 12
    "XXXXXXX",
    "XS X  X",
    "X X X X",
    "X X   X",
    "X X X X",
    "X   XGX",
    "XXXXXXX"
};
#endif


// 方向指示構造体
struct Direction {
    int  x;
    int  y;
};

//==================================================================================================
int main(void)
{
    // 乱数生成関連
    std::random_device rnd;
    std::mt19937        gen(rnd());
    std::uniform_int_distribution<>   mv(0, 3);  // 移動方向(0～3)を決める乱数

    // 移動方向 (0:右, 1:左, 2:下, 3:上)
    Direction   dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // スタート'S'とゴール'G'のx,y座標
    int   sx = 0, sy = 0;    // スタート座標
    int   gx = 0, gy = 0;    // ゴール座標

    int   x, y, d;
    int   new_x, new_y;

    int   moves = 0;        // 1回の試行における移動回数
    int   sum_moves = 0;    // 移動回数のTRIALS回合計
    int   max_moves = 0;    // 最大移動回数
    int   ave_moves = 0;    // 平均移動回数

    // スタート'S'とゴール'G'の座標を求める．
    for (int i = 0; i < MAZEY; i++) {
        for (int j = 0; j < MAZEX; j++) {
            if (maze_map[i][j] == 'S') {
                sx = j;
                sy = i;
            }
            else if (maze_map[i][j] == 'G') {
                gx = j;
                gy = i;
            }
        }
    }

    // 迷路探索をtrial回試行
    for(int i=0; i<TRIALS; i++) {
        x = sx;     // 初期位置(x,y)をスタート座標(sx,sy)で初期化
        y = sy;
        moves = 0;  // 最初，移動回数は0

        // 迷路探索ループ：ゴールに着くまでランダムウォークする．
        while (x != gx || y != gy) {
            d = mv(gen);
            new_x = x + dir[d].x;
            new_y = y + dir[d].y;
            if (maze_map[new_y][new_x] != 'X') {
                x = new_x;
                y = new_y;
                moves++;
            }
        }

        // 最大移動回数を更新する．
        if (moves > max_moves) {
            max_moves = moves;
        }

        // 移動回数の累計
        sum_moves += moves;
    }

    // 移動回数の平均
    ave_moves = (double)sum_moves / TRIALS;

    // 結果表示
    std::cout << "試行回数: " << TRIALS << std::endl;
    std::cout << "最大移動回数 = " << max_moves << std::endl;
    std::cout << "平均移動回数 = " << ave_moves << std::endl;

    return 0;
}


/* 実行結果 ========================================================================================

[迷路Aの場合]
試行回数: 10000
最大移動回数 = 6353
平均移動回数 = 634

----------------------------------------------------------------------------------------------------
[迷路Bの場合]
試行回数: 10000
最大移動回数 = 1376
平均移動回数 = 187

==================================================================================================*/