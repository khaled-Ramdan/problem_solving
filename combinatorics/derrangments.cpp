#define _CRT_SECURE_NO_WARNINGS
/*إِنَّ اللَّهَ وَمَلَائِكَتَهُ يُصَلُّونَ عَلَى النَّبِيِّ ۚ يَا أَيُّهَا الَّذِينَ آمَنُوا صَلُّوا عَلَيْهِ وَسَلِّمُوا تَسْلِيمًا*/
#include <bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W int g; cin >> g; while (g--)
#define sz(v) int(v.size())
#define FIO freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
typedef long long ll;
const long long N = 5e5 + 5, Mod = 1e9 + 7 , INF = 1e18;
ll gcd(ll a, ll b) { return a ? gcd(b % a, a) : b; }
ll lcm(ll a, ll b) { return a * b / gcd(a, b); }
ll inv(ll a, ll b = Mod) { return 1 < a ? b - inv(b % a, a) * b / a : 1; }
const int dx[9] = { 0, 0, 1, -1, 1, 1, -1, -1, 0 };
const int dy[9] = { 1, -1, 0, 0, -1, 1, 1, -1, 0 };
ll dr[N];
ll add(ll a, ll b, ll mod = Mod) {
	return ((a % mod + b % mod) % mod + mod) % mod;
}
ll mul(ll a, ll b, ll mod = Mod) {
	return ((a % mod * b % mod) % mod + mod) % mod;
}
void derrangement() {
	dr[0] = 1;
	dr[1] = 0;
	for (int i = 2; i < N; i++)
		dr[i] = mul((i - 1LL), add(dr[i - 1], dr[i - 2]));
}
int main()
{
	IO;
	derrangement();
	return 0;
}
/*
	//https://codeforces.com/contest/888/problem/D
	https://en.m.wikipedia.org/wiki/Derangement#:~:text=In%20combinatorial%20mathematics%2C%20a%20derangement,that%20has%20no%20fixed%20points
	part 1 
		https://youtu.be/pbXg5EI5t4c
	part 2
		https://youtu.be/qYAWjIVY7Zw
	Derrangement: permutation has no fixed point 
	[4 1 2 3] => derragment
	[1 3 4 2] => not a derrangement (1 maps to 1)
	!n ==> number of derrangements for permutation of size n
	note: n! ==> factorial(n)  , !n ==>derrangment(n)
	!n = [n/e] , e = 2.71828... nearest integer to fraction
	!n = |_ n/e + 1/2 _|     ==> floor function
	probabilty of no fixed points = !n / n!  = n/e/n = 1/e = 0.37
	when n>=4 probability of derrangement  = 37% 
	or 63% to get a match (there are fixed points in permutaion)
	 n => 0 1 2 3 4 5    6    7
	!n => 1 0 1 2 9 44  265  1854
	dp recurrance: 
		!n = (n-1) * [!(n-1)+!(n-2)] for n>=2
		!1 = 0, !0 = 1
	other recurrance:
	! n =  n==0? 1 : n * !(n-1) + (-1)^ n
*/
