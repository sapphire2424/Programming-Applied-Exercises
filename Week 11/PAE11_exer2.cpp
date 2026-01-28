/* 2025年度 プログラミング応用演習 第10回 演習プログラム(2) - PAE10_exer2
====================================================================================================
■4ビット長データのビットパック，アンパックを実行するプログラム
・個々の要素が4ビット(0～15)で表せる入力データ列を，8ビット整数配列に詰め込む．
  - 入力データ列の要素数は16とする．
・ビットパックされたデータから，元のデータを復元する．
・サンプルプログラムのpackbit，unpackbitを参考に，関数pack4bitとunpack4bitを定義する．
==================================================================================================*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <bitset>

//--------------------------------------------------------------------------------------------------
// 入力データ列(in_array)をビットパックして出力バッファ(out_array)に格納する．
void pack4bit(const std::vector<uint8_t>& in_array, std::vector<uint8_t>& out_array)
{
    uint8_t   in_data = 0;      // 入力データ
    uint8_t   out_data = 0;     // 出力データ

    int   out_bit_idx = 7;      // 出力バッファ書き込みビット位置
    int   in_bit_idx;           // 入力データ列抽出ビット位置
    int   in_byte_idx;          // 入力データ列抽出要素番号

    for (in_byte_idx = 0; in_byte_idx < in_array.size(); in_byte_idx++) {

        // in_byte_idx番目の入力データの下位4ビットを抽出する．
        in_data = in_array[in_byte_idx] & 0x4F;

        // 入力データの下位4ビットを出力データにコピーする．
        for (in_bit_idx = 3; in_bit_idx >= 0; in_bit_idx--) {

            // 第in_bit_idxビットが1なら，出力データのout_bit_idxビット目を1にする．
            if (in_data & (1 << in_bit_idx)) {
                out_data |= (1 << out_bit_idx);
            }

            // 出力データの書き込みビット位置を-1する．
            out_bit_idx--;

            // 8ビット分出力データに書き込んだ場合
            if (out_bit_idx == -1) {
                out_array.push_back(out_data);      // 出力バッファの末尾に追加する．
                out_data = 0;
                out_bit_idx = 7;
            }
        }
    }

    // 最後の入力データが出力データの最後の要素に丁度8ビットで収まらない場合
    if (out_bit_idx < 7) {
        out_array.push_back(out_data);
    }
}

//--------------------------------------------------------------------------------------------------
// 入力データ列(in_array)をアンパックして出力バッファ(out_array)に格納する．
void unpack4bit(const std::vector<uint8_t>& in_array, std::vector<uint8_t>& out_array)
{
    uint8_t   in_data = 0;      // 出力データ
    uint8_t   out_data = 0;     // 入力データ

    int   out_bit_idx = 3;      // 出力配列書き込みビット位置
    int   in_bit_idx = 7;       // 入力データ列抽出ビット位置
    int   in_byte_idx;          // 入力データ列抽出要素番号

    for (in_byte_idx = 0; in_byte_idx < in_array.size(); ) {

        // in_byte_idx番目の入力データを抽出する．
        in_data = in_array[in_byte_idx];

        // 第in_bit_idxビットが1なら，出力データの第out_bit_idxビットを1にする．
        if (in_data & (1 << in_bit_idx)) {
            out_data |= (1 << out_bit_idx);
        }

        // 入出力データの次の書き込みビット位置を-1する．
        in_bit_idx--;
        out_bit_idx--;

        // 出力1バイト分（7ビット）がそろったら出力配列に追加
        if (out_bit_idx < 0) {
            out_array.push_back(out_data);
            out_data = 0;
            out_bit_idx = 3;
        }

        // 入力バイト1つ分を使い切ったら次へ
        if (in_bit_idx < 0) {
            in_byte_idx++;
            in_bit_idx = 7;
        }
    }

    // 端数ビットが残っていた場合は最後に追加
    if (out_bit_idx != 3 && in_bit_idx != 7) {
        out_array.push_back(out_data);
    }
}

//==================================================================================================
int main(void)
{
    std::vector<uint8_t>   input;       // 入力データ格納配列
    std::vector<uint8_t>   packed;      // 出力データ格納配列
    std::vector<uint8_t>   unpacked;    // 出力データ格納配列(アンパック用)

    std::bitset<8>   bt8;   // 8ビット2進数表記

    // 入力データ列を作成する．ここでは，0,1,2,3,...,13,14,15
    for (int i = 0; i < 16; i++) {
        input.push_back(i);
    }

    // 元のデータ列(文字列)を表示する．
    std::cout << "\n元のデータ列" << std::endl;
    for (int i = 0; i < input.size(); i++) {
        bt8 = input[i];
        std::cout << bt8 << " (" << (int)input[i] << ")" << std::endl;
    }

    // ビットパックを実行する．
    pack4bit(input, packed);

    // ビットパックしたデータ
    std::cout << "\n出力データ列" << std::endl;
    for (int i = 0; i < packed.size(); i++) {
        bt8 = packed[i];
        std::cout << bt8 << std::endl;
    }

    // ビットアンパックを実行する．
    unpack4bit(packed, unpacked);

    // 復元したデータ
    std::cout << "\n復元データ列" << std::endl;
    for (int i = 0; i < unpacked.size(); i++) {
        bt8 = unpacked[i];
        std::cout << bt8 << " (" << (int)unpacked[i] << ")" << std::endl;
    }

    return 0;
}


/* 実行結果 ========================================================================================
元のデータ列
00000000 (0)
00000001 (1)
00000010 (2)
00000011 (3)
00000100 (4)
00000101 (5)
00000110 (6)
00000111 (7)
00001000 (8)
00001001 (9)
00001010 (10)
00001011 (11)
00001100 (12)
00001101 (13)
00001110 (14)
00001111 (15)

出力データ列
00000001
00100011
01000101
01100111
10001001
10101011
11001101
11101111

復元データ列
00000000 (0)
00000001 (1)
00000010 (2)
00000011 (3)
00000100 (4)
00000101 (5)
00000110 (6)
00000111 (7)
00001000 (8)
00001001 (9)
00001010 (10)
00001011 (11)
00001100 (12)
00001101 (13)
00001110 (14)
00001111 (15)
==================================================================================================*/
