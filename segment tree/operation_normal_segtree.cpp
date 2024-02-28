int n;
pair<int, int> a[N];
class segmentTree
{
    vector<ll> tree;
    bool state = 0;
 
public:
    segmentTree(int n = N, bool c = false)
    {
        tree.assign(n * 4, 0);
        state = c;
    }
    ll build(ll s, ll e, ll p)
    {
        if (s == e)
            return tree[p] = (state ? a[s - 1].first : a[s - 1].second);
        return tree[p] = operation(build(s, (s + e) / 2, 2 * p), build((s + e) / 2 + 1, e, 2 * p + 1));
    }
    void update(ll s, ll e, ll p, ll i, ll v)
    {
        if (s == e)
            return tree[p] = (i % 2 ? v : -v), void();
        if (i <= (s + e) / 2)
            update(s, (s + e) / 2, 2 * p, i, v);
        else
            update((s + e) / 2 + 1, e, 2 * p + 1, i, v);
        tree[p] = operation(tree[2 * p], tree[2 * p + 1]);
    }
    ll getRange(ll s, ll e, ll p, ll l, ll r)
    {
        if (s >= l and e <= r)
            return tree[p];
        if (l > (s + e) / 2)
            return getRange((s + e) / 2 + 1, e, 2 * p + 1, l, r);
        else if (r <= (s + e) / 2)
            return getRange(s, (s + e) / 2, 2 * p, l, r);
        else
            return operation(getRange(s, (s + e) / 2, 2 * p, l, r), getRange((s + e) / 2 + 1, e, 2 * p + 1, l, r));
    }
    ll operation(ll v1, ll v2)
    {
        if (state)
            return max(v1, v2);
        else
            return min(v1, v2);
    }
};
