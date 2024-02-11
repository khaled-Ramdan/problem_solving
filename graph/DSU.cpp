#include<bits/stdc++.h>
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
/// DSU
/// </summary>
vector<ll>parent, siz;
ll n;
ll findParent(int i) {
	if (i == parent[i])return i;
	return parent[i] = findParent(parent[i]);
}
void join(ll u, ll v) {
	u = findParent(u);
	v = findParent(v);
	if (u != v) {
		if (siz[u] > siz[v])
			swap(u, v);
		parent[u] = v;
		siz[v] += siz[u];
	}
}
void init(){
parent.resize(n + 1);
	siz.resize(n + 1);
	iota(parent.begin(), parent.end(), 0);
	fill(siz.begin(), siz.end(), 1);
}
void solve() {
	cin >> n;
	
}
int main() {
	IO;
	solve();
	return 0;
}
