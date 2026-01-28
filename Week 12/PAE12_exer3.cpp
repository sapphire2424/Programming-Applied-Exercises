/* 2025年度 プログラミング応用演習 第12回 演習プログラム(3) - PAE12_exer3
====================================================================================================
■ネットワークの信頼性評価
・ネットワークをグラフで表現し，切断されると経路が維持できなくなる辺を検出する．
  - 切断すると経路が維持できなくなる辺を橋と呼ぶ．
・#if 1でグラフA，#if 0でグラフBで実行する．
==================================================================================================*/
#include <iostream>
#include <vector>

// 橋となる辺の構造体
struct BridgeEdge {    // 頂点uと頂点vの間の辺が橋となる．
    int u;
    int v;
};

//==================================================================================================
// 橋を検出する．
std::vector<BridgeEdge> detect_bridge(
        int u,      // 注目となる頂点の番号
        const std::vector<std::vector<int>> &aj,    // 隣接リスト
        std::vector<bool> &vist,
        std::vector<int> &disc,
        std::vector<int> &low,
        std::vector<int> &par,
        int &time
) {
    int     v;
    BridgeEdge  b;

    std::vector<BridgeEdge>   res;          // この頂点の部分木で見つかる橋
    std::vector<BridgeEdge>   child_brdg;

    vist[u] = true;
    disc[u] = low[u] = ++time;

    for(int i=0; i<aj[u].size(); i++) {

        v = aj[u][i];

        if(vist[v] == false) {   // まだ訪問していない頂点
            par[v] = u;     // vに対する親ノード

            // 子vの探索結果を受け取る
            child_brdg = detect_bridge(v, aj, vist, disc, low, par, time);

            // 子で見つかった橋をまとめる
            res.insert(res.end(), child_brdg.begin(), child_brdg.end());

            // low値更新
            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            // 頂点vとuの間の辺が橋の条件:low[v] > disc[u]
            if (low[v] > disc[u]) {
                b.u = u;
                b.v = v;
                res.push_back(b);
            }
        } else if(v != par[u]) {
            if(disc[v] < low[u]) {
                low[u] = disc[v];
            }
        }
    }

    return res;
}

//==================================================================================================
int main(void)
{
    // 隣接行列
#if 0
    // グラフA
    std::vector<std::vector<double>>   E_mtx = {
        { 0, 1, 0, 0, 0, 0, 0},
        { 1, 0, 1, 0, 0, 1, 0},
        { 0, 1, 0, 1, 0, 0, 0},
        { 0, 0, 1, 0, 1, 1, 0},
        { 0, 0, 0, 1, 0, 1, 0},
        { 0, 1, 0, 1, 1, 0, 1},
        { 0, 0, 0, 0, 0, 1, 0}
    };
#else
    // グラフB
    std::vector<std::vector<double>>   E_mtx = {
        { 0, 1, 0, 0, 0, 0, 1},
        { 1, 0, 1, 0, 0, 0, 0},
        { 0, 1, 0, 1, 0, 0, 0},
        { 0, 0, 1, 0, 1, 0, 0},
        { 0, 0, 0, 1, 0, 1, 0},
        { 0, 0, 0, 0, 1, 0, 1},
        { 1, 0, 0, 0, 0, 1, 0}
    };
#endif

    int     N = E_mtx.size();    // 隣接行列サイズ
    int     time = 0;

    std::vector<std::vector<int>>   aj(N);    // 隣接リスト
    std::vector<BridgeEdge>   brdg;           // ある頂点に関する橋の一覧
    std::vector<BridgeEdge>   brdg_total;     // 全体の橋の一覧

    std::vector<bool>   vist(N, false);        // 訪問済み頂点か否か
    std::vector<int>    disc(N, -1);
    std::vector<int>    low(N, -1);
    std::vector<int>    par(N, -1);

    // 隣接リストに変換：辺があるか否かだけ使う．
    for(int i=0; i<N; i++) {
        for(int j=i+1; j<N; j++) { // 無向グラフなので i<j のみでよい．
            if(E_mtx[i][j] != 0.0) {
                aj[i].push_back(j);
                aj[j].push_back(i);
            }
        }
    }

    // 非連結グラフの可能性があるので，全頂点から開始する．
    for(int i=0; i<N; i++) {
        if(vist[i] == false) {   // まだ訪問していない頂点
            brdg = detect_bridge(i, aj, vist, disc, low, par, time);
            brdg_total.insert(brdg_total.end(), brdg.begin(), brdg.end());
        }
    }

    // 橋の一覧を表示する．
    std::cout << "橋一覧:" << std::endl;
    for(int i=0; i<brdg_total.size(); i++) {
        std::cout << "辺(" << brdg_total[i].u << " - " << brdg_total[i].v << ")" << std::endl;
    }

    return 0;
}

/* 実行結果 ========================================================================================

[グラフAの場合]
橋一覧:
辺(5 - 6)
辺(0 - 1)


----------------------------------------------------------------------------------------------------
[グラフBの場合]
橋一覧:


==================================================================================================*/
