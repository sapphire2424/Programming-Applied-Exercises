/* 2025年度 プログラミング応用演習 第5回 演習プログラム(2) - PAE05_exer2
====================================================================================================
■std::stringクラスの派生クラスを使ったプログラム
・派生クラスをmystringとする．
・演算子「文字列(mystring)*整数」「整数*文字列(mystring)」の定義
  - 同じ文字列をn個並べた文字列を生成して返す．
==================================================================================================*/
#include <iostream>
#include <string>

// 拡張文字列クラスの定義
class mystring : public std::string {
public:
#if 0
    // コンストラクタ
    mystring(void) : std::string() {}       // デフォルト
    mystring(const std::string &s) : std::string(s) {}      // 文字列クラスで初期化
    mystring(const char *s) : std::string(s) {}             // 文字列リテラルで初期化
#else
    // これでstd::stringのコンストラクタを引き継げる(上のように書く必要がない)．
    using std::string::string;
#endif

    // 演算子 文字列(mystring)*整数(n) の定義：同じ文字列をn個並べた文字列を生成して返す．
    mystring operator*(int n) const {
        mystring   r;   // 同じ文字列をn個並べた文字列の格納先

        for(int i=0; i<n; i++) {
            r += *this;     // r.append(*this); でもOK
        }

        return r;
    }

//--------------------------------------------------------------------------------------------------
    // mystringのメンバを使わないのでfriendにする必要はないが，mystringとの関係を明示している．
    // 文字列sをn個並べる．
    friend mystring operator*(int n, const mystring &s);
};

// 文字列sをn個並べる演算子関数：整数*文字列(mystring)
mystring operator*(int n, const mystring &s)
{
    return s*n;     // クラス定義されているoperator*を使う．
}

//==================================================================================================
int main(void)
{
    mystring   a = "Chiba";
    mystring   b, c;

    b = a*3;    // 演算子*による「文字列(mystring)*整数」
    c = 5*a;    // 演算子*による「整数*文字列(mystring)」

    std::cout << "a=\"" << a << "\"" << std::endl;
    std::cout << "b=\"" << b << "\"" << std::endl;
    std::cout << "c=\"" << c << "\"" << std::endl;

    return 0;
}


/* 実行結果 ========================================================================================

a="Chiba"
b="ChibaChibaChiba"
c="ChibaChibaChibaChibaChiba"

==================================================================================================*/
