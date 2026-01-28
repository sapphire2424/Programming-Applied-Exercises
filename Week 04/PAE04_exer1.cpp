/* 2025年度 プログラミング応用演習 第4回 演習プログラム(1) - PAE04_exer1
====================================================================================================
■平面上の点を表すクラスを使ったプログラム
・直交座標系の点クラス(PointCartesian) - 直交する2軸(x,y)で表す．
  - 原点から点までの距離を取得する関数(getDist)を定義する．
・極座標系の点クラス(PointPolar) - 原点からの距離(動径,radius)と原点から見た方向(偏角,angle)で表す．
  - PointCartesianクラスで初期化するコンストラクタを定義する．
  - 原点から点までの距離を取得する関数(getDist)を定義する．
  - 極座標から直交座標(PointCartesian)を取得する関数(getCartesian)を定義する．
==================================================================================================*/
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;
//--------------------------------------------------------------------------------------------------
// 直交座標系の点クラス
class PointCartesian {
public:
    double  x, y;   // 点の座標

    // コンストラクタ
    PointCartesian(void) : x(0.0), y(0.0) {}
    PointCartesian(double x, double y) : x(x), y(y) {}

    // 原点から点までの距離を取得する．
    double getDist(void) {
        // √x^2 + y^2
        return sqrt(x*x+y*y);
    }

    // 座標を表示する．
    void print(void) {
        std::cout << "x=" << x << ", y=" << y << std::endl;
    }
};

//--------------------------------------------------------------------------------------------------
// 極座標系の点クラス
class PointPolar {
public:
    double  radius;     // 動径
    double  angle;      // 偏角(rad)

    // コンストラクタ
    PointPolar(void) : radius(1.0), angle(0.0) {}
    PointPolar(double r, double a) : radius(r), angle(a) {}
    PointPolar(const PointCartesian &pc) {


    }

    // 原点から点までの距離を取得する．
    double getDist(void) {
        return radius;
    }

    // 極座標(radius,angle)に対する直交座標系の点(PointCartesian)を求める．
    PointCartesian getCartesian(void) {
        double x = radius * cos(angle);
        double y = radius * sin(angle);
        return PointCartesian(x,y);
    }

    // 座標を表示する．
    void print(void) {
        std::cout << "radius=" << radius << ", angle=" << angle << std::endl;
    }
};

//==================================================================================================
int main(void)
{
    PointCartesian  pc1(1.0, 2.0);      // (x, y) = (1.0, 2.0)で初期化
    PointCartesian  pc2 = pc1;          // pc1で初期化
    PointCartesian  pc3;
    PointPolar      pp1(1.0, 0.0);      // (radius,angle) = (1.0, 0.0)で初期化
    PointPolar      pp2 = pp1;          // pp1で初期化

    std::cout << "1．生成・初期化状態の各パラメータ" << std::endl;
    std::cout << "pc1： ";
    pc1.print();
    std::cout << "pc2： ";
    pc2.print();
    std::cout << "pc3： ";
    pc3.print();
    std::cout << "pp1： ";
    pp1.print();
    std::cout << "pp2： ";
    pp2.print();

    std::cout << "\n2．原点から点までの距離" << std::endl;
    std::cout << "pc1： " << pc1.getDist() << std::endl;
    std::cout << "pp1： " << pp1.getDist() << std::endl;

    std::cout << "\n3．極座標pp1から直交座標pc3を取得" << std::endl;
    pc3 = pp1.getCartesian();
    std::cout << "pc3： ";
    pc3.print();


    return 0;
}


/* 実行結果 ========================================================================================

1．生成・初期化状態の各パラメータ
pc1： x=1, y=2
pc2： x=1, y=2
pc3： x=0, y=0
pp1： radius=1, angle=0
pp2： radius=1, angle=0

2．原点から点までの距離
pc1： 2.23607
pp1： 1

3．極座標pp1から直交座標pc3を取得
pc3： x=1, y=0

==================================================================================================*/
