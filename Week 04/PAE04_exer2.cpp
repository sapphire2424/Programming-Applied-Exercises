/* 2025年度 プログラミング応用演習 第4回 演習プログラム(2) - PAE04_exer2
====================================================================================================
■円クラスに関して，下記の機能(メンバ関数)を追加する．
・それぞれ[追加]で始まるコメント行の次の行から追加する．
・area：円の面積を計算して戻り値とする．
・overlap：円が重なっているかどうかチェックする．
・operator==,operator!=：同じ(中心座標と半径が同じ)円か否かチェックする(比較演算子==,!=)．
==================================================================================================*/
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

// 円クラスの定義
class Circle {
private:
    float   xc, yc;      // 中心座標
    float   radius;      // 半径

public:
    // コンストラクタ
    Circle(void) : xc(0.0), yc(0.0), radius(1.0) { }
    Circle(float x, float y, float r) : xc(x), yc(y), radius(r) { }

    // 中心座標の設定
    void setCenter(const float x, const float y) {
        xc = x;
        yc = y;
    }

    // 半径の設定
    void setRadius(const float r) {
        radius = r;
    }

    // パラメータ表示
    void print(void) {
        std::cout << "(xc, yc) = (" << xc << ", " << yc << "), r = " << radius << std::endl;
    }

    // [追加] 面積を計算し，戻り値とする．
    float area(){
        return radius * radius * M_PI;

    }
    // [追加] 引数で与えられた円と重なっているかチェックする．
    bool overlap(const Circle other){
        float dx = xc - other.xc;
        float dy = yc - other.yc;
        float d = sqrt(dx*dx+dy*dy);
        float r_sum = radius + other.radius;
        if (d < r_sum){
            return true;
        }else{
            return false;
        }

    }
    // [追加] 比較演算子(==)
    bool operator==(const Circle other){
        if ((xc == other.xc)&&(yc == other.yc)&&(radius == other.radius)){
            return true;
        }else{
            return false;
        }
    }
    // [追加] 比較演算子(!=)
    bool operator!=(const Circle other){
        if ((xc == other.xc)&&(yc == other.yc)&&(radius == other.radius)){
            return false;
        }else{
            return true;
        }
    }
};

//==================================================================================================
int main(void)
{
    // 円クラスオブジェクトのインスタンス生成
    Circle   c1;                   // 中心(0, 0)，半径1
    Circle   c2(1.0, 0.0, 1.0);    // 中心(1, 0)，半径1
    Circle   c3(5.0, 5.0, 2.0);    // 中心(5, 5)，半径2

    // 初期パラメータを表示する．
    std::cout << "初期パラメータ" << std::endl;
    std::cout << "c1: ";
    c1.print();
    std::cout << "c2: ";
    c2.print();
    std::cout << "c3: ";
    c3.print();

    // 円の面積を計算し，表示する．
    std::cout << "--------------------" << std::endl;
    std::cout << "面積" << std::endl;
    std::cout << "s1 area = " << c1.area() << std::endl;
    std::cout << "s2 area = " << c2.area() << std::endl;
    std::cout << "s3 area = " << c3.area() << std::endl;

    // 円の重なりをチェックする．
    std::cout << "--------------------" << std::endl;
    std::cout << "重なっているか否か" << std::endl;
    std::cout << "c1とc2は重なって";

    if(c1.overlap(c2) == true)    std::cout << "いる．" << std::endl;
    else    std::cout << "いない．" << std::endl;

    std::cout << "c1とc3は重なって";
    if(c1.overlap(c3) == true)    std::cout << "いる．" << std::endl;
    else    std::cout << "いない．" << std::endl;

    std::cout << "c2とc3は重なって";
    if(c2.overlap(c3) == true)    std::cout << "いる．" << std::endl;
    else    std::cout << "いない．" << std::endl;

	// 以降の==を確認するため，c2の中心座標と半径をc1と同じ値に変更する．
	c2.setCenter(0, 0);
	c2.setRadius(1);

    // 同じ円か否かチェックする．
    std::cout << "--------------------" << std::endl;
    std::cout << "2円が同じか否か" << std::endl;
    std::cout << "c1とc2は同じで";

    if(c1 == c2)    std::cout << "ある．" << std::endl;
    else    std::cout << "はない．" << std::endl;
    std::cout << "c1とc3は同じで";
    if(c1 != c3)    std::cout << "はない．" << std::endl;
    else    std::cout << "ある．" << std::endl;

    return 0;
}


/* 実行結果 ========================================================================================
初期パラメータ
c1: (xc, yc) = (0, 0), r = 1
c2: (xc, yc) = (1, 0), r = 1
c3: (xc, yc) = (5, 5), r = 2
--------------------
面積
s1 area = 3.14159
s2 area = 3.14159
s3 area = 12.5664
--------------------
重なっているか否か
c1とc2は重なっている．
c1とc3は重なっていない．
c2とc3は重なっていない．
--------------------
2円が同じか否か
c1とc2は同じである．
c1とc3は同じではない．
==================================================================================================*/
