/* 2025年度 プログラミング応用演習 第5回 演習プログラム(4) - PAE05_exer4
====================================================================================================
■第4回 サンプルプログラム(4.3)のComplexNumberクラスを，テンプレートクラス化する．
・実行結果が，同サンプルと同じになるようにすること．
・friend関数(operator*)をテンプレート関数化するにあたり， templateの宣言も含めて関数の定義であること
  に注意すること．
==================================================================================================*/
#include <iostream>
using namespace std;
// テンプレート複素数クラスの定義
template <typename T>
class ComplexNumber {
  private:
    T a,b;
  public:
    ComplexNumber(void) : a(T(0)),b(T(0)) {}
    ComplexNumber(T x,T y) : a(x),b(y){}
    void print(void){
      cout << "Re=" << a << ",Im=" << b << endl;
    }
    ComplexNumber<T> operator+(const ComplexNumber<T> &y)const{
      ComplexNumber<T> z;
      z.a = this->a + y.a;
      z.b = this->b + y.b;
      return z;
    }
    ComplexNumber<T> operator*(const T &y)const{
      ComplexNumber<T> z;
      z.a = this->a * y;
      z.b = this->b * y;
      return z;
    }
    template <typename U>
    friend ComplexNumber<double> operator*(const double &x, const ComplexNumber &y);
};

// 演算子'*'：<実数>*<複素数>のフレンド関数の実体
ComplexNumber<double> operator*(const double &x, const ComplexNumber<double> &y)
{
    return y * x;
}
//==================================================================================================
int main(void)
{
    // 以下，第4回 サンプルプログラム(4.3)のままなので，必要に応じて書き換えること．

    // 複素数クラスオブエジェクトのインスタンス(x,y,z)の生成
    ComplexNumber<double>   x(5.0, 2.0);    // x = 5.0 + 2.0i
    ComplexNumber<double>   y(0.5, 0.2);    // y = 0.5 + 0.2i
    ComplexNumber<double>   z;

    // 初期状態の値の表示
    std::cout << "x: ";
    x.print();
    std::cout << "y: ";
    y.print();
    std::cout << "z: ";
    z.print();

    // xとyの加算
    z = x + y;
    std::cout << "z = x + y: ";
    z.print();

    // xの実数倍
    z = x*10.0;
    std::cout << "z = x*10.0: ";
    z.print();

    // xの実数倍(実数を前に書く場合)
    z = 10.0*x;
    std::cout << "z = 10.0*x: ";
    z.print();

    return 0;
}


/* 実行結果 ========================================================================================
x: Re=5,Im=2
y: Re=0.5,Im=0.2
z: Re=0,Im=0
z = x + y: Re=5.5,Im=2.2
z = x*10.0: Re=50,Im=20
z = 10.0*x: Re=50,Im=20
==================================================================================================*/
