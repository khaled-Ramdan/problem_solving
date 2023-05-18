/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/

// problem link : https://vjudge.net/problem/SPOJ-FREQ2/origin
#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 1e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
int n, m, len, a[N], fr1[N], fr2[N], ans[N], res;
struct query
{
    int l, r, idx;
} q[N];
bool cmp(query one, query two)
{
    if (one.l / len != two.l / len)
        return one.l < two.l;
    if ((one.l / len) & 1)
        return two.r < one.r;
    else
        return one.r < two.r;
}
void add(int i)
{
    int cur = ++fr1[a[i]];
    fr2[cur - 1]--;
    fr2[cur]++;
    res = max(res, cur);
}
void remove(int i)
{
    int cur = --fr1[a[i]];
    fr2[cur + 1]--;
    fr2[cur]++;
    if (fr2[res] == 0)
        res--;
}
void solve()
{
    scanf("%d %d", &n, &m);
    len = (sqrt(n)) + 1;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d %d", &q[i].l, &q[i].r);
        q[i].idx = i;
    }
    sort(q, q + m, cmp);
    int curl = 1, curr = 0;
    for (int i = 0; i < m; ++i)
    {
        while (curl < q[i].l)
            remove(curl++);
        while (curl > q[i].l)
            add(--curl);
        while (curr < q[i].r)
            add(++curr);
        while (curr > q[i].r)
            remove(curr--);
        ans[q[i].idx] = res;
    }
    for (int i = 0; i < m; i++)
        printf("%d\n", ans[i]);
}
int main()
{
    // IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
