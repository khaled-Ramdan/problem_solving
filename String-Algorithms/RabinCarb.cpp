///https://www.spoj.com/problems/NAJPF/

/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/
#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
class RabinCarb
{
private:
    const ll x = 128, mod = 1e9 + 7;
    int len = 0;
    vector<int> power;

public:
    RabinCarb(int n)
    {
        power = vector<int>(n + 7);
        power[0] = 1;
        for (int i = 1; i < n + 7; i++)
            power[i] = mul(x, power[i - 1]);
    }
    ll hash = 0;
    ll pushBack(char ch)
    {
        len++;
        return hash = add(mul(hash, x), ch);
    }
    ll popFront(char ch)
    {
        len--;
        return hash = add(hash, -mul(ch, power[len]));
    }
    ll popBack(char ch)
    {
        len--;
        return hash = mul(add(hash, -ch), inv(x, mod));
    }
    ll pushFront(char ch)
    {
        len++;
        return hash = add(hash, mul(ch, power[len - 1]));
    }
    ll add(ll a, ll b)
    {
        return ((a % mod + b % mod) % mod + mod) % mod;
    }
    ll mul(ll a, ll b)
    {
        return ((a % mod * b % mod) % mod + mod) % mod;
    }
};
int tst = -1;
void solve()
{
    tst++;
    string a, b;
    cin >> a >> b;
    if (tst)
        cout << "\n";
    int n = a.size(), m = b.size();
    if (m > n)
    {
        cout << "Not Found\n";
        return;
    }
    RabinCarb hashA(n), hashB(m);
    for (int i = 0; i < m; i++)
    {
        hashB.pushBack(b[i]);
        hashA.pushBack(a[i]);
    }

    vector<int> ans;
    if (hashA.hash == hashB.hash)
        ans.push_back(0);

    for (int i = m; i < n; i++)
    {
        hashA.pushBack(a[i]);
        hashA.popFront(a[i - m]);
        if (hashA.hash == hashB.hash)
            ans.push_back(i - m + 1);
    }
    if (ans.empty())
    {
        cout << "Not Found\n";
        return;
    }
    cout << ans.size() << endl;
    for (auto &i : ans)
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
