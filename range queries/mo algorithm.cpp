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
const long long N = 4e5 + 3, Mod = 1e9 + 7, INF = 1e12;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1,0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1,0 };
struct query {
    int l, r, b_idx, q_idx;
    query() {
        l = r = b_idx = q_idx = -1;
    };
    query(int ll, int rr, int qqidx, int sqr) {
        l = ll, r = rr, b_idx = l / sqr, q_idx = qqidx;
    }
    bool operator<(const query& tmp)const {
        if (tmp.b_idx == b_idx)return r < tmp.r;
        return b_idx < tmp.b_idx;
    }
};
ll n, m, q, sqr, a[N], ans[N], res, frq[int(1e6 + 1)];
query queries[N];
void add(int i) {
    frq[a[i]]++;
    if (frq[a[i]] == 1)
        res++;
}
void remove(int i) {
    frq[a[i]]--;
    if (frq[a[i]] == 0)
        res--;
}
void process() {
    sort(queries, queries + m);
    int curL = 1, curR = 0;
    for (auto& q : queries) {
        while (curL < q.l)remove(curL++);
        while (curL > q.l)add(--curL);
        while (curR < q.r)add(++curR);
        while (curR > q.r)remove(curR--);
        ans[q.q_idx] = res;
    }
}
void solve(){
    cin >> n;       sqr = (int)ceil(sqrt(n));
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++) {
        int left, right;
        cin >> left >> right;
        queries[i] = query(--left, --right, i, sqr);
    }
    process();
    for (int i = 0; i < m; i++)
        cout << ans[i] << endl;
}
int main() {
    IO;
    solve();
    return 0;
}
