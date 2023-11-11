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
		vector<vector<int>> a(n_ + 1);
		adj = a;
	}
	bool find_cycle(vector<int>& colors, vector<int>& parents,
		int x, int y, int k);
	void build(int m)
	{
		for (int i = 0; i < m; i++)
		{
			int u, v;
			cin >> u;
			cin >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
	}

private:
	int n;
	vector<vector<int>> adj;
};
bool Graph::find_cycle(vector<int>& colors, vector<int>& parents,
	int x, int y, int k)
{
	if (colors[x] == 1)
		return true;

	if (colors[x] == 2)
	{
		vector<int> cycle;
		int here = y;

		cycle.push_back(here);
		while (here != x)
		{
			cycle.push_back(parents[here]);
			here = parents[here];
		}
		if (cycle.size() >= k)
		{
			cout << cycle.size() << endl;
			for (int i = 0; i < cycle.size(); i++)
			{
				cout << cycle[i] << " ";
			}
			exit(0);
		}
		return false;
	}
	parents[x] = y;
	colors[x] = 2;

	for (int i = 0; i < adj[x].size() ; i++)
	{
		if (adj[x][i] == parents[x])
			continue;
		find_cycle(colors, parents, adj[x][i], x, k);
	}

	colors[x] = 1;
}


int main()
{
	int n, k, m;
	cin >> n;
	cin >> m;
	cin >> k;
	Graph g(n);
	g.build(m);
	vector<int> colors(n + 1, -1);
	vector<int> parents(n + 1, -1);

	if (g.find_cycle(colors, parents, 1, 0, k) == false)
		cout << -1 << endl;
}

