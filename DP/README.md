# DP

[トップへ戻る](../README.md)

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[digit_dp.cpp](digit_dp.cpp)|桁DP|N 以下の整数のうち条件を満たすものを数える（ABC154 E の解答）|

---

## digit_dp.cpp

ライブラリではなく、書き換えて使う**サンプル**。
問題: [ABC154 E - Almost Everywhere Zero](https://atcoder.jp/contests/abc154/tasks/abc154_e)（N 以下で、0 でない桁がちょうど K 個の整数の個数）

```
dp[i][isless][k]
  i      : 上から i 桁目まで決めた
  isless : ここまでで N より小さいことが確定しているか (0 / 1)
  k      : ここまでで 0 以外の数字を使った回数    ← 問題ごとに変える部分
```

- 遷移: 次の桁に `nxt` を置く。`isless == 0` なら置けるのは `N[i]` まで、`1` なら 9 まで。`nxt < limit` なら `isless` は 1 になる。
- 答え: `dp[桁数][0][K] + dp[桁数][1][K]`
- 計算量: O(桁数 × 2 × 状態数 × 10)

```
入力: 100 1      → 19
入力: 25 2       → 14
入力: 314159 2   → 937
```
