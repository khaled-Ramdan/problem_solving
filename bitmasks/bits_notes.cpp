#include<bits\stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
const long long N = 1e5 + 0, MOD = 1e9 + 7;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
ll grayCode(ll i){
	return (i ^ (i>>1));
}
//every two successive numbers have a difference of one bit 
void printGrayCode(ll len){
	for(int i=0;i< (1<<len)-1;i++){
		bitset<4>a(i);
		cout<< a <<"\t\t";
		a = grayCode(i);
		cout<< a<<"\t\t";
		cout<<__builtin_popcount(grayCode(i))<<endl; 
	}
}
//assume a complete mask and printing all subsets by decreasing 
void printAllSubSetsAllOnes(ll len){
	ll mask= (1<<len)-1; // compelete mask of size 4 = 1111 = 2^4-1=15
	for(ll i = mask;i>=0;i--){
		bitset<32>a(i);
		cout<< a << endl;
	}
}
//tring to mask valid subsets only in a given mask => valid subsets = initally have ones
void getAllValidSubSets(ll mask){
	//any bit have initally zero will not be considerd
	// only consider inital ones bits
	for(ll submask= mask;submask;submask= mask&(submask-1)){//this loop doesn't print zero
		bitset<8>a(submask),b(submask^mask);
		cout << a << " " << b << endl;// for the operation and its reverse
	}
	//for reveres :submask^mask = ~submask&mask
}
//get intersection between two arrays 
void intersection(int*a,int*b,int n){
	int mask1=0,mask2=0;
	for(int i=0;i<n;i++){
		mask1 |= ((a[i]!=0)<< i);//set the bit if value not zero
	}
	for(int i=0;i<n;i++)mask2 |= ((b[i]!=0)<<i);
	int inter= mask1&mask2;
	for(int i=0;i<32;i++){
		if(inter & (1<<i))cout<<i+1<<" "; 
	}
}
//to make a visited array it means too mach space
// we can reduce this space using bits
const int MAX=1e5;
char vis[(MAX>>3)+1];//divide the size by 8 as each char has a one byte = 8 bits
void setvisited(int i){
	vis[(i>>3)] |= (1<<(i&7));
	//same as: vis[i/8]= |= (1<<(i%8))
	// generally a%n = a&(n-1)
}
bool is_visited(int i){
	return vis[(i>>3)]&(1<<(i&7));
}
void solve() {
	ll n;
	/*int a[5]={1,0,1,1,0},b[5]={0,1,1,1,0};
	intersection(a,b,5);*/

}
int main() {
	IO;
	FIO
	solve();
	return 0;
}
