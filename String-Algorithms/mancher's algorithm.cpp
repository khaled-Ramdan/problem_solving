#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
/*
Mancher algorithm: used to count the maximum substring to be a palindrome
p[i] => maximum palindrome considering i as the center of the substring
complexity O(n^2)
*/
vector<int> manacher_odd_ON2(string s)
{
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    for (int i = 1; i <= n; i++)
    {
        while (s[i - p[i]] == s[i + p[i]])
            p[i]++;
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
// complexity : O (N)
vector<int> manacher_odd(string s)
{
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]])
        {
            p[i]++;
        }
        if (i + p[i] > r)
        {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
// to get mancher for also even
vector<int> manacher(string s)
{
    string t;
    for (auto c : s)
    {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}
void solve()
{
    string s = "aabaac";
    auto v = manacher_odd(s);
    for (auto it : v)
        cout << it << " ";
    cout << endl;
    auto vv = manacher(s);
    for (auto it : vv)
        cout << it << " ";
    cout << endl;

    // input : aaabaaa
    // output : 1 2 1 4 1 2 1
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
