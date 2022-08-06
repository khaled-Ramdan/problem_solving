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
const long long N = 1e5 + 3, Mod = 1e9 + 7, INF = 1e12;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll tree[N], lazy[N], a[N], n;
void propagate(int s, int e, int p) {
    int mid = (s + e) / 2;
    tree[2 * p] += (mid - s + 1) * lazy[p];
    lazy[2 * p] += lazy[p];
    tree[2 * p + 1] += (e - (mid + 1) + 1) * lazy[p];
    lazy[2 * p + 1] += lazy[p];
    lazy[p] = 0;
}
ll build(int s, int e, int p) {
    if (s == e)return tree[p] = a[s];
    return tree[p] = build(s, (s + e) / 2, 2 * p) + build((s + e) / 2 + 1, e, 2 * p + 1);
}
void update(int s, int e, int p, int l, int r, int val) {
    if (s >= l and e <= r) {
        lazy[p] += val;
        tree[p] += (e - s + 1) * val;
        return;
    }
    propagate(s, e, p);
    if (l > (s + e) / 2)
        update((s + e) / 2 + 1, e, 2 * p + 1, l, r, val);
    else if (r <= (s + e) / 2)
        update(s, (s + e) / 2, 2 * p + 1, l, r, val);
    else
        update(s, (s + e) / 2, 2 * p + 1, l, r, val),
        update((s + e) / 2 + 1, e, 2 * p + 1, l, r, val);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
}
ll get(int s, int e, int p, int l, int r) {
    if (s >= l and e <= r)return tree[p];
    propagate(s, e, p);
    if (l > (s + e) / 2)
        return get((s + e) / 2 + 1, e, 2 * p + 1, l, r);
    else if (r <= (s + e) / 2)
        return get(s, (s + e) / 2, 2 * p + 1, l, r);
    else 
        return get(s, (s + e) / 2, 2 * p + 1, l, r)+ get((s + e) / 2 + 1, e, 2 * p + 1, l, r);
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, n, 1);
    cout << get(1, n, 1, 1, n) << endl;
    update(1, n, 1, 1, 3, 5);
    cout << get(1, n, 1, 1, n) << endl;

}
int main() {
    IO;
    solve();
    return 0;
}
/*
 5
 1 1 1 1 1
 */
