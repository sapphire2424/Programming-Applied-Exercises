/* 2025年度 プログラミング応用演習 第4回 課題レポートプログラム(1) - PAE04_repo1
====================================================================================================
■正多角形クラス(RegularPolygon)を定義する．
・それぞれ[追加]で始まるコメント行の次の行から追加する．
・コンストラクタ
  ① デフォルト(原点中心で半径1の円の内接三角形)
  ② 頂点数(原点中心で半径1の円の内接N角形)で初期化
・メンバ関数
  ① 頂点数を取得する：getSize
  ② 頂点座標を計算する：calcVertices
  ③ n角形に変更する：reshape
  ④ 頂点座標の一覧を表示する：print
・演算子"*"：多角形を実数(float型)培に拡大・縮小
             <多角形オブジェクト>*<実数>，<実数>*<多角形オブジェクト>，両方対応すること．
・頂点座標は，Vertex構造体で定義する(定義済)．
==================================================================================================*/
#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;
// 頂点座標構造体の定義 - 一つの頂点の2次元(x,y)座標を表す．
typedef struct vertex_t {
    float  x, y;    // 点の座標
} Vertex;


// 正多角形クラスの定義
class RegularPolygon {
private:
    std::vector<Vertex>   vertices;     // 頂点配列

public:
    // [追加] デフォルトコンストラクタ
    RegularPolygon(void) : RegularPolygon(3){


    }
    // [追加] 頂点数による初期化コンストラクタ
    RegularPolygon(int n){
        vertices.resize(n);
        calcVertices();
    }
    // [追加] 頂点数を取得する関数
    int getSize(){
        return vertices.size();

    }
    // [追加] 頂点座標を計算する関数
    void calcVertices(){
        for(int i = 0;i < vertices.size();i++){
            vertices[i].x = cos(i*((2.0 * M_PI) / vertices.size())) ;
            vertices[i].y = sin(i*((2.0 * M_PI) / vertices.size())) ;
        }
    }
    // [追加] n角形に変更する関数
    void reshape(int n){
        vertices.resize(n);
        calcVertices();
    }
    // [追加] 算術演算子"*"：<多角形>*<実数>
    RegularPolygon operator*(float a){
        RegularPolygon new_poly = *this;;
        for(int i = 0;i<vertices.size();i++){
            new_poly.vertices[i].x = vertices[i].x*a;
            new_poly.vertices[i].y = vertices[i].y*a;
        }
        return new_poly;
    }
    // 頂点座標一覧の表示
    void print(void) {
        std::cout << std::fixed << std::setprecision(6);
        for(int i=0; i<vertices.size(); i++) {
            std::cout << vertices[i].x << ", " << vertices[i].y << std::endl;
        }
    }

    // 算術演算子"*"：<実数>*<多角形>のフレンド宣言
    friend RegularPolygon operator*(const float a, const RegularPolygon& p);
};

// [追加] 算術演算子"*"：<実数>*<多角形>の実体
    RegularPolygon operator*(const float a, const RegularPolygon& p){
        RegularPolygon new_poly = p;
        for(int i = 0;i<p.vertices.size();i++){
            new_poly.vertices[i].x = p.vertices[i].x*a;
            new_poly.vertices[i].y = p.vertices[i].y*a;
        }
        return new_poly;
    }








//==================================================================================================
int main(void)
{
    // 多角形クラスオブジェクトのインスタンス生成
    RegularPolygon   poly1;
    RegularPolygon   poly2;

    // 初期状態のpoly1の頂点座標を表示する．
    std::cout << "初期状態(3角形)" << std::endl;
    poly1.print();

    // poly1を4角形に変更し，頂点座標を表示する．
    std::cout << "\n4角形に変更" << std::endl;
    poly1.reshape(4);
    poly1.print();

    // poly1の2倍（<多角形>*<実数>）をpoly2に代入し，poly2の頂点座標を表示する．
    std::cout << "\npoly1を2倍し，poly2に代入(1)" << std::endl;
    poly2 = poly1 * 2.0;
    poly2.print();

    // poly1の2倍（<実数>*<多角形>）をpoly2に代入し，poly2の頂点座標を表示する．
    std::cout << "\npoly1を2倍し，poly2に代入(2)" << std::endl;
    poly2 = 2.0 * poly1;
    poly2.print();

	return 0;
}


/* 実行結果 ========================================================================================
初期状態(3角形)
1.000000, 0.000000
-0.500000, 0.866025
-0.500000, -0.866025

4角形に変更
1.000000, 0.000000
0.000000, 1.000000
-1.000000, 0.000000
-0.000000, -1.000000

poly1を2倍し，poly2に代入(1)
2.000000, 0.000000
0.000000, 2.000000
-2.000000, 0.000000
-0.000000, -2.000000

poly1を2倍し，poly2に代入(2)
2.000000, 0.000000
0.000000, 2.000000
-2.000000, 0.000000
-0.000000, -2.000000
==================================================================================================*/
