/* 2025年度 プログラミング応用演習 第9回 演習プログラム(4) - PAE09_exer4
====================================================================================================
■サンプルプログラム(3.2)のStackクラスに機能(メンバ関数)の追加・変更したプログラム
・スタックに記憶されている要素の数を返すsize関数を追加する．
・追加できる要素の数を5個に制限できるようにpush関数を変更する．
  - 制限を超えて追加しようとした場合は，例外("overflow")を送出する．
・要素数が0の時に要素を取り出そうとした場合は，例外("underflow")を送出するように，pop関数を変更する．
==================================================================================================*/
#include <iostream>
#include <list>

// スタックのテンプレートクラスの定義
template <typename T>
class Stack {
private:
   std::list<T>   ls;       // 連結リスト(実際にデータを記憶するオブジェクト)

public:
    // コンストラクタ
    Stack(void) {}

    // 値がvの要素を追加する．
void push(T v) {
        // 要素数が5個以上なら，例外"overflow"を送出する．
        if ((int)ls.size() >= 5) {
            throw "overflow";
        }


		ls.push_back(v);
    }

    // 先頭要素を取り出す．
T pop(void) {
        T   r;

        // 連結リストが空なら，例外"underflow"を送出する．
        if (ls.empty()) {
            throw "underflow";
        }


        r = ls.back();     // 末尾要素の値を取得する(ノードはそのまま)．
        ls.pop_back();     // 末尾要素を取り出す(ノードは削除される)．

        return r;
    }

    // スタックに記憶されたデータ数を返す．
int size(void) {
        return (int)ls.size();
    }

    // 末尾要素(最後に追加した要素)の値を取得する． // 実行結果に合わせて追加
    T top(void) {
        return ls.back();
    }

    // スタックに記憶されている全要素(連結リストのノードの記憶値)を表示する．
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
    Stack<int>   stack;     // int型スタッククラスのインスタンスを生成する．
    int   x;

    // スタックに要素を追加する．
std::cout << "1. スタックに要素を追加する．" << std::endl;
    try {
		for(int i=0; i<10; i++) {
			x = (i+1)*10;
			stack.push(x);
std::cout << " Push " << x << " => ";
			stack.print();
}
    } catch(const char *e) {
        std::cout << "Error: " << e << std::endl;
}

    std::cout << "要素数 = " << stack.size() << std::endl;
    std::cout << "末尾要素の値 = " << stack.top() << std::endl; // 実行結果に合わせて追加

    // スタックの要素を取り出す．
    std::cout << "\n2. スタックの要素を取り出す．" << std::endl;
    try {
		for(int i=0; i<10; i++) {
			x = stack.pop();
std::cout << " Pop  " << x << " <= ";
			stack.print();
}
    } catch(const char *e) {
        std::cout << "Error: " << e << std::endl;
}

    std::cout << "要素数 = " << stack.size() << std::endl;

    return 0;
}


/* 実行結果 ========================================================================================

1. スタックに要素を追加する。
 Push 10 => [10]
 Push 20 => [10][20]
 Push 30 => [10][20][30]
 Push 40 => [10][20][30][40]
 Push 50 => [10][20][30][40][50]
 Error: overflow
要素数 = 5
末尾要素の値 = 50

2. スタックの要素を取り出す。
 Pop  50 <= [10][20][30][40]
 Pop  40 <= [10][20][30]
 Pop  30 <= [10][20]
 Pop  20 <= [10]
 Pop  10 <= 
 Error: underflow
要素数 = 0

==================================================================================================*/