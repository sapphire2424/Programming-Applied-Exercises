/* 2025年度 プログラミング応用演習 第10回 演習プログラム(3) - PAE10_exer3
====================================================================================================
■ASCIIデータのビットパック，アンパックのプログラム
・テキストデータ(PAE10_data.txt)を読み込んで，ビットパックしてファイル(PAE10_out.bpk)に保存する．
・ファイル(PAE10_out.bpk)を読み込んで，アンパックしてファイル(PAE10_out.txt)に保存する．
・packbit, unpackbit関数は，サンプルプログラム(1.2)に記載されているものを使用する．
==================================================================================================*/
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//--------------------------------------------------------------------------------------------------
// 関数プロトタイプ宣言 (関数本体はmainの後に記述)
void packbit(const std::vector<uint8_t> &in_array, std::vector<uint8_t> &out_array);
void unpackbit(const std::vector<uint8_t> &in_array, std::vector<uint8_t> &out_array);

//--------------------------------------------------------------------------------------------------
// ファイル(filename)を読み込み，配列bufに格納する．
// return: true(読み込み成功)/false(読み込み失敗)
bool read_file(const std::string &filename, std::vector<uint8_t> &buf)
{
    // ファイル入力ストリームの定義
    std::ifstream   ifs;

    // ファイル(filenameをバイナリ形式(std::ios::binary)で開いて，成否を確認する．
    ifs.open(filename, std::ios::binary);

    if(ifs.is_open() == false) {
        return false;
    }

    // ファイルの内容を読み込む．
    int size;
    ifs.seekg(0, std::ios::end);
    size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    buf.resize(size);

    // ファイルから格納先(buf)にデータを読み込む．
    ifs.read((char*)buf.data(), size);


    // ファイルを閉じる．
    ifs.close();

    return true;
}

//--------------------------------------------------------------------------------------------------
// 配列bufのデータをファイル(filename)に書き込む．
// return: true(書き込み成功)/false(書き込み失敗)
bool write_file(const std::string &filename, std::vector<uint8_t> &buf)
{
    // ファイル出力ストリームの定義
    std::ofstream   ofs;
    
    // ファイル(filenameをバイナリ形式(std::ios::binary)で開いて，成否を確認する．
    ofs.open(filename, std::ios::binary);

    if(ofs.is_open() == false) {
        return false;
    }

    // データを書き込む．
    ofs.write((char*)buf.data(), buf.size());

    // ファイルを閉じる．
    ofs.close();

    return true;
}

//==================================================================================================
int main(void)
{
    std::vector<uint8_t>   input;     // 入力データ格納配列
    std::vector<uint8_t>   output;    // 出力データ格納配列

	//------------------------------------------------
	// テキストファイルのデータをビットパックして別のファイルに保存する．

	// ファイルを読み込み，成否を判定する．
	if(read_file(".\\PAE10_data.txt", input) == false) {
		std::cout << "Error: txtファイルの読み込み失敗" << std::endl;
		return -1;
	}

	std::cout << "PAE10_data.txtを読み込みました(" << input.size() << "バイト)．" << std::endl;

	// ビットパックする．
	packbit(input, output);

	// ファイルを保存し，成否を判定する．
	if(write_file("PAE10_out.bpk", output) == false) {
		std::cout << "Error: bpkファイルの書き込み失敗" << std::endl;
		return -1;
	}

	std::cout << "PAE10_out.bpkに保存しました(" << output.size() << "バイト)．" << std::endl;

    // 配列をクリアする．
    input.clear();
    output.clear();

	//------------------------------------------------
	// 保存したファイルからデータを読み込み，アンパックして別のファイルにテキストとして保存する．

	// ファイルを読み込み，成否を判定する．
	if(read_file(".\\PAE10_out.bpk", input) == false) {
		std::cout << "Error: bpkファイルの読み込み失敗" << std::endl;
		return -1;
	}

	std::cout << "PAE10_out.bpkを読み込みました(" << input.size() << "バイト)．" << std::endl;

	// アンパックする．
	unpackbit(input, output);

	// ファイルを保存し，成否を判定する．
	if(write_file("PAE10_out.txt", output) == false) {
		std::cout << "Error: failed to write txt file." << std::endl;
		return -1;
	}

	std::cout << "PAE10_out.txtに保存しました(" << output.size() << "バイト)．" << std::endl;
    
    return 0;
}

//--------------------------------------------------------------------------------------------------
// 入力データ列(in_array)をビットパックして出力バッファ(out_array)に格納する．
void packbit(const std::vector<uint8_t> &in_array, std::vector<uint8_t> &out_array)
{
    uint8_t   in_data = 0;      // 入力データ
    uint8_t   out_data = 0;     // 出力データ

    int   out_bit_idx = 7;      // 出力バッファ書き込みビット位置
    int   in_bit_idx;           // 入力データ列抽出ビット位置
    int   in_byte_idx;          // 入力データ列抽出要素番号

    for(in_byte_idx=0; in_byte_idx<in_array.size(); in_byte_idx++) {

        // in_byte_idx番目の入力データの下位7ビットを抽出する．
        in_data = in_array[in_byte_idx] & 0x7F;

        // 入力データの下位7ビットを出力データにコピーする．
        for(in_bit_idx=6; in_bit_idx>=0; in_bit_idx--) {

            // 第in_bit_idxビットが1なら，出力データのout_bit_idxビット目を1にする．
            if(in_data & (1 << in_bit_idx)) {
                out_data |= (1 << out_bit_idx);
            }

            // 出力データの書き込みビット位置を-1する．
            out_bit_idx--;

            // 8ビット分出力データに書き込んだ場合
            if(out_bit_idx == -1) {
                out_array.push_back(out_data);      // 出力バッファの末尾に追加する．
                out_data = 0;
                out_bit_idx = 7;
            }
        }
    }

    // 最後の入力データが出力データの最後の要素に丁度8ビットで収まらない場合
    if(out_bit_idx < 7) {
        out_array.push_back(out_data);
    }
}

//--------------------------------------------------------------------------------------------------
// 入力データ列(in_array)をアンパックして出力バッファ(out_array)に格納する．
void unpackbit(const std::vector<uint8_t> &in_array, std::vector<uint8_t> &out_array)
{
    uint8_t   in_data = 0;      // 出力データ
    uint8_t   out_data = 0;     // 入力データ

    int   out_bit_idx = 6;      // 出力配列書き込みビット位置
    int   in_bit_idx = 7;       // 入力データ列抽出ビット位置
    int   in_byte_idx;          // 入力データ列抽出要素番号

    for(in_byte_idx=0; in_byte_idx<in_array.size(); ) {

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
        if(out_bit_idx < 0) {
            out_array.push_back(out_data);
            out_data = 0;
            out_bit_idx = 6;
        }

        // 入力バイト1つ分を使い切ったら次へ
        if(in_bit_idx < 0) {
            in_byte_idx++;
            in_bit_idx = 7;
        }
    }

    // 端数ビットが残っていた場合は最後に追加
    if (out_bit_idx != 6 && in_bit_idx != 7) {
        out_array.push_back(out_data);
    }
}


/* 実行結果 ========================================================================================

[成功の場合]
PAE10_data.txtを読み込みました(1109バイト)．
PAE10_out.bpkに保存しました(971バイト)．
PAE10_out.bpkを読み込みました(971バイト)．
PAE10_out.txtに保存しました(1109バイト)．
----------------------------------------------------------------------------------------------------
[テキストファイル読み込み失敗の場合]
Error: txtファイルの読み込み失敗
----------------------------------------------------------------------------------------------------
[ビットパックファイル読み込み失敗の場合]
PAE10_data.txtを読み込みました(1109バイト)．
PAE10_out.bpkに保存しました(971バイト)．
Error: bpkファイルの読み込み失敗
==================================================================================================*/
