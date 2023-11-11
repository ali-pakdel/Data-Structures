#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

const long int m = 1000000007;
const long int p = 311;

class Sol
{
public:
	Sol(long int _len, vector<long int> idx, string _word, long int wa);
	void fill_text();
	void build_hash();

private:
	long int set_free(long int i, long int word_len);
	bool invalid_place(long int shared);
	void set_state(vector<long int> s) { state = s; }

	long int text_len;

	long int idx_amounts;
	vector<long int> index;
	string word;
	string rev_word;

	vector<long int> state;

	long int word_l;

	long int free;

	long int all_shares;

	vector<long int> hash;

};

Sol::Sol(long int _len, vector<long int> idx, string _word, long int wa)
{
	text_len = _len;

	index = idx;

	word = _word;
	rev_word = word;

	word_l = word.size();
	idx_amounts = wa;

	free = _len;

	all_shares = 0;
	vector<long int> a(word_l , -2);
	hash = a;
}


bool Sol::invalid_place(long int shared)
{
	long int indx1 = 0;
	long int indx2 = word_l - shared;
	long int hash1 = hash[indx1 + shared - 1] % m;

	if (indx1)
		hash1 = (m + (hash1 - hash[indx1 - 1]) % m) % m;

	long int hash2 = hash[indx2 + shared - 1] % m;
	if (indx2)
		hash2 = (m + (hash2 - hash[indx2 - 1]) % m) % m;

	if (hash1 * state[indx2 - indx1] % m == hash2 % m)
		return false;
	else
		return true;
}

void Sol::build_hash()
{
	vector<long int> state(word_l);
	state[0] = 1;


	for (int i = 1; i < word_l; i++) 
		state[i] = (m + (state[i - 1] * p) % m) % m;

	for (int i = 0; i < word_l; i++) 
	{
		hash[i] = (m + (word[i] - 96) * state[i] % m) % m;
		if (i >= 1)
			hash[i] = (m + (hash[i] + hash[i - 1]) % m) % m;
	}

	set_state(state);

	//for (int i = 1; i < word_l; i++)
	//{
	//	string str = word.substr(0, i);
	//	hash1[i] = hassh(str, i);
	//}

	//int j = word_l - 1;
	//for (int i = 0; i < word_l - 1; i++)
	//{
	//	word.erase(word.begin() + 0);
	//	hash2[j] = hassh(word, j);
	//	j--;
	//}
}

void Sol::fill_text()
{
	build_hash();
	long int word_len = word.size();

	if (idx_amounts)
		if (index[idx_amounts - 1] + word_len - 1 > text_len)
		{
			cout << 0 << endl;
			return;
		}

	for (int j = 1; j < idx_amounts; j++)
	{
		if (index[j - 1] + word_len - 1 >= index[j])
		{
			long int shared = (index[j - 1] + word_len - index[j]);
			all_shares += shared;
			if (invalid_place(shared))
			{
				cout << 0 << endl;
				return;
			}
			//for (int i = 0; i < shared; i++)
			//{
			//	if (word[i] != word[word_len - shared + i])
			//	{
			//		cout << 0 << endl;
			//		return;
			//	}
			//}
		}
	}
	free = free - (idx_amounts * word_len) + all_shares;
	/*for (long int i = 0; i < idx_amounts; i++)
	{
		
		for (long int j = 0; j < word_len; j++)
		{

			if (text[index[i] + j] == 0 || text[index[i] + j] == int(word[j]) - 96)
			{
				if (text[index[i] + j] == 0)
					free--;
				text[index[i] + j] = int(word[j]) - 96;
			}
			else
			{
				cout << 0 << endl;
				exit(0);
			}
		}
	}*/
	long int x = 1;
	for (long int j = 0; j < free; j++)
	{
		x = x * 26;
		x = x % 1000000007;
	}
	if (free)
		cout << x << endl;
	else
		cout << 1 << endl;
}

long int Sol::set_free(long int i, long int word_len)
{
	if (i == 0)
		return free - word_len;
	
	if (index[i] - index[i - 1] >= word_len)
		return free - word_len;

	return free - word_len + (index[i] - index[i - 1]);
}

int main()
{
	long int n, m, x;
	vector<long int> index;
	string word;
	cin >> n >> m;
	cin >> word;
	for (long int i = 0; i < m; i++)
	{
		cin >> x;
		index.push_back(x);
	}
	if (n == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	if (m == 0)
	{
		long int x = 1;
		for (long int j = 0; j < n; j++)
		{
			x = x * 26;
			x = x % 1000000007;
		}
		cout << x << endl;
		return 0;
	}

	Sol s = Sol(n, index, word, m);
	s.fill_text();

}