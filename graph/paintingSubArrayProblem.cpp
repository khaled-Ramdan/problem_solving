/*
https://cp-algorithms.com/data_structures/disjoint_set_union.html#historical-retrospective
Painting subarrays offline problem:
We have a segment of length L, each element initially has the color 0.
We have to repaint the subarray [l,r] with the color C for each query . 
At the end we want to find the final color of each cell. 
We assume that we know all the queries in advance.
*/

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
const long long N = 3e5 + 10, Mod = 1e9 + 7, INF = 1e16;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
#define sz(V) int(V.size())
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1,0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1 ,0 };
class DSU {
private:
	vector<int>a, par, siz;
	int n;
public:
	void init(int n) {
		this->n = n;
		a.clear(), par.clear(), siz.clear();
		a.resize(n + 1);
		siz.resize(n + 1, 1);
		par.resize(n + 2);
		iota(par.begin(), par.end(), 0);
	}
	int find_set(int u) {
		if (u == par[u])return u;
		return par[u] = find_set(par[u]);
	}
	void union_sets(int u, int v) {//O(log(n))
		u = find_set(u);
		v = find_set(v);
		if (u == v)
			return;
		par[u] = v;
	}
	void clear() {
		a.clear(), par.clear(), siz.clear();
	}
};
struct query {
	int l, r, c;
};
void solve() {
	int n, m;
	cin >> n >> m;
	vector<query>q(m);
	vector<int>ans(n + 1);
	DSU sol;
	sol.init(n);
	for (int i = 0; i < m; i++)
		cin >> q[i].l >> q[i].r >> q[i].c;
	/*
	* Now to solve this problem,
	*we consider the queries in the reverse order: from last to first.
	*This way when we execute a query, we only have to paint exactly the unpainted cells in the subarray 
	*/
	for (int i = m - 1; i >= 0; i--) {
		int l = q[i].l, r = q[i].r, c = q[i].c;
		/*
		*  We find the left-most unpainted cell inside of a segment,
		*repaint it, and with the pointer we move to the next empty cell to the right.
		*/
		for (int v = sol.find_set(l); v <= r; v = sol.find_set(v)) {
			ans[v] = c;
			sol.union_sets(v, v + 1);//order is important 
		}
	}
	for (int i = 1; i <= n; i++)
		cout << ans[i] << " ";
}
int main() {
	IO;
	solve();
	return 0;
}
/*
* input:
5 4
1 2 1
2 4 2
3 4 3
4 5 4

*/
