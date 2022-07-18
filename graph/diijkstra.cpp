#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef  long long  ll;
const long long N = 1e6 + 3, Mod = 1e9 + 7, INF = 1e14;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
/*وَقُلِ اعْمَلُوا فَسَيَرَى اللَّهُ عَمَلَكُمْ*/
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll n, m, u, v, c, src, tar;
vector<vector<pair<ll, ll>>>g;
vector<ll>parent;
ll dijkstra(ll src,ll tar) {
	vector <ll> dis(n + 1, INF);
	priority_queue < pair<ll, ll>, vector < pair < ll, ll >> , greater<pair<ll, ll>> > q;
	dis[src] = 0;
	q.push({ 0,src });
	while (q.size()){
		ll u = q.top().second;
		ll c = q.top().first;
		q.pop();
		if (u == tar)return c;
		if (c != dis[u])continue;
		for (auto& p : g[u]) {
			ll v = p.second;
			ll vc = p.first;
			if (dis[v] > dis[u] + vc) {
				parent[v] = u;
				dis[v] = dis[u] + vc;
				q.push({ dis[v],v });
			}
		}
	}
	return -1;
}
void solve(){
	cin >> n >> m;
	g.resize(n + 1);
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> c;
		g[u].push_back({ c,v });
		g[v].push_back({ c,u }); 
	}
	cin >> src >> tar;
	cout << dijkstra(src, tar) << endl;
}
int main() {
	IO;
	W solve();
	return 0;
}
