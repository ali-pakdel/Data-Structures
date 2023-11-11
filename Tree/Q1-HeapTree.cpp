#include <iostream>
#include <vector>

using namespace std;

class Klass
{
public:
	Klass(long int id) { index = id; }
	long int get_index() { return index; }
	void insert(long int grade);
	void increase_grades(long int x);
	long int get_min() { if (grades.size()) return grades[0]; }
	void delete_min();
	bool is_empty() { if (grades.size()) return false; return true; }
	void fix_down(long int i);
	vector<long int> grades;


private:
	long int index;
};

void Klass::delete_min()
{
	swap(grades[0], grades[grades.size() - 1]);
	grades.pop_back();
	fix_down(0);
}

void Klass::insert(long int grade)
{
	grades.push_back(grade);
	long int i = grades.size() - 1;
	while (i  && grades[(i-1)/2] > grades[i])
	{
		swap(grades[i], grades[(i-1)/2]);
		i = (i-1)/2;
	}	
}

void Klass::increase_grades(long int x)
{
	for (long int i = 0; i < grades.size(); i++)
		grades[i] += x;
}

void Klass::fix_down(long int i)
{
	long int min = i;

	if (2 * i + 1 < grades.size() && grades[i * 2 + 1] < grades[i])
		min = i * 2 + 1;

	if (i * 2 + 2 < grades.size() && grades[i * 2 + 2] < grades[min])
		min = i * 2 + 2;

	if (min != i) {
		swap(grades[i], grades[min]);
		fix_down(min);
	}
}

class School
{

public:
	void insert_class(Klass key);
	void insert_std(long int c, long int g);
	void increase_grades(long int c, long int x);
	long int get_minimum();

private:
	vector<Klass> school;
	vector<long int> idx;

	void fix_down(long int i);
	void fix_up(long int i);
};

void School::fix_down(long int i)
{
	long int min = i;

	if (school[i].grades.size() != 0)
	{
		if (2 * i + 1 < school.size())
			if (school[2 * i + 1].grades.size() != 0)
				if (school[2 * i + 1].get_min() < school[i].get_min() || school[2*i+1].get_min() == school[i].get_min())
					min = 2 * i + 1;

		if (2 * i + 2 < school.size())
			if (school[2 * i + 2].grades.size() != 0)
				if (school[2 * i + 2].get_min() < school[min].get_min() || school[2*i+2].get_min() == school[min].get_min())
					min = 2 * i + 2;
	}

	else
	{
		if (2 * i + 2 < school.size())
		{
			if (school[2 * i + 1].grades.size() != 0 && school[2 * i + 2].grades.size() != 0)
			{
				if (school[2 * i + 1].get_min() < school[2 * i + 2].get_min() || school[2*i+1].get_min() == school[2*i+2].get_min())
					min = 2 * i + 1;

				else if (school[2 * i + 1].get_min() > school[2 * i + 2].get_min() || school[2*i+1].get_min() == school[2*i+2].get_min())
					min = 2 * i + 2;
			}
			else if (school[2 * i + 1].grades.size() == 0 && school[2 * i + 2].grades.size() != 0)
				min = 2 * i + 2;

			else if (school[2 * i + 1].grades.size() != 0 && school[2 * i + 2].grades.size() == 0)
				min = 2 * i + 1;
		}

		else if (2 * i + 2 < school.size() && school[2 * i + 1].grades.size() != 0)
			min = 2 * i + 2;

		else if (2 * i + 2 < school.size() && school[2 * i + 1].grades.size() == 0)
			min = 2 * i + 1;
	}
	if (min != i)
	{
		swap(school[i], school[min]);
		swap(idx[school[i].get_index()], idx[school[min].get_index()]);

		fix_down(min);
	}
}

void School::fix_up(long int i)
{
	if (i && (school[(i - 1) / 2].grades.size() == 0 || school[(i - 1) / 2].get_min() > school[i].get_min()))
	{
		swap(school[i], school[(i - 1) / 2]);
		swap(idx[school[i].get_index()], idx[school[(i - 1) / 2].get_index()]);

		fix_up((i - 1) / 2);
	}
}

void School::insert_class(Klass key)
{
	school.push_back(key);
	idx.push_back(school.size() - 1);
}

void School::insert_std(long int c, long int g)
{
	long int i = idx[c - 1];
	school[i].insert(g);
	fix_up(i);
}

void School::increase_grades(long int c, long int x)
{
	long int i = idx[c - 1];
	school[i].increase_grades(x);
	fix_down(i);
	fix_up(i);

}

long int School::get_minimum()
{
	if (school[0].grades.size() == 0)
		return -1;

	long int i = school[0].get_min();
	school[0].delete_min();
	fix_down(0);
	return i;
}


int main()
{
	long int n, q, c, t, x;
	cin >> n >> q;
	School big_heap;
	for (long int i = 0; i < n; i++)
	{
		Klass clas(i);
		big_heap.insert_class(clas);
	}
	for (long int i = 0; i < q; i++)
	{
		cin >> t;
		if (t == 1)
		{
			cin >> c >> x;
			big_heap.insert_std(c, x);
		}
		else if (t == 2)
		{
			cin >> c >> x;
			big_heap.increase_grades(c, x);
		}
		else
			cout << big_heap.get_minimum() << endl;
	}
}