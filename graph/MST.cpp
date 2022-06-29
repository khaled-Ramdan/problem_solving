#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef  long long  ll;
const long long N = 2e5 + 10, MOD = 1e9 + 7, INF = 1e12;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
						/*وَقُلِ اعْمَلُوا فَسَيَرَى اللَّهُ عَمَلَكُمْ*/
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
/// <summary>
/// MST =>minimam spaning tree
/// Kruskal algorithm
/// problem link: https://www.spoj.com/problems/MST/
/// </summary>
ll n, k, x, y, ans, m, c;
struct Edge
{
	ll cost, from, to;
};
vector<ll>par, siz;
vector<Edge>g;
void init() {
	iota(par.begin(), par.end(), 0);
	fill(siz.begin(), siz.end(), 1);
}
ll findParent(ll u) {
	if (u == par[u])return u;
	return par[u] = findParent(par[u]);
}
void join(ll u, ll v) {
	u = findParent(u);
	v = findParent(v);
	if (u == v)return;
	if (siz[u] > siz[v])
		swap(u, v);
	par[u] = v;
	siz[v] += siz[u];
}
bool sort_key(Edge& a, Edge& b) {
	return a.cost < b.cost;
}
ll kruskal() {
	ll ret = 0;
	init();
	sort(g.begin(), g.end(), sort_key);
	for (auto& child : g) {
		if (findParent(child.from) == findParent(child.to))
			continue;
		ret += child.cost;
		join(child.from, child.to);
	}
	return ret;
}
void solve() {
	cin >> n >> m;
	par.resize(n + 1);
	siz.resize(n + 1);
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> c;
		g.push_back({ c,x,y });
	}
	cout << kruskal() << endl;
}
int main() {
	IO;
	solve();
	return 0;
}
