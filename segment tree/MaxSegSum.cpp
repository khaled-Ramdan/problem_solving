//https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A




#define _CRT_SECURE_NO_WARNINGS
/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/
#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W int g; cin >> g; while (g--)
#define sz(v) int(v.size())
#define FIO freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
typedef long long ll;
const long long N = 1e5 + 5, Mod = 998244353, INF = 1e18;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1, 0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1, 0 };
class segmentTree {
	struct data
	{
		ll best, sum, pref, suff;
		data(ll val) {
			sum = val;
			best = pref = suff = max(0LL, val);
		}
	};
	vector<data>tree;
public:
	segmentTree(int n = N) {
		tree.assign(4 * n, 0);
	}
	ll curBest() {
		return tree[1].best;
	}
	void build(const vector<ll>& v, int st, int en, int p) {
		if (st == en)return tree[p] = data(v[st]), void();
		build(v, st, (st + en) / 2, 2 * p);
		build(v, (st + en) / 2 + 1, en, 2 * p + 1);
		tree[p] = operation(tree[2 * p], tree[2 * p + 1]);
	}
	void update(int idx, int val, int st, int en, int p) {
		if (idx<st or idx>en)return;
		if (st == en) return tree[p] = data(val), void();
		update(idx, val, st, (st + en) / 2, 2 * p);
		update(idx, val, (st + en) / 2 + 1, en, 2 * p + 1);
		tree[p] = operation(tree[2 * p], tree[2 * p + 1]);
	}
	data operation(data l, data r) {
		data res(0);
		res.sum = l.sum + r.sum;
		res.pref = max(l.pref, l.sum + r.pref);
		res.suff = max(r.suff, r.sum + l.suff);
		res.best = max({ l.best,r.best,l.suff + r.pref });
		return res;
	}
};
void solve() {
	int n, m, x, y;
	cin >> n >> m;
	vector<ll>v(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> v[i];
	segmentTree tr;
	tr.build(v, 1, n, 1);
	cout << tr.curBest() << endl;
	while (m--)
	{
		cin >> x >> y;
		tr.update(x + 1, y, 1, n, 1);
		cout << tr.curBest() << endl;
	}
}
int main()
{
    IO;

    solve();
}
