/* 2025年度 プログラミング応用演習 第12回 課題レポートプログラム(1) - PAE12_repo1
====================================================================================================
■ファイルを読み込み，データの出現頻度を求め，頻度の高い順に並べて表示するプログラム
・データ種cとその出現頻度fのペアを表現するDataFrequency構造体を用いる．
  - fの大小に従って，{c,f}をまとめて順番を入れ替える必要があるため．
・文字の範囲(' '(0x20)～'~'(0x7E))で，頻度が0でないもののみ表示する．
==================================================================================================*/
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>

//--------------------------------------------------------------------------------------------------
// データの出現頻度構造体
typedef struct data_frequency {
    char    c;      // データの種類(0～255)
    int     f;      // 文字cの出現頻度
} DataFrequency;

//--------------------------------------------------------------------------------------------------
// 並べ替え用比較関数：DataFrequencyのfを比較する．
int compare_func(const void *a, const void *b)
{
    DataFrequency *dA = (DataFrequency *)a;
    DataFrequency *dB = (DataFrequency *)b;
    return dB->f - dA->f;
}

//--------------------------------------------------------------------------------------------------
// ファイル(filename)を読み込み，配列bufに格納する．
// return: true(読み込み成功)/false(読み込み失敗)
bool read_file(const std::string &filename, std::vector<uint8_t> &buf)
{
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) return false;

    ifs.seekg(0, std::ios::end);
    size_t size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    buf.resize(size);
    ifs.read((char*)buf.data(), size);





























    return true;
}
//==================================================================================================
int main(void)
{
    std::vector<uint8_t>   input;         // 入力データ格納配列
    DataFrequency          hist[256];     // データと頻度の配列

    char    c;
    int     f;

	// ファイルを読み込み，成否を判定する．
	if(read_file(".\\PAE11_samp31d.txt", input) == false) {
		std::cout << "Error: ファイルの読み込み失敗" << std::endl;
		return -1;
	}

    // データ値と出現頻度(DataFrequency配列)を初期化する．
    for(int i=0; i<256; i++) {
        hist[i].c = (char)i;
        hist[i].f = 0;
    }

    // 1バイトずつ取り出して，出現頻度を求める．
    for(size_t i=0; i<input.size(); i++) {
        hist[input[i]].f++;
    }


    // 出現頻度の高い順に並べ替える．
    qsort(hist, 256, sizeof(DataFrequency), compare_func);

    // 結果を表示する．
    std::cout << std::showbase;      // 16進表記の数値の前に"0X"を付ける指定
    std::cout << std::uppercase;     // 16進表記のアルファベットを大文字とする指定

    for(int i=0; i<256; i++) {
        c = hist[i].c;
        f = hist[i].f;
        // 表示範囲かつ頻度が0でない場合のみ表示
        if (c >= 0x20 && c <= 0x7E && f > 0) {
             std::cout << "'" << c << "'(" << std::hex << (int)(unsigned char)c << "): " << std::dec << f << std::endl;
        }
    }

    return 0;
}


/* 実行結果 ========================================================================================
' '(0X20): 174
'e'(0X65): 100
'o'(0X6F): 78
'a'(0X61): 64
'n'(0X6E): 61
's'(0X73): 59
'i'(0X69): 57
't'(0X74): 57
'r'(0X72): 47
'm'(0X6D): 44
'c'(0X63): 38
'l'(0X6C): 37
'd'(0X64): 37
'f'(0X66): 35
'h'(0X68): 35
'u'(0X75): 28
'p'(0X70): 23
'g'(0X67): 20
'b'(0X62): 18
'y'(0X79): 18
'.'(0X2E): 10
'w'(0X77): 9
'v'(0X76): 7
'H'(0X48): 7
','(0X2C): 7
'T'(0X54): 4
'A'(0X41): 3
'M'(0X4D): 3
'I'(0X49): 2
'-'(0X2D): 2
'D'(0X44): 2
'C'(0X43): 2
')'(0X29): 2
'"'(0X22): 2
'('(0X28): 2
'''(0X27): 2
'2'(0X32): 1
'9'(0X39): 1
'x'(0X78): 1
'q'(0X71): 1
'1'(0X31): 1
'/'(0X2F): 1
'S'(0X53): 1
'R'(0X52): 1
'5'(0X35): 1
==================================================================================================*/
