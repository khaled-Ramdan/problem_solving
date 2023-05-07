/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/
#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
typedef long long ll;
const long long N = 3e5 + 7, Mod = 1e9 + 7, INF = 2e18;
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = {0, 0, 1, -1, 1, 1, -1, -1, 0};
const int dy[9] = {1, -1, 0, 0, -1, 1, 1, -1, 0};
class MO
{
private:
    struct query
    {
        int l, r, blockIndex, queryIndex;
        query() {}
        query(int l, int r, int queryIndex, int squareRoot)
        {
            this->l = l;
            this->r = r;
            this->queryIndex = queryIndex;
            this->blockIndex = l / squareRoot;
        }
        bool operator<(const query &q) const
        {
            if (this->blockIndex == q.blockIndex)
                return this->r < q.r;
            return this->blockIndex < q.blockIndex;
        }
    };
    int n, squareRoot = 0, res = 0;
    vector<int> a, ans;
    vector<query> queries;

public: 
    MO(int n, vector<int> &a, vector<pair<int, int>> &queries)
    {// queries l and r taken 1-based from input 
        this->n = n;
        this->a = a;
        this->squareRoot = ceil(sqrt(n));
        for (int i = 0; i < queries.size(); i++)
            this->queries.push_back(query(queries[i].first - 1, queries[i].second - 1, i, squareRoot));
        ans.resize(queries.size());
        process();
    }
    void process()
    {
        sort(queries.begin(), queries.end());
        int curL = 1, curR = 0;
        for (query q : queries)
        {
            while (curL < q.l)
                remove(curL++);
            while (curL > q.l)
                add(--curL);
            while (curR < q.r)
                add(++curR);
            while (curR > q.r)
                remove(curR--);
            ans[q.queryIndex] = res;
        }
    }
    void add(int idx)
    {
        res += a[idx];
    }
    void remove(int idx)
    {
        res -= a[idx];
    }
    vector<int> ansOfQuries()
    {
        return ans;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<pair<int, int>> qu(q);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < q; i++)
        cin >> qu[i].first >> qu[i].second;
    MO mo(n, a, qu);
    auto ans = mo.ansOfQuries();
    for (auto it : ans)
        cout << it << endl;
}
int main()
{
    IO;
    int TC = 1;
    // cin >> TC;
    while (TC--)
        solve();
}
