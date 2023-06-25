/*
s < t [size] 
hashes s to h_s 
make a sliding window on t with s_size and compare current hash for s substring with t 
power must be preprocessed for multiple time of using 
*/

vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurences;
    for (int i = 0; i + S - 1 < T; i++) { 
        long long cur_h = (h[i+S] + m - h[i]) % m; 
        if (cur_h == h_s * p_pow[i] % m)
            occurences.push_back(i);
    }
    return occurences;
}


/*
preprocessing power and simulate pop and push operations for the string 

*/

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

/*
prefix[i] => the boarder for the string from 0 to i
boarder => max length for a prefix to equal suffix of the string , max length = String.size - 1
*/
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
