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
const long long N = 2e5 + 7, Mod = 1e9, INF = 2e18;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1, 0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1, 0 };
vector<vector<int>>g, anc;
vector<int>dpth;
int n, m, u, v, q, k;
void dfs(int u, int p) {
	for (int& v : g[u]) {
		if (v == p)
			continue;
		dpth[v] = dpth[u] + 1;
		anc[v][0] = u;
		for (int i = 1; i < m; i++)
			anc[v][i] = anc[anc[v][i - 1]][i - 1];
		dfs(v, u);
	}
}
int k_anc(int u, int k) {
	if (k > dpth[u])
		return -1;
	for (int i = 0; i < m; i++) {
		if (k & (1 << i))
			u = anc[u][i];
	}
	return u;
}
void init(int root) {
	anc[root][0] = root;
	dpth[root] = 0;
	dfs(root, 0);
}
void solve() {
	cin >> n;
	dpth = vector<int>(n + 1);
	m = int(log2(n)) + 1;
	anc = vector<vector<int>>(1+n, vector<int>(m));
	g = vector<vector<int>>(n + 1);
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	init(1);
	cin >> q;
	while (q--)
	{
		cin >> u >> k;
		cout << k_anc(u, k) << endl;
	}
}
int main() {
	IO;
	solve();
}
