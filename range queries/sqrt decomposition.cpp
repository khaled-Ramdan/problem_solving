#include<bits/stdc++.h>
#include<unordered_set>
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
const long long N = 4e5 + 3, Mod = 1e9 + 7, INF = 1e9;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll n, sqr, q;
/*
square root decomposition: O(sqrt(n)*O(operation time)
*/
void solve() {
    cin >> n;       sqr = (int)ceil(sqrt(n));
    vector<ll>a(n), block(sqr);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        block[i / sqr] += a[i];
    }
    cin >> q;
    while (q--)
    {
        ll t, l, r, sum = 0, idx, val;
        cin >> t;
        if (t == 1) {//answer query
            cin >> l >> r;
            --l, --r;
            for (int i = l; i <= r;) {
                if (i % sqr == 0 and i + sqr - 1 <= r) {// block inside the range 
                    sum += block[i];
                    i += sqr;
                }
                else//brute force movement
                    sum += a[i++];
            }
        }
        else {//update
            cin >> idx >> val;
            idx--;
            block[idx / sqr] -= a[idx];//undo
            a[idx] = val;//update array
            block[idx / sqr] += a[idx];//do
        }
    }
}
int main() {
    IO;
    solve();
    return 0;
}
