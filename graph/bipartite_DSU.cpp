#include<bits/stdc++.h>
#include<unordered_set>
#include<unordered_map>
#pragma GCC optimize("-Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx2,tune=native")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-funroll-all-loops,-fpeel-loops,-funswitch-loops")
#define _CRT_SECURE_NO_WARNINGS
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)			
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
using namespace std;
typedef  long long  ll;
const long long N = 5e5 + 5, Mod = 1e9 + 7, INF = 1e16;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
#define sz(V) int(V.size())
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1,0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1 ,0 };
struct DSU
{
	vector<int>par,len,siz,bipartite;
	int n;
	DSU(int ln) {
		n = ln;
		par.resize(n + 1);
		siz.resize(n + 1,1);
		len.resize(n + 1);
		bipartite.resize(n + 1);
		iota(par.begin(), par.end(), 0);
	}
	pair<int, int>parent(int u) {
		if (u == par[u])return { u,0 };
		auto val = parent(par[u]);
		par[u] = val.first;
		len[u] = (len[u] + val.second) % 2;
		return { par[u],len[u] };
	}
	void join(int a, int b) {
		auto u = parent(a);
		auto v = parent(b);
		if (u.first == v.first) {
			if (u.second == v.second)
				bipartite[u.first] = 0;
			return;
		}
		if (siz[u.first] > siz[u.second])
			swap(u, v);
		par[u.first] = v.first;
		siz[v.first] += siz[u.first];
		len[u.first] = (1 + u.second + v.second) % 2;
		bipartite[a] &= bipartite[b];
	}
	bool is_bipartite(int u) {
		return bipartite[parent(u).first];
	}
};
void solve() {
	
}
int main() {
	IO;
	solve();
	return 0;
}
