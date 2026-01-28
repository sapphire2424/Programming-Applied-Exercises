/* 2025年度 プログラミング応用演習 第3回 演習プログラム(3) - PAE03_exer3
====================================================================================================
■学生情報データベースへのデータ登録のプログラム
・学生データベース(vector<Student>)に情報を追加する関数を同名(addtodb)で2種類作成する．
  1．引数を{データベース，学生番号，氏名，入学年，GPA}とし，戻り値はvoid型とする．
  2．引数を{データベース，学生情報(Student)}とし，戻り値はvoid型とする．
・main側では，(1)～(6)のパターンでaddtodbを呼び出して学生データを登録し，結果を表示する．
==================================================================================================*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// 学生情報構造体
typedef struct student {
    int    id;            // 学生番号    
    string  name;    // 氏名
    int     year;         // 入学年
    float   gpa;          // GPA
} Student;

// 学生データベース(vector<Student>)に情報を追加する関数: addtodb
// 引数は，順に{データベースオブジェクト，学生番号，氏名，入学年，GPA}とし，戻り値はvoid型とする．
// デフォルト値は講義資料の実行結果例を参照すること．
void addtodb(vector<Student> &db,int id = 1000,string name = "NONAME",int year = 2022,float gpa = 0){
  Student s = {id,name,year,gpa};
  db.push_back(s);
}
// 学生データベース(vector<Student>)に情報を追加する関数: addtodb
// 引数は，順に{データベース，学生情報(Student)}とし，戻り値はvoid型とする．
void addtodb(vector<Student> &db,Student s){
  db.push_back(s);
}


int main (void)
{
    vector<Student>   db;      // 学生データベース
    Student   s = {1010, "Nick Greenbury", 2024, 2.43};     // 初期化済み学生データ

    // (1) 第2引数以降すべてをデフォルトとする． 
    addtodb(db);

    // 以下，(2)～(5)で指定する引数値は，講義資料の実行結果を参考にすること．

    // (2) 学生番号のみを指定する．
    addtodb(db,1001);

    // (3) 学生番号と氏名のみを指定する．
    addtodb(db,1002,"Carl Cripps");

    // (4) 学生番号，氏名，入学年を指定する．
    addtodb(db,1003,"Jackson Hodson",2023);

    // (5) 全てを指定する．
    addtodb(db,1004,"Allen Hather",2023,3.2);

    // (6) 初期化済みの学生データを指定する．
    addtodb(db,s);

    // データベースの全学生情報を表示する．
    cout << "全登録データ" << endl;
    for (int i = 0;i < db.size();i++){
      cout << "NAME=\"" << db[i].name <<"\",ID=" << db[i].id << ",YEAR=" << db[i].year << ",GPA=" << db[i].gpa << endl;
    }
    return 0;
}


/* 実行結果 ========================================================================================
全登録データ
NAME="NONAME",ID=1000,YEAR=2022,GPA=0
NAME="NONAME",ID=1001,YEAR=2022,GPA=0
NAME="Carl Cripps",ID=1002,YEAR=2022,GPA=0
NAME="Jackson Hodson",ID=1003,YEAR=2023,GPA=0
NAME="Allen Hather",ID=1004,YEAR=2023,GPA=3.2
NAME="Nick Greenbury",ID=1010,YEAR=2024,GPA=2.43
==================================================================================================*/
