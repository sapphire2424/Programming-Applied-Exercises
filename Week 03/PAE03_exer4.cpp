/* 2025年度 プログラミング応用演習 第3回 演習プログラム(4) - PAE03_exer4
====================================================================================================
■3種類の型の配列(vector)の最大値・最小値とその要素番号を求めるプログラム
・データ型は，int, float, stringとする．
  文字列(string)は，辞書順で前が小，後が大で比較できる．
==================================================================================================*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// 配列(vector)に記憶されたデータから，最大値，最小値及びそれらの要素番号（インデックス）を求め
// て返す関数minmaxidを関数テンプレートとして定義する．
// 引数は{配列，最小値，最大値，最小値要素番号，最大値要素番号}．戻り値はvoid型とする．
template <typename T>
void minmaxid(vector<T> &data,T &min,T &max,int &min_idx,int &max_idx){
  max = data[0];
  min = data[0];
  max_idx = 0;
  min_idx = 0;
  for (int i = 1;i<data.size();i++){
    if (data[i]>max){
      max = data[i]; 
      max_idx = i;
    } else if (data[i] < min){
      min = data[i]; 
      min_idx = i;
    }
  }
}
int main (void)
{
    // 3種類の型による配列(vector)
    vector<int>   datai = { 2,  3, -8,  7, 0,  1, -5,  9,  6,  4};
    vector<float>   dataf = {9.2, 0.1, 1.6, 7.3, 3.3, 5.9, -2.2, 6.1, -8.8, 4.3};
    vector<string>   datas = {"taro", "hanako", "nobuo", "yoshio", "akira", "shin"};

    // 最大値・最小値となる要素番号
    int    max_idx, min_idx;

    // 3種類の型の最大値・最小値を記憶する変数
    int    max_valuei, min_valuei;
    float  max_valuef, min_valuef;
    string  max_values, min_values;

    // (1) int型配列から最大値・最小値及びその要素番号を求めて表示する．
    minmaxid(datai,min_valuei,max_valuei,min_idx,max_idx);
    cout << "配列dataiの最大値は" << max_idx << "番目の要素" << max_valuei << endl << "最小値は" << min_idx << "番目の要素" << min_valuei << endl;
    // (2) float型配列から最大値・最小値及びその要素番号を求めて表示する．
    minmaxid(dataf,min_valuef,max_valuef,min_idx,max_idx);
    cout << "配列datafの最大値は" << max_idx << "番目の要素" << max_valuef << endl << "最小値は" << min_idx << "番目の要素" << min_valuef << endl;
    // (3) string型配列から最大値・最小値及びその要素番号を求めて表示する．
    minmaxid(datas,min_values,max_values,min_idx,max_idx);
    cout << "配列datasの最大値は" << max_idx << "番目の要素" << max_values << endl << "最小値は" << min_idx << "番目の要素" << min_values << endl;
    return 0;
}


/* 実行結果 ========================================================================================
配列dataiの最大値は7番目の要素9
最小値は2番目の要素-8
配列datafの最大値は0番目の要素9.2
最小値は8番目の要素-8.8
配列datasの最大値は3番目の要素yoshio
最小値は4番目の要素akira
==================================================================================================*/
