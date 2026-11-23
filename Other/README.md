# Other

[トップへ戻る](../README.md)

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[random.hpp](random.hpp)|乱数 (Xorshift128)|高速な乱数。整数・実数・配列からランダムに1つ・シャッフル|
|[timer.hpp](timer.hpp)|タイマー|経過秒数を測る（ヒューリスティックの時間管理）|
|[splitmix64.hpp](splitmix64.hpp)|ハッシュ|整数をよく混ざった 64bit 値に変換する（Zobrist hash 等）|

---

## random.hpp

グローバル変数 `rng`（`Xorshift128`、シード固定）を使う。

|関数|意味|
|:--|:--|
|`random_int_range(a, b)`|`[a, b)` の整数（**b は含まない**）|
|`random_real_0_1()`|`[0, 1)` の実数|
|`random_pickup(v)`|`vector` からランダムに1つ|
|`shuffle_vector(v)`|`vector` をシャッフル（Fisher–Yates）|
|`rng.next()`|64bit の乱数|
|`rng.next_int(n)`|`[0, n)` の整数|

- シードは固定なので毎回同じ乱数列になる（再現しやすい）。変えたいときは `rng.x` などを書き換える。

```cpp
int d = random_int_range(0, 4);  // 0..3
if (random_real_0_1() < 0.3) { ... }
```

## timer.hpp

```cpp
TIMER timer;           // 作った時点から計測開始
timer.count();         // 経過秒数 (double)
timer.is_under(1.9);   // 1.9 秒未満か
timer.reset();         // 計測しなおす
```

```cpp
TIMER timer;
while (timer.is_under(1.9)) { /* 改善 */ }
```

## splitmix64.hpp

```cpp
uint64_t splitmix64(uint64_t x)
```

- 整数をランダムに見えるハッシュ値に変換する。`unordered_map` のハッシュ攻撃対策や、盤面の Zobrist hash 用の乱数表を作るのに使う。
- 参考: https://drken1215.hatenablog.com/entry/2022/05/12/105000

```cpp
vector<uint64_t> zobrist(H * W);
rep(i, 0, H * W) zobrist[i] = splitmix64(i + 12345);
```
