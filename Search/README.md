# Search

[トップへ戻る](../README.md)

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[binary_search.hpp](binary_search.hpp)|二分探索|条件を満たす最小 / 最大の整数を求める|

---

## binary_search.hpp

```cpp
ll binary_search_range(ll low, ll high, Func check)      // check を満たす最小の値
ll binary_search_range_max(ll low, ll high, Func check)  // check を満たす最大の値
```

- `[low, high]`（**両端を含む**）の範囲を探す。`check` は `ll` を受け取って `bool` を返す関数（ラムダ）。
- 条件を満たす値がなければ `-1` を返す（`-1` が答えになりうる範囲では注意）。
- 単調性が必要:
  - `binary_search_range`: `check` が `false ... false true ... true` の形
  - `binary_search_range_max`: `check` が `true ... true false ... false` の形
- 計算量: O(log(high - low)) 回の `check` 呼び出し
- 参考: https://atcoder.jp/contests/typical90/submissions/80262367

```cpp
// x*x >= 50 となる最小の x
ll a = binary_search_range(0, 100, [](ll x) { return x * x >= 50; });      // 8
// x*x <= 50 となる最大の x
ll b = binary_search_range_max(0, 100, [](ll x) { return x * x <= 50; });  // 7
```
