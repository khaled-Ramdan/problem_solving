//https://www.spoj.com/problems/NAJPF/

/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/
#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
vector<int> buildPrefix(string &s)
{
    vector<int> prefix;
    prefix = vector<int>(s.size());
    int border = 0;
    for (int i = 1; i < s.size(); i++)
    {
        while (border != 0 and s[i] != s[border])
            border = prefix[border - 1];
        if (s[i] == s[border])
            border++;
        prefix[i] = border;
    }
    return prefix;
}
int tst = -1;
void solve()
{
    tst++;
    string s, a, b;
    int n, m;
    cin >> a >> b;
    s = b + '$' + a;
    n = a.size(), m = b.size();
    auto prefix = buildPrefix(s);
    vector<int> ans;
    for (int i = m + 1; i < s.size(); i++)
        if (prefix[i] == m)
            ans.push_back(i - 2 * m);

    if (tst)
        cout << "\n";
    if (ans.empty())
    {
        cout << "Not Found\n";
        return;
    }
    cout << ans.size() << endl;
    for (int &i : ans)
        cout << i + 1 << " ";
    cout << endl;
}
int main()
{
    IO;
    int TC = 1;
    cin >> TC;
    while (TC--)
        solve();
}
