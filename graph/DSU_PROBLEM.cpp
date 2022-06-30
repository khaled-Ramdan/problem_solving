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
//https://codeforces.com/contest/1131/problem/F
//
struct DSU {
	vector<ll>par, siz, st, en, nxt;
	DSU(int n) {
		par.resize(n + 1);
		siz.resize(n + 1);
		st.resize(n + 1);
		en.resize(n + 1);
		nxt.resize(n + 1);
		iota(par.begin(), par.end(), 0);
		iota(st.begin(), st.end(), 0);
		iota(en.begin(), en.end(), 0);
		fill(siz.begin(), siz.end(), 1);
	}
	ll parent(ll u) {
		if (u == par[u])return u;
		return par[u] = parent(par[u]);
	}
	void join(ll u, ll v) {
		u = parent(u);
		v = parent(v);
		if (u == v)return;
		if (siz[u] > siz[v])
			swap(u, v);
		par[u] = v;
		siz[v] += siz[u];
		nxt[en[v]] = st[u];
		en[v] = en[u];
	}
	void print() {
		int u = parent(1);
		while (u)
		{
			cout << u << " ";
			u = nxt[u];
		}
	}
};
void solve() {
	ll n, x, y;
	cin >> n;
	DSU g(n);
	for (int i = 1; i < n; i++) {
		cin >> x >> y;
		g.join(x, y);
	}
	g.print();
}
int main() {
	IO;
	solve();
	return 0;
}
