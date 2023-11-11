#include <iostream>
#include <vector>

using namespace std;
int myXOR(int num1, int num2)
{
	int result = 0;
	bool result_bit;
	for (int i = 31; i >= 0; i--)
	{
		bool num1_bit = num1 & (1 << i);
		bool num2_bit = num2 & (1 << i);
		
		if (num1_bit & num2_bit)
			result_bit = 0;
		else
			result_bit = num1_bit | num2_bit;

		result <<= 1;
		result |= result_bit;
	}
	return result;
}
int main()
{
	int n, q, t, r, l, x, index;
	cin >> n >> q;
	vector<int> arr(n, 0);
	for (int i = 0; i < q; i++)
	{
		cin >> t;
		if (t == 1)
		{
			cin >> l >> r >> x;
			for (int j = l - 1; j < r; j++)
			{
				if (j < 0 || j >= n)
					continue;
				arr[j] = myXOR(arr[j], x);
			}
		}
		else
		{
			cin >> index;
			cout << arr[index - 1] << endl;
		}
	}

}