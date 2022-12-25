//  https://codeforces.com/edu/course/2/lesson/5/1/practice/contest/279634/problem/C


#define _CRT_SECURE_NO_WARNINGS
/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/
#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W int g; cin >> g; while (g--)
#define sz(v) int(v.size())
#define FIO freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
typedef long long ll;
const long long N = 4e5 + 5, Mod = 998244353, INF = 1e18;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1, 0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1, 0 };
class segmentTree {
	vector<ll>tree, lazy;
#define mid (( s + e) >> 1)
public:
	segmentTree(int n = N) {
		tree.assign(n * 4, 0);
		lazy.assign(n * 4, -1);
	}
	void relax(ll s, ll e, ll p) {
		if (lazy[p] == -1)return;

		tree[p << 1] = (mid - s + 1) * lazy[p];
		lazy[p << 1] = lazy[p];

		tree[p << 1 | 1] = (e - (mid + 1) + 1) * lazy[p];
		lazy[p << 1 | 1] = lazy[p];

		lazy[p] = -1;
	}
	void update(ll s, ll e, ll p, ll l, ll r, ll v) {
		if (l > e or r < s)return;
		if (s >= l and e <= r) {
			tree[p] = (e - s + 1) * v;
			lazy[p] = v;
			relax(s, e, p);
			return;
		}
		relax(s, e, p);
		update(s, mid, p << 1, l, r, v);
		update(mid + 1, e, p << 1 | 1 , l, r, v);
		tree[p] = tree[p << 1] + tree[p << 1 | 1];
	}
	ll get(ll s, ll e, ll p, ll i) {
		relax(s, e, p);
		if (s == e)return tree[p];
		if (i <= mid)
			return get(s, mid, p << 1, i);
		else
			return get(mid + 1, e, p << 1 | 1, i);
	}
};
void solve() {
	ll n, m, t, l, r, v, i;
	cin >> n >> m;
	segmentTree tr;
	while (m--)
	{
		cin >> t;
		if (t == 1) {
			cin >> l >> r >> v;
			tr.update(1, n, 1, l + 1, r, v);
			continue;
		}
		cin >> i;
		cout << tr.get(1, n, 1, i + 1) << "\n";
	}
}
int main()
{
	IO;

	solve();
}
