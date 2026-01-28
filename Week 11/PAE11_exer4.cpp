/* 2025年度 プログラミング応用演習 第10回 演習プログラム(4) - PAE10_exer4
====================================================================================================
■ランレングス圧縮されたデータ列を復元するプログラム
・復元する関数decodingを定義する．
==================================================================================================*/
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

//--------------------------------------------------------------------------------------------------
// ランレングス圧縮：データ列din(データサイズsin)を圧縮して，doutに格納する．
// return: データサイズ(バイト)
int encoding(const std::vector<uint8_t> &din, std::vector<uint8_t> &dout)
{
    char    cur;      // 現在のデータ(文字)
    int     cnt;      // 同一値連続回数

    // 最初のデータを現在のデータcurとし，その連続回数cntを1回とする．
    cur = din[0];
    cnt = 1;

    // 2個目(0から数えて1個目)から'\0'に至るまでデータを確認する．
    for(int i=1; i<din.size(); i++) {

        if(din[i] == cur) {     // 同じデータが連続している場合
            cnt++;      // 連続数をカウントする．
        } else {    // 連続が終わった場合
            // 現在のデータ及びその連続回数を出力データdoutの末尾に追加する．
            dout.push_back(cur);
            dout.push_back(cnt);

            // 現在のデータを登録し，連続回数を1とする．
            cur = din[i];
            cnt = 1;
        }
    }

	// 最後のデータ及びその連続回数を出力データdoutの末尾に追加する．
	dout.push_back(cur);
	dout.push_back(cnt);

    return dout.size();
}

//--------------------------------------------------------------------------------------------------
// ランレングス圧縮の復元：ランレングス圧縮されたデータdinを復元してdoutに格納する．
// return: データサイズ(バイト)
int decoding(const std::vector<uint8_t> &din, std::vector<uint8_t> &dout)
{
    char   cur;     // 現在の文字
    int    cnt;     // 同一値連続回数

    for(int i = 0; i < din.size(); i += 2) {
        cur = din[i];
        cnt = din[i+1];
        for(int j = 0; j < cnt; j++) {
            dout.push_back(cur);
        }
    }

    return dout.size();
}

//==================================================================================================
int main(void)
{
    // 圧縮前のデータの元となる文字列：細かく値が変化する場合と，同じ値が続いてる箇所がある場合
#if 1
    std::string  str = "aaabccddddddeeeebbbbggggggccccaaaeeeeddcccgbbdddaa";
#else
    std::string  str = "aaaaaaaaeeeeeeeccccccccccggggggggbbbbbbbbbbbdddddd";
#endif

    std::vector<uint8_t>    data_in(str.begin(), str.end());    // 圧縮前のデータ格納配列
    std::vector<uint8_t>    data_out;       // 圧縮後のデータ格納配列
    std::vector<uint8_t>    data_res;       // 復元後のデータ格納配列

    std::cout << "1. 圧縮前のデータ量: " << data_in.size() << std::endl;
    std::cout << "data_in :" << str << std::endl;

    // ランレングス圧縮
    encoding(data_in, data_out);

    std::cout << "\n2. 圧縮後のデータ量: " << data_out.size() << std::endl;
    for(int i=0; i<data_out.size(); i+=2) {
        // (int)：data_outがuint8_t(unsigned char)型なので，int型にキャストする必要がある．
        std::cout << "'" << data_out[i] << "' " << (int)data_out[i+1] << "個, ";
    }
    std::cout << std::endl;

    // ランレングス圧縮の復元
    decoding(data_out, data_res);
    std::cout << "\n3. 復元後のデータ量: " << data_res.size() << std::endl;
    std::cout << "data_res:" << std::string(data_res.begin(), data_res.end())  << std::endl;
    std::cout << "(data_in:" << str << ")" << std::endl;

    return 0;
}


/* 実行結果 ========================================================================================
1. 圧縮前のデータ量: 50
data_in :aaabccddddddeeeebbbbggggggccccaaaeeeeddcccgbbdddaa

2. 圧縮後のデータ量: 32
'a' 3個, 'b' 1個, 'c' 2個, 'd' 6個, 'e' 4個, 'b' 4個, 'g' 6個, 'c' 4個, 'a' 3個, 'e' 4個, 'd' 2個, 'c' 3個, 'g' 1個, 'b' 2個, 'd' 3個, 'a' 2個,

3. 復元後のデータ量: 50
data_res:aaabccddddddeeeebbbbggggggccccaaaeeeeddcccgbbdddaa
(data_in:aaabccddddddeeeebbbbggggggccccaaaeeeeddcccgbbdddaa)
==================================================================================================*/
