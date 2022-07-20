#include<bits/stdc++.h>
#include<unordered_set>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef  long long  ll;
const long long N = 2e5 + 3, Mod = 1e9 + 7, INF = 1e14;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
								/*وَقُلِ اعْمَلُوا فَسَيَرَى اللَّهُ عَمَلَكُمْ*/
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll n, m, x, y, c;
vector<tuple<ll, ll, ll>>g;
//just check if there is a negative cycle ==>get answer when no cylce is found 
pair<bool, ll> bellman(int src, int tar) {
	bool hasCycle = 0,isUpdated=0;
	vector<ll>dis(n, INF);
	dis[src] = 0;
	for (int i = 0; i < n; i++) {
		isUpdated = 0;
		for (auto& e : g) {
			if (dis[get<2>(e)] > dis[get<1>(e)] + get<0>(e)) {
				dis[get<2>(e)] = dis[get<1>(e)] + get<0>(e);
				isUpdated = 1;
			}
		}
		if (!isUpdated)break;
		if (i == n - 1)
			hasCycle = 1;
	}
	return { hasCycle,dis[tar] };
}
//get  nodes which contribute in negative cycles
pair<bool,ll> bellman2(int src,int tar) {
	vector<ll>dis(n, INF);
	dis[src] = 0;
	for (int i = 0; i < n - 1; i++) {
		bool isUpdated = 0;
		for (auto& e : g) {
			if (dis[get<2>(e)] > dis[get<1>(e)] + get<0>(e)) {
				dis[get<2>(e)] = dis[get<1>(e)] + get<0>(e);
				isUpdated = 1;
			}
		}
		if (!isUpdated)
			break;
	}
	vector<bool>hasCylce(n, 0);
	for (int i = 0; i < n - 1; i++) {
		bool isUpdated = 0;
		for (auto& e : g) {
			if (dis[get<2>(e)] > dis[get<1>(e)] + get<0>(e)) {
				dis[get<2>(e)] = dis[get<1>(e)] + get<0>(e);
				hasCylce[get<2>(e)] = 1;
				isUpdated = 1;
			}
			if(hasCylce[get<1>(e)])
				hasCylce[get<2>(e)] = 1;
		}
		if (!isUpdated)
			break;
	}
	if (hasCylce[tar])return { 0,-INF };
	return { 1,dis[tar] };
}
void solve() {
	cin >> n >> m;
	g.resize(n);
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> c;
		g.push_back({ c,x,y });
	}
	int src, tar;
	cin >> src >> tar;
	auto P = bellman(--src, --tar);
	if (P.first)
		cout << "HAS NEGATIVE CYCLE\n";
	else
		cout << P.second << endl;
}
int main() {
	IO;
	W solve();
	return 0;
}
