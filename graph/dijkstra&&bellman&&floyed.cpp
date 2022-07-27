#include<bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef  long long  ll;
const long long N = 1e6 + 3, Mod = 1e9 + 7, INF = 1e14;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll n, m, x, y, c;
vector<vector<pair<ll, ll>>>g;
struct myComp {
    constexpr bool operator()(pair<int, int> const& a, pair<int, int> const& b) const noexcept {
        return a.second < b.second;
    }
};
struct edge {
    int from, to, cost;
};
vector<edge>adj;
ll dijkstra(int src, int tar) {
    vector<ll>dis(n + 1, INF);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>q;
    dis[src] = 0;
    q.push({ 0,src });
    while (q.size()) {
        ll u = q.top().second, uc = q.top().first;
        q.pop();
        if (u == tar)return c;
        if (uc != dis[u])continue;
        for (auto& e : g[u]) {
            ll v = e.second, vc = e.first;
            if (dis[v] > dis[u] + vc) {
                dis[v] = dis[u] + vc;
                q.push({ dis[v],v });
            }
        }
    }
    return -1;
}
pair<bool, ll>bellman1(int src, int tar) {
    bool isUpdated = 0, hasCycles = 0;
    vector<ll>dis(n, INF);
    dis[src] = 0;
    for (int i = 0; i < n; i++) {
        isUpdated = 0;
        for (auto& e : adj) {
            if (dis[e.to] > dis[e.from] + e.cost) {
                dis[e.to] = dis[e.from] + e.cost;
                isUpdated = 1;
            }
        }
        if (!isUpdated)break;
        if (i == n - 1)
            hasCycles = 1;
    }
    return { hasCycles,dis[tar] };
}
ll bellman2(int src, int tar) {
    vector<ll>dis(n, INF);
    dis[src] = 0;
    bool isUpdated = 0;
    for (int i = 0; i < n - 1; i++) {
        isUpdated = 0;
        for (auto& e : adj) {
            if (dis[e.to] > dis[e.from] + e.cost) {
                isUpdated = 1;
                dis[e.to] = dis[e.from] + e.cost;
            }
        }
        if (!isUpdated)break;
    }
    vector<int>hasCycles(n, 0);
    for (int i = 0; i < n - 1; i++) {
        isUpdated = 0;
        for (auto& e : adj) {
            if (dis[e.to] > dis[e.from] + e.cost) {
                isUpdated = 1;
                dis[e.to] = dis[e.from] + e.cost;
                hasCycles[e.to] = 1;
            }
            hasCycles[e.to] |= hasCycles[e.from];
        }
        if (!isUpdated)break;
    }
    if (hasCycles[tar])return -1;
    return dis[tar];
}
ll Fdis[500][500], nxt[505][505];
void init_floyed() {
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            if (i == j)continue;
            Fdis[i][j] = INF;
        }
    }
}
void floyd_warshall() {//dp algorithm
    for (int k = 0; k < n; k++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (Fdis[u][v] > Fdis[u][k] + Fdis[k][v])
                    Fdis[u][v] = Fdis[u][k] + Fdis[k][v]
                    ,nxt[u][v] = nxt[u][k];
}
void solve() {
    cin >> n >> m;
    g.resize(n + 1);
    init_floyed();
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> c;
        g[x].push_back({ c,y });
        g[y].push_back({ c,x });
        edge tmp = { x - 1,y - 1,c };
        adj.push_back(tmp);
        Fdis[x - 1][y - 1] = min(c, Fdis[x - 1][y - 1]);
        Fdis[y - 1][x - 1] = min(c, Fdis[y - 1][x - 1]);
        nxt[x - 1][y - 1] = y - 1;
        nxt[y - 1][x - 1] = x - 1;
    }
    int src, tar;
    cin >> src >> tar;
    cout << dijkstra(src, tar) << endl;
    floyd_warshall();
    vector<ll>path;
    path.push_back(src);
    while (src!=tar)
    {
        src = nxt[src][tar];
        path.push_back(src);
    }
    for (int i = 0; i < path.size(); i++)
        cout << path[i] << " ";
}
int main() {
    IO;
    W solve();
    return 0;
}
