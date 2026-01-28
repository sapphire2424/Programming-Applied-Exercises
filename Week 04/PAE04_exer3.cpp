/* 2025年度 プログラミング応用演習 第4回 演習プログラム(3) - PAE04_exer3
====================================================================================================
■3次元ベクトルクラスに，下記のメンバ関数・演算子を追加する．
・それぞれ[追加]で始まるコメント行の次の行から追加する．
・norm：ベクトルの大きさ(長さ)を求める．
・inner：ベクトルの内積を求める．
・cross：ベクトルの外積を求める．
・operator*：ベクトルのスカラ倍を求める(演算子*)．
  <ベクトル>×<実数>，<実数>×<ベクトル>，両方に対応すること．
・operator*=：ベクトルのスカラ倍を求める(複合代入演算子*=)．
==================================================================================================*/
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
// 3次元ベクトルクラスの定義
class Vec3d {
private:
    float   x, y, z;

public:
    // コンストラクタ
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
    Vec3d operator+(const Vec3d& v) const {
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
        return !(*this == v);
    }

    // [追加] ベクトルの大きさ(長さ)を求める．
    float norm(){
        return sqrt(x*x+y*y+z*z);

    }
    // [追加] ベクトルの内積を求める．
    float inner(const Vec3d other){
        return x*other.x+y*other.y+z*other.z;

    }
    // [追加] ベクトルの外積を求める．
    Vec3d cross(const Vec3d other){
        float i = y*other.z-z*other.y;
        float j = z*other.x-x*other.z;
        float k = x*other.y-y*other.x;
        return Vec3d(i,j,k);


    }
    // [追加] 算術演算子(*)
    Vec3d operator*(const float a){
        Vec3d new_vec;
        new_vec.x = a*x;
        new_vec.y = a*y;
        new_vec.z = a*z;
        return new_vec;
    }
    // [追加] 複合代入演算子(*=)
    Vec3d operator*=(const float a){
        x *= a;
        y *= a;
        z *= a;
        return Vec3d(x,y,z);
    }
    // パラメータ表示
    void print(void) {
        std::cout << "(x,y,z) = (" << x << "," << y << "," << z << ")" << std::endl;
    }

    // [追加] 算術演算子(*)：<実数>×<ベクトル>のフレンド宣言
    friend Vec3d operator*(const float a, const Vec3d copy_vec);
};

// [追加] 算術演算子(*)：<実数>×<ベクトル>の実体
Vec3d operator*(const float a, const Vec3d copy_vec){
    Vec3d new_vec;
    new_vec.x = copy_vec.x * a;
    new_vec.y = copy_vec.y * a;
    new_vec.z = copy_vec.z * a;
    return new_vec;

}
//==================================================================================================
int main(void)
{
    // 3次元ベクトルクラスオブジェクトのインスタンス生成
    Vec3d   vec1(1, 1, 1);
    Vec3d   vec2(1, 2, 3);
    Vec3d   vec;

    // 初期パラメータの表示する．
    std::cout << "--------------------" << std::endl;
    std::cout << "初期パラメータ" << std::endl;
    std::cout << "vec1 = ";
    vec1.print();
    std::cout << "vec2 = ";
    vec2.print();

    // ベクトルの大きさを求めて表示する．
    std::cout << "--------------------" << std::endl;
    std::cout << "ベクトルの大きさ" << std::endl;
    std::cout << "|vec1| = " << vec1.norm() << std::endl;
    std::cout << "|vec2| = " << vec2.norm() << std::endl;

    // ベクトルの内積を求めて表示する．
    std::cout << "--------------------" << std::endl;
    std::cout << "ベクトルの内積" << std::endl;
    std::cout << "vec1・vec2 = " << vec1.inner(vec2) << std::endl;

    // ベクトルの外積を求めて表示する．
    std::cout << "--------------------" << std::endl;
    std::cout << "ベクトルの外積" << std::endl;
    vec = vec1.cross(vec2);
    //std::cout << "vec1×vec2 = (" << vec.x << "," << vec.y << "," << vec.z << ")" << std::endl;
    std::cout << "vec1×vec2 = ";
    vec.print();

    // ベクトルのスカラ倍(<ベクトル>×<実数>)のベクトルを求めて表示する．
    std::cout << "--------------------" << std::endl;
    std::cout << "ベクトルのスカラ倍" << std::endl;
    vec = vec1*3.0;
    std::cout << "vec = vec1×3 = ";
    vec.print();

    // ベクトルのスカラ倍(<実数>×<ベクトル>)のベクトルを求めて表示する．
    std::cout << "--------------------" << std::endl;
    std::cout << "ベクトルのスカラ倍" << std::endl;
    vec = 4.0*vec2;
    std::cout << "vec = 4×vec1 = ";
    vec.print();

    // ベクトルのスカラ倍の複合代入演算を実行し結果を表示する．
    std::cout << "--------------------" << std::endl;
    std::cout << "ベクトルのスカラ倍の複合代入演算" << std::endl;
    vec1 *= 5.0;
    std::cout << "vec1 = ";
    vec1.print();

    return 0;
}


/* 実行結果 ========================================================================================
--------------------
初期パラメータ
vec1 = (x,y,z) = (1,1,1)
vec2 = (x,y,z) = (1,2,3)
--------------------
ベクトルの大きさ
|vec1| = 1.73205
|vec2| = 3.74166
--------------------
ベクトルの内積
vec1・vec2 = 6
--------------------
ベクトルの外積
vec1×vec2 = (x,y,z) = (1,-2,1)
--------------------
ベクトルのスカラ倍
vec = vec1×3 = (x,y,z) = (3,3,3)
--------------------
ベクトルのスカラ倍
vec = 4×vec1 = (x,y,z) = (4,8,12)
--------------------
ベクトルのスカラ倍の複合代入演算
vec1 = (x,y,z) = (5,5,5)
==================================================================================================*/
