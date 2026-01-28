/* 2025年度 プログラミング応用演習 第3回 課題レポートプログラム(1) - PAE03_repo1
====================================================================================================
■学生情報データベースの検索プログラム
・検索キーの型の違いによるオーバーロードを利用して，同じ関数名の検索関数を実現する．
・同名の検索関数(search)を定義する．検索キーは以下のとおりとする．
  「氏名」「入学年」「GPA(下限指定)」「GPA(下限と上限指定)」「休学か否か」
==================================================================================================*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 学生情報構造体
typedef struct student {
    int    id;            // 学生番号    
    std::string  name;    // 氏名
    int     year;         // 入学年
    float   gpa;          // GPA
    bool    leave;        // 休学(休学ならtrue，そうでなければfalse)
} Student;

// 学生情報データベースの検索結果srの内容を表示する関数のプロトタイプ
void showResults(const std::vector<Student> &sr);


// 学生情報データベース(db)から検索する関数群
// 関数名はすべて，searchとする．
// 第1引数：学生情報データベース(std::vector)
// 第2引数以降：1個以上の検索キー
// 戻り値：検索結果の学生情報配列(std::vector)
// 氏名(name)による検索：同姓同名に対応する．
vector<Student> search(vector<Student> db,const char* name){
    vector<Student> results;
    for (int i = 0;i < db.size();i++){
        if(db[i].name == name){
            results.push_back(db[i]);
        }
    }
    return results;
}

// 入学年(year)による検索
vector<Student> search(vector<Student> db,int year){
    vector<Student> results;
    for (int i = 0;i < db.size();i++){
        if(db[i].year == year){
            results.push_back(db[i]);
        } else{
            continue;
        }
    }
    return results;
}
// GPA(gpa)による検索：gpa以上を検索対象とする．
vector<Student> search(vector<Student> db,double gpa_lower){
    vector<Student> results;
    for (int i = 0;i < db.size();i++){
        if(db[i].gpa >= gpa_lower){
            results.push_back(db[i]);
        } else{
            continue;
        }
    }
    return results;
}
// GPA(gpa)による検索：gpa_l以上，gpa_u未満を検索対象とする．
vector<Student> search(vector<Student> db,float gpa_lower,float gpa_upper){
    vector<Student> results;
    for (int i = 0;i < db.size();i++){
        if((db[i].gpa >= gpa_lower)&&(db[i].gpa < gpa_upper)){
            results.push_back(db[i]);
        } else{
            continue;
        }
    }
    return results;
}
// 休学(leave)による検索
vector<Student> search(vector<Student> db,bool leave){
    vector<Student> results;
    for (int i = 0;i < db.size();i++){
        if(db[i].leave == leave){
            results.push_back(db[i]);
        } else{
            continue;
        }
    }
    return results;
}
//==================================================================================================
int main(void)
{
    // 学生情報データベース：下記のとおり登録済みとする．
    std::vector<Student>  database = {
        {2001, "Anthony Trevathan", 2022, 2.24, false}, 
        {2002, "Eliot Dale", 2022, 3.89, true}, 
        {3001, "Jarod Gompers", 2023, 3.77, false}, 
        {3002, "Floyd Fleetwood", 2023, 2.81, false}, 
        {3003, "Nathanael Mitchison", 2023, 1.62, false}, 
        {4001, "Matt Alvarez", 2024, 3.28, false}, 
        {5001, "Ulysses Edwardes", 2025, 2.68, false}, 
        {5002, "Evan Bywaters", 2025, 3.61, true}, 
        {5003, "Eliot Dale", 2025, 1.99, false}, 
        {5004, "Arron Cartpenter", 2025, 3.95, false}, 
    };

    // 検索結果を記憶する配列
    std::vector<Student>  results;

    // 氏名により検索し，その結果を表示する．
    std::cout << "1．氏名(Eliot Dale)による検索結果" << std::endl;
    results = search(database, "Eliot Dale");
    showResults(results);

    // 入学年により検索し，その結果を表示する．
    std::cout << "\n2．2023年入学生による検索結果" << std::endl;
    results = search(database, 2023);
    showResults(results);

    // GPA(下限)により検索し，その結果を表示する．
    std::cout << "\n3．GPA 3.8以上の検索結果" << std::endl;
    results = search(database, 3.8);
    showResults(results);

    // GPA(下限～上限)により検索し，その結果を表示する．
    std::cout << "\n4．GPA 2.5以上3.5未満による検索結果" << std::endl;
    results = search(database, 2.5, 3.5);
    showResults(results);

    // 休学中か否かにより検索し，その結果を表示する．
    std::cout << "\n5．休学中による検索結果" << std::endl;
    results = search(database, true);
    showResults(results);

    // 入学年により検索し，その結果を表示する(結果0の場合)．
    std::cout << "\n6．2021年入学生による検索結果" << std::endl;
    results = search(database, 2021);
    showResults(results);

	return 0;
}

// 学生情報データベースの検索結果srの内容を表示する．
void showResults(const std::vector<Student> &sr) {
    // 検索結果が0だった場合
    if(sr.size() == 0) {
        std::cout << "Not found." << std::endl;
        return;
    }

    // 検索結果すべての学生情報を表示する．
    for(int i=0; i<sr.size(); i++) {
        std::cout << "ID: " << sr[i].id
                  << ", NAME: \"" << sr[i].name
                  << "\", YEAR: " << sr[i].year
                  << ", GPA: " << sr[i].gpa
                  << ", LEAVE: " << sr[i].leave << std::endl;
    }
}


/* 実行結果 ========================================================================================
1．氏名(Eliot Dale)による検索結果
ID: 2002, NAME: "Eliot Dale", YEAR: 2022, GPA: 3.89, LEAVE: 1
ID: 5003, NAME: "Eliot Dale", YEAR: 2025, GPA: 1.99, LEAVE: 0

2．2023年入学生による検索結果
ID: 3001, NAME: "Jarod Gompers", YEAR: 2023, GPA: 3.77, LEAVE: 0
ID: 3002, NAME: "Floyd Fleetwood", YEAR: 2023, GPA: 2.81, LEAVE: 0
ID: 3003, NAME: "Nathanael Mitchison", YEAR: 2023, GPA: 1.62, LEAVE: 0

3．GPA 3.8以上の検索結果
ID: 2002, NAME: "Eliot Dale", YEAR: 2022, GPA: 3.89, LEAVE: 1
ID: 5004, NAME: "Arron Cartpenter", YEAR: 2025, GPA: 3.95, LEAVE: 0

4．GPA 2.5以上3.5未満による検索結果
ID: 3002, NAME: "Floyd Fleetwood", YEAR: 2023, GPA: 2.81, LEAVE: 0
ID: 4001, NAME: "Matt Alvarez", YEAR: 2024, GPA: 3.28, LEAVE: 0
ID: 5001, NAME: "Ulysses Edwardes", YEAR: 2025, GPA: 2.68, LEAVE: 0

5．休学中による検索結果
ID: 2002, NAME: "Eliot Dale", YEAR: 2022, GPA: 3.89, LEAVE: 1
ID: 5002, NAME: "Evan Bywaters", YEAR: 2025, GPA: 3.61, LEAVE: 1

6．2021年入学生による検索結果
Not found.
==================================================================================================*/
