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
        // put $ before n = s.size
        n = s.size();
        KtoL = suffix = vector<int>(n);
        last_k = 0; // last index in suffix array
        while ((1 << last_k) < n)
            last_k++;
        c = vector<vector<int>>(last_k + 1, vector<int>(n));

        for (int i = 0, j = 0; i < n; i++)
        {
            while ((1 << (j + 1)) <= i)
                j++;
            KtoL[i] = j;
        }
    }

public:
    string s;
    int n, last_k = 0;
    vector<int> suffix, lcp, KtoL;
    vector<vector<int>> c;
    suffix_array() {}
    suffix_array(string s)
    {
        init(s);
    }
    void build()
    {
        int k = 0;
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

            c[k][suffix[0]] = 0;
            for (int i = 1; i < n; i++)
                c[k][suffix[i]] = c[k][suffix[i - 1]] + (a[i].first != a[i - 1].first);
        }
        while ((1 << k) < n)
        {                               // k -> k + 1
            for (int i = 0; i < n; i++) // shift to the righ by 1 << k to be sorted by second half
                suffix[i] = (suffix[i] - (1 << k) + n) % n;

            count_sort(suffix, c[k]);

            c[k + 1][suffix[0]] = 0;
            for (int i = 1; i < n; i++)
            {
                pair<int, int> prv = {c[k][suffix[i - 1]], c[k][(suffix[i - 1] + (1 << k)) % n]};
                pair<int, int> cur = {c[k][suffix[i]], c[k][(suffix[i] + (1 << k)) % n]};

                c[k + 1][suffix[i]] = c[k + 1][suffix[i - 1]] + (cur != prv);
            }
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
    { // get the longest common prefix of consecutive suffixes in O(n) between me and before me
        lcp = vector<int>(n);
        int k = 0;
        for (int i = 0; i < n - 1; i++)
        {
            int pi = c[last_k][i];
            int j = suffix[pi - 1]; // lcp[i] = lcp(s[i.. ], s[j...])
            while (s[(i + k) % n] == s[(j + k) % n])
                k++;
            lcp[pi] = k;
            k = max(0, k - 1);
        }
    }
    // lcp[i] = LCP(i, i - 1) , lcp(i, j) = Min(lcp[i...j]) => use sparse table or segment tree

    ll different_substrings_count()
    { // returns the number of different substrings in a string :: require => build(), lcp_build()
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
    // compare two strings from statring positions i, j with length l where k is the greatest such that 2**k <= l
    int compare(int i, int j, int l) // requires build()
    {
        pair<int, int> a = {c[KtoL[l]][i], c[KtoL[l]][(i + l - (1 << KtoL[l])) % n]};
        pair<int, int> b = {c[KtoL[l]][j], c[KtoL[l]][(j + l - (1 << KtoL[l])) % n]};
        if (a == b)
            return 0;
        return a < b ? -1 : 1;
    }
    // compare two strings s[a.fr ... a.sec] , s[b.fr ... b.sec] requires build()
    // make sure using 0 based pairs
    bool comp(const pair<int, int> &a, const pair<int, int> &b)
    {
        int l1 = a.second - a.first + 1, l2 = b.second - b.first + 1;
        int l = min(l1, l2);
        int res = compare(a.first, b.first, l);
        if (res != 0)
            return res == -1;

        if (l1 == l2)
            return a < b;

        return l1 < l2;
    }
};

void solve()
{
    string s;
    cin >> s;
    suffix_array suf(s);
    suf.build();

    int q;
    cin >> q;
    vector<pair<int, int>> v(q);
    for (int i = 0; i < q; i++)
    {
        cin >> v[i].first >> v[i].second;
        v[i].first--;
        v[i].second--;
    }

    sort(v.begin(), v.end(), [&](pair<int, int> a, pair<int, int> b)
         { return suf.comp(a, b); });
    for (int i = 0; i < v.size(); i++)
        cout << v[i].first + 1 << " " << v[i].second + 1 << "\n";
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}

// 10 3 11 5 13 8 0 16 4 12 7 15 6 14 9 2 1
// 10 3 11 5 13 8 0 16 4 12 7 15 6 14 9 2 1
