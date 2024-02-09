#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
int n, m;
vector<vector<int>> a, bit;
/*
    binary indexed tree to get sum on range with update on a single value.
    could be used in sum, oxr, multiplication,...
    for 2D
input: 
4 4
1 2 3 9
5 7 8 0
2 3 5 5
1 7 2 3
6
1 1 1 4 4 
1 2 2 4 3
2 2 2 -7
1 2 2 4 3
2 1 1 0
1 1 1 4 4

ans: 
63
32
18
48

*/
void add(int x, int y, int toAdd)
{
    // add the least significant bit to i
    for (int i = x; i <= n; i += (i & -i))
        for (int j = y; j <= m; j += (j & -j))
            bit[i][j] += toAdd;
}
void build()
{
    bit = vector<vector<int>>(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            add(i, j, a[i][j]);
}
ll prefixSum(int x, int y)
{
    ll sum = 0;
    // accumulate the sum and update i by removing its least significant bit
    for (int i = x; i >= 1; i -= (i & -i))
        for (int j = y; j >= 1; j -= (j & -j))
            sum += bit[i][j];
    return sum;
}
// from point (l1,r1) [at top left corner] to point (l2,r2) [at bottom right corner]
int rangeSum(int l1, int r1, int l2, int r2)
{
    return prefixSum(l2, r2) - prefixSum(l1 - 1, r2) - prefixSum(l2, r1 - 1) + prefixSum(l1 - 1, r1 - 1);
}
void update(int x, int y, int value)
{
    add(x, y, value - a[x][y]);
}
void solve()
{
    cin >> n >> m;
    a = vector<vector<int>>(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    build();
    int q;
    cin >> q;
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            cout << rangeSum(l1, r1, l2, r2) << endl;
        }
        else
        {
            int x, y, value;
            cin >> x >> y >> value;
            update(x, y, value);
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
