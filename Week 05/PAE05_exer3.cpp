/* 2025年度 プログラミング応用演習 第5回 演習プログラム(2) - PAE05_exer2
====================================================================================================
■モンスタークラスの派生クラス(Slime,Goblin,Ork)を戦闘させるプログラム
・Monsterクラスは抽象クラスとする．
・メンバ関数仕様
  attack関数を下記のように定義する．
    攻撃相手を引数とするように書き換えよ(現状はvoid)．
    自身の攻撃力を引数にして，攻撃相手のdefence関数を呼び出す．
  defence関数を下記のように定義する．
    受けた攻撃力を引数とするように書き換えよ(現状はvoid)．
    受けた攻撃力を減衰させた値を，自身の生命力から引く．
  治癒関数 void cure(void) を定義する．
・オブジェクトは，vectorを用いて配列で扱う．
・各処理(A)～(E)において，各オブジェクトの処理をループを用いて実行する．
==================================================================================================*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//------------------------------------------------
// モンスターの基底クラス(Monster)の定義
class Monster {
protected:
    int     life;        // 生命力

    std::string   name;

public:
    Monster(void) : life(100) {}

    // 攻撃する(攻撃力は派生先で決める)．
    virtual void attack(Monster& m) = 0;

    // 防御する(防御力は派生先で決める)．
    virtual void defence(int a) = 0;

    // 治癒する(回復量は派生先で決める)．
    virtual void cure(void) = 0;

    // 生命力を表示する．
    void print(void) {
        std::cout << name << ": Life = " << life << std::endl;
    }
};

//------------------------------------------------
// スライムクラスの定義
class Slime : public Monster {
public:
    Slime(void) {
        name = "Slime";
    }

    // 攻撃する(攻撃力20)．
    void attack(Monster& m) {
		// 攻撃対象mの防御を実行する．
        m.defence(20);
    }

    // 防御する(攻撃力がそのままダメージとなる)．
    void defence(int a) {
        // ダメージ分の生命力を減らす
        life -= a;
    }

    // 治癒する(生命力5増加)．
    void cure(void) {
        // 治癒(生命力を増やす)．
        life += 5;
    }
};

//------------------------------------------------
// ゴブリンクラスの定義
class Goblin : public Monster {
public:
    Goblin(void) {
        name = "Goblin";
    }

    // 攻撃する(攻撃力30)．
    void attack(Monster& m) {
        m.defence(30);
    }

    // 防御する(攻撃力の1/2がダメージとなる)．
    void defence(int a) {
        life -= a/2;
    }

    // 治癒する．
    void cure(void) {
        life += 10;
    }
};

//------------------------------------------------
// オーククラスの定義
class Ork : public Monster {
public:
    Ork(void) {
        name = "Ork";
    }

    // 攻撃する(攻撃力80)．
    void attack(Monster& m) {
        m.defence(80);
    }

    // 防御する(攻撃力の1/10がダメージとなる)．
    void defence(int a) {
        life -= a/10;
    }

    // 治癒する(完全回復)．
    void cure(void) {
        life = 100;
    }
};

//==================================================================================================
int main(void)
{
    // Monsterクラスのポインタの配列(vector)を作成
    std::vector<Monster*>   monsters;

    Monster *m;

    // 各モンスター派生クラスオブジェクトのインスタンスを配列に追加する．
    m = new Slime();
    monsters.push_back(m);
    m = new Goblin();
    monsters.push_back(m);
    m = new Ork();
    monsters.push_back(m);

    // (A) 初期状態の生命力を表示する．
    std::cout << "1. 初期状態の生命力" << std::endl;
    for (int i = 0;i < monsters.size();i++){
        monsters[i]->print();
    }
    // (B) 攻撃する．
    // monsters[0]がmonsters[1]を，monster[1]がmonsters[2]を，monsters[2]がmonsters[0]を攻撃する．
    for (int i = 0;i < monsters.size();i++){
        if(i == monsters.size()-1){
            monsters[i]->attack(*monsters[0]);
        } else {
            monsters[i]->attack(*monsters[i+1]);
        }
    }
    // (C) 攻撃後の生命力を表示する．
    std::cout << std::endl << "2. 攻撃後の生命力" << std::endl;
    for (int i = 0;i < monsters.size();i++){
        monsters[i]->print();
    }
    // (D) 治癒する．
    for (int i = 0;i < monsters.size();i++){
        monsters[i]->cure();
    }
    // (E) 治癒後の生命力を表示する．
    std::cout << std::endl << "3. 治癒後の生命力" << std::endl;
    for (int i = 0;i < monsters.size();i++){
        monsters[i]->print();
    }
    return 0;
}


/* 実行結果 ========================================================================================
1. 初期状態の生命力
Slime: Life = 100
Goblin: Life = 100
Ork: Life = 100

2. 攻撃後の生命力
Slime: Life = 20
Goblin: Life = 90
Ork: Life = 97

3. 治癒後の生命力
Slime: Life = 25
Goblin: Life = 100
Ork: Life = 100
==================================================================================================*/
