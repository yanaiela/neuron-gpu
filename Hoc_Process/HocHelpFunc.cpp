#include "HocHelpFunc.h"
#include "Defs.h"



vector<int> HocHelpFunc::VectorComparison(vector<int> vec1, vector<int> vec2)
{
	if (vec1.size() == ONE)
	{
		return HocHelpFunc::VectorComparison(vec2, vec1[ZERO]);
	}
	else if (vec2.size() == ONE)
	{
		return HocHelpFunc::VectorComparison(vec1, vec2[ZERO]);
	}

	vector<int> comparison;

	for (size_t i = 0; i < vec1.size(); i++)
	{
		if (vec1[i] == vec2[i])
		{
			comparison.push_back(ONE);
		}
		else
		{
			comparison.push_back(ZERO);
		}
	}

	return comparison;
}

vector<int> HocHelpFunc::VectorComparison(vector<int> vec, int num)
{
	vector<int> comparison;
	
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] == num)
		{
			comparison.push_back(ONE);
		}
		else
		{
			comparison.push_back(ZERO);
		}
	}

	return comparison;
}

vector<int> HocHelpFunc::VectorComparison(int num, vector<int> vec)
{
	return HocHelpFunc::VectorComparison(vec, num);
}

/*******************/

vector<int> HocHelpFunc::VectorSmallerComparison(vector<int> vec1, vector<int> vec2)
{
	vector<int> comparison;

	if (vec2.size() == ONE)
	{
		return HocHelpFunc::VectorSmallerComparison(vec1, vec2[ZERO]);
	}
	else if (vec1.size() == ONE)
	{
		return HocHelpFunc::VectorSmallerComparison(vec1[ZERO], vec2);
	}

	for (size_t i = 0; i < vec1.size(); i++)
	{
		if (vec1[i] < vec2[i])
		{
			comparison.push_back(ONE);
		}
		else
		{
			comparison.push_back(ZERO);
		}
	}

	return comparison;
}

vector<int> HocHelpFunc::VectorSmallerComparison(vector<int> vec, int num)
{
	vector<int> comparison;

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] < num)
		{
			comparison.push_back(ONE);
		}
		else
		{
			comparison.push_back(ZERO);
		}
	}
	return comparison;
}

vector<int> HocHelpFunc::VectorSmallerComparison(int num, vector<int> vec)
{
	vector<int> comparison;

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] > num)
		{
			comparison.push_back(ONE);
		}
		else
		{
			comparison.push_back(ZERO);
		}
	}
	return comparison;
}

/*******************/

vector<int> HocHelpFunc::VectorSmallerEqualsComparison(vector<int> vec1, vector<int> vec2)
{
	vector<int> comparison;

	if (vec2.size() == ONE)
	{
		return HocHelpFunc::VectorSmallerEqualsComparison(vec1, vec2[ZERO]);
	}

	for (size_t i = 0; i < vec1.size(); i++)
	{
		if (vec1[i] <= vec2[i])
		{
			comparison.push_back(ONE);
		}
		else
		{
			comparison.push_back(ZERO);
		}
	}

	return comparison;
}

vector<int> HocHelpFunc::VectorSmallerEqualsComparison(vector<int> vec, int num)
{
	vector<int> comparison;
	int size = vec.size();
	comparison.resize(size);

	for (int i = 0; i < size; i++)
	{
		if (vec[i] <= num)
		{
			comparison[i] = ONE;
		}
		else
		{
			comparison[i] = ZERO;
		}
	}

	return comparison;
}

vector<int> HocHelpFunc::VectorSmallerEqualsComparison(int num, vector<int> vec)
{
	vector<int> comparison;
	int size = vec.size();
	comparison.resize(size);

	for (int i = 0; i < size; i++)
	{
		if (vec[i] >= num)
		{
			comparison[i] = ONE;
		}
		else
		{
			comparison[i] = ZERO;
		}
	}

	return comparison;
}

/*******************/

vector<int> HocHelpFunc::SubVector(vector<int> vec, int from, int to)
{
	vector<int> sub_vec;

	for (int i = from; i <= to; i++)
	{
		sub_vec.push_back(vec[i]);
	}

	return sub_vec;
}

vector<int> HocHelpFunc::SubVector(vector<int> vec, vector<int> indices_vec)
{
	vector<int> sub_vec;
	
	for (size_t i = 0; i < indices_vec.size(); i++)
	{
		sub_vec.push_back(vec[indices_vec[i]]); // TODO maby - 1. not sure.
	}

	return sub_vec;
}

/*******************/

vector<int> HocHelpFunc::FlipLr(vector<int> vec)
{
	vector<int> swap;

	for (int i = vec.size() - 1; i >= ZERO; i--)
	{
		swap.push_back(vec[i]);
	}

	return swap;
}


vector<int> HocHelpFunc::ConnectVectors(vector<int> vec1, vector<int> vec2)
{
	for (size_t i = 0; i < vec2.size(); i++)
	{
		vec1.push_back(vec2[i]);
	}
	return vec1;
}

/**
	Kind of the Ones funtion in matlab
*/
vector<int> HocHelpFunc::HomoVecNum(int size, int num)
{
	vector<int> vec(size);
	for (int i = 0; i < size; i++)
	{
		vec[i] = num;
	}
	return vec;
}



