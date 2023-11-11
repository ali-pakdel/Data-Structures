#include <iostream>
#include <vector>

using namespace std;

class Graph
{
public:
	Graph(int n_)
	{
		n = n_;
		vector<int> b{ -1 };
		vector<vector<int>> a(n_ + 1, b);
		adj = a;
	}
	void add_vertex(int u, int v);
	bool check_odd_cycle(int i, vector<bool>& visited, vector<int>& colors);
private:
	int n;
	vector<vector<int>> adj;
};

void Graph::add_vertex(int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

bool Graph::check_odd_cycle(int i, vector<bool>& visited, vector<int>& colors)
{
	for (int j = 1; j < adj[i].size(); j++)
	{
		if (visited[adj[i][j]] == false)
		{
			visited[adj[i][j]] = true;
			colors[adj[i][j]] = !colors[i];
			if (check_odd_cycle(adj[i][j], visited, colors))
				return true;
		}
		else if (colors[i] == colors[adj[i][j]])
			return true;
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	long int n, m;
	cin >> n >> m;
	vector<pair<int, int>> edges;
	Graph g = Graph(n);
	if (m == 0)
	{
		cout << "NO" << endl;
		return 0;
	}
	vector<int> colors(n+1, 0);
	vector<bool> visited(n+1, false);

	for (long int i = 0; i < m; i++)
	{
		long int v1, v2;
		cin >> v1 >> v2;
		g.add_vertex(v1, v2);
		edges.push_back(make_pair(v1, v2));
	}
	bool odd = false;
	visited[1] = true;
	colors[1] = 1;
	odd = g.check_odd_cycle(1, visited, colors);
	if (odd == true)
	{
		cout << "NO" << endl;
		return 0;
	}
	for (int i = 1; i < n + 1; i++)
	{
		if (visited[i] == false)
			odd = g.check_odd_cycle(i, visited, colors);
		if (odd == true)
			break;
	}
	if (odd == true)
	{
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	for (long int i = 0; i < edges.size(); i++)
	{
		if (colors[edges[i].first] == true)
			cout << 0;
		else
			cout << 1;
	}
	cout << endl;
}