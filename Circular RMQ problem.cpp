//https://codeforces.com/contest/52/submission/167560382
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
const long long N = 4e5 + 3, Mod = 1e9 + 7, INF = 1e9;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll a[N], tree[N * 4], lazy[N * 4], l, r, q, m, n, val;
string str;
ll build(int s, int e, int p) {
    if (s == e)return tree[p] = a[s];
    return tree[p] = min(build(s, (s + e) / 2, 2 * p), build((s + e) / 2 + 1, e, 2 * p + 1));
}
void propagate(int s, int e, int p) {
    if (!lazy[p])return;
    tree[p] += lazy[p];
    if (s != e) {
        lazy[2 * p] += lazy[p];
        lazy[2 * p + 1] += lazy[p];
    }
    lazy[p] = 0;
}
void update(int s, int e, int p, int l, int r, int toAdd) {
    propagate(s, e, p);
    if(s > r or e < l)return;
    if (s >= l and e <= r) {
        lazy[p] += toAdd;
        propagate(s, e, p);
        return;
    }
    update(s, (s + e) / 2, 2 * p, l, r, toAdd);
    update((s + e) / 2 + 1, e, 2 * p + 1, l, r, toAdd);
    tree[p] = min(tree[2 * p], tree[2 * p + 1]);
}
ll get(int s, int e, int p, int l, int r) {
    propagate(s, e, p);
    if (s > r or e < l)return INF;
    if (s >= l and e <= r)return tree[p];
    return min(get(s, (s + e) / 2,2 * p, l, r), get((s + e) / 2 + 1, e, 2 * p + 1, l, r));
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, n, 1);
    cin >> m;
    cin.ignore();
    while(m--) {
        int x;
        getline(cin, str);
        stringstream ss(str);
        vector<int>v;
        while (ss >> x)v.push_back(x);
        if (v.size() == 3) {
            l = v[0], r = v[1], val = v[2];
            ++l, ++r;
            if (r >= l) {
                update(1, n, 1, l, r, val);
            }
            else {
                update(1, n, 1, l, n, val);
                update(1, n, 1, 1, r, val);
            }
        }
        else {
            l = v[0], r = v[1];
            ++l, ++r;
            if (r >= l) {
                printf("%lld\n" , get(1, n, 1, l, r));
            }
            else {
                printf("%lld\n", min(get(1, n, 1, l, n), get(1, n, 1, 1, r)));
            }
        }
    }
}
int main() {
    IO;
    solve();
    return 0;
}
