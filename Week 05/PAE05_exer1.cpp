/* 2025年度 プログラミング応用演習 第5回 演習プログラム(1) - PAE05_exer1
====================================================================================================
■Figureクラスの派生クラスに対して，以下の修正・追加を行う．
・派生クラスとして，楕円クラス(Ellipse)を定義する(必要なコンストラクタ，メンバ関数を定義)
・大きさを返すメンバ関数 float size(void) を定義する．
  大きさ：Lineクラスは線の長さ，Circle, Ellipse, Rectangleは面積
==================================================================================================*/
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
using namespace std;
//------------------------------------------------
// 図形の基底クラスの定義
class Figure {
protected:      // 派生クラスからの直接アクセスのため，x0,y0はprotectedメンバ
    float   x0;     // 基点x座標
    float   y0;     // 基点y座標

public:
    Figure(void) : x0(0.0), y0(0.0) {}
    Figure(float x, float y) : x0(x), y0(y) {}

    // 基点を現座標からdx,dy移動する．
    void move(float dx, float dy) {
        x0 += dx;
        y0 += dy;
    }

    // パラメータを表示する．
    void print(void) {
        std::cout << "(" << x0 << ", " << y0 << ")";
    }

    // 大きさを求める．
    float size(void) {
        return 0;       // 点の大きさは0とする．
    }
};

//------------------------------------------------
// 線分クラスの定義
class Line : public Figure {
private:
    float   x1;     // 終点のx座標
    float   y1;     // 終点のy座標

    // 始点はFigureのx0,y0

public:
    Line(void) : x1(1.0), y1(0.0), Figure() {}
    Line(float x, float y) : x1(x), y1(y), Figure() {}

    // 線分を現座標からdx,dy移動する．
    // 始点と終点を移動させるため，Line独自のmoveを定義する．
    void move(float dx, float dy) {
        Figure::move(dx, dy);

        x1 += dx;   // 終点を移動する．
        y1 += dy;
    }

    // パラメータを表示する．
    void print(void) {
        std::cout << "Line: (" << x0 << ", " << y0 << ") - ";
        std::cout << "(" << x1 << ", " << y1 << ")" << std::endl;
    }

    // [追加] 大きさを求める．
    float size(void) {
        return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
	}
};

//------------------------------------------------
// 円クラスの定義
class Circle : public Figure {
private:
    float   radius;     // 半径

    // 中心座標はFigureのx0,y0

public:
    Circle(void) : radius(1.0), Figure() {}
    Circle(float r) : radius(r), Figure() {}

    // 中心座標x0,y0を移動すればいいので，独自のmove関数は不要
    //void move(float dx, float dy) {...}

    // パラメータを表示する．
    void print(void) {
        std::cout << "Circle: center=(" << x0 << ", " << y0 << "), ";
        std::cout << "radius=" << radius << std::endl;
    }

    // [追加] 大きさを求める．
    float size(void) {
        return pow(radius,2)*M_PI;




    }
};

//------------------------------------------------
// [追加] 楕円クラスの定義 (大きさを求めるメンバ関数を含む)
class Ellipse : public Figure {
private:
    // 長軸・短軸の半径(a,bの大小関係で，縦長，横長の楕円となるものとする)
    float   a;
    float   b;

public:
    // コンストラクタ
    Ellipse(void) : a(1.0), b(1.0), Figure() {}
    Ellipse(float x, float y) : a(x), b(y), Figure() {}
    // パラメータを表示する．
    void print(void) {
        std::cout << "Ellipse: center=(" << x0 << ", " << y0 << "), ";
        std::cout << "a=" << a << ",b=" << b << std::endl;
    }
    // 大きさを求める．
    float size(void) {
        return M_PI * a * b;
    }
};

//------------------------------------------------
// 四角形クラスの定義
class Rectangle : public Figure {
private:
    float   width;      // 幅
    float   height;     // 高さ

    // 左下頂点座標はFigureのx0,y0

public:
    Rectangle(void) : width(1.0), height(1.0), Figure() {}
    Rectangle(float w, float h) : width(w), height(h), Figure() {}

    // 左上座標x0,y0を移動すればいいので，独自のmove関数は不要
    //void move(float dx, float dy) {...}

    // パラメータを表示する．
    void print(void) {
        std::cout << "Rectangle: v0=(" << x0 << ", " << y0 << "), ";
        std::cout << "width=" << width << ", height=" << height << std::endl;
    }

    // [追加] 大きさを求める．
    float size(void) {
        return width * height;
    }
};

//==================================================================================================
int main(void)
{
    // 各図形クラスオブジェクトのインスタンスを生成する．
    Line       line(3, 5);        // 終点を(3, 5)で初期化
    Circle     circle(10);        // 半径を10で初期化
    Ellipse    ellipse(7, 5);     // 長径7, 短径5で初期化
    Rectangle  rectangle(5, 8);   // 幅5, 高さ8で初期化

    // 各図形オブジェクトのパラメータを表示する．
    std::cout << "各図形オブジェクトのパラメータ：" << std::endl;
    line.print();
    circle.print();
    ellipse.print();
    rectangle.print();


    // 各図形の大きさを求めて表示する．
    std::cout << "\n各図形の大きさ：" << std::endl;
    cout << "Line's size:" << line.size() << endl;
    cout << "Circle's size:" << circle.size() << endl;
    cout << "Ellipse's size:" << ellipse.size() << endl;
    cout << "Rectangle's size:" << rectangle.size() << endl;


    return 0;
}


/* 実行結果 ========================================================================================
各図形オブジェクトのパラメータ：
Line: (0, 0) - (3, 5)
Circle: center=(0, 0), radius=10
Ellipse: center=(0, 0), a=7,b=5
Rectangle: v0=(0, 0), width=5, height=8

各図形の大きさ：
Line's size:5.83095
Circle's size:314.159
Ellipse's size:109.956
Rectangle's size:40
==================================================================================================*/
