/* 2025年度 プログラミング応用演習 第4回 演習プログラム(4)解 - PAE04_exer4
====================================================================================================
■Vec3dクラスにcin, coutの演算子(<<,>>)オーバーロードを追加する．
・<<や>>を対象となっていない型・クラス(Vec3d)に対して定義する．
・<<は，括弧でくくり，成分をカンマ区切りで表示する．例) (1,2,3)
・>>は，スペース区切りで成分をキー入力する．例) 3 4 5  [Enter]
==================================================================================================*/
#include <iostream>
using namespace std;
// 3次元ベクトル(Vec3d)クラスの定義
class Vec3d {
private:
    float   x, y, z;

public:
    Vec3d(void) : x(0), y(0), z(0) {}
    Vec3d(float x, float y, float z) : x(x), y(y), z(z) {}

    // 代入演算子(=)
    Vec3d& operator=(const Vec3d& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    // 算術演算子(+)
    Vec3d operator+(const Vec3d& v) {
        Vec3d  r;
        r.x = x + v.x;
        r.y = y + v.y;
        r.z = z + v.z;
        return r;
    }

    // 複合代入演算子(+=)
    Vec3d& operator+=(const Vec3d& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // 関係演算子(==)
    bool operator==(const Vec3d& v) {
        if(x == v.x && y == v.y && z == v.z) {
            return true;
        }
        return false;
    }

    // 関係演算子(!=)
    bool operator!=(const Vec3d& v) {
        return !(*this == v);       // 関係演算子(==)の結果の否定
    }

    // coutを用いた <<演算子による標準出力のフレンド関数演算子(operator<<)の宣言
    // ベクトルの成分を(x,y,z)形式で表示する．
    friend ostream& operator<<(ostream& cout,const Vec3d& vec);
    // cinを用いた >>演算子による標準出力のフレンド関数演算子(operator>>)の宣言
    // ベクトルの成分をスペース区切りx y zで入力する．
    friend istream& operator>>(istream& cin,Vec3d& vec);
};


// coutを用いた <<演算子による標準出力のフレンド関数演算子(operator<<)の定義
ostream& operator<<(ostream& cout,const Vec3d& vec){
    cout << "(" << vec.x << "," << vec.y << "," << vec.z << ")";
    return cout;
}
// cinを用いた >>演算子による標準入力のフレンド関数演算子(operator>>)の定義
istream& operator>>(istream& cin,Vec3d& vec){
    cin >> vec.x >> vec.y >> vec.z;
    return cin;
}
//==================================================================================================
int main(void)
{
    Vec3d   x, y;
    Vec3d   z;

    // 1．初期状態のx,yを表示する．
    std::cout << "1．初期状態のx,y: " << std::endl;
    std::cout << "x = " << x << ",  y = " << y << std::endl;

    // 2．x,yの成分を入力し，結果を表示する．
    std::cout << "\n2．x,yの成分を入力する．" << std::endl;
    std::cout << "x = ";
    std::cin >> x;
    std::cout << "y = ";
    std::cin >> y;

    std::cout << "\n成分入力後のx,y: " << std::endl;
    std::cout << "x = " << x << ",  y = " << y << std::endl;

    // 3．ベクトルの加算 z = x + yの結果を表示する．
    z = x + y;
    std::cout << "\n3．ベクトルの加算: " << std::endl;
    std::cout << "z = x + y = " << z << std::endl;


    // 4．全ベクトル(x,y,z)を表示する．
    std::cout << "\n4．全ベクトルx,y,z: " << std::endl;
    std::cout << "x = " << x << ",  y = " << y << ",  z = " << z << std::endl;

	return 0;
}


/* 実行結果 ========================================================================================
1．初期状態のx,y: 
x = (0,0,0),  y = (0,0,0)

2．x,yの成分を入力する．
x = 1 2 3
y = 4 5 6

成分入力後のx,y: 
x = (1,2,3),  y = (4,5,6)

3．ベクトルの加算: 
z = x + y = (5,7,9)

4．全ベクトルx,y,z: 
x = (1,2,3),  y = (4,5,6),  z = (5,7,9)
==================================================================================================*/
