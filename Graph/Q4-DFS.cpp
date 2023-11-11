#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Point
{
	int x, y;
};
struct Element
{
	int x, y, d;
};
typedef vector<vector<bool> > Table;
class Farm
{
public:
	Farm(int n, int m);
	void fill_table(int i, int j);
	void find_source(int i, int j);
	void bfs();
	//bool is_valid(vector<vector<bool> > visited, int row, int col);
private:
	Table table;
	Table stars;

	int door_x;
	int door_y;
};

Farm::Farm(int n, int m)
{
	vector<bool> temp(m, false);
	Table temp2(n, temp);
	table = temp2;

	Table temp3(n, temp);
	stars = temp3;
}

void Farm::fill_table(int i, int j)
{
	char line;
	cin >> line;
	if (line == '#')
		table[i][j] = false;

	if (line == '-' || line == '*')
		table[i][j] = true;

	if (line == '*')
		stars[i][j] = true;

	find_source(i, j);
}

void Farm::find_source(int i, int j)
{
	cout << table.size() << " " << table[0].size();
	if (table[i][0] == true)
	{
		door_x = i;
		door_y = 0;
	}
	if (table[i][table[0].size() - 1] == true)
	{
		door_x = i;
		door_y = table[0].size() - 1;
	}

	if (table[0][j] == true)
	{
		door_x = 0;
		door_y = j;
	}
	if (table[table.size() - 1][j] == true)
	{
		door_x = table.size() - 1;
		door_y = j;
	}
}

int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };


bool is_valid(int n, int m, Table table, vector<vector<bool> > visited, int row, int col)
{
	return (row >= 0) && (row < table.size()) && (col >= 0) && (col < table[0].size()) && !visited[row][col] && table[row][col];
}

void Farm::bfs()
{
	int n = table.size();
	int m = table[0].size();
	vector<bool> temp(m, false);
	Table visited(n, temp);

	queue<Element> points;

	visited[door_x][door_y] = true;
	points.push({ door_x, door_y, 0 });

	int cur_dist = -10;
	int duplicates = 0;
	int max = -1;

	while (!points.empty())
	{
		Element e = points.front();
		points.pop();
		int dist = e.d, x = e.x, y = e.y;

		for (int i = 0; i < 4; i++)
			//if (is_valid(visited, x + row[i], y + col[i]))
			//{
			//	visited[x + row[i]][y + col[i]] = true;
			//	points.push({x + row[i], y + col[i], dist + 1});
			//}


			if (stars[x][y] == true)
			{
				if (dist != cur_dist)
				{
					if (dist <= cur_dist + duplicates)
					{
						duplicates++;
						dist = cur_dist + duplicates;
					}
					else
					{
						cur_dist = dist;
						duplicates = 0;
					}
				}
				else
				{
					duplicates++;
					dist = dist + duplicates;
				}
				if (max < dist)
					max = dist;
			}
	}
	cout << max + 1 << endl;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int m;
	int n;
	cin >> n;
	cin >> m;

	vector<bool> temp(m, false);
	Table table(n, temp);
	Table stars(n, temp);
	int door_x, door_y;


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			char line;
			cin >> line;
			if (line == '#')
				table[i][j] = false;

			if (line == '-' || line == '*')
				table[i][j] = true;

			if (line == '*')
				stars[i][j] = true;

			if (table[i][0] == true)
			{
				door_x = i;
				door_y = 0;
			}
			if (table[i][m-1] == true)
			{
				door_x = i;
				door_y = m-1;
			}

			if (table[0][j] == true)
			{
				door_x = 0;
				door_y = j;
			}
			if (table[n-1][j] == true)
			{
				door_x = n-1;
				door_y = j;
			}
		}
	}

	Table visited(n, temp);

	queue<Element> points;

	visited[door_x][door_y] = true;
	points.push({door_x, door_y, 0 });

	int cur_dist = -10;
	int duplicates = 0;
	int max = -10;

	while (!points.empty())
	{
		Element e = points.front();
		points.pop();
		int dist = e.d, x = e.x, y = e.y;

		for (int i = 0; i < 4; i++)
			if ((x + row[i] >= 0) && (x + row[i] < n)) 
				if ((y + col[i] >= 0) && (y+ col[i] < m))
					if (!visited[x+row[i]][y+col[i]] && table[x+row[i]][y+col[i]])
					{
							visited[x + row[i]][y + col[i]] = true;
							points.push({ x + row[i], y + col[i], dist + 1 });
					}

		if (stars[x][y] == true)
		{
			if (dist != cur_dist)
			{
				if (dist <= cur_dist + duplicates)
				{
					duplicates++;
					dist = cur_dist + duplicates;
				}
				else
				{
					cur_dist = dist;
					duplicates = 0;
				}
			}
			else
			{
				duplicates++;
				dist = dist + duplicates;
			}
			if (max < dist)
				max = dist;
		}
	}
	cout << max + 1 << endl;
}


