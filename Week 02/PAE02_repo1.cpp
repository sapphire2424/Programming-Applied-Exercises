/* 2025年度 プログラミング応用演習 第2回 課題プログラム(1) - PAE02_repo1
====================================================================================================
■ファイルから人物データを読み込んで，個々のBMI値，全員の年齢，身長，体重の平均を求めるプログラム
・データはPAE02_repo1db.txtから読み込む．
  1行が1人分のデータであり，各行はカンマ区切りで，"氏名,年齢,身長,体重"である．
・平均値を求め一人分のデータとして追加し，全員分をファイル名(PAE02_repo1new.txt)で保存する．
  平均値データの氏名は，"AVERAGE"とする．
  各行はカンマ区切りで，"氏名,年齢,身長,体重,BMI"である．
==================================================================================================*/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
//--------------------------------------------------------------------------------------------------
// 人物情報構造体
typedef struct humandata {
    std::string name; // 氏名
    int age; // 年齢
    float height; // 身長(m)
    float weight; // 体重(kg)
    float BMI; // BMI
} HumanData;

//--------------------------------------------------------------------------------------------------
// HumanDataの内容を表示する関数のプロトタイプ(実体はmainの後)
void show_human(std::vector<HumanData> d);
//==================================================================================================
int main(void)
{
    std::string filename; // ファイル名
    std::ifstream ifs; // 入力ファイルストリーム
    std::ofstream ofs; // 出力ファイルストリーム
    std::string line; // ファイルから読み込む文字列
    std::string val; // カンマで区切られたデータの文字列
    HumanData human; // 人物情報構造体
    HumanData ave; // 人物情報構造体(平均値用)

    std::stringstream sstrm; // 文字列をストリームとして使用するクラス(stringstream)
    std::vector<HumanData> db; // データベース(HumanDataの配列)

    //----------------------------------------------
    // ファイルからデータを読み込む．
    ifs.open("PAE02_repo1db.txt");

    // ファイルが開けたかチェック
    if (ifs.is_open() == false) { // 開けなかった場合
        std::cout << "Error: open" << std::endl; // エラー終了
        return -1;
    }

    // 1行ずつ読み込み，データベース(HumanData配列)に登録する．
    // 複数行のカンマ区切りデータの読み込みは，サンプルプログラム(1,3),(4,3)を参照のこと．
    getline(ifs, line);
    sstrm.str(line);
    getline(sstrm, val, ',');
    human.name = val;
    getline(sstrm, val, ',');
    human.age = stoi(val);
    getline(sstrm, val, ',');
    human.height = stof(val);
    getline(sstrm, val, ',');
    human.weight = stof(val);
    human.BMI = 0;
    db.push_back(human);
    sstrm.clear();
    while (getline(ifs, line)) {
        sstrm.str(line);
        getline(sstrm, val, ',');
        human.name = val;
        getline(sstrm, val, ',');
        human.age = stoi(val);
        getline(sstrm, val, ',');
        human.height = stof(val);
        getline(sstrm, val, ',');
        human.weight = stof(val);
        human.BMI = 0;
        db.push_back(human);
        sstrm.clear();
    }


    // ファイルを閉じる．
    ifs.close();

    // 読み込み確認表示
    std::cout << "(1) 読み込みデータ" << std::endl;
    show_human(db);

    //----------------------------------------------
    // 個々のMBI値と，全員の平均値を計算する．
    std::cout << "\n(2) BMI値" << std::endl;

    // 平均値用HumanDataを初期化する．
    ave.name = "AVERAGE";
    ave.age = 0.0;
    ave.height = 0.0;
    ave.weight = 0.0;
    ave.BMI = 0.0;

    for (int i = 0; i < db.size(); i++) { // db.size()は，dbに登録済みの人数を表す．
        // BMIの計算
        db[i].BMI = db[i].weight / db[i].height / db[i].height;
        cout << db[i].name << ":" << db[i].BMI << endl;

        // 平均値用に，各人の年齢，身長，体重，BMIを逐次加算する．
        ave.age += db[i].age;
        ave.height += db[i].height;
        ave.weight += db[i].weight;
        ave.BMI += db[i].BMI;
    }

    // 年齢，身長，体重，BMIの平均値を求め，データベースに保存する．
    ave.age = ave.age /db.size();
    ave.height = ave.height / db.size();
    ave.weight = ave.weight / db.size();
    ave.BMI = ave.BMI / db.size();
    db.push_back(ave);

    std::cout << "\n(3) 平均値追加後のデータ" << std::endl;
    show_human(db);

    //----------------------------------------------
    // 平均値を追加したデータを保存する．
    ofs.open("PAE02_repo1new.txt");
    for (int i = 0; i < db.size(); i++) {
        // 1人分のデータの書き出し
        ofs << db[i].name << "," << db[i].age << "," << db[i].height << "," << db[i].weight << ","<< db[i].BMI << endl;
    }

    // ファイルを閉じる．
    ofs.close();

    return 0;
}

// HumanDataの内容を表示する．
void show_human(std::vector<HumanData> d)
{
    std::vector<HumanData>::iterator itr; // HumanDataのベクトルの反復子
    for (itr = d.begin();itr != d.end();++itr) {
        cout << "NAME=\"" << itr->name << '"' << ",AGE=" << itr->age << ",HEIGHT=" << itr->height << ",WEIGHT=" << itr->weight << ",BMI=" << itr->BMI << endl;
    }
}


/* 実行結果 ========================================================================================

[表示内容]
(1) 読み込みデータ
NAME="Carl Cripps",AGE=29,HEIGHT=1.6134,WEIGHT=46.221,BMI=0
NAME="Jackson Hodson",AGE=28,HEIGHT=1.8699,WEIGHT=67.5559,BMI=0
NAME="Allen Hather",AGE=20,HEIGHT=1.5828,WEIGHT=77.0047,BMI=0
NAME="Nick Greenbury",AGE=20,HEIGHT=1.7559,WEIGHT=70.8325,BMI=0
NAME="Victor Hydon",AGE=26,HEIGHT=1.8941,WEIGHT=59.7896,BMI=0

(2) BMI値
Carl Cripps:17.7564
Jackson Hodson:19.3209
Allen Hather:30.7373
Nick Greenbury:22.9738
Victor Hydon:16.6656

(3) 平均値追加後のデータ
NAME="Carl Cripps",AGE=29,HEIGHT=1.6134,WEIGHT=46.221,BMI=17.7564
NAME="Jackson Hodson",AGE=28,HEIGHT=1.8699,WEIGHT=67.5559,BMI=19.3209
NAME="Allen Hather",AGE=20,HEIGHT=1.5828,WEIGHT=77.0047,BMI=30.7373
NAME="Nick Greenbury",AGE=20,HEIGHT=1.7559,WEIGHT=70.8325,BMI=22.9738
NAME="Victor Hydon",AGE=26,HEIGHT=1.8941,WEIGHT=59.7896,BMI=16.6656
NAME="AVERAGE",AGE=24,HEIGHT=1.74322,WEIGHT=64.2807,BMI=21.4908
[保存ファイルPAE02_repo1new.txtの内容]
Carl Cripps,29,1.6134,46.221,17.7564
Jackson Hodson,28,1.8699,67.5559,19.3209
Allen Hather,20,1.5828,77.0047,30.7373
Nick Greenbury,20,1.7559,70.8325,22.9738
Victor Hydon,26,1.8941,59.7896,16.6656
AVERAGE,24,1.74322,64.2807,21.4908

==================================================================================================*/ 