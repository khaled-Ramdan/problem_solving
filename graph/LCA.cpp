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
struct LCA {
	int n = 0, m = 0, root = 0;
	vector<vector<int>>g, anc;
	vector<int>dpth;
	LCA(){}
	LCA(int n_, vector<vector<int>>g_, int root_ = 1) {
		n = n_;
		g = g_;
		root = root_;
		dpth.resize(n + 1);
		m = int(ceil(log2(n)));
		anc = vector<vector<int>>(n + 1, vector<int>(m + 1));
		init(root);
	}
	void init(int root) {
		anc[root][0] = root;
		dpth[root] = 0;
		dfs(root, 0);
	}
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
		for (int i = 0; i < m; i++)
			if (k & (1 << i))
				u = anc[u][i];
		return u;
	}
	int lca(int u, int v) {
		if (dpth[u] < dpth[v])
			swap(u, v);
		int k = dpth[u] - dpth[v];
		u = k_anc(u, k);
		if (u == v)
			return u;
		for (int i = m - 1; i >= 0; i--) {
			if (anc[u][i] == anc[v][i])
				continue;
			u = anc[u][i];
			v = anc[v][i];
		}
		return anc[u][0];
	}
};
void solve() {
	int n, x, s, root = 0, q, u, v;
	cin >> n;
	vector<vector<int>>g(n + 1);
	vector<int>rt(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> s;
		for (int j = 0; j < s; j++) {
			cin >> x;
			g[i].push_back(x);
			g[x].push_back(i);
			rt[x] = 1;
		}
	}
	for (int i = 1; i <= n; i++)
		if (!rt[i])root = i;
	LCA lc(n, g, root);
	cin >> q;
	while (q--)
	{
		cin >> u >> v;
		cout << lc.lca(u, v) << endl;
	}
}
int main() {
	IO;
	int t;
	cin >> t;
	for(int i=1;i<=t;i++){
		cout << "Case " << i << ":\n";
		solve(); 
	}
}
