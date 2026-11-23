# Math

[トップへ戻る](../README.md)

|File Name|Algorithm|Explanation|
|:--:|:--:|:--:|
|[pow_int.hpp](pow_int.hpp)|繰り返し二乗法|`base^exponent` を O(log exponent) で計算する|
|[cumulative_sum.hpp](cumulative_sum.hpp)|累積和|区間和を O(1) で求めるための配列を作る|
|[cumulative_sum_2d.hpp](cumulative_sum_2d.hpp)|二次元累積和・二次元いもす法|長方形の和を O(1)、長方形への一括加算|
|[prime.hpp](prime.hpp)|素数列挙・素因数分解|エラトステネスの篩、試し割りによる素因数分解|
|[gcd.hpp](gcd.hpp)|最大公約数|ユークリッドの互除法|
|[base_conversion.hpp](base_conversion.hpp)|進数変換|n 進数 ⇔ 整数、a 進数 → b 進数|
|[binomial_table.hpp](binomial_table.hpp)|二項係数（パスカルの三角形）|mod を取らない nCk を表で持つ|
|[combination.hpp](combination.hpp)|二項係数（modint）|nCk・nPk・nHk を mod 付きで O(1)|

---

## pow_int.hpp

```cpp
T pow_int(T base, unsigned int exponent)
```

- `base` の `exponent` 乗を返す。`T` は `ll`・`mint`・行列など `*=` があれば何でもよい。
- 計算量: O(log exponent)
- `ll` のオーバーフローはチェックしない。

```cpp
ll a = pow_int<ll>(3, 13);     // 1594323
mint b = pow_int<mint>(2, 40);
```

## cumulative_sum.hpp

```cpp
vector<ll> cumulative_sum(const vector<ll>& A)
```

- 長さ `N+1` の累積和 `B` を返す（`B[0] = 0`, `B[i+1] = A[0] + ... + A[i]`）。
- 区間 `[l, r)` の和は `B[r] - B[l]`。
- 計算量: 構築 O(N)、区間和 O(1)

```cpp
auto B = cumulative_sum({3, 1, 4, 1, 5});
cout << B[4] - B[1];  // A[1]+A[2]+A[3] = 6
```

## cumulative_sum_2d.hpp

```cpp
CUMSUM2D cs(A);                  // A: vector<vector<ll>>（H × W）
cs.query(x1, y1, x2, y2);        // [x1, x2) × [y1, y2) の和（空なら 0）

IMOS2D im(H, W);
im.add(x1, y1, x2, y2, v);       // [x1, x2) × [y1, y2) に v を足す
auto B = im.build();             // B[i][j] = マス (i, j) の値（H × W）
```

- 区間はどちらも**半開区間**（`x2`, `y2` は含まない）。
- 計算量: `CUMSUM2D` 構築 O(HW)・クエリ O(1)、`IMOS2D` の `add` O(1)・`build` O(HW)

```cpp
IMOS2D im(H, W);
rep(i, 0, Q) { int a, b, c, d; cin >> a >> b >> c >> d; im.add(a, b, c, d, 1); }
auto B = im.build();
```

## prime.hpp

### era

```cpp
vector<ll> era(int n)
```

- **n 以下**の素数を昇順で返す（エラトステネスの篩）。
- 計算量: O(n log log n)、メモリ O(n)

```cpp
auto p = era(30);  // 2 3 5 7 11 13 17 19 23 29
```

### prime_factor

```cpp
vector<pair<T, T>> prime_factor(T n)
```

- `n` を素因数分解し、`{素因数, 指数}` を素因数の昇順で返す。`n = 1` なら空。
- 計算量: O(√n)

```cpp
auto f = prime_factor<ll>(360);  // {2,3} {3,2} {5,1}
for (auto [p, e] : f) { ... }
```

## gcd.hpp

```cpp
int gcd(int a, int b)
```

- 最大公約数を返す。`gcd(a, 0) = a`。
- `ll` を渡したときは `std::gcd` が呼ばれる（どちらも同じ結果）。最小公倍数は `std::lcm`。
- 計算量: O(log min(a, b))

## base_conversion.hpp

桁は**下の桁から順**に並んだ `vector<ll>`（`digits[0]` が1の位）。

|関数|意味|
|:--|:--|
|`ll from_base_n(int base, const vector<ll>& digits)`|`base` 進数の桁列 → 整数|
|`vector<ll> to_base_m(ll value, int base)`|整数 → `base` 進数の桁列（`0` なら `{0}`）|
|`vector<ll> convert_base_digits(int from, int to, const vector<ll>& digits)`|`from` 進数 → `to` 進数|

```cpp
auto d = to_base_m(10, 2);                     // {0,1,0,1}  (= 1010)
ll x = from_base_n(2, d);                      // 10
auto h = convert_base_digits(10, 16, {5,5,2}); // 255 → {15,15} (= FF)
```

- 値は `ll` に収まる範囲で使う。

## binomial_table.hpp

```cpp
C2 c(n = 3000);   // 0 <= B <= A <= n の表を作る
ll c.get(A, B);   // AのCB。A < B や負なら 0
```

- mod を取らない二項係数。パスカルの三角形 O(n²) で前計算、取得 O(1)。
- `ll` に収まるのはおおよそ `A <= 66` まで（それ以上はオーバーフローする）。
- `A > n` を渡すと範囲外アクセスになるので、コンストラクタの `n` を十分大きくする。

```cpp
C2 c(60);
c.get(5, 2);  // 10
```

## combination.hpp

```cpp
Combination comb(max_val = 700000);  // max_val 未満まで前計算
mint comb(n, k);   // nCk
mint comb.P(n, k); // nPk
mint comb.H(n, k); // nHk = (n+k-1)Ck  重複組合せ
```

- `mint`（テンプレートで `modint1000000007` / `modint998244353` を選ぶ）で計算する。mod は素数であること。
- 計算量: 前計算 O(max_val)、各クエリ O(1)
- 範囲外（`n < k`、負の値）は 0 を返す。`n` は `max_val` 未満にする（`max_val >= 2`）。

```cpp
Combination comb(200001);
cout << comb(5, 2).val();  // 10
```
