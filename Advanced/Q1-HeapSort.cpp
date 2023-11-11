#include <iostream>
#include <vector>

using namespace std;

void merge_sort(vector<pair<long int, long int>>& vec, long int vec_len)
{
	if (vec_len <= 1)
		return;
	long int m = vec_len / 2;

	vector<pair<long int, long int>> left = vector<pair<long int, long int>>(vec.begin(), vec.begin() + m);
	vector<pair<long int, long int>> right = vector<pair<long int, long int>>(vec.begin() + m, vec.end());

	long int left_len = m, right_len = vec_len - m;

	merge_sort(left, left_len);
	merge_sort(right, right_len);

	long int i = 0, j = 0, k = 0;
	while (i < left_len && j < right_len)
	{
		if (left[i].second < right[j].second)
		{
			vec[k] = left[i];
			i++;
		}
		else
		{
			vec[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < left_len)
	{
		vec[k] = left[i];
		i++;
		k++;
	}
	while (j < right_len)
	{
		vec[k] = right[j];
		j++;
		k++;
	}
}

class Sol
{
public:
	Sol(long int _n);
	void add_dist(long int i, long int _dist);
	void add_cost(long int c);
	void find_min_cost();
	void add_capacity(long int z);
	void print();
	int check_capacity();

private:
	pair<long int, long int> find_best_city();
	void move_frw(long int city);
	void buy_choc(pair<long int, long int> city);
	bool move_next();
	void fill_choc();
	void buy_this(long int must_have);
	void move_one();
	void move_one2();

	long int n;

	long int choc;
	long int capacity;

	long int cur_city;
	long int spend;

	long int last_buy;

	vector<pair<long int, long int>> dist;
	vector<long int> cost;

	pair<long int, long int> bcc;
	int bc = 0;

};

Sol::Sol(long int _n)
{
	n = _n;
	cost.push_back(0);
	spend = 0;
}

void Sol::add_dist(long int i, long int d)
{
	dist.push_back(make_pair(i, d));
}

void Sol::add_cost(long int c)
{
	cost.push_back(c);
}

void Sol::add_capacity(long int z)
{
	capacity = z;
	choc = capacity;
}

void Sol::print()
{
	if (spend != -1)
		cout << spend << endl;
}

void Sol::fill_choc()
{
	long int b = capacity - choc;
	spend += (b * cost[dist[cur_city].first]);
	choc = capacity;
}

void Sol::buy_this(long int must_have)
{
	long int b = must_have - choc;
	spend += b * cost[dist[cur_city].first];
	choc += b;
}

void Sol::find_min_cost()
{
	merge_sort(dist, n);
	choc -= dist[0].second;
	cur_city = 0;

	if (choc < 0)
	{
		cout << -1 << endl;
		exit(0);
	}

	while (cur_city < n - 1)
	{
		if (dist[n - 1].second - dist[cur_city].second <= choc)
			break;
		if (bc == 1)
		{
			if (choc >= dist[bcc.first].second - dist[cur_city].second)
			{
				choc -= dist[bcc.first].second - dist[cur_city].second;
				cur_city = bcc.first;
				bc = 0;
				continue;
			}
		}
		if (move_next() == false)
		{
			pair<long int, long int> best_city = find_best_city();
			if (best_city.first == -2 && bc == 0)
				move_one();
			else if(best_city.first == -2 && bc == 1)
			{
				move_one2();
			}
		}
		
	}

}

void Sol::move_one2()
{
	long int need = dist[cur_city + 1].second - dist[cur_city].second;
	if (need > capacity)
	{
		cout << -1 << endl;
		exit(0);
	}
	fill_choc();
	choc -= need;
	cur_city++;
	bcc.second -= need;

	if (bcc.second <= capacity)
	{
		if (choc >= bcc.second)
		{
			choc -= bcc.second;
			cur_city = bcc.first;
			bc = 0;
		}
	}
}

void Sol::move_one()
{
	long int need = dist[cur_city + 1].second - dist[cur_city].second;
	if (need > capacity)
	{
		cout << -1 << endl;
		exit(0);
	}
	fill_choc();
	choc -= need;
	cur_city++;
}
bool Sol::move_next()
{
	if (cost[dist[cur_city].first] >= cost[dist[cur_city + 1].first])
	{
		if (choc >= dist[cur_city + 1].second - dist[cur_city].second)
		{
			choc -= dist[cur_city + 1].second - dist[cur_city].second;
			cur_city++;
			return true;
		}
		else
		{
			long int c = dist[cur_city + 1].second - dist[cur_city].second;
			if (c > capacity)
			{
				cout << -1 << endl;
				exit(0);
			}
			pair<long int, long int> city(cur_city + 1, c);
			buy_choc(city);
			choc -= c;
			cur_city++;
			return true;
		}
	}
	return false;
}

void Sol::buy_choc(pair<long int, long int> city)
{
	long int must_buy = city.second - choc;
	long int b = 0;
	if (choc + must_buy > capacity)
	{
		cout << -1 << endl;
		exit(0);
	}
	else
		b = must_buy;

	spend += (b * cost[dist[cur_city].first]);
	choc += b;
}

void Sol::move_frw(long int city)
{
	for (long int i = cur_city + 1; i <= city; i++)
	{
		choc -= (dist[i].second - dist[i - 1].second);
		cur_city += 1;
	}
}

pair<long int, long int> Sol::find_best_city()
{
	long int cur_price = cost[dist[cur_city].first];
	long int temp_choc = choc;
	pair<long int, long int> b_city_spend(-1, 0);
	long int must_have = 0;
	int flag = 0;


	for (long int i = cur_city + 1; i < n; i++)
	{
		must_have += (dist[i].second - dist[i - 1].second);

		if (must_have > capacity)
		{
			if (b_city_spend.first == -1)
			{
				must_have -= (dist[i].second - dist[i - 1].second);
				for (int j = i; j < n; j++)
				{
					must_have += (dist[j].second - dist[j - 1].second);
					if (cost[dist[j].first] <= cost[dist[cur_city].first])
					{
						bc = 1;
						bcc.first = j;
						bcc.second = must_have;
						break;
					}
					
				}
				b_city_spend.first = -2;
				return b_city_spend;
			}
			else
			{
				if (must_have > choc)
				{
					buy_this(b_city_spend.second);
					cur_city = b_city_spend.first;
					choc -= b_city_spend.second;
					return b_city_spend;
				}
				else if (must_have < choc)
				{
					choc -= b_city_spend.second;
					cur_city = b_city_spend.first;
					return b_city_spend;
				}
			}
		}
		if (cost[dist[i].first] <= cur_price)
			if (b_city_spend.first == -1)
			{
				b_city_spend.first = i;
				b_city_spend.second = must_have;
				cur_price = cost[dist[i].first];
				flag = 1;
				break;
			}
	}
	if (flag == 1)
	{
		if (choc >= b_city_spend.second)
			choc -= b_city_spend.second;
		else
		{
			buy_this(b_city_spend.second);
			choc -= b_city_spend.second;
		}
		cur_city = b_city_spend.first;
		return b_city_spend;
	}
	if (b_city_spend.first != -1)
	{
		if (choc >= b_city_spend.second)
			choc -= b_city_spend.second;
		else
		{
			buy_this(b_city_spend.second);
			choc -= b_city_spend.second;
		}
		cur_city = b_city_spend.first;
		return b_city_spend;
	}
	else
	{
		if (choc >= must_have)
			choc -= must_have;
		else
		{
			buy_this(must_have);
			choc -= must_have;
		}
		cur_city = n - 1;
		return b_city_spend;
	}
}

int Sol::check_capacity()
{
	if (dist[0].second > capacity)
	{
		cout << -1 << endl;
		return 1;
	}
	for (int i = 1; i < n; i++)
	{
		if (dist[i].second - dist[i - 1].second > capacity)
		{
			cout << -1 << endl;
			return 1;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	long int n, c, d, z;
	cin >> n;

	Sol s = Sol(n);

	for (long int i = 1; i <= n; i++)
	{
		cin >> d;
		s.add_dist(i, d);
	}
	for (long int i = 1; i <= n; i++)
	{
		cin >> c;
		s.add_cost(c);
	}
	cin >> z;
	s.add_capacity(z);


	s.find_min_cost();
	s.print();
}