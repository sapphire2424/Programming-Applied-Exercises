/* 2025年度 プログラミング応用演習 第10回 課題レポートプログラム(1) - PAE10_repo1
====================================================================================================
■講義資料課題1のグラフからプリム法により最小全域木を求めるプログラム
・隣接行列をファイルから読み込む関数read_matrixを作成する．
  - 連接行列は"PAE10_repo1d.txt"から読み込む．
==================================================================================================*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

#define INF     10000     // 辺の値の最大値より大きい値

//------------------------------------------------------------
// 連結グラフの隣接行列を読み込み，graphを初期化する．
std::vector<std::vector<int>> read_matrix(const std::string &fn)
{
    std::vector<std::vector<int>>   w;      // グラフ
    std::ifstream   ifs(fn);        // 入力ファイルストリーム

    int     vcount;     // 頂点数
    int     c;

    if(ifs.is_open() == true) {
        ifs >> vcount;
        w.resize(vcount, std::vector<int>(vcount));
        for(int i=0; i<vcount; i++) {
            for(int j=0; j<vcount; j++) {
                ifs >> c;
                w[i][j] = c;
            }
        }
    }

    return w;
}

//==================================================================================================
int main(void)
{
    // グラフの隣接行列
    // 0は接続されていないことを示す．正の数は接続されている場合の重みを示す．
    std::vector<std::vector<int>>   graph;

    // 最小全域木の隣接行列
    // 0は接続されていないことを示す．1は接続されていることを示す．
    std::vector<std::vector<int>>   tree;

    // 頂点の状態
    // i番目の要素がfalseの場合，頂点iが未処理であることを示す．
    // i番目の要素がtrueの場合，頂点iが処理済であることを示す．
    std::vector<bool>   used;

    // 全域最小木の辺のコストの和
    int   total_cost = 0;

    // グラフの頂点数
    int   vcount;

    int   i, j, k, n;
    int   v1, v2;
    int   m1, m2;
    int   w;

    // グラフの隣接行列をファイル"PAE10_repo1d.txt"から読み込む．
    graph = read_matrix("PAE10_repo1d.txt");

    // 読み込んだグラフの頂点数を取得する．
    vcount = graph.size();

    // 読み込んだグラフを表示する．
    std::cout << "1.読み込んだグラフ" << std::endl;
    for(i=0; i<vcount; i++) {
        for(j=0; j<vcount; j++) {
            std::cout << graph[i][j] << " ";
        }

        std::cout << std::endl;
    }

    // 最小全域木の隣接行列をグラフの隣接行列と同サイズとし，全要素を0で初期化する．
    tree = std::vector<std::vector<int>>(vcount, std::vector<int>(vcount, 0));

    // 配列usedのサイズを頂点数に合わせ，全要素をfalseとする．
    used.resize(vcount, false);

    // 頂点0を処理済みに設定する．
    used[0] = true;

    // 未処理の頂点がなくなるまで繰り返す．
    // 上で頂点0を処理済みにしているので，vcount-1個が未処理のはず．
    for(n=1; n<vcount; n++) {
        m1 = INF;
        for(i=0; i<vcount; i++) {
            if(used[i]) {
                m2 = INF;
                for(j=0; j<vcount; j++) {
                    if(!used[j] && graph[i][j] > 0) {
                        if(graph[i][j] < m2) {
                            m2 = graph[i][j];
                            k = j;
                        }
                    }
                }
                if(m2 < m1) {
                    m1 = m2;
                    v1 = i;
                    v2 = k;
                }
            }
        }
        
        used[v2] = true;
        tree[v1][v2] = tree[v2][v1] = m1;
        total_cost += m1;
    }

    // コストと最小全域木の隣接行列を表示する．
    std::cout << "\n2.最小全域木(";
    std::cout << "全コスト=" << total_cost << ")" << std::endl;

    for(i=0; i < vcount; i += 1) {
        for(j=0; j < vcount; j += 1) {
            std::cout << tree[i][j] << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}

/* 実行結果 ========================================================================================
1.読み込んだグラフ
0 8 5 1 0 0 0
8 0 0 6 2 0 0
5 0 0 6 0 4 0
1 6 6 0 4 3 5
0 2 0 4 0 0 3
0 0 4 3 0 0 7
0 0 0 5 3 7 0

2.最小全域木(全コスト=17)
0 0 0 1 0 0 0
0 0 0 0 2 0 0
0 0 0 0 0 4 0
1 0 0 0 4 3 0
0 2 0 4 0 0 3 
0 0 4 3 0 0 0
0 0 0 0 3 0 0
==================================================================================================*/
