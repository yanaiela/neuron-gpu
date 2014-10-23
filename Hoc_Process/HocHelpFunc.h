#ifndef HOCHELPFUNC_H
#define HOCHELPFUNC_H


#include <vector>
#include "Defs.h"

using namespace std;


class HocHelpFunc
{

public:

	/**
		Kind of a mimic of the matlab find function.
		returns a vector of the indices of numbers that aren't zero's.
	*/
	template <typename T>
	static vector<T> Find(vector<T> vec);
	
	/**
		Works the same, just gets an input of an array
	*/
	template <typename T>
	static vector<T> Find(T arr[], int size);

	/**
		Also mimics another overload of the matlab function.
		searching for the num numbers that are'nt zero's. is start is true, starting from
		the begining, else - from the end.
	*/
	template <typename T>
	static vector<T> Find(vector<T> vec, int num, bool start);


	static vector<int> VectorComparison(vector<int> vec1, vector<int> vec2);
	static vector<int> VectorComparison(vector<int> vec, int num);
	static vector<int> VectorComparison(int num, vector<int> vec);

	/**
		If the vectors aren't from the same size, 
	*/
	static vector<int> VectorSmallerComparison(vector<int> vec1, vector<int> vec2);
	static vector<int> VectorSmallerComparison(vector<int> vec, int num);
	static vector<int> VectorSmallerComparison(int num, vector<int> vec);


	static vector<int> VectorSmallerEqualsComparison(vector<int> vec1, vector<int> vec2);
	static vector<int> VectorSmallerEqualsComparison(vector<int> vec, int num);
	static vector<int> VectorSmallerEqualsComparison(int num, vector<int> vec);
	/**
		@param vec - the vector which will get cut.
		@param from - the index of the first member that will be included
		@param to - the last member that will be included (include him).
	
	*/
	static vector<int> SubVector(vector<int> vec, int from, int to);
	static vector<int> SubVector(vector<int> vec, vector<int> indices_vec);

	/**
		Flips the vector so that the first element will be the last
		and so forth...
	*/
	static vector<int> FlipLr(vector<int> vec);

	static vector<int> ConnectVectors(vector<int> vec1, vector<int> vec2);

	static vector<int> HomoVecNum(int size, int num);
};


template<typename T>
vector<T> HocHelpFunc::Find(vector<T> vec)
{
	vector<T> bool_vec;

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] != ZERO)
		{
			bool_vec.push_back(i);
		}

	}
	return bool_vec;
}

template <typename T>
vector<T> HocHelpFunc::Find(T arr[], int size)
{
	vector<T> bool_vec;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] != ZERO)
		{
			bool_vec.push_back(i);
		}
	
	}
	
	return bool_vec;
}

template <typename T>
vector<T> HocHelpFunc::Find(vector<T> vec, int num, bool start)
{
	vector<T> bool_vec = Find(vec);
	if (bool_vec.size() == ZERO)
	{
		return bool_vec;
	}
	vector<T> sub_vec;
	
	int i = num;
	if (start)
	{
		int j = 0;
		while (i > 0)
		{
			sub_vec.push_back(bool_vec[j]);
	
			j++;
			i--;
		}
	}
	else
	{
		int j = bool_vec.size();
		while (i > 0)
		{
			sub_vec.push_back(bool_vec[j - ONE]);
	
			i--;
			j--;
		}
	}
	return sub_vec;
}

#endif