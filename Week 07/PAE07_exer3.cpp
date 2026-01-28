/* 2025年度 プログラミング応用演習 第7回 演習プログラム(3) - PAE07_exer3
====================================================================================================
■ヒューマンクラスのデータベースをランダムで生成してファイルに保存するプログラム
・ここのヒューマンクラスは，第4回 サンプルプログラム(2.1)のものを改変している．
・氏名のみ確定しているものとする．
・年齢，身長，体重を乱数で生成して登録する．
・氏名，年齢，身長，体重，BMIをファイル(PAE07_exer3.csv)に保存する．
  ※実行結果には，保存したファイルの内容を貼り付けること．
・各自の情報は，メンバ変数をファイルストリームに書き込むメンバ関数(write_members)によって処理する．
  ※クラス定義の[追加]部分にメンバ関数を定義すること．
==================================================================================================*/
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
using namespace std;
// ヒューマンクラス(Human)の定義
class Human {
private:
    int     age;         // 年齢
    float   height;      // 身長(m)
    float   weight;      // 体重(kg)
    float   BMI;         // BMI = weight/(height*height)

public:
    std::string  name;   // 名前

    // コンストラクタ
    Human(void) : name("NONAME"), age(-1),  height(-1.0), weight(-1.0), BMI(-1.0) {}
    Human(const std::string &n, int a, float h, float w) : name(n) {
        setAge(a);
        setHeight(h);
        setWeight(w);
    }

    //------------------------------------------------
    // 非公開メンバ設定用関数
    void setHeight(float h) {
        if(h > 0.0 && h < 5.0) {
            height = h;
			calcBMI();
        }
    }

    void setWeight(float w) {
        if(w > 0.0 && w < 300.0) {
            weight = w;
			calcBMI();
        }
    }

    void setAge(int a) {
        if(a >= 0 && a <= 200) {
            age = a;
        }
    }

    //------------------------------------------------
    // 非公開メンバ取得用関数
    float getHeight(void) { return height; }
    float getWeight(void) { return weight; }
    float getBMI(void) { return BMI; }
    int   getAge(void) { return age; }

    //------------------------------------------------
    // BMIを計算する．
    void calcBMI(void) {
        BMI = weight/(height*height);
    }

    // メンバ変数の値を表示する．
    void show_members(void) {
        std::cout << "name=\"" << name << "\"";
        std::cout << ", Age=" << age << ", Height=" << height << ", Weight=" << weight;
        std::cout << ", BMI=" << BMI << std::endl;
    }

    // [追加] 氏名,年齢,身長,体重,BMIをファイル(ストリーム)ofsに保存する関数：write_members
    void write_members(ofstream &ofs){
        ofs << name << "," << age << "," << height << "," << weight << "," << BMI << endl;

    }
    // デストラクタ
    ~Human() {}
};

//==================================================================================================
int main(void)
{
    // 乱数関係クラスのオブジェクトの生成
    std::random_device   dev;
    std::mt19937    gen(dev());

    // 乱数分布クラスオブジェクトの生成
    // ①年齢(歳)：20～60の整数一様分布乱数
    uniform_int_distribution<int> age(20,60);

    // ②身長(m)：平均1.63，標準偏差0.17の正規分布乱数
    normal_distribution<float> height(1.63,0.17);

    // ③体重(kg)：平均62.7，標準偏差17.2の正規分布乱数
    normal_distribution<float> weight(62.7,17.2);

    // データベース登録者の氏名
    std::vector<std::string>   names = {
		"Andy Barth", "Ansel Morphew", "Brion Boon", "Ciaran Ace", "Davey Druitt", "Dillon Fish",
        "Edmond Lumley", "Everette Barr", "Gillian Lowson", "Greg Lipson", "Hamelin Shown",
        "Hugo Parrot", "Isaac Agnew", "Jaxtyn Amell", "Jimmie Thurman", "Kay McKellen", "Loyd Geary",
        "Lyndon Dawson", "Norris Kearns", "Randolph Chauncey", "Seward Emptage", "Terrance Irvine",
        "Tim Richmond", "Victor Clayton"
    };

    Human    human;     // ヒューマンクラスのインスタンス
    std::vector<Human>  db;   // データベース用配列
    std::ofstream       ofs("PAE07_exer3.csv");     // ファイル出力ストリームを生成し，ファイルを開く．

    // 身長，体重，年齢を乱数で設定して，データベース登録する．
    for(int i=0; i<names.size(); i++) {
        // ヒューマンクラスのインスタンスを生成する．
        human = Human();

        // humanのメンバ変数に値を設定する．nameは，配列namesの値を順に使用する．
        human.name = names[i];
        human.setAge(age(gen));
        human.setHeight(height(gen));
        human.setWeight(weight(gen));

        // データベース(配列)に登録する．
        db.push_back(human);
    }

    // データベース(db)の全登録情報をファイル(ofs)に保存する．
    for(int i=0; i<names.size(); i++) {
        db[i].write_members(ofs);
    }
    // ファイルを閉じる．
    ofs.close();

    return 0;
}


/* 実行結果 ========================================================================================

["PAE07_exer3.csv"の内容]
Andy Barth,34,1.74799,89.9872,29.4513
Ansel Morphew,29,1.55443,47.8316,19.7959
Brion Boon,48,1.52694,97.402,41.7756
Ciaran Ace,47,1.66355,48.9785,17.6985
Davey Druitt,44,1.6759,84.7388,30.1708
Dillon Fish,37,1.56833,75.4843,30.6888
Edmond Lumley,49,1.54433,77.8331,32.6351
Everette Barr,58,1.57022,34.2531,13.8925
Gillian Lowson,48,1.75949,67.9399,21.9459
Greg Lipson,58,1.71229,64.4608,21.9858
Hamelin Shown,43,1.56696,50.2941,20.4834
Hugo Parrot,27,1.82279,72.0905,21.6973
Isaac Agnew,29,1.65206,72.3473,26.5075
Jaxtyn Amell,39,1.59678,66.794,26.1967
Jimmie Thurman,47,1.61325,100.655,38.6751
Kay McKellen,37,1.74248,82.1252,27.0484
Loyd Geary,59,2.038,64.925,15.6315
Lyndon Dawson,40,1.64793,40.9686,15.0861
Norris Kearns,44,1.43716,58.6698,28.4057
Randolph Chauncey,50,1.60706,29.3946,11.3815
Seward Emptage,37,1.58036,82.5205,33.0407
Terrance Irvine,50,1.47968,52.8766,24.1505
Tim Richmond,23,1.7536,54.2782,17.6508
Victor Clayton,43,1.84979,42.9229,12.5442

==================================================================================================*/
