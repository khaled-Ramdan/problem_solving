#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
class suffix_array
{ // build O(n log n)
private:
    void init(string str)
    {
        this->s = str;
        this->s += '$';
        // but $ before n = s.size
        n = s.size();
        suffix = c = vector<int>(n);
    }

public:
    string s;
    int n;
    vector<int> suffix, c, lcp;
    suffix_array() {}
    suffix_array(string s)
    {
        init(s);
    }
    void build()
    {
        { // k = 0
            vector<pair<char, int>> a(n);
            for (int i = 0; i < n; i++)
                a[i] = {s[i], i};

            sort(a.begin(), a.end());

            for (int i = 0; i < n; i++)
                suffix[i] = a[i].second;

            // assign class to each string
            // a string which is equal to previous one have same class
            // otherwise take next class

            c[suffix[0]] = 0;
            for (int i = 1; i < n; i++)
                c[suffix[i]] = c[suffix[i - 1]] + (a[i].first != a[i - 1].first);
        }
        int k = 0;
        while ((1 << k) < n)
        {                               // k -> k + 1
            for (int i = 0; i < n; i++) // shift to the righ by 1 << k to be sorted by second half
                suffix[i] = (suffix[i] - (1 << k) + n) % n;

            count_sort(suffix, c);

            vector<int> c_new(n);
            c_new[suffix[0]] = 0;
            for (int i = 1; i < n; i++)
            {
                pair<int, int> prv = {c[suffix[i - 1]], c[(suffix[i - 1] + (1 << k)) % n]};
                pair<int, int> cur = {c[suffix[i]], c[(suffix[i] + (1 << k)) % n]};

                c_new[suffix[i]] = c_new[suffix[i - 1]] + (cur != prv);
            }
            c = c_new;
            k++;
        }
    }
    static void count_sort(vector<int> &suffix, const vector<int> &c)
    { // O(n)
        int n = suffix.size();
        vector<int> cnt(n);
        for (auto x : c)
            cnt[x]++;

        vector<int> suffix_new(n), pos(n);
        pos[0] = 0;
        for (int i = 1; i < n; i++)
            pos[i] = pos[i - 1] + cnt[i - 1];

        for (auto x : suffix)
        {
            int i = c[x];
            suffix_new[pos[i]] = x;
            pos[i]++;
        }
        suffix = suffix_new;
    }
    void lcp_build()
    { // get the longest common prefix of consecutive suffixes in O(n)
        lcp = vector<int>(n);
        int k = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int pi = c[i];
            int j = suffix[pi - 1]; // lcp[i] = lcp(s[i.. ], s[j...])
            while (s[(i + k) % n] == s[(j + k) % n])
                k++;
            lcp[pi] = k;
            k = max(0, k - 1);
        }
    }
    // lcp[i] = LCP(i, i - 1) , lcp(i, j) = Min(lcp[i...j]) => use sparse table or segment tree

    ll different_substrings_count()
    {   // returns the number of different substrings in a string :: require => build(), lcp_build()
        ll ans = 0;

        for (int i = 1; i < n; i++)
            ans += 1ll * n - suffix[i] - lcp[i] - 1;
        return ans;
    }
    static string longest_common_substring(string s, string t)
    { // takes two strings and returns the longest common substring in O(n log n)
        string str = s + "#" + t;
        suffix_array suf(str);
        suf.build();
        suf.lcp_build();

        int pos = 0, len = 0;

        for (int i = 1; i < suf.n; i++)
        {
            int a = suf.suffix[i], b = suf.suffix[i - 1];
            if (a > b)
                swap(a, b);
            if (a < s.size() and b > s.size())
            {
                if (len < suf.lcp[i])
                {
                    len = suf.lcp[i];
                    pos = suf.suffix[i];
                }
            }
        }
        return str.substr(pos, len);
    }
};
void solve()
{
    string s, t;
    cin >> s >> t;
    string str = s + "#" + t;

    cout << suffix_array::longest_common_substring(s, t);
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
