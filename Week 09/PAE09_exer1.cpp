/* 2025年度 プログラミング応用演習 第9回 演習プログラム(1) - PAE09_exer1
====================================================================================================
■サンプルプログラム(1.2)の単方向連結リストに機能(メンバ関数)の追加・変更したプログラム
・リストが空か否かを調べる(empty関数)．空ならtrue，そうでなければfalseを返す．
・リストの先頭ノードを削除する(pop_front関数)．
・リストの末尾ノードを削除する(pop_back関数)．
・デストラクタをemptyとpop_frontを使って簡潔にする．
==================================================================================================*/
#include <iostream>

// 単方向連結リストクラスの定義
class SinglyLinkedList {
private:
    // 単方向連結リストのノードクラスの定義
    class Node {
    public:
        Node* next;    // 連結する次のノードのポインタ(アドレス)
        int   data;    // ノードが記憶するデータ

        // コンストラクタ：ノードの記憶するデータd(デフォルト値0)で初期化する．
        Node(int d = 0) : next(NULL), data(d) {}
    };

    // 先頭ノードを示すためのダミーノード
    Node* head;

public:
    // デフォルトコンストラクタ
    SinglyLinkedList(void) {
        head = new Node();
    }

    // デストラクタ：headを含めすべてのノードを破棄する．
    ~SinglyLinkedList() {
        // リストが空になるまで，先頭ノードを削除する．
        while (empty() == false) {
            pop_front();
        }

        // 全てのノードを削除したら，ダミーノードを削除する．
        delete head;
    }

    // リストの先頭にデータdを記憶するノードを追加する．
    void push_front(int d) {
        Node* new_node;      // 新しいノードのポインタ

        // 追加する新しいノードを生成する．
        new_node = new Node(d);

        // 新しいノードの次のノードは今まで先頭だったノード(ダミーノードの次のノード)にする．
        new_node->next = head->next;

        // ダミーノードの次のノードを新しいノードで置き換える．
        head->next = new_node;
    }

    // リストの末尾にデータdを記憶するノードを追加する．
    void push_back(int d) {
        Node* new_node;      // 新しいノードのポインタ
        Node* cur;           // 現在のノードのポインタ

        // 現在のノードとしてダミーノードを設定する．
        cur = head;

        // 追加する新しいノードを生成する．
        new_node = new Node(d);

        // 現在の末尾ノード(次のノードがNULLであるノード)を見つける．
        while (cur->next != NULL) {
            cur = cur->next;
        }

        // 現在の末尾ノードの次のノードを新しいノードで置き換える．
        cur->next = new_node;
    }

    // リストが空か否か調べる．空ならtrue，ダミー以外のノードがあればfalseを返す．
    bool empty(void) {
        if (head->next == NULL) {
            return true;  // 空なので true
        }
        else {
            return false; // 空ではないので false
        }
    }

    // リストの先頭ノードを削除する．
    void pop_front(void) {
        Node* del;       // 削除対象ノードのポインタ

        // リストが空なら終了する．
        if (empty() == true) {
            return;
        }
        del = head->next;
        head->next = del->next;
        delete del;
    }

    // リストの末尾ノードを削除する．
    void pop_back(void) {
        Node* del;       // 削除対象ノードのポインタ
        Node* cur;       // 現在のノードのポインタ

        // リストが空なら終了する．
        if (empty() == true) {
            return;
        }
        cur = head;
        while (cur->next->next != NULL) {
            cur = cur->next;
        }
        del = cur->next;
        cur->next = NULL;
        delete del;
    }

    // リスト内のノードが記憶するデータを先頭ノードから順次表示する．
    void print(void) {
        // 現在のノードとして先頭ノード(ダミーノードの次のノード)を設定する．
        Node* cur = head->next;

        // 最終ノードの次のノード(NULL値)になるまで繰り返す．
        while (cur != NULL) {
            std::cout << "Data = " << cur->data << std::endl;
            std::cout << "  This Addr. = " << cur << std::endl;
            std::cout << "  Next Addr. = " << cur->next << std::endl;

            // 現在のノードを現在のノードの次のノードに変更する．
            cur = cur->next;
        }
    }
};

//==================================================================================================
int main(void)
{
    SinglyLinkedList  ls;      // 単方向連結リストクラスのインスタンスを生成する．

    // ノードを追加していない状態で削除してもエラーにならないか確認する．
    ls.pop_front();
    ls.pop_back();

    // データとして1,2,3を記憶するノードをリストの先頭に順次追加する．
    ls.push_front(1);
    ls.push_front(2);
    ls.push_front(3);

    // データとして4を記憶するノードをリストの末尾に追加する．
    ls.push_back(4);

    // ノード追加後の全データを表示する．
    std::cout << "1．ノード追加後の全データ" << std::endl;
    ls.print();

    // 先頭ノード(Data = 3のノード)を削除する．
    ls.pop_front();

    // 末尾ノード(Data = 4のノード)を削除する．
    ls.pop_back();

    // ノード削除後の全データを表示する．
    std::cout << "\n2．ノード削除後の全データ" << std::endl;
    ls.print();

    return 0;
}


/* 実行結果 ========================================================================================
1．ノード追加後の全データ
Data = 3
  This Addr. = 0x1a636a11650
  Next Addr. = 0x1a636a11630
Data = 2
  This Addr. = 0x1a636a11630
  Next Addr. = 0x1a636a11610
Data = 1
  This Addr. = 0x1a636a11610
  Next Addr. = 0x1a636a11670
Data = 4
  This Addr. = 0x1a636a11670
  Next Addr. = 0

2．ノード削除後の全データ
Data = 2
  This Addr. = 0x1a636a11630
  Next Addr. = 0x1a636a11610
Data = 1
  This Addr. = 0x1a636a11610
  Next Addr. = 0
==================================================================================================*/