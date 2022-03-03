#define _CRT_SECURE_NO_WARNINGS
#include<bits\stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define lp(x,y) for(auto i=x;i<y;i++)
#define lpj(x,y) for(auto j=x;j<y;j++)
#define W  int g;  cin>>g; while(g--)
#define SIZ ll(1e6)
const long long N = 5e5 + 5, MOD = 1e9 + 9;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll d;
vector<ll>ans;
// get power of 2 numbers for the binary representation for a number
void power_of_two(int x) {
	bitset<32>a(x);
	for (int i = 0;i < 32;i++) {
		if (a.to_ullong() & (1 << i)) {
			cout << i << " ";
		}
	}
}
//check if a number is power of 2
bool power2check(int x) {
	return __builtin_popcount(x) == 1;//count number of ones in a number
	//another method
	bitset<32>bit(x);
	return bit.count() == 1;//count number of ones at the number
}
//get least significant bit integer
int lsb(int x) {
	return (x & -x);
	/*		
		get negative value of x by complementing and adding one to x
		000000001100 
	  & 111111110100
	  = 000000000100
	*/
}
void solve() {
	bitset<32>a(126);
	cout << a << endl;
	power_of_two(a.to_ullong());
}
int main() {
	IO;
	solve();
	return 0;
}
/*
	notes:
	set a bit :  bit[index] = bit[index] | 1
	reset a bit: bit[index] = bit[index] & 0
	check if a bit is one : if(bit[index]&1)
	flip a bit : bit[index] = bit[index]^1
	mask a bit: n & (1 << i)
	 __builtin_popcount(x) => count number of ones in a number
	 __builtin_ctz(x) => count number of zeros from left until first one (count trailing zeros)
	 __builtin_clz(x) => count number of zeros from right until first one (count leading zeros)
	 lsb => least significant bit => (n & -n) 
	 __lg(n) => get frist one index from left (zero indexed function) => the result will be surly power of 2
	 __lg(n & -n) => get index of least significant bit 
	 at oxr 
	 every two equal bits cancel each other c^c = 0 as they have equal binary represenation
*/
