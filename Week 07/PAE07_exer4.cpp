/* 2025年度 プログラミング応用演習 第7回 演習プログラム(4) - PAE07_exer4
====================================================================================================
■モンスターのパーティを編成するプログラム
・サンプルプログラム(2.3)を下記のように変更する．
  - 3種族とも最低1体はパーティに含んだうえで，8体以下のパーティを編成する．
  - モンスターのパラメータの初期値は，乱数で決める．ただし，大小関係は下記のとおりとする．
    life: Ork > Goblin > Slime
    atk : Ork > Goblin > Slime
    dfn : Goblin > Ork > Slime
    agl : Slime > Goblin > Ork
==================================================================================================*/
//
// サンプルプログラム(2.3)の"#include <iostream>"の行以降を貼り付けて書き直す．
//
#include <iostream>
#include <vector>
#include <string>
#include <random>

//------------------------------------------------
// モンスターの基底クラス(Monster)の定義
class Monster {
protected:
    int    life;      // 生命力(初期値：10～99)
    int    atk;       // 攻撃力(初期値：10～99)
    int    dfn;       // 防御力(初期値：10～99)
    int    agl;       // 敏捷力(初期値：10～99)

public:
    std::string   race;     // 種族名

    // コンストラクタ
    Monster(void) : life(0), atk(0), dfn(0), agl(0), race("") {}

    // パラメータを設定する(仮想関数)．
    virtual void setParameters(std::mt19937  &gen) = 0;

    // パラメータを表示する．
    void showParameter(void) {
        std::cout << race << std::endl;
        std::cout << "  Life=" << life << ", Atk=" << atk;
        std::cout << ", Dfn=" << dfn << ", Agl=" << agl << std::endl;
    }
};

//------------------------------------------------
// スライムクラスの定義
class Slime : public Monster {
public:
    // コンストラクタ
    Slime(void) {race = "Slime";}

    // パラメータを設定する．
    void setParameters(std::mt19937 &gen) {
		std::uniform_int_distribution<> rnd(10, 39);    // パラメータの乱数
    std::uniform_int_distribution<> agl_rnd(70,99);
        life = rnd(gen);
        atk  = rnd(gen);
        dfn  = rnd(gen);
        agl  = agl_rnd(gen);
    }
};

//------------------------------------------------
// ゴブリンクラスの定義
class Goblin : public Monster {
public:
    // コンストラクタ
    Goblin(void) {race = "Goblin";}

    // パラメータを設定する．
    void setParameters(std::mt19937 &gen) {
		std::uniform_int_distribution<>    rnd(40, 69);    // パラメータの乱数
    std::uniform_int_distribution<> dfn_rnd(70,99);
        life = rnd(gen);
        atk  = rnd(gen);
        dfn  = dfn_rnd(gen);
        agl  = rnd(gen);
    }
};

//------------------------------------------------
// オーククラスの定義
class Ork : public Monster {
public:
    Ork(void) {race = "Ork";}

    void setParameters(std::mt19937 &gen) {
		std::uniform_int_distribution<>    rnd(70, 99);    // パラメータの乱数
    std::uniform_int_distribution<> agl_rnd(10, 39);
    std::uniform_int_distribution<> dfn_rnd(40, 69);
        life = rnd(gen);
        atk  = rnd(gen);
        dfn  = dfn_rnd(gen);
        agl  = agl_rnd(gen);
    }
};

//------------------------------------------------
// モンスターのパーティを作成する．
std::vector<Monster*> createMonsterParty(void)
{
    std::vector<Monster*>   m;
    std::random_device      dev;
    std::mt19937            gen(dev());

    std::uniform_int_distribution<>     n_rnd(3, 8);     // モンスター数の乱数(3～8)
    std::uniform_int_distribution<>     r_rnd(0, 2);     // モンスター種別の乱数

    Monster  *p;      // モンスタークラスインスタンスのポインタ
    int      N;       // モンスター数
    int      r;
    
    N = n_rnd(gen);   // 3～8の乱数でモンスター数を決める．

    p = new Slime;
    p->setParameters(gen);
    m.push_back(p);
    p = new Ork;
    p->setParameters(gen);
    m.push_back(p);
    p = new Goblin;
    p->setParameters(gen);
    m.push_back(p);

    for(int i=0; i<N-3; i++) {
        r = r_rnd(gen);     // モンスター種別の選択

        if(r == 0) {
            p = new Slime();        // スライムを生成
			p->setParameters(gen);
        } else if(r == 1) {
            p = new Goblin();       // ゴブリンを生成
			p->setParameters(gen);
        } else if(r == 2) {
            p = new Ork();          // オークを生成
			p->setParameters(gen);
        }

        m.push_back(p);
    }

    return m;
}

//==================================================================================================
int main(void)
{
    // モンスタークラスのポインタの配列
    std::vector<Monster*>    monsters;

    monsters = createMonsterParty();

    std::cout << monsters.size() << " monsters appeared." << std::endl;
    for(int i=0; i<monsters.size(); i++) {
        std::cout << i+1 << ".";
        monsters[i]->showParameter();
    }

    return 0;
}

/* 実行結果 ========================================================================================
4 monsters appeared.
1.Slime
  Life=36, Atk=10, Dfn=14, Agl=81
2.Ork
  Life=87, Atk=76, Dfn=57, Agl=36
3.Goblin
  Life=43, Atk=40, Dfn=98, Agl=56
4.Ork
  Life=91, Atk=96, Dfn=45, Agl=39
==================================================================================================*/
