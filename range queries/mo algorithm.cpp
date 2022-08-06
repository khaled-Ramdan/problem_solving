#include<bits/stdc++.h>
#include<unordered_set>
#pragma GCC optimize("-Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx2,tune=native")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-funroll-all-loops,-fpeel-loops,-funswitch-loops")
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef  long long  ll;
const long long N = 1e5 + 3, Mod = 1e9 + 7, INF = 1e9;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
struct query{
    int l, r, b_idx, q_idx;
    query() {};
    query(int l, int r, int q_idx, int sqr) {
        this->l = l, this->r = r, this->b_idx = l / sqr, this->q_idx = q_idx;
    }
    bool operator<(const query& tmp)const {
        if (tmp.b_idx == this->b_idx)return this->r < tmp.r;
        return b_idx < tmp.b_idx;
    }
};
ll n,m, sqr,res;
vector<ll>a,ans;
vector<query>queries;
void remove(int i) {
    res -= a[i];
}
void add(int i) {
    res += a[i];
}
void process() {
    sort(queries.begin(), queries.end());
    int curL = 1, curR = 0;
    for (query& q : queries) {
        while (curL < q.l)remove(curL++);
        while (curL > q.l)add(--curL);
        while (curR < q.r)add(++curL);
        while (curR > q.r)remove(curL--);
        ans[q.q_idx] = res;
    }
}
void solve() {
    cin >> n;
    sqr = (int)ceil(sqrt(n));
    a = vector<ll>(n);
    for (ll& i : a)
        cin >> i;
    cin >> m;
    ans = vector<ll>(m);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        queries[i] = query(l, r, i, sqr);
   }
}
int main() {
    IO;
    W solve();
    return 0;
}
