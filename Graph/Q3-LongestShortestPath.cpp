#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph
{
public:
	Graph(int n_)
	{
		n = n_;
		vector<int> b{-1};
		vector<vector<int>> a(n_ + 1, b);
		adj = a;
		vector<int> d(n+1, 0);
		degrees = d;
	}
	void add_vertex(int u, int v);
	vector<int> min_longest_paths();
	void find_leaves();
	vector<int> get_leaves() { return leaves; }

private:
	int n;
	vector<int> degrees;
	vector<int> leaves;
	vector<vector<int>> adj;
};

void Graph::add_vertex(int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
	degrees[u]++;
	degrees[v]++;
}

void Graph::find_leaves()
{
	for (int i = 1; i < degrees.size(); i++)
		if (degrees[i] == 1)
			leaves.push_back(i);
}

vector<int> Graph::min_longest_paths()
{
	while (n > 2)
	{
		n -= leaves.size();	
		vector<int> new_leaves;

		for (int i = 0; i < leaves.size(); i++)
		{
			int v = leaves[i];
			
			int neigh = adj[v][1];
			for (int j = 1; j < adj[neigh].size(); j++)
			{
				if (adj[neigh][j] == v)
				{
					adj[neigh].erase(adj[neigh].begin() + j);
					break;
				}
			}
			degrees[neigh]--;

			if (degrees[neigh] == 1)
				new_leaves.push_back(neigh);
		}
		leaves = new_leaves;
	}
	return leaves;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	Graph g = Graph(n);
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		g.add_vertex(u, v);
	}
	if (n <= 2)
	{
		g.find_leaves();
		for (int i = 0; i < g.get_leaves().size(); i++)
			cout << g.get_leaves()[i] << " ";
	}
	else
	{
		g.find_leaves();
		vector<int> vertices = g.min_longest_paths();
		sort(vertices.begin(), vertices.end());
		for (int i = 0; i < vertices.size(); i++)
			cout << vertices[i] << " ";
	}


}