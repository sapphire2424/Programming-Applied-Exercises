/* 2025年度 プログラミング応用演習 第7回 演習プログラム(4) - PAE07_exer4
====================================================================================================
■3種類の手法で3種類の関数を定積分するプログラム
・講義資料の「モンテカルロ法による定積分(1)」のページを参考にintegral_mc1関数を定義する．
・講義資料の「モンテカルロ法による定積分(2)」のページを参考にintegral_mc2関数を定義する．
・積分手法の関数と被積分関数を引数で指定する積分実行関数integralを定義する．
  mainでの積分に関する関数呼び出しは，integralのみとする．
==================================================================================================*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

//------------------------------------------------------------------------------
// 0～1の一様分布乱数
double urnd(void)
{
    return (double)rand() / RAND_MAX;
}

//------------------------------------------------------------------------------
// シンプソンの公式により，被積分関数fの区間[a,b]の定積分を計算する．サンプルプログラムで提示済み．
// 終了判定(収束判定)の基準を十分小さい値tcとする．
double integral_simpson(double (*f)(double), double a, double b, double tc)
{
    double   d = tc + 1.0;  // 積分値比較用
    double   s0 = 0.0;      // 積分値格納用(1つ前)
    double   s1 = 1.0;      // 積分値格納用
    int      n = 0;         // 等分数(実際の等分数は2n)
    double   h;             // 等分された区間幅
    double   y_odd;         // 奇数番目の分点における関数値
    double   y_even;        // 奇数番目・偶数番目の分点における関数値
    double   y_0, y_2n;     // 積分区間の両端における被積分関数の値
    double   xi;            // 分点

    // 積分区間の両端a,bにおける被積分関数の値
    y_0 = f(a);
    y_2n = f(b);

    // nを増やしつつ，積分Sを求める．
    do {
        n++;
        s0 = s1;
        y_even = 0.0;
        y_odd = 0.0;

        // nから等分された区間の幅を求める … 式(1)
        h = (b - a) / (2.0 * n);

        // 奇数番目分点(xi)における被積分関数値の和 … 式(3)
        for (int i = 1; i <= 2 * n - 1; i += 2) {
            xi = a + i * h;       // 等分された区間の幅 … 式(2)
            y_odd = y_odd + f(xi);
        }

        // 偶数番目分点(xi)における被積分関数値の和 … 式(4)
        for (int i = 2; i <= 2 * n - 2; i += 2) {
            xi = a + i * h;
            y_even = y_even + f(xi);
        }

        // 積分Sの近似値 … 式(5)
        s1 = (h / 3.0) * (y_0 + y_2n + 4.0 * y_odd + 2.0 * y_even);

        if (n > 1) {
            d = abs(s0 - s1);     // s0とs1の差の絶対値 … (6)
        }
    } while (d >= tc);   // 収束判定 … (6)

    return s1;
}

//------------------------------------------------------------------------------
// 単純モンテカルロ法により定積分を計算する．
// 全部の点と，y=f(x)の下側にある点の比によって求める．
double integral_mc1(double(*f)(double), double a, double b, double tc)
{
    double  fa, fb;     // 積分区間の端点a,bにおける非積分関数値
    double  xi, yi;     // 一様分布乱数による(x,y)座標
    double  ymax;       // fa, fbの大きい方
    double  int_f;      // fの定積分結果
    int     S = 0;      // 乱数の点(x,y)がy=f(x)の下の点である数

    // 積分区間の両端a,bにおける関数値を求める．
    fa = a;
    fb = b;

    // fa, fbの大きい方を抽出する．
    if (a < b)ymax = b;
    else if (a >= b)ymax = a;




    // tc回の繰り返し試行
    for (int i = 0; i < tc; i++) {
        // 積分区間[a,b]の一様分布乱数を生成する．
        xi = a + b * urnd();

        // 区間[0,ymax]の一様分布乱数を生成する．
        yi = ymax * urnd();

        // xiにおける関数値f(xi)より乱数yiが小さければSを増やす．
        if (f(xi) > yi) {
            S++;
        }
    }

    // f(x)の下の部分の面積を求める．

    int_f = (b - a) * ymax * S / tc;
    return int_f;
}

//------------------------------------------------------------------------------
// 平均値によるモンテカルロ法により定積分を計算する．
// 平均定積分の値を求める a<=x<=b を乱数として，f(x)の平均値を積分値とする．
double integral_mc2(double(*f)(double), double a, double b, double tc)
{
    double  xi;             // 区間[a,b]の一様分布乱数
    double  f_all = 0;      // f(xi)の合計
    double  f_ave = 0;      // f(xi)の平均
    double  int_f;          // fの定積分結果

    // tc回の繰り返し試行
    for (int i = 0; i < tc; i++) {
        // 積分区間[a,b]の乱数を生成する．
        xi = a + b * urnd();

        // xiにおける関数値を順次加算する．
        f_all += f(xi);
    }

    // f(xi)の平均値を求める．
    f_ave = f(xi) / tc;

    // 平均に積分区間の幅(b-a)を掛けて面積を求める．
    int_f = (b-a)*f_all/tc;

    return int_f;
}

//------------------------------------------------------------------------------
// 被積分関数：f1(x) = e^(-x)
double f1(double x)
{
    return std::exp(-x);
}

// f1(x)の積分
double f1i(double x)
{
    return -std::exp(-x);
}

//------------------------------------------------------------------------------
// 被積分関数：f2(x) = x
double f2(double x)
{
    return x;
}

// f2の積分
double f2i(double x)
{
    return x * x / 2.0;
}

//------------------------------------------------------------------------------
// 被積分関数：f3(x) = 1/(1+x^2)
double f3(double x)
{
    return 1.0 / (1.0 + x * x);
}

// f3の積分
double f3i(double x)
{
    return atan(x);
}

//==================================================================================================
// 積分実行関数：integral
// 積分手法(関数)imにより，被積分関数fを区間[a,b]で定積分する．
// tcは積分手法における終了条件となる値である．
// imは，integral_simpson,integral_mc1,integral_mc2のような関数のポインタである．
// fは，f1, f2, f3のような関数のポインタである．
double integral(double (*im)(double (*)(double), double, double, double), double (*f)(double),
    double a, double b, double tc)
{
    return im(f, a, b, tc);
}

//==================================================================================================
int main(void)
{
    double    e = 0.0000000001;   // 収束判定定数
    int       MAX_TRIAL = 10000000;      // ランダムな点の数
    double    a, b;           // 積分区間の端点
    double    intval;         // 積分値
    clock_t   t0, t1, tt;     // 処理開始時刻[ms]，処理終了時刻[ms]，処理時間[ms]

    srand((unsigned)time(NULL));

    // 積分区間の指定
    a = 0;
    b = 1;

    //------------------------------------------------
    // f1の定積分
    std::cout << "f1の定積分" << std::endl;
    std::cout << "理論値    = " << f1i(b) - f1i(a) << std::endl;

    // シンプソンの公式による定積分
    t0 = clock();
    intval = integral(integral_simpson, f1, a, b, e);
    t1 = clock();
    std::cout << "シンプソンの公式 = " << intval << ",  t=" << t1 - t0 << " [ms]" << std::endl;

    // 単純モンテカルロ法による定積分
    t0 = clock();
    intval = integral(integral_mc1, f1, a, b, MAX_TRIAL);
    t1 = clock();
    std::cout << "単純モンテカルロ = " << intval << ",  t=" << t1 - t0 << " [ms]" << std::endl;

    // 平均値モンテカルロ法による定積分
    t0 = clock();
    intval = integral(integral_mc2, f1, a, b, MAX_TRIAL);
    t1 = clock();
    std::cout << "平均モンテカルロ = " << intval << ",  t=" << t1 - t0 << " [ms]" << std::endl;

    //------------------------------------------------
    // f2の定積分
    std::cout << "\nf2の定積分" << std::endl;
    std::cout << "理論値    = " << f2i(b) - f2i(a) << std::endl;

    // シンプソンの公式による定積分
    t0 = clock();
    intval = integral(integral_simpson, f2, a, b, e);
    t1 = clock();
    std::cout << "シンプソンの公式 = " << intval << ",  t=" << t1 - t0 << " [ms]" << std::endl;

    // 単純モンテカルロ法による定積分
    t0 = clock();
    intval = integral(integral_mc1, f2, a, b, MAX_TRIAL);
    t1 = clock();
    std::cout << "単純モンテカルロ = " << intval << ",  t=" << t1 - t0 << " [ms]" << std::endl;

    // 平均値モンテカルロ法による定積分
    t0 = clock();
    intval = integral(integral_mc2, f2, a, b, MAX_TRIAL);
    t1 = clock();
    std::cout << "平均モンテカルロ = " << intval << ",  t=" << t1 - t0 << " [ms]" << std::endl;

    //------------------------------------------------
    // f3の定積分
    std::cout << "\nf3の定積分" << std::endl;
    std::cout << "理論値    = " << f3i(b) - f3i(a) << std::endl;

    // シンプソンの公式による定積分
    t0 = clock();
    intval = integral(integral_simpson, f3, a, b, e);
    t1 = clock();
    std::cout << "シンプソンの公式 = " << intval << ",  t=" << t1 - t0 << " [ms]" << std::endl;

    // 単純モンテカルロ法による定積分
    t0 = clock();
    intval = integral(integral_mc1, f3, a, b, MAX_TRIAL);
    t1 = clock();
    std::cout << "単純モンテカルロ = " << intval << ",  t=" << t1 - t0 << " [ms]" << std::endl;

    // 平均値モンテカルロ法による定積分
    t0 = clock();
    intval = integral(integral_mc2, f3, a, b, MAX_TRIAL);
    t1 = clock();
    std::cout << "平均モンテカルロ = " << intval << ",  t=" << t1 - t0 << " [ms]" << std::endl;

    return 0;
}


/* 実行結果 ========================================================================================
f1の定積分
理論値    = 0.632121
シンプソンの公式 = 0.632121,  t=0 [ms]
単純モンテカルロ = 0.632236,  t=450 [ms]
平均モンテカルロ = 0.632157,  t=209 [ms]

f2の定積分
理論値    = 0.5
シンプソンの公式 = 0.5,  t=0 [ms]
単純モンテカルロ = 0.500027,  t=410 [ms]
平均モンテカルロ = 0.499856,  t=190 [ms]

f3の定積分
理論値    = 0.785398
シンプソンの公式 = 0.785398,  t=0 [ms]
単純モンテカルロ = 0.785398,  t=390 [ms]
平均モンテカルロ = 0.785478,  t=193 [ms]
==================================================================================================*/
