#include<bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef  long long  ll;
const long long N = 5e5 + 10, MOD = 1e9 + 7, INF = 1e12;
const double PI = 3.14159265;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
/*وَقُلِ اعْمَلُوا فَسَيَرَى اللَّهُ عَمَلَكُمْ*/
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll n, a[N], interval[N];
/*
st-en=> for the segment itself
p => for index in interval array
*/
ll intialOne(ll st, ll en, ll p) {
	//return number of elements in the root node
	if (st == en)return interval[p] = 1;
	return interval[p] = intialOne(st, (st + en) / 2, 2 * p) + intialOne((st + en) / 2 + 1, en, 2 * p + 1);
}
ll insert(ll num, ll st, ll en, ll p) {
	//return the kth order of the element
	/*
	suppose elements
	1 1 2 3 4 5 5 6
	the kth order of 6 is 8
	*/
	interval[p]++;
	if (st == en)return interval[p];
	if (num <= (st + en) / 2)return insert(num, st, (st + en) / 2, 2 * p);
	return  interval[2 * p] + insert(num, (st + en) / 2 + 1, en, 2 * p + 1);
}
ll delkth(ll kth, ll st, ll en, ll p) {
	/*
	this function is to delete Kth element and returns its value  
	*/
	if (kth > interval[p])return 0;
	interval[p]--;
	if (st == en) return st;
	if (kth <= interval[2 * p])return delkth(kth, st, (st + en) / 2, 2 * p);
	return delkth(kth - interval[2 * p], (st + en) / 2 + 1 , en, 2 * p + 1);
}
ll remove(ll num, ll st, ll en, ll p) {
	//decrease the number value by one 
	interval[p]--;
	if (st == en)return interval[p] + 1;
	if (num <= (st + en) / 2)return remove(num, st, (st + en) / 2, 2 * p);
	return interval[2 * p] +  remove(num, (st + en) / 2 + 1, en, 2 * p + 1);
}
ll get_elements(ll i, ll j, ll s, ll e, ll p) {
	if (s >= i and e <= j)
		return interval[p];
	else if (i > (s + e) / 2)
		return get_elements(i, j, (s + e) / 2 + 1, e, 2 * p + 1);
	else if (j <= (s + e) / 2)
		return get_elements(i, j, s, (s + e) / 2, 2 * p);
	else return get_elements(i, j, s, (s + e) / 2, 2 * p) + get_elements(i, j, (s + e) / 2 + 1, e, 2 * p + 1);
}
void clear_tree(ll s, ll e, ll p = 1) {
	if (p>=N or not interval[p])return;
	interval[p] = 0;
	clear_tree(s, (s + e) / 2, 2 * p);
	clear_tree((s + e) / 2 + 1, e, 2 * p + 1);
}
void solve() {
	cout << intialOne(0, 5, 1) << endl;
	interval;
	cout << insert(1, 0, 5, 1) << endl;
	cout << insert(1, 0, 5, 1) << endl;
	cout << insert(1, 0, 5, 1) << endl;
	cout << insert(5, 0, 5, 1) << endl;
	cout << insert(3, 0, 5, 1) << endl;
	cout << insert(5, 0, 5, 1) << endl;
	interval;
	cout << remove(1, 0, 5, 1) << endl;
	cout << remove(1, 0, 5, 1) << endl;
	cout << remove(1, 0, 5, 1) << endl;
	cout << remove(1, 0, 5, 1) << endl;
	cout << remove(1, 0, 5, 1) << endl;
	interval;
}
int main() {
	IO;
	solve();
	return 0;
}
