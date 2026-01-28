/* 2025年度 プログラミング応用演習 第9回 演習プログラム(3) - PAE09_exer3
====================================================================================================
■サンプルプログラム(3.1)のQueueクラスに機能(メンバ関数)の追加・変更したプログラム
・追加できる要素の数を制限できるようにenqueue関数を変更する．
  - 制限数で初期化するためのコンストラクタを追加する．
  - 制限を超えて追加しようとした場合は，例外("overflow")を送出する．
・要素数が0の時に要素を取り出そうとした場合に，例外("underflow")を送出するように，dequeue関数を変更
  する．
==================================================================================================*/
#include <iostream>
#include <list>

//--------------------------------------------------------------------------------------------------
// キューのテンプレートクラスの定義
template <typename T>
class Queue {
private:
    std::list<T>   ls;       // 連結リスト(実際にデータを記憶するオブジェクト)
    int   max_elem;          // 追加できる要素の最大数

public:
    // コンストラクタ
    Queue(void) {}
    Queue(int m) : max_elem(m) {}

    // 値がvの要素を追加する．
    void enqueue(T v) {
        // 要素数が既にmax_elemなら，例外"overflow"を送出する．
        if ((int)ls.size() >= max_elem) {
                    throw "overflow";
                }
        ls.push_back(v);
    }

    // 先頭要素を取り出す．
    T dequeue(void) {
        T   r;

        // 連結リストが空なら，例外"underflow"を送出する．
        if (ls.empty()) {
            throw "underflow";
        }

        r = ls.front();    // 先頭要素の値を取得する(ノードはそのまま)．
        ls.pop_front();    // 先頭要素を取り出す(ノードは削除される)．

        return r;
    }

    // スタックに記憶されたデータ数を返す．
    int size(void) {
        return (int)ls.size();
    }
    // キューに記憶されている全要素(連結リストのノードの記憶値)を表示する．
    void print(void) {
        typename std::list<T>::iterator  ite;
        for(ite=ls.begin(); ite!=ls.end(); ite++) {
            std::cout << "[" << *ite << "]";
        }

        std::cout << std::endl;
    }
};

//==================================================================================================
int main(void)
{
    Queue<int>   queue(2);     // int型キュークラスのインスタンスを生成する．
    int   x;

    // キューに要素を追加する．
    std::cout << "1. キューに要素を追加する．" << std::endl;
    try {
        for(int i=0; i<8; i++) {
            x = (i+1)*10;
            queue.enqueue(x);
            std::cout << "  Enqueue " << x << " => ";
            queue.print();
        }
    } catch(const char *e) {
        std::cout << "Error: " << e << std::endl;
    }
    std::cout << "要素数 = " << queue.size() << std::endl;

    // キューの要素を取り出す．
    std::cout << "\n2. キューの要素を取り出す．" << std::endl;
    try {
        for(int i=0; i<8; i++) {
            x = queue.dequeue();
            std::cout << "  Dequeue " << x << " <= ";
            queue.print();
        }
    } catch(const char *e) {
        std::cout << "Error: " << e << std::endl;
    }
    std::cout << "要素数 = " << queue.size() << std::endl;
    return 0;
}


/* 実行結果 ========================================================================================

[要素数を4に制限した場合]

1. キューに要素を追加する．
  Enqueue 10 => [10]
  Enqueue 20 => [10][20]
  Enqueue 30 => [10][20][30]
  Enqueue 40 => [10][20][30][40]
Error: overflow
要素数 = 4

2. キューの要素を取り出す．
  Dequeue 10 <= [20][30][40]
  Dequeue 20 <= [30][40]
  Dequeue 30 <= [40]
  Dequeue 40 <=
Error: underflow
要素数 = 0

----------------------------------------------------------------------------------------------------
[要素数を2に制限した場合]

1. キューに要素を追加する．
  Enqueue 10 => [10]
  Enqueue 20 => [10][20]
Error: overflow
要素数 = 2

2. キューの要素を取り出す．
  Dequeue 10 <= [20]
  Dequeue 20 <=
Error: underflow
要素数 = 0

==================================================================================================*/
