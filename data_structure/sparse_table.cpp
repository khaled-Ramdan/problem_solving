#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
class sparse_table
{
private:
    vector<int> lg;
    vector<vector<int>> st;
    int n, K;

public:
    sparse_table() {}
    sparse_table(const vector<int> &a) { init(a); }
    void init(const vector<int> &a)
    {
        n = a.size();
        lg = vector<int>(n + 1);
        lg[1] = 0;
        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        K = lg[n];
        st = vector<vector<int>>(K + 1, vector<int>(n + 1));
        st[0] = a;
        build();
    }
    void build()
    { // O(n log n)
        for (int i = 1; i <= K; i++)
            for (int j = 0; j + (1 << i) <= n; j++)
                st[i][j] = operation(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
    static inline int operation(int x, int y)
    {
        return (x + y);
    }

    int query(int l, int r)
    { // O (1) [0 based] => for overlapping operations :: min, max, gcd
        int i = lg[r - l + 1];
        int res = operation(st[i][l], st[i][r - (1 << i) + 1]);
    }

    ll sum_query(int l, int r)
    { // O (log n) [0 based] => use this if the operation is sum x + y
        long long sum = 0;
        for (int i = K; i >= 0; i--)
        {
            if ((1 << i) <= r - l + 1)
            {
                sum += st[i][l];
                l += 1 << i;
            }
        }
        return sum;
    }
};
sparse_table st;
void solve()
{
    int n, q;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    st.init(a);

    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << st.sum_query(l - 1, r - 1) << endl;
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
