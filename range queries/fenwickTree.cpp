#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
int n;
vector<int> a, bit;
/*
    binary indexed tree to get sum on range with update on a single value.
    could be used in sum, oxr, multiplication,...
    
*/
// O(log n)
void add(int index, int toAdd)
{
    if (index == 0)
        return;
    // add the least significant bit to i
    for (int i = index; i <= n; i += (i & -i))
        bit[i] += toAdd;
}
// O(n log n)
void build()
{
    bit = vector<int>(n + 1);
    for (int i = 1; i <= n; i++)
        add(i, a[i]);
}
// O(log n)
ll prefixSum(int index)
{
    ll sum = 0;
    // accumulate the sum and update i by removing its least significant bit
    for (int i = index; i >= 1; i -= (i & -i))
        sum += bit[i];
    return sum;
}
// O(log n)
int rangeSum(int l, int r)
{
    return prefixSum(r) - prefixSum(l - 1);
}
// O(log n)
void update(int index, int value)
{
    add(index, value - a[index]);
}
void solve()
{
    cin >> n;
    a = vector<int>(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build();
    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << rangeSum(l, r) << endl;
        }
        else
        {
            int index, value;
            cin >> index >> value;
            update(index, value);
        }
    }
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
