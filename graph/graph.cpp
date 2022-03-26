#include<bits/stdc++.h>
#define IO ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define W  int g;  cin>>g; while(g--)
#define FIO freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
const long long N = 5e5 + 10, MOD = 1e9+ 7,INF=1e18;
using namespace std;
typedef  long long  ll;
const int dx[8] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dy[8] = { 1, -1, 0, 0, -1, 1, 1, -1 };
class GRID{
	private:
	int n,m,island_count=0;
	vector<string>grid;
	vector<vector<bool>>visited;
	public:
	GRID(){
		cin>>n>>m;
		grid.resize(n);
		visited.resize(n,vector<bool>(m));
		for(int i=0;i<n;i++)cin>>grid[i];
	}
	bool inside(int i,int j){
		return i>=0 and j>=0 and i<n and j<m;
	}
	void flodfill(){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(not visited[i][j] and grid[i][j]!='#'){
					dfs(i,j);
					island_count++;
				}
			}
		}
		cout<<island_count<<endl;
	}
	void dfs(int i,int j){
		visited[i][j]=true;
		for(int k=0;k<4;k++){
			int x=i+dx[k],y=j+dy[k];
			if(inside(x,y) and not visited[x][y] and grid[x][y]!='#')
				dfs(x,y);
		}
	}
	/*
	example :count number of islands => (. = land) (# = water)
	@	6 6
	@	##..##
	@	.#.#.#
	@	###.##
	@	.#####
	@	##...#
	@	.#..##
	output: 
	@	5=> for 8 dimensions
	@	7=> for 4 dimensions
	*/
};
class GRAPH {
private:
	vector<vector<int>>graph;
	vector<bool>visited,instack;
	vector<int>parent,color;
	int n, m, to = 0;
public:
	GRAPH(bool directed=false) {
		int x, y;
		cin >> n >> m;
		graph.resize(n + 1);
		visited.resize(n + 1);
		instack.resize(n + 1);
		parent.resize(n + 1);
		color.resize(n + 1);
		while (m--)
		{
			cin >> x >> y;
			graph[x].push_back(y);
			if(directed)continue;
			graph[y].push_back(x);
		}
	}
	GRAPH(vector<vector<int>>G,int vertices) {
		graph = G;
		n = vertices;
		visited.resize(n + 1);
		instack.resize(n + 1);
		parent.resize(n +1);
		color.resize(n + 1);
	}
	void find_path(int init, int fin) {
		to = fin;
		dfs(init);
	}
	void iterative_dfs(int i){
		stack<int>st;
		st.push(i);
		visited[i]=true;
		while (st.size())
		{
			int top=st.top();
			st.pop();
			for(int child:graph[top]){
				if(not visited[child]){
					st.push(child);
					visited[child]=true;
				}
			}
		}
	}
	//IS there a path ?
	bool dfs(int i) {
		if (i == to)return true;
		for (int& child : graph[i]) {
			if (not visited[child]) {
				visited[child] = true;
				parent[child] = i;
				if (dfs(child))return true;
			}
		}
		return false;
	}
	//build solution
	void build_solution(int i,int j) {
		find_path(i, j);
		list<int>path;
		for (int node = j;node != i;node = parent[node]) {
			path.push_front(node);
		}
		path.push_front(i);
		for (int& i : path)cout << i << " ";
		cout << endl;
	}
	bool directed_cylces(int i) {
		/*
		this function works only if there  is no reflected connection like:
		1 2
		2 1
		if this condition exist : there may be wrong answer by counting a cycle which 
		does not exist 
		to avoid this error => you have to take parent and check it is not equal to your
		child and this child is visited before
		3 4 <= n,m
		1 2
		2 1
		2 3
		1 3
		for this example => output :YES <= WRONG ANSWER
		*/
		visited[i] = 1;
		instack[i] = 1;
		for (int& child : graph[i])
			if ((not visited[child] and directed_cylces(child)) or instack[child])
				return true;
		instack[i] = 0;
		return false;
	}
	bool directed_cylces(int i,int parent){
		visited[i]=true;
		instack[i]=true;
		for(int&child:graph[i]){
			if(visited[child] and parent != child and instack[child])return true;
			if(not visited[child] and directed_cylces(child,i))return true;
		}
		instack[i]=false;
		return false;
	}
	bool undirected_cycles(int i,int parent){
		//initial parent => unvalid vertix (-1)
		/*
		this function works for undirected graph only 
		*/ 
		visited[i]=true;
		for(int&child:graph[i]){
			if(visited[child] and child!=parent)return true;
			if(not visited[child] and undirected_cycles(child,i))return true;
		}
		return false;
	}
	//topology sort => from low dependancy to heigher one
	void topo(int i){
		visited[i]=true;
		for(int&child:graph[i])if(!visited[child])topo(child);
		cout<<i<<" ";
	}
	void bfs(int i,int j){
		queue<int>q;
		q.push(i);
		visited[i]=true;
		int depth=0,s=0;
		/*
			i_th queue size => number of elements in  i_th layer
			every time all of these elements go away,it means we are in a new layer
			make s = size of queue in the comming iteration 
			go until s reachs zero => it means all elements in the previous layer are deleted 
			increase depth by one and repeat 
		*/
		while (s=q.size())
		{
			//every inner while loop represents a new layer on the graph
			while(s--){
				int front =q.front();
				q.pop();
				if(front==j)break;
				for(int&child:graph[front]){
					if(not visited[child]){
						q.push(child);
						visited[child]=true;
						parent[child]=front;
					}
				}
			}
			depth++;
		}
		cout<<"depth = "<<depth<<endl;
		build_path(i,j);
	}
	void build_path(int i,int j){
		list<int>path;
		for(int node=j;node!=i;node=parent[node]){
			path.push_front(node);
		}
		path.push_front(i);
		for(int&i:path)cout<<i<<"=>";
		cout<<"end\n";
	}
	/*biparite graph => we can seperate nodes into two groups 
	without any connection between nodes in each group indvidually*/
	bool bipartite(int i,int c=1){
		if(color[i])return color[i]==c;
		color[i]=c;
		for(int&child:graph[i]){
				if(not bipartite(child,-c))return false;
		}
		return true;
	}
	/*to get tree diameter => dfs from any point and get the most far one from this node
	then dfs from the answer point to reach the most far point from last one=>this is the diameter of the tree
	
	*/
};
void solve() {
	GRAPH a(true);
	a.bfs(1,6);
	//cout<<(a.directed_cylces(1,-1)?"YES":"NO")<<endl;
}
int main() {
	IO;
	FIO
	solve();
	return 0;
}
/*
5 6
1 2
1 3
1 4
2 3
2 5                          
4 5
*/
