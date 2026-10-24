//予め事前にAIが作ったコードを含んでいます、下記参照
//https://github.com/genno360/KyoPro-library

#include <bits/stdc++.h>
#include <atcoder/all>
using namespace atcoder;
/*	using	*/
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
using mint = modint1000000007;
//using mint = modint998244353;
/*	マクロ	*/
//#define HEURISTIC_GRAPH

#define rep(i, P, n) for (ll i = P; i < (ll)(n); i++)
#define REP(i, P, n) for (ll i = P; i <= (ll)(n); i++)
#define repm(i, P, n, m) for (ll i = P; i < (ll)(n); i += m)
#define rrep(i, P, n) for (ll i = P; i >= (ll)(n); i--)

//#define rep(i, A, n) for (int i = A; i < (n); i++)
//#define REP(i, A, n) for (int i = A; i <= (n); i++)
//#define repm(i, A, n, m) for (int i = A; i < (n); i += m)
//#define rrep(i, A, n) for (int i = A; i >= (n); i--)
#define Yes cout << "Yes" << el
#define No cout << "No" << el
#define debug(x) cerr << #x << " = " << x << el
#define el '\n'
//小数表示桁数
#define SETPREC(X)  std::fixed << std::setprecision(X)

#define ALL(x) (x).begin(), (x).end()

//構造体にこれを加えればsort可能になる mapのkeyに構造体を使うときにも
#define DEF_CMP(T) auto operator<=>(const T&) const = default;

template<class T, class U> inline bool chmax(T& a, const U& b) { if (a < b) { a = b; return true; } return false; }
template<class T, class U> inline bool chmin(T& a, const U& b) { if (a > b) { a = b; return true; } return false; }
inline void YN(bool ok) {
	cout << (ok ? "Yes" : "No") << el;
}
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string abc = "abcdefghijklmnopqrstuvwxyz";
const int DX[4] = { -1, 1, 0, 0 };
const int DY[4] = { 0, 0, -1, 1 };

const ll INF = LLONG_MAX / 4;

/*	演算子オーバーロード	*/

/* 標準入力 */
template<typename T1, typename T2> istream& operator >> (istream& is, std::pair<T1, T2>& p) { is >> p.first >> p.second; return is; }
template<typename T>istream& operator >> (istream& is, vector<T>& vec) { for (T& x : vec) is >> x; return is; }
/* 標準出力 */
struct Init { Init() { ios::sync_with_stdio(0); cin.tie(0); } }init;

template<typename T1, typename T2>
std::ostream& operator<< (std::ostream& os, std::pair<T1, T2> p) { os << p.first << " " << p.second; return os; }
/*	標準出力系	*/
template<typename T>ostream& operator << (ostream& os, vector<T>& vec) {
	bool first = true;
	for (const auto& x : vec) {
		if (!first)os << ' ';
		first = false;
		os << x;
	}
	return os;
}
template<typename T>
ostream& operator<<(ostream& os, const set<T>& st) {
	bool first = true;
	for (const auto& x : st) {
		if (!first) os << ' ';
		first = false;
		os << x;
	}
	return os;
}
template<typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V>& mp) {
	bool first = true;
	for (const auto& [k, v] : mp) {
		if (!first) os << ' ';
		first = false;
		os << k << ':' << v;
	}
	return os;
}
template<typename T>
ostream& operator<<(ostream& os, const multiset<T>& st) {
	bool first = true;
	for (const auto& x : st) {
		if (!first) os << ' ';
		first = false;
		os << x;
	}
	return os;
}
template<typename K, typename V>
ostream& operator<<(ostream& os, const multimap<K, V>& mp) {
	bool first = true;
	for (const auto& [k, v] : mp) {
		if (!first) os << ' ';
		first = false;
		os << k << ':' << v;
	}
	return os;
}
#ifdef _DEBUG
template<class T>
struct DebugMultiset : std::multiset<T> {
	using Base = std::multiset<T>;
	using Base::Base;
	using Base::erase;

	void erase(const T& x) {
		cerr << "WARNING: multiset::erase(value) は同じ値全消しです\n";
		cerr << "ポインタならひとつだけ消せる\n";
		assert(false);
	}
};
#define multiset DebugMultiset
#else
#define multiset std::multiset
#endif

/*	乱数	*/
struct Xorshift128 {
	uint64_t x = 16354976620950309654ULL, y = 12985040979062584389ULL, z = 7179524487253565650ULL, w = 4967618042211634159ULL;
	inline uint64_t next() {
		uint64_t t = x ^ (x << 11);
		x = y; y = z; z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
	inline int next_int(int n) {
		return (int)(next() % (uint64_t)n);
	} inline double next_double()
	{
		return (next() >> 11) * (1.0 / 9007199254740992.0);
	}
} rng;

inline double random_real_0_1() {
	return rng.next_double();
}
inline int random_int_range(int a, int b) {
	return a + rng.next_int(b - a);
}
template<class T>
inline T random_pickup(const vector<T>& v) {
	return v[rng.next_int((int)v.size())];
}
template<class T>
inline void shuffle_vector(vector<T>& v) {
	for (int i = (int)v.size() - 1; i > 0; --i) {
		int j = rng.next_int(i + 1); // [0, i]
		std::swap(v[i], v[j]);
	}
}

/* 時間管理 */

class TIMER {
	chrono::system_clock::time_point start;
public:
	TIMER() : start(chrono::system_clock::now()) {}
	void reset() {
		start = chrono::system_clock::now();
	}
	double count() {
		chrono::duration<double> Time_ = chrono::system_clock::now() - start;
		return Time_.count();
	}

	bool is_under(double x) {
		return (this->count()) < x;
	}

};

/*	演算	*/

/* 数値演算 */
template<typename T>
T pow_int(T base, unsigned int exponent) {
	T result = 1;
	while (exponent > 0) {
		if (exponent & 1) {  // 奇数の場合
			result *= base;
		}
		base *= base;
		exponent >>= 1;  // 2で割る
	}
	return result;
}

vector<ll> cumulative_sum(const vector<ll>& A) {//累積和 元配列 A の区間 [l, r) の和は B[r] - B[l]
	vector<ll> B;
	B.push_back(0);
	rep(i, 0, A.size()) {
		B.push_back(B.back() + A[i]);
	}
	return B;
}

template<typename T>
vector<pair<T, int>> RLE(const vector<T>& A) { //ランレングス圧縮
	vector<pair<T, int>> ans;
	if (A.empty()) return ans;

	ans.push_back({ A[0], 1 });

	for (size_t i = 1; i < A.size(); i++) {
		if (ans.back().first == A[i]) {
			ans.back().second++;
		}
		else {
			ans.push_back({ A[i], 1 });
		}
	}
	return ans;
}

//素数列挙(n以下)
vector < ll > era(int n) {
	vector < bool > isprime;
	isprime.resize(n, true);
	vector < ll > res;
	isprime[0] = false;
	isprime[1] = false;
	for (ll i = 2; i < n; ++i) isprime[i] = true;
	for (ll i = 2; i < n; ++i) {
		if (isprime[i]) {
			res.push_back(i);
			for (ll j = i * 2; j < n; j += i) isprime[j] = false;
		}
	}
	return res;
}
template <typename T>
vector<pair<T, T>> prime_factor(T n) {//素因数分解
	vector<pair<T, T>> ret;
	for (T i = 2; i * i <= n; i++) {
		if (n % i != 0) continue;
		T tmp = 0;
		while (n % i == 0) {
			tmp++;
			n /= i;
		}
		ret.push_back(make_pair(i, tmp));
	}
	if (n != 1) ret.push_back(make_pair(n, 1));
	return ret;
}
int gcd(int a, int b) {//最大公約数
	if (a % b == 0) {
		return b;
	}
	else {
		return gcd(b, a % b);
	}
}

ll from_base_n(int base, const vector<ll>& digits) {//n進数を数字に
	ll value = 0;
	ll power = 1;
	for (ll d : digits) {
		value += d * power;
		power *= base;
	}
	return value;
}

vector<ll> to_base_m(ll value, int base) {//数字をn進数に
	if (value == 0) return { 0 };
	vector<ll> digits;
	while (value > 0) {
		digits.push_back(value % base);
		value /= base;
	}
	return digits;
}

vector<ll> convert_base_digits(//a進数をb進数に
	int from_base,
	int to_base,
	const vector<ll>& digits
) {
	return to_base_m(from_base_n(from_base, digits), to_base);
}

//二分探索
//Funcはboolが返り値で引数に整数を持つ関数
//https://atcoder.jp/contests/typical90/submissions/80262367
//条件を満たす最小のnを探す
template <typename Func>
ll binary_search_range(ll low, ll high, Func check) {
	ll left = low;
	ll right = high;
	ll result = -1; // 条件を満たす値が見つからなかった場合の初期値

	while (left <= right) {
		ll mid = left + (right - left) / 2; // オーバーフロー防止

		if (check(mid)) {
			result = mid;      // midは条件を満たすので候補として記録
			right = mid - 1;   // さらに小さな値で満たすか左側を探索
		}
		else {
			left = mid + 1;    // midは条件を満たさないので右側を探索
		}
	}
	return result;
}

//条件を満たす最大のnを探す
template <typename Func>
ll binary_search_range_max(ll low, ll high, Func check) {
	ll left = low;
	ll right = high;
	ll result = -1;

	while (left <= right) {
		ll mid = left + (right - left) / 2;

		if (check(mid)) {
			result = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	return result;
}

struct C2 {//二項係数

	C2(int n = 3000) {
		C.resize(n + 10, vector<ll>(n + 10));
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= i; j++) {
				if (j == 0 || j == i) {
					C[i][j] = 1;
				}
				else {
					C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
				}
			}
		}
	}

	ll get(ll A, ll B) {
		if (A < B) return 0;
		if (A < 0 || B < 0) return 0;
		return C[A][B];
	}
private:
	vector<vector<ll>> C;
};

struct Combination {// modint用二項係数を扱う構造体
	std::vector<mint> fac, finv, inv;

	// コンストラクタで最大値 (MAX) を指定してテーブルを初期化
	Combination(int max_val = 700000) : fac(max_val), finv(max_val), inv(max_val) {
		const int MOD = mint::mod();
		fac[0] = fac[1] = 1;
		finv[0] = finv[1] = 1;
		inv[1] = 1;

		for (int i = 2; i < max_val; i++) {
			fac[i] = fac[i - 1] * i;
			inv[i] = MOD - inv[MOD % i] * (MOD / i);
			finv[i] = finv[i - 1] * inv[i];
		}
	}

	// nCk を計算
	mint operator()(int n, int k) const {
		if (n < k || n < 0 || k < 0) return 0;
		return fac[n] * finv[k] * finv[n - k];
	}

	// 順列 nPk も必要な場合に
	mint P(int n, int k) const {
		if (n < k || n < 0 || k < 0) return 0;
		return fac[n] * finv[n - k];
	}

	// 重複組合せ nHk (= n+k-1 C k)
	mint H(int n, int k) const {
		if (n < 0 || k < 0) return 0;
		if (n == 0 && k == 0) return 1;
		return (*this)(n + k - 1, k);
	}
};

/* 座標 */

template<typename T>
double euclid(T a, T b) {
	ll dx = a.first - b.first;
	ll dy = a.second - b.second;
	return sqrt(dx * dx + dy * dy);
}
template<typename T>
double euclid(T ax, T ay, T bx, T by) {
	ll dx = ax - bx;
	ll dy = ay - by;
	return sqrt(dx * dx + dy * dy);
}
template<typename T>
T getDistanceSq(T x1, T y1, T x2, T y2) {
	T dx = x1 - x2;
	T dy = y1 - y2;
	return dx * dx + dy * dy;
}

template<typename T>
ll manhattan(T ax, T ay, T bx, T by) {
	return abs(ax - bx) + abs(ay - by);
}
bool isInArea(int a, int b, int H, int W) {
	return a >= 0 && b >= 0 && a < H && b < W;
}

/* 幾何学 */
struct LINE {
	/*
		ax + by + c = 0の直線

	*/

	ll a;
	ll b;
	ll c;
	friend auto operator<=>(const LINE&, const LINE&) = default;
	LINE(ll A, ll B, ll C) {
		a = A; b = B; c = C;
		normalization();
	}
	LINE(ll px, ll py, ll qx, ll qy) {
		a = qy - py;
		b = px - qx;
		c = qx * py - px * qy;

		normalization();
	}
	//表現の正規化 　以下をすることで同じ直線が一意に表現される
	void normalization() {
		//全部の最大公約数で割る
		ll g = gcd(a, gcd(b, c));
		a /= g, b /= g, c /= g;
		//傾きを正の向きに直す
		if (a < 0) a = -a, b = -b, c = -c;
		//傾き0なら、bを正にする
		if (a == 0 and b < 0) b = -b, c = -c;
	}
	//点が線上にある
	bool contains(ll x, ll y) const {
		return a * x + b * y + c == 0;
	}
	//点が上側or下側
	ll eval(ll x, ll y) const {
		return a * x + b * y + c;
	}

	//平行の関係
	bool is_parallel(const LINE& rhs) const {
		return a * rhs.b == b * rhs.a;
	}
	//同じ
	bool is_same(const LINE& rhs) const {
		return *this == rhs;
	}
	//垂直
	bool is_vertical(const LINE& rhs) const {
		return a * rhs.a + b * rhs.b == 0;
	}
	//向きベクトル
	pair<ll, ll> direction() const {
		return { -b,a };
	}
	// 法線ベクトル
	pair<ll, ll> normal() const {
		return { a,b };
	}
};
//垂直二等分線を得る
LINE get_canonical(ll px, ll py, ll qx, ll qy) {

	ll a = 2 * (qx - px);
	ll b = 2 * (qy - py);
	ll c = px * px + py * py - qx * qx - qy * qy;
	LINE l(a, b, c);
	return l;
}

/* 文字列 */
vector<int> manacher(string& str) {
	//その文字を中心とした最長の回文の半径を計算する
	vector<int> res(str.size());
	int i = 0, j = 0;
	while (i < str.size()) {
		while (i - j >= 0 && i + j < str.size() && str[i - j] == str[i + j]) ++j;
		res[i] = j;
		int k = 1;
		while (i - k >= 0 && k + res[i - k] < j) res[i + k] = res[i - k], ++k;
		i += k; j -= k;
	}
	return res;
}

// ダブリング
struct DOUBLING {
	int N;
	vector<vector<int>> table;

	DOUBLING(int n, const vector<int>& a, ll max_step) : N(n) {
		int log = 1;
		while ((1LL << log) <= max_step) log++;

		table.assign(log, vector<int>(N));
		table[0] = a;

		for (int k = 1; k < log; k++) {
			for (int i = 0; i < N; i++) {
				table[k][i] = table[k - 1][table[k - 1][i]];
			}
		}
	}

	int query(int pos, ll step) {
		for (int k = 0; step > 0; k++, step >>= 1) {
			if (step & 1) pos = table[k][pos];
		}
		return pos;
	}
};

// ==========================================
// 1. ストレージポリシー (コンテナ管理)
// ==========================================

// A. Setベース (Algo)
template <typename Edge>
class SetStorage {
protected:
	int N;
	vector<set<Edge>> concat;

public:
	SetStorage() = default;
	explicit SetStorage(int n) : N(n), concat(n) {}

	const auto& get_neighbors(int v) const { return concat[v]; }
	auto& get_neighbors(int v) { return concat[v]; }
	int size() const { return N; }

	void add_edge_raw(int a, const Edge& e) { concat[a].insert(e); }
	void remove_edge_raw(int a, const Edge& e) { concat[a].erase(e); }
	bool find_edge_raw(int a, const Edge& e) const { return concat[a].find(e) != concat[a].end(); }

	void print_dot(ostream& os) const {
		for (int i = 0; i < N; ++i) {
			for (const auto& c : concat[i]) {
				os << i << " " << c << el;
			}
		}
	}
};

// B. Vector + Posベース (Heuristic / O(1)削除)
template <typename Edge>
class VectorStorage {
protected:
	int N;
	vector<vector<Edge>> concat;
	vector<vector<int>> pos; // 高速削除用インデックスマップ

	// Edgeから宛先頂点(to)を取得するヘルパー (int または pairに対応)
	static int get_to(int v) { return v; }
	static int get_to(const pair<int, ll>& p) { return p.first; }

public:
	VectorStorage() = default;
	explicit VectorStorage(int n) : N(n), concat(n), pos(n, vector<int>(n, -1)) {}

	const auto& get_neighbors(int v) const { return concat[v]; }
	auto& get_neighbors(int v) { return concat[v]; }
	int size() const { return N; }

	void add_edge_raw(int a, const Edge& e) {
		int target = get_to(e);
		pos[a][target] = concat[a].size();
		concat[a].push_back(e);
	}

	void remove_edge_raw(int a, const Edge& e) {
		int target = get_to(e);
		int i = pos[a][target];
		if (i == -1) return;

		auto last = concat[a].back();
		concat[a][i] = last;
		pos[a][get_to(last)] = i;

		concat[a].pop_back();
		pos[a][target] = -1;
	}

	bool find_edge_raw(int a, const Edge& e) const {
		return pos[a][get_to(e)] != -1;
	}

	void update_weight(int u, int v, ll w) {
		// 重み付きの場合の更新用（必要に応じて）
		// テンプレートの制約で重み付きのみ有効にするか、pairの場合のみ定義
	}

	void print_dot(ostream& os) const {
		for (int i = 0; i < N; ++i) {
			for (const auto& c : concat[i]) {
				os << i << " " << c << el;
			}
		}
	}
};


// ==========================================
// 2. グラフアルゴリズム本体 (共通テンプレート)
// ==========================================
template <typename Storage, typename Edge>
class GraphTemplate : public Storage {
public:
	using Storage::Storage;

	// 辺の操作ラッパー
	void add(int a, int b) { this->add_edge_raw(a, b); }
	void add(int a, int b, ll c) { this->add_edge_raw(a, { b, c }); }

	void add_bidir(int a, int b) { add(a, b); add(b, a); }
	void add_bidir(int a, int b, ll c) { add(a, b, c); add(b, a, c); }

	void remove(int a, int b) { this->remove_edge_raw(a, b); }
	void remove(int a, int b, ll c) { this->remove_edge_raw(a, { b, c }); }

	bool find(int a, int b) const { return this->find_edge_raw(a, b); }
	bool find(int a, int b, ll c) const { return this->find_edge_raw(a, { b, c }); }

	// --- 汎用 DFS ---
	void dfs(int start, vector<bool>& visited) const {
		stack<int> st;
		st.push(start);
		while (!st.empty()) {
			int v = st.top();
			st.pop();
			if (visited[v]) continue;
			visited[v] = true;
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (!visited[u]) {
					st.push(u);
				}
			}
		}
	}

	// --- 汎用 BFS ---
	void bfs(int start, vector<int>& dist, vector<int>& route) const {
		vector<int> q;
		q.reserve(this->size());
		int head = 0;

		q.push_back(start);
		dist[start] = 0;

		while (head < (int)q.size()) {
			int v = q[head++];
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (dist[u] == -1) {
					dist[u] = dist[v] + 1;
					route[u] = v;
					q.push_back(u);
				}
			}
		}
	}

	void bfs(int start, vector<int>& dist) const {
		vector<int> q;
		q.reserve(this->size());
		int head = 0;

		q.push_back(start);
		dist[start] = 0;

		while (head < (int)q.size()) {
			int v = q[head++];
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (dist[u] == -1) {
					dist[u] = dist[v] + 1;
					q.push_back(u);
				}
			}
		}
	}

	// --- 木の中心 (Tree Center) ---
	vector<int> get_tree_centers() const {
		int N = this->size();
		if (N == 0) return {};

		vector<int> dist1(N, -1), route1(N, -1);
		bfs(0, dist1, route1);

		int u = 0;
		for (int i = 0; i < N; ++i) {
			if (dist1[i] > dist1[u]) u = i;
		}

		vector<int> dist2(N, -1), route2(N, -1);
		bfs(u, dist2, route2);

		int v = u;
		for (int i = 0; i < N; ++i) {
			if (dist2[i] > dist2[v]) v = i;
		}

		vector<int> path;
		for (int cur = v; cur != -1; cur = route2[cur]) {
			path.push_back(cur);
		}

		int len = path.size();
		if (len % 2 == 1) return { path[len / 2] };
		return { path[len / 2 - 1], path[len / 2] };
	}

	// --- 木の重心 (Tree Centroid) ---
	vector<int> get_tree_centroids() const {
		int N = this->size();
		if (N == 0) return {};

		vector<int> centroids;
		vector<int> subtree_size(N, 0);

		auto dfs_size = [&](auto self, int v, int p) -> void {
			subtree_size[v] = 1;
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (u != p) {
					self(self, u, v);
					subtree_size[v] += subtree_size[u];
				}
			}
		};

		dfs_size(dfs_size, 0, -1);

		auto dfs_centroid = [&](auto self, int v, int p) -> void {
			bool is_centroid = true;
			for (const auto& nx : this->get_neighbors(v)) {
				int u = get_to_v(nx);
				if (u != p) {
					if (subtree_size[u] > N / 2) is_centroid = false;
					self(self, u, v);
				}
			}
			if (N - subtree_size[v] > N / 2) is_centroid = false;
			if (is_centroid) centroids.push_back(v);
		};

		dfs_centroid(dfs_centroid, 0, -1);
		return centroids;
	}

	// --- 閉路検出 ---
	bool dfs_cycle(int v, int parent, vector<bool>& visited) const {
		visited[v] = true;
		for (const auto& nx : this->get_neighbors(v)) {
			int u = get_to_v(nx);
			if (!visited[u]) {
				if (dfs_cycle(u, v, visited)) return true;
			}
			else if (u != parent) {
				return true;
			}
		}
		return false;
	}

	// --- ダイクストラ法 (重み付き用) ---
	vector<ll> dijkstra(int start) const {
		int N = this->size();
		vector<ll> dist(N, INF);
		dist[start] = 0;

		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
		pq.push({ 0, start });

		while (!pq.empty()) {
			auto [cd, v] = pq.top(); pq.pop();
			if (cd > dist[v]) continue;

			for (const auto& nx : this->get_neighbors(v)) {
				int to = nx.first;
				ll cost = nx.second;
				if (dist[to] > cd + cost) {
					dist[to] = cd + cost;
					pq.push({ dist[to], to });
				}
			}
		}
		return dist;
	}

	void dijkstra(int start, vector<ll>& dist, vector<int>& route) const {
		int N = this->size();
		dist[start] = 0;

		priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
		pq.push({ 0, start });

		while (!pq.empty()) {
			auto [cd, v] = pq.top(); pq.pop();
			if (cd > dist[v]) continue;

			for (const auto& nx : this->get_neighbors(v)) {
				int to = nx.first;
				ll cost = nx.second;
				if (dist[to] > cd + cost) {
					dist[to] = cd + cost;
					route[to] = v;
					pq.push({ dist[to], to });
				}
			}
		}
	}

	// --- ワーシャルフロイド ---
	vector<vector<ll>> warshall_floyd() const {
		int N = this->size();
		vector<vector<ll>> dist(N, vector<ll>(N, INF));

		for (int i = 0; i < N; i++) dist[i][i] = 0;
		for (int i = 0; i < N; i++) {
			for (const auto& nx : this->get_neighbors(i)) {
				dist[i][nx.first] = min(dist[i][nx.first], (ll)nx.second);
			}
		}

		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++) {
				if (dist[i][k] == INF) continue;
				for (int j = 0; j < N; j++) {
					if (dist[k][j] == INF) continue;
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
		return dist;
	}

	void print_debug() const {
		cerr << "https://emkjp.github.io/WebTools/dot.html" << el;
		this->print_dot(cerr);
	}

private:
	// エッジ型から接続先頂点を取り出すヘルパー
	static int get_to_v(int to) { return to; }
	static int get_to_v(const pair<int, ll>& p) { return p.first; }
};


// ==========================================
// 3. エイリアス定義 (切り替え部分)
// ==========================================
using GraphAlgo = GraphTemplate<SetStorage<int>, int>;
using WeightGraphAlgo = GraphTemplate<SetStorage<pair<int, ll>>, pair<int, ll>>;
using GraphHeuristic = GraphTemplate<VectorStorage<int>, int>;
using WeightGraphHeuristic = GraphTemplate<VectorStorage<pair<int, ll>>, pair<int, ll>>;

#ifdef HEURISTIC_GRAPH
namespace graph_impl {
	using Graph = GraphHeuristic;
	using WGraph = WeightGraphHeuristic;
}
#else
namespace graph_impl {
	using Graph = GraphAlgo;
	using WGraph = WeightGraphAlgo;
}
#endif
using GRAPH = graph_impl::Graph;
using WGRAPH = graph_impl::WGraph;

//経路復元
vector<int> restoration(int start, vector<int>& route) {
	vector<int> path;

	path.push_back(start);

	while (1) {
		if (route[path.back()] == -1)break;
		path.push_back(route[path.back()]);
	}
	return path;
}

struct DIAMETERTREE {
	int a;
	int b;
	ll dist;
};

//木の直径(重み無し)
DIAMETERTREE calc_diameter_of_tree(GRAPH& graph) {

	int a, b;
	int N = graph.size();
	ll d = 0;
	{
		vector<int> dist(N, -1), route(N, -1);

		graph.bfs(0, dist, route);

		a = distance(dist.begin(), max_element(ALL(dist)));
	}
	{
		vector<int> dist(N, -1), route(N, -1);

		graph.bfs(a, dist, route);

		b = distance(dist.begin(), max_element(ALL(dist)));

		d = dist[b];
	}
	return { a,b,d };
}
//木の直径(重み有り)
DIAMETERTREE calc_diameter_of_tree(WGRAPH& graph) {
	int N = graph.size();
	auto farthest = [&](int start) {
		int vertex = start;
		ll max_dist = 0;
		stack<tuple<int, int, ll>> st;
		st.push({ start, -1, 0 });

		while (!st.empty()) {
			auto [v, parent, dist] = st.top();
			st.pop();
			if (dist > max_dist) {
				vertex = v;
				max_dist = dist;
			}
			for (const auto& nx : graph.get_neighbors(v)) {
				int u = nx.first;
				if (u != parent) st.push({ u, v, dist + nx.second });
			}
		}
		return pair<int, ll>{ vertex, max_dist };
	};

	int a = farthest(0).first;
	auto [b, d] = farthest(a);
	return { a, b, d };
}

//https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/union-find

class UNIONFIND
{
public:

	UNIONFIND() = default;

	explicit UNIONFIND(size_t n)
		: m_parents(n)
		, m_sizes(n, 1)
	{
		std::iota(m_parents.begin(), m_parents.end(), 0);
	}

	int find(int i) {
		if (m_parents[i] == i)
		{
			return i;
		}
		return (m_parents[i] = find(m_parents[i]));
	}
	void merge(int a, int b) {
		a = find(a);
		b = find(b);

		if (a != b)
		{
			if (m_sizes[a] < m_sizes[b])
			{
				std::swap(a, b);
			}

			m_sizes[a] += m_sizes[b];
			m_parents[b] = a;
		}
	}

	bool connected(int a, int b) {
		return (find(a) == find(b));
	}

	int size(int i) {
		return m_sizes[find(i)];
	}

private:

	std::vector<int> m_parents;
	std::vector<int> m_sizes;
};

template<class T, class Op>
//セグメントツリー
// 宣言は SEGMENTTREE<ll, SumOp> seg_sum;というように
//initで初期化(長さN、各要素e)
// //updateでpos番目をxに更新 /
// /queryでl番目からr番目の区間の演算値を得る
class SEGMENTTREE {
public:
	int siz;
	vector<T> dat;
	Op op;

	void init(int N) {
		siz = 1;
		while (siz < N) siz <<= 1;
		dat.assign(siz * 2, op.id());
	}

	void update(int pos, T x) {
		pos += siz;
		dat[pos] = x;
		while (pos > 1) {
			pos >>= 1;
			dat[pos] = op(dat[pos * 2], dat[pos * 2 + 1]);
		}
	}

	T query(int l, int r) const {
		T vl = op.id(), vr = op.id();
		l += siz; r += siz;
		while (l < r) {
			if (l & 1) vl = op(vl, dat[l++]);
			if (r & 1) vr = op(dat[--r], vr);
			l >>= 1; r >>= 1;
		}
		return op(vl, vr);
	}
};
struct SumOp {
	ll operator()(ll a, ll b) const { return a + b; }
	ll id() const { return 0; }
};

struct MaxOp {
	ll operator()(ll a, ll b) const { return max(a, b); }
	ll id() const { return LLONG_MIN; }
};

struct MinOp {
	ll operator()(ll a, ll b) const { return min(a, b); }
	ll id() const { return LLONG_MAX; }
};

//フェネック木(フェネックツリー)
// 一点更新 + 区間和取得をどちらも O(log N) で行えるデータ構造
// 別名 BIT (Binary Indexed Tree)
/* 使用例

	FenwickTree fw(100);

	fw.add(5,10);

	cout<<fw.sum(0,5)<<endl;
*/
struct FenwickTree {
	int n;
	vector<ll> bit;

	FenwickTree(int n) :n(n) {
		bit.assign(n + 1, 0);
	}

	void add(int idx, ll val) {
		idx++;

		while (idx <= n) {
			bit[idx] += val;
			idx += idx & -idx;
		}
	}

	ll sum_prefix(int idx) {
		idx++;

		ll res = 0;

		while (idx > 0) {
			res += bit[idx];
			idx -= idx & -idx;
		}

		return res;
	}

	ll sum(int l, int r) {
		if (l > r) return 0;

		return sum_prefix(r)
			- (l ? sum_prefix(l - 1) : 0);
	}
};
// IntervalSet （出典：drken1215）
// ライセンス：CC0 1.0
// 参照元：github.com/drken1215/algorithm

//l以上r未満の区間を管理する
template<class T, class VAL = long long> struct IntervalSet {
	struct Node {
		T l, r;
		VAL val;
		Node(const T& l, const T& r, const VAL& val) : l(l), r(r), val(val) {}
		constexpr bool operator < (const Node& rhs) const {
			if (l != rhs.l) return l < rhs.l;
			else return r < rhs.r;
		}
		friend ostream& operator << (ostream& s, const Node& e) {
			return s << "([" << e.l << ", " << e.r << "): " << e.val << ")";
		}
	};

	// internal values
	const VAL identity;
	set<Node> S;

	// constructor
	IntervalSet(const VAL& identity = VAL()) : identity(identity) {}
	IntervalSet(const vector<VAL>& v, const VAL& identity = VAL()) : identity(identity) {
		vector<Node> vec;
		for (int l = 0; l < (int)v.size();) {
			int r = l;
			while (r < (int)v.size() && v[r] == v[l]) r++;
			vec.emplace_back(l, r, v[l]);
			l = r;
		}
		S = set<Node>(vec.begin(), vec.end());
	}

	constexpr typename set<Node>::iterator begin() { return S.begin(); }
	constexpr typename set<Node>::iterator end() { return S.end(); }

	constexpr typename set<Node>::iterator get(const T& p) {
		auto it = S.upper_bound(Node(p, numeric_limits<T>::max(), 0));
		if (it == S.begin()) return S.end();
		it = move(it);
		if (it->l <= p && p < it->r) return it;
		else return S.end();
	}

	// 点pを含む区間を検索
	constexpr typename set<Node>::iterator lower_bound(const T& p) {
		auto it = get(p);
		if (it != S.end()) return it;
		return S.upper_bound(Node(p, numeric_limits<T>::max(), 0));
	}

	// どこかに含まれているか
	constexpr bool covered(const T& p) {
		auto it = get(p);
		if (it != S.end()) return true;
		else return false;
	}
	constexpr bool covered(const T& l, const T& r) {
		assert(l <= r);
		if (l == r) return true;
		auto it = get(l);
		if (it != S.end() && r <= it->r) return true;
		else return false;
	}

	// 同じ区間か?
	constexpr bool same(const T& p, const T& q) {
		if (!covered(p) || !covered(q)) return false;
		return get(p) == get(q);
	}

	//値を取得
	constexpr VAL get_val(const T& p) {
		auto it = get(p);
		if (it != S.end()) return it->val;
		else return identity;
	}
	VAL operator [] (const T& p) const {
		return get_val(p);
	}

	// 最小の未使用値
	constexpr T get_mex(const T& p = 0) {
		auto it = S.upper_bound(Node(p, numeric_limits<T>::max(), 0));
		if (it == S.begin()) return p;
		it = move(it);
		if (it->l <= p && p < it->r) return it->r;
		else return p;
	}

	// update [l, r) with value val / insert [l, r)
	// del: reflect effects of interval-delete
	// add: reflect effects of interval-add
	// add and del should be reversed operation each other
	template<class ADDFUNC, class DELFUNC> void update(T l, T r, const VAL& val, const ADDFUNC& add, const DELFUNC& del) {
		auto it = S.lower_bound(Node(l, 0, val));
		while (it != S.end() && it->l <= r) {
			if (it->l == r) {
				if (it->val == val) {
					r = it->r;
					del(it->l, it->r, it->val);
					it = S.erase(it);
				}
				break;
			}
			if (it->r <= r) {
				del(it->l, it->r, it->val);
				it = S.erase(it);
			}
			else {
				if (it->val == val) {
					r = it->r;
					del(it->l, it->r, it->val);
					it = S.erase(it);
				}
				else {
					Node node = *it;
					del(it->l, it->r, it->val);
					it = S.erase(it);
					it = S.emplace_hint(it, r, node.r, node.val);
					add(it->l, it->r, it->val);
				}
			}
		}
		if (it != S.begin()) {
			it = move(it);
			if (it->r == l) {
				if (it->val == val) {
					l = it->l;
					del(it->l, it->r, it->val);
					it = S.erase(it);
				}
			}
			else if (l < it->r) {
				if (it->val == val) {
					l = min(l, it->l);
					r = max(r, it->r);
					del(it->l, it->r, it->val);
					it = S.erase(it);
				}
				else {
					if (r < it->r) {
						it = S.emplace_hint(next(it), r, it->r, it->val);
						add(it->l, it->r, it->val);
						it = move(it);
					}
					Node node = *it;
					del(it->l, it->r, it->val);
					it = S.erase(it);
					it = S.emplace_hint(it, node.l, l, node.val);
					add(it->l, it->r, it->val);
				}
			}
		}
		if (it != S.end()) it = next(it);
		it = S.emplace_hint(it, l, r, val);
		add(it->l, it->r, it->val);
	}
	void update(const T& l, const T& r, const VAL& val) {
		update(l, r, val, [](T, T, VAL) {}, [](T, T, VAL) {});
	}
	template<class ADDFUNC, class DELFUNC> void insert(T l, T r, const ADDFUNC& add, const DELFUNC& del) {
		update(l, r, VAL(), add, del);
	}
	void insert(const T& l, const T& r) {
		update(l, r, VAL(), [](T, T, VAL) {}, [](T, T, VAL) {});
	}

	// erase [l, r)
	// del: reflect effects of interval-delete
	// add: reflect effects of interval-add
	// add and del should be reversed operation each other
	template<class ADDFUNC, class DELFUNC> void erase(T l, T r, const ADDFUNC& add, const DELFUNC& del) {
		auto it = S.lower_bound(Node(l, 0, VAL()));
		//COUT(*it);
		while (it != S.end() && it->l <= r) {
			if (it->l == r) break;
			if (it->r <= r) {
				del(it->l, it->r, it->val);
				it = S.erase(it);
			}
			else {
				Node node = *it;
				del(it->l, it->r, it->val);
				it = S.erase(it);
				it = S.emplace_hint(it, r, node.r, node.val);
				add(it->l, it->r, it->val);
			}
		}
		if (it != S.begin()) {
			it = move(it);
			if (l < it->r) {
				if (r < it->r) {
					it = S.emplace_hint(next(it), r, it->r, it->val);
					add(it->l, it->r, it->val);
					it = move(it);
				}
				Node node = *it;
				//COUT(*it);
				del(it->l, it->r, it->val);
				it = S.erase(it);
				it = S.emplace_hint(it, node.l, l, node.val);
				add(it->l, it->r, it->val);
				//COUT(*it);
			}
		}
	}
	void erase(const T& l, const T& r) {
		erase(l, r, [](T, T, VAL) {}, [](T, T, VAL) {});
	}

	// debug
	friend ostream& operator << (ostream& s, const IntervalSet& ins) {
		for (auto e : ins.S) {
			s << "([" << e.l << ", " << e.r << "): " << e.val << ") ";
		}
		return s;
	}
};

template <class T>
void kMeans(						//kmeans法でクラスタリング
	const vector<pair<T, T>>& pts,	//座標
	vector<int>& cluster_id,		//クラスタ番号　予め適当に割り振る
	int K,							//クラスタ数
	int max_iterations = 100		//最大反復（繰り返し）回数 数百程度で十分
) {
	int N = pts.size();
	assert((int)cluster_id.size() == N);

	vector<pair<double, double>> centroid(K);
	vector<int> cnt(K);

	for (int iter = 0; iter < max_iterations; iter++) {
		// --- 重心計算 ---
		fill(centroid.begin(), centroid.end(), make_pair(0.0, 0.0));
		fill(cnt.begin(), cnt.end(), 0);

		for (int i = 0; i < N; i++) {
			int c = cluster_id[i];
			assert(0 <= c && c < K);
			centroid[c].first += pts[i].first;
			centroid[c].second += pts[i].second;
			cnt[c]++;
		}

		for (int k = 0; k < K; k++) {
			if (cnt[k] == 0) {
				// 空クラスタ → ランダム点を重心に
				int i = rand() % N;
				centroid[k] = {
					(double)pts[i].first,
					(double)pts[i].second
				};
			}
			else {
				centroid[k].first /= cnt[k];
				centroid[k].second /= cnt[k];
			}
		}

		// --- 再割当 ---
		bool changed = false;
		for (int i = 0; i < N; i++) {
			double best = 1e100;
			int best_k = -1;
			for (int k = 0; k < K; k++) {
				double dx = pts[i].first - centroid[k].first;
				double dy = pts[i].second - centroid[k].second;
				double d = dx * dx + dy * dy;
				if (d < best) {
					best = d;
					best_k = k;
				}
			}
			if (cluster_id[i] != best_k) {
				cluster_id[i] = best_k;
				changed = true;
			}
		}

		if (!changed) break;
	}
}
template <class T>
void kMeansWithSizes(						//kmeans法でクラスタリング クラスタサイズを指定できる
	const vector<pair<T, T>>& pts,			//座標
	vector<int>& cluster_id,				//クラスタ番号　予め割り振りたい数だけ割り振る
	int K,									//クラスタ数
	int max_iterations = 100				//最大反復（繰り返し）回数 数百程度で十分
) {
	int N = pts.size();
	assert((int)cluster_id.size() == N);

	vector<pair<double, double>> centroid(K);
	vector<int> cnt(K);

	for (int iter = 0; iter < max_iterations; iter++) {
		// --- 重心計算（そのまま） ---
		fill(centroid.begin(), centroid.end(), make_pair(0.0, 0.0));
		fill(cnt.begin(), cnt.end(), 0);

		for (int i = 0; i < N; i++) {
			int c = cluster_id[i];
			centroid[c].first += pts[i].first;
			centroid[c].second += pts[i].second;
			cnt[c]++;
		}
		for (int k = 0; k < K; k++) {
			centroid[k].first /= cnt[k];
			centroid[k].second /= cnt[k];
		}

		// --- サイズ不変 swap ---
		bool changed = false;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++) {
				int ci = cluster_id[i];
				int cj = cluster_id[j];
				if (ci == cj) continue;

				auto dist = [&](int p, int c) {
					double dx = pts[p].first - centroid[c].first;
					double dy = pts[p].second - centroid[c].second;
					return dx * dx + dy * dy;
				};

				double delta =
					dist(i, cj) + dist(j, ci)
					- dist(i, ci) - dist(j, cj);

				if (delta < 0) {
					swap(cluster_id[i], cluster_id[j]);
					changed = true;
				}
			}
		}

		if (!changed) break;
	}
}
template<class T>
vector<pii> mst_points(const vector<pair<T, T>>& p) {	//最小全域木 
	int N = p.size();
	const ll INF = (1LL << 62);

	vector<ll> dist(N, INF);
	vector<int> parent(N, -1);
	vector<bool> used(N, false);

	dist[0] = 0;

	for (int it = 0; it < N; it++) {
		int v = -1;
		for (int i = 0; i < N; i++) {
			if (!used[i] && (v == -1 || dist[i] < dist[v])) v = i;
		}
		used[v] = true;

		for (int u = 0; u < N; u++) {
			if (used[u]) continue;
			ll dx = p[v].first - p[u].first;
			ll dy = p[v].second - p[u].second;
			ll w = dx * dx + dy * dy;
			if (w < dist[u]) {
				dist[u] = w;
				parent[u] = v;
			}
		}
	}

	vector<pii> res;
	for (int i = 1; i < N; i++) {
		res.push_back({ parent[i], i });
	}
	return res;
}

// 行動を復元する永続stack
//https://jetbead.github.io/AtCoderHeuristicContestMemo/Library/persistent_stack.html
template <class T>
class PersistentStack {
public:
	struct History {
		T v;
		shared_ptr<History> parent;
		History(const T& v, shared_ptr<History> parent) : v(v), parent(parent) {}
	};

	PersistentStack() : head(nullptr) {}
	PersistentStack(shared_ptr<History> head) : head(head) {}
	bool empty() const {
		return head == nullptr;
	}
	T top() {
		return head->v;
	}
	PersistentStack push(const T& v) {
		return PersistentStack(make_shared<History>(v, head));
	}
	PersistentStack pop() {
		return PersistentStack(head->parent);
	}
	std::vector<T> to_vector() const {
		std::vector<T> result;
		for (PersistentStack cur = *this; !cur.empty(); cur = cur.pop()) {
			result.push_back(cur.top());
		}
		std::reverse(result.begin(), result.end());
		return result;
	}
private:
	shared_ptr<History> head;
};

class IndexedSet {
public:
	IndexedSet(int N) {
		index.assign(N, -1);
	}

	bool add(int a) {
		if (index[a] != -1) return false;

		index[a] = arr.size();
		arr.push_back(a);
		return true;
	}
	bool remove(int a) {
		if (index[a] == -1) return false;

		int pos = index[a];
		int last = arr.back();

		arr[pos] = last;
		index[last] = pos;

		arr.pop_back();
		index[a] = -1;
		return true;
	}
	bool contains(int a) const {
		return index[a] != -1;
	}

	int position(int a) const {
		return index[a];
	}

	int operator[](int i) const {
		return arr[i];
	}

	int size() const {
		return arr.size();
	}

private:
	vector<int> arr;    // 実体（順序付き）
	vector<int> index;  // 値 → arr 内の位置
};

namespace ANNEALING {
	template<class T>
	bool temperature(
		double& turn,
		double& turn_max,
		T& old_score,
		T& new_score,
		double start_temp = 30.0,
		double end_temp = 2.0,
		bool is_minimizing = true// trueなら小さい方が良い
	) {
		double temp = start_temp + (end_temp - start_temp) * turn / turn_max;
		T score_diff = is_minimizing ? new_score - old_score : old_score - new_score;

		if (score_diff <= 0) return true;
		double probability = exp(-score_diff / temp);
		return random_real_0_1() < probability;
	}


	/*
	BURNクラス：焼きなまし法を行う
	*/
	template<class State, class Task, class Prob>
	class BURN {
	public:
		BURN(State& s, Task task, Prob prob, double tl = 1.95)
			: state(s), task(task), prob(prob), timeLimit(tl) {}
		double time;
		void run() {
			TIMER timer;
			ll loop = 0, adopt = 0;

			while ((time = timer.count()) < timeLimit) {
				if (task(state, time, timeLimit)) {
					adopt++;
				}
				loop++;
			}
			cerr << "loop=" << loop << " adopt=" << adopt << el;
		}

	private:
		State& state;
		Task task;
		Prob prob;
		double timeLimit;
	};
	//温度関数

	inline bool probability(double old_score, double new_score,
		double now, double limit) {
		return temperature(
			now, limit,
			old_score, new_score,
			30.0, 2.0,
			false	//小さいほうが良いスコアならtrue
		);
	};
	//焼きなまし法における現状態の管理を行う
	struct Annealing {
		int score_ = 0;

		void input() {

		}

		void make_first() {

		}

		int cale_score_all() {
			score_ = 0;
			return score_;
		}
		int cale_score() {
			int score = 0;
			return score;
		}
		void print() {

		}
		//bool operator<(const Annealing& other) const {
		//	return score_ < other.score_;
		//}
	};



	//焼きなまし法の1ループで行うこと
	bool task1(Annealing& s, double& time, double& timeLimit) {

		int new_score = 0;
		if (!probability(s.score_, new_score, time, timeLimit)) {

			return false;
		}

		return true;

	}
	bool task(Annealing& s, double& time, double& timeLimit) {

		return task1(s, time, timeLimit);

	};
	void solve_burn() {

		Annealing state;
		state.input();
		state.make_first();
		state.cale_score_all();
		BURN burn(
			state,
			task,
			probability,
			1.95
		);

		burn.run();
		state.print();
	}
}

namespace BEAMSEARCH {

	struct Beam {
		using ACTION = int;
		/*TODO:スコアが小さいほど良いかどうかを確認する*/
		bool LOWER_IS_BETTER = true;
		const int BEAM_WIDTH = 700;
		const int BEAM_TURN = 1000;	//必要ターン数見積もり(初期状態も含まれることに注意)

		//スコアが小さいほうが良いか?
		inline bool better(int a, int b) {
			if (LOWER_IS_BETTER) {
				return a < b;
			}
			else {
				return a > b;
			}
		}
		// スコアだけ計算して上位を選ぶために用いる仮ノード
		struct TemporaryNode {
			int score;
			uint64_t hash;
			int node_index;
			ACTION actions_;
			double rand; // タイブレーク用

			TemporaryNode(int score, uint64_t hash, int node_index, ACTION& actions_) :
				score(score), hash(hash), node_index(node_index), actions_(actions_) {
				rand = random_real_0_1();
			}
		};

		struct State {
			int score_;

			PersistentStack<ACTION> stack;// どの行動で来たか


			uint64_t hash_;

			State() {

			}

			bool isDone() const {
				return false;
			}

			void advance(const ACTION& action) {
				// 状態更新
				// score_ もここで更新

			}
			pair<int, uint64_t> try_move(const ACTION& action) const {
				//点数とハッシュを返す
				return { 0,0 };
			}
			vector<ACTION> legalActions() const {
				vector<ACTION> act;


				return act;
			}

			//bool operator<(const State& other) const {		//未使用
			//	return score_ > other.score_; // 降順
			//}
		};

		State make_first() {
			State state;
			return state;
		}

		void task() {

			TIMER timer;
			vector<State> cur, next;

			cur.reserve(BEAM_WIDTH);
			next.reserve(BEAM_WIDTH);
			vector<TemporaryNode> temp_nodes;
			temp_nodes.reserve(BEAM_WIDTH * 100);
			unordered_map<uint64_t, int> mp_index;

			cur.push_back(make_first());
			for (int turn = 0; turn < BEAM_TURN; turn++) {


				temp_nodes.clear();
				mp_index.clear();
				// --- 展開 ---
				rep(i, 0, cur.size()) {
					auto& st = cur[i];
					auto actions = st.legalActions();
					for (auto action : actions) {
						auto [next_score, next_hash] = st.try_move(action);
						if (mp_index.count(next_hash)) {
							int idx = mp_index[next_hash];

							// 既存より良いなら更新
							if (better(next_score, temp_nodes[idx].score)) {
								temp_nodes[idx] = { next_score, next_hash, (int)i, action };
							}
						}
						else {
							mp_index[next_hash] = temp_nodes.size();
							temp_nodes.emplace_back(next_score, next_hash, i, action);
						}
					}
				}


				// --- 上位K件 ---

				int node_size = temp_nodes.size();
				// 候補がビーム幅より多いなら上位beam_width個を選ぶ
				if (node_size > BEAM_WIDTH) {
					nth_element(temp_nodes.begin(), temp_nodes.begin() + BEAM_WIDTH, temp_nodes.end(),
						[this](TemporaryNode& n1, TemporaryNode& n2) {
						if (n1.score == n2.score) {
							return n1.rand < n2.rand;
						}
						/*	TODO：scoreが大きいほど良いのか、小さいほど良いのか確認 */
						return better(n1.score, n2.score);
					});
				}
				for (int i = 0; i < min(BEAM_WIDTH, node_size); i++) {
					int index = temp_nodes[i].node_index;
					next.emplace_back(cur[index]);
					next.back().advance(temp_nodes[i].actions_);
					next.back().stack = next.back().stack.push(temp_nodes[i].actions_);
					// 必要ならスコアとハッシュ値を確認
					//assert(next.back().score_ == temp_nodes[i].score);
					//assert(next.back().hash_ == temp_nodes[i].hash);
				}
				// --- 終了判定 ---
				vector<int> doned_index;
				for (int i = 0; i < next.size(); i++) {
					if (next[i].isDone()) {
						// 復元してreturn
						if (next[i].isDone()) {
							// 復元してreturn
							doned_index.push_back(i);

						}
						vector<ACTION> ans = next[i].stack.to_vector();


						return;
					}
				}
				if (!doned_index.empty()) {
					auto ite = min_element(doned_index.begin(), doned_index.end(), [&](int& n1, int& n2) {
						return better(next[n1].score_, next[n2].score_);
					});

					int i = *ite;

					vector<ACTION> ans = next[i].stack.to_vector();

					return;
				}
				// --- 入れ替え ---
				swap(cur, next);
				next.clear();
			}

		}
	};
}

//予め事前にAIが作ったコードを含んでいます、下記参照
//https://github.com/genno360/KyoPro-library

//using namespace ANNEALING;
//using namespace BEAMSEARCH;


int main() {

}

