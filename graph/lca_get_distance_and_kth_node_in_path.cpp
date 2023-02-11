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
const long long N = 2e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1, 0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1, 0 };
int n, m = 20, anc[N][20], dpth[N], x, y, c, k;
ll dist[N][20];
vector<int>g[N];
map<pair<int, int>, ll>cost;
void dfs(int u, int p) {
	for (int& v : g[u]) {
		if (v == p)
			continue;
		dpth[v] = dpth[u] + 1;
		anc[v][0] = u;
		dist[v][0] = cost[{v, u}];
		for (int i = 1; i < m; i++) {
			anc[v][i] = anc[anc[v][i - 1]][i - 1];
			dist[v][i] = dist[v][i - 1] + dist[anc[v][i - 1]][i - 1];
		}
		dfs(v, u);
	}
}
pair<int,ll> k_anc(int u, int k) {
	ll ret = 0;
	for (int i = 0; i < m; i++) {
		if (k & (1LL << i)) {
			ret += dist[u][i];
			u = anc[u][i];
		}
	}
	return { u,ret };
}
pair<int, ll>lca(int u, int v) {
	if (dpth[u] < dpth[v])
		swap(u, v);
	int k = dpth[u] - dpth[v];
	auto kth = k_anc(u, k);
	ll ret = kth.second;
	u = kth.first;
	if (u == v)
		return kth;
	for (int i = m - 1; i >= 0; i--) {
		if (anc[u][i] == anc[v][i])
			continue;
		ret += dist[u][i] + dist[v][i];
		u = anc[u][i];
		v = anc[v][i];
	}
	ret += dist[u][0] + dist[v][0];
	return { anc[u][0] , ret };
}
ll get_distance(int u, int v) {
	return lca(u, v).second;
}
int kth_node_in_path(int u, int v, int k) {
	auto r = lca(u, v).first;
	if (dpth[u] - dpth[r] >= k)
		return k_anc(u, k).first;
	k -= dpth[u] - dpth[r];
	k = dpth[v] - dpth[r] - k;
	return k_anc(v, k).first;
}
void start() {
	dpth[1] = 0;
	anc[1][0] = 1;
	dfs(1, -1);
}
void solve() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y >> c;
		g[x].push_back(y);
		g[y].push_back(x);
		cost[{x, y}] = cost[{y, x}] = c;
	}
	start();
	//queriess
	string s;
	while (cin >> s)
	{
		if (s == "DONE")
			break;
		if (s == "DIST") {
			cin >> x >> y;
			cout << get_distance(x, y) << endl;
			continue;
		}
		cin >> x >> y >> k;
		cout << kth_node_in_path(x, y, k - 1) << endl;
	}
	//clearing
	for (int i = 1; i <= n; i++) {
		g[i].clear();
		for(int j=0;j<20;j++)
			dist[i][j] = 0;
	}
	cost.clear();
}
int main() {
	IO;
	W
	solve();
}
