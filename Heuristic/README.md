# Heuristic

[トップへ戻る](../README.md)

AHC（AtCoder Heuristic Contest）向け。焼きなまし・ビームサーチは**ひな形**なので、問題に合わせて中身を書き足して使う。

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[annealing.hpp](annealing.hpp)|焼きなまし法|温度関数・時間管理ループ・状態のひな形|
|[beam_search.hpp](beam_search.hpp)|ビームサーチ|ハッシュで重複除去・永続スタックで行動列を復元するひな形|
|[kmeans.hpp](kmeans.hpp)|k-means 法|2次元の点をクラスタリング（サイズ指定版あり）|
|[simple_connection_judge.hpp](simple_connection_judge.hpp)|簡易連結判定|グリッドの1マスを変えても周囲の連結が保たれるかを O(1) で判定|
|[bit_field.hpp](bit_field.hpp)|ビット盤面|10×10 の盤面を `bitset<100>` で持ち、平行移動する|

---

## annealing.hpp

`namespace ANNEALING` の中にある。

### 温度関数

```cpp
bool temperature(double& turn, double& turn_max, T& old_score, T& new_score,
                 double start_temp = 30.0, double end_temp = 2.0, bool is_minimizing = true)
```

- 温度を `start_temp` → `end_temp` へ線形に下げ、遷移を受理するなら `true`。
- 良くなる遷移は必ず受理、悪くなる遷移は確率 `exp(-悪化量 / 温度)` で受理。
- 引数は参照なので変数で渡す。温度はスコアの変化量の大きさに合わせて調整する。

```cpp
bool probability(double old_score, double new_score, double now, double limit)
```

- `temperature` を時間ベースで呼ぶラッパー。**初期設定はスコアが大きいほど良い（`is_minimizing = false`）**ので、問題に合わせて書き換える。

### 実行の流れ

```cpp
using namespace ANNEALING;
int main() { solve_burn(); }
```

`solve_burn()` は次の順に呼ぶ: `Annealing::input()` → `make_first()`（初期解）→ `cale_score_all()` → `BURN::run()`（制限時間まで `task` を繰り返す）→ `print()`

書き足す場所:

|場所|書くこと|
|:--|:--|
|`struct Annealing`|状態（盤面など）とスコア `score_`、入力・初期解・スコア計算・出力|
|`task1(s, time, timeLimit)`|近傍を1つ作って新スコアを計算 → `probability` で受理なら状態を更新して `true`、却下なら元に戻して `false`|
|`task(...)`|近傍が複数あるときに `task1`, `task2` … を確率で選ぶ|
|`solve_burn` の `1.95`|制限時間（秒）|

`run()` は終了時に `loop=（試行回数） adopt=（受理回数）` を `cerr` に出す。

## beam_search.hpp

`namespace BEAMSEARCH` の `struct Beam` の中にある。

|設定|意味|
|:--|:--|
|`LOWER_IS_BETTER`|スコアが小さいほど良いなら `true`|
|`BEAM_WIDTH`|ビーム幅（各ターンに残す状態数）|
|`BEAM_TURN`|最大ターン数|
|`ACTION`|行動の型（初期は `int`）|

書き足す場所（`struct State`）:

|メンバ|書くこと|
|:--|:--|
|`try_move(action)`|状態を**変えずに**、行動後の `{スコア, ハッシュ}` を返す|
|`advance(action)`|実際に状態を進める（`score_` と `hash_` も更新）|
|`legalActions()`|今の状態で取れる行動の一覧|
|`isDone()`|終了状態か|
|`make_first()`|初期状態|

流れ（`task()`）:
1. 全状態の全行動について `try_move` で次のスコアを計算（状態はコピーしない）
2. 同じハッシュの状態は良い方だけ残す
3. 上位 `BEAM_WIDTH` 個（同点はランダム）だけ実際にコピーして `advance`
4. 終了状態があれば、その中の最良の状態の行動列（`stack.to_vector()`）を得て終了 → `// TODO: ans を出力する` の所に出力を書く

```cpp
int main() {
	BEAMSEARCH::Beam beam;
	beam.task();
}
```

- ハッシュは `Other/splitmix64.hpp` で作った Zobrist hash を差分更新するのが定番。

## kmeans.hpp

```cpp
void kMeans(const vector<pair<T, T>>& pts, vector<int>& cluster_id, int K, int max_iterations = 100)
void kMeansWithSizes(const vector<pair<T, T>>& pts, vector<int>& cluster_id, int K, int max_iterations = 100)
```

- `cluster_id` に初期のクラスタ番号（`0..K-1`）を入れて渡すと、結果に書き換える。
- `kMeans`: 普通の k-means。重心計算と再割り当てを、変化がなくなるか `max_iterations` 回まで繰り返す。O(反復 × N × K)。空になったクラスタは `rand()` で選んだ点を重心にする。
- `kMeansWithSizes`: **各クラスタの要素数を初期の割り当てのまま保つ**。2点のクラスタを入れ替えて良くなるなら入れ替える。O(反復 × N²)。初期で各クラスタに1点以上割り当てること。

```cpp
vector<int> id(N);
rep(i, 0, N) id[i] = i % K;   // 各クラスタ N/K 個ずつ
kMeansWithSizes(pts, id, K);
```

## simple_connection_judge.hpp

```cpp
bool simple_connection_judge(int N, vector<vector<T>>& V, int x, int y)
```

- N×N グリッドで、`V[x][y]` と同じ値の上下左右のマスたちが、`V[x][y]` を別の値に変えた後も（周囲 3×3 の中で）つながっているかを O(1) で判定。
- 正確には「周囲 8 マスで見た同じ値の連結成分がちょうど1つか」。遠回りでつながるケースは考えないので**簡易判定**（つながっていても `false` になることがある）。
- 領域を連結に保ったまま1マスずつ変える焼きなましで使う。

```
***    ***
.*. →  ...   true
...    ...

**.    **.
.*. →  ...   false（左上と右下が離れる）
.**    .**
```

## bit_field.hpp

```cpp
BIT_FIELD bf;
bf.init_mask();          // 最初に必ず呼ぶ（左右の端のマスクを作る）
bf.set(x, y);            // x 行 y 列を 1 に
bf.reset(x, y);
bf.bit_shift_h(n);       // n > 0 なら下へ、n < 0 なら上へ n 行ずらす
bf.bit_shift_w(n);       // n > 0 なら右へ、n < 0 なら左へ（はみ出した分は消える）
bf.bit_shift_hw(h, w);
bf.print();              // 盤面を出力
bf.allocated_blocks;     // bitset<100> 本体。& や count() で重なり判定
```

- 盤面サイズは 10×10 固定（旧版）。サイズを変えるときは `AREA_H`, `AREA_W`, `bitset` のサイズ、`init_mask` のループを変える。
