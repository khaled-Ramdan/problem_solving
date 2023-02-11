#define _CRT_SECURE_NO_WARNINGS
/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/
#include <bits/stdc++.h>
#include<unordered_set>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W int g; cin >> g; while (g--)
#define sz(v) int(v.size())
#define FIO freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
typedef long long ll;
const long long N = 2e5 + 7, Mod = 1e9 + 7 , INF = 2e18;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1, 0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1, 0 };
vector<vector<ll>>anc, graph, mx, mn;
vector<ll>dpth;
map<pair<ll, ll>, ll>cost;
ll n, m, x, y, c, q;
void init() {
	m = ll(ceil(log2(n)));
	anc = vector<vector<ll>>(n + 1, vector<ll>(m + 1));
	mx = vector<vector<ll>>(n + 1, vector<ll>(m + 1));
	mn = vector<vector<ll>>(n + 1, vector<ll>(m + 1, INF));
	graph = vector<vector<ll>>(n + 1);
	dpth = vector<ll>(n + 1);
}
void dfs(ll i, ll p) {
	for (ll& child : graph[i]) {
		if (child == p)
			continue;
		dpth[child] = dpth[i] + 1;
		anc[child][0] = i;
		mn[child][0] = mx[child][0] = cost[{child, i}];
		for (ll j = 1; j < m; j++) {
			anc[child][j] = anc[anc[child][j - 1]][j - 1];
			mx[child][j] = max(mx[child][j - 1], mx[anc[child][j - 1]][j - 1]);
			mn[child][j] = min(mn[child][j - 1], mn[anc[child][j - 1]][j - 1]);
		}
		dfs(child, i);
	}
}
pair<ll,pair<ll,ll>> k_anc(ll u, ll k) {
	ll mxval = 0, mnVal = INF;
	for (ll i = 0; i < m; i++) {
		if (k & (1LL << i)) {
			mxval = max(mxval, mx[u][i]);
			mnVal = min(mnVal, mn[u][i]);
			u = anc[u][i];
		}
	}
	return { u,{mxval,mnVal} };
}
pair<ll,pair<ll,ll>> lca(ll u, ll v) {
	if (dpth[u] < dpth[v])
		swap(u, v);
	ll k = dpth[u] - dpth[v];
	auto kth = k_anc(u, k);
	u = kth.first;
	ll mxVAl = 0;
	ll mnVal = INF;
	if (u == v)
		return kth;
	for (ll i = m - 1; i >= 0; i--) {
		if (anc[v][i] != anc[u][i]) {
			mxVAl = max(mxVAl, mx[u][i]);
			mxVAl = max(mxVAl, mx[v][i]);
			mnVal = min(mnVal, mn[u][i]);
			mnVal = min(mnVal, mn[v][i]);
			u = anc[u][i];
			v = anc[v][i];
		}
	}
	mxVAl = max(mxVAl, mx[u][0]);
	mxVAl = max(mxVAl, mx[v][0]);
	mnVal = min(mnVal, mn[u][0]);
	mnVal = min(mnVal, mn[v][0]);
	mxVAl = max(mxVAl, kth.second.first);
	mnVal = min(mnVal, kth.second.second);
	return { anc[u][0] ,{mxVAl,mnVal} };
}
void start(ll rt = 1) {
	anc[rt][0] = rt;
	dpth[rt] = 0;
	dfs(rt, -1);
}
void solve() {
	cin >> n;
	init();
	for (ll i = 1; i < n; i++) {
		cin >> x >> y >> c;
		graph[x].push_back(y);
		graph[y].push_back(x);
		cost[{x, y}] = cost[{y, x}] = c;
	}
	start();
	cin >> q;
	while (q--)
	{
		cin >> x >> y;
		auto ans = lca(x, y);
		cout << ans.second.second << " " << ans.second.first << endl;
	}
}
int main() {
	IO;
	solve();
}
