#include <iostream>
#include <vector>

using namespace std;

class Graph 
{
public:
	Graph(long int _n);
	void add_edge(long int v, long int u);
	void add_cost(long int c);

	vector<vector<long int>> find_strong_component();
	vector<long int> first_graph();
	vector<vector<long int>> second_graph(vector<long int> stk);
	void calculate_cost(vector<vector<long int>> comps);

	void inverse_edges();

private:
	long int n;
	vector<vector<long int>> adj;
	vector<vector<long int>> inv_adj;
	vector<long int> cost;
	void first_DFS(long int v, vector<bool>& visited, vector<long int> &stk);
	void sec_DFS(long int v, vector<bool>& visited, vector<long int>& vers);
	long int find_min(vector<long int> vers);
	long int find_amount(vector<long int> vers, long int min);

};

Graph::Graph(long int _n) 
{
	vector<long int> temp{-1};
	cost.push_back(0);

	vector<vector<long int>> tempp(_n + 1, temp);
	adj = tempp;
	inv_adj = tempp;
	n = _n;
}

void Graph::sec_DFS(long int v, vector<bool>& visited, vector<long int>& vers) {
	visited[v] = true;
	vers.push_back(v);

	for (long int i = 1; i < inv_adj[v].size(); i++)
		if (visited[inv_adj[v][i]] == false)
			sec_DFS(inv_adj[v][i], visited, vers);
}

void Graph::inverse_edges() {
	for (long int v = 1; v <= n; v++)
		for (long int i = 1; i < adj[v].size(); i++)
			inv_adj[adj[v][i]].push_back(v);
}

void Graph::add_edge(long int v, long int u) 
{
	adj[v].push_back(u);	
}

void Graph::add_cost(long int c)
{
	cost.push_back(c);
}

void Graph::first_DFS(long int v, vector<bool>& visited, vector<long int> &stk) {
	visited[v] = true;

	for (long int i = 1; i < adj[v].size(); i++)
		if (visited[adj[v][i]] == false)
			first_DFS(adj[v][i], visited, stk);

	stk.push_back(v);
}

vector<long int> Graph::first_graph() {
	vector<long int> stk;

	vector<bool> visited(n + 1, false);
		
	for (long int i = 1; i <= n; i++)
		if (visited[i] == false)
			first_DFS(i, visited, stk);
	return stk;
}

vector<vector<long int>> Graph::second_graph(vector<long int> stk)
{
	vector<vector<long int>> comps;
	vector<long int> vers;
	vector<bool> visited(n + 1, false);
	inverse_edges();

	while (stk.size()) {
		long int v = stk[stk.size() - 1];
		stk.erase(stk.begin() + stk.size() - 1);

		if (visited[v] == false) {
			sec_DFS(v, visited, vers);
			comps.push_back(vers);
			vers.clear();
		}
	}
	return comps;
}

vector<vector<long int>> Graph::find_strong_component()
{
	vector<long int> stk = first_graph();
	vector<vector<long int>> comps = second_graph(stk);
	return comps;
}

void Graph::calculate_cost(vector<vector<long int>> comps)
{
	long int min_cost = 0;
	long int ways = 1;
	for (long int i = 0; i < comps.size(); i++)
	{
		long int min = find_min(comps[i]);
		long int amount = find_amount(comps[i], min);
		min_cost += min;
		ways *= amount;
	}
	cout << min_cost << " " << ways % (1000000007) << endl;
}

long int Graph::find_min(vector<long int> vers)
{
	long long int min = cost[vers[0]];
	for (long long int i = 1; i < vers.size(); i++)
		if (cost[vers[i]] < min)
			min = cost[vers[i]];
	return min;
}

long int Graph::find_amount(vector<long int> vers, long int min)
{
	long int amount = 0;
	for (long int i = 0; i < vers.size(); i++)
		if (cost[vers[i]] == min)
			amount += 1;
	return amount;
}

int main() {
	long int n, x, m, v, u;
	cin >> n;
	Graph g = Graph(n);
	vector<long int> cost(n+1, 0);

	for (long int i = 1; i <= n; i++)
	{
		cin >> x;
		g.add_cost(x);
	}

	cin >> m;
	for (long int i = 0; i < m; i++)
	{
		cin >> v >> u;
		g.add_edge(v, u);
	}

	vector<vector<long int>> strongs = g.find_strong_component();
	g.calculate_cost(strongs);
}