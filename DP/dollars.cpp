#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define lp(x,y) for(auto i=x;i<y;i++)
#define lpj(x,y) for(auto j=x;j<y;j++)
#define W  int g;  cin>>g; while(g--)
#define SIZ ll(1e6)
const long long N = 2e5, MOD = 1e9 + 7, INF = 1e9;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
//counting dollars =>prolem link => https://vjudge.net/problem/UVA-147
ll coins[11] = { 5,10,20,50,100,200,500,1000,2000,5000,10000 }, dp[11][N];//memory order = coins * 11
//momization code- counting category
ll sol(int x, int rem) {//time order O(x*rem*loop(rem))=>O(coins*11*11)
	if (not rem)return 1;//there is no remider
	if (rem < coins[x] or x == 11)return 0;//not valid
	ll& ret = dp[x][rem];
	if (~ret)return ret;
	ret = sol(x + 1, rem);//leave it - when you leave it, it tries for different values
	//and this must be the ret for the sub problem 
	while (rem>=coins[x])//try as much as you can
	{
		ret += sol(x + 1, rem - coins[x]);
		rem -= coins[x];
	}
	return ret;
}
//push loop to parameter version
/*
* when you have a loop on a parameter
* in first version =>we try leaving current indx and find all ways => then go to next
* in this version => trace all ways for leaving your self and finding all ways  for yourself
* when you find your code makes a loop on some indecies => you may can push loop to parameter
* now you git rid of the loop 
* O(x*rem)
*/
ll sol1(int x, int rem) {
	if (not rem)return 1;//there is no remider
	if (rem < coins[x] or x == 11)return 0;//not valid
	ll& ret = dp[x][rem];
	if (~ret)return ret;
	return ret = sol1(x + 1, rem) + sol1(x, rem - coins[x]);//get all possible values to your self if you take current and if you leave it
}
/*
* momization=> top dowen approach => start with big problem and cut it into sub problems
* dp=> bottom up approach => starts with sub problem and create solution
* you must be sure that sub problem of x is ready to make process on sub of x+1
*/
void solve() {
	float n;
	memset(dp, -1, sizeof dp);
	while (scanf("%f", &n))
	{
		cout << sol1(0, n*100) << endl;
	}
}
int main() {
	IO;
	solve();
	return 0;
}